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

//#include <forward_list>
#include "single-list.h"

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
        
            /* Constructor */
            
            /**
             * \brief Constructor.
             */
            Polynomial();
            
            /**
             * \brief Constructor.
             * \param s: String representing the polynomial.
             */
            Polynomial(std::string const s);
            
            /**
             * \brief Copy constructor.
             * \param polynomial: Polynomial to copy.
             */
            Polynomial(Polynomial const & polynomial);
            
            /**
             * \brief Move constructor.
             * \param polynomial: Polynomial to move.
             */
            Polynomial(Polynomial && polynomial);
            
            
            /* Destructor */
            
            /**
             * \brief Destructor.
             */
            ~Polynomial();
            
            /**
             * \brief Delete all the terms.
             */
            void clear();
            
            /**
              * \brief Erase all the term from it to the end of the polynomial.
              * \param it: Pointer on a node.
              */
             void deleteAfter(NodeList<Element> * it);
            
            
            /* Miscellaneous */
            
            /**
             * \brief Print the polynomial.
             */
            void printPolynomial (std::ostream & stream) const;
            
            /**
             * \brief Get the number of terms of this.
             * \return Number of terms of this.
             */
            int getNbTerm() const;
             
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
            * \brief Get the coefficient of the term of monomial numMon.
            * \return Coefficient of the term of monomial numMon.
            */
            Element getCoefficient(int numMon) const;
            
            /**
            * \brief Get an iterator on the beginning of the polynomial.
            * \return Iterator on the beginning of _polynomial.
            */
            NodeList<Element> * getPolynomialBegin();
            
            /**
            * \brief Get an iterator before the beginning of the polynomial.
            * \return Iterator before the beginning of _polynomial.
            */
            NodeList<Element> * getPolynomialBeforeBegin();
            
            /**
            * \brief Get a constant iterator on the beginning of the polynomial.
            * \return Constant iterator on the beginning of _polynomial.
            */
            NodeList<Element> const * getPolynomialBeginConst() const;
            
            /**
            * \brief Delete the leading term of this.
            */
            void deleteLT(); 
            
            /**
             * \brief Normalize this.
             */
            void normalize();
            
            /**
             * \brief Test if the polynomial is empty or not.
             * \return true if _polynomial is empty.
             * \return false otherwise.
             */
            bool isEmpty();
            
            /**
             * \brief Add a term after pos. Beware to keep a correct order.
             * \param pos: iterator, term is contructed after the position specified by pos.
             * \param coeff: Coefficient of the new term.
             * \param numMon: Number of the monomial of the new term.
             * \return Iterator to the new term.
             */
            NodeList<Element> * emplaceAfter(NodeList<Element> * pos, Element coeff, int numMon);
            
            /**
             * \brief Add a term after pos. Beware to keep a correct order.
             * \param pos: iterator, term is contructed after the position specified by pos.
             * \param coeff: Coefficient of the new term.
             * \param numMon: Number of the monomial of the new term.
             * \return Iterator to the new term.
             */
            NodeList<Element> * emplaceOn(NodeList<Element> * pos, Element coeff, int numMon);
            
            
            /* Internal operators */
            
            /**
             * \brief Overload the operator =.
             * \param polynomial: Polynomial to copy.
             * \return Reference on this.
             */
            Polynomial & operator=(Polynomial const & polynomial);
            
            /**
             * \brief Overload the move operator =.
             * \param polynomial: Polynomial to move.
             * \return Reference on this.
             */
            Polynomial & operator=(Polynomial && polynomial);
            
            /**
             * \brief Overload the operator *= to multiply this with a monomial. Prefer multNumMon(int numMon) if the monomial is under integer form.
             * \param mon: Monomial.
             * \return Reference on this.
             */
            Polynomial & operator*=(Monomial const & monomial);
            
            /**
             * \brief Overload the operator *= to multiply this with an Element.
             * \param element: Element.
             * \return Reference on this.
             */
            Polynomial & operator*=(Element element);
            
            /**
             * \brief Overload the operator *= to multiply this with a term.
             * \param term: Term.
             * \return Reference on this.
             */
            Polynomial & operator*=(Term<Element> const & term);
            
        private:
            SingleList<Element> _polynomial; /*!< Define a polynomial as a single chained list of Terms. */
    };
    
    
    /* External operators */
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    template <typename Element>
    std::ostream & operator<<(std::ostream & stream, Polynomial<Element> const & polynomial);
    
    /**
     * \brief Overload the operator *= to multiply this with a monomial.
     * \param mon: Monomial.
     * \param polynomial: Polynomial.
     * \return Reference on this.
     */
    template <typename Element>
    Polynomial<Element> operator * (Monomial const & monomial, Polynomial<Element> const & polynomial);
    
    /**
     * \brief Overload the operator *= to multiply this with a monomial.
     * \param mon: Monomial.
     * \param polynomial: Polynomial.
     * \return Reference on this.
     */
    template <typename Element>
    Polynomial<Element> operator * (Polynomial<Element> const & polynomial, Monomial const & monomial);

    /**
     * \brief Overload the operator *= to multiply this with an Element.
     * \param element: Element.
     * \param polynomial: Polynomial.
     * \return Reference on this.
     */
    template <typename Element>
    Polynomial<Element> operator * (Element element, Polynomial<Element> const & polynomial);
    
    /**
     * \brief Overload the operator *= to multiply this with an Element.
     * \param element: Element.
     * \param polynomial: Polynomial.
     * \return Reference on this.
     */
    template <typename Element>
    Polynomial<Element> operator * (Polynomial<Element> const & polynomial, Element element);

    /**
     * \brief Overload the operator *= to multiply this with a term.
     * \param term: Term.
     * \param polynomial: Polynomial.
     * \return Reference on this.
     */
    template <typename Element>
    Polynomial<Element> operator * (Term<Element> const & term, Polynomial<Element> const & polynomial);
    
    /**
     * \brief Overload the operator *= to multiply this with a term.
     * \param term: Term.
     * \param polynomial: Polynomial.
     * \return Reference on this.
     */
    template <typename Element>
    Polynomial<Element> operator * (Polynomial<Element> const & polynomial, Term<Element> const & term);
}

#include "../src/polynomial.inl"

#endif // F4_POLYNOMIAL_H
