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
  * \file element-gf2.inl
  * \brief Definition of ElementGF2 methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_ELEMENT_GF2_INL
#define F4_ELEMENT_GF2_INL

using namespace std;

namespace F4
{
    /* Global variables */
    
    extern int VERBOSE;
    
    
    /* Miscellaneous */
    
    inline bool
    ElementGF2::getElement ()
    {
        return _element;
    }
    
    ElementGF2 &
    ElementGF2::addMult(ElementGF2 const & element, ElementGF2 const & mult)
    {
        _element^=(element._element & mult._element);
        return * this;
    }
    
    ElementGF2 &
    ElementGF2::inverse ()
    {
        return *this;
    }
    
    void
    ElementGF2::printElementGF2 (std::ostream & stream) const
    {
        stream << (int)_element;
    }
            
    bool
    ElementGF2::isZero() const
    {
        return _element==0;
    }
    
    bool
    ElementGF2::isOne() const
    {
        return _element==1;
    }
    
    void 
    ElementGF2::setZero()
    {
        _element=0;
    }
    
    void 
    ElementGF2::setOne()
    {
        _element=1;
    }
    
    
    /* Operator overload */
            
    ElementGF2 & 
    ElementGF2::operator=(bool element)
    {
        _element=element;
        return * this;
    }
            
    ElementGF2 & 
    ElementGF2::operator*=(ElementGF2 const & mult)
    {
        _element&=mult._element;
        return * this;
    }
    
    ostream & 
    operator<<(ostream & stream, ElementGF2 const & element)
    {
        element.printElementGF2(stream);
        return stream;
    }
    
    ElementGF2 
    operator * (ElementGF2 const & element1, ElementGF2 const & element2)
    {
        ElementGF2 copy;
        copy._element=element1._element;
        return (copy*=element2);
    }
    
    ElementGF2 
    operator - (ElementGF2 const & element)
    {
        ElementGF2 copy;
        copy._element=element._element;
        return copy;
    }

}

#endif // F4_ELEMENT_GF2_INL
