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
    // Constructor 
    
    template <typename Element>
    Term<Element>::Term(): _coefficient(0), _numMonomial(-1)
    {
    }
    
    template <typename Element>
    Term<Element>::Term(Element coeff, Monomial mon): _coefficient(coeff), _numMonomial(mon.monomialToInt())
    {
    }
    
    template <typename Element>
    Term<Element>::Term(std::string const s)
    {
        // Be carefull, a specialised readCoefficient method must be defined.
        _coefficient=readCoefficient(s);
        Monomial mon(s);
        _numMonomial=mon.monomialToInt();
        mon.~Monomial();
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
    Term<Element>::getCoefficient()
    {
        return _coefficient;
    }
    
    template <typename Element>
    void 
    Term<Element>::setCoefficient(Element coeff)
    {
        _coefficient=coeff;
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
        mon.~Monomial();
    }
    
    template <typename Element>
    void
    Term<Element>::printTerm (ostream & stream) const
    {
        Monomial mon;
        mon.intToMonomial(_numMonomial);
        stream << _coefficient << "*" << mon;
        mon.~Monomial();
    }
    
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
    
    // Operator overload
    
    template <typename Element>
    ostream & operator<<(ostream & stream, Term<Element> const & term)
    {
        term.printTerm();
        return stream;
    }
}

#endif // F4_TERM_INL
