/* 
 * Copyright (C) 2010 Antoine Joux and Vanessa Vitse 

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 */

  /**
  * \file specialisation-echelonize-fflas-ffpack.inl
  * \brief Specialisation of echelonize method with fflas-ffpack.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_SPECIALISATION_ECHELONIZE_FFLAS_FFPACK_INL
#define F4_SPECIALISATION_ECHELONIZE_FFLAS_FFPACK_INL
    
using namespace std;

namespace F4
{
    #ifndef PARALLEL
    template <typename Element>
    int
    Matrix<Element>::echelonizeRight (chrono::duration<int,milli> & tmp_ech_db, chrono::duration<int,milli> & tmp_ech_dh)
    {
        chrono::steady_clock::time_point startc;
        typedef chrono::duration<int,milli> millisecs_t;
        typedef Givaro::ModularBalanced<double> Field;
        Field F(Element::getModulo());
        typename Field::Element * matrixRight = FFLAS::fflas_new (F,_height,_width-_nbPiv);
        typename Field::Element one, minusOne;
        size_t *P = new size_t[_height-_nbPiv]();
        size_t *Q = new size_t[_width-_nbPiv]();
        int ld=_width-_nbPiv;
        F.init(one,1);
        F.init(minusOne,-1);
        
        /* Convert left slice into FFLAS-FFPACK matrix */
        startc=chrono::steady_clock::now();
        for(int i=0; i<_height; i++)
        {
            for(int j=0; j<ld; j++)
            {
                F.init(matrixRight[i*ld+j], _matrix[i][_nbPiv+j].getElement());
            }
        }
        cout << "Time conversion 1: " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-startc).count() << " ms" << endl;
        
        typename Field::Element * B=matrixRight;
        typename Field::Element * D=matrixRight+_nbPiv*ld;
        
        startc=chrono::steady_clock::now();
        /* PLUQ(D) */
        int rank = (int)FFPACK::PLUQ (F, FFLAS::FflasUnit, (_height-_nbPiv), (_width-_nbPiv), D, ld, P, Q);
        /* D2 = D1^(-1) * D2 */
        FFLAS::ftrsm (F, FFLAS::FflasLeft, FFLAS::FflasUpper, FFLAS::FflasNoTrans, FFLAS::FflasUnit, rank, (_width-_nbPiv)-rank, one, D, ld, D+rank, ld);
        /* Suppress L */
        FFLAS::fidentity (F, rank, rank, D, ld);
        /* B = B * Q^T */
        FFPACK::applyP(F, FFLAS::FflasRight, FFLAS::FflasTrans, _nbPiv, 0, (_width-_nbPiv), B, ld, Q);
        /* Carry the column swap over */
        int exc=0;
        for(int i=0; i<ld; i++)
        {
            int l = _nbPiv+i;
            int ca = _nbPiv+Q[i];
            _tau[_sigma[l]] = ca;
            _tau[_sigma[ca]] = l;
            exc = _sigma[l];
            _sigma[l] = _sigma[ca];
            _sigma[ca] = exc;
            exc = _endCol[l];
            _endCol[l] = _endCol[ca];
            _endCol[ca] = exc;
        }
        
        tmp_ech_db=chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-startc);
        startc=chrono::steady_clock::now();
        /* B2 = B2 - B1 * D2 */
        FFLAS::fgemm(F, FFLAS::FflasNoTrans, FFLAS::FflasNoTrans, _nbPiv, (_width-_nbPiv)-rank, rank, minusOne, B , ld, D+rank, ld, one, B+rank, ld);
        /* B1 = 0 */
        FFLAS::fzero(F, _nbPiv, rank, B, ld);
        tmp_ech_dh=chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-startc);
        
        /* Convert the FFLAS-FFPACK matrix into integer matrix */
        startc=chrono::steady_clock::now();
        for(int i=0; i<_nbPiv+rank; i++)
        {
            for(int j=0; j<ld; j++)
            {
                _matrix[i][_nbPiv+j] = (int32_t)matrixRight[i*ld+j];
            }
        }
        cout << "Time conversion 2: " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-startc).count() << " ms" << endl;
        delete[] P;
        delete[] Q;
        FFLAS::fflas_delete(matrixRight);
        return _nbPiv+rank;
    }
    #endif // PARALLEL
    
    #ifdef PARALLEL
    template <typename Element>
    int
    Matrix<Element>::echelonizeRight (chrono::duration<int,milli> & tmp_ech_db, chrono::duration<int,milli> & tmp_ech_dh)
    {
        chrono::steady_clock::time_point startc;
        typedef chrono::duration<int,milli> millisecs_t;
        typedef Givaro::ModularBalanced<double> Field;
        Field F(Element::getModulo());
        typename Field::Element * matrixRight = FFLAS::fflas_new (F,_height,_width-_nbPiv);
        typename Field::Element one, minusOne;
        size_t *P = new size_t[_height-_nbPiv]();
        size_t *Q = new size_t[_width-_nbPiv]();
        int ld=_width-_nbPiv;
        int rank=0;
        F.init(one,1);
        F.init(minusOne,-1);
        
        /* Convert left slice into FFLAS-FFPACK matrix */
        startc=chrono::steady_clock::now();
        for(int i=0; i<_height; i++)
        {
            for(int j=0; j<ld; j++)
            {
                F.init(matrixRight[i*ld+j], _matrix[i][_nbPiv+j].getElement());
            }
        }
        cout << "Time conversion 1: " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-startc).count() << " ms" << endl;
        
        typename Field::Element * B=matrixRight;
        typename Field::Element * D=matrixRight+_nbPiv*ld;
        
        startc=chrono::steady_clock::now();
        /* PLUQ(D) */
        PAR_BLOCK{
            rank = (int)FFPACK::PLUQ (F, FFLAS::FflasUnit, (_height-_nbPiv), (_width-_nbPiv), D, ld, P, Q);
        }
        /* D2 = D1^(-1) * D2 */
        PAR_BLOCK{
            FFLAS::ftrsm (F, FFLAS::FflasLeft, FFLAS::FflasUpper, FFLAS::FflasNoTrans, FFLAS::FflasUnit, rank, (_width-_nbPiv)-rank, one, D, ld, D+rank, ld);
        }
        /* Suppress L */
        FFLAS::fidentity (F, rank, rank, D, ld);
        /* B = B * Q^T */
        PAR_BLOCK{
            FFPACK::applyP(F, FFLAS::FflasRight, FFLAS::FflasTrans, _nbPiv, 0, (_width-_nbPiv), B, ld, Q);
        }
        /* Carry the column swap over */
        int exc=0;
        for(int i=0; i<ld; i++)
        {
            int l = _nbPiv+i;
            int ca = _nbPiv+Q[i];
            _tau[_sigma[l]] = ca;
            _tau[_sigma[ca]] = l;
            exc = _sigma[l];
            _sigma[l] = _sigma[ca];
            _sigma[ca] = exc;
            exc = _endCol[l];
            _endCol[l] = _endCol[ca];
            _endCol[ca] = exc;
        }
        
        tmp_ech_db=chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-startc);
        startc=chrono::steady_clock::now();
        /* B2 = B2 - B1 * D2 */
        PAR_BLOCK{
            FFLAS::fgemm(F, FFLAS::FflasNoTrans, FFLAS::FflasNoTrans, _nbPiv, (_width-_nbPiv)-rank, rank, minusOne, B , ld, D+rank, ld, one, B+rank, ld);
        }
        /* B1 = 0 */
        FFLAS::fzero(F, _nbPiv, rank, B, ld);
        tmp_ech_dh=chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-startc);
        
        /* Convert the FFLAS-FFPACK matrix into integer matrix */
        startc=chrono::steady_clock::now();
        for(int i=0; i<_nbPiv+rank; i++)
        {
            for(int j=0; j<ld; j++)
            {
                _matrix[i][_nbPiv+j] = (int32_t)matrixRight[i*ld+j];
            }
        }
        cout << "Time conversion 2: " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-startc).count() << " ms" << endl;
        delete[] P;
        delete[] Q;
        FFLAS::fflas_delete(matrixRight);
        return _nbPiv+rank;
    }
    #endif // PARALLEL
    
    template <>
    int
    Matrix<ElementPrime<int16_t>>::echelonize ()
    {
        return echelonizePrime();
    }
    
    template <>
    int
    Matrix<ElementPrime<int32_t>>::echelonize ()
    {
        return echelonizePrime();
    }
    
    template <>
    int
    Matrix<ElementPrime<int64_t>>::echelonize ()
    {
        return echelonizePrime();
    }
    
    #ifndef PARALLEL
    template <typename Element>
    int
    Matrix<Element>::echelonizePrime ()
    {
        chrono::steady_clock::time_point start;
        typedef chrono::duration<int,milli> millisecs_t;
        millisecs_t tmp_ech_g, tmp_ech_db, tmp_ech_dh;
        int i, l, l2, ll;
        i = 0;
        l = 0;

        if (VERBOSE > 1)
        {
            printf ("Echelonization time: ");
        }

    #define TRANCHE 64
    
        /* Echelonize the left part of the matrix */
        start = chrono::steady_clock::now();
        for (l = _nbPiv - 1; l >= 0; l -= TRANCHE)
        {
            /* 1st slice */
            if (l < TRANCHE)
            {
                /* Triangular part */
                for (ll = l; ll > 0; ll--)
                {
                    /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                    normalizeRow(_matrix[ll], ll, _width);
                    for (l2 = 0; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
                /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                normalizeRow(_matrix[0], 0, _width);
                
                /* Low rectangular part (under  _nbPiv) */
                for (l2 = _nbPiv; l2 < _endCol[l]; l2++)
                {
                    for (ll = l; ll >= 0; ll--)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
            }
            /* Other slices */
            else
            {
                /* Triangular part */
                for (ll = l; ll > l - TRANCHE; ll--)
                {
                    /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                    normalizeRow(_matrix[ll], ll, _width);
                    for (l2 = l - TRANCHE + 1; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
                /* Hight rectangular part */ 
                for (l2 = 0; l2 <= l - TRANCHE; l2++)
                {
                    for (ll = l; ll > l - TRANCHE; ll--)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
                /* Low rectangular part (under  _nbPiv) */
                for (l2 = _nbPiv; l2 < _endCol[l]; l2++)
                {
                    for (ll = l; ll > l - TRANCHE; ll--)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
            }
        }
        tmp_ech_g = chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start);
        
        /* Echelonize the right part of the matrix */
        
        #define SEUIL_FFLAS_FFPACK 1000000
        
        if((_width-_nbPiv)*(_height-_nbPiv) > SEUIL_FFLAS_FFPACK)
        {
            int rank=echelonizeRight(tmp_ech_db, tmp_ech_dh);
            /* All the rows under the l-th row are zeros */ 
            for(l2=rank; l2<_height; l2++)
            {
                delete[] _matrix[l2];
            }
            _height=rank;
        }
        else
        {
            int ca = 0;
            int exc;
            Element inv, piv;
            
            /* Echelonize the low right part of the matrix */
            start = chrono::steady_clock::now();
            ca = _nbPiv;
            l = _nbPiv;
            while (l < _height)
            {
                for (; ca < _width; ca++)
                {
                    /* Search a pivot in column ca */
                    for (i = l; i < _height; i++)
                    {
                        /* Normalize in  [-MODULO/2, MODULO/2]. */
                        _matrix[i][ca].modulo();
                        if (!isZero(i,ca) )
                        {
                            break;
                        }
                    }
                    if (i < _height)
                    {
                        /* Pivot found in column ca */
                        break;          
                    }
                }
                if (ca == _width)
                {
                    /* All the rows under the l-th row are zeros */ 
                    for(l2=l; l2<_height; l2++)
                    {
                        delete[] _matrix[l2];
                    }
                    /* Forget all the zeros rows */
                    _height = l;
                }
                else
                {
                    /* Swap with the row containing the pivot */
                    swapRow(l,i);
                    if (ca != l)
                    {
                        /* Column swap */
                        ll = (_endCol[l] > _endCol[ca] ? _endCol[l] : _endCol[ca]);
                        swapCol(l,ca,0, ll);
                        swapCol(l, ca, _nbPiv, _height);
                        /* Carry the column swap over */
                        _tau[_sigma[l]] = ca;
                        _tau[_sigma[ca]] = l;
                        exc = _sigma[l];
                        _sigma[l] = _sigma[ca];
                        _sigma[ca] = exc;
                        exc = _endCol[l];
                        _endCol[l] = _endCol[ca];
                        _endCol[ca] = exc;
                    }
                    piv = _matrix[l][l];
                    inv = piv.inverse();
                    
                    /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                    multRow (_matrix[l], inv, ca + 1, _width);      
                    _matrix[l][l].setOne();
                    
                    /* Suppress the elements under the pivot */
                    for (l2 = l + 1; l2 < _height; l2++)
                    {
                        /* Normalize in  [-MODULO/2, MODULO/2]. */
                        _matrix[l2][l].modulo();
                        if (!isZero(l2,l) )
                        {
                            addMultRow (_matrix[l2], _matrix[l], -_matrix[l2][l], ca, _width);
                            _matrix[l2][l].setZero();
                        }
                    }
                    l++;
                    ca++;
                }
            }
            tmp_ech_db = chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start);

            /* Echelonize the hight right part of the matrix */
            start = chrono::steady_clock::now();

            /* Check _endCol */
            for (l = _nbPiv; l < _height - 1; l++)
            {
                if (_endCol[l + 1] < _endCol[l])
                {
                    fprintf (stderr, "_endCol hypothesis voided: please report\n");
                    exit (1);
                }
            }

            int min_endcol, max_endcol;
            for (l = _height - 1; l >= _nbPiv; l -= TRANCHE)
            {
                if (l < (_nbPiv + TRANCHE))
                {
                    /* 1st slice */
                    /* Triangular part */
                    for (ll = l; ll > _nbPiv; ll--)
                    {
                        /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                        normalizeRow(_matrix[ll], ll, _width);
                        for (l2 = _nbPiv; l2 < ll; l2++)
                        {
                            if (!isZero(l2,ll) )
                            {
                                /* Normalize in  [-MODULO/2, MODULO/2]. */
                                _matrix[l2][ll].modulo();
                                if (!isZero(l2,ll) )
                                {
                                    addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                    _matrix[l2][ll].setZero();
                                }
                            }
                        }
                    }
                    /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                    normalizeRow(_matrix[_nbPiv], _nbPiv, _width);
                    
                    max_endcol = _endCol[l];
                    min_endcol = _endCol[_nbPiv];
                    /* Upper rectangular part */
                    for (l2 = 0; l2 < min_endcol; l2++)
                    {
                        for (ll = l; ll >= _nbPiv; ll--)
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                    for (l2 = min_endcol; l2 < max_endcol; l2++)
                    {
                        for (ll = l; _endCol[ll] > l2; ll--)
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll))
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
                else
                {
                    /* Triangular part */
                    for (ll = l; ll > l - TRANCHE + 1; ll--)
                    {
                       /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                        normalizeRow(_matrix[ll], ll, _width);
                        for (l2 = l - TRANCHE + 1; l2 < ll; l2++)
                        {
                            if (!isZero(l2,ll) )
                            {
                                /* Normalize in  [-MODULO/2, MODULO/2]. */
                                _matrix[l2][ll].modulo();
                                if (!isZero(l2,ll) )
                                {
                                    addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                    _matrix[l2][ll].setZero();
                                }
                            }
                        }
                    }
                    /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                    normalizeRow(_matrix[l - TRANCHE + 1], l - TRANCHE + 1, _width);
                    
                    /* Upper rectangular part */
                    max_endcol = _endCol[l];
                    min_endcol = _endCol[l - TRANCHE + 1];
                    for (l2 = 0; l2 < min_endcol; l2++)
                    {
                        for (ll = l; ll > l - TRANCHE; ll--)
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                    for (l2 = min_endcol; l2 < max_endcol; l2++)
                    {
                        for (ll = l; _endCol[ll] > l2; ll--)
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                    for (l2 = _nbPiv; l2 <= l - TRANCHE; l2++)
                    {
                        for (ll = l; ll > l - TRANCHE; ll--)
                        {
                            if (!isZero(l2,ll) )
                            {
                                /* Normalize in  [-MODULO/2, MODULO/2]. */
                                _matrix[l2][ll].modulo();
                                if (!isZero(l2,ll) )
                                {
                                    addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                    _matrix[l2][ll].setZero();
                                }
                            }
                        }
                    }
                }
            }
            tmp_ech_dh = chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start);
        }
            
        /* Normalize the matrix */
        for (i = 0; i < _height; i++)
        {
            for (l = i; l < _width; l++)
            {
                _matrix[i][l].modulo();
            }
        }

        if (VERBOSE > 1)
        {
            cout << tmp_ech_g.count() << " + " << tmp_ech_db.count() << " + " << tmp_ech_dh.count() << " = " << (tmp_ech_g + tmp_ech_db + tmp_ech_dh).count() << " ms" << endl << endl;
        }
        return _height;
    }
    #endif // PARALLEL
    
    #ifdef PARALLEL
    template <typename Element>
    int
    Matrix<Element>::echelonizePrime ()
    {
        chrono::steady_clock::time_point start;
        typedef chrono::duration<int,milli> millisecs_t;
        millisecs_t tmp_ech_g, tmp_ech_db, tmp_ech_dh;
        int i, l, l2, ll;
        i = 0;
        l = 0;
        
        /* Thread parameters */
        omp_set_num_threads(NB_THREAD);
        int chunk = 1;

        if (VERBOSE > 1)
        {
            printf ("Echelonization time: ");
        }

    #define TRANCHE 64
    
        /* Echelonize the left part of the matrix */
        start = chrono::steady_clock::now();
        for (l = _nbPiv - 1; l >= 0; l -= TRANCHE)
        {
            /* 1st slice */
            if (l < TRANCHE)
            {
                /* Triangular part */
                for (ll = l; ll > 0; ll--)
                {
                    /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                    normalizeRow(_matrix[ll], ll, _width);
                    #pragma omp parallel for schedule(dynamic,chunk)
                    for (l2 = 0; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
                /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                normalizeRow(_matrix[0], 0, _width);
                
                /* Low rectangular part (under  _nbPiv) */
                #pragma omp parallel for private(ll) schedule(dynamic,chunk)
                for (l2 = _nbPiv; l2 < _endCol[l]; l2++)
                {
                    for (ll = l; ll >= 0; ll--)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
            }
            /* Other slices */
            else
            {
                /* Triangular part */
                for (ll = l; ll > l - TRANCHE; ll--)
                {
                    /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                    normalizeRow(_matrix[ll], ll, _width);
                    #pragma omp parallel for schedule(dynamic,chunk)
                    for (l2 = l - TRANCHE + 1; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
                /* Hight rectangular part */
                #pragma omp parallel 
                {
                    #pragma omp for private(ll) nowait schedule(dynamic,chunk)
                    for (l2 = 0; l2 <= l - TRANCHE; l2++)
                    {
                        for (ll = l; ll > l - TRANCHE; ll--)
                        {
                            if (!isZero(l2,ll) )
                            {
                                /* Normalize in  [-MODULO/2, MODULO/2]. */
                                _matrix[l2][ll].modulo();
                                if (!isZero(l2,ll) )
                                {
                                    addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                    _matrix[l2][ll].setZero();
                                }
                            }
                        }
                    }
                    /* Low rectangular part (under  _nbPiv) */
                    #pragma omp for private(ll) nowait schedule(dynamic,chunk)
                    for (l2 = _nbPiv; l2 < _endCol[l]; l2++)
                    {
                        for (ll = l; ll > l - TRANCHE; ll--)
                        {
                            if (!isZero(l2,ll) )
                            {
                                /* Normalize in  [-MODULO/2, MODULO/2]. */
                                _matrix[l2][ll].modulo();
                                if (!isZero(l2,ll) )
                                {
                                    addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                    _matrix[l2][ll].setZero();
                                }
                            }
                        }
                    }
                }
            }
        }
        tmp_ech_g = chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start);
        
        /* Echelonize the right part of the matrix */
        
        #define SEUIL_FFLAS_FFPACK 1000000
        
        if((_width-_nbPiv)*(_height-_nbPiv) > SEUIL_FFLAS_FFPACK)
        {
            int rank=echelonizeRight(tmp_ech_db, tmp_ech_dh);
            /* All the rows under the l-th row are zeros */ 
            for(l2=rank; l2<_height; l2++)
            {
                delete[] _matrix[l2];
            }
            _height=rank;
        }
        else
        {
            int ca = 0;
            int exc;
            Element inv, piv;
            
            /* Echelonize the low right part of the matrix */
            start = chrono::steady_clock::now();
            ca = _nbPiv;
            l = _nbPiv;
            while (l < _height)
            {
                for (; ca < _width; ca++)
                {
                    /* Search a pivot in column ca */
                    for (i = l; i < _height; i++)
                    {
                        /* Normalize in  [-MODULO/2, MODULO/2]. */
                        _matrix[i][ca].modulo();
                        if (!isZero(i,ca) )
                        {
                            break;
                        }
                    }
                    if (i < _height)
                    {
                        /* Pivot found in column ca */
                        break;          
                    }
                }
                if (ca == _width)
                {
                    /* All the rows under the l-th row are zeros */ 
                    for(l2=l; l2<_height; l2++)
                    {
                        delete[] _matrix[l2];
                    }
                    /* Forget all the zeros rows */
                    _height = l;
                }
                else
                {
                    /* Swap with the row containing the pivot */
                    swapRow(l,i);
                    if (ca != l)
                    {
                        /* Column swap */
                        ll = (_endCol[l] > _endCol[ca] ? _endCol[l] : _endCol[ca]);
                        swapCol(l,ca,0, ll);
                        swapCol(l, ca, _nbPiv, _height);
                        /* Carry the column swap over */
                        _tau[_sigma[l]] = ca;
                        _tau[_sigma[ca]] = l;
                        exc = _sigma[l];
                        _sigma[l] = _sigma[ca];
                        _sigma[ca] = exc;
                        exc = _endCol[l];
                        _endCol[l] = _endCol[ca];
                        _endCol[ca] = exc;
                    }
                    piv = _matrix[l][l];
                    inv = piv.inverse();
                    
                    /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                    multRow (_matrix[l], inv, ca + 1, _width);      
                    _matrix[l][l].setOne();
                    
                    /* Suppress the elements under the pivot */
                    #pragma omp parallel for schedule(dynamic,chunk)
                    for (l2 = l + 1; l2 < _height; l2++)
                    {
                        /* Normalize in  [-MODULO/2, MODULO/2]. */
                        _matrix[l2][l].modulo();
                        if (!isZero(l2,l) )
                        {
                            addMultRow (_matrix[l2], _matrix[l], -_matrix[l2][l], ca, _width);
                            _matrix[l2][l].setZero();
                        }
                    }
                    l++;
                    ca++;
                }
            }
            tmp_ech_db = chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start);

            /* Echelonize the hight right part of the matrix */
            start = chrono::steady_clock::now();

            /* Check _endCol */
            for (l = _nbPiv; l < _height - 1; l++)
            {
                if (_endCol[l + 1] < _endCol[l])
                {
                    fprintf (stderr, "_endCol hypothesis voided: please report\n");
                    exit (1);
                }
            }

            int min_endcol, max_endcol;
            for (l = _height - 1; l >= _nbPiv; l -= TRANCHE)
            {
                if (l < (_nbPiv + TRANCHE))
                {
                    /* 1st slice */
                    /* Triangular part */
                    for (ll = l; ll > _nbPiv; ll--)
                    {
                        /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                        normalizeRow(_matrix[ll], ll, _width);
                        #pragma omp parallel for schedule(dynamic,chunk)
                        for (l2 = _nbPiv; l2 < ll; l2++)
                        {
                            if (!isZero(l2,ll) )
                            {
                                /* Normalize in  [-MODULO/2, MODULO/2]. */
                                _matrix[l2][ll].modulo();
                                if (!isZero(l2,ll) )
                                {
                                    addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                    _matrix[l2][ll].setZero();
                                }
                            }
                        }
                    }
                    /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                    normalizeRow(_matrix[_nbPiv], _nbPiv, _width);
                    
                    max_endcol = _endCol[l];
                    min_endcol = _endCol[_nbPiv];
                    /* Upper rectangular part */
                    #pragma omp parallel
                    {
                        #pragma omp for private(ll) nowait schedule(dynamic,chunk)
                        for (l2 = 0; l2 < min_endcol; l2++)
                        {
                            for (ll = l; ll >= _nbPiv; ll--)
                            {
                                /* Normalize in  [-MODULO/2, MODULO/2]. */
                                _matrix[l2][ll].modulo();
                                if (!isZero(l2,ll) )
                                {
                                    addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                    _matrix[l2][ll].setZero();
                                }
                            }
                        }
                        #pragma omp for private(ll) nowait schedule(dynamic,chunk)
                        for (l2 = min_endcol; l2 < max_endcol; l2++)
                        {
                            for (ll = l; _endCol[ll] > l2; ll--)
                            {
                                /* Normalize in  [-MODULO/2, MODULO/2]. */
                                _matrix[l2][ll].modulo();
                                if (!isZero(l2,ll))
                                {
                                    addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                    _matrix[l2][ll].setZero();
                                }
                            }
                        }
                    }
                }
                else
                {
                    /* Triangular part */
                    for (ll = l; ll > l - TRANCHE + 1; ll--)
                    {
                       /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                        normalizeRow(_matrix[ll], ll, _width);
                        #pragma omp parallel for schedule(dynamic,chunk)
                        for (l2 = l - TRANCHE + 1; l2 < ll; l2++)
                        {
                            if (!isZero(l2,ll) )
                            {
                                /* Normalize in  [-MODULO/2, MODULO/2]. */
                                _matrix[l2][ll].modulo();
                                if (!isZero(l2,ll) )
                                {
                                    addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                    _matrix[l2][ll].setZero();
                                }
                            }
                        }
                    }
                    /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                    normalizeRow(_matrix[l - TRANCHE + 1], l - TRANCHE + 1, _width);
                    
                    /* Upper rectangular part */
                    max_endcol = _endCol[l];
                    min_endcol = _endCol[l - TRANCHE + 1];
                    #pragma omp parallel
                    {
                        #pragma omp for private(ll) nowait schedule(dynamic,chunk)
                        for (l2 = 0; l2 < min_endcol; l2++)
                        {
                            for (ll = l; ll > l - TRANCHE; ll--)
                            {
                                /* Normalize in  [-MODULO/2, MODULO/2]. */
                                _matrix[l2][ll].modulo();
                                if (!isZero(l2,ll) )
                                {
                                    addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                    _matrix[l2][ll].setZero();
                                }
                            }
                        }
                        #pragma omp for private(ll) nowait schedule(dynamic,chunk)
                        for (l2 = min_endcol; l2 < max_endcol; l2++)
                        {
                            for (ll = l; _endCol[ll] > l2; ll--)
                            {
                                /* Normalize in  [-MODULO/2, MODULO/2]. */
                                _matrix[l2][ll].modulo();
                                if (!isZero(l2,ll) )
                                {
                                    addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                    _matrix[l2][ll].setZero();
                                }
                            }
                        }
                        #pragma omp for private(ll) nowait schedule(dynamic,chunk)
                        for (l2 = _nbPiv; l2 <= l - TRANCHE; l2++)
                        {
                            for (ll = l; ll > l - TRANCHE; ll--)
                            {
                                if (!isZero(l2,ll) )
                                {
                                    /* Normalize in  [-MODULO/2, MODULO/2]. */
                                    _matrix[l2][ll].modulo();
                                    if (!isZero(l2,ll) )
                                    {
                                        addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                        _matrix[l2][ll].setZero();
                                    }
                                }
                            }
                        }
                    }
                }
            }
            tmp_ech_dh = chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start);
        }
            
        /* Normalize the matrix */
        #pragma omp parallel for private(l) schedule(dynamic,chunk)
        for (i = 0; i < _height; i++)
        {
            for (l = i; l < _width; l++)
            {
                _matrix[i][l].modulo();
            }
        }

        if (VERBOSE > 1)
        {
            cout << tmp_ech_g.count() << " + " << tmp_ech_db.count() << " + " << tmp_ech_dh.count() << " = " << (tmp_ech_g + tmp_ech_db + tmp_ech_dh).count() << " ms" << endl << endl;
        }
        return _height;
    }
    #endif // PARALLEL
}

#endif // F4_SPECIALISATION_ECHELONIZE_FFLAS_FFPACK_INL
