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
             */
            Term();
            
            /**
             * \brief Constructor.
             * \param coeff: Coefficient of the term.
             * \param mon: Pointer on the monomial of the term.
             */
            Term(Element coeff, Monomial mon);
            
            /**
             * \brief Constructor.
             * \param s: String representing the term.
             */
            Term(std::string const s);
            
            
            // Destructor
            
            /**
             * \brief Destructor.
             */
            ~Term();
            
            
            // Get / Set
            
            /**
             * \brief Get the coefficient of this.
             * \return Coefficient of this.
             */
            Element getCoefficient();
            
            /**
             * \brief Set the coefficient of this.
             * \param Coefficient.
             */
            void setCoefficient(Element coeff);
            
            // Miscellaneous
            
            /**
             * \brief Initialize this with s.
             * \param s: String representing the term.
             */
            void setTerm(std::string const s);
            
            /**
             * \brief Print the term.
             * \return void
             */
            void printTerm (std::ostream & stream = std::cout) const;
            
            /**
             * \brief Get the coefficient of the term written s. Must be specialized for each type of Element.
             * \param s: String representing the term.
             * \return Coefficent the term.
             */
            Element readCoefficient(std::string const s);
        
        private:
            Element _coefficient;
            int _numMonomial;
    };
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    template <typename Element>
    std::ostream & operator<<(std::ostream & stream, Term<Element> const & term);
}

#include "../src/term.inl"

#endif // F4_TERM_H
