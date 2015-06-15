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
  * \file element-givaro.inl
  * \brief Definition of ElementGivaro methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_ELEMENT_GIVARO_INL
#define F4_ELEMENT_GIVARO_INL

using namespace std;

namespace F4
{
    /* Global variables */
    
    extern int VERBOSE;
    
    
    /* Static variables */
    
    template <class Field>
    Field ElementGivaro<Field>::F;
    
    template <class Field>
    string ElementGivaro<Field>::VARIABLE_NAME=string("t");
    
    
    /* Static methods */
    
    template <class Field>
    void 
    ElementGivaro<Field>::setVariableName(string var)
    {
        VARIABLE_NAME=var;
    }
    
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
    ElementGivaro<Field>::printElementGivaro (std::ostream & stream) const
    {
        F.write(stream,_element);
    }
    
    template <>
    void
    ElementGivaro<Givaro::GFqDom<long>>::printElementGivaro (std::ostream & stream) const
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
    
    /* For Integer (gmp) */
    template <class Field>
    ElementGivaro<Field> & 
    ElementGivaro<Field>::operator=(string element)
    {
        _element=F.init(_element,Givaro::Integer(element.c_str()));
        return * this;
    }
    
    /* For Givaro GFq */
    template <>
    ElementGivaro<Givaro::GFqDom<long>> & 
    ElementGivaro<Givaro::GFqDom<long>>::operator=(string element)
    {
        typedef Givaro::GFqDom<long> Field; 
        typedef Givaro::Poly1FactorDom<Field, Givaro::Dense> Polynomials; 
        Field Zp(F.characteristic(),1 );
        Polynomials PZp(Zp, Givaro::Indeter(VARIABLE_NAME));
        Polynomials::Element P; 
        Field::Element e; 
        bool firstTerm = true;
        bool neg = false;
        
        //cout << "Element Givaro gfq: " << element << endl; 
        
        /* Remove spaces */
        element.erase(remove_if(element.begin(), element.end(), [](char x){return isspace(x);}), element.end());
        _element=0;
        string tmp;
        int64_t coeff=0;
        int deg;
        size_t pos1=0;
        size_t pos2=0;
        size_t pos3=0;
        while(pos2 != string::npos)
        {
            if(element[pos1]=='-')
            {
                neg = true;
                pos1++;
            }
            pos2= min(element.find('+', pos1), element.find('-', pos1));
            tmp=element.substr(pos1, (pos2-pos1));
            
            if(tmp.find(VARIABLE_NAME)==string::npos)
            {
                /* Constant */
                if(neg)
                {
                    coeff=-stol(tmp);
                }
                else
                {
                    coeff=stol(tmp);
                }
                if(firstTerm)
                {
                    //cout << "First term: coeff = " << coeff << ", degree = " << 0 << endl;
                    PZp.init(P, Givaro::Degree(0), coeff);
                    firstTerm=false;
                }
                else
                {
                    //cout << "Term: coeff = " << coeff << ", degree = " << 0 << endl;
                    PZp.addin(P, Zp.init(e,coeff));
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
                        if(firstTerm)
                        {
                            //cout << "First term: coeff = " << 1 << ", degree = " << 1 << endl;
                            PZp.init(P, Givaro::Degree(1), 1);
                            firstTerm=false;
                        }
                        else
                        {
                            //cout << "Term: coeff = " << 1 << ", degree = " << 1 << endl;
                            Zp.assign(P[1], Zp.init(e,1));
                        }
                    }
                    else
                    {
                        if(neg)
                        {
                            coeff=-stol(tmp);
                        }
                        else
                        {
                            coeff=stol(tmp);
                        }
                        if(firstTerm)
                        {
                            //cout << "First term: coeff = " << coeff << ", degree = " << 1 << endl;
                            PZp.init(P, Givaro::Degree(1), coeff);
                            firstTerm=false;
                        }
                        else
                        {
                            //cout << "Term: coeff = " << coeff << ", degree = " << 1 << endl;
                            Zp.assign(P[1], Zp.init(e,coeff));
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
                        if(firstTerm)
                        {
                            //cout << "First term: coeff = " << 1 << ", degree = " << deg << endl;
                            PZp.init(P, Givaro::Degree(deg), 1);
                            firstTerm=false;
                        }
                        else
                        {
                            //cout << "Term: coeff = " << 1 << ", degree = " << deg << endl;
                            Zp.assign(P[deg], Zp.init(e,1));
                        }
                    }
                    else
                    {
                        /* Skip t^ */
                        tmp=tmp.substr(0, pos3-1);
                        if(neg)
                        {
                            coeff=-stol(tmp);
                        }
                        else
                        {
                            coeff=stol(tmp);
                        }
                        if(firstTerm)
                        {
                            //cout << "First term: coeff = " << coeff << ", degree = " << deg << endl;
                            PZp.init(P, Givaro::Degree(deg), coeff);
                            firstTerm=false;
                        }
                        else
                        {
                            //cout << "Term: coeff = " << coeff << ", degree = " << deg << endl;
                            Zp.assign(P[deg], Zp.init(e,coeff));
                        }
                    }
                }
            }
            /* We skip + or - */
            pos1=pos2+1;
            neg = false;
        }
        
        //cout << "Polynomial: " << P << endl;
        
        F.init(_element ,P);
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
        element.printElementGivaro(stream);
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

#endif // F4_ELEMENT_GIVARO_INL
