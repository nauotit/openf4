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
    // Static methods
    
    
    // Constructor
    
    template <typename Element>
    TaggedPolynomial<Element>::TaggedPolynomial()
    {
    }
    
    template <typename Element>
    TaggedPolynomial<Element>::TaggedPolynomial(Polynomial<Element> const & polynomial)
    {
        _polynomial=polynomial;
    }
    
    template <typename Element>
    TaggedPolynomial<Element>::TaggedPolynomial(TaggedPolynomial const & taggedPolynomial)
    {
        _polynomial=taggedPolynomial._polynomial;
        _simplyrules=taggedPolynomial._simplyrules;
    }
    
    // Destructor
    
    template <typename Element>
    TaggedPolynomial<Element>::~TaggedPolynomial()
    {
        _polynomial.reset();
        _simplyrules.clear();
    }
    
    
    // Miscellaneous
    
    template <typename Element>
    void 
    TaggedPolynomial<Element>::printTaggedPolynomial (std::ostream & stream) const
    {
        stream << "polynomial: ";
        _polynomial.printPolynomial(stream);
        stream << endl;
        typename vector<int>::const_iterator it, it_tmp;
        stream << "Simplyrules: [";
        for (it = _simplyrules.begin(); it != _simplyrules.end(); ++it)
        {
            it_tmp=it;
            it_tmp++;
            if(it_tmp !=_simplyrules.end())
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
            return (_polynomial.getNbTerm() - taggedPolynomial._polynomial.getNbTerm());
        }
        return cmp;
    }
    
    
    // Operator overload
    
    template <typename Element>
    TaggedPolynomial<Element> & 
    TaggedPolynomial<Element>::operator=(TaggedPolynomial const & taggedPolynomial)
    {
        _polynomial=taggedPolynomial._polynomial;
        _simplyrules=taggedPolynomial._simplyrules;
        return * this;
    }
    
    template <typename Element>
    ostream & operator<<(ostream & stream, TaggedPolynomial<Element> const & taggedPolynomial)
    {
        taggedPolynomial.printTaggedPolynomial();
        return stream;
    }
    
}

#endif // F4_TAGGED_POLYNOMIAL_INL
