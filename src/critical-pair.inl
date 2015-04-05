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
    /* Static variables */
    
    template <typename Element>
    vector<TaggedPolynomial<Element>> * CriticalPair<Element>::TAGGEG_POLYNOMIAL_ARRAY=0;
    
    template <typename Element>
    MonomialArray * CriticalPair<Element>::MONOMIAL_ARRAY=0;
    
    
    /* Static methods */
    
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
    
    template <typename Element>
    void
    CriticalPair<Element>::setMonomialArray(MonomialArray * monomialArray)
    {
        MONOMIAL_ARRAY=monomialArray;
    }
    
    
    /* Constructor */
    
    template <typename Element>
    CriticalPair<Element>::CriticalPair(): _p1(-1), _p2(-1)
    {
        _lcm.allocate();
        _u1.allocate();
        _u2.allocate();
    }
            
    template <typename Element>
    CriticalPair<Element>::CriticalPair(int p1, int p2): _p1(p1), _p2(p2)
    {
        _lcm.allocate();
        _u1.allocate();
        _u2.allocate();
        
        int nbVars=Monomial::getNbVariable();
        
        /* Get the varlist of LM(p1) and LM(p2) */
        
        Monomial const & ltP1=MONOMIAL_ARRAY->getNumMonomial(getTaggedPolynomialArray(p1).getLM());
        uint8_t const * varlistp1=ltP1.getVarlist();
        
        Monomial const & ltP2=MONOMIAL_ARRAY->getNumMonomial(getTaggedPolynomialArray(p2).getLM());
        uint8_t const * varlistp2=ltP2.getVarlist();
        
        uint8_t varlistLcm[nbVars];
        uint8_t varlistU1[nbVars];
        uint8_t varlistU2[nbVars];
        
        /* Computation of _lcm, _u1 and _u2 */
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
        
        _lcm.setMonomial(varlistLcm);
        _u1.setMonomial(varlistU1);
        _u2.setMonomial(varlistU2);
    }
    
    template <typename Element>
    CriticalPair<Element>::CriticalPair(CriticalPair<Element> const & cp): _p1(cp._p1), _p2(cp._p2)
    {
        _lcm.allocate();
        _lcm.setMonomial(cp._lcm);
        _u1.allocate();
        _u1.setMonomial(cp._u1);
        _u2.allocate();
        _u2.setMonomial(cp._u2);
    }
    
    
    /* Destructor */
    
    template <typename Element>
    CriticalPair<Element>::~CriticalPair()
    {
        _lcm.erase();
        _u1.erase();
        _u2.erase();
    }
    
    
    /* Get / Set */
    
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
    Monomial const & 
    CriticalPair<Element>::getLcm() const
    {
        return _lcm;
    }
    
    template <typename Element>
    Monomial const & 
    CriticalPair<Element>::getU1() const
    {
        return _u1;
    }
    
    template <typename Element>
    Monomial const & 
    CriticalPair<Element>::getU2() const
    {
        return _u2;
    }
    
    template <typename Element>
    int 
    CriticalPair<Element>::getDegree() const
    {
        return _lcm.getDegree();
    }
    
    template <typename Element>
    bool 
    CriticalPair<Element>::setCriticalPair(int p1, int p2)
    {
        _p1=p1;
        _p2=p2;
        
        int nbVars=Monomial::getNbVariable();
        
        /* Get the varlist of LM(p1) and LM(p2) */
        Monomial const & ltP1=MONOMIAL_ARRAY->getNumMonomial(getTaggedPolynomialArray(p1).getLM());
        uint8_t const * varlistp1=ltP1.getVarlist();
        
        Monomial const & ltP2=MONOMIAL_ARRAY->getNumMonomial(getTaggedPolynomialArray(p2).getLM());
        uint8_t const * varlistp2=ltP2.getVarlist();
        
        uint8_t varlistLcm[nbVars];
        uint8_t varlistU1[nbVars];
        uint8_t varlistU2[nbVars];
        
        /* Computation of _lcm, _u1 and _u2 */
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
        
        _lcm.setMonomial(varlistLcm);
        _u1.setMonomial(varlistU1);
        _u2.setMonomial(varlistU2);
        
        return ( (ltP1.getDegree() + ltP2.getDegree()) != _lcm.getDegree());
    }
    
    /* Miscellaneous */
    
    template <typename Element>
    void 
    CriticalPair<Element>::printCriticalPair (std::ostream & stream) const
    {
        stream << "(" << _lcm << ", " <<_u1 << ", " << _p1 << ", " << _u2 << ", " << _p2 << ")" ;
    }
    
    
    template <typename Element>
    int 
    CriticalPair<Element>::compareCriticalPair (CriticalPair const & criticalPair) const
    {
        int cmp=_lcm.compareMonomial(criticalPair._lcm);
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
    
    
    /* Operator overload */
    
    
    template <typename Element>
    CriticalPair<Element> & 
    CriticalPair<Element>::operator=(CriticalPair const & criticalPair)
    {
        _p1=criticalPair._p1;
        _p2=criticalPair._p2;
        _lcm.setMonomial(criticalPair._lcm);
        _u1.setMonomial(criticalPair._u1);
        _u2.setMonomial(criticalPair._u2);
        return * this;
    }
    
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
