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
  * \file element-prime.h
  * \brief Declaration of class ElementPrime.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef OPENF4_ELEMENT_PRIME_H
#define OPENF4_ELEMENT_PRIME_H

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
     * \class ElementPrime
     * \brief Represent an element of a prime field, this class is a POD (Plain Old Data) because of the alignement required in class Matrix.
     */
    template <typename baseType>
    class ElementPrime
    {
        public:
            
            /* static methods */
            
            /**
             * \brief Set the static variable MODULO.
             * \param modulo: Characteristic of the base field.
             */
            static void setModulo(baseType modulo);
            
            /**
             * \brief Get the static variable MODULO.
             * \return Characteristic of the base field.
             */
            static baseType getModulo();
            
            /**
             * \brief Get the static variable MAX.
             * \return Maximum range for the baseType elements.
             */
            static baseType getMax();
            
            
            /* No constructor because POD */
            
            /* No Destructor because POD */
            
            
            /* Miscellaneous */
            
            /**
             * \brief Set this in [-MODULO/2, MODULO/2].
             * \post this is set in [-MODULO/2, MODULO/2].
             * \return Integer form of this.
             */
            baseType modulo ();
            
            /**
             * \brief Return this.
             * \return Integer form of this.
             */
            baseType getElement ();
            
            /**
             * \brief Set this+=(mult*element).
             * \param element: Element of the prime field.
             * \param mult: Element of the prime field.
             * \pre mult is set in [-MODULO/2, MODULO/2].
             * \pre element is set in [-MODULO/2, MODULO/2].
             * \post this is set in [-MAX, MAX].
             * \return this.
             */
            ElementPrime<baseType> & addMult(ElementPrime<baseType> const & element, ElementPrime<baseType> const & mult);
            
            /**
             * \brief Inverse this according to the base field.
             * \pre The static variable MODULO must be set beforehand. Beware, baseType must be signed.
             * \post this is set in [-MODULO/2, MODULO/2].
             * \return this.
             */
            ElementPrime<baseType> & inverse();
            
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
             * \pre The static variable MODULO must be set beforehand.
             * \param element: Element of a prime field.
             * \return Reference on this.
             */
            ElementPrime & operator=(baseType element);
            
            /**
             * \brief Overload the operator *=.
             * \pre The static variable MODULO must be set beforehand.
             * \param element: Element of a prime field.
             * \pre mult is set in [-MODULO/2, MODULO/2].
             * \post this is set in [-MODULO/2, MODULO/2].
             * \return Reference on this.
             */
            ElementPrime & operator*=(ElementPrime const & mult); 
            
            
            /* Public attribute because POD */
            
            baseType _element; /*!< Represent an element of the field of characteristic MODULO */
            
            static baseType MODULO; /*!< Characteristic of the base field. */
            static baseType MAX; /*!< Maximum range for the baseType elements. */
    };
    
    
    /* External operators */
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    template <typename baseType>
    std::ostream & operator<<(std::ostream & stream, ElementPrime<baseType> const & element);
    
    /**
     * \brief Overload the operator *.
     * \return element1 * element2.
     */
    template <typename baseType>
    ElementPrime<baseType> operator * (ElementPrime<baseType> const & element1, ElementPrime<baseType> const & element2);
    
    /**
     * \brief Overload the operator -.
     * \return -element.
     */
    template <typename baseType>
    ElementPrime<baseType> operator - (ElementPrime<baseType> const & element);
}

/** \cond */
#include "../src/element-prime.inl"
/** \endcond */

#endif // OPENF4_ELEMENT_PRIME_H
