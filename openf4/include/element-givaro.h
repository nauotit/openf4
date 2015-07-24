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
  * \file element-givaro.h
  * \brief Declaration of class ElementGivaro.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef OPENF4_ELEMENT_GIVARO_H
#define OPENF4_ELEMENT_GIVARO_H

#ifdef HAVE_GIVARO

/** \cond */
#include "global.h"
#include <iostream>
#include <string.h>
#include <cassert>
#include <cmath>
#include "givaro/modular-log16.h"
#include "givaro/modular-integer.h"
#include "givaro/gfq.h"
/** \endcond */

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \class ElementGivaro
     * \brief Represent an element of a field with Givaro, this class is a POD (Plain Old Data) because of the alignement required in class Matrix.
     */
    template <class Field>
    class ElementGivaro
    {
        public:
            
            /* static methods */
            
            /**
             * \brief Set the base field.
             * \param field: Givaro modular-log base field.
             */
            static void setField(Field & field);
            
            /**
             * \brief Set the static variable VARIABLE_NAME.
             * \param var: Letter (or string) used to define a polynomial in GFq, default is 't'.
             */
            static void setVariableName(std::string var);
            
            
            /* No constructor because POD */
            
            /* No Destructor because POD */
            
            
            /* Miscellaneous */
            
            /**
             * \brief Set this+=(mult*element).
             * \param element: Element of the prime field.
             * \param mult: Element of the prime field.
             * \return this.
             */
            ElementGivaro<Field> & addMult(ElementGivaro<Field> const & element, ElementGivaro<Field> const & mult);
            
            /**
             * \brief Inverse this according to the base field.
             * \pre The static variable F must be set beforehand.
             * \return this.
             */
            ElementGivaro<Field> & inverse();
            
            /**
             * \brief Print the element.
             */
            void printElementGivaro (std::ostream & stream) const;
            
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
            ElementGivaro & operator=(typename Field::Element element);
            
            /**
             * \brief Overload the operator =.
             * \pre The static variable F must be set beforehand.
             * \param element: Big integer (gmp) under string representation.
             * \return Reference on this.
             */
            ElementGivaro & operator=(std::string element);
            
            /**
             * \brief Overload the operator *=.
             * \pre The static variable F must be set beforehand.
             * \param element: Element of a prime field.
             * \return Reference on this.
             */
            ElementGivaro & operator*=(ElementGivaro const & mult); 
            
            /**
             * \brief Overload the operator -.
             * \pre The static variable F must be set beforehand.
             * \param element: Element of a prime field.
             * \post This is set to -element. 
             * \return Reference on this.
             */
            ElementGivaro & operator-=(ElementGivaro const & element);
            
            
            /* Public attribute because POD */
            
            typename Field::Element _element; /*!< Represent an element of the field of characteristic MODULO */
            
            static Field F; /*!< Base field. */
            static std::string VARIABLE_NAME; /*!< Letter (or string) used to define a polynomial in GF2, default is 't'. */
    };
    
    
    /* External operators */
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    template <class Field>
    std::ostream & operator<<(std::ostream & stream, ElementGivaro<Field> const & element);
    
    /**
     * \brief Overload the operator *.
     * \return element1 * element2.
     */
    template <class Field>
    ElementGivaro<Field> operator * (ElementGivaro<Field> const & element1, ElementGivaro<Field> const & element2);
    
    /**
     * \brief Overload the operator -.
     * \return -element.
     */
    template <class Field>
    ElementGivaro<Field> operator - (ElementGivaro<Field> const & element);
}

/** \cond */
#include "../src/element-givaro.inl"
/** \endcond */

#endif // HAVE_GIVARO
#endif // OPENF4_ELEMENT_GIVARO_H
