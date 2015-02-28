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
  * \file monomial.inl
  * \brief Definition of Monomial methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON 
  */

#ifndef F4_MONOMIAL_INL
#define F4_MONOMIAL_INL

using namespace std;

namespace F4
{
    // static variables
    
    int Monomial::NB_VARIABLE = 0;
    
    string const  * Monomial::VARS=0;
    
    int * Monomial::WEIGHT=0;
    
    // static functions
    
    void Monomial::setNbVariable(int nbVariable)
    {
        Monomial::NB_VARIABLE = nbVariable;
    }
             
    int Monomial::getNbVariable()
    {
        return Monomial::NB_VARIABLE;
    }
    
    void Monomial::setVariable(string const  * vars)
    {
        Monomial::VARS=vars;
    }
    
    string const  * Monomial::getVariable()
    {
        return Monomial::VARS;
    }
    
    void Monomial::setWeight(int  * weight)
    {
        Monomial::WEIGHT=weight;
    }
    
    int * Monomial::getWeight()
    {
        return Monomial::WEIGHT;
    }
    
    // Constructor
    
    Monomial::Monomial(): _deg(0)
    {
        assert(NB_VARIABLE>0);
        _varlist=new int[NB_VARIABLE]();
        assert(_varlist != 0);
    }
    
    Monomial::Monomial(int const * varlist): _deg(0)
    {
        assert(NB_VARIABLE>0);
        _varlist=new int[NB_VARIABLE]();
        assert(_varlist != 0);
        for (int i=0; i<NB_VARIABLE; i++)
        {
            _varlist[i]=varlist[i];
            _deg+=varlist[i];
        }
    }
    
    Monomial::Monomial(Monomial const & toCopy): _deg(toCopy._deg)
    {
        _varlist=new int[NB_VARIABLE];
        assert(_varlist != 0);
        for(int i=0; i<NB_VARIABLE; i++)
        {
            _varlist[i]=toCopy._varlist[i];
        }
    }
    
    // Destructor
    
    Monomial::~Monomial()
    {
        delete[] _varlist;
        _varlist=0;
    }
    
    // Miscellaneous
    
    void
    Monomial::printMonomial (ostream & stream) const
    {
        int i;
        for (i = 0; i < NB_VARIABLE && (_varlist)[i] == 0; i++);
        if (i < NB_VARIABLE)
        {
            if (VARS!=0 && VARS[i]!= "")
                stream << VARS[i] << "^" << (_varlist)[i];
            else
                stream << "x" << i << "^" << (_varlist)[i];
            i++;
            for (; i < NB_VARIABLE; i++)
                if ((_varlist)[i] > 0)
                {
                    if (VARS != 0 && VARS[i]!= "")
                        stream <<"*" << VARS[i] << "^" << (_varlist)[i];
                    else
                        stream << "*x" << i << "^" << (_varlist)[i];
                }
        }
        else
            stream << "1";
    }
    
    int 
    Monomial::compareMonomial(Monomial const & mon) const
    {
        if (_deg == mon._deg)
        {
            for (int k = NB_VARIABLE - 1; k > 0; k--)
            {                       //deggrevlex
                if ((_varlist)[k] > (mon._varlist)[k])
                    return -1;
                if ((_varlist)[k] < (mon._varlist)[k])
                    return 1;
            }
            return 0;
        }
        return (_deg > mon._deg ? 1 : -1);
    }
    
    bool Monomial::isDivisible(Monomial const & mon) const
    {
        if (mon._deg > _deg)
        {
            return false;
        }
        bool test = true;
        for (int i = 0; i < NB_VARIABLE && test; i++)
        {
            test = test && (mon._varlist[i]) <= (_varlist[i]);
        }
        return test;
    }
    
    void Monomial::reset()
    {
        _deg=0;
        for(int i=0; i< NB_VARIABLE; i++)
        {
            _varlist[i]=0;
        }
    }
    
    // Operator overload
    
    Monomial & Monomial::operator=(Monomial const & mon)
    {
        if(this!=&mon)
        {
            _deg=mon._deg;
            for(int i=0; i<NB_VARIABLE; i++)
            {
                _varlist[i]=mon._varlist[i];
            }
        }
        return *this;
    }
    
    Monomial & Monomial::operator*=(Monomial const & mon)
    {
        _deg += mon._deg;
        for (int k = 0; k < NB_VARIABLE; k++)
        {
            (_varlist)[k] += (mon._varlist)[k];
        }
        return * this;
    }
    
    Monomial & Monomial::operator/=(Monomial const & mon)
    {
        if (mon._deg > _deg)
        {
            cout << "Monomial: not divisible" << endl;
            return * this;               // not divisible
        }
        Monomial copy(*this);
        for (int i = 0; i < NB_VARIABLE; i++)
        {
            if ((mon._varlist[i]) <= (_varlist[i]))
            {
                copy._varlist[i] -= mon._varlist[i];
                if (WEIGHT!=0)
                {
                    // weighted monomial order
                    copy._deg -= (mon._varlist)[i] * WEIGHT[i];
                }
                else
                {
                    copy._deg -= (mon._varlist)[i];
                }
            }
            else
            {
                cout << "Monomial: not divisible" << endl;
                return * this;           // not divisible
            }
        }
        (* this)=copy;
        copy.~Monomial();
        return * this;
    }
    
    ostream & operator<<(ostream & stream, Monomial const & mon)
    {
        mon.printMonomial();
        return stream;
    }
    
    bool operator==(Monomial const & mon1, Monomial const & mon2)
    {
        return (mon1.compareMonomial(mon2)==0);
    }
    
    bool operator>(Monomial const & mon1, Monomial const & mon2)
    {
        return (mon1.compareMonomial(mon2)==1);
    }
    
    bool operator>=(Monomial const & mon1, Monomial const & mon2)
    {
        return (mon1.compareMonomial(mon2)!=-1);
    }
    
    bool operator<(Monomial const & mon1, Monomial const & mon2)
    {
        return (mon1.compareMonomial(mon2)==-1);
    }
    
    bool operator<=(Monomial const & mon1, Monomial const & mon2)
    {
        return (mon1.compareMonomial(mon2)!=1);
    }
    
    Monomial operator * (Monomial const & mon1, Monomial const & mon2)
    {
        Monomial copy(mon1);
        return copy*=mon2;
    }
    
    Monomial operator / (Monomial const & mon1, Monomial const & mon2)
    {
        Monomial copy(mon1);
        return (copy/=mon2);
    }

}

#endif // F4_MONOMIAL_INL
