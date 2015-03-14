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
  * \file critical-pair.h
  * \brief Declaration of class CriticalPair.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_CRITICAL_PAIR_H
#define F4_CRITICAL_PAIR_H

#include "tagged-polynomial.h"

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \class CriticalPair
     * Represent a critical pair.
     */
    template <typename Element>
    class CriticalPair
    {
        public:
            
            // Static methods
            
            /**
             * \brief Set the array of tagged polynomial to use.
             * \param taggedPolynomialArray: Address of the array.
             */
            static void setTaggedPolynomialArray(vector<TaggedPolynomial<Element>> * taggedPolynomialArray);
            
            /**
             * \brief Get a tagged polynomial from the array of tagged polynomial.
             * \param numTaggedPolynomial: Index of a tagged polynomial in the array pointed by TAGGEG_POLYNOMIAL_ARRAY.
             */
            static TaggedPolynomial<Element> const &  getTaggedPolynomialArray(int numTaggedPolynomial);
            
             /**
             * \brief Get the size of the array pointed by TAGGEG_POLYNOMIAL_ARRAY.
             */
            static int getSizeTaggedPolynomialArray();
          
            
            
            // Constructor
            
            /**
             * \brief Constructor.
             */ 
            CriticalPair();
            
            /**
             * \brief Constructor.
             * \pre The static variable TAGGEG_POLYNOMIAL_ARRAY must be set beforhand.
             * \param p1: Index of a tagged polynomial in TAGGEG_POLYNOMIAL_ARRAY.
             * \param p2: Index of a tagged polynomial in TAGGEG_POLYNOMIAL_ARRAY.
             */ 
            CriticalPair(int p1, int p2);
            
            
            // Destructor
            
            /**
             * \brief Destructor.
             */ 
            ~CriticalPair();
            
            // Get / Set
            
            /**
             * \brief Get the index of the first tagged polynomial.
             * \return Index of the first tagged polynomial.
             */
            int getP1() const;
            
            /**
             * \brief Get the index of the second tagged polynomial.
             * \return Index of the second tagged polynomial.
             */
            int getP2() const;
            
            /**
             * \brief Get the number of the lcm.
             * \return Number of the lcm.
             */
            int getLcm() const;
            
            /**
             * \brief Get the number of the monomial u1.
             * \return Number of u1.
             */
            int getU1() const;
            
            /**
             * \brief Get the number of the monomial u2.
             * \return Number of u2.
             */
            int getU2() const;
            
            /**
             * \brief Get the degree of this.
             * \return Degree of the critical pair.
             */
            int getDegree() const;
            
            /**
             * \brief Modify an already created critical pair.
             * \pre The static variable TAGGEG_POLYNOMIAL_ARRAY must be set beforhand.
             * \param p1: Index of a tagged polynomial in TAGGEG_POLYNOMIAL_ARRAY.
             * \param p2: Index of a tagged polynomial in TAGGEG_POLYNOMIAL_ARRAY.
             * \return true if the critical pair cannot be skipped with the 1st Buchberger criteria.
             * \return false if it can.
             */ 
            bool setCriticalPair(int p1, int p2);
            
            
            // Miscellaneous
            
            /**
             * \brief Print the critical pair.
             */
            void printCriticalPair (std::ostream & stream = std::cout) const;
            
            /**
             * \brief Compare this with criticalPair.
             * \param criticalPair: CriticalPair.
             * \return 1 if LM(this) > LM(criticalPair) or if (lcm1 = lcm2) & this.(_p1,_p2) newer than criticalPair.(_p1,_p2)
             * \return 0 if this == criticalPair.
             * \return -1 otherwise.
             */
            int compareCriticalPair (CriticalPair const & criticalPair) const;
            
            
            // Internal operator
        
        private:
            int _lcm;              /*!< lcm( LT(List[GTotal[p1]].poly), LT(List[GTotal[p2]].poly) ). */
            int _u1;               /*!< Monomial such that lcm(u1*p1)=lcm=lcm(u2*p2). */
            int _p1;       /*!< Index in GTotal of the tagged polynomial (etiqPol). */
            int _u2;               /*!< Monomial such that lcm(u1*p1)=lcm=lcm(u2*p2). */
            int _p2;       /*!< Index in GTotal of the tagged polynomial (etiqPol). */
            
            static std::vector<TaggedPolynomial<Element>> * TAGGEG_POLYNOMIAL_ARRAY; /*!< Pointer on a dynamic array of TaggedPolynomial */
        
    };
    
    // External operator
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    template <typename Element>
    std::ostream & operator<<(std::ostream & stream, CriticalPair<Element> const & criticalPair);
    
    /**
     * \brief Overload the operator ==.
     * \return true if criticalPair1 == criticalPair2.
     * \return false otherwise.
     */
    template <typename Element>
    bool operator==(CriticalPair<Element> const & criticalPair1, CriticalPair<Element> const & criticalPair2);
    
    /**
     * \brief Overload the operator >.
     * \return true if criticalPair1 > criticalPair2.
     * \return false otherwise.
     */
    template <typename Element>
    bool operator>(CriticalPair<Element> const & criticalPair1, CriticalPair<Element> const & criticalPair2);
    
    /**
     * \brief Overload the operator >=.
     * \return true if criticalPair1 >= criticalPair2.
     * \return false otherwise.
     */
    template <typename Element>
    bool operator>=(CriticalPair<Element> const & criticalPair1, CriticalPair<Element> const & criticalPair2);
    
    /**
     * \brief Overload the operator <.
     * \return true if criticalPair1 < criticalPair2.
     * \return false otherwise.
     */
    template <typename Element>
    bool operator<(CriticalPair<Element> const & criticalPair1, CriticalPair<Element> const & criticalPair2);
    
    /**
     * \brief Overload the operator <=.
     * \return true if criticalPair1 <= criticalPair2.
     * \return false otherwise.
     */
    template <typename Element>
    bool operator<=(CriticalPair<Element> const & criticalPair1, CriticalPair<Element> const & criticalPair2);
}

#include "../src/critical-pair.inl"

#endif // F4_CRITICAL_PAIR_H
