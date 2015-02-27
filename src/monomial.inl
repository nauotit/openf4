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
    int Monomial::NB_VARIABLE = 0;
    
    Monomial::Monomial(int nbVariable): _deg(0)
    {
        NB_VARIABLE=nbVariable;
        _varlist=new int[NB_VARIABLE]();
        assert(_varlist != 0);
    }
    
    Monomial::Monomial(int nbVariable, int const * varlist)
    {
        NB_VARIABLE=nbVariable;
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
        for(int i=0; i<NB_VARIABLE; i++)
        {
            _varlist[i]=toCopy._varlist[i];
        }
    }
    
    Monomial::~Monomial()
    {
        delete _varlist;
        _varlist=0;
    }
    
    void
    Monomial::printMonomial (ostream & stream, std::string const * vars) const
    {
        int i;
        for (i = 0; (_varlist)[i] == 0 && i < NB_VARIABLE; i++);
        if (i < NB_VARIABLE)
        {
            if (vars!=0 && vars[i]!= "")
                stream << vars[i] << "^" << (_varlist)[i];
            else
                stream << "x" << i << "^" << (_varlist)[i];
            i++;
            for (; i < NB_VARIABLE; i++)
                if ((_varlist)[i] > 0)
                {
                    if (vars != 0 && vars[i]!= "")
                        stream <<"*" << vars[i] << "^" << (_varlist)[i];
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
    
    // Operator overload
    
    Monomial & Monomial::operator=(Monomial const & toCopy)
    {
        if(this!=&toCopy)
        {
            _deg=toCopy._deg;
            for(int i=0; i<NB_VARIABLE; i++)
            {
                _varlist[i]=toCopy._varlist[i];
            }
        }
        return *this;
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

}

#endif // F4_MONOMIAL_INL
