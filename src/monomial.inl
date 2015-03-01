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
    
    int Monomial::VERBOSE=0;
    
    int Monomial::NB_VARIABLE = 0;
    
    string const  * Monomial::VARS=0;
    
    int * Monomial::WEIGHT=0;
    
    int ** Monomial::NB_MONOMIAL=0;
    
    int Monomial::MAX_DEGREE=0;
    
    int ** Monomial::TABULATED_PRODUCT=0;
    
    
    // static functions
    
    void Monomial::setVerbose(int verbose)
    {
        VERBOSE=verbose;
    }
    
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
        // Preconditions
        assert(WEIGHT != 0);
        assert(NB_VARIABLE > 0);
        
        MAX_DEGREE=maxDegree;
        
        double size = 0;
        NB_MONOMIAL = new int*[maxDegree + 1];     //NbMon[d][v] = nb de monomes de deg d et en les v premieres variables
        size += (maxDegree + 1) * sizeof (int *);
        assert(NB_MONOMIAL != 0);
        for (int d = 0; d <= maxDegree; d++)
        {
            NB_MONOMIAL[d] = new int[NB_VARIABLE + 2];
            assert(NB_MONOMIAL[d] != 0);
        }
        size += ((maxDegree + 1) * (NB_VARIABLE + 2)) * sizeof (int);
        if (VERBOSE > 1)
        {
            cout << "NB_MONOMIAL: " << size / 1000000 << "Mo allocated for NB_MONOMIAL" <<endl;
        }
        for (int d = 0; d <= maxDegree; d++)
        {
            NB_MONOMIAL[d][0] = 0;
        }

        for (int v = 1; v <= NB_VARIABLE; v++)
        {
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
        NB_MONOMIAL[0][NB_VARIABLE + 1] = 1;
        for (int d = 1; d <= maxDegree; d++)
        {
            NB_MONOMIAL[d][NB_VARIABLE + 1] = NB_MONOMIAL[d - 1][NB_VARIABLE + 1] + NB_MONOMIAL[d][NB_VARIABLE];
        }
    }
    
    int ** Monomial::getNbMonomial()
    {
        return NB_MONOMIAL;
    }
    
    void Monomial::freeNbMonomial(int maxDegree)
    {
        for (int d = 0; d <= maxDegree; d++)
        {
            delete[] NB_MONOMIAL[d];
            NB_MONOMIAL[d]=0;
        }
        delete[] NB_MONOMIAL;
        NB_MONOMIAL=0;
    }
    
    void Monomial::setTabulatedProduct(int deg1, int deg2)
    {
        // Preconditions
        assert(NB_VARIABLE > 0);
        assert(NB_MONOMIAL != 0);
        
        int nb;
        double size=0;
        int numMax1 = NB_MONOMIAL[deg1][NB_VARIABLE + 1];
        int numMax2 = NB_MONOMIAL[deg2][NB_VARIABLE + 1];
        
        TABULATED_PRODUCT = new int*[numMax1];
        size += numMax1 * sizeof (int *);

        assert(TABULATED_PRODUCT!=0);
        
        Monomial mon;
        Monomial tmp;

        for (int numMon = 0; numMon < numMax1; numMon++)
        {
            mon.intToMonomial(numMon);
            nb = NB_MONOMIAL[MAX_DEGREE - mon._deg][NB_VARIABLE + 1];
            if (nb > numMax2)
            {
                nb = numMax2;
            }
            TABULATED_PRODUCT[numMon] = new int[nb];
            size += nb * sizeof (int);
            for (int numMon2 = 0; numMon2 < nb; numMon2++)
            {
                tmp.intToMonomial(numMon2);
                TABULATED_PRODUCT[numMon][numMon2] = (tmp*=mon).monomialToInt();
            }
        }
        mon.~Monomial();
        tmp.~Monomial();
        if (VERBOSE > 1)
        {
            cout << "Monomial: products computed up to deg "<< deg1 <<" x " << deg2 <<endl; 
            cout << "Monomial: " << size << "Mo allocated for TABULATED_PRODUCT " << endl;
        }
    }
    
    int ** 
    Monomial::getTabulatedProduct()
    {
        return TABULATED_PRODUCT;
    }
    
    void 
    Monomial::freeTabulatedProduct(int deg1, int deg2)
    {
        // Preconditions
        assert(NB_VARIABLE > 0);
        assert(NB_MONOMIAL != 0);
        
        int numMax1 = NB_MONOMIAL[deg1][NB_VARIABLE + 1];
        for (int numMon = 0; numMon < numMax1; numMon++)
        {
            delete[] TABULATED_PRODUCT[numMon];
            TABULATED_PRODUCT[numMon]=0;
        }
        delete[] TABULATED_PRODUCT;
        TABULATED_PRODUCT=0;
    }
    
    // Constructor
    
    Monomial::Monomial(): _deg(0)
    {
        // Preconditions
        assert(NB_VARIABLE > 0);
        
        _varlist=new int[NB_VARIABLE]();
        assert(_varlist != 0);
    }
    
    Monomial::Monomial(int const * varlist): _deg(0)
    {
        // Preconditions
        assert(NB_VARIABLE > 0);
        
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
        // Preconditions
        assert(NB_VARIABLE > 0);
        
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
    Monomial::setMonomial(int const * varlist)
    {
        // Preconditions
        assert(NB_VARIABLE > 0);
        
        for (int i=0; i<NB_VARIABLE; i++)
        {
            _varlist[i]=varlist[i];
            _deg+=varlist[i];
        }
    }
    
    void 
    Monomial::intToMonomial(int numMon)
    {
        // Preconditions
        assert(WEIGHT != 0);
        assert(NB_MONOMIAL != 0);
        assert(NB_VARIABLE > 0);
        
        int d;
        //degre du monome numMon
        for (d = 0; NB_MONOMIAL[d][NB_VARIABLE + 1] <= numMon; d++);
        _deg = d;
        //on cherche le numero parmi les monomes de degre d
        if (d != 0)
        {
            numMon -= NB_MONOMIAL[d - 1][NB_VARIABLE + 1];
        }
        //pour chaque variable on cherche la puissance correspondante
        int i, j;
        if(WEIGHT!=0)
        {
            for (i = NB_VARIABLE - 1; i > 0; i--)
            {
                j = d / WEIGHT[i];      //deg de la variable num i
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
        else
        {
            for (i = NB_VARIABLE - 1; i > 0; i--)
            {
                j = d;      //deg de la variable num i
                while (numMon >= NB_MONOMIAL[d - j][i])
                {
                    numMon -= NB_MONOMIAL[d - j][i];
                    j--;
                }
                _varlist[i] = j;
                d -= j;
            }
            _varlist[0] = d;
        }
    }
    
    int Monomial::monomialToInt()
    {
        // Preconditions
        assert(WEIGHT != 0);
        assert(NB_MONOMIAL != 0);
        assert(NB_VARIABLE > 0);
        assert(_deg <= MAX_DEGREE);
        
        int i, res;
        if (_deg == 0)
        {
            return 0;
        }

        //on saute les monomes de deg total < deg
        res = NB_MONOMIAL[_deg - 1][NB_VARIABLE + 1];
        //on recherche la position du monome pour le degre deg
        //tmp = degre restant apres avoir enleve le degre des dernieres variables
        int tmp = _deg - _varlist[NB_VARIABLE - 1] * WEIGHT[NB_VARIABLE - 1];
        for (i = NB_VARIABLE - 1; i > 0 && tmp > 0; i--)
        {
            //les mon dont le deg en les i premieres variables est <
            if (tmp >= WEIGHT[i])
                res += NB_MONOMIAL[tmp - WEIGHT[i]][i + 1];
            tmp -= _varlist[i - 1] * WEIGHT[i - 1];
        }
        return (res);
    }
    
    void
    Monomial::printMonomial (ostream & stream) const
    {
        // Preconditions
        assert(NB_VARIABLE > 0);
        
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
        // Preconditions
        assert(NB_VARIABLE > 0);
        
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
        // Preconditions
        assert(NB_VARIABLE > 0);
        
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
        // Preconditions
        assert(NB_VARIABLE > 0);
        
        _deg=0;
        for(int i=0; i< NB_VARIABLE; i++)
        {
            _varlist[i]=0;
        }
    }
    
    // Operator overload
    
    Monomial & Monomial::operator=(Monomial const & mon)
    {
        // Preconditions
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
    
    Monomial & Monomial::operator*=(Monomial const & mon)
    {
        // Preconditions
        assert(NB_VARIABLE > 0);
        
        _deg += mon._deg;
        for (int k = 0; k < NB_VARIABLE; k++)
        {
            (_varlist)[k] += (mon._varlist)[k];
        }
        return * this;
    }
    
    Monomial & Monomial::operator/=(Monomial const & mon)
    {
        // Preconditions
        assert(NB_VARIABLE > 0);
        
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
