/* 
 * Copyright (C) 2015 Antoine Joux, Vanessa Vitse and Titouan Coladon
 * 
 * This file is part of openf4.
 * 
 * openf4 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * openf4 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with openf4.  If not, see <http://www.gnu.org/licenses/>.
 */

  /**
  * \file specialisation-echelonize-gf2-extension.inl
  * \brief Specialisation of echelonize method for ElementGF2Extension type.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef OPENF4_SPECIALISATION_ECHELONIZE_GF2_EXTENSION_INL
#define OPENF4_SPECIALISATION_ECHELONIZE_GF2_EXTENSION_INL
    
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
        for(int i=start; i<end; ++i)
        {
            row1[i].addMult(row2[i], element);
        }
    }
    
    template <typename Element>
    void
    Matrix<Element>::doubleAddMultRowGF2Extension(Element * dest1, Element * dest2, Element mult1, Element mult2, Element * vec, int start, int end)
    {
        addMultRowGF2Extension(dest1, vec, mult1, start, end);
        addMultRowGF2Extension(dest2, vec, mult2, start, end);
    }
    
    template <typename Element>
    void
    Matrix<Element>::tripleAddMultRowGF2Extension(Element * dest1, Element * dest2, Element * dest3, Element mult1, Element mult2, Element mult3, Element * vec, int start, int end)
    {
        addMultRowGF2Extension(dest1, vec, mult1, start, end);
        addMultRowGF2Extension(dest2, vec, mult2, start, end);
        addMultRowGF2Extension(dest3, vec, mult3, start, end);
    }
    
    template <typename Element>
    void
    Matrix<Element>::quadAddMultRowGF2Extension(Element * dest1, Element * dest2, Element * dest3, Element * dest4, Element mult1, Element mult2, Element mult3, Element mult4, Element * vec, int start, int end)
    {
        addMultRowGF2Extension(dest1, vec, mult1, start, end);
        addMultRowGF2Extension(dest2, vec, mult2, start, end);
        addMultRowGF2Extension(dest3, vec, mult3, start, end);
        addMultRowGF2Extension(dest4, vec, mult4, start, end);
    }
    
    template <typename Element>
    void
    Matrix<Element>::octAddMultRowGF2Extension(Element * dest1, Element * dest2, Element * dest3, Element * dest4, Element * dest5, Element * dest6, Element * dest7, Element * dest8, Element mult1, Element mult2, Element mult3, Element mult4, Element mult5, Element mult6, Element mult7, Element mult8, Element * vec, int start, int end)
    {
        addMultRowGF2Extension(dest1, vec, mult1, start, end);
        addMultRowGF2Extension(dest2, vec, mult2, start, end);
        addMultRowGF2Extension(dest3, vec, mult3, start, end);
        addMultRowGF2Extension(dest4, vec, mult4, start, end);
        addMultRowGF2Extension(dest5, vec, mult5, start, end);
        addMultRowGF2Extension(dest6, vec, mult6, start, end);
        addMultRowGF2Extension(dest7, vec, mult7, start, end);
        addMultRowGF2Extension(dest8, vec, mult8, start, end);
    }
    
    template <typename Element>
    void
    Matrix<Element>::groupAddMultRowGF2Extension(int ll, int dec, int startL2, int endL2, int start,int end)
    {
        int l2,stcount,stl1=0,stl2=0,stl3=0,stl4=0,stl5=0,stl6=0,stl7=0;
        stcount=0;
        
        for(l2=startL2;l2<endL2;l2++) 
        {
            if (!_matrix[l2][ll+dec].isZero()) 
            {
                if (stcount==7) 
                {
                    octAddMultRowGF2Extension(_matrix[stl1],_matrix[stl2],_matrix[stl3],_matrix[stl4],_matrix[stl5],_matrix[stl6],_matrix[stl7],_matrix[l2],
                                _matrix[stl1][ll+dec],_matrix[stl2][ll+dec],_matrix[stl3][ll+dec],_matrix[stl4][ll+dec],
                                _matrix[stl5][ll+dec],_matrix[stl6][ll+dec],_matrix[stl7][ll+dec],_matrix[l2][ll+dec],
                                _matrix[ll],start, end);
                    _matrix[l2][ll+dec]=0;
                    _matrix[stl1][ll+dec]=0;
                    _matrix[stl2][ll+dec]=0;
                    _matrix[stl3][ll+dec]=0;
                    _matrix[stl4][ll+dec]=0;
                    _matrix[stl5][ll+dec]=0;
                    _matrix[stl6][ll+dec]=0;
                    _matrix[stl7][ll+dec]=0;
                    stcount=0;
                }
                else 
                {
                    stcount++;
                    if (stcount==1) stl1=l2;
                    if (stcount==2) stl2=l2;
                    if (stcount==3) stl3=l2;
                    if (stcount==4) stl4=l2;
                    if (stcount==5) stl5=l2;
                    if (stcount==6) stl6=l2;
                    if (stcount==7) stl7=l2;
                }
            }
        }
        if (stcount==7)     
        {
            quadAddMultRowGF2Extension(_matrix[stl1],_matrix[stl2],_matrix[stl3],_matrix[stl4],
                          _matrix[stl1][ll+dec],_matrix[stl2][ll+dec],_matrix[stl3][ll+dec],_matrix[stl4][ll+dec],
                          _matrix[ll],start, end);
            tripleAddMultRowGF2Extension(_matrix[stl5],_matrix[stl6],_matrix[stl7],_matrix[stl5][ll+dec],_matrix[stl6][ll+dec],_matrix[stl7][ll+dec],_matrix[ll],start, end);
            _matrix[stl1][ll+dec]=0;
            _matrix[stl2][ll+dec]=0;
            _matrix[stl3][ll+dec]=0;
            _matrix[stl4][ll+dec]=0;
            _matrix[stl5][ll+dec]=0;
            _matrix[stl6][ll+dec]=0;
            _matrix[stl7][ll+dec]=0;
        }
        else if (stcount==6) 
        {
            quadAddMultRowGF2Extension(_matrix[stl1],_matrix[stl2],_matrix[stl3],_matrix[stl4],
                          _matrix[stl1][ll+dec],_matrix[stl2][ll+dec],_matrix[stl3][ll+dec],_matrix[stl4][ll+dec],
                          _matrix[ll],start, end);
            doubleAddMultRowGF2Extension(_matrix[stl5],_matrix[stl6],_matrix[stl5][ll+dec],_matrix[stl6][ll+dec],_matrix[ll],start, end);
            _matrix[stl1][ll+dec]=0;
            _matrix[stl2][ll+dec]=0;
            _matrix[stl3][ll+dec]=0;
            _matrix[stl4][ll+dec]=0;
            _matrix[stl5][ll+dec]=0;
            _matrix[stl6][ll+dec]=0;
        }
        else if (stcount==5) 
        {
            quadAddMultRowGF2Extension(_matrix[stl1],_matrix[stl2],_matrix[stl3],_matrix[stl4],
                          _matrix[stl1][ll+dec],_matrix[stl2][ll+dec],_matrix[stl3][ll+dec],_matrix[stl4][ll+dec],
                          _matrix[ll],start, end);
            addMultRowGF2Extension(_matrix[stl5],_matrix[ll],_matrix[stl5][ll+dec],start, end);
            _matrix[stl1][ll+dec]=0;
            _matrix[stl2][ll+dec]=0;
            _matrix[stl3][ll+dec]=0;
            _matrix[stl4][ll+dec]=0;
            _matrix[stl5][ll+dec]=0;
        }
        else if (stcount==4) 
        {
            quadAddMultRowGF2Extension(_matrix[stl1],_matrix[stl2],_matrix[stl3],_matrix[stl4],
                          _matrix[stl1][ll+dec],_matrix[stl2][ll+dec],_matrix[stl3][ll+dec],_matrix[stl4][ll+dec],
                          _matrix[ll],start, end);
            _matrix[stl1][ll+dec]=0;
            _matrix[stl2][ll+dec]=0;
            _matrix[stl3][ll+dec]=0;
            _matrix[stl4][ll+dec]=0;
        }
        else if (stcount==3) 
        {
            tripleAddMultRowGF2Extension(_matrix[stl1],_matrix[stl2],_matrix[stl3],_matrix[stl1][ll+dec],_matrix[stl2][ll+dec],_matrix[stl3][ll+dec],_matrix[ll],start, end);
            _matrix[stl1][ll+dec]=0;
            _matrix[stl2][ll+dec]=0;
            _matrix[stl3][ll+dec]=0;
        }
        else if (stcount==2) 
        {
            doubleAddMultRowGF2Extension(_matrix[stl1],_matrix[stl2],_matrix[stl1][ll+dec],_matrix[stl2][ll+dec],_matrix[ll],start, end);
            _matrix[stl1][ll+dec]=0;
            _matrix[stl2][ll+dec]=0;
        }
        else if (stcount==1) 
        {
            addMultRowGF2Extension(_matrix[stl1],_matrix[ll],_matrix[stl1][ll+dec],start, end);
            _matrix[stl1][ll+dec]=0;
        }
    }
    
    #if defined(HAVE_SSE4_2) && defined(OS_64_BIT)
    /* We can only set 2 uint64_t in one __m128i vector */
    template <>
    void
    Matrix<ElementGF2Extension<uint64_t>>::groupAddMultRowGF2Extension(int ll, int dec, int startL2, int endL2, int start,int end)
    {
        int l2,stcount,stl1=0;

        stcount=0;
        for(l2=startL2;l2<endL2;l2++) 
        {
            if (!_matrix[l2][ll+dec].isZero()) 
            {
                if (stcount==1) 
                {
                    doubleAddMultRowGF2Extension(_matrix[stl1],_matrix[l2],_matrix[stl1][ll+dec],_matrix[l2][ll+dec],_matrix[ll],start, end);
                    _matrix[l2][ll+dec]=0;
                    _matrix[stl1][ll+dec]=0;
                    stcount=0;
                }
                else 
                {
                    stcount++;
                    if (stcount==1)
                    {
                        stl1=l2;
                    }
                }
            }
        }
        if (stcount==1) 
        {
            addMultRowGF2Extension(_matrix[stl1],_matrix[ll],_matrix[stl1][ll+dec],start, end);
            _matrix[stl1][ll+dec]=0;
        }
    }
    #endif // HAVE_SSE4_2
    
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
                    groupAddMultRowGF2Extension(ll, 0, 0, ll, _startTail[ll], _width);
                }
                
                /* Low rectangular part (under  _nbPiv) */
                for (ll = l; ll >= 0; ll--)
                {
                    groupAddMultRowGF2Extension(ll, 0, _nbPiv, _endCol[l], _startTail[ll], _width);
                }
            }
            
            /* Other slices */
            else
            {
                /* Triangular part */
                for (ll = l; ll > l - TRANCHE; ll--)
                {
                    groupAddMultRowGF2Extension(ll, 0, l - TRANCHE + 1, ll, _startTail[ll], _width);
                }
                /* Hight rectangular part */
                for (ll = l; ll > l - TRANCHE; ll--)
                {
                    groupAddMultRowGF2Extension(ll, 0, 0, l - TRANCHE + 1, _startTail[ll], _width);
                }
                /* Low rectangular part (under  _nbPiv) */
                for (ll = l; ll > l - TRANCHE; ll--)
                {
                    groupAddMultRowGF2Extension(ll, 0, _nbPiv, _endCol[l], _startTail[ll], _width);
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
                groupAddMultRowGF2Extension(l, 0, l+1, _height, ca, _width);
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
                    groupAddMultRowGF2Extension(ll, 0, _nbPiv, ll, _height, _width);
                }
                
                max_endcol = _endCol[l];
                min_endcol = _endCol[_nbPiv];
                /* Upper rectangular part */
                for (ll = l; ll >= _nbPiv; ll--)
                {
                    groupAddMultRowGF2Extension(ll, 0, 0, min_endcol, _height, _width);
                }
                for (ll = l; _endCol[ll] > _nbPiv; ll--) 
                {
                    groupAddMultRowGF2Extension(ll, 0, min_endcol, max_endcol, _height, _width);
                }
            }
            else
            {
                /* Triangular part */
                for (ll = l; ll > l - TRANCHE + 1; ll--)
                {
                    groupAddMultRowGF2Extension(ll, 0, l - TRANCHE + 1, ll, _height, _width);
                }
                /* Upper rectangular part */
                max_endcol = _endCol[l];
                min_endcol = _endCol[l - TRANCHE + 1];
                for (ll = l; ll > l - TRANCHE; ll--)
                {
                    groupAddMultRowGF2Extension(ll, 0, 0, min_endcol, _height, _width);
                }
                for (ll = l; _endCol[ll] > l-TRANCHE; ll--)
                {
                    groupAddMultRowGF2Extension(ll, 0, min_endcol, max_endcol, _height, _width);
                }
                for (ll = l; ll > l - TRANCHE; ll--)
                {
                    groupAddMultRowGF2Extension(ll, 0, _nbPiv, l - TRANCHE + 1 , _height, _width);
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
}

#endif // OPENF4_SPECIALISATION_ECHELONIZE_GF2_EXTENSION_INL
