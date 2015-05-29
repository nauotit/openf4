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
  * \file element-gf2-extension.inl
  * \brief Definition of ElementGF2Extension methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_ELEMENT_GF2_EXTENSION_INL
#define F4_ELEMENT_GF2_EXTENSION_INL

using namespace std;

namespace F4
{
    /* Global variables */
    
    extern int VERBOSE;
    
    
    /* Static variables */
    
    template <typename baseType>
    baseType ElementGF2Extension<baseType>::MODULO=0;
    
    template <typename baseType>
    baseType ElementGF2Extension<baseType>::MASK=0;
    
    template <typename baseType>
    baseType ElementGF2Extension<baseType>::MASK_BIT=0;
    
    template <typename baseType>
    string ElementGF2Extension<baseType>::VARIABLE_NAME=string("t");
    
    
    /* Static methods */
    
    template <typename baseType>
    void 
    ElementGF2Extension<baseType>::setVariableName(string var)
    {
        VARIABLE_NAME=var;
    }
    
    template <typename baseType>
    void 
    ElementGF2Extension<baseType>::setModulo(baseType modulo)
    {
        MODULO=modulo;
        /* Bit of MASK */
        for(int j = sizeof(baseType)*8-1; j > 0; j--)
        {
            if(MODULO & ((baseType)1 << j))
            {
                /* pow = degree extension */
                MASK_BIT=j;
                break;
            }
        }
        /* Maximum power of 2 lower than MODULO */
        MASK=(baseType)1 << MASK_BIT;
    }
    
    template <typename baseType>
    void 
    ElementGF2Extension<baseType>::setModulo(string modulo)
    {
        /* Remove spaces */
        modulo.erase(remove_if(modulo.begin(), modulo.end(), [](char x){return isspace(x);}), modulo.end());
        MODULO=0;
        string tmp;
        int coeff=0;
        int deg;
        size_t pos1=0;
        size_t pos2=0;
        size_t pos3=0;
        while(pos2 != string::npos)
        {
            pos2= min(modulo.find('+', pos1), modulo.find('-', pos1));
            tmp=modulo.substr(pos1, (pos2-pos1));
            
            if(tmp.find(VARIABLE_NAME)==string::npos)
            {
                /* Constant */
                coeff=stoi(tmp);
                coeff%=2;
                if(coeff==1)
                {
                    MODULO^=0x1;
                }
            }
            else
            {
                /* Not constant */
                if((pos3=tmp.find('^'))==string::npos)
                {
                    /* Power = 1 */
                    if(tmp==VARIABLE_NAME)
                    {
                        /* Implicit coeff = 1 */
                        MODULO^=((baseType)1<<1);
                    }
                    else
                    {
                        coeff=stoi(tmp);
                        coeff%=2;
                        if(coeff==1)
                        {
                            MODULO^=((baseType)1<<1);
                        }
                    }
                }
                else
                {
                    /* Power != 1 */
                    deg=stoi(tmp.substr(pos3+1));
                    
                    /* Skip ^ */
                    tmp=tmp.substr(0, pos3);
                    if(tmp==VARIABLE_NAME)
                    {
                        /* Implicit coeff = 1 */
                        MODULO^=((baseType)1<<deg);
                    }
                    else
                    {
                        /* Skip t^ */
                        tmp=tmp.substr(0, pos3-1);
                        coeff=stoi(tmp);
                        coeff%=2;
                        if(coeff==1)
                        {
                            MODULO^=((baseType)1<<deg);
                        }
                    }
                }
            }
            /* We skip + or - */
            pos1=pos2+1; 
        }
        /* Bit of MASK */
        for(int j = sizeof(baseType)*8-1; j > 0; j--)
        {
            if(MODULO & ((baseType)1 << j))
            {
                /* pow = degree extension */
                MASK_BIT=j;
                break;
            }
        }
        /* Maximum power of 2 lower than MODULO */
        MASK=(baseType)1 << MASK_BIT;
        
        //cout << "Modulo: " << MODULO << ", MASK_BIT: " << MASK_BIT << ", MASK: " << MASK << endl;
    }
    
    template <typename baseType>
    baseType 
    ElementGF2Extension<baseType>::getModulo()
    {
        return MODULO;
    }
    
    template <typename baseType>
    baseType 
    ElementGF2Extension<baseType>::getMask()
    {
        return MASK;
    }
    
    template <typename baseType>
    baseType 
    ElementGF2Extension<baseType>::getMaskBit()
    {
        return MASK_BIT;
    }
    
    
    /* Miscellaneous */
    
    
    template <typename baseType>
    inline baseType
    ElementGF2Extension<baseType>::modulo ()
    {        
        int i = sizeof(baseType)*8-1;
        while(_element >= MASK && i >= 0)
        {
            if(_element & ((baseType)1 << i))
            {
                _element ^= (MODULO << (i-MASK_BIT));
            }
            i--;
        }
        return _element;
    }
    
    template <typename baseType>
    inline baseType
    ElementGF2Extension<baseType>::getElement () const
    {
        return _element;
    }
    
    template <typename baseType>
    ElementGF2Extension<baseType> &
    ElementGF2Extension<baseType>::addMult(ElementGF2Extension<baseType> const & element, ElementGF2Extension<baseType> const & mult)
    {
        addMultBase4(element, mult);
        return * this;
    }
    
    /* amul = [0, a, 2a, 4a, 8a, ..., (2^31)a] */
    template <typename baseType>
    ElementGF2Extension<baseType> & 
    ElementGF2Extension<baseType>::addMultBase2(ElementGF2Extension<baseType> const & element, ElementGF2Extension<baseType> const & mult)
    {
        static baseType a=0;
        static baseType amul[sizeof(baseType)*8]={0};
        if(mult.getElement()!=a)
        {
            a=mult.getElement();
            amul[1]=a;
            for(size_t i=2; i<sizeof(baseType)*8; i++)
            {
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                amul[i]=a;
            }
            
            baseType tmp=element.getElement();
            for(size_t i=1; i<sizeof(baseType)*8; i++)
            {
                _element^=amul[i * (tmp & 0x1)];
                tmp >>= 1;
            }
        }
        return * this;
    }
    
    /* For 32 bits integer amul = 
     * [0,       a,       2a,           3a] 
     * [0,      4a,       8a,          12a]
     * ...
     * [0, (4^15)a, 2(4^15)a, (4^16-4^15)a]
     */
    template <typename baseType>
    ElementGF2Extension<baseType> & 
    ElementGF2Extension<baseType>::addMultBase4(ElementGF2Extension<baseType> const & element, ElementGF2Extension<baseType> const & mult)
    {
        static baseType a=0;
        static baseType amul[sizeof(baseType)*16]={0};
        if(mult.getElement()!=a)
        {
            a=mult.getElement();
            for(size_t i=0; i<sizeof(baseType)*4; i++)
            {
                amul[4*i]=0;
                amul[4*i+1]=a;
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                for(int j=0; j<2; j++)
                {
                    amul[4*i+j+2]=a^amul[4*i+j];
                }
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
            }
            
            baseType tmp=element.getElement();
            for(size_t i=0; i<sizeof(baseType)*4; i++)
            {
                _element^=amul[4*i + (tmp & 0x3)];
                tmp >>= 2;
            }
        }
        return * this;
    }
    
    /* For 32 bits integer amul = 
     * [0,        a,        2a,           3a, ...,          15a] 
     * [0,      16a,       32a,          48a, ...,         240a]
     * ...
     * [0,  (16^7)a,  2(16^7)a,     3(16^7)a, ..., (16^8-16^7)a]
     */
    template <typename baseType>
    ElementGF2Extension<baseType> & 
    ElementGF2Extension<baseType>::addMultBase16(ElementGF2Extension<baseType> const & element, ElementGF2Extension<baseType> const & mult)
    {
        static baseType a=0;
        static baseType amul[sizeof(baseType)*32]={0};
        if(mult.getElement()!=a)
        {
            a=mult.getElement();
            for(size_t i=0; i<sizeof(baseType)*2; i++)
            {
                amul[16*i]=0;
                amul[16*i+1]=a;
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                for(int j=0; j<2; j++)
                {
                    amul[16*i+j+2]=a^amul[16*i+j];
                }
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                for(int j=0; j<4; j++)
                {
                    amul[16*i+j+4]=a^amul[16*i+j];
                }
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                for(int j=0; j<8; j++)
                {
                    amul[16*i+j+8]=a^amul[16*i+j];
                }
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
            }
            
            baseType tmp=element.getElement();
            for(size_t i=0; i<sizeof(baseType)*2; i++)
            {
                _element^=amul[16*i + (tmp & 0xf)];
                tmp >>= 4;
            }
        }
        return * this;
    }
    
    
    /* For 32 bits integer amul = 
     * [0,        a,        2a,           3a, ...,           255a] 
     * [0,      16a,       32a,          48a, ...,           240a]
     * ...
     * [0, (256^3)a, 2(256^3)a,    3(256^3)a, ..., (256^4-256^3)a]
     */
    template <typename baseType>
    ElementGF2Extension<baseType> & 
    ElementGF2Extension<baseType>::addMultBase256(ElementGF2Extension<baseType> const & element, ElementGF2Extension<baseType> const & mult)
    {
        static baseType a=0;
        static baseType amul[sizeof(baseType)*256]={0};
        if(mult.getElement()!=a)
        {
            a=mult.getElement();
            for(size_t i=0; i<sizeof(baseType); i++)
            {
                amul[256*i]=0;
                amul[256*i+1]=a;
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                for(int j=0; j<2; j++)
                {
                    amul[256*i+j+2]=a^amul[256*i+j];
                }
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                for(int j=0; j<4; j++)
                {
                    amul[256*i+j+4]=a^amul[256*i+j];
                }
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                for(int j=0; j<8; j++)
                {
                    amul[256*i+j+8]=a^amul[256*i+j];
                }
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                for(int j=0; j<16; j++)
                {
                    amul[256*i+j+16]=a^amul[256*i+j];
                }
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                for(int j=0; j<32; j++)
                {
                    amul[256*i+j+32]=a^amul[256*i+j];
                }
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                for(int j=0; j<64; j++)
                {
                    amul[256*i+j+64]=a^amul[256*i+j];
                }
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                for(int j=0; j<128; j++)
                {
                    amul[256*i+j+128]=a^amul[256*i+j];
                }
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
            }
            
            baseType tmp=element.getElement();
            for(size_t i=0; i<sizeof(baseType); i++)
            {
                _element^=amul[256*i + (tmp & 0xff)];
                tmp >>= 8;
            }
        }
        return * this;
    }
    
    template <typename baseType>
    ElementGF2Extension<baseType> &
    ElementGF2Extension<baseType>::inverse ()
    {
        if (_element==0)
        {
            cout << "Division by zero !" << endl;
            exit(-1);
        }
        baseType a,b,ca,cb,sh_a,sh_ca,tmp;
        ca = (baseType)1;
        cb = (baseType)0;
        
        a = _element;
        b = MODULO;
        
        while (a) 
        {
            while (b>=a) 
            {
                sh_a=a;
                sh_ca=ca;
                while ((b^sh_a)>(sh_a)) 
                {
                    sh_a<<=1;
                    sh_ca<<=1;
                }
                b^=sh_a;
                cb^=sh_ca;
            }
            tmp=a;a=b;b=tmp;
            tmp=ca;ca=cb;cb=tmp;
        }
        _element=cb;
        return *this;
    }

    template <typename baseType>
    void
    ElementGF2Extension<baseType>::printElementGF2Extension (std::ostream & stream) const
    {
        stream << "(";
        int i=sizeof(baseType)*8-1;
        /* Print higher term */
        while(i>1)
        {
            if(_element & ((baseType)1<<i))
            {
                stream << VARIABLE_NAME << "^" << i;
                i--;
                break;
            }
            i--;
        }
        /* Print other terms with pow > 1 */
        while(i>1)
        {
            if(_element & ((baseType)1<<i))
            {
                stream << "+" << VARIABLE_NAME << "^" << i;
            }
            i--;
        }
        /* Print other terms with pow = 1 */
        if(_element & (1<<1))
        {
            stream << "+" << VARIABLE_NAME;
        }
        /* Print other terms with pow = 1 */
        if(_element & 0x1)
        {
            stream << "+" << "1";
        }
        stream << ")";
    }
            
    template <typename baseType>
    bool
    ElementGF2Extension<baseType>::isZero() const
    {
        return _element==0;
    }
    
    template <typename baseType>
    bool
    ElementGF2Extension<baseType>::isOne() const
    {
        return _element==1;
    }
    
    template <typename baseType>
    void 
    ElementGF2Extension<baseType>::setZero()
    {
        _element=(baseType)0;
    }
    
    template <typename baseType>
    void 
    ElementGF2Extension<baseType>::setOne()
    {
        _element=(baseType)1;
    }
    
    
    /* Operator overload */
            
    template <typename baseType>
    ElementGF2Extension<baseType> & 
    ElementGF2Extension<baseType>::operator=(baseType const element)
    {
        _element=element;
        return * this;
    }
    
    template <typename baseType>
    ElementGF2Extension<baseType> & 
    ElementGF2Extension<baseType>::operator=(string element)
    {
        /* Remove spaces */
        element.erase(remove_if(element.begin(), element.end(), [](char x){return isspace(x);}), element.end());
        _element=0;
        string tmp;
        int coeff=0;
        int deg;
        size_t pos1=0;
        size_t pos2=0;
        size_t pos3=0;
        while(pos2 != string::npos)
        {
            pos2= min(element.find('+', pos1), element.find('-', pos1));
            tmp=element.substr(pos1, (pos2-pos1));
            
            if(tmp.find(VARIABLE_NAME)==string::npos)
            {
                /* Constant */
                coeff=stoi(tmp);
                coeff%=2;
                if(coeff==1)
                {
                    _element^=0x1;
                }
            }
            else
            {
                /* Not constant */
                if((pos3=tmp.find('^'))==string::npos)
                {
                    /* Power = 1 */
                    if(tmp==VARIABLE_NAME)
                    {
                        /* Implicit coeff = 1 */
                        _element^=(1<<1);
                    }
                    else
                    {
                        coeff=stoi(tmp);
                        coeff%=2;
                        if(coeff==1)
                        {
                            _element^=(1<<1);
                        }
                    }
                }
                else
                {
                    /* Power != 1 */
                    deg=stoi(tmp.substr(pos3+1));
                    
                    /* Skip ^ */
                    tmp=tmp.substr(0, pos3);
                    if(tmp==VARIABLE_NAME)
                    {
                        /* Implicit coeff = 1 */
                        _element^=(1<<deg);
                    }
                    else
                    {
                        /* Skip t^ */
                        tmp=tmp.substr(0, pos3-1);
                        coeff=stoi(tmp);
                        coeff%=2;
                        if(coeff==1)
                        {
                            _element^=(1<<deg);
                        }
                    }
                }
            }
            /* We skip + or - */
            pos1=pos2+1; 
        }
        modulo();
        
        return * this;
    }
    
    /* amul = [0, a, 2a, 4a, 8a, ..., (2^31)a] */
    template <typename baseType>
    ElementGF2Extension<baseType> & 
    ElementGF2Extension<baseType>::multBase2(ElementGF2Extension<baseType> const & mult)
    {
        static baseType a=0;
        static baseType amul[sizeof(baseType)*8]={0};
        if(mult.getElement()!=a)
        {
            a=mult.getElement();
            amul[1]=a;
            for(size_t i=2; i<sizeof(baseType)*8; i++)
            {
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                amul[i]=a;
            }
            
            baseType tmp=0;
            for(size_t i=1; i<sizeof(baseType)*8; i++)
            {
                tmp^=amul[i * (_element & 0x1)];
                _element >>= 1;
            }
            _element=tmp;
        }
        return * this;
    }
    
    /* For 32 bits integer amul = 
     * [0,       a,       2a,           3a] 
     * [0,      4a,       8a,          12a]
     * ...
     * [0, (4^15)a, 2(4^15)a, (4^16-4^15)a]
     */
    template <typename baseType>
    ElementGF2Extension<baseType> & 
    ElementGF2Extension<baseType>::multBase4(ElementGF2Extension<baseType> const & mult)
    {
        static baseType a=0;
        static baseType amul[sizeof(baseType)*16]={0};
        if(mult.getElement()!=a)
        {
            a=mult.getElement();
            for(size_t i=0; i<sizeof(baseType)*4; i++)
            {
                amul[4*i]=0;
                amul[4*i+1]=a;
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                for(int j=0; j<2; j++)
                {
                    amul[4*i+j+2]=a^amul[4*i+j];
                }
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
            }
            
            baseType tmp=0;
            for(size_t i=0; i<sizeof(baseType)*4; i++)
            {
                tmp^=amul[4*i + (_element & 0x3)];
                _element >>= 2;
            }
            _element=tmp;
        }
        return * this;
    }
    
    /* For 32 bits integer amul = 
     * [0,        a,        2a,           3a, ...,          15a] 
     * [0,      16a,       32a,          48a, ...,         240a]
     * ...
     * [0,  (16^7)a,  2(16^7)a,     3(16^7)a, ..., (16^8-16^7)a]
     */
    template <typename baseType>
    ElementGF2Extension<baseType> & 
    ElementGF2Extension<baseType>::multBase16(ElementGF2Extension<baseType> const & mult)
    {
        static baseType a=0;
        static baseType amul[sizeof(baseType)*32]={0};
        if(mult.getElement()!=a)
        {
            a=mult.getElement();
            for(size_t i=0; i<sizeof(baseType)*2; i++)
            {
                amul[16*i]=0;
                amul[16*i+1]=a;
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                for(int j=0; j<2; j++)
                {
                    amul[16*i+j+2]=a^amul[16*i+j];
                }
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                for(int j=0; j<4; j++)
                {
                    amul[16*i+j+4]=a^amul[16*i+j];
                }
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                for(int j=0; j<8; j++)
                {
                    amul[16*i+j+8]=a^amul[16*i+j];
                }
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
            }
            
            baseType tmp=0;
            for(size_t i=0; i<sizeof(baseType)*2; i++)
            {
                tmp^=amul[16*i + (_element & 0xf)];
                _element >>= 4;
            }
            _element=tmp;
        }
        return * this;
    }
    
    
    /* For 32 bits integer amul = 
     * [0,        a,        2a,           3a, ...,           255a] 
     * [0,      16a,       32a,          48a, ...,           240a]
     * ...
     * [0, (256^3)a, 2(256^3)a,    3(256^3)a, ..., (256^4-256^3)a]
     */
    template <typename baseType>
    ElementGF2Extension<baseType> & 
    ElementGF2Extension<baseType>::multBase256(ElementGF2Extension<baseType> const & mult)
    {
        static baseType a=0;
        static baseType amul[sizeof(baseType)*256]={0};
        if(mult.getElement()!=a)
        {
            a=mult.getElement();
            for(size_t i=0; i<sizeof(baseType); i++)
            {
                amul[256*i]=0;
                amul[256*i+1]=a;
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                for(int j=0; j<2; j++)
                {
                    amul[256*i+j+2]=a^amul[256*i+j];
                }
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                for(int j=0; j<4; j++)
                {
                    amul[256*i+j+4]=a^amul[256*i+j];
                }
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                for(int j=0; j<8; j++)
                {
                    amul[256*i+j+8]=a^amul[256*i+j];
                }
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                for(int j=0; j<16; j++)
                {
                    amul[256*i+j+16]=a^amul[256*i+j];
                }
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                for(int j=0; j<32; j++)
                {
                    amul[256*i+j+32]=a^amul[256*i+j];
                }
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                for(int j=0; j<64; j++)
                {
                    amul[256*i+j+64]=a^amul[256*i+j];
                }
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
                for(int j=0; j<128; j++)
                {
                    amul[256*i+j+128]=a^amul[256*i+j];
                }
                a <<= 1;
                if(a & MASK)
                {
                    a^=MODULO;
                }
            }
            
            baseType tmp=0;
            for(size_t i=0; i<sizeof(baseType); i++)
            {
                tmp^=amul[256*i + (_element & 0xff)];
                _element >>= 8;
            }
            _element=tmp;
        }
        return * this;
    }
            
    template <typename baseType>
    ElementGF2Extension<baseType> & 
    ElementGF2Extension<baseType>::operator*=(ElementGF2Extension<baseType> const & mult)
    {
        multBase4(mult);
        return * this;
    }
    
    template <typename baseType>
    ostream & 
    operator<<(ostream & stream, ElementGF2Extension<baseType> const & element)
    {
        element.printElementGF2Extension(stream);
        return stream;
    }
    
    template <typename baseType>
    ElementGF2Extension<baseType> 
    operator * (ElementGF2Extension<baseType> const & element1, ElementGF2Extension<baseType> const & element2)
    {
        ElementGF2Extension<baseType> copy;
        copy._element=element1._element;
        return (copy*=element2);
    }
    
    template <typename baseType>
    ElementGF2Extension<baseType> 
    operator - (ElementGF2Extension<baseType> const & element)
    {
        /* For genericity (- does nothing in characteristic 2) */
        ElementGF2Extension<baseType> copy;
        copy._element=element._element;
        return copy;
    }

}

#endif // F4_ELEMENT_GF2_EXTENSION_INL
