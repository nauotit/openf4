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
  * \file matrix.h
  * \brief Declaration of class Matrix.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_MATRIX_H
#define F4_MATRIX_H

#include <iostream>
#include <cassert>

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \class Matrix
     * Represent a matrix.
     */
    template <typename Element>
    class Matrix
    {
        public:
            
            // Constructor
            
            /**
             * \brief Constructor
             */
            Matrix();
            
            /**
             * \brief Constructor
             * \param height: Height of _matrix.
             * \param width: Width of _matrix.
             */
            Matrix(int height, int width);
            
            
            // Destructor
            
            /**
             * \brief Destructor
             */
            ~Matrix();
            
            
            // Get / Set
            
            Element & operator() (unsigned row, unsigned col);
              
            Element operator() (unsigned row, unsigned col) const;
            
            
            
        private:
            Element * _matrix; /*!<  */
            int _height; /*!< Height of _matrix. */
            int _width; /*!< Width of _matrix. */
            int _nbPiv; /*!< Number of pivots. */
            int * _tau; /*!< Permutation, _sigma(_tau(i))=_tau(_sigma(i))=i. _tau[i]=column of the monomial tab_mon[i]. */
            int * _sigma; /*!< _sigma[i]=index in tab_mon of the column i monomial. */
            int * _startTail; /*!< startTail[i]=column of the first possibly non zero coefficient (in line i) after nb_piv if i < nb_piv. Otherwise startTail[i]=0. startTail[i] = min{j>=nb_piv : _igma[i]<_sigma[j]}. */
            int * _endCol; /*!< endCol[i] = end of column i if i < nbPiv. Otherwise endCol[i]=end of column i without taking into account the lines under nbPiv. */
    };
}

#include "../src/matrix.inl"

#endif // F4_MATRIX_H
