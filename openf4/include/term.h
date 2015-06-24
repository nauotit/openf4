/* 
 * Copyright (C) 2015 Antoine Joux, Vanessa Vitse and Titouan Coladon
 * 
 * This file is part of F4.
 * 
 * F4 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * F4 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with F4.  If not, see <http://www.gnu.org/licenses/>.
 */

  /**
  * \file term.h
  * \brief Declaration of class Term.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_TERM_H
#define F4_TERM_H

/** \cond */
#include "global.h"
/** \endcond */
#include "monomial-array.h"
#include "element-prime.h"
#include "element-gf2.h"
#include "element-gf2-extension.h"
#ifdef HAVE_GIVARO
#include "element-givaro.h"
#endif // HAVE_GIVARO

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \class Term
     * \brief Represent a term.
     */
    template <typename Element>
    class Term
    {
        public:
            
            /* Static methods */
            
            /**
             * \brief Set the monomial array to use.
             * \param monomialArray: Address of the array.
             */
            static void setMonomialArray(MonomialArray * monomialArray);
            
        
            /* Constructor */
            
            /**
             * \brief Constructor.
             */
            Term();
            
            /**
             * \brief Constructor.
             * \param coeff: Coefficient of the term.
             * \param mon: Monomial of the term.
             */
            Term(Element coeff, Monomial const & mon);
            
            /**
             * \brief Constructor.
             * \param coeff: Coefficient of the term.
             * \param numMon: Number of the monomial of the term.
             */
            Term(Element coeff, int numMon);
            
            /**
             * \brief Constructor.
             * \param s: String representing the term.
             */
            Term(std::string const s);
            
            /**
             * \brief Copy constructor.
             * \param toCopy: Term.
             */
            Term(Term const & toCopy);
            
            
            /* Get / Set */
            
            /**
             * \brief Get the coefficient of this.
             * \return Coefficient of this.
             */
            Element getCoefficient() const;
            
            /**
             * \brief Set the coefficient of this.
             * \param Coefficient.
             */
            void setCoefficient(Element coeff);
            
            /**
             * \brief Set the coefficient of this to 1.
             * \param Coefficient.
             */
            void setCoefficientOne();
            
            /**
             * \brief Get the number of the monomial of this.
             * \return numMonomial of this.
             */
            int getNumMonomial() const;
            
            /**
             * \brief Set the number of the monomial of this.
             * \param numMon: Number of the monomial of this.
             */
            void setNumMonomial(int numMon);
            
            /**
             * \brief Initialize this with s.
             * \param s: String representing the term.
             */
            void setTerm(std::string const s);
            
            
            /* Miscellaneous */
            
            /**
             * \brief Get the coefficient of the term written s. Must be specialized for each type of Element.
             * \param s: String representing the term.
             * \return Coefficent the term.
             */
            void readCoefficient(std::string const s);
            
            /**
             * \brief Print the term.
             */
            void printTerm (std::ostream & stream) const;
            
            /**
             * \brief Multiply this with a monomial under integer form.
             * \param numMon: number of a monomial.
             */
            void multNumMon(int numMon);
            
            /**
             * \brief Compare terms according to the grevlex order. Coefficient are not taking into accout.
             * \param term: Term.
             * \return  0 if this==term.
             * \return  1 if this>term.
             * \return -1 if this<term.
             */
            int compareTerm(Term<Element> const & term) const;
            
            
            /* Internal operators */
            
            /**
             * \brief Overload the operator =.
             * \param term: Term to copy.
             * \return Reference on this.
             */
            Term & operator=(Term const & term);
            
            /**
             * \brief Overload the operator *= to multiply this with a monomial.
             * \param mon: Monomial.
             * \return Reference on this.
             */
            Term & operator*=(Monomial const & monomial);
            
            /**
             * \brief Overload the operator *= to multiply this with an Element.
             * \param element: Element.
             * \return Reference on this.
             */
            Term & operator*=(Element element);
            
            /**
             * \brief Overload the operator *= to multiply this with a term.
             * \param term: Term.
             * \return Reference on this.
             */
            Term & operator*=(Term const & term);
        
        private:
            Element _coefficient; /*!< Coefficient of the term. */
            int _numMonomial; /*!< Number of the monomial of the term. */
            
            static MonomialArray * MONOMIAL_ARRAY; /*!< Pointer on a monomial array */
    };
    
    
    /* External operators */
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    template <typename Element>
    std::ostream & operator<<(std::ostream & stream, Term<Element> const & term);
    
    /**
     * \brief Overload the operator *.
     * \return mon * term.
     */
    template <typename Element>
    Term<Element> operator * (Monomial const & mon, Term<Element> const & term);
    
    /**
     * \brief Overload the operator *.
     * \return term * mon.
     */
    template <typename Element>
    Term<Element> operator * (Term<Element> const & term, Monomial const & mon);
    
    /**
     * \brief Overload the operator *.
     * \return term1 * term2.
     */
    template <typename Element>
    Term<Element> operator * (Term<Element> const & term1, Term<Element> const & term2);
    
    /**
     * \brief Overload the operator >.
     * \param term1: Term.
     * \param term2: Term.
     * \return true if term1>term2.
     * \return false otherwise.
     */
    template <typename Element>
    bool operator>(Term<Element> const & term1, Term<Element> const & term2);
    
    /**
     * \brief Overload the operator <.
     * \param term1: Term.
     * \param term2: Term.
     * \return true if term1<term2.
     * \return false otherwise.
     */
    template <typename Element>
    bool operator<(Term<Element> const & term1, Term<Element> const & term2);
}

/** \cond */
#include "../src/term.inl"
/** \endcond */

#endif // F4_TERM_H
