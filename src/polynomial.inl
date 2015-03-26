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
    Polynomial<Element>::Polynomial():_nbTerm(0)
    {
    }
    
    template <typename Element>
    Polynomial<Element>::Polynomial(string const s):_nbTerm(0)
    {
        typename forward_list<Term<Element>>::const_iterator it=_polynomial.before_begin();
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
                it=_polynomial.insert_after(it, term);
                _nbTerm++;
            }
        }
    }
    
    template <typename Element>
    Polynomial<Element>::Polynomial(Polynomial const & polynomial): _polynomial(polynomial._polynomial), _nbTerm(polynomial._nbTerm)
    {
    }
    
    template <typename Element>
    Polynomial<Element>::Polynomial(Polynomial && polynomial): _polynomial(polynomial._polynomial), _nbTerm(polynomial._nbTerm)
    {
    }
    
    
    /* Destructor */
    
    template <typename Element>
    Polynomial<Element>::~Polynomial()
    {
    }
    
    /* Miscellaneous */
    
    template <typename Element>
    void
    Polynomial<Element>::printPolynomial (ostream & stream) const
    {
        if(!_polynomial.empty())
        {
            typename forward_list<Term<Element>>::const_iterator it, it_tmp;
            for (it = _polynomial.begin(); it != _polynomial.end(); ++it)
            {
                it_tmp=it;
                ++it_tmp;
                if(it_tmp !=_polynomial.end())
                {
                    stream << "(" << *it << ") + ";
                }
                else
                {
                    stream << "(" << *it << ")";
                }
            }
        }
    }
    
    template <typename Element>
    int 
    Polynomial<Element>::getNbTerm() const
    {
        return _nbTerm;
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
        typename forward_list<Term<Element>>::const_iterator it;
        for (it = _polynomial.begin(); it != _polynomial.end(); ++it)
        {
            if((*it).getNumMonomial() == numMon)
            {
                return ((*it).getCoefficient());
            }
        }
        return 0;
    }
    
    template <typename Element>
    typename forward_list<Term<Element>>::const_iterator 
    Polynomial<Element>::getPolynomialBegin() const
    {
        return _polynomial.begin();
    }
    
    template <typename Element>
    typename forward_list<Term<Element>>::const_iterator 
    Polynomial<Element>::getPolynomialBeforeBegin() const
    {
        return _polynomial.before_begin();
    }
    
    template <typename Element>
    typename forward_list<Term<Element>>::const_iterator 
    Polynomial<Element>::getPolynomialEnd() const
    {
        return _polynomial.end();
    }
    
    template <typename Element>
    void
    Polynomial<Element>::deleteLT()
    {
        if(!_polynomial.empty())
        {
            _polynomial.pop_front();
        }
    }
    
    template <typename Element>
    void
    Polynomial<Element>::reset()
    {
        _polynomial.clear();
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
            
            typename forward_list<Term<Element>>::iterator it;
            it= _polynomial.begin();
            
            /* Modify the leading coefficient */
            (*it).setCoefficient(1);
            ++it;
            for (; it != _polynomial.end(); ++it)
            {
                /* Modify the other coefficients */
                (*it)*=invCoef;
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
    typename forward_list<Term<Element>>::const_iterator 
    Polynomial<Element>::emplaceAfter(typename forward_list<Term<Element>>::const_iterator pos, Element coeff, int numMon)
    {
        return _polynomial.emplace_after(pos, coeff, numMon);
        _nbTerm++;
    }
    
    
    
    /* Operator overload */
    
    template <typename Element>
    Polynomial<Element> & 
    Polynomial<Element>::operator=(Polynomial const & polynomial)
    {
        _polynomial=polynomial._polynomial;
        _nbTerm=polynomial._nbTerm;
        return * this;
    }
    
    template <typename Element>
    Polynomial<Element> & 
    Polynomial<Element>::operator=(Polynomial && polynomial)
    {
        _polynomial=polynomial._polynomial;
        _nbTerm=polynomial._nbTerm;
        polynomial._nbTerm=0;
        return * this;
    }
    
    template <typename Element>
    Polynomial<Element> & 
    Polynomial<Element>::operator*=(Monomial const & monomial)
    {
        int numMon=monomial.monomialToInt();
        typename forward_list<Term<Element>>::iterator it;
        for (it = _polynomial.begin(); it != _polynomial.end(); ++it)
        {
            (*it).multNumMon(numMon);
        }
        return *this;
    }
    
    template <typename Element>
    Polynomial<Element> & 
    Polynomial<Element>::operator*=(Element element)
    {
        typename forward_list<Term<Element>>::iterator it;
        for (it = _polynomial.begin(); it != _polynomial.end(); ++it)
        {
            (*it)*=element;
        }
        return *this;
    }
            
    template <typename Element>
    Polynomial<Element> & 
    Polynomial<Element>::operator*=(Term<Element> const & term)
    {
        typename forward_list<Term<Element>>::iterator it;
        for (it = _polynomial.begin(); it != _polynomial.end(); ++it)
        {
            (*it)*=term;
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
        polynomial.printPolynomial();
        return stream;
    }
}

#endif // F4_POLYNOMIAL_INL
