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
    // Static methods
    
    template<typename Element>
    Element
    Term<Element>::readCoefficient(std::string const s)
    {
        cout << "Term: no defined readCoefficient method for this type" << endl;
        return 0;
    }
    
    template<>
    int
    Term<int>::readCoefficient(std::string const s)
    {
        int res;
        try
        { 
            res=stoi(s);
        }
        catch(exception const & e)
        {
            res=1;
        }
        return res;
    }
    
    template<>
    double
    Term<double>::readCoefficient(std::string const s)
    {
        double res;
        try
        { 
            res=stod(s);
        }
        catch(exception const & e)
        {
            res=1;
        }
        return res;
    }
    
    
    // Constructor 
    
    template <typename Element>
    Term<Element>::Term(): _coefficient(0), _numMonomial(-1)
    {
    }
    
    template <typename Element>
    Term<Element>::Term(Element coeff, Monomial const & mon): _coefficient(coeff), _numMonomial(mon.monomialToInt())
    {
    }
    
    template <typename Element>
    Term<Element>::Term(Element coeff, int numMon): _coefficient(coeff), _numMonomial(numMon)
    {
    }
    
    template <typename Element>
    Term<Element>::Term(std::string const s)
    {
        // Be carefull, a specialised readCoefficient method must be defined.
        _coefficient=readCoefficient(s);
        Monomial mon(s);
        _numMonomial=mon.monomialToInt();
    }
    
    template <typename Element>
    Term<Element>::Term(Term const & toCopy): _coefficient(toCopy._coefficient), _numMonomial(toCopy._numMonomial)
    {
    }
    
    
    // Destructor
    template <typename Element>
    Term<Element>::~Term()
    {
        _coefficient.~Element();
    }
    
    
    // Get / Set 
    
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
        _coefficient=coeff;
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
    
    
    // Miscellaneous
    
    template <typename Element>
    void 
    Term<Element>::setTerm(std::string const s)
    {
        // Be carefull, a specialised readCoefficient method must be defined.
        _coefficient=readCoefficient(s);
        Monomial mon(s);
        _numMonomial=mon.monomialToInt();
    }
    
    template <typename Element>
    void
    Term<Element>::printTerm (ostream & stream) const
    {
        Monomial mon(_numMonomial);
        stream << _coefficient << "*" << mon;
    }
    
    
    // Operator overload
    
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
        _numMonomial=Monomial::multNumMonomial(_numMonomial, monomial.monomialToInt());
        return * this;
    }
    
    template <typename Element>
    Term<Element> &
    Term<Element>::operator*=(int numMon)
    {
        _numMonomial=Monomial::multNumMonomial(_numMonomial, numMon);
        return * this;
    }
    
    template <typename Element>
    Term<Element> &
    Term<Element>::operator*=(Term const & term)
    {
        _coefficient*=term._coefficient;
        _numMonomial=Monomial::multNumMonomial(_numMonomial, term._numMonomial);
        return *this;
    }
    
    template <typename Element>
    Term<Element> &
    Term<Element>::operator/=(Monomial const & monomial)
    {
        _numMonomial=(Monomial(_numMonomial)/monomial).monomialToInt();
        return * this;
    }
            
    template <typename Element>
    Term<Element> &
    Term<Element>::operator/=(int numMon)
    {
        _numMonomial=(Monomial(_numMonomial)/Monomial(numMon)).monomialToInt();
        return * this;
    }
            
    template <typename Element>
    Term<Element> &
    Term<Element>::operator/=(Term const & term)
    {
        _coefficient/=term._coefficient;
        _numMonomial=(Monomial(_numMonomial)/Monomial(term._numMonomial)).monomialToInt();
        return * this;
    }
    
    template <typename Element>
    ostream & operator<<(ostream & stream, Term<Element> const & term)
    {
        term.printTerm();
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
    
    template <typename Element>
    Term<Element> operator / (Term<Element> const & term, Monomial const & mon)
    {
        Term<Element> copy(term);
        return copy/=mon;
    }
   
    template <typename Element>
    Term<Element> operator / (Term<Element> const & term1, Term<Element> const & term2)
    {
        Term<Element> copy(term1);
        return copy/=term2;
    }
}

#endif // F4_TERM_INL
