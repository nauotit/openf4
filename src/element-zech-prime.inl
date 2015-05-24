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
  * \file element-zech-prime.inl
  * \brief Definition of ElementZechPrime methods.
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
    Field ElementZechPrime<Field>::F;
    
    
    /* Static methods */
    
    template <class Field>
    void 
    ElementZechPrime<Field>::setField(Field & field)
    {
        F=field;
    }
    
    
    /* Miscellaneous */
    
    template <class Field>
    ElementZechPrime<Field> &
    ElementZechPrime<Field>::addMult(ElementZechPrime<Field> const & element, ElementZechPrime<Field> const & mult)
    {
        _element=F.axpyin (_element, element._element, mult._element);
        return * this;
    }
    
    template <class Field>
    ElementZechPrime<Field> &
    ElementZechPrime<Field>::inverse ()
    {
        _element=F.invin(_element);
        return *this;
    }

    template <class Field>
    void
    ElementZechPrime<Field>::printElementPrime (std::ostream & stream) const
    {
        F.write(stream,_element);
    }
            
    template <class Field>
    bool
    ElementZechPrime<Field>::isZero() const
    {
        return F.isZero(_element);
    }
    
    template <class Field>
    bool
    ElementZechPrime<Field>::isOne() const
    {
        return F.isOne(_element);
    }
    
    template <class Field>
    void 
    ElementZechPrime<Field>::setZero()
    {
        F.assign(_element,F.zero);
    }
    
    template <class Field>
    void 
    ElementZechPrime<Field>::setOne()
    {
        F.assign(_element,F.one);
    }
    
    
    /* Operator overload */
            
    template <class Field>
    ElementZechPrime<Field> & 
    ElementZechPrime<Field>::operator=(typename Field::Element element)
    {
        //cout << "Enter assign Zech" << endl;
        _element=F.assign(_element,element);
        return * this;
    }
    
    template <class Field>
    ElementZechPrime<Field> & 
    ElementZechPrime<Field>::operator=(int element)
    {
        //cout << "Enter init Zech" << endl;
        //cout << "F.characteristic(): " << F.characteristic() << endl;
        _element=F.init(_element,(long)element);
        return * this;
    }
    
    template <class Field>
    ElementZechPrime<Field> & 
    ElementZechPrime<Field>::operator=(long element)
    {
        //cout << "Enter init Zech" << endl;
        //cout << "F.characteristic(): " << F.characteristic() << endl;
        _element=F.init(_element,element);
        return * this;
    }
            
    template <class Field>
    ElementZechPrime<Field> & 
    ElementZechPrime<Field>::operator*=(ElementZechPrime<Field> const & mult)
    {
        _element=F.mulin(_element,mult._element);
        return * this;
    }
    
    template <class Field>
    ElementZechPrime<Field> &
    ElementZechPrime<Field>::operator -= (ElementZechPrime<Field> const & element)
    {
        _element=F.neg(_element,element._element);
        return * this;
    }
    
    template <class Field>
    ostream & 
    operator<<(ostream & stream, ElementZechPrime<Field> const & element)
    {
        element.printElementPrime(stream);
        return stream;
    }
    
    template <class Field>
    ElementZechPrime<Field> 
    operator * (ElementZechPrime<Field> const & element1, ElementZechPrime<Field> const & element2)
    {
        ElementZechPrime<Field> copy;
        copy=element1._element;
        return (copy*=element2);
    }
    
    template <class Field>
    ElementZechPrime<Field> 
    operator - (ElementZechPrime<Field> const & element)
    {
        ElementZechPrime<Field> copy;
        copy-=element;
        return copy;
    }
}

#endif // F4_ELEMENT_ZECH_PRIME_INL
