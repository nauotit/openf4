/* 
 * Copyright (C) 2015 Antoine Joux, Vanessa Vitse and Titouan Coladon
 * 
 * This file is part of openf4.
 * 
 * openf4 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * openf4 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with openf4.  If not, see <http://www.gnu.org/licenses/>.
 */

  /**
  * \file monomial.h
  * \brief Declaration of class Monomial.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef OPENF4_MONOMIAL_H
#define OPENF4_MONOMIAL_H

/** \cond */
#include "global.h"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
/** \endcond */

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \class Monomial
     * \brief Represent a monomial.
     */
    class Monomial
    {
        public:
            
            /* Static methods */
             
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
             * \param weight: Array of weights.
             */
             static void setWeight(int  * weight);
             
             /**
             * \brief Get the static variable WEIGHT.
             * \return Value of WEIGHT.
             */
             static int * getWeight();
             
             /**
             * \brief Get the static variable MAX_DEGREE.
             * \return Value of MAX_DEGREE.
             */
             static short getMaxDegree();
             
            /**
             * \brief Modify the dynamic 2D array NB_MONOMIAL, and call setMonomialArray().
             * \pre Static variables NB_VARIABLE and WEIGHT must be set beforehand.
             * \param maxDegree: Maximal degree (height) of NB_MONOMIAL.
             */
             static void setNbMonomial(short maxDegree);
             
             /**
             * \brief Modify the dynamic 2D array NB_MONOMIAL.
             * \pre Static variables NB_VARIABLE and WEIGHT must be set beforehand.
             * \param numMonomial: NB_MONOMIAL is set such that numMonomial belongs to it.
             */
             static void increaseNbMonomial(int numMonomial);
             
             /**
             * \brief Get NB_MONOMIAL[MAX_DEGREE][NB_VARIABLE+1].
             * \return Number of monomials of degree less than MAX_DEGREE.
             */
             static int getNbMonomial();
             
             /**
             * \brief Get NB_MONOMIAL[row][column].
             * \param row: Index of the row.
             * \param column: Index of the column.
             * \return NB_MONOMIAL[row][column].
             */
             static int getNbMonomial(int row, int column);
             
             /**
             * \brief Free the dynamic 2D array NB_MONOMIAL, and call freeMonomialArray().
             * \param maxDegree: Maximal degree (height) of NB_MONOMIAL.
             */
             static void freeNbMonomial();
             
             /**
             * \brief Compare two monomials, using MONOMIAL_ARRAY if possible.
             * \param numMon1: Number of the first monomial.
             * \param numMon2: Number of the second monomial.
             * \return  0 if numMon1==numMon2.
             * \return  1 if numMon1>numMon2.
             * \return -1 if numMon1<numMon2.
             */
             static int compareNumMonomial(int numMon1, int numMon2);
             
             /**
              * \brief Compute the number of a monomial from its varlist.
              * \param varlist: Array representing the degree of each variable of the monomial.
              * \return Number of the corresponding monomial.
              */
             static int varlistToInt(uint8_t const * varlist);
             
             /**
              * \brief Compute the number of a monomial from its varlist and its degree.
              * \pre NB_MONOMIAL must be set up to degree deg.
              * \param varlist: Array representing the degree of each variable of the monomial.
              * \param degree: Degree of the monomial.
              * \return Number of the corresponding monomial.
              */
             static int varlistToInt(uint8_t const * varlist, short deg);
             
             /**
              * \brief Compute the number of a product of 2 monomials from their varlists.
              * \param varlist1: Array representing the degree of each variable of the first monomial.
              * \param varlist2: Array representing the degree of each variable of the second monomial.
              * \return Number of the corresponding monomial.
              */
             static int varlistToInt(uint8_t const * varlist1, uint8_t const * varlist2);
             
             /**
              * \brief Initialise the static parameters of Monomial.
              * \param nbVariable: Number of variables of the polynomial ring.
              * \param degree: Initialise NB_MONOMIAL up to degree "degree".
              */
             static void initMonomial(int nbVariable, short degree=1);
             
             /**
              * \brief Free the space allocated by initMonomial.
              */
             static void freeMonomial();
            
            /* Constructor */
            
            /**
             * \brief Constructor. Beware, varlist is not allocated.
             */
            Monomial();
            
            /**
             * \brief Copy constructor.
             */
            Monomial(Monomial const & toCopy);
            
            
            /* Get / Set */
            
            /**
             * \brief Get the degree of this.
             * \return Degree of this.
             */
            short getDegree() const;
            
            /**
             * \brief Get the varlist of this.
             * \return Varlist of this.
             */
            uint8_t const * getVarlist() const;
            
            /**
             * \brief Get varlist[index].
             * \return varlist[index].
             */
            uint8_t getVarlist(int index) const;
            
             /**
             * \brief Set the varlist of this.
             */
            void setVarlist(uint8_t * varlist);
            
            
            /* Miscellaneous */
            
            /**
             * \brief Allocate the varlist of this.
             */
            void allocate();
            
            /**
             * \brief Delete the varlist of this.
             */
            void erase();
            
            /**
             * \brief Initialize this with varlist. 
             * \pre Static variables NB_VARIABLE and WEIGHT must be set beforehand.
             * \param varlist: Array representing the degree of each variable of the monomial.
             */
            void setMonomial(uint8_t const * varlist);
            
            /**
             * \brief Initialize this with s.
             * \pre Static variables NB_VARIABLE, WEIGHT and VARS must be set beforehand.
             * \param s: String representing the monomial.
             */
            void setMonomial(std::string const s);
            
            /**
             * \brief Initialize this with the numMon th monomial. 
             * \pre Static variables NB_VARIABLE and WEIGHT must be set beforehand.
             * \param numMon: number of the constructed monomial, 0 is the smallest monomial.
             */
            void setMonomial(int numMon);
            
            /**
             * \brief Initialize this with mon. 
             * \pre Static variables NB_VARIABLE and WEIGHT must be set beforehand.
             * \param mon: Monomial.
             */
            void setMonomial(Monomial const & mon);
            
            /**
             * \brief Initialize this with mon1 * mon2. 
             * \pre Static variables NB_VARIABLE and WEIGHT must be set beforehand.
             * \param mon1: Monomial.
             * \param mon2: Monomial.
             */
            void setMonomialMultiply(Monomial const & mon1, Monomial const & mon2);
            
            /**
             * \brief Initialize this with mon1 / mon2. 
             * \pre Static variables NB_VARIABLE and WEIGHT must be set beforehand.
             * \pre mon1 must be divisible by mon2.
             * \param mon1: Monomial.
             * \param mon2: Monomial.
             */
            void setMonomialDivide(Monomial const & mon1, Monomial const & mon2);
            
            /**
             * \brief Initialize this with the num-th monomial.
             * \pre Static variables NB_VARIABLE, WEIGHT and NB_MONOMIAL must be set beforehand.
             * \param numMon: number of the constructed monomial, 0 is the smallest monomial.
             */
            void intToMonomial(int numMon);
            
            /**
             * \brief Compute the number of this. 
             * \pre Static variables NB_VARIABLE and WEIGHT must be set beforehand.
             * \return Number of this.
             */
            int monomialToInt() const;
            
            /**
             * \brief Print the monomial. 
             * \pre The static variable NB_VARIABLE must be set beforehand.
             */
            void printMonomial (std::ostream & stream) const;
            
            /**
             * \brief Compare monomials according to the grevlex order.
             * \pre The static variable NB_VARIABLE must be set beforehand.
             * \param mon: Monomial.
             * \return  0 if this==mon.
             * \return  1 if this>mon.
             * \return -1 if this<mon.
             */
            int compareMonomial(Monomial const & mon) const;
            
            /**
             * \brief Test if this is divisible by mon.
             * \pre The static variable NB_VARIABLE must be set beforehand.
             * \param mon: Divisor.
             * \return true if mon divides this.
             * \return false otherwise.
             */
            bool isDivisible(Monomial const & mon) const;
            
            /**
             * \brief Reset this.
             * \pre The static variable NB_VARIABLE must be set beforehand.
             */
            void reset();
            
            
            /* Internal operators */
            
            /**
             * \brief Overload the operator =.
             * \pre The static variable NB_VARIABLE must be set beforehand.
             * \param mon: Monomial to copy.
             * \return Reference on this.
             */
            Monomial & operator=(Monomial const & mon);
            
            /**
             * \brief Overload the operator = (move assignment). Used when mon is unnamed (only copy the pointer).
             * \pre The static variable NB_VARIABLE must be set beforehand.
             * \param mon: Monomial to copy.
             * \return Reference on this.
             */
            Monomial & operator=(Monomial && mon);
            
            /**
             * \brief Overload the operator *=.
             * \pre The static variable NB_VARIABLE must be set beforehand.
             * \param mon: Monomial.
             * \return Reference on this.
             */
            Monomial & operator*=(Monomial const & mon); 
            
            /**
             * \brief Multiply mon1 and mon2.
             * \param mon1: Monomial.
             * \param mon2: Monomial.
             * \return Number of mon1 * mon2.
             */
            friend int multiplyMonomial(Monomial const & mon1, Monomial const & mon2);
            
            /**
             * \brief Overload the operator /=.
             * \pre Static variables NB_VARIABLE and WEIGHT must be set beforehand.
             * \pre this must be divisible by mon.
             * \param mon: Monomial (divisor).
             * \return Reference on this.
             */
            Monomial & operator/=(Monomial const & mon); 
        
        private:
            short _deg;                /*!< Degree of the monomial */
            uint8_t *_varlist;           /*!< Array representing the degree of each variable of the monomial */
            
            static int NB_VARIABLE;   /*!< Number of variables of the polynomial ring. */
            static std::string const * VARS; /*!< Array of NB_VARIABLE string representing the variable names. */
            static int * WEIGHT; /*!< Array of NB_VARIABLE weights. */
            /**
             * \brief NB_MONOMIAL[d][v] = Number of degree d monomials in the v first variables.
             * NB_MONOMIAL[d][NB_VARIABLE+1] = Number of monomials of degree <= d.
             */
            static std::vector<int *> NB_MONOMIAL;
            static short MAX_DEGREE; /*!< Maximal degree (height) of NB_MONOMIAL. */
            
    };
    
    /* External operators */
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    std::ostream & operator<<(std::ostream & stream, Monomial const & mon);
    
    /**
     * \brief Overload the operator ==.
     * \param mon1: Monomial.
     * \param mon2: Monomial.
     * \return true if mon1==mon2.
     * \return false otherwise.
     */
    bool operator==(Monomial const & mon1, Monomial const & mon2);
    
    /**
     * \brief Overload the operator >.
     * \param mon1: Monomial.
     * \param mon2: Monomial.
     * \return true if mon1>mon2.
     * \return false otherwise.
     */
    bool operator>(Monomial const & mon1, Monomial const & mon2);
    
    /**
     * \brief Overload the operator >=.
     * \param mon1: Monomial.
     * \param mon2: Monomial.
     * \return true if mon1>=mon2.
     * \return false otherwise.
     */
    bool operator>=(Monomial const & mon1, Monomial const & mon2);
    
    /**
     * \brief Overload the operator <.
     * \param mon1: Monomial.
     * \param mon2: Monomial.
     * \return true if mon1<mon2.
     * \return false otherwise.
     */
    bool operator<(Monomial const & mon1, Monomial const & mon2);
    
    /**
     * \brief Overload the operator <=.
     * \param mon1: Monomial.
     * \param mon2: Monomial.
     * \return true if mon1<=mon2.
     * \return false otherwise.
     */
    bool operator<=(Monomial const & mon1, Monomial const & mon2);
}

/** \cond */
#include "../src/monomial.inl"
/** \endcond */

#endif // OPENF4_MONOMIAL_H
