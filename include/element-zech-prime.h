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
  * \file element-zech-prime.h
  * \brief Declaration of class ElementZechPrime.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_ELEMENT_ZECH_PRIME_H
#define F4_ELEMENT_ZECH_PRIME_H

/** \cond */
#include <iostream>
#include <string.h>
#include <cassert>
#include <cmath>
#include "givaro/modular-log16.h"
/** \endcond */

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \class ElementZechPrime
     * Represent an element of a prime field with zech logarithm tables, this class is a POD (Plain Old Data) because of the alignement required in class Matrix.
     */
    template <class Field>
    class ElementZechPrime
    {
        public:
            
            /* static methods */
            
            /**
             * \brief Set the base field.
             * \param field: Givaro modular-log base field.
             */
            static void setField(Field & field);
            
            
            /* No constructor because POD */
            
            /* No Destructor because POD */
            
            
            /* Miscellaneous */
            
            /**
             * \brief Set this+=(mult*element).
             * \param element: Element of the prime field.
             * \param mult: Element of the prime field.
             * \return this.
             */
            ElementZechPrime<Field> & addMult(ElementZechPrime<Field> const & element, ElementZechPrime<Field> const & mult);
            
            /**
             * \brief Inverse this according to the base field.
             * \pre The static variable F must be set beforehand.
             * \return this.
             */
            ElementZechPrime<Field> & inverse();
            
            /**
             * \brief Print the element.
             */
            void printElementPrime (std::ostream & stream) const;
            
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
             * \pre The static variable F must be set beforehand.
             * \param element: Element of a prime field.
             * \return Reference on this.
             */
            ElementZechPrime & operator=(typename Field::Element element);
            
            /**
             * \brief Overload the operator =.
             * \pre The static variable F must be set beforehand.
             * \param element: Integer representing  an element of a prime field.
             * \return Reference on this.
             */
            ElementZechPrime & operator=(int element);
            
            /**
             * \brief Overload the operator =.
             * \pre The static variable F must be set beforehand.
             * \param element: Integer representing  an element of a prime field.
             * \return Reference on this.
             */
            ElementZechPrime & operator=(long element);
            
            /**
             * \brief Overload the operator *=.
             * \pre The static variable F must be set beforehand.
             * \param element: Element of a prime field.
             * \return Reference on this.
             */
            ElementZechPrime & operator*=(ElementZechPrime const & mult); 
            
            /**
             * \brief Overload the operator -.
             * \pre The static variable F must be set beforehand.
             * \param element: Element of a prime field.
             * \post This is set to -element. 
             * \return Reference on this.
             */
            ElementZechPrime & operator-=(ElementZechPrime const & element);
            
            
            /* Public attribute because POD */
            
            typename Field::Element _element; /*!< Represent an element of the field of characteristic MODULO */
            
            static Field F; /*!< Base field. */
    };
    
    
    /* External operators */
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    template <class Field>
    std::ostream & operator<<(std::ostream & stream, ElementZechPrime<Field> const & element);
    
    /**
     * \brief Overload the operator *.
     * \return element1 * element2.
     */
    template <class Field>
    ElementZechPrime<Field> operator * (ElementZechPrime<Field> const & element1, ElementZechPrime<Field> const & element2);
    
    /**
     * \brief Overload the operator -.
     * \return -element.
     */
    template <class Field>
    ElementZechPrime<Field> operator - (ElementZechPrime<Field> const & element);
}

#include "../src/element-zech-prime.inl"

#endif // F4_ELEMENT_ZECH_PRIME_H
