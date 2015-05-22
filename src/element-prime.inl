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
  * \file element-prime.inl
  * \brief Definition of ElementPrime methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_ELEMENT_PRIME_INL
#define F4_ELEMENT_PRIME_INL

using namespace std;

namespace F4
{
    /* Global variables */
    
    extern int VERBOSE;
    
    
    /* Static variables */
    
    template <typename baseType>
    baseType ElementPrime<baseType>::MODULO=0;
    
    template <typename baseType>
    baseType ElementPrime<baseType>::MAX=0;
    
    
    /* Static methods */
    
    template <typename baseType>
    void 
    ElementPrime<baseType>::setModulo(baseType modulo)
    {
        MODULO=modulo;
        MAX=((baseType)1<<(sizeof(baseType)*8-2));
    }
    
    template <>
    void 
    ElementPrime<double>::setModulo(double modulo)
    {
        MODULO=modulo;
        MAX=((int64_t)1<<(sizeof(double)*8-2));
    }
    
    template <typename baseType>
    baseType 
    ElementPrime<baseType>::getModulo()
    {
        return MODULO;
    }
    
    template <typename baseType>
    baseType 
    ElementPrime<baseType>::getMax()
    {
        return MAX;
    }
    
    
    /* Miscellaneous */
    
    template <typename baseType>
    inline baseType
    ElementPrime<baseType>::modulo ()
    {
        if((_element > MODULO / 2) || (_element < -MODULO / 2))
        {
            _element%=MODULO;
            if (_element > MODULO / 2)
            {
                _element -= MODULO;
            }
            if (_element < -MODULO / 2)
            {
                _element += MODULO;
            }
        }
        return _element;
    }
    
    template <typename baseType>
    inline baseType
    ElementPrime<baseType>::getElement ()
    {
        return _element;
    }
    
    template <>
    inline double
    ElementPrime<double>::modulo ()
    {
        if((_element > MODULO / 2) || (_element < -MODULO / 2))
        {
            _element=fmod(_element,MODULO);
            if (_element > MODULO / 2)
            {
                _element -= MODULO;
            }
            if (_element < -MODULO / 2)
            {
                _element += MODULO;
            }
        }
        return _element;
    }
    
    template <typename baseType>
    ElementPrime<baseType> &
    ElementPrime<baseType>::addMult(ElementPrime<baseType> const & element, ElementPrime<baseType> const & mult)
    {
        assert((mult._element>=-MODULO/2) && (mult._element<=MODULO/2));
        assert((element._element>=-MODULO/2) && (element._element<=MODULO/2));
        if(( _element<=-MAX) || (_element>=MAX))
        {
            _element%=MODULO;
        }
        _element+=(element._element*mult._element);
        return * this;
    }
    
    template <>
    ElementPrime<double> &
    ElementPrime<double>::addMult(ElementPrime<double> const & element, ElementPrime<double> const & mult)
    {
        assert((mult._element>=-MODULO/2) && (mult._element<=MODULO/2));
        assert((element._element>=-MODULO/2) && (element._element<=MODULO/2));
        if(( _element<=-MAX) || (_element>=MAX))
        {
            _element=fmod(_element,MODULO);
        }
        _element+=(element._element*mult._element);
        return * this;
    }
    
    template <typename baseType>
    ElementPrime<baseType> &
    ElementPrime<baseType>::inverse ()
    {
        _element%=MODULO;
        baseType a, b, c, inv;
        baseType a_x, a_p, b_x, b_p, c_x, c_p;
        baseType l;
        inv = _element;
        if (inv < 0)
        {
            inv += MODULO;
        }
        a = inv;
        a_x = 1;
        a_p = 0;
        b = MODULO;
        b_x = 0;
        b_p = 1;

        while (a)
        {
            if (b < 2 * a)
            {
                c = b - a;
                c_x = b_x - a_x;
                c_p = b_p - a_p;
            }
            else
            {
                l = b / a;
                c = b - l * a;
                c_x = b_x - l * a_x;
                c_p = b_p - l * a_p;
            }
            b = a;
            b_x = a_x;
            b_p = a_p;
            a = c;
            a_x = c_x;
            a_p = c_p;
        }

        if (b != 1)
        {
            cerr << "Inverse impossible Mod(" << _element << ", " << MODULO << ") -> gcd = " << b << endl; 
            exit (1);
        }
        _element=b_x;
        modulo();
        return *this;
    }
    
    template <>
    ElementPrime<double> &
    ElementPrime<double>::inverse ()
    {
        _element=fmod(_element,MODULO);
        double a, b, c, inv;
        double a_x, a_p, b_x, b_p, c_x, c_p;
        double l;
        inv = _element;
        if (inv < 0)
        {
            inv += MODULO;
        }
        a = inv;
        a_x = 1;
        a_p = 0;
        b = MODULO;
        b_x = 0;
        b_p = 1;

        while (a)
        {
            if (b < 2 * a)
            {
                c = b - a;
                c_x = b_x - a_x;
                c_p = b_p - a_p;
            }
            else
            {
                l = floor(b / a);
                c = b - l * a;
                c_x = b_x - l * a_x;
                c_p = b_p - l * a_p;
            }
            b = a;
            b_x = a_x;
            b_p = a_p;
            a = c;
            a_x = c_x;
            a_p = c_p;
        }

        if (b != 1)
        {
            cerr << "Inverse impossible Mod(" << _element << ", " << MODULO << ") -> gcd = " << b << endl; 
            exit (1);
        }
        _element=b_x;
        modulo();
        return *this;
    }

    template <typename baseType>
    void
    ElementPrime<baseType>::printElementPrime (std::ostream & stream) const
    {
        stream << _element;
    }
            
    template <typename baseType>
    bool
    ElementPrime<baseType>::isZero() const
    {
        return _element==0;
    }
    
    template <typename baseType>
    bool
    ElementPrime<baseType>::isOne() const
    {
        if(_element<0)
        {
            return (_element+MODULO)==1;
        }
        else
        {
            return _element==1;
        }
    }
    
    template <typename baseType>
    void 
    ElementPrime<baseType>::setZero()
    {
        _element=0;
    }
    
    template <typename baseType>
    void 
    ElementPrime<baseType>::setOne()
    {
        _element=1;
    }
    
    
    /* Operator overload */
            
    template <typename baseType>
    ElementPrime<baseType> & 
    ElementPrime<baseType>::operator=(baseType element)
    {
        _element=element;
        return * this;
    }
            
    template <typename baseType>
    ElementPrime<baseType> & 
    ElementPrime<baseType>::operator*=(ElementPrime<baseType> const & mult)
    {
        assert((mult._element>=-MODULO/2) && (mult._element<=MODULO/2));
        _element%=MODULO;
        _element*=mult._element;
        modulo();
        return * this;
    }
    
    template <>
    ElementPrime<double> & 
    ElementPrime<double>::operator*=(ElementPrime<double> const & mult)
    {
        assert((mult._element>=-MODULO/2) && (mult._element<=MODULO/2));
        _element=fmod(_element,MODULO);
        _element*=mult._element;
        modulo();
        return * this;
    }
    
    template <typename baseType>
    ostream & 
    operator<<(ostream & stream, ElementPrime<baseType> const & element)
    {
        element.printElementPrime(stream);
        return stream;
    }
    
    template <typename baseType>
    ElementPrime<baseType> 
    operator * (ElementPrime<baseType> const & element1, ElementPrime<baseType> const & element2)
    {
        ElementPrime<baseType> copy;
        copy._element=element1._element;
        return (copy*=element2);
    }
    
    template <typename baseType>
    ElementPrime<baseType> 
    operator - (ElementPrime<baseType> const & element)
    {
        ElementPrime<baseType> copy;
        copy._element=-element._element;
        return copy;
    }

}

#endif // F4_ELEMENT_PRIME_INL
