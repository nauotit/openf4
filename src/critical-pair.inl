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
  * \file critical-pair.inl
  * \brief Definition of CriticalPair methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_CRITICAL_PAIR_INL
#define F4_CRITICAL_PAIR_INL

namespace F4
{
    // Static variables
    
    template <typename Element>
    vector<TaggedPolynomial<Element>> * CriticalPair<Element>::TAGGEG_POLYNOMIAL_ARRAY=0;
    
    
    // Static methods
    
    template <typename Element>
    void
    CriticalPair<Element>::setTaggedPolynomialArray(vector<TaggedPolynomial<Element>> * taggedPolynomialArray)
    {
        TAGGEG_POLYNOMIAL_ARRAY=taggedPolynomialArray;
    }
    
    template <typename Element>
    TaggedPolynomial<Element> const & 
    CriticalPair<Element>::getTaggedPolynomialArray(int numTaggedPolynomial)
    {
        return (*TAGGEG_POLYNOMIAL_ARRAY)[numTaggedPolynomial];
    }
    
    template <typename Element>
    int
    CriticalPair<Element>::getSizeTaggedPolynomialArray()
    {
        return (*TAGGEG_POLYNOMIAL_ARRAY).size();
    }
    
    
    // Constructor
    
    template <typename Element>
    CriticalPair<Element>::CriticalPair(): _lcm(-1), _u1(-1), _p1(-1), _u2(-1), _p2(-1)
    {
    }
            
    template <typename Element>
    CriticalPair<Element>::CriticalPair(int p1, int p2): _p1(p1), _p2(p2)
    {
        int nbVars=Monomial::getNbVariable();
        
        // Get the varlist of LM(p1) and LM(p2)
        Monomial ltP1(getTaggedPolynomialArray(p1).getLM());
        int * varlistp1=ltP1.getVarlist();
        
        Monomial ltP2(getTaggedPolynomialArray(p2).getLM());
        int * varlistp2=ltP2.getVarlist();
        
        int varlistLcm[nbVars];
        int varlistU1[nbVars];
        int varlistU2[nbVars];
        
        // computation of _lcm, _u1 and _u2
        for (int i = 0; i < nbVars; i++)
        {
            if (varlistp1[i] < varlistp2[i])
            {
                varlistU1[i] = varlistp2[i] - varlistp1[i];
                varlistU2[i] = 0;
                varlistLcm[i] = varlistp2[i];
            }
            else
            {
                varlistU1[i] = 0;
                varlistU2[i] = varlistp1[i] - varlistp2[i];
                varlistLcm[i] = varlistp1[i];
            }
        }
        
        _lcm=Monomial(varlistLcm).monomialToInt();
        _u1=Monomial(varlistU1).monomialToInt();
        _u2=Monomial(varlistU2).monomialToInt();
        
        //return (lt_f.deg + lt_g.deg != res->lcm.deg);
    }
    
    
    // Destructor
    
    template <typename Element>
    CriticalPair<Element>::~CriticalPair()
    {
    }
    
    
    // Get / Set
    
    template <typename Element>
    int 
    CriticalPair<Element>::getP1() const
    {
        return _p1;
    }
            
    template <typename Element>
    int 
    CriticalPair<Element>::getP2() const
    {
        return _p2;
    }
            
    template <typename Element>
    int 
    CriticalPair<Element>::getLcm() const
    {
        return _lcm;
    }
            
    template <typename Element>
    int 
    CriticalPair<Element>::getU1() const
    {
        return _u1;
    }
            
    template <typename Element>
    int 
    CriticalPair<Element>::getU2() const
    {
        return _u2;
    }
    
    template <typename Element>
    int 
    CriticalPair<Element>::getDegree() const
    {
        return Monomial::getNumMonomial(_lcm).getDegree();
    }
    
    template <typename Element>
    bool 
    CriticalPair<Element>::setCriticalPair(int p1, int p2)
    {
        _p1=p1;
        _p2=p2;
        
        int nbVars=Monomial::getNbVariable();
        
        // Get the varlist of LM(p1) and LM(p2)
        Monomial ltP1(getTaggedPolynomialArray(p1).getLM());
        int * varlistp1=ltP1.getVarlist();
        
        Monomial ltP2(getTaggedPolynomialArray(p2).getLM());
        int * varlistp2=ltP2.getVarlist();
        
        int varlistLcm[nbVars];
        int varlistU1[nbVars];
        int varlistU2[nbVars];
        
        // computation of _lcm, _u1 and _u2
        for (int i = 0; i < nbVars; i++)
        {
            if (varlistp1[i] < varlistp2[i])
            {
                varlistU1[i] = varlistp2[i] - varlistp1[i];
                varlistU2[i] = 0;
                varlistLcm[i] = varlistp2[i];
            }
            else
            {
                varlistU1[i] = 0;
                varlistU2[i] = varlistp1[i] - varlistp2[i];
                varlistLcm[i] = varlistp1[i];
            }
        }
        
        Monomial lcm(varlistLcm);
        
        _lcm=lcm.monomialToInt();
        _u1=Monomial(varlistU1).monomialToInt();
        _u2=Monomial(varlistU2).monomialToInt();
        
        return ( (ltP1.getDegree() + ltP2.getDegree()) != lcm.getDegree());
    }
    
    // Miscellaneous
    
    template <typename Element>
    void 
    CriticalPair<Element>::printCriticalPair (std::ostream & stream) const
    {
        if((_lcm >= 0) && (_u1 >= 0) && (_p1 >= 0) && (_u2 >= 0) && (_p2 >= 0)) 
        {
            stream << "(" << Monomial::getNumMonomial(_lcm) << ", " << Monomial::getNumMonomial(_u1) << ", " << _p1 << ", " << Monomial::getNumMonomial(_u2) << ", " << _p2 << ")" ;
        }
        else
        {
            stream << "(" << _lcm << ", " <<_u1 << ", " << _p1 << ", " << _u2 << ", " << _p2 << ")" ;
        }
    }
    
    
    template <typename Element>
    int 
    CriticalPair<Element>::compareCriticalPair (CriticalPair const & criticalPair) const
    {
        int cmp=Monomial::compareNumMonomial(_lcm, criticalPair._lcm);
        if (cmp == 0)
        {
            if (_p1 > criticalPair._p1)
            {
                return 1;
            }
            else if (_p1 < criticalPair._p1)
            {
                return -1;
            }
            else if (_p2 > criticalPair._p2)
            {
                return 1;
            }
            else if (_p2 < criticalPair._p2)
            {
                return -1;
            }
        }
        return cmp;
    }
    
    
    // Operator overload
    
    template <typename Element>
    ostream & operator<<(ostream & stream, CriticalPair<Element> const & criticalPair)
    {
        criticalPair.printCriticalPair();
        return stream;
    }
    
    template <typename Element>
    bool operator==(CriticalPair<Element> const & criticalPair1, CriticalPair<Element> const & criticalPair2)
    {
        return (criticalPair1.compareCriticalPair(criticalPair2)==0);
    }
    
    template <typename Element>
    bool operator>(CriticalPair<Element> const & criticalPair1, CriticalPair<Element> const & criticalPair2)
    {
        return (criticalPair1.compareCriticalPair(criticalPair2)==1);
    }
    
    template <typename Element>
    bool operator>=(CriticalPair<Element> const & criticalPair1, CriticalPair<Element> const & criticalPair2)
    {
        return (criticalPair1.compareCriticalPair(criticalPair2)!=-1);
    }
    
    template <typename Element>
    bool operator<(CriticalPair<Element> const & criticalPair1, CriticalPair<Element> const & criticalPair2)
    {
        return (criticalPair1.compareCriticalPair(criticalPair2)==-1);
    }
    
    template <typename Element>
    bool operator<=(CriticalPair<Element> const & criticalPair1, CriticalPair<Element> const & criticalPair2)
    {
        return (criticalPair1.compareCriticalPair(criticalPair2)!=1);
    }

}

#endif // F4_CRITICAL_PAIR_INL
