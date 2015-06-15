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
  * \file element-gf2.h
  * \brief Declaration of class ElementGF2.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_ELEMENT_GF2_H
#define F4_ELEMENT_GF2_H

/** \cond */
#include "global.h"
#include <iostream>
#include <string.h>
#include <cassert>
#include <cmath>
/** \endcond */

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \class ElementGF2
     * \brief Represent an element of the field GF(2), this class is a POD (Plain Old Data) because of the alignement required in class Matrix.
     */
    class ElementGF2
    {
        public:
            
            /* No constructor because POD */
            
            /* No Destructor because POD */
            
            
            /* Miscellaneous */
            
            /**
             * \brief Return this.
             * \return Integer form of this.
             */
            bool getElement ();
            
            /**
             * \brief Set this+=(mult*element).
             * \param element: Element of the prime field.
             * \param mult: Element of the field gf2.
             * \return this.
             */
            ElementGF2 & addMult(ElementGF2 const & element, ElementGF2 const & mult);
            
            /**
             * \brief Inverse this according to the base field (for genericity).
             * \return this.
             */
            ElementGF2 & inverse();
            
            /**
             * \brief Print the element.
             */
            void printElementGF2 (std::ostream & stream) const;
            
            /**
             * \brief Test if this is nul.
             * \return  true if this==zero.
             * \return  false otherwise.
             */
            bool isZero() const;
            
            /**
             * \brief Test if this is one (neutral multiplicative element).
             * \return  true if this==one.
             * \return  false otherwise.
             */
            bool isOne() const;
            
            /**
             * \brief Set the element to zero.
             */
            void setZero();
            
             /**
             * \brief Set the element to one.
             */
            void setOne();
            
            
            /* Internal operators */
            
            /**
             * \brief Overload the operator =.
             * \param element: Element of the field GF(2).
             * \return Reference on this.
             */
            ElementGF2 & operator=(bool element);
            
            /**
             * \brief Overload the operator *=.
             * \param element: Element of the field GF(2).
             * \return Reference on this.
             */
            ElementGF2 & operator*=(ElementGF2 const & mult); 
            
            
            /* Public attribute because POD */
            
            bool _element; /*!< Represent an element of the field GF(2) */
            
    };
    
    
    /* External operators */
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    std::ostream & operator<<(std::ostream & stream, ElementGF2 const & element);
    
    /**
     * \brief Overload the operator *.
     * \return element1 * element2.
     */
    ElementGF2 operator * (ElementGF2 const & element1, ElementGF2 const & element2);
    
    /**
     * \brief Overload the operator -.
     * \return -element.
     */
    ElementGF2 operator - (ElementGF2 const & element);
}

/** \cond */
#include "../src/element-gf2.inl"
/** \endcond */

#endif // F4_ELEMENT_GF2_H
