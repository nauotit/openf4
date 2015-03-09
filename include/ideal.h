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
  * \file ideal.h
  * \brief Declaration of class Ideal.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_IDEAL_H
#define F4_IDEAL_H

#include <iostream>
#include <queue>
#include "critical-pair.h"
#include "matrix.h"

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \class Ideal
     * Represent an ideal.
     */
    template <typename Element>
    class Ideal
    {
        public:
            
            // Constructor
            
            /**
             * \brief Constructor.
             * \param polynomialArray: Array of polynomials.
             */
            Ideal(std::vector<Polynomial<Element>> & polynomialArray);
            
            
            // Destructor 
            
            /**
             * \brief Destructor.
             */
            ~Ideal();
            
            
            // Miscellaneous
            
            
            // F4 Algorithm
            
            /**
             * \brief Compute a groebner basis of this using the F4 algorithm.
             */
            void f4();
            
            
            
        private:
            std::vector<Polynomial<Element>> _polynomialArray; /*!< Array of polynomials */
            
            std::vector<TaggedPolynomial<Element>> _taggedPolynomialArray; /*!< Array of tagged polynomials */
    };
}

#include "../src/ideal.inl"

#endif // F4_IDEAL_H
