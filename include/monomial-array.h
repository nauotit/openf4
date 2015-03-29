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
  * \file monomial-array.h
  * \brief Declaration of class MonomialArray.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_MONOMIAL_ARRAY_H
#define F4_MONOMIAL_ARRAY_H

#include <iostream>
#include <string>
#include <cassert>

#include "monomial.h"


/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \class MonomialArray
     * Represent a array of monomials.
     */
    class MonomialArray
    {
        public:
             
             /* Constructor */
             
             /**
              * \brief Constructor.
              * \param nbVariable: Number of variable of the polynomial ring.
              */
             MonomialArray(int nbVariable, int capacity);
             
             /**
              * \brief Constructor.
              * \param nbVariable: Number of variable of the polynomial ring.
              * \param degree: Initialise the monomial array up to monomial of degree "degree". 
              */
             MonomialArray(int nbVariable, int capacity, int degree);
             
             /**
              * \brief Constructor.
              * \param nbVariable: Number of variable of the polynomial ring.
              * \param degree: Initialise the monomial array up to monomial of degree "degree". 
              * \param deg1: Maximum degree of row monomials.
              * \param deg2: Maximum degree of column monomials.
              */
             MonomialArray(int nbVariable, int capacity, int degree, int deg1, int deg2);
             
             
             /* Destructor */
             
             /**
              * \brief Destructor.
              */
            ~MonomialArray();
            
            
            /* Miscellaneous */
            
            /**
             * \brief Modify the dynamic array _monomialArray.
             * \pre The array _nbMonomial must be set beforehand.
             */
             void setMonomialArray();
             
             /**
             * \brief Modify the static 2D array TABULATED_PRODUCT.
             * \pre Static variables NB_VARIABLE, NB_MONOMIAL and MONOMIAL_ARRAY must be set beforehand.
             * \param deg1: Maximum degree of row monomials.
             * \param deg2: Maximum degree of column monomials.
             */
             void setTabulatedProduct(int deg1, int deg2);
             
             /**
             * \brief Free the static 2D array NB_MONOMIAL.
             * \pre The static variables NB_VARIABLE must be set beforehand.
             */
             void freeTabulatedProduct();
             
             /**
             * \brief Get _monomialArray[numMon]._varlist[i].
             * \param numMon: Number of the monomial.
             * \param index: Index of a variable in varlist.
             * \return _monomialArray[numMon]._varlist[i].
             */
             int getNumVarlist(int numMon, int index);
             
             /**
             * \brief Multiply two monomials, using _tabulatedProduct if possible. Prefer numMon1<numMon2.
             * \param numMon1: Number of the first monomial.
             * \param numMon2: Number of the second monomial.
             * \return Number of the product intToMonomial[numMon1] * intToMonomial[numMon2].
             */
             int multNumMonomial(int numMon1, int numMon2);
             
             
             /* Access */
             
             /**
             * \brief Overload the operator [].
             * \return Reference on a monomial.
             */
            Monomial & operator[](int index);
             
             
        
        private:
            Monomial *_monomialArray ; /*!< Array of monomial */
            int ** _tabulatedProduct; /*!< _tabulatedProduct[i][j] = number of the product intToMonomial[i] * intToMonomial[j] */
            int _nbVariable;   /*!< Number of variables of the polynomial ring. */
            size_t _size; /*!< Size of _monomialArray */
            size_t _capacity; /*!< Capacity of _monomialArray */
            int * _varlistArray[100]; /*!< 2D array of varlist */
            int _varlistIndex; /*!< Next available row index in _varlistArray */
            int _numMaxRow; /*!< Number of rows in _tabulatedProduct. */
            int _numMaxColumn; /*!< Number of columns in _tabulatedProduct. */
            
        
    };
}

#include "../src/monomial-array.inl"

#endif // F4_MONOMIAL_ARRAY_H
