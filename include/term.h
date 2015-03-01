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
  * \file term.h
  * \brief Declaration of class Term.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_TERM_H
#define F4_TERM_H

#include "monomial.h"

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \class Term
     * Represent a term.
     */
    template <typename Element>
    class Term
    {
        public:
        
            // Constructor
            /**
             * \brief Constructor.
             * \param coeff: Coefficient of the term.
             * \param mon: Pointer on the monomial of the term.
             */
            Term(Element coeff, Monomial * mon);
            
            // Destructor
            /**
             * \brief Destructor.
             */
            ~Term();
        
        private:
            Element _coefficient;
            Monomial * _monomial;
    };
}

#include "../src/term.inl"

#endif // F4_TERM_H
