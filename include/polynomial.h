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
  * \file polynomial.h
  * \brief Declaration of class Polynomial.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_POLYNOMIAL_H
#define F4_POLYNOMIAL_H

#include <forward_list>
#include <string>
#include "term.h"

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \class Polynomial
     * Represent a polynomial.
     */
    template <typename Element>
    class Polynomial
    {
        public:
        
            // Constructor
            
            /**
             * \brief Constructor.
             */
            Polynomial();
            
            /**
             * \brief Constructor.
             * \param s: String representing the polynomial.
             */
            Polynomial(std::string const s);
            
            
            // Destructor
            
            /**
             * \brief Destructor.
             */
            ~Polynomial();
            
            
            // Miscellaneous
            
            /**
             * \brief Print the polynomial.
             * \return void
             */
            void printPolynomial (std::ostream & stream = std::cout) const;
            
        private:
            std::forward_list<Term<Element>> _polynomial;
    };
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    template <typename Element>
    std::ostream & operator<<(std::ostream & stream, Polynomial<Element> const & polynomial);
}

#include "../src/polynomial.inl"

#endif // F4_POLYNOMIAL_H
