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
  * \file element-gf2-extension.h
  * \brief Declaration of class ElementGF2Extension.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_ELEMENT_GF2_EXTENSION_H
#define F4_ELEMENT_GF2_EXTENSION_H

/** \cond */
#include "global.h"
#include <iostream>
#include <string.h>
#include <cassert>
#include <algorithm>
#include <cctype>
/** \endcond */

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \class ElementGF2Extension
     * \brief Represent an element of an extension of GF2, this class is a POD (Plain Old Data) because of the alignement required in class Matrix.
     */
    template <typename baseType>
    class ElementGF2Extension
    {
        public:
            
            /* static methods */
            
            /**
             * \brief Set the static variable MODULO.
             * \param modulo: Irreducible polynomial used to construct GF(2^n). MODULO is under bits representation (ex: 0x10011001 = t^7+t^4+t^3+1).
             */
            static void setModulo(baseType modulo);
            
            /**
             * \brief Set the static variable MODULO.
             * \param modulo: Irreducible polynomial used to construct GF(2^n). MODULO is under string representation (ex: "t^7+t^4+t^3+1").
             */
            static void setModulo(std::string modulo);
            
            /**
             * \brief Get the static variable MODULO.
             * \return Irreducible polynomial used to construct GF(2^n). MODULO is under bits representation (ex: 0x10011001 = t^7+t^4+t^3+1).
             */
            static baseType getModulo();
            
            /**
             * \brief Set the static variable VARIABLE_NAME.
             * \param var: Letter (or string) used to define a polynomial in GF2, default is 't'.
             */
            static void setVariableName(std::string var);
            
            /**
             * \brief Get the static variable MASK.
             * \return Maximum power of 2 lower than MODULO.
             */
            static baseType getMask();
            
            /**
             * \brief Get the static variable MASK_BIT.
             * \return Number j such that MASK = 1 << j.
             */
            static baseType getMaskBit();
            
            
            /* No constructor because POD */
            
            /* No Destructor because POD */
            
            
            /* Miscellaneous */
            
            /**
             * \brief Set this with a degree lower than MODULO.
             * \post this with a degree lower than MODULO.
             * \return Integer form of this.
             */
            baseType modulo ();
            
            /**
             * \brief Return this.
             * \return Integer form of this.
             */
            baseType getElement () const;
            
            /**
             * \brief Set this+=(mult*element).
             * \param element: Element of the field GF2[t]/MODULO.
             * \param mult: Element of the field GF2[t]/MODULO.
             * \pre mult has a degree lower than MODULO.
             * \pre element has a degree lower than MODULO.
             * \post this mult has a degree lower than MODULO.
             * \return this.
             */
            ElementGF2Extension<baseType> & addMult(ElementGF2Extension<baseType> const & element, ElementGF2Extension<baseType> const & mult);
            
            /**
             * \brief Set this+=(mult*element). Use a base of 2.
             * \param element: Element of the field GF2[t]/MODULO.
             * \param mult: Element of the field GF2[t]/MODULO.
             * \pre mult has a degree lower than MODULO.
             * \pre element has a degree lower than MODULO.
             * \post this mult has a degree lower than MODULO.
             * \return this.
             */
            ElementGF2Extension<baseType> & addMultBase2(ElementGF2Extension<baseType> const & element, ElementGF2Extension<baseType> const & mult);
            
            /**
             * \brief Set this+=(mult*element). Use a base of 4.
             * \param element: Element of the field GF2[t]/MODULO.
             * \param mult: Element of the field GF2[t]/MODULO.
             * \pre mult has a degree lower than MODULO.
             * \pre element has a degree lower than MODULO.
             * \post this mult has a degree lower than MODULO.
             * \return this.
             */
            ElementGF2Extension<baseType> & addMultBase4(ElementGF2Extension<baseType> const & element, ElementGF2Extension<baseType> const & mult);
            
            /**
             * \brief Set this+=(mult*element). Use a base of 16.
             * \param element: Element of the field GF2[t]/MODULO.
             * \param mult: Element of the field GF2[t]/MODULO.
             * \pre mult has a degree lower than MODULO.
             * \pre element has a degree lower than MODULO.
             * \post this mult has a degree lower than MODULO.
             * \return this.
             */
            ElementGF2Extension<baseType> & addMultBase16(ElementGF2Extension<baseType> const & element, ElementGF2Extension<baseType> const & mult);
            
            /**
             * \brief Set this+=(mult*element). Use a base of 256.
             * \param element: Element of the field GF2[t]/MODULO.
             * \param mult: Element of the field GF2[t]/MODULO.
             * \pre mult has a degree lower than MODULO.
             * \pre element has a degree lower than MODULO.
             * \post this mult has a degree lower than MODULO.
             * \return this.
             */
            ElementGF2Extension<baseType> & addMultBase256(ElementGF2Extension<baseType> const & element, ElementGF2Extension<baseType> const & mult);
            
            /**
             * \brief Inverse this according to the base field.
             * \pre The static variable MODULO must be set beforehand. Beware, baseType must be signed.
             * \post this is set in [-MODULO/2, MODULO/2].
             * \return this.
             */
            ElementGF2Extension<baseType> & inverse();
            
            /**
             * \brief Print the element.
             */
            void printElementGF2Extension (std::ostream & stream) const;
            
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
             * \param element: Element of GF(2^n) under binary representation.
             * \return Reference on this.
             */
            ElementGF2Extension & operator=(baseType const element);
            
            /**
             * \brief Overload the operator =.
             * \pre The static variable MODULO must be set beforehand.
             * \post this has a degree lower than MODULO.
             * \param element: Element of GF(2^n) under string representation.
             * \return Reference on this.
             */
            ElementGF2Extension & operator=(std::string element);
            
            /**
             * \brief Overload the operator *=.
             * \pre The static variable MODULO must be set beforehand.
             * \param element: Element of the field GF2[t]/MODULO.
             * \pre mult has a degree lower than MODULO.
             * \post this has a degree lower than MODULO.
             * \return Reference on this.
             */
            ElementGF2Extension & operator*=(ElementGF2Extension const & mult); 
            
            /**
             * \brief Multiply this by mult using base2 decomposition.
             * \pre The static variable MODULO must be set beforehand.
             * \param element: Element of the field GF2[t]/MODULO.
             * \pre mult has a degree lower than MODULO.
             * \post this has a degree lower than MODULO.
             * \return Reference on this.
             */
            ElementGF2Extension & multBase2(ElementGF2Extension const & mult); 
            
            /**
             * \brief Multiply this by mult using base4 decomposition.
             * \pre The static variable MODULO must be set beforehand.
             * \param element: Element of the field GF2[t]/MODULO.
             * \pre mult has a degree lower than MODULO.
             * \post this has a degree lower than MODULO.
             * \return Reference on this.
             */
            ElementGF2Extension & multBase4(ElementGF2Extension const & mult); 
            
            /**
             * \brief Multiply this by mult using base16 decomposition.
             * \pre The static variable MODULO must be set beforehand.
             * \param element: Element of the field GF2[t]/MODULO.
             * \pre mult has a degree lower than MODULO.
             * \post this has a degree lower than MODULO.
             * \return Reference on this.
             */
            ElementGF2Extension & multBase16(ElementGF2Extension const & mult);
            
            /**
             * \brief Multiply this by mult using base256 decomposition.
             * \pre The static variable MODULO must be set beforehand.
             * \param element: Element of the field GF2[t]/MODULO.
             * \pre mult has a degree lower than MODULO.
             * \post this has a degree lower than MODULO.
             * \return Reference on this.
             */
            ElementGF2Extension & multBase256(ElementGF2Extension const & mult);
            
            /* Public attribute because POD */
            
            baseType _element; /*!< Represent an element of the field GF2[t]/MODULO */
            
            static baseType MODULO; /*!< Irreducible polynomial used to construct GF(2^n). MODULO is under bits representation (ex: 0x10011001 = t^7+t^4+t^3+1). */
            static baseType MASK_BIT; /*!< MASK = 1 << MASK_BIT */
            static baseType MASK; /*!< Power of 2 used to test if MODULO must be applied */
            static std::string VARIABLE_NAME; /*!< Letter (or string) used to define a polynomial in GF2, default is 't'. */
    };
    
    
    /* External operators */
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    template <typename baseType>
    std::ostream & operator<<(std::ostream & stream, ElementGF2Extension<baseType> const & element);
    
    /**
     * \brief Overload the operator *.
     * \return element1 * element2.
     */
    template <typename baseType>
    ElementGF2Extension<baseType> operator * (ElementGF2Extension<baseType> const & element1, ElementGF2Extension<baseType> const & element2);
    
    /**
     * \brief Overload the operator -.
     * \return -element.
     */
    template <typename baseType>
    ElementGF2Extension<baseType> operator - (ElementGF2Extension<baseType> const & element);
}

/** \cond */
#include "../src/element-gf2-extension.inl"
/** \endcond */

#endif // F4_ELEMENT_GF2_EXTENSION_H
