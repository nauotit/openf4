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
  * \file monomial.h
  * \brief Declaration of class Monomial.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_MONOMIAL_H
#define F4_MONOMIAL_H

#include <iostream>
#include <string>
#include <cassert>

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \class Monomial
     * Represent a monomial.
     */
    class Monomial
    {
        public:
            /**
             * \brief Constructor.
             * \param nbVariable: Number of variables of the polynomial ring.
             */
            Monomial(int nbVariable); 
            
            /**
             * \brief Constructor.
             * \param nbVariable: Number of variables of the polynomial ring.
             * \param varlist: Array representing the degree of each variable of the monomial.
             */
            Monomial(int nbVariable, int const * varlist); 
            
            /**
             * \brief Copy constructor.
             * \param Monomial.
             */
             Monomial(Monomial const & toCopy);
            
            /**
             * \brief Destructor.
             */
            ~Monomial();
            
            /**
             * \brief Print the monomial.
             * \param vars: Array of string representing the variable names.
             * \return void
             */
            void printMonomial (std::ostream & stream = std::cout, std::string const  * vars=0) const;
            
            /**
             * \brief Compare monomials according to the grevlex order.
             * \param mon: Monomial.
             * \return  0 if this==mon.
             * \return  1 if this>mon.
             * \return -1 if this<mon.
             */
            int compareMonomial(Monomial const & mon) const;
            
            /**
             * \brief Overload the operator =.
             * \return Reference on this.
             */
            Monomial & operator=(Monomial const & toCopy);
        
        private:
            int _deg;                /*!< Degree of the monomial */
            int *_varlist;           /*!< Array representing the degree of each variable of the monomial */
            static int NB_VARIABLE;   /*!< Number of variables of the polynomial ring. */
    };
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    std::ostream & operator<<(std::ostream & stream, Monomial const & mon);
    
    /**
     * \brief Overload the operator ==.
     * \return true if mon1==mon2.
     * \return false otherwise.
     */
    bool operator==(Monomial const & mon1, Monomial const & mon2);
    
    /**
     * \brief Overload the operator >.
     * \return true if mon1>mon2.
     * \return false otherwise.
     */
    bool operator>(Monomial const & mon1, Monomial const & mon2);
    
    /**
     * \brief Overload the operator >=.
     * \return true if mon1>=mon2.
     * \return false otherwise.
     */
    bool operator>=(Monomial const & mon1, Monomial const & mon2);
    
    /**
     * \brief Overload the operator <.
     * \return true if mon1<mon2.
     * \return false otherwise.
     */
    bool operator<(Monomial const & mon1, Monomial const & mon2);
    
        /**
     * \brief Overload the operator <=.
     * \return true if mon1<=mon2.
     * \return false otherwise.
     */
    bool operator<=(Monomial const & mon1, Monomial const & mon2);
}




#include "../src/monomial.inl"

#endif // F4_MONOMIAL_H
