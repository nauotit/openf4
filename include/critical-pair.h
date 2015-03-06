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
            
            // Constructor
            
            CriticalPair();
            
            CriticalPair(int p1, int p2);
            
            
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
