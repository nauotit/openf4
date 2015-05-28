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
  * \file specialisation-echelonize-gf2-extension.inl
  * \brief Specialisation of echelonize method for ElementGF2Extension type.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_SPECIALISATION_ECHELONIZE_GF2_EXTENSION_INL
#define F4_SPECIALISATION_ECHELONIZE_GF2_EXTENSION_INL
    
using namespace std;

namespace F4
{
    /* echelonize specialisation for ElementGF2Extension */
    
    template <>
    int
    Matrix<ElementGF2Extension<uint16_t>>::echelonize ()
    {
        return echelonizeGF2Extension();
    }
    
    template <>
    int
    Matrix<ElementGF2Extension<uint32_t>>::echelonize ()
    {
        return echelonizeGF2Extension();
    }
    
    template <>
    int
    Matrix<ElementGF2Extension<uint64_t>>::echelonize ()
    {
        return echelonizeGF2Extension();
    }
    
    /* normalizeRow specialisation for ElementGF2Extension */
    
    template <>
    void
    Matrix<ElementGF2Extension<uint16_t>>::normalizeRow(ElementGF2Extension<uint16_t> * row, int start, int end)
    {
        normalizeRowGF2Extension(row, start, end);
    }
    
    template <>
    void
    Matrix<ElementGF2Extension<uint32_t>>::normalizeRow (ElementGF2Extension<uint32_t> * row, int start, int end)
    {
        normalizeRowGF2Extension(row, start, end);
    }
    
    template <>
    void
    Matrix<ElementGF2Extension<uint64_t>>::normalizeRow (ElementGF2Extension<uint64_t> * row, int start, int end)
    {
        normalizeRowGF2Extension(row, start, end);
    }
    
    /* multRow specialisation for ElementGF2Extension */
    
    template <>
    void
    Matrix<ElementGF2Extension<uint16_t>>::multRow(ElementGF2Extension<uint16_t> * row, ElementGF2Extension<uint16_t> const & element, int start, int end)
    {
        multRowGF2Extension(row, element, start, end);
    }
    
    template <>
    void
    Matrix<ElementGF2Extension<uint32_t>>::multRow (ElementGF2Extension<uint32_t> * row, ElementGF2Extension<uint32_t> const & element, int start, int end)
    {
        multRowGF2Extension(row, element, start, end);
    }
    
    template <>
    void
    Matrix<ElementGF2Extension<uint64_t>>::multRow (ElementGF2Extension<uint64_t> * row, ElementGF2Extension<uint64_t> const & element, int start, int end)
    {
        multRowGF2Extension(row, element, start, end);
    }
    
    /* addMultRow specialisation for ElementGF2Extension */
    
    template <>
    void
    Matrix<ElementGF2Extension<uint16_t>>::addMultRow (ElementGF2Extension<uint16_t> * row1, ElementGF2Extension<uint16_t> * row2, ElementGF2Extension<uint16_t> element, int start, int end)
    {
        addMultRowGF2Extension(row1, row2, element, start, end);
    }
    
    template <>
    void
    Matrix<ElementGF2Extension<uint32_t>>::addMultRow (ElementGF2Extension<uint32_t> * row1, ElementGF2Extension<uint32_t> * row2, ElementGF2Extension<uint32_t> element, int start, int end)
    {
        addMultRowGF2Extension(row1, row2, element, start, end);
    }
    
    template <>
    void
    Matrix<ElementGF2Extension<uint64_t>>::addMultRow (ElementGF2Extension<uint64_t> * row1, ElementGF2Extension<uint64_t> * row2, ElementGF2Extension<uint64_t> element, int start, int end)
    {
        addMultRowGF2Extension(row1, row2, element, start, end);
    }
    
    /* Definition of normalizeRowGF2Extension, multRowGF2Extension, addMultRowGF2Extension, echelonizeGF2Extension */
    
    template <typename Element>
    void
    Matrix<Element>::normalizeRowGF2Extension(Element * row, int start, int end)
    {
        assert((start >= 0) && (end <= _width));
        for(int i=start; i<end; ++i)
        {
            row[i].modulo();
        }
    }
    
    template <typename Element>
    void
    Matrix<Element>::multRowGF2Extension(Element * row, Element const & element, int start, int end)
    {
        assert((start >= 0) && (end <= _width));
        for(int i=start; i<end; ++i)
        {
            row[i]*=element;
        }
    }
    
    template <typename Element>
    inline void
    Matrix<Element>::addMultRowGF2Extension(Element * row1, Element * row2, Element element, int start, int end)
    {
        assert((start >= 0) && (end <= _width));
        element.modulo();
        for(int i=start; i<end; ++i)
        {
            row1[i].addMult(row2[i], element);
        }
    }
    
    #ifndef PARALLEL
    template <typename Element>
    int
    Matrix<Element>::echelonizeGF2Extension ()
    {
        chrono::steady_clock::time_point start;
        typedef chrono::duration<int,milli> millisecs_t;
        millisecs_t tmp_ech_g, tmp_ech_db, tmp_ech_dh;
        int ca = 0;
        int i, l, l2, ll;
        i = 0;
        l = 0;
        Element piv, inv;
        int exc;

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
                    for (l2 = 0; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _startTail[ll], _width);
                            _matrix[l2][ll].setZero();
                        }
                    }
                }
                
                /* Low rectangular part (under  _nbPiv) */
                for (l2 = _nbPiv; l2 < _endCol[l]; l2++)
                {
                    for (ll = l; ll >= 0; ll--)
                    {
                        if (!isZero(l2,ll) )
                        {
                            addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _startTail[ll], _width);
                            _matrix[l2][ll].setZero();
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
                    for (l2 = l - TRANCHE + 1; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _startTail[ll], _width);
                            _matrix[l2][ll].setZero();
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
                            addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _startTail[ll], _width);
                            _matrix[l2][ll].setZero();
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
                            addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _startTail[ll], _width);
                            _matrix[l2][ll].setZero();
                        }
                    }
                }
            }
        }
        tmp_ech_g = chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start);
        
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
                    if (!isZero(l2,l) )
                    {
                        addMultRow (_matrix[l2], _matrix[l], _matrix[l2][l], ca, _width);
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
                    for (l2 = _nbPiv; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _height, _width);
                            _matrix[l2][ll].setZero();
                        }
                    }
                }
                
                max_endcol = _endCol[l];
                min_endcol = _endCol[_nbPiv];
                /* Upper rectangular part */
                for (l2 = 0; l2 < min_endcol; l2++)
                {
                    for (ll = l; ll >= _nbPiv; ll--)
                    {
                        if (!isZero(l2,ll) )
                        {
                            addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _height, _width);
                            _matrix[l2][ll].setZero();
                        }
                    }
                }
                for (l2 = min_endcol; l2 < max_endcol; l2++)
                {
                    for (ll = l; _endCol[ll] > l2; ll--)
                    {
                        if (!isZero(l2,ll))
                        {
                            addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _height, _width);
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
                    for (l2 = l - TRANCHE + 1; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _height, _width);
                            _matrix[l2][ll].setZero();
                        }
                    }
                }

                
                /* Upper rectangular part */
                max_endcol = _endCol[l];
                min_endcol = _endCol[l - TRANCHE + 1];
                for (l2 = 0; l2 < min_endcol; l2++)
                {
                    for (ll = l; ll > l - TRANCHE; ll--)
                    {
                        if (!isZero(l2,ll) )
                        {
                            addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _height, _width);
                            _matrix[l2][ll].setZero();
                        }
                    }
                }
                for (l2 = min_endcol; l2 < max_endcol; l2++)
                {
                    for (ll = l; _endCol[ll] > l2; ll--)
                    {
                        if (!isZero(l2,ll) )
                        {
                            addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _height, _width);
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
                            addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _height, _width);
                            _matrix[l2][ll].setZero();
                        }
                    }
                }
            }
        }
        tmp_ech_dh = chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start);

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
    Matrix<Element>::echelonizeGF2Extension ()
    {
        chrono::steady_clock::time_point start;
        typedef chrono::duration<int,milli> millisecs_t;
        millisecs_t tmp_ech_g, tmp_ech_db, tmp_ech_dh;
        int ca = 0;
        int i, l, l2, ll;
        i = 0;
        l = 0;
        Element piv, inv;
        int exc;
        
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
                    #pragma omp parallel for schedule(dynamic,chunk)
                    for (l2 = 0; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _startTail[ll], _width);
                            _matrix[l2][ll].setZero();
                        }
                    }
                }
                
                /* Low rectangular part (under  _nbPiv) */
                #pragma omp parallel for private(ll) schedule(dynamic,chunk)
                for (l2 = _nbPiv; l2 < _endCol[l]; l2++)
                {
                    for (ll = l; ll >= 0; ll--)
                    {
                        if (!isZero(l2,ll) )
                        {
                            addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _startTail[ll], _width);
                            _matrix[l2][ll].setZero();
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
                    #pragma omp parallel for schedule(dynamic,chunk)
                    for (l2 = l - TRANCHE + 1; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _startTail[ll], _width);
                            _matrix[l2][ll].setZero();
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
                                addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _startTail[ll], _width);
                                _matrix[l2][ll].setZero();
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
                                addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _startTail[ll], _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
            }
        }
        tmp_ech_g = chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start);
        
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
                    if (!isZero(l2,l) )
                    {
                        addMultRow (_matrix[l2], _matrix[l], _matrix[l2][l], ca, _width);
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
                    #pragma omp parallel for schedule(dynamic,chunk)
                    for (l2 = _nbPiv; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _height, _width);
                            _matrix[l2][ll].setZero();
                        }
                    }
                }
                
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
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _height, _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                    #pragma omp for private(ll) nowait schedule(dynamic,chunk)
                    for (l2 = min_endcol; l2 < max_endcol; l2++)
                    {
                        for (ll = l; _endCol[ll] > l2; ll--)
                        {
                            if (!isZero(l2,ll))
                            {
                                addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _height, _width);
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
                    #pragma omp parallel for schedule(dynamic,chunk)
                    for (l2 = l - TRANCHE + 1; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _height, _width);
                            _matrix[l2][ll].setZero();
                        }
                    }
                }

                
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
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _height, _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                    #pragma omp for private(ll) nowait schedule(dynamic,chunk)
                    for (l2 = min_endcol; l2 < max_endcol; l2++)
                    {
                        for (ll = l; _endCol[ll] > l2; ll--)
                        {
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _height, _width);
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
                                addMultRow (_matrix[l2], _matrix[ll], _matrix[l2][ll], _height, _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
            }
        }
        tmp_ech_dh = chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start);

        if (VERBOSE > 1)
        {
            cout << tmp_ech_g.count() << " + " << tmp_ech_db.count() << " + " << tmp_ech_dh.count() << " = " << (tmp_ech_g + tmp_ech_db + tmp_ech_dh).count() << " ms" << endl << endl;
        }
        return _height;
    }
    #endif // PARALLEL
}

#endif // F4_SPECIALISATION_ECHELONIZE_GF2_EXTENSION_INL
