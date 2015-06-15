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
        _coefficient.setZero();
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
        _coefficient.setOne();
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
    Term<ElementGF2>::readCoefficient(std::string const s)
    {
        int res;
        try
        { 
            res=stoi(s)%2;
        }
        catch(exception const & e)
        {
            res=1;
        }
        _coefficient=res;
    }
    
    template<>
    void
    Term<ElementGF2Extension<uint16_t>>::readCoefficient(std::string const s)
    { 
        /* Detect the beginning of the monomial */
        string tmp;
        size_t pos1=s.find(Monomial::getVariable()[0]);
        size_t pos2=0;
        for (int i = 1; i < Monomial::getNbVariable(); ++i)
        {
            pos2=s.find(Monomial::getVariable()[i]);
            if(pos2 != string::npos)
            {
                pos1=min(pos1, pos2);
            }
        }
        /* Term with coefficient only */
        if(pos1==string::npos)
        {
            tmp=s;
        }
        
        /* Term without coefficient */
        if(pos1==0)
        {
            tmp=string("1");
        }
        else
        {
            /* Term with coefficient and monomial */
            if(s[pos1-1]=='*')
            {
                /* remove '*' */
                tmp=s.substr(0, pos1-1);
            }
            else
            {
                tmp=s.substr(0, pos1);
            }
        }
        
        /* Here tmp is either the empty string, a sign, a sign and a number or a number */
        if(tmp.empty())
        {
            tmp=string("1");
        }
        if(tmp.size()==1)
        {
            /* In case tmp is just a sign */
            tmp=string("1");
        }
        /* remove brackets */
        tmp.erase(std::remove(tmp.begin(), tmp.end(), ')'), tmp.end());
        tmp.erase(std::remove(tmp.begin(), tmp.end(), '('), tmp.end());
        if(tmp[0]=='+' || tmp[0]=='-')
        {
            /* remove sign */
            tmp=tmp.substr(1);
        }
        _coefficient=tmp;
    }
    
    template<>
    void
    Term<ElementGF2Extension<uint32_t>>::readCoefficient(std::string const s)
    { 
        /* Detect the beginning of the monomial */
        string tmp;
        size_t pos1=s.find(Monomial::getVariable()[0]);
        size_t pos2=0;
        for (int i = 1; i < Monomial::getNbVariable(); ++i)
        {
            pos2=s.find(Monomial::getVariable()[i]);
            if(pos2 != string::npos)
            {
                pos1=min(pos1, pos2);
            }
        }
        /* Term with coefficient only */
        if(pos1==string::npos)
        {
            tmp=s;
        }
        
        /* Term without coefficient */
        if(pos1==0)
        {
            tmp=string("1");
        }
        else
        {
            /* Term with coefficient and monomial */
            if(s[pos1-1]=='*')
            {
                /* remove '*' */
                tmp=s.substr(0, pos1-1);
            }
            else
            {
                tmp=s.substr(0, pos1);
            }
        }
        
        /* Here tmp is either the empty string, a sign, a sign and a number or a number */
        if(tmp.empty())
        {
            tmp=string("1");
        }
        if(tmp.size()==1)
        {
            /* In case tmp is just a sign */
            tmp=string("1");
        }
        /* remove brackets */
        tmp.erase(std::remove(tmp.begin(), tmp.end(), ')'), tmp.end());
        tmp.erase(std::remove(tmp.begin(), tmp.end(), '('), tmp.end());
        if(tmp[0]=='+' || tmp[0]=='-')
        {
            /* remove sign */
            tmp=tmp.substr(1);
        }
        _coefficient=tmp;
    }
    
    template<>
    void
    Term<ElementGF2Extension<uint64_t>>::readCoefficient(std::string const s)
    { 
        /* Detect the beginning of the monomial */
        string tmp;
        size_t pos1=s.find(Monomial::getVariable()[0]);
        size_t pos2=0;
        for (int i = 1; i < Monomial::getNbVariable(); ++i)
        {
            pos2=s.find(Monomial::getVariable()[i]);
            if(pos2 != string::npos)
            {
                pos1=min(pos1, pos2);
            }
        }
        /* Term with coefficient only */
        if(pos1==string::npos)
        {
            tmp=s;
        }
        
        /* Term without coefficient */
        if(pos1==0)
        {
            tmp=string("1");
        }
        else
        {
            /* Term with coefficient and monomial */
            if(s[pos1-1]=='*')
            {
                /* remove '*' */
                tmp=s.substr(0, pos1-1);
            }
            else
            {
                tmp=s.substr(0, pos1);
            }
        }
        
        /* Here tmp is either the empty string, a sign, a sign and a number or a number */
        if(tmp.empty())
        {
            tmp=string("1");
        }
        if(tmp.size()==1)
        {
            /* In case tmp is just a sign */
            tmp=string("1");
        }
        /* remove brackets */
        tmp.erase(std::remove(tmp.begin(), tmp.end(), ')'), tmp.end());
        tmp.erase(std::remove(tmp.begin(), tmp.end(), '('), tmp.end());
        if(tmp[0]=='+' || tmp[0]=='-')
        {
            /* remove sign */
            tmp=tmp.substr(1);
        }
        _coefficient=tmp;
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
    
    #ifdef HAVE_GIVARO
    template<>
    void
    Term<ElementGivaro<Givaro::Modular<Givaro::Log16>>>::readCoefficient(std::string const s)
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
        _coefficient=(int)res;
    }
    
    template<>
    void
    Term<ElementGivaro<Givaro::Modular<Givaro::Integer>>>::readCoefficient(std::string const s)
    {
        /* Detect the beginning of the monomial */
        string tmp;
        size_t pos1=s.find(Monomial::getVariable()[0]);
        size_t pos2=0;
        for (int i = 1; i < Monomial::getNbVariable(); ++i)
        {
            pos2=s.find(Monomial::getVariable()[i]);
            if(pos2 != string::npos)
            {
                pos1=min(pos1, pos2);
            }
        }
        /* Term with coefficient only */
        if(pos1==string::npos)
        {
            tmp=s;
        }
        
        /* Term without coefficient */
        if(pos1==0)
        {
            tmp=string("1");
        }
        else
        {
            /* Term with coefficient and monomial */
            if(s[pos1-1]=='*')
            {
                /* remove '*' */
                tmp=s.substr(0, pos1-1);
            }
            else
            {
                tmp=s.substr(0, pos1);
            }
        }
        
        /* Here tmp is either the empty string, a sign, a sign and a number or a number */
        if(tmp.empty())
        {
            tmp=string("1");
        }
        if(tmp.size()==1)
        {
            /* In case tmp is just a sign */
            if(tmp[0]=='-')
            {
                tmp=string("-1");
            }
            else
            {
                tmp=string("1");
            }
        }
        if(tmp[0]=='+')
        {
            /* remove sign */
            tmp=tmp.substr(1);
        }
        _coefficient=tmp;
    }
    
    template<>
    void
    Term<ElementGivaro<Givaro::GFqDom<long>>>::readCoefficient(std::string const s)
    {
        /* Detect the beginning of the monomial */
        string tmp;
        size_t pos1=s.find(Monomial::getVariable()[0]);
        size_t pos2=0;
        for (int i = 1; i < Monomial::getNbVariable(); ++i)
        {
            pos2=s.find(Monomial::getVariable()[i]);
            if(pos2 != string::npos)
            {
                pos1=min(pos1, pos2);
            }
        }
        /* Term with coefficient only */
        if(pos1==string::npos)
        {
            tmp=s;
        }
        
        /* Term without coefficient */
        if(pos1==0)
        {
            tmp=string("1");
        }
        
        else
        {
            /* Term with coefficient and monomial */
            if(s[pos1-1]=='*')
            {
                /* remove '*' */
                tmp=s.substr(0, pos1-1);
            }
            else
            {
                tmp=s.substr(0, pos1);
            }
        }
        
        /* Here tmp is either the empty string, a sign, a sign and a number or a number */
        if(tmp.empty())
        {
            tmp=string("(1)");
        }
        if(tmp.size()==1)
        {
            /* In case tmp is just a sign */
            if(tmp=="-")
            {
                tmp=string("(-1)");
            }
            else
            {
                tmp=string("(1)");
            }
        }
        /* remove brackets */
        tmp.erase(std::remove(tmp.begin(), tmp.end(), ')'), tmp.end());
        tmp.erase(std::remove(tmp.begin(), tmp.end(), '('), tmp.end());
        if(tmp[0]=='+')
        {
            /* remove sign */
            tmp=tmp.substr(1);
        }
        if(tmp[0]=='-')
        {
            /* remove sign */
            //tmp=tmp.substr(1);
        }
        
        _coefficient=tmp;
    }
    #endif // HAVE_GIVARO
    
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
    
    template <typename Element>
    int
    Term<Element>::compareTerm(Term<Element> const & term) const
    {
        return Monomial::compareNumMonomial(_numMonomial, term._numMonomial);
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
    
    template <typename Element>
    bool operator>(Term<Element> const & term1, Term<Element> const & term2)
    {
        return term1.compareTerm(term2)==1;
    }
    
    template <typename Element>
    bool operator<(Term<Element> const & term1, Term<Element> const & term2)
    {
        return term1.compareTerm(term2)==-1;
    }
}

#endif // F4_TERM_INL
