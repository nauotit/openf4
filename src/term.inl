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
  * \file term.inl
  * \brief Definition of Term methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_TERM_INL
#define F4_TERM_INL

namespace F4
{
    /* Static variables */
    
    template <typename Element>
    MonomialArray * Term<Element>::MONOMIAL_ARRAY=0;
    
    
    /* Static methods */
    
    template <typename Element>
    void
    Term<Element>::setMonomialArray(MonomialArray * monomialArray)
    {
        MONOMIAL_ARRAY=monomialArray;
    }
    
    
    /* Constructor */ 
    
    template <typename Element>
    Term<Element>::Term(): _numMonomial(-1)
    {
        _coefficient=0;
    }
    
    template <typename Element>
    Term<Element>::Term(Element coeff, Monomial const & mon): _numMonomial(mon.monomialToInt())
    {
        _coefficient=coeff._element;
    }
    
    template <typename Element>
    Term<Element>::Term(Element coeff, int numMon): _numMonomial(numMon)
    {
        _coefficient=coeff._element;
    }
    
    template <typename Element>
    Term<Element>::Term(std::string const s)
    {
        /* Beware, a specialised readCoefficient method must be defined. */
        readCoefficient(s);
        Monomial mon;
        mon.allocate();
        mon.setMonomial(s);
        _numMonomial=mon.monomialToInt();
        mon.erase();
    }
    
    template <typename Element>
    Term<Element>::Term(Term const & toCopy): _numMonomial(toCopy._numMonomial)
    {
        _coefficient=toCopy._coefficient._element;
    }
    
    
    /* Destructor */
    
    template <typename Element>
    Term<Element>::~Term()
    {
    }
    
    
    /* Get / Set */
    
    template <typename Element>
    Element 
    Term<Element>::getCoefficient() const
    {
        return _coefficient;
    }
    
    template <typename Element>
    void 
    Term<Element>::setCoefficient(Element coeff)
    {
        _coefficient._element=coeff._element;
    }
    
    template <typename Element>
    void 
    Term<Element>::setCoefficientOne()
    {
        _coefficient._element=1;
    }
    
    template <typename Element>
    int 
    Term<Element>::getNumMonomial() const
    {
        return _numMonomial;
    }

    template <typename Element>
    void 
    Term<Element>::setNumMonomial(int numMon)
    {
        _numMonomial=numMon;
    }
    
    template <typename Element>
    void 
    Term<Element>::setTerm(std::string const s)
    {
        /* Beware, a specialised readCoefficient method must be defined */
        readCoefficient(s);
        Monomial mon;
        mon.allocate();
        mon.setMonomial(s);
        _numMonomial=mon.monomialToInt();
        mon.erase();
    }
    
    
    /* Miscellaneous */
    
    template<typename Element>
    void
    Term<Element>::readCoefficient(std::string const s)
    {
        cout << "Term: no defined readCoefficient method for this type" << endl;
    }
    
    template<>
    void
    Term<ElementPrime<int16_t>>::readCoefficient(std::string const s)
    {
        int res;
        try
        { 
            res=stoi(s);
        }
        catch(exception const & e)
        {
            if(s[0]=='-')
            {
                res=-1;
            }
            else
            {
                res=1;
            }
        }
        _coefficient=res;
    }
    
    template<>
    void
    Term<ElementPrime<int32_t>>::readCoefficient(std::string const s)
    {
        int res;
        try
        { 
            res=stoi(s);
        }
        catch(exception const & e)
        {
            if(s[0]=='-')
            {
                res=-1;
            }
            else
            {
                res=1;
            }
        }
        _coefficient=res;
    }
    
    template<>
    void
    Term<ElementPrime<int64_t>>::readCoefficient(std::string const s)
    {
        long res;
        try
        { 
            res=stol(s);
        }
        catch(exception const & e)
        {
            if(s[0]=='-')
            {
                res=-1;
            }
            else
            {
                res=1;
            }
        }
        _coefficient=res;
    }
    
    template<>
    void
    Term<ElementPrime<double>>::readCoefficient(std::string const s)
    {
        long res;
        try
        { 
            res=stol(s);
        }
        catch(exception const & e)
        {
            if(s[0]=='-')
            {
                res=-1;
            }
            else
            {
                res=1;
            }
        }
        _coefficient=(double)res;
    }
    
    template <typename Element>
    void
    Term<Element>::printTerm (ostream & stream) const
    {
        Monomial mon;
        mon.allocate();
        mon.setMonomial(_numMonomial);
        stream << _coefficient << "*" << mon;
        mon.erase();
    }
    
    template <typename Element>
    void
    Term<Element>::multNumMon(int numMon)
    {
        _numMonomial=MONOMIAL_ARRAY->multNumMonomial(_numMonomial, numMon);
    }
    
    
    /* Operators overload */
    
    template <typename Element>
    Term<Element> & 
    Term<Element>::operator=(Term const & term)
    {
        _coefficient=term._coefficient;
        _numMonomial=term._numMonomial;
        return * this;
    }
    
    template <typename Element>
    Term<Element> &
    Term<Element>::operator*=(Monomial const & monomial)
    {
        _numMonomial=MONOMIAL_ARRAY->multNumMonomial(_numMonomial, monomial.monomialToInt());
        return * this;
    }
    
    template <typename Element>
    Term<Element> &
    Term<Element>::operator*=(Element element)
    {
        _coefficient*=element;
        return * this;
    }
    
    template <typename Element>
    Term<Element> &
    Term<Element>::operator*=(Term const & term)
    {
        _coefficient*=term._coefficient;
        _numMonomial=MONOMIAL_ARRAY->multNumMonomial(_numMonomial, term._numMonomial);
        return *this;
    }
    
    template <typename Element>
    ostream & operator<<(ostream & stream, Term<Element> const & term)
    {
        term.printTerm(stream);
        return stream;
    }
    
    template <typename Element>
    Term<Element> operator * (Monomial const & mon, Term<Element> const & term)
    {
        Term<Element> copy(term);
        return copy*=mon;
    }
    
    template <typename Element>
    Term<Element> operator * (Term<Element> const & term, Monomial const & mon)
    {
        Term<Element> copy(term);
        return copy*=mon;
    }
    
    template <typename Element>
    Term<Element> operator * (Term<Element> const & term1, Term<Element> const & term2)
    {
        Term<Element> copy(term1);
        return copy*=term2;
    }
}

#endif // F4_TERM_INL
