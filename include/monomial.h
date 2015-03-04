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
#include <vector>
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
             * \param weight: Array of weights.
             */
             static void setWeight(int  * weight);
             
             /**
             * \brief Get the static variable WEIGHT.
             * \return Value of WEIGHT.
             */
             static int * getWeight();
             
            /**
             * \brief Modify the dynamic 2D array NB_MONOMIAL, and call setMonomialArray().
             * \pre Static variables NB_VARIABLE and WEIGHT must be set beforehand.
             * \param maxDegree: Maximal degree (height) of NB_MONOMIAL.
             */
             static void setNbMonomial(int maxDegree);
             
             /**
             * \brief Get the dynamic 2D array NB_MONOMIAL.
             * \return Reference on NB_MONOMIAL.
             */
             static std::vector<int *> & getNbMonomial();
             
             /**
             * \brief Free the dynamic 2D array NB_MONOMIAL, and call freeMonomialArray().
             * \param maxDegree: Maximal degree (height) of NB_MONOMIAL.
             */
             static void freeNbMonomial();
             
             /**
             * \brief Modify the dynamic array MONOMIAL_ARRAY.
             * \pre Static variables NB_VARIABLE and NB_MONOMIAL must be set beforehand.
             */
             static void setMonomialArray();
             
             /**
             * \brief Get the dynamic array MONOMIAL_ARRAY.
             * \return Reference on MONOMIAL_ARRAY.
             */
             static std::vector<Monomial> & getMonomialArray();
             
             /**
             * \brief Free the dynamic array MONOMIAL_ARRAY.
             */
             static void freeMonomialArray();
             
             /**
             * \brief Modify the static 2D array TABULATED_PRODUCT.
             * \pre Static variables NB_VARIABLE, NB_MONOMIAL and MONOMIAL_ARRAY must be set beforehand.
             * \param deg1: Maximum degree of line monomials.
             * \param deg2: Maximum degree of column monomials.
             */
             static void setTabulatedProduct(int deg1, int deg2);
             
             /**
             * \brief Get the static 2D array NB_MONOMIAL.
             * \return Value of NB_MONOMIAL.
             */
             static int ** getTabulatedProduct();
             
             /**
             * \brief Free the static 2D array NB_MONOMIAL.
             * \pre The static variables NB_VARIABLE must be set beforehand.
             */
             static void freeTabulatedProduct();
             
             /**
             * \brief Multiply two monomials, using TABULATED_PRODUCT if possible.
             * \param numMon1: Number of the first monomial.
             * \param numMon2: Number of the second monomial.
             * \return Number of the product intToMonomial[numMon1] * intToMonomial[numMon2].
             */
             static int multNumMonomial(int numMon1, int numMon2);
             
             /**
              * \brief Initialise the static parameters of Monomial.
              * \param nbVariable: Number of variables of the polynomial ring.
              * \param maxDegree: maxDegree: Maximal degree (height) of NB_MONOMIAL.
              * \param deg1: Maximum degree of line monomials in TABULATED_PRODUCT.
              * \param deg2: Maximum degree of column monomials in TABULATED_PRODUCT.
              * \param verbose: verbosity level.
              */
             static void initMonomial(int nbVariable, int maxDegree, int deg1, int deg2, int verbose);
             
             /**
              * \brief Free the space allocated by initMonomial.
              */
             static void freeMonomial();
            
            // Constructor
            
            /**
             * \brief Constructor.
             * \pre The static variable NB_VARIABLE must be set beforehand.
             */
            Monomial(); 
            
            /**
             * \brief Constructor.
             * \pre Static variables NB_VARIABLE and WEIGHT must be set beforehand.
             * \param varlist: Array representing the degree of each variable of the monomial.
             */
            Monomial(int const * varlist); 
            
            /**
             * \brief Constructor.
             * \pre Static variables NB_VARIABLE, WEIGHT and VARS must be set beforehand.
             * \param s: String representing the monomial.
             */
            Monomial(std::string const s); 
            
            /**
             * \brief Constructor.
             * \pre Static variables NB_VARIABLE, WEIGHT and VARS must be set beforehand.
             * \param numMon: number of the constructed monomial, 0 is the smallest monomial of the given degree.
             */
            Monomial(int numMon); 
            
            /**
             * \brief Copy constructor.
             * \pre The static variable NB_VARIABLE must be set beforehand.
             * \param toCopy: Monomial.
             */
            Monomial(Monomial const & toCopy);
            
            /**
             * \brief Move constructor. Used when mon is unnamed.
             * \pre The static variable NB_VARIABLE must be set beforehand.
             * \param toCopy: Monomial.
             */
            Monomial(Monomial && toCopy);
             
             
             // Destructor
            
            /**
             * \brief Destructor.
             */
            ~Monomial();
            
            
            // Get / Set
            
            /**
             * \brief Get the degree of this.
             * \return Degree of this.
             */
            int getDegree() const;
            
            /**
             * \brief Get the varlist of this.
             * \return Varlist of this.
             */
            int * getVarlist() const;
            
            // Miscellaneous
            
            /**
             * \brief Initialize this with varlist. 
             * \pre Static variables NB_VARIABLE and WEIGHT must be set beforehand.
             * \param varlist: Array representing the degree of each variable of the monomial.
             */
            void setMonomial(int const * varlist);
            
            /**
             * \brief Initialize this with s.
             * \pre Static variables NB_VARIABLE, WEIGHT and VARS must be set beforehand.
             * \param s: String representing the monomial.
             */
            void setMonomial(std::string const s);
            
            /**
             * \brief Initialize this with the num-th monomial.
             * \pre Static variables NB_VARIABLE, WEIGHT and NB_MONOMIAL must be set beforehand.
             * \param numMon: number of the constructed monomial, 0 is the smallest monomial of the given degree.
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
            void printMonomial (std::ostream & stream = std::cout) const;
            
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
            
            
            // Internal operators
            
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
             * \brief Overload the operator /=.
             * \pre Static variables NB_VARIABLE and WEIGHT must be set beforehand.
             * \param mon: Monomial (divisor).
             * \return Reference on this.
             */
            Monomial & operator/=(Monomial const & mon); 
        
        private:
            int _deg;                /*!< Degree of the monomial */
            int *_varlist;           /*!< Array representing the degree of each variable of the monomial */
            
            static int VERBOSE; 
            static int NB_VARIABLE;   /*!< Number of variables of the polynomial ring. */
            static std::string const * VARS; /*!< Array of NB_VARIABLE string representing the variable names. */
            static int * WEIGHT; /*!< Array of NB_VARIABLE weights. */
            /**
             * \brief NB_MONOMIAL[d][v] = Number of degree d monomials in the v first variables.
             * NB_MONOMIAL[d][NB_VARIABLE+1] = Number of monomials of degree <= d.
             */
            static std::vector<int *> NB_MONOMIAL;
            static std::vector<Monomial> MONOMIAL_ARRAY; /*!< Dynamic array of monomial */
            static int MAX_DEGREE; /*!< Maximal degree (height) of NB_MONOMIAL. */
            static int NUM_MAX_LINE; /*!< Number of line in TABULATED_PRODUCT. */
            static int NUM_MAX_COLUMN; /*!< Number of column in TABULATED_PRODUCT. */
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
