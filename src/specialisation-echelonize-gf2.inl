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
  * \file specialisation-echelonize-gf2.inl
  * \brief Specialisation of addMultRow method for ElementGF2 type.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_SPECIALISATION_ECHELONIZE_GF2_INL
#define F4_SPECIALISATION_ECHELONIZE_GF2_INL
    
using namespace std;

namespace F4
{
    
    /* multRow specialisation for ElementGF2 */
    
    template <>
    void
    Matrix<ElementGF2>::multRow(ElementGF2 * row, ElementGF2 const & element, int start, int end)
    {
        assert((start >= 0) && (end <= _width));
        /* Do nothing */
    }
    
    /* addMultRow specialisation for ElementGF2 */
    
    template <>
    void
    Matrix<ElementGF2>::addMultRow (ElementGF2 * row1, ElementGF2 * row2, ElementGF2 element, int start, int end)
    {
        assert((start >= 0) && (end <= _width));
        
        //__m128i *sserow2, *sserow1;
        //sserow2 = reinterpret_cast<__m128i *>(row2);
        //sserow1 = reinterpret_cast<__m128i *>(row1);
        //for (int i = (start / 16); i < (end + 15) / 16; i++)
        //{
            //sserow1[i]=_mm_xor_si128(sserow1[i],sserow2[i]);
        //}
        for(int i=start; i<end; i++)
        {
            row1[i]._element^=row2[i]._element;
        }
    }
}

#endif // F4_SPECIALISATION_ECHELONIZE_GF2_INL
