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
            
            /**
             * \brief Move Constructor.
             * \param taggedPolynomial: TaggedPolynomial.
             */ 
            TaggedPolynomial(TaggedPolynomial  && taggedPolynomial);
            
            
            // Destructor
            
            ~TaggedPolynomial();
            
            
            // Get / Set
            
            /**
             * \brief Get the polynomial of this.
             * \return Polynomial of this.
             */
            Polynomial<Element> const & getPolynomial() const;
            
            /**
            * \brief Get the leading term of this.
            * \pre _polynomial is not empty.
            * \return Leading term of this.
            */
            const Term<Element> & getLT() const; 
            
            /**
            * \brief Get the number of the leading monomial of this.
            * \pre _polynomial is not empty.
            * \return Number of the leading monomial of this.
            */
            int getLM() const;
            
            /**
            * \brief Get the leading coefficient of this.
            * \pre _polynomial is not empty.
            * \return Leading coefficient of this.
            */
            Element getLC() const;
            
            /**
             * \brief Get _simplyrules[i].
             * \param index: Index of a variable in _simplyrules.
             * \return _simplyrules[i].
             */
            int getSimplyrule(int index) const;
            
            /**
             * \brief Set _simplyrules[i].
             * \param index: Index of a variable in _simplyrules.
             * \param numPol: Index of a tagged polynomial in a tagged polynomial Array.
             * \return _simplyrules[i].
             */
            void setSimplyrule(int index, int numPol);
            
            
            // Miscellaneous
            
            /**
             * \brief Print the polynomial and the _simplyrules of this.
             */
            void printTaggedPolynomial (std::ostream & stream = std::cout) const;
            
            /**
             * \brief Compare this with taggedPolynomial.
             * \param taggedPolynomial: TaggedPolynomial.
             * \return (Number of terms of this) - (Number of terms of taggedPolynomial) if LM(this)==LM(taggedPolynomial).
             * \return 1 if LM(this) > LM(taggedPolynomial).
             * \return -1 if LM(this) < LM(taggedPolynomial).
             */
            int compareTaggedPolynomial (TaggedPolynomial const & taggedPolynomial) const;
            
            /**
             * \brief Test if the polynomial is empty or not.
             * \return true if _polynomial is empty.
             * \return false otherwise.
             */
            bool isEmpty();
            
            
            // Internal operators
            
            /**
             * \brief Overload the operator =.
             * \param taggedPolynomial: Tagged polynomial to copy.
             * \return Reference on this.
             */
            TaggedPolynomial & operator=(TaggedPolynomial const & taggedPolynomial);
            
            /**
             * \brief Overload the move operator =.
             * \param taggedPolynomial: Tagged polynomial to move.
             * \return Reference on this.
             */
            TaggedPolynomial & operator=(TaggedPolynomial  && taggedPolynomial);
            
            /**
             * \brief Overload the operator *= to multiply this with a monomial.
             * \param mon: Monomial.
             * \return Reference on this.
             */
            TaggedPolynomial & operator*=(Monomial const & monomial);
            
            /**
             * \brief Overload the operator *= to multiply this with an Element.
             * \param element: Element.
             * \return Reference on this.
             */
            TaggedPolynomial & operator*=(Element element);
            
            /**
             * \brief Overload the operator *= to multiply this with a term.
             * \param term: Term.
             * \return Reference on this.
             */
            TaggedPolynomial & operator*=(Term<Element> const & term);
            
        private:
        
            Polynomial<Element> _polynomial;           /*!< Polynomial . */
            int * _simplyrules;       /*!< Array of integer, mainly used by the simplify algorithm. simplifyrules[i] is the index of a tagged polynomial of List. */
    };
    
    // External operators
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    template <typename Element>
    std::ostream & operator<<(std::ostream & stream, TaggedPolynomial<Element> const & taggedPolynomial);
    
    /**
     * \brief Overload the operator ==.
     * \return true if taggedPolynomial1 == taggedPolynomial2.
     * \return false otherwise.
     */
    template <typename Element>
    bool operator==(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2);
    
    /**
     * \brief Overload the operator >.
     * \return true if taggedPolynomial1 > taggedPolynomial2.
     * \return false otherwise.
     */
    template <typename Element>
    bool operator>(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2);
    
    /**
     * \brief Overload the operator >=.
     * \return true if taggedPolynomial1 >= taggedPolynomial2.
     * \return false otherwise.
     */
    template <typename Element>
    bool operator>=(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2);
    
    /**
     * \brief Overload the operator <.
     * \return true if taggedPolynomial1 < taggedPolynomial2.
     * \return false otherwise.
     */
    template <typename Element>
    bool operator<(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2);
    
    /**
     * \brief Overload the operator <=.
     * \return true if taggedPolynomial1 <= taggedPolynomial2.
     * \return false otherwise.
     */
    template <typename Element>
    bool operator<=(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2);
    
    /**
     * \brief Overload the operator *= to multiply this with a monomial.
     * \param mon: Monomial.
     * \param TaggedPolynomial: taggedPolynomial.
     * \return Reference on this.
     */
    template <typename Element>
    TaggedPolynomial<Element> operator * (Monomial const & monomial, TaggedPolynomial<Element> const & taggedPolynomial);
    
    /**
     * \brief Overload the operator *= to multiply this with a monomial.
     * \param mon: Monomial.
     * \param TaggedPolynomial: taggedPolynomial.
     * \return Reference on this.
     */
    template <typename Element>
    TaggedPolynomial<Element> operator * (TaggedPolynomial<Element> const & taggedPolynomial, Monomial const & monomial);

    /**
     * \brief Overload the operator *= to multiply this with an Element.
     * \param element: Element.
     * \param TaggedPolynomial: taggedPolynomial.
     * \return Reference on this.
     */
    template <typename Element>
    TaggedPolynomial<Element> operator * (Element element, TaggedPolynomial<Element> const & taggedPolynomial);
    
    /**
     * \brief Overload the operator *= to multiply this with an Element.
     * \param element: Element.
     * \param TaggedPolynomial: taggedPolynomial.
     * \return Reference on this.
     */
    template <typename Element>
    TaggedPolynomial<Element> operator * (TaggedPolynomial<Element> const & taggedPolynomial, Element element);

    /**
     * \brief Overload the operator *= to multiply this with a term.
     * \param term: Term.
     * \param TaggedPolynomial: taggedPolynomial.
     * \return Reference on this.
     */
    template <typename Element>
    TaggedPolynomial<Element> operator * (Term<Element> const & term, TaggedPolynomial<Element> const & taggedPolynomial);
    
    /**
     * \brief Overload the operator *= to multiply this with a term.
     * \param term: Term.
     * \param TaggedPolynomial: taggedPolynomial.
     * \return Reference on this.
     */
    template <typename Element>
    TaggedPolynomial<Element> operator * (TaggedPolynomial<Element> const & taggedPolynomial, Term<Element> const & term);
}

#include "../src/tagged-polynomial.inl"

#endif // F4_TAGGED_POLYNOMIAL_H
