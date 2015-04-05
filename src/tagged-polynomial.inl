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
  * \file tagged-polynomial.inl
  * \brief Definition of TaggedPolynomial methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_TAGGED_POLYNOMIAL_INL
#define F4_TAGGED_POLYNOMIAL_INL

namespace F4
{
    /* Static variables */
    
    template <typename Element>
    MonomialArray * TaggedPolynomial<Element>::MONOMIAL_ARRAY=0;
    
    
    /* Static methods */
    
    template <typename Element>
    void
    TaggedPolynomial<Element>::setMonomialArray(MonomialArray * monomialArray)
    {
        MONOMIAL_ARRAY=monomialArray;
    }
    
    
    /* Constructor */
    
    template <typename Element>
    TaggedPolynomial<Element>::TaggedPolynomial()
    {
        int nbVars=Monomial::getNbVariable();
        _simplyrules=new int[nbVars];
        for(int i=0; i< nbVars; i++)
        {
            _simplyrules[i]=-1;
        }
    }
    
    template <typename Element>
    TaggedPolynomial<Element>::TaggedPolynomial(Polynomial<Element> const & polynomial):_polynomial(polynomial)
    {
        int nbVars=Monomial::getNbVariable();
        _simplyrules=new int[nbVars];
        for(int i=0; i< nbVars; i++)
        {
            _simplyrules[i]=-1;
        }
    }
    
    template <typename Element>
    TaggedPolynomial<Element>::TaggedPolynomial(TaggedPolynomial const & taggedPolynomial):_polynomial(taggedPolynomial._polynomial)
    {
        int nbVars=Monomial::getNbVariable();
        _simplyrules=new int[nbVars];
        for(int i=0; i< nbVars; i++)
        {
            _simplyrules[i]=taggedPolynomial._simplyrules[i];
        }
    }
    
    template <typename Element>
    TaggedPolynomial<Element>::TaggedPolynomial(TaggedPolynomial  && taggedPolynomial):_polynomial(taggedPolynomial._polynomial), _simplyrules(taggedPolynomial._simplyrules)
    {
        taggedPolynomial._simplyrules=0;
    }
    
    
    /* Destructor */
    
    template <typename Element>
    TaggedPolynomial<Element>::~TaggedPolynomial()
    {
        if(_simplyrules!=0)
        {
            delete[] _simplyrules;
            _simplyrules=0;
        }
    }
    
     
    /* Get / Set */
    
    template <typename Element>
    Polynomial<Element> const & 
    TaggedPolynomial<Element>::getPolynomialConst() const
    {
        return _polynomial;
    }
    
    template <typename Element>
    Polynomial<Element> & 
    TaggedPolynomial<Element>::getPolynomial()
    {
        return _polynomial;
    }
    
    template <typename Element>
    void  
    TaggedPolynomial<Element>::setPolynomial(Polynomial<Element> && polynomial)
    {
        _polynomial=polynomial;
    }
    
    template <typename Element>
    const Term<Element> & 
    TaggedPolynomial<Element>::getLT() const
    {
        return _polynomial.getLT();
    }
            
    template <typename Element>
    int 
    TaggedPolynomial<Element>::getLM() const
    {
        return _polynomial.getLM();
    }
            
    template <typename Element>
    Element 
    TaggedPolynomial<Element>::getLC() const
    {
        return _polynomial.getLC();
    }
    
    template <typename Element>
    int 
    TaggedPolynomial<Element>::getNbTerm() const
    {
        return _polynomial.getNbTerm();
    }
    
    template <typename Element>
    int 
    TaggedPolynomial<Element>::getSimplyrule(int index) const
    {
        assert(index < Monomial::getNbVariable());
        return _simplyrules[index];
    }
    
    template <typename Element>
    void 
    TaggedPolynomial<Element>::setSimplyrule(int index, int numPol)
    {
        assert(index < Monomial::getNbVariable());
        _simplyrules[index]=numPol;
    }
    
    template <typename Element>
    NodeList<Element> *
    TaggedPolynomial<Element>::getPolynomialBegin()
    {
        return _polynomial.getPolynomialBegin();
    }
    
    template <typename Element>
    NodeList<Element> const *
    TaggedPolynomial<Element>::getPolynomialBeginConst() const
    {
        return _polynomial.getPolynomialBeginConst();
    }
    
    
    /* Miscellaneous */
    
    template <typename Element>
    void 
    TaggedPolynomial<Element>::printTaggedPolynomial (std::ostream & stream) const
    {
        stream << "polynomial: ";
        _polynomial.printPolynomial(stream);
        stream << endl;
        stream << "Simplyrules: [";
        int * it;
        int * begin(_simplyrules);
        int * end(_simplyrules+ Monomial::getNbVariable());
        for (it = begin; it != end; ++it)
        {
            if((it+1) !=end)
            {
                stream << *it << ", ";
            }
            else
            {
                stream << *it;
            }
        }
        stream << "]";
    }
    
    template <typename Element>
    int 
    TaggedPolynomial<Element>::compareTaggedPolynomial (TaggedPolynomial const & taggedPolynomial) const
    {
        int cmp=Monomial::compareNumMonomial(_polynomial.getLM(), taggedPolynomial._polynomial.getLM());
        if (cmp == 0)
        {
            if(_polynomial.getNbTerm() - taggedPolynomial._polynomial.getNbTerm() > 0)
            {
                return -1;
            }
            else if (taggedPolynomial._polynomial.getNbTerm() - _polynomial.getNbTerm() > 0)
            {   
                return 1;
            }
        }
        return cmp;
    }
    
    template <typename Element>
    bool 
    TaggedPolynomial<Element>::isEmpty()
    {
        return _polynomial.isEmpty();
    }
    
    template <typename Element>
    void 
    TaggedPolynomial<Element>::resetSimplyrules()
    {
        for(int i=0; i< Monomial::getNbVariable(); i++)
        {
            _simplyrules[i]=-1;
        }
    }
    
    template <typename Element>
    void 
    TaggedPolynomial<Element>::setTaggedPolynomial(TaggedPolynomial const & taggedPolynomial, uint8_t const * varlist)
    {
        int numMon=Monomial::varlistToInt(varlist);
        
        NodeList<Element> * pos;
        NodeList<Element> const * start;
        pos=_polynomial.getPolynomialBegin();
        start=taggedPolynomial.getPolynomialBeginConst();
        while(start)
        {
            pos=_polynomial.emplaceAfter(pos, start->getCoefficient(), MONOMIAL_ARRAY->multNumMonomial(start->getNumMonomial(), numMon));
            start=start->_next;
        }
    }
    
    /* Operator overload */
    
    template <typename Element>
    TaggedPolynomial<Element> & 
    TaggedPolynomial<Element>::operator=(TaggedPolynomial const & taggedPolynomial)
    {
        _polynomial=taggedPolynomial._polynomial;
        for(int i=0; i< Monomial::getNbVariable(); i++)
        {
            _simplyrules[i]=taggedPolynomial._simplyrules[i];
        }
        return * this;
    }
    
    template <typename Element>
    TaggedPolynomial<Element> & 
    TaggedPolynomial<Element>::operator=(TaggedPolynomial  && taggedPolynomial)
    {
        if(this != &taggedPolynomial)
        {
            _polynomial=taggedPolynomial._polynomial;
            delete[] _simplyrules;
            _simplyrules=taggedPolynomial._simplyrules;
            taggedPolynomial._simplyrules=0;
        }
        return * this;
    }
    
    template <typename Element>
    TaggedPolynomial<Element> & 
    TaggedPolynomial<Element>::operator=(Polynomial<Element> const & polynomial)
    {
        _polynomial=polynomial;
        return * this;
    }
    
    template <typename Element>
    TaggedPolynomial<Element> & 
    TaggedPolynomial<Element>::operator=(Polynomial<Element>  && polynomial)
    {
        _polynomial=polynomial;
        return * this;
    }
    
    template <typename Element>
    TaggedPolynomial<Element> & 
    TaggedPolynomial<Element>::operator*=(Monomial const & monomial)
    {
        _polynomial*=monomial;
        return *this;
    }
    
    template <typename Element>
    TaggedPolynomial<Element> & 
    TaggedPolynomial<Element>::operator*=(Element element)
    {
        _polynomial*=element;
        return *this;
    }
            
    template <typename Element>
    TaggedPolynomial<Element> & 
    TaggedPolynomial<Element>::operator*=(Term<Element> const & term)
    {
        _polynomial*=term;
        return *this;
    }
    
    template <typename Element>
    ostream & operator<<(ostream & stream, TaggedPolynomial<Element> const & taggedPolynomial)
    {
        taggedPolynomial.printTaggedPolynomial(stream);
        return stream;
    }
    
    template <typename Element>
    bool operator==(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2)
    {
        return (taggedPolynomial1.compareTaggedPolynomial(taggedPolynomial2)==0);
    }
    
    template <typename Element>
    bool operator>(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2)
    {
        return (taggedPolynomial1.compareTaggedPolynomial(taggedPolynomial2)==1);
    }
    
    template <typename Element>
    bool operator>=(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2)
    {
        return (taggedPolynomial1.compareTaggedPolynomial(taggedPolynomial2)!=-1);
    }
    
    template <typename Element>
    bool operator<(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2)
    {
        return (taggedPolynomial1.compareTaggedPolynomial(taggedPolynomial2)==-1);
    }
    
    template <typename Element>
    bool operator<=(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2)
    {
        return (taggedPolynomial1.compareTaggedPolynomial(taggedPolynomial2)!=1);
    }
    
    template <typename Element>
    TaggedPolynomial<Element> operator * (Monomial const & monomial, TaggedPolynomial<Element> const & taggedPolynomial)
    {
        TaggedPolynomial<Element> copy(taggedPolynomial);
        return copy*=monomial;
    }
    
    template <typename Element>
    TaggedPolynomial<Element> operator * (TaggedPolynomial<Element> const & taggedPolynomial, Monomial const & monomial)
    {
        TaggedPolynomial<Element> copy(taggedPolynomial);
        return copy*=monomial;
    }

    template <typename Element>
    TaggedPolynomial<Element> operator * (Element element, TaggedPolynomial<Element> const & taggedPolynomial)
    {
        TaggedPolynomial<Element> copy(taggedPolynomial);
        return copy*=element;
    }
    
    template <typename Element>
    TaggedPolynomial<Element> operator * (TaggedPolynomial<Element> const & taggedPolynomial, Element element)
    {
        TaggedPolynomial<Element> copy(taggedPolynomial);
        return copy*=element;
    }

    template <typename Element>
    TaggedPolynomial<Element> operator * (Term<Element> const & term, TaggedPolynomial<Element> const & taggedPolynomial)
    {
        TaggedPolynomial<Element> copy(taggedPolynomial);
        return copy*=term;
    }
    
    template <typename Element>
    TaggedPolynomial<Element> operator * (TaggedPolynomial<Element> const & taggedPolynomial, Term<Element> const & term)
    {
        TaggedPolynomial<Element> copy(taggedPolynomial);
        return copy*=term;
    }
}

#endif // F4_TAGGED_POLYNOMIAL_INL
