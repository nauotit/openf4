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
  * \file matrix.inl
  * \brief Definition of Matrix methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_MATRIX_INL
#define F4_MATRIX_INL

namespace F4
{
    // Constructor 
    
    template <typename Element>
    Matrix<Element>::Matrix():_matrix(0), _height(0), _width(0), _nbPiv(0), _tau(0), _sigma(0), _startTail(0), _endCol(0)
    {
    }
    
    template <typename Element>
    Matrix<Element>::Matrix(int height, int width): _height(height), _width(width), _nbPiv(0), _tau(0), _sigma(0), _startTail(0), _endCol(0)
    {
        _matrix=new Element[_height*_width];
    }
    
    
    // Destructor 
    
    template <typename Element>
    Matrix<Element>::~Matrix()
    {
        delete[] _matrix;
    }
    
    
    // Get / Set
    
    template <typename Element>
    inline Element & 
    Matrix<Element>::operator() (unsigned row, unsigned col) 
    { 
        assert(row >= _height || col >= _width); 
        return _matrix[_height*row + col]; 
    } 
    
    template <typename Element>
    inline Element 
    Matrix<Element>::operator() (unsigned row, unsigned col) const 
    { 
        assert(row >= _height || col >= _width);
        return _matrix[_height*row + col]; 
    }

}

#endif // F4_MATRIX_INL
