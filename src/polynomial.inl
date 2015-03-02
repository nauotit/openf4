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
    // Constructor 
    
    template <typename Element>
    Polynomial<Element>::Polynomial()
    {
    }
    
    template <typename Element>
    Polynomial<Element>::Polynomial(string const s)
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
                tmp=s[pos1-1]+tmp;
            }
            
            pos1=pos2+1; // We skip +
            cout << "Polynomial: " << tmp << endl;
            term.setTerm(tmp);
            
            it=_polynomial.insert_after(it, term);
        }
    }
    
    // Destructor
    
    template <typename Element>
    Polynomial<Element>::~Polynomial()
    {
        _polynomial.~forward_list();
    }
    
    // Miscellaneous
    
    template <typename Element>
    void
    Polynomial<Element>::printPolynomial (ostream & stream) const
    {
        typename forward_list<Term<Element>>::const_iterator it, it_tmp;
        for (it = _polynomial.begin(); it != _polynomial.end(); ++it)
        {
            it_tmp=it;
            it_tmp++;
            if(it_tmp !=_polynomial.end())
            {
                stream << "(" << *it << ") +";
            }
            else
            {
                stream << "(" << *it << ")";
            }
        }
    }
    
    // Operator overload
    
    template <typename Element>
    ostream & operator<<(ostream & stream, Polynomial<Element> const & polynomial)
    {
        polynomial.printPolynomial();
        return stream;
    }
}

#endif // F4_POLYNOMIAL_INL
