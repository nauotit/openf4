/* 
 * Copyright (C) 2015 Antoine Joux, Vanessa Vitse and Titouan Coladon
 * 
 * This file is part of F4.
 * 
 * F4 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * F4 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with F4.  If not, see <http://www.gnu.org/licenses/>.
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
        for(int i=start; i<end; i++)
        {
            row1[i]._element^=row2[i]._element;
        }
    }
}

#endif // F4_SPECIALISATION_ECHELONIZE_GF2_INL
