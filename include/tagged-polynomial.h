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
  * \file tagged-polynomial.h
  * \brief Declaration of class TaggedPolynomial.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON 
  */

#ifndef F4_TAGGED_POLYNOMIAL_H
#define F4_TAGGED_POLYNOMIAL_H

#include "polynomial.h"

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \class TaggedPolynomial
     * Represent a tagged polynomial.
     */
    template <typename Element>
    class TaggedPolynomial
    {
        public:
            
            // Constructor 
            
            /**
             * \brief Constructor.
             */ 
            TaggedPolynomial();
            
            /**
             * \brief Constructor.
             * \param polynomial: Polynomial.
             */ 
            TaggedPolynomial(Polynomial<Element> const & polynomial);
            
            /**
             * \brief Copy Constructor.
             * \param taggedPolynomial: TaggedPolynomial.
             */ 
            TaggedPolynomial(TaggedPolynomial const & taggedPolynomial);
            
            
            // Destructor
            
            ~TaggedPolynomial();
            
            
            // Miscellaneous
            
            /**
             * \brief Print the polynomial and the _simplyrules of this.
             */
            void printTaggedPolynomial (std::ostream & stream = std::cout) const;
            
            /**
             * \brief Compare the tagged polynomial p1 and p2. Be careful with the non intuitive return value.
             * \param p1: Tagged polynomial.
             * \param p2: Tagged polynomial.
             * \return (Number of terms of p1) - (Number of terms of p2) if LM(p1)==LM(P2).
             * \return 1 if LM(p1) > LM(p2).
             * \return -1 if LM(p1) < LM(p2).
             */
            int compareTaggedPolynomial (TaggedPolynomial const & taggedPolynomial) const;
            
            
            // Operator overload
            
            /**
             * \brief Overload the operator =.
             * \param taggedPolynomial: Tagged polynomial to copy.
             * \return Reference on this.
             */
            TaggedPolynomial & operator=(TaggedPolynomial const & taggedPolynomial);
            
        private:
        
            Polynomial<Element> _polynomial;           /*!< Polynomial . */
            std::vector<int> _simplyrules;       /*!< Array of integer, mainly used by the simplify algorithm. simplifyrules[i] is the index of a tagged polynomial of List. */
    };
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    template <typename Element>
    std::ostream & operator<<(std::ostream & stream, TaggedPolynomial<Element> const & taggedPolynomial);
}

#include "../src/tagged-polynomial.inl"

#endif // F4_TAGGED_POLYNOMIAL_H
