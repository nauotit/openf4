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
  * \file element-givaro.inl
  * \brief Definition of ElementGivaro methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_ELEMENT_ZECH_PRIME_INL
#define F4_ELEMENT_ZECH_PRIME_INL

using namespace std;

namespace F4
{
    /* Global variables */
    
    extern int VERBOSE;
    
    
    /* Static variables */
    
    template <class Field>
    Field ElementGivaro<Field>::F;
    
    
    /* Static methods */
    
    template <class Field>
    void 
    ElementGivaro<Field>::setField(Field & field)
    {
        F=field;
    }
    
    
    /* Miscellaneous */
    
    template <class Field>
    ElementGivaro<Field> &
    ElementGivaro<Field>::addMult(ElementGivaro<Field> const & element, ElementGivaro<Field> const & mult)
    {
        _element=F.axpyin (_element, element._element, mult._element);
        return * this;
    }
    
    template <class Field>
    ElementGivaro<Field> &
    ElementGivaro<Field>::inverse ()
    {
        _element=F.invin(_element);
        return *this;
    }

    template <class Field>
    void
    ElementGivaro<Field>::printElementPrime (std::ostream & stream) const
    {
        F.write(stream,_element);
    }
            
    template <class Field>
    bool
    ElementGivaro<Field>::isZero() const
    {
        return F.isZero(_element);
    }
    
    template <class Field>
    bool
    ElementGivaro<Field>::isOne() const
    {
        return F.isOne(_element);
    }
    
    template <class Field>
    void 
    ElementGivaro<Field>::setZero()
    {
        F.assign(_element,F.zero);
    }
    
    template <class Field>
    void 
    ElementGivaro<Field>::setOne()
    {
        F.assign(_element,F.one);
    }
    
    
    /* Operator overload */
            
    template <class Field>
    ElementGivaro<Field> & 
    ElementGivaro<Field>::operator=(typename Field::Element element)
    {
        _element=F.assign(_element,element);
        return * this;
    }
    
    template <class Field>
    ElementGivaro<Field> & 
    ElementGivaro<Field>::operator=(int element)
    {
        _element=F.init(_element,(long)element);
        return * this;
    }
    
    template <class Field>
    ElementGivaro<Field> & 
    ElementGivaro<Field>::operator=(long element)
    {
        _element=F.init(_element,element);
        return * this;
    }
    
    /* For Integer (gmp) */
    template <class Field>
    ElementGivaro<Field> & 
    ElementGivaro<Field>::operator=(string element)
    {
        _element=F.init(_element,Givaro::Integer(element.c_str()));
        return * this;
    }
            
    template <class Field>
    ElementGivaro<Field> & 
    ElementGivaro<Field>::operator*=(ElementGivaro<Field> const & mult)
    {
        _element=F.mulin(_element,mult._element);
        return * this;
    }
    
    template <class Field>
    ElementGivaro<Field> &
    ElementGivaro<Field>::operator -= (ElementGivaro<Field> const & element)
    {
        _element=F.neg(_element,element._element);
        return * this;
    }
    
    template <class Field>
    ostream & 
    operator<<(ostream & stream, ElementGivaro<Field> const & element)
    {
        element.printElementPrime(stream);
        return stream;
    }
    
    template <class Field>
    ElementGivaro<Field> 
    operator * (ElementGivaro<Field> const & element1, ElementGivaro<Field> const & element2)
    {
        ElementGivaro<Field> copy;
        copy=element1._element;
        return (copy*=element2);
    }
    
    template <class Field>
    ElementGivaro<Field> 
    operator - (ElementGivaro<Field> const & element)
    {
        ElementGivaro<Field> copy;
        copy-=element;
        return copy;
    }
}

#endif // F4_ELEMENT_ZECH_PRIME_INL
