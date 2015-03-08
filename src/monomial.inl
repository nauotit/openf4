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
    // Global variables
    
    extern int VERBOSE;
    
    
    // static variables
    
    int Monomial::NB_VARIABLE = 0;
    
    string const  * Monomial::VARS = 0;
    
    int * Monomial::WEIGHT = 0;
    
    vector<Monomial> Monomial::MONOMIAL_ARRAY;
    
    vector<int *> Monomial::NB_MONOMIAL;
    
    int Monomial::MAX_DEGREE = 0;
    
    int Monomial::NUM_MAX_LINE = 0; 
    
    int Monomial::NUM_MAX_COLUMN = 0;
    
    int ** Monomial::TABULATED_PRODUCT = 0;
    
    
    // static methods
    
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
        assert(maxDegree>MAX_DEGREE);
        
        double size = 0;
        //NB_MONOMIAL[d][v] = number of degree d monomials in the v first variables.
        NB_MONOMIAL.reserve(maxDegree + 1);     
        size += (maxDegree + 1) * sizeof (int *);
        if(MAX_DEGREE==0)
        {
            // First call to setNbMonomial.
            for (int d = 0; d <= maxDegree; d++)
            {
                NB_MONOMIAL.push_back(new int[NB_VARIABLE + 2]);
                assert(NB_MONOMIAL[d] != 0);
            }
            size += ((maxDegree + 1) * (NB_VARIABLE + 2)) * sizeof (int);
        }
        else
        {
            // Other calls
            for (int d = MAX_DEGREE+1; d <= maxDegree; d++)
            {
                NB_MONOMIAL.push_back(new int[NB_VARIABLE + 2]);
                assert(NB_MONOMIAL[d] != 0);
            }
            size += ((maxDegree-MAX_DEGREE) * (NB_VARIABLE + 2)) * sizeof (int);
        }
        if (VERBOSE > 1)
        {
            cout << "Monomial: " << size / 1000000 << "Mo allocated for NB_MONOMIAL" <<endl;
        }
        
        if(MAX_DEGREE==0)
        {
            // First call to setNbMonomial
            for (int d = 0; d <= maxDegree; d++)
            {
                NB_MONOMIAL[d][0] = 0;
            }
        }
        else
        {
            // Other calls
            for (int d = MAX_DEGREE+1; d <= maxDegree; d++)
            {
                NB_MONOMIAL[d][0] = 0;
            }
        }

        for (int v = 1; v <= NB_VARIABLE; v++)
        {
            if(MAX_DEGREE==0)
            {
                // First call to setNbMonomial.
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
                // Other calls
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
            // First call to setNbMonomial.
            NB_MONOMIAL[0][NB_VARIABLE + 1] = 1;
            for (int d = 1; d <= maxDegree; d++)
            {
                NB_MONOMIAL[d][NB_VARIABLE + 1] = NB_MONOMIAL[d - 1][NB_VARIABLE + 1] + NB_MONOMIAL[d][NB_VARIABLE];
            }
        }
        else
        {
            // Other calls
            for (int d = MAX_DEGREE+1; d <= maxDegree; d++)
            {
                NB_MONOMIAL[d][NB_VARIABLE + 1] = NB_MONOMIAL[d - 1][NB_VARIABLE + 1] + NB_MONOMIAL[d][NB_VARIABLE];
            }
        }
        MAX_DEGREE=maxDegree;
        
        // Update MONOMIAL_ARRAY
        setMonomialArray(); 
    }
    
    vector<int *> & Monomial::getNbMonomial()
    {
        return NB_MONOMIAL;
    }
    
    void Monomial::freeNbMonomial()
    {
        for(vector<int*>::iterator it=NB_MONOMIAL.begin(); it != NB_MONOMIAL.end(); ++it)
        {
            delete[] *it;
            *it=0;
        }
        freeMonomialArray();
    }

    void Monomial::setMonomialArray()
    {
        int size=NB_MONOMIAL[MAX_DEGREE][NB_VARIABLE+1];
        if (VERBOSE>1)
        {
            cout << "Monomial: " << ((double)size * (sizeof(Monomial) + NB_VARIABLE*sizeof(int)))/1000000 << " Mo reserved for MONOMIAL_ARRAY " << endl;
        }
        MONOMIAL_ARRAY.reserve(size);
        for(int i=(int)MONOMIAL_ARRAY.size(); i<size; i++)
        {
            MONOMIAL_ARRAY.push_back(Monomial(i));
        }
    }
     
    vector<Monomial> & Monomial::getMonomialArray()
    {
        return MONOMIAL_ARRAY;
    }
    
    void Monomial::freeMonomialArray()
    {
        MONOMIAL_ARRAY.clear();
    }
    
    void Monomial::setTabulatedProduct(int deg1, int deg2)
    {
        // Preconditions
        assert(NB_VARIABLE > 0);
        assert(!NB_MONOMIAL.empty());
        
        if((int)NB_MONOMIAL.size() < deg1+deg2)
        {
            setNbMonomial(deg1+deg2);
        }
        
        int nb;
        double size=0;
        NUM_MAX_LINE = NB_MONOMIAL[deg1][NB_VARIABLE + 1];
        NUM_MAX_COLUMN = NB_MONOMIAL[deg2][NB_VARIABLE + 1];
        
        cout << "Monomial: NUM_MAX_LINE: " << NUM_MAX_LINE << endl;
        cout << "Monomial: NUM_MAX_COLUMN: " << NUM_MAX_COLUMN << endl;
        
        TABULATED_PRODUCT = new int*[NUM_MAX_LINE];
        size += NUM_MAX_LINE * sizeof (int *);

        assert(TABULATED_PRODUCT!=0);
        
        Monomial tmp1;
        Monomial tmp2;

        for (int numMon1 = 0; numMon1 < NUM_MAX_LINE; numMon1++)
        {
            tmp1=MONOMIAL_ARRAY[numMon1];
            nb = NB_MONOMIAL[MAX_DEGREE - tmp1._deg][NB_VARIABLE + 1];
            if (nb > NUM_MAX_COLUMN)
            {
                nb = NUM_MAX_COLUMN;
            }
            TABULATED_PRODUCT[numMon1] = new int[nb];
            size += nb * sizeof (int);
            for (int numMon2 = 0; numMon2 < nb; numMon2++)
            {
                tmp2=tmp1*MONOMIAL_ARRAY[numMon2];
                TABULATED_PRODUCT[numMon1][numMon2] = tmp2.monomialToInt();
            }
        }
        if (VERBOSE > 1)
        {
            cout << "Monomial: products computed up to deg "<< deg1 <<" x " << deg2 <<endl; 
            cout << "Monomial: " << size/1000000 << "Mo allocated for TABULATED_PRODUCT " << endl;
        }
    }
    
    int ** 
    Monomial::getTabulatedProduct()
    {
        return TABULATED_PRODUCT;
    }
    
    void 
    Monomial::freeTabulatedProduct()
    {
        // Preconditions
        assert(NB_VARIABLE > 0);
        
        for (int numMon = 0; numMon < NUM_MAX_LINE; numMon++)
        {
            delete[] TABULATED_PRODUCT[numMon];
            TABULATED_PRODUCT[numMon]=0;
        }
        delete[] TABULATED_PRODUCT;
        TABULATED_PRODUCT=0;
    }
    
    int 
    Monomial::multNumMonomial(int numMon1, int numMon2)
    {
        if (numMon1 > numMon2)
        {
            swap(numMon1,numMon2);
        }
        if (numMon1 < NUM_MAX_LINE && numMon2 < NUM_MAX_COLUMN)
        {
            return TABULATED_PRODUCT[numMon1][numMon2];
        }
        else
        {
            if( VERBOSE > 1)
            {
                cout << "Monomial: MultNumMonomial, cannot use TABULATED_PRODUCT " << MONOMIAL_ARRAY[numMon1].getDegree() <<" " << MONOMIAL_ARRAY[numMon2].getDegree()  << endl;
            }
            Monomial tmp=MONOMIAL_ARRAY[numMon1]*MONOMIAL_ARRAY[numMon2];
            return tmp.monomialToInt();
        }
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
    
    Monomial const &
    Monomial::getNumMonomial(int numMon)
    {
        // Preconditions
        assert(! NB_MONOMIAL.empty());
        assert(NB_VARIABLE > 0);
        
        while(NB_MONOMIAL[MAX_DEGREE][NB_VARIABLE+1]<numMon)
        {
            // We increase NB_MONOMIAL:
            setNbMonomial(MAX_DEGREE+5);
        }
        return MONOMIAL_ARRAY[numMon];
    }
    
    void 
    Monomial::initMonomial(int nbVariable, int maxDegree, int deg1, int deg2)
    {
        // Set the number of variable
        setNbVariable(nbVariable);
        string *vars =new string[NB_VARIABLE];
        int * weight=new int[NB_VARIABLE];
        for(int i=0; i < NB_VARIABLE; i++)
        {
            vars[i]="x"+to_string(i);
            weight[i]=1;
        }
        
        // Set variable names
        setVariable(vars);
        
        // Set weights
        setWeight(weight);
        
        // Set NB_MONOMIAL and MONOMIAL_ARRAY
        setNbMonomial(maxDegree);
        
        // Set TABULATED_PRODUCT
        setTabulatedProduct(deg1, deg2);
        
        if(VERBOSE>1)
        {
            cout << "Monomial::initMonomial: allocation done ! " << endl;
        }
    }
    
    void 
    Monomial::freeMonomial()
    {
        freeTabulatedProduct();
        freeNbMonomial();
        delete[] VARS;
        delete[] WEIGHT;
        if(VERBOSE>1)
        {
            cout << "Monomial::freeMonomial: liberation done ! " << endl;
        }
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
        assert(WEIGHT!=0);
        
        _varlist=new int[NB_VARIABLE]();
        assert(_varlist != 0);
        for (int i=0; i<NB_VARIABLE; i++)
        {
            _varlist[i]=varlist[i];
            _deg+=varlist[i]*WEIGHT[i];
        }
    }
    
    Monomial::Monomial(std::string const s)
    {
        // Preconditions
        assert(NB_VARIABLE > 0);
        assert(WEIGHT!=0);
        assert(VARS!=0);
        
        _deg=0;
        _varlist=new int[NB_VARIABLE]();
        assert(_varlist != 0);
        
        size_t pos=0;
        
        for(int i=0; i<NB_VARIABLE; i++)
        {
            pos=s.find(VARS[i]);
            if(pos != string::npos)
            {
                // VARS[i] is used in s
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
        }
    }
    
    Monomial::Monomial(int numMon)
    {
        // Preconditions
        assert(WEIGHT != 0);
        assert(!NB_MONOMIAL.empty());
        assert(NB_VARIABLE > 0);
        
        while(NB_MONOMIAL[MAX_DEGREE][NB_VARIABLE+1]<numMon)
        {
            // We increase NB_MONOMIAL:
            setNbMonomial(MAX_DEGREE+5);
        }
        
        _deg=0;
        _varlist=new int[NB_VARIABLE]();
        assert(_varlist != 0);
        
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
    
    Monomial::Monomial(Monomial && toCopy)
    {
        // Preconditions
        assert(NB_VARIABLE > 0);
        
        if(this!=&toCopy)
        {
            _deg=toCopy._deg;
            toCopy._deg=0;
            _varlist=toCopy._varlist;
            toCopy._varlist=0;
        }
    }


    // Destructor
    
    Monomial::~Monomial()
    {
        if(_varlist != 0)
        {
            delete[] _varlist;
            _varlist=0;
        }
    }
    
    
    // Get / Set
            
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
    
    
    // Miscellaneous
    
    void 
    Monomial::setMonomial(int const * varlist)
    {
        // Preconditions
        assert(NB_VARIABLE > 0);
        assert(WEIGHT!=0);
        
        for (int i=0; i<NB_VARIABLE; i++)
        {
            _varlist[i]=varlist[i];
            _deg+=varlist[i]*WEIGHT[i];
        }
    }
    
    void 
    Monomial::setMonomial(std::string const s)
    {
        // Preconditions
        assert(NB_VARIABLE > 0);
        assert(WEIGHT!=0);
        assert(VARS!=0);
        
        _deg=0;
        size_t pos=0;
        
        for(int i=0; i<NB_VARIABLE; i++)
        {
            pos=s.find(VARS[i]);
            if(pos != string::npos)
            {
                // VARS[i] is used in s
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
    Monomial::intToMonomial(int numMon)
    {
        // Preconditions
        assert(WEIGHT != 0);
        assert(! NB_MONOMIAL.empty());
        assert(NB_VARIABLE > 0);
        
        while(NB_MONOMIAL[MAX_DEGREE][NB_VARIABLE+1]<numMon)
        {
            // We increase NB_MONOMIAL:
            setNbMonomial(MAX_DEGREE+5);
        }
        
        int d;
        // degree of monomial numMon
        for (d = 0; NB_MONOMIAL[d][NB_VARIABLE + 1] <= numMon; d++);
        _deg = d;
        // look for its number among the degree d monomials.
        if (d != 0)
        {
            numMon -= NB_MONOMIAL[d - 1][NB_VARIABLE + 1];
        }
        // for each variable, look for the matching power. 
        int i, j;

        for (i = NB_VARIABLE - 1; i > 0; i--)
        {
            // degree of the i-th variable
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
        // Preconditions
        assert(WEIGHT != 0);
        assert(NB_VARIABLE > 0);
        
        if(_deg > MAX_DEGREE)
        {
            setNbMonomial(_deg);
        }
        
        assert(_deg <= MAX_DEGREE);
        
        int i, res;
        if (_deg == 0)
        {
            return 0;
        }

        // skip monomials of degree < _deg 
        res = NB_MONOMIAL[_deg - 1][NB_VARIABLE + 1];
        // on recherche la position du monome pour le degre deg
        // tmp = degre restant apres avoir enleve le degre des dernieres variables
        int tmp = _deg - _varlist[NB_VARIABLE - 1] * WEIGHT[NB_VARIABLE - 1];
        for (i = NB_VARIABLE - 1; i > 0 && tmp > 0; i--)
        {
            // les mon dont le deg en les i premieres variables est <
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
        // Preconditions
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
        // Preconditions
        assert(NB_VARIABLE > 0);
        
        if (_deg == mon._deg)
        {
            for (int k = NB_VARIABLE - 1; k > 0; k--)
            {   // deggrevlex monomial order
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
    
    Monomial & Monomial::operator=(Monomial && mon)
    {
        // Preconditions
        assert(NB_VARIABLE > 0);
        
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
        assert(WEIGHT!=0);
        
        if (mon._deg > _deg)
        {
            // not divisible
            cout << "Monomial: not divisible" << endl;
            return * this;               
        }
        Monomial copy(*this);
        for (int i = 0; i < NB_VARIABLE; i++)
        {
            if ((mon._varlist[i]) <= (_varlist[i]))
            {
                copy._varlist[i] -= mon._varlist[i];
                // weighted monomial order
                copy._deg -= (mon._varlist)[i] * WEIGHT[i];
                
            }
            else
            {
                // not divisible
                cout << "Monomial: not divisible" << endl;
                return * this;           
            }
        }
        (* this)=copy;
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
