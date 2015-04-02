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
  * \file polynomial.inl
  * \brief Definition of Polynomial methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_POLYNOMIAL_INL
#define F4_POLYNOMIAL_INL

using namespace std;

namespace F4
{
    /* Constructor */
    
    template <typename Element>
    Polynomial<Element>::Polynomial()
    {
    }
    
    template <typename Element>
    Polynomial<Element>::Polynomial(string const s)
    {
        NodeList<Element> * it=_polynomial.getBegin();
        string tmp;
        size_t pos1=0;
        size_t pos2=0;
        while(pos2 != string::npos)
        {
            Term<Element> term;
            pos2= min(s.find('+', pos1), s.find('-', pos1));
            tmp=s.substr(pos1, (pos2-pos1));
            
            if(pos1!=0 && (s[pos1-1]=='+' || s[pos1-1]=='-'))
            {
                /* Add sign */
                tmp=s[pos1-1]+tmp;
            }
            /* We skip + or - */
            pos1=pos2+1; 
            if(tmp != "")
            {
                /* In case the first character is a sign */
                term.setTerm(tmp);
                it=_polynomial.insertAfter(it, term);
            }
        }
    }
    
    template <typename Element>
    Polynomial<Element>::Polynomial(Polynomial const & polynomial): _polynomial(polynomial._polynomial)
    {
    }
    
    template <typename Element>
    Polynomial<Element>::Polynomial(Polynomial && polynomial): _polynomial(polynomial._polynomial)
    {
    }
    
    
    /* Destructor */
    
    template <typename Element>
    Polynomial<Element>::~Polynomial()
    {
    }
    
    template <typename Element>
    void
    Polynomial<Element>::clear()
    {
        _polynomial.clear();
    }
    
    template<typename Element>
    void
    Polynomial<Element>::deleteAfter(NodeList<Element> * it)
    {
        _polynomial.deleteAfter(it);
    }
    
    /* Miscellaneous */
    
    template <typename Element>
    void
    Polynomial<Element>::printPolynomial (ostream & stream) const
    {
        if(!_polynomial.empty())
        {
            NodeList<Element> * it;
            it=_polynomial.getBegin();
            while(it->_next)
            {
                stream << "(" << it->_term << ") + ";
                it=it->_next;
            }
            stream << "(" << it->_term << ")";
        }
    }
    
    template <typename Element>
    int 
    Polynomial<Element>::getNbTerm() const
    {
        return _polynomial.getNbTerms();
    }
    
    template <typename Element>
    const Term<Element> & 
    Polynomial<Element>::getLT() const
    {
        assert(!_polynomial.empty());
        return _polynomial.front();
    }
    
    template <typename Element>
    int
    Polynomial<Element>::getLM() const
    {
        assert(!_polynomial.empty());
        return _polynomial.front().getNumMonomial();
    }
    
    template <typename Element>
    Element 
    Polynomial<Element>::getLC() const
    {
        assert(!_polynomial.empty());
        return _polynomial.front().getCoefficient();
    }
    
    
    template <typename Element>
    Element
    Polynomial<Element>::getCoefficient(int numMon) const
    {
        NodeList<Element> * it = _polynomial.getBegin();
        while(it)
        {
            if((it->_term).getNumMonomial() == numMon)
            {
                return ((it->_term).getCoefficient());
            }
            it=it->_next;
        }
        return 0;
    }
    
    template <typename Element>
    NodeList<Element> * 
    Polynomial<Element>::getPolynomialBegin()
    {
        return _polynomial.getBegin();
    }
    
    template <typename Element>
    NodeList<Element> * 
    Polynomial<Element>::getPolynomialBeforeBegin()
    {
        return _polynomial.getBeforeBegin();
    }
    
    template <typename Element>
    NodeList<Element> const * 
    Polynomial<Element>::getPolynomialBeginConst() const
    {
        return _polynomial.getBegin();
    }
    
    template <typename Element>
    void
    Polynomial<Element>::deleteLT()
    {
        if(!_polynomial.empty())
        {
            _polynomial.popFront();
        }
    }
    
    template <typename Element>
    void
    Polynomial<Element>::normalize()
    {
        Element lc=getLC();
        if (lc.isZero())
        {
            cout << "Polynomial::Normalize: problem with Normalize : lc = 0 " << endl;
        }
        if (!lc.isOne())
        {
            Element invCoef;
            invCoef = lc.inverse();
            NodeList<Element> * it = _polynomial.getBegin();
            
            /* Modify the leading coefficient */
            it->setCoefficient(1);
            it=it->_next;
            while(it)
            {
                /* Modify the other coefficients */
                it->setCoefficient(it->getCoefficient()*invCoef);
                it=it->_next;
            }
        }
    }
    
    template <typename Element>
    bool 
    Polynomial<Element>::isEmpty()
    {
        return _polynomial.empty();
    }
    
    template <typename Element>
    NodeList<Element> *
    Polynomial<Element>::emplaceAfter(NodeList<Element> * pos, Element coeff, int numMon)
    {
        return _polynomial.emplaceAfter(pos, coeff, numMon);
    }
    
    template <typename Element>
    NodeList<Element> *
    Polynomial<Element>::emplaceOn(NodeList<Element> * pos, Element coeff, int numMon)
    {
        return _polynomial.emplaceOn(pos, coeff, numMon);
    }
    
    
    
    /* Operator overload */
    
    template <typename Element>
    Polynomial<Element> & 
    Polynomial<Element>::operator=(Polynomial const & polynomial)
    {
        _polynomial=polynomial._polynomial;
        return * this;
    }
    
    template <typename Element>
    Polynomial<Element> & 
    Polynomial<Element>::operator=(Polynomial && polynomial)
    {
        if(*this != polynomial)
        {
            _polynomial=polynomial._polynomial;
        }
        return * this;
    }
    
    template <typename Element>
    Polynomial<Element> & 
    Polynomial<Element>::operator*=(Monomial const & monomial)
    {
        int numMon=monomial.monomialToInt();
        NodeList<Element> * it=_polynomial.getBegin();
        while(it)
        {
            (it->_term).multNumMon(numMon);
            it=it->_next;
        }
        return *this;
    }
    
    template <typename Element>
    Polynomial<Element> & 
    Polynomial<Element>::operator*=(Element element)
    {
        NodeList<Element> * it=_polynomial.getBegin();
        while(it)
        {
            (it->_term)*=element;
            it=it->_next;
        }
        return *this;
    }
            
    template <typename Element>
    Polynomial<Element> & 
    Polynomial<Element>::operator*=(Term<Element> const & term)
    {
        NodeList<Element> * it=_polynomial.getBegin();
        while(it)
        {
            (it->_term)*=term;
            it=it->_next;
        }
        return *this;
    }
    
    template <typename Element>
    Polynomial<Element> 
    operator * (Monomial const & monomial, Polynomial<Element> const & polynomial)
    {
        Polynomial<Element> copy(polynomial);
        return copy*=monomial;
    }
    
    template <typename Element>
    Polynomial<Element> 
    operator * (Polynomial<Element> const & polynomial, Monomial const & monomial)
    {
        Polynomial<Element> copy(polynomial);
        return copy*=monomial;
    }

    template <typename Element>
    Polynomial<Element> 
    operator * (Element element, Polynomial<Element> const & polynomial)
    {
        Polynomial<Element> copy(polynomial);
        return copy*=element;
    }
    
    template <typename Element>
    Polynomial<Element> 
    operator * (Polynomial<Element> const & polynomial, Element element)
    {
        Polynomial<Element> copy(polynomial);
        return copy*=element;
    }

    template <typename Element>
    Polynomial<Element> 
    operator * (Term<Element> const & term, Polynomial<Element> const & polynomial)
    {
        Polynomial<Element> copy(polynomial);
        return copy*=term;
    }
    
    template <typename Element>
    Polynomial<Element> 
    operator * (Polynomial<Element> const & polynomial, Term<Element> const & term)
    {
        Polynomial<Element> copy(polynomial);
        return copy*=term;
    }
    
    template <typename Element>
    ostream & operator<<(ostream & stream, Polynomial<Element> const & polynomial)
    {
        polynomial.printPolynomial(stream);
        return stream;
    }
}

#endif // F4_POLYNOMIAL_INL
