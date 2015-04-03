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
    /* Global variables */
    
    extern int VERBOSE;
    
    
    /* Static variables */
    
    int Monomial::NB_VARIABLE = 0;
    
    string const  * Monomial::VARS = 0;
    
    int * Monomial::WEIGHT = 0;
    
    vector<int *> Monomial::NB_MONOMIAL;
    
    int Monomial::MAX_DEGREE = 0;
    
    
    /* Static methods */
    
    void Monomial::setNbVariable(int nbVariable)
    {
        NB_VARIABLE = nbVariable;
    }
             
    int Monomial::getNbVariable()
    {
        return NB_VARIABLE;
    }
    
    void Monomial::setVariable(string const  * vars)
    {
        VARS=vars;
    }
    
    string const  * Monomial::getVariable()
    {
        return VARS;
    }
    
    void Monomial::setWeight(int  * weight)
    {
        WEIGHT=weight;
    }
    
    int * Monomial::getWeight()
    {
        return WEIGHT;
    }
    
    void Monomial::setNbMonomial(int maxDegree)
    {
        /* Preconditions */
        assert(WEIGHT != 0);
        assert(NB_VARIABLE > 0);
        
        if(maxDegree>MAX_DEGREE)
        {
            double size = 0;
            NB_MONOMIAL.reserve(10*maxDegree+1);     
            size += (maxDegree + 1) * sizeof (int *);
            if(MAX_DEGREE==0)
            {
                /* First call to setNbMonomial. */
                for (int d = 0; d <= maxDegree; d++)
                {
                    NB_MONOMIAL.push_back(new int[NB_VARIABLE + 2]);
                    assert(NB_MONOMIAL[d] != 0);
                }
                size += ((maxDegree + 1) * (NB_VARIABLE + 2)) * sizeof (int);
            }
            else
            {
                /* Other calls */
                for (int d = MAX_DEGREE+1; d <= maxDegree; d++)
                {
                    NB_MONOMIAL.push_back(new int[NB_VARIABLE + 2]);
                    assert(NB_MONOMIAL[d] != 0);
                }
                size += ((maxDegree-MAX_DEGREE) * (NB_VARIABLE + 2)) * sizeof (int);
            }
            if (VERBOSE > 1)
            {
                cout << "Monomial: " << size / 1000000 << "Mo allocated for NB_MONOMIAL (MAXDEGREE = " << maxDegree << ")" <<endl;
            }
            
            if(MAX_DEGREE==0)
            {
                /* First call to setNbMonomial */
                for (int d = 0; d <= maxDegree; d++)
                {
                    NB_MONOMIAL[d][0] = 0;
                }
            }
            else
            {
                /* Other calls */
                for (int d = MAX_DEGREE+1; d <= maxDegree; d++)
                {
                    NB_MONOMIAL[d][0] = 0;
                }
            }

            for (int v = 1; v <= NB_VARIABLE; v++)
            {
                if(MAX_DEGREE==0)
                {
                    /* First call to setNbMonomial. */
                    NB_MONOMIAL[0][v] = 1;
                    for (int d = 1; d <= maxDegree; d++)
                    {
                        if (d >= WEIGHT[v - 1])
                        {
                            NB_MONOMIAL[d][v] = NB_MONOMIAL[d - WEIGHT[v - 1]][v] + NB_MONOMIAL[d][v - 1];
                        }
                        else
                        {
                            NB_MONOMIAL[d][v] = NB_MONOMIAL[d][v - 1];
                        }
                    }
                }
                else
                {
                    /* Other calls */
                    for (int d = MAX_DEGREE+1; d <= maxDegree; d++)
                    {
                        if (d >= WEIGHT[v - 1])
                        {
                            NB_MONOMIAL[d][v] = NB_MONOMIAL[d - WEIGHT[v - 1]][v] + NB_MONOMIAL[d][v - 1];
                        }
                        else
                        {
                            NB_MONOMIAL[d][v] = NB_MONOMIAL[d][v - 1];
                        }
                    }
                }
            }
            if(MAX_DEGREE==0)
            {
                /* First call to setNbMonomial. */
                NB_MONOMIAL[0][NB_VARIABLE + 1] = 1;
                for (int d = 1; d <= maxDegree; d++)
                {
                    NB_MONOMIAL[d][NB_VARIABLE + 1] = NB_MONOMIAL[d - 1][NB_VARIABLE + 1] + NB_MONOMIAL[d][NB_VARIABLE];
                }
            }
            else
            {
                /* Other calls */
                for (int d = MAX_DEGREE+1; d <= maxDegree; d++)
                {
                    NB_MONOMIAL[d][NB_VARIABLE + 1] = NB_MONOMIAL[d - 1][NB_VARIABLE + 1] + NB_MONOMIAL[d][NB_VARIABLE];
                }
            }
            MAX_DEGREE=maxDegree;
        }
    }
    
    void Monomial::increaseNbMonomial(int numMonomial)
    {
        while(NB_MONOMIAL[MAX_DEGREE][NB_VARIABLE+1]<numMonomial)
        {
            /* We increase NB_MONOMIAL */
            setNbMonomial(MAX_DEGREE+2);
        }
    }
    
    int Monomial::getNbMonomial()
    {
        return NB_MONOMIAL[MAX_DEGREE][NB_VARIABLE+1];
    }
    
    int Monomial::getNbMonomial(int row, int column)
    {
        return NB_MONOMIAL[row][column];
    }
    
    void Monomial::freeNbMonomial()
    {
        for(vector<int*>::iterator it=NB_MONOMIAL.begin(); it != NB_MONOMIAL.end(); ++it)
        {
            delete[] *it;
            *it=0;
        }
        NB_MONOMIAL.clear();
    }
    
    int 
    Monomial::compareNumMonomial(int numMon1, int numMon2)
    {
        if (numMon1 > numMon2)
        {
            return 1;
        }
        else if (numMon1 < numMon2)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
    
    int 
    Monomial::varlistToInt(int const * varlist)
    {
        /* Preconditions */
        assert(WEIGHT != 0);
        assert(NB_VARIABLE > 0);
        
        int i, res;
        int deg = 0;
        for(i=0; i<NB_VARIABLE; i++)
        {
            deg+=varlist[i]*WEIGHT[i];
        }
        if (deg == 0)
        {
            return 0;
        }
        if(deg > MAX_DEGREE)
        {
            cout << "Monomial: monomialToInt, increase max degree" << endl;
            setNbMonomial(deg);
        }
        assert(deg <= MAX_DEGREE);
        /* skip monomials of degree < deg */
        res = NB_MONOMIAL[deg - 1][NB_VARIABLE + 1];
        /* Search the monomial position for the given degree */
        /* tmp = degree after removing the degree of the last variables */
        int tmp = deg - varlist[NB_VARIABLE - 1] * WEIGHT[NB_VARIABLE - 1];
        for (i = NB_VARIABLE - 1; i > 0 && tmp > 0; i--)
        {
            if (tmp >= WEIGHT[i])
            {
                res += NB_MONOMIAL[tmp - WEIGHT[i]][i + 1];
            }
            tmp -= varlist[i - 1] * WEIGHT[i - 1];
        }
        return (res);
    }
    
    int 
    Monomial::varlistToInt(int const * varlist1, int const * varlist2)
    {
        /* Preconditions */
        assert(WEIGHT != 0);
        assert(NB_VARIABLE > 0);
        
        int i, res;
        int deg = 0;
        int varlist[NB_VARIABLE];
        for(i=0; i<NB_VARIABLE; i++)
        {
            varlist[i]=varlist1[i]+varlist2[i];
            deg+=varlist[i]*WEIGHT[i];
        }
        if (deg == 0)
        {
            return 0;
        }
        if(deg > MAX_DEGREE)
        {
            cout << "Monomial: monomialToInt, increase max degree" << endl;
            setNbMonomial(deg);
        }
        assert(deg <= MAX_DEGREE);

        /* skip monomials of degree < deg */
        res = NB_MONOMIAL[deg - 1][NB_VARIABLE + 1];
        /* Search the monomial position for the given degree */
        /* tmp = degree after removing the degree of the last variables */
        int tmp = deg - varlist[NB_VARIABLE - 1] * WEIGHT[NB_VARIABLE - 1];
        for (i = NB_VARIABLE - 1; i > 0 && tmp > 0; i--)
        {
            if (tmp >= WEIGHT[i])
            {
                res += NB_MONOMIAL[tmp - WEIGHT[i]][i + 1];
            }
            tmp -= varlist[i - 1] * WEIGHT[i - 1];
        }
        return (res);
    }
    
    void 
    Monomial::initMonomial(int nbVariable, int degree)
    {
        if(nbVariable != NB_VARIABLE)
        {
            if (VARS != 0)
            {
                delete[] VARS;
            }
            if( WEIGHT != 0)
            {
                delete[] WEIGHT;
            }
            /* Set the number of variables */
            setNbVariable(nbVariable);
            string *vars = new string[NB_VARIABLE];
            int * weight = new int[NB_VARIABLE];
            for(int i=0; i < NB_VARIABLE; i++)
            {
                vars[i]="x"+to_string(i);
                weight[i]=1;
            }
            
            /* Set variable names */
            setVariable(vars);
            
            /* Set weights */
            setWeight(weight);
        }
        
        /* Set NB_MONOMIAL */
        setNbMonomial(degree);
        
        if(VERBOSE>1)
        {
            cout << "Monomial::initMonomial: allocation done ! " << endl << endl;
        }
    }
    
    void 
    Monomial::freeMonomial()
    {
        freeNbMonomial();
        if(VARS!=0)
        {
            delete[] VARS;
            VARS = 0;
        }
        if(WEIGHT!=0)
        {
            delete[] WEIGHT;
            WEIGHT = 0;
        }
        MAX_DEGREE = 0;
        NB_VARIABLE = 0;
        
        if(VERBOSE>1)
        {
            cout << "Monomial::freeMonomial: liberation done ! " << endl;
        }
    }
    
    
    /* Constructor */
    
    Monomial::Monomial(): _deg(0), _varlist(0)
    {
    }
    
    
    /* Destructor */
    
    Monomial::~Monomial()
    {
    }
    
    
    /* Get / Set */
            
    int 
    Monomial::getDegree() const
    {
        return _deg;
    }
    
    int * 
    Monomial::getVarlist() const
    {
        return _varlist;
    }
    
    int 
    Monomial::getVarlist(int index) const
    {
        assert(index<NB_VARIABLE);
        assert(index >= 0);
        return _varlist[index];
    }
    
    void 
    Monomial::setVarlist(int * varlist)
    {
        _varlist=varlist;
    }
    
    
    /* Miscellaneous */
    
    void 
    Monomial::allocate()
    {
        _varlist=new int[NB_VARIABLE]();
        assert(_varlist != 0);
        _deg=0;
    }
    
    void 
    Monomial::erase()
    {
        delete[] _varlist;
        _varlist=0;
        _deg=0;
    }
    
    void 
    Monomial::setMonomial(int const * varlist)
    {
        /* Preconditions */
        assert(NB_VARIABLE > 0);
        assert(WEIGHT!=0);
        
        _deg=0;
        for (int i=0; i<NB_VARIABLE; i++)
        {
            _varlist[i]=varlist[i];
            _deg+=_varlist[i]*WEIGHT[i];
        }
    }
    
    void 
    Monomial::setMonomial(std::string const s)
    {
        /* Preconditions */
        assert(NB_VARIABLE > 0);
        assert(WEIGHT!=0);
        assert(VARS!=0);
        
        _deg=0;
        size_t pos=0;
        
        for(int i=0; i<NB_VARIABLE; i++)
        {
            pos=s.find(VARS[i]);
            if((pos != string::npos) && ((s[pos+VARS[i].size()]<'0') || (s[pos+VARS[i].size()]>'9')) )
            {
                /* VARS[i] is used in s */
                pos+=VARS[i].size();
                if(s[pos]=='^')
                {
                    _varlist[i]=stoi(s.substr(pos+1));
                    _deg+=_varlist[i]*WEIGHT[i];
                }
                else
                {
                    _varlist[i]=1;
                    _deg+=_varlist[i]*WEIGHT[i];
                }
            }
            else
            {
                _varlist[i]=0;
            }
        }
    }
    
    void
    Monomial::setMonomial(int numMon)
    {
        /* Preconditions */
        assert(WEIGHT != 0);
        assert(!NB_MONOMIAL.empty());
        assert(NB_VARIABLE > 0);
        
        while(NB_MONOMIAL[MAX_DEGREE][NB_VARIABLE+1]<numMon)
        {
            /* We increase NB_MONOMIAL */
            setNbMonomial(MAX_DEGREE+2);
        }
        
        int d;
        /* Degree of monomial numMon */
        for (d = 0; NB_MONOMIAL[d][NB_VARIABLE + 1] <= numMon; d++);
        _deg = d;
        /* Look for its number among the degree d monomials */
        if (d != 0)
        {
            numMon -= NB_MONOMIAL[d - 1][NB_VARIABLE + 1];
        }
        /* For each variable, look for the matching power */
        int i, j;

        for (i = NB_VARIABLE - 1; i > 0; i--)
        {
            /* Degree of variable number i */
            j = d / WEIGHT[i];      
            while (numMon >= NB_MONOMIAL[d - j * WEIGHT[i]][i])
            {
                numMon -= NB_MONOMIAL[d - j * WEIGHT[i]][i];
                j--;
            }
            _varlist[i] = j;
            d -= j * WEIGHT[i];
        }
        _varlist[0] = d / WEIGHT[0];
    }
    
    void
    Monomial::setMonomial(Monomial const & mon)
    {
        if(this!=&mon)
        {
            _deg=mon._deg;
            for(int i=0; i<NB_VARIABLE; i++)
            {
                _varlist[i]=mon._varlist[i];
            }
        }
    }
    
    void 
    Monomial::setMonomialMultiply(Monomial const & mon1, Monomial const & mon2)
    {
        /* Preconditions */
        assert(NB_VARIABLE > 0);
        assert(WEIGHT!=0);
        
        for (int i=0; i<NB_VARIABLE; i++)
        {
            _varlist[i]=mon1._varlist[i]+mon2._varlist[i];
        }
        _deg=mon1._deg+mon2._deg;
    }
    
    void 
    Monomial::setMonomialDivide(Monomial const & mon1, Monomial const & mon2)
    {
        /* Preconditions */
        assert(NB_VARIABLE > 0);
        assert(WEIGHT!=0);
        
        for (int i=0; i<NB_VARIABLE; i++)
        {
            _varlist[i]=(mon1._varlist[i]-mon2._varlist[i]);
        }
        _deg=(mon1._deg-mon2._deg);
    }
    
    
    void 
    Monomial::intToMonomial(int numMon)
    {
        /* Preconditions */
        assert(WEIGHT != 0);
        assert(! NB_MONOMIAL.empty());
        assert(NB_VARIABLE > 0);
        
        while(NB_MONOMIAL[MAX_DEGREE][NB_VARIABLE+1]<numMon)
        {
            /* We increase NB_MONOMIAL */
            setNbMonomial(MAX_DEGREE+2);
        }
        
        int d;
        /* Degree of monomial numMon */
        for (d = 0; NB_MONOMIAL[d][NB_VARIABLE + 1] <= numMon; d++);
        _deg = d;
        /* Look for its number among the degree d monomials */
        if (d != 0)
        {
            numMon -= NB_MONOMIAL[d - 1][NB_VARIABLE + 1];
        }
        /* For each variable, look for the matching power */
        int i, j;

        for (i = NB_VARIABLE - 1; i > 0; i--)
        {
            /* Degree of the i-th variable */
            j = d / WEIGHT[i];
            while (numMon >= NB_MONOMIAL[d - j * WEIGHT[i]][i])
            {
                numMon -= NB_MONOMIAL[d - j * WEIGHT[i]][i];
                j--;
            }
            _varlist[i] = j;
            d -= j * WEIGHT[i];
        }
        _varlist[0] = d / WEIGHT[0];
    }
    
    int Monomial::monomialToInt() const
    {
        /* Preconditions */
        assert(WEIGHT != 0);
        assert(NB_VARIABLE > 0);
        
        if (_deg == 0)
        {
            return 0;
        }
        if(_deg > MAX_DEGREE)
        {
            cout << "Monomial: monomialToInt, increase max degree" << endl;
            setNbMonomial(_deg);
        }
        assert(_deg <= MAX_DEGREE);
        int i, res;
        
        /* skip monomials of degree < deg */
        res = NB_MONOMIAL[_deg - 1][NB_VARIABLE + 1];
        /* Search the monomial position for the given degree */
        /* tmp = degree after removing the degree of the last variables */
        int tmp = _deg - _varlist[NB_VARIABLE - 1] * WEIGHT[NB_VARIABLE - 1];
        for (i = NB_VARIABLE - 1; i > 0 && tmp > 0; i--)
        {
            if (tmp >= WEIGHT[i])
            {
                res += NB_MONOMIAL[tmp - WEIGHT[i]][i + 1];
            }
            tmp -= _varlist[i - 1] * WEIGHT[i - 1];
        }
        return (res);
    }
    
    void
    Monomial::printMonomial (ostream & stream) const
    {
        /* Preconditions */
        assert(NB_VARIABLE > 0);
        
        int i;
        for (i = 0; i < NB_VARIABLE && (_varlist)[i] == 0; i++);
        if (i < NB_VARIABLE)
        {
            if (VARS!=0 && VARS[i]!= "")
            {
                stream << VARS[i] << "^" << (_varlist)[i];
            }
            else
            {
                stream << "x" << i << "^" << (_varlist)[i];
            }
            i++;
            for (; i < NB_VARIABLE; i++)
            {
                if ((_varlist)[i] > 0)
                {
                    if (VARS != 0 && VARS[i]!= "")
                    {
                        stream <<"*" << VARS[i] << "^" << (_varlist)[i];
                    }
                    else
                    {
                        stream << "*x" << i << "^" << (_varlist)[i];
                    }
                }
            }
        }
        else
        {
            stream << "1";
        }
    }
    
    int 
    Monomial::compareMonomial(Monomial const & mon) const
    {
        /* Preconditions */
        assert(NB_VARIABLE > 0);
        
        if (_deg == mon._deg)
        {
            for (int k = NB_VARIABLE - 1; k > 0; k--)
            {   
                /* deggrevlex monomial order */
                if ((_varlist)[k] > (mon._varlist)[k])
                {
                    return -1;
                }
                if ((_varlist)[k] < (mon._varlist)[k])
                {
                    return 1;
                }
            }
            return 0;
        }
        return (_deg > mon._deg ? 1 : -1);
    }
    
    bool Monomial::isDivisible(Monomial const & mon) const
    {
        /* Preconditions */
        assert(NB_VARIABLE > 0);
        
        if (mon._deg > _deg)
        {
            return false;
        }
        for (int i = 0; i < NB_VARIABLE; i++)
        {
            if((mon._varlist[i]) > (_varlist[i]))
            {
                return false;
            }
        }
        return true;
    }
    
    void Monomial::reset()
    {
        /* Preconditions */
        assert(NB_VARIABLE > 0);
        
        _deg=0;
        for(int i=0; i< NB_VARIABLE; i++)
        {
            _varlist[i]=0;
        }
    }
    
    
    /* Operator overload */
    
    Monomial & Monomial::operator=(Monomial const & mon)
    {
        /* Preconditions */
        assert(NB_VARIABLE > 0);
        
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
    
    Monomial & Monomial::operator=(Monomial && mon)
    {
        /* Preconditions */
        assert(NB_VARIABLE > 0);
        
        cout << "MOVE = called" << endl;
        
        if(this!=&mon)
        {
            _deg=mon._deg;
            mon._deg=0;
            delete[] _varlist;
            _varlist=mon._varlist;
            mon._varlist=0;
        }
        return *this;
    }
    
    Monomial & Monomial::operator*=(Monomial const & mon)
    {
        /* Preconditions */
        assert(NB_VARIABLE > 0);
        
        _deg += mon._deg;
        for (int k = 0; k < NB_VARIABLE; k++)
        {
            (_varlist)[k] += (mon._varlist)[k];
        }
        return * this;
    }
    
    int multiplyMonomial (Monomial const & mon1, Monomial const & mon2)
    {
        /* Preconditions */
        assert(Monomial::WEIGHT != 0);
        assert(Monomial::NB_VARIABLE > 0);
        
        int i, res;
        int deg = 0;
        int varlist[Monomial::NB_VARIABLE];
        for(i=0; i<Monomial::NB_VARIABLE; i++)
        {
            varlist[i]=mon1._varlist[i]+mon2._varlist[i];
            deg+=varlist[i]*Monomial::WEIGHT[i];
        }
        if (deg == 0)
        {
            return 0;
        }
        if(deg > Monomial::MAX_DEGREE)
        {
            cout << "Monomial: monomialToInt, increase max degree" << endl;
            Monomial::setNbMonomial(deg);
        }
        assert(deg <= Monomial::MAX_DEGREE);

        /* skip monomials of degree < deg */
        res = Monomial::NB_MONOMIAL[deg - 1][Monomial::NB_VARIABLE + 1];
        /* Search the monomial position for the given degree */
        /* tmp = degree after removing the degree of the last variables */
        int tmp = deg - varlist[Monomial::NB_VARIABLE - 1] * Monomial::WEIGHT[Monomial::NB_VARIABLE - 1];
        for (i = Monomial::NB_VARIABLE - 1; i > 0 && tmp > 0; i--)
        {
            if (tmp >= Monomial::WEIGHT[i])
            {
                res += Monomial::NB_MONOMIAL[tmp - Monomial::WEIGHT[i]][i + 1];
            }
            tmp -= varlist[i - 1] * Monomial::WEIGHT[i - 1];
        }
        return (res);
    }
    
    Monomial & Monomial::operator/=(Monomial const & mon)
    {
        /* Preconditions */
        assert(NB_VARIABLE > 0);
        assert(WEIGHT!=0);
        
        for (int i = 0; i < NB_VARIABLE; i++)
        {
            _varlist[i] -= mon._varlist[i];
            /* Weighted monomial order */
            _deg -= (mon._varlist)[i] * WEIGHT[i];
        }
        return * this;
    }
    
    ostream & operator<<(ostream & stream, Monomial const & mon)
    {
        mon.printMonomial(stream);
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
