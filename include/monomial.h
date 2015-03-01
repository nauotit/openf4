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
            
            // static functions
            
            /**
             * \brief Modify the static variable VERBOSE.
             * \param verbose: Verbosity level.
             */
             static void setVerbose(int verbose);
             
            /**
             * \brief Modify the static variable NB_VARIABLE.
             * \param nbVariable: Number of variables of the polynomial ring.
             */
             static void setNbVariable(int nbVariable);
             
             /**
             * \brief Get the static variable NB_VARIABLE.
             * \return Value of NB_VARIABLE.
             */
             static int getNbVariable();
             
             /**
             * \brief Modify the static variable VARS.
             * \param vars: Array of variable names of the polynomial ring.
             */
             static void setVariable(std::string const  * vars);
             
             /**
             * \brief Get the static variable VARS.
             * \return Value of VARS.
             */
             static std::string const  * getVariable();
             
             /**
             * \brief Modify the static variable WEIGHT.
             * \param weight: Array of weights. [1,...,1] by default.
             */
             static void setWeight(int  * weight);
             
             /**
             * \brief Get the static variable WEIGHT.
             * \return Value of WEIGHT.
             */
             static int * getWeight();
             
            /**
             * \brief Modify the static array NB_MONOMIAL.
             * \param maxDegree: Maximal degree (height) of NB_MONOMIAL.
             */
             static void setNbMonomial(int maxDegree);
             
             /**
             * \brief Get the static variable NB_MONOMIAL.
             * \return Value of NB_MONOMIAL.
             */
             static int ** getNbMonomial();
             
             /**
             * \brief Free the static array NB_MONOMIAL.
             * \param maxDegree: Maximal degree (height) of NB_MONOMIAL.
             */
             static void freeNbMonomial(int maxDegree);
             
             /**
             * \brief Modify the static array TABULATED_PRODUCT.
             * \param deg1: .
             * \param deg2: .
             */
             static void setTabulatedProduct(int deg1, int deg2);
             
             /**
             * \brief Get the static variable NB_MONOMIAL.
             * \return Value of NB_MONOMIAL.
             */
             static int ** getTabulatedProduct();
             
             /**
             * \brief Free the static array NB_MONOMIAL.
             * \param maxDegree: Maximal degree (height) of NB_MONOMIAL.
             */
             static void freeTabulatedProduct(int deg1, int deg2);
            
            // Constructor
            
            /**
             * \brief Constructor, the static variable NB_VARIABLE must be set beforehand.
             */
            Monomial(); 
            
            /**
             * \brief Constructor, the static variable NB_VARIABLE must be set beforehand.
             * \param varlist: Array representing the degree of each variable of the monomial.
             */
            Monomial(int const * varlist); 
            
            /**
             * \brief Copy constructor.
             * \param Monomial.
             */
             Monomial(Monomial const & toCopy);
             
             // Destructor
            
            /**
             * \brief Destructor.
             */
            ~Monomial();
            
            // Miscellaneous
            
            /**
             * \brief Initialize this with varlist.
             * \param varlist: Array representing the degree of each variable of the monomial.
             */
            void setMonomial(int const * varlist);
            
            /**
             * \brief Initialize this with the num-th monomial of degree deg. The static array NB_MONOMIAL must be set beforehand.
             * \param num: number of the constructed monomial, 0 is the smallest monomial of the given degree.
             */
            void intToMonomial(int numMon);
            
            /**
             * \brief Compute the number of this. The static array NB_MONOMIAL must be set beforehand.
             * \return Number of this.
             */
            int monomialToInt();
            
            /**
             * \brief Print the monomial.
             * \return void
             */
            void printMonomial (std::ostream & stream = std::cout) const;
            
            /**
             * \brief Compare monomials according to the grevlex order.
             * \param mon: Monomial.
             * \return  0 if this==mon.
             * \return  1 if this>mon.
             * \return -1 if this<mon.
             */
            int compareMonomial(Monomial const & mon) const;
            
            /**
             * \brief Test if this is divisible by mon.
             * \param mon: Divisor.
             * \return true if mon divides this.
             * \return false otherwise.
             */
            bool isDivisible(Monomial const & mon) const;
            
            /**
             * \brief Reset this.
             */
            void reset();
            
            // Internal operators
            
            /**
             * \brief Overload the operator =.
             * \return Reference on this.
             */
            Monomial & operator=(Monomial const & mon);
            
            /**
             * \brief Overload the operator *=.
             * \return Reference on this.
             */
            Monomial & operator*=(Monomial const & mon); 
            
            /**
             * \brief Overload the operator /=.
             * \return Reference on this.
             */
            Monomial & operator/=(Monomial const & mon); 
        
        private:
            int _deg;                /*!< Degree of the monomial */
            int *_varlist;           /*!< Array representing the degree of each variable of the monomial */
            
            static int VERBOSE; 
            static int NB_VARIABLE;   /*!< Number of variables of the polynomial ring. */
            static std::string const * VARS; /*!< Array of NB_VARIABLE string representing the variable names. */
            static int * WEIGHT; /*!< Array of NB_VARIABLE weights. [1,...,1] by default */
            /**
             * \brief NB_MONOMIAL[d][v] = Number of degree d monomials in the v first variables.
             * NB_MONOMIAL[d][NB_VARIABLE+1] = Number of monomials of degree <= d.
             */
            static int **NB_MONOMIAL;
            static int MAX_DEGREE; /*!< Maximal degree (height) of NB_MONOMIAL. */
            static int ** TABULATED_PRODUCT; /*!< TABULATED_PRODUCT[i][j] = number of the product intToMonomial[i] * intToMonomial[j] */
    };
    
    // External operators
    
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
    
    /**
     * \brief Overload the operator *.
     * \return mon1 * mon2.
     */
    Monomial operator * (Monomial const & mon1, Monomial const & mon2);
    
    /**
     * \brief Overload the operator /.
     * \return mon1 / mon2.
     */
    Monomial operator / (Monomial const & mon1, Monomial const & mon2);
}




#include "../src/monomial.inl"

#endif // F4_MONOMIAL_H
