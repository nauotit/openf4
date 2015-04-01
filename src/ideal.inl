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
  * \file ideal.inl
  * \brief Definition of Ideal methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_IDEAL_INL
#define F4_IDEAL_INL

using namespace std;

namespace F4
{
    /* Constructor */
    
    template <typename Element>
    Ideal<Element>::Ideal(std::vector<Polynomial<Element>> & polynomialArray, int nbVariable, int capacity, int degree, int deg1, int deg2): _polynomialArray(polynomialArray), _nbVariable(Monomial::getNbVariable()), _numPol(0), _numTot(0), _numGen(0), _monomialArray(nbVariable, capacity, degree, deg1, deg2)
    {
        /* Share the monomial array. */
        Term<Element>::setMonomialArray(&_monomialArray);
        TaggedPolynomial<Element>::setMonomialArray(&_monomialArray);
        CriticalPair<Element>::setMonomialArray(&_monomialArray);
        /* Share the tagged polynomial array. */
        CriticalPair<Element>::setTaggedPolynomialArray(&_taggedPolynomialArray);
        
        _taggedPolynomialArray.reserve(40000);
        _total.reserve(10000);
        _basis.reserve(1000);
        _used.reserve(10000);
        
        timeSimplify=0;
    }
    
    
    /* Destructor */
    
    template <typename Element>
    Ideal<Element>::~Ideal()
    {
    }
    
    
    /* Miscellaneous */
    
    template <typename Element>
    void
    Ideal<Element>::printInfo() const
    {
        cout << "_total: ";
        for(vector<int>:: const_iterator it=_total.begin(); it != _total.end(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
        
        cout << "_used: ";
        for(vector<int>:: const_iterator it=_used.begin(); it != _used.end(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
        
        cout << "_basis: ";
        for(vector<int>:: const_iterator it=_basis.begin(); it != _basis.end(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
        cout << "_total[_basis]: ";
        for(vector<int>:: const_iterator it=_basis.begin(); it != _basis.end(); ++it)
        {
            cout << _total[*it] << " ";
        }
        cout << endl;
        
        cout << "_numPol: " << _numPol << endl;
        cout << "_numTot: " << _numTot << endl;
        cout << "_numGen: " << _numGen << endl << endl << endl;
    }
    
    template <typename Element>
    void
    Ideal<Element>::printReducedGroebnerBasis(bool printBasis) const
    {
        cout << "_basis: ";
        for(vector<int>:: const_iterator it=_basis.begin(); it != _basis.end(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
        cout << "_total[_basis]: ";
        for(vector<int>:: const_iterator it=_basis.begin(); it != _basis.end(); ++it)
        {
            cout << _total[*it] << " ";
        }
        cout << endl;
        
        if(printBasis)
        { 
            for(vector<int>:: const_iterator it=_basis.begin(); it != _basis.end(); ++it)
            {
                cout << _total[*it] << ": " << _taggedPolynomialArray[_total[*it]] << endl << endl;
            }
        }
    }
    
    template <typename Element>
    void
    Ideal<Element>::printReducedGroebnerBasis(string const filename, long modulo) const
    {
        ofstream file(filename);
        if (file)
        {
            file << "FF:=FiniteField(" << modulo << ");" << endl;
            file << "P<";
            for(int i=0; i< _nbVariable - 1; i++)
            {
                file << Monomial::getVariable()[i] << ",";
            }
            file << Monomial::getVariable()[_nbVariable-1];
            file << ">:=PolynomialRing(FF, "<< _nbVariable << ", \"grevlex\");" << endl;
            file << "S:={ " << endl;
            
            for(int i = 0; i < _numGen - 1 ; i++)
            {
                file << _taggedPolynomialArray[_total[_basis[i]]].getPolynomialConst() << "," << endl;
            }
            file << _taggedPolynomialArray[_total[_basis[_numGen - 1]]].getPolynomialConst() << "};" << endl;
            file.close();
        }
        else
        {
            cout << "File open failed" << endl;
        }
    }
    
    template <typename Element>
    void
    Ideal<Element>::printMonomialAvl() const
    {
        cout << endl << "------------------- Monomial AVL -------------------------" << endl;
        NodeAvlMonomial const * itMonBeg = M_mons.findBiggest();
        while(itMonBeg != 0)
        {
            cout << itMonBeg->_numMonomial << ", lt = " << itMonBeg->_lt << endl;
            itMonBeg=M_mons.findNextBiggest(itMonBeg);
        }
        cout << endl << endl;
    }
            
    template <typename Element>
    void
    Ideal<Element>::printTaggedPolynomialAvl() const
    {
        cout << endl << "------------------- Tagged polynomial index AVL -------------------------" << endl;
        
        NodeAvlPolynomial const * itPolBeg = M.findBiggest(); 
        while(itPolBeg != 0)
        {
            cout << "_numPol = " << itPolBeg->_numPolynomial << ", NumLM = " << itPolBeg->_numMonomial << ", Number of terms = " << itPolBeg->_nbTerms << endl;
            itPolBeg=M.findNextBiggest(itPolBeg);
        }
    }
    
    template <typename Element>
    void
    Ideal<Element>::printMatrix (Matrix<Element> & mat, int *tabMon, int *sigma, string const & filename)
    {
        ofstream file(filename);
        int d;
        const string color[7] = { " 0 0 0 ", " 0 0 1 ", " 0 1 0 ", " 0 1 1 ", " 1 0 0 ", " 1 0 1 ", " 1 1 0 "};

        if (file)
        {
            file << "P3" << endl << mat.getWidth() << " " << mat.getHeight() << endl << 1 << endl;
            int i, j;
            for (i = 0; i < mat.getHeight(); i++)
            {
                for (j = 0; j < mat.getWidth(); j++)
                {
                    if (!mat.isZero(i,j))
                    {
                        d=_monomialArray[tabMon[sigma[j]]].getDegree();
                        file << color[d%7];
                    }
                    else
                    {
                        file << " 1 1 1 ";
                    }
                }
                file << endl;
            }
            file.close();
        }
        else
        {
            cout << "File open failed" << endl;
        }
    }
    
    
    /* Algorithms */
    
    template <typename Element>
    int
    Ideal<Element>::simplify (Monomial const & u, int numList) 
    {
        //cout << "--------------- simplify input---------------------" << endl;
        //cout << numList << ": " << _taggedPolynomialArray[numList]  << endl;
        //cout << numList << " x " << u  << ": " << (_taggedPolynomialArray[numList] * Monomial(u)) << endl << endl;
        
        clock_t start=clock();
        
        int numList_prev = numList;
        int i, j, k;
        int const * varlistU = u.getVarlist();
        
        int varlistTmp[_nbVariable];
        for(i=0; i<_nbVariable; i++)
        {
            varlistTmp[i]=varlistU[i];
        }
        
        for (i = _nbVariable - 1; i >= 0; i--)
        {
            for (j = 1; j <= varlistU[i]; j++)
            {
                if (_taggedPolynomialArray[numList].getSimplyrule(i) >= 0)
                {
                    numList = _taggedPolynomialArray[numList].getSimplyrule(i);
                    if (!_taggedPolynomialArray[numList].isEmpty())
                    {
                        numList_prev = numList;
                        varlistTmp[i]=varlistU[i]-j;
                        
                        for (k = i + 1; k < _nbVariable; k++)
                        {
                            varlistTmp[k]=0;
                        }
                    }
                }
                else
                {
                    _taggedPolynomialArray[numList].setSimplyrule(i, _numPol);
                    
                    /* Insert a new "empty" tagged polynomial in _taggedPolynomialArray */
                    _taggedPolynomialArray.emplace_back();
                    numList = _numPol;
                    _numPol++;
                }
            }
        }
        
        if (_taggedPolynomialArray[numList].isEmpty())
        {
            // Product does not exist => we create it.
            _taggedPolynomialArray[numList].setTaggedPolynomial(_taggedPolynomialArray[numList_prev], varlistTmp);
        }
        
        timeSimplify+=(clock()-start);
        
        //cout << "--------------- simplify output---------------------" << endl;
        //cout << numList << ": " << _taggedPolynomialArray[numList] << endl << endl;
        return numList;
    }
    
    template <typename Element>
    void 
    Ideal<Element>::update(int index, bool purge, Stat & stat)
    {
        size_t j; 
        bool divisorFound, div, strct1, strct2;
        clock_t startPurgeCp = 0;
        clock_t startAddCp = 0;
        clock_t startMajBasis = 0;
        
        NodeAvlCriticalPair<Element> * itcp1 = _criticalPairSet.findSmallest();
        NodeAvlCriticalPair<Element> * itcp2 = 0;
        
        CriticalPair<Element> cp1;
        CriticalPair<Element> sp;
        
        /* Strict divisibility criteria to avoid the problem of "eliminate 2 critical pairs over 3" */
        if (VERBOSE > 1)
        {
            startPurgeCp = clock ();
        }
        while(itcp1 != 0)
        {
            div = true;
            strct1 = false;
            strct2 = false;
            
            Monomial const & lt_f=_monomialArray[_taggedPolynomialArray[itcp1->_cp.getP1()].getLM()];
            Monomial const & lt_g=_monomialArray[_taggedPolynomialArray[itcp1->_cp.getP2()].getLM()];
            Monomial const & lcm=itcp1->_cp.getLcm();
            
            for (j = 0; j < (size_t)_nbVariable && div; j++)
            {
                if(_monomialArray.getNumVarlist(_taggedPolynomialArray[index].getLM(), j) < lcm.getVarlist(j) )
                {
                    if(lt_f.getVarlist(j) < lt_g.getVarlist(j))
                    {
                        strct1 = true;
                    }
                    else if (lt_f.getVarlist(j) > lt_g.getVarlist(j))
                    {
                        strct2 = true;
                    }
                }
                else
                {
                    if (_monomialArray.getNumVarlist(_taggedPolynomialArray[index].getLM(), j) > lcm.getVarlist(j) )
                    {
                        div=false;
                    }
                }
            }
            
            if (div && strct1 && strct2)
            {
                //cout << "Critical pair deleted " << endl;
                /* Suppress the critical pair */
                //_used[itcp1->getP1()]--;
                //_used[itcp1->getP2()]--;
                stat._nbCp--;
                itcp1=_criticalPairSet.erase(itcp1);
                
            }
            else
            {
                itcp1=_criticalPairSet.findNextSmallest(itcp1);
            }
        }
        
        if (VERBOSE > 1)
        {
            stat._timePurgeCp += (clock () - startPurgeCp);
            startAddCp = clock ();
        }

        /* Computation of critical pairs */ 
        for (j = 0; j < _basis.size(); j++)
        {
            if (!sp.setCriticalPair(index, _total[_basis[j]]))
            {
                //cout << "Insert int _cpSet0, sp = " << sp << endl;
                _cpSet0.insert(sp);
            }
            else
            {
                //cout << "Insert int _cpSet1, sp = " << sp << endl;
                _cpSet1.insert(sp);
            }
        }
        
        itcp1=_cpSet1.findSmallest();
        while(itcp1 != 0)
        {
            cp1=itcp1->_cp;
            itcp1=_cpSet1.findNextSmallest(itcp1);
            
            /* Test if cp1 verifies criteria 2 */
            divisorFound = false;
            
            /* Scan _cpSet0 */
            itcp2=_cpSet0.findSmallest();
            while (itcp2 != 0 && !divisorFound)
            {
                if ((cp1.getLcm()).isDivisible(itcp2->_cp.getLcm()))
                {
                    divisorFound = true;
                }
                itcp2=_cpSet0.findNextSmallest(itcp2);
            }
            
            /* Scan _cpSet1 */
            itcp2=itcp1;
            while (itcp2 != 0 && !divisorFound)
            {
                if ((cp1.getLcm()).isDivisible(itcp2->_cp.getLcm()))
                {
                    divisorFound = true;
                }
                itcp2=_cpSet1.findNextSmallest(itcp2);
            }
            
            /* Scan _cpSet2 */
            itcp2=_cpSet2.findSmallest();
            while (itcp2 != 0 && !divisorFound)
            {
                if ((cp1.getLcm()).isDivisible(itcp2->_cp.getLcm()))
                {
                    divisorFound = true;
                }
                itcp2=_cpSet2.findNextSmallest(itcp2);
            }
            if (!divisorFound)
            {
                /* Add cp1 to _cpSet2 */
                _cpSet2.insert(cp1);
            }
        }
        _cpSet1.reset();
        
        /* CP <- CP U _cpSet2 */
        itcp1=_cpSet2.findSmallest();
        while(itcp1!=0)
        { 
            //_used[itcp1->getP1()]++;
            //_used[itcp1->getP2()]++;
            _criticalPairSet.insert(itcp1->_cp);
            itcp1=_cpSet2.findNextSmallest(itcp1);
            stat._nbCp++;
        }
        _cpSet2.reset();
        
        /* Free _cpSet0 */
        _cpSet0.reset();
        
        if (VERBOSE > 1)
        {
            stat._timeAddCp +=(clock () - startAddCp);
            startMajBasis = clock ();
        }
        /* End of critical pair computation */
        
        if(purge)
        {
            /* Purge of generators */
            divisorFound = false;
            Monomial const & lt_f=_monomialArray[_taggedPolynomialArray[index].getLM()];
            for (j = 0; j < _basis.size(); j++)
            {
                if (lt_f.isDivisible(_monomialArray[_taggedPolynomialArray[_total[_basis[j]]].getLM()]))
                {
                    divisorFound = true;
                    //_used[index]--;
                    break;
                }
            }
            if (!divisorFound)
            {
                /* Add the polynomial in _basis */
                _basis.push_back(_numTot);
                _numGen++;
                /* purge of _basis by the new polynomial */
                for (j = 0; j < _basis.size()-1; j++)
                {
                    if (_monomialArray[_taggedPolynomialArray[_total[_basis[j]]].getLM()].isDivisible(lt_f))
                    { 
                        //_used[_total[_basis[j]]]--;
                        _basis.erase(_basis.begin()+j);
                        _numGen--;
                        stat._cmptGenPurg++;
                        j--;
                    }
                }
            }
        }
        else
        {
            Monomial const & lt_f=_monomialArray[_taggedPolynomialArray[index].getLM()];
            /* Add the polynomial in _basis */
            _basis.push_back(_numTot);
            _numGen++;
            /* Purge of _basis by the new polynomial */
            for (j = 0; j < _basis.size()-1; j++)
            {
                if (_monomialArray[_taggedPolynomialArray[_total[_basis[j]]].getLM()].isDivisible(lt_f))
                { 
                    //_used[_total[_basis[j]]]--;
                    _basis.erase(_basis.begin()+j);
                    _numGen--;
                    stat._cmptGenPurg++;
                    j--;
                }
            }
        }
        if (VERBOSE > 1)
        {
            stat._timeMajBasis +=(clock () - startMajBasis);
        }
    }
    
    template <typename Element>
    void 
    Ideal<Element>::appendMatrixF4 (CriticalPair<Element> & p, int & h, int & nbPiv)
    {
        NodeList<Element> const * itTerm;
        
        int u1p1=simplify(p.getU1(), p.getP1()); 
        
        if(M.insert(u1p1, (_taggedPolynomialArray[u1p1]).getLM(), (_taggedPolynomialArray[u1p1]).getNbTerm())!=1)
        {
            /* If u1p1 is not already in M we insert its monomials in M_Mons */
            itTerm=_taggedPolynomialArray[u1p1].getPolynomialBeginConst();

            if(M_mons.insert(itTerm->getNumMonomial(), true) != 1)
            {
                nbPiv++;
            }
            itTerm=itTerm->_next;
            while(itTerm)
            {
                /* Insert the other monomials */
                M_mons.insert(itTerm->getNumMonomial(), false);
                itTerm=itTerm->_next;
            }
            h++;
        }
        
        int u2p2=simplify(p.getU2(), p.getP2());
        
        if(M.insert(u2p2, (_taggedPolynomialArray[u2p2]).getLM(), (_taggedPolynomialArray[u2p2]).getNbTerm())!=1)
        {
            /* If u2p2 is not already in M we insert its monomials in M_Mons */
            itTerm=_taggedPolynomialArray[u2p2].getPolynomialBeginConst();
            M_mons.insert(itTerm->getNumMonomial(), true);
            itTerm=itTerm->_next;
            while(itTerm)
            {
                /* Insert the other monomials */
                M_mons.insert(itTerm->getNumMonomial(), false);
                itTerm=itTerm->_next;
            }
            h++;
        }
    }
    
    template <typename Element>
    double 
    Ideal<Element>::transform(Matrix<Element> & mat, int *tabMon, int nbPiv, int *tau, int *sigma, int *startTail, int *endCol)
    {
        int height=mat.getHeight();
        int width=mat.getWidth();
        int nb = 0;                 /* for sparsitude */
        int icur, ih, ib, j;
        int c = 0;                  /* Column of the last lt */
        
        /* Iterators on M_mons, M, and polynomials */
        NodeAvlMonomial * itMonBeg = 0;
        NodeAvlPolynomial * itPolBeg = 0;
        NodeList<Element> const * itTerm;
        
        /* Temporary */
        int numMon;
        int numMonLT;

        /* Unroll the AVL of monomial into an array */
        ih = 0;
        ib = nbPiv;
        icur = 0;

        /* We take the biggest monomial of M_mons */
        itMonBeg=M_mons.findBiggest();
        do
        {
            if (itMonBeg->_lt == true)
            {
                sigma[ih] = icur;
                tau[icur] = ih;
                startTail[ih] = ib;
                ih++;
            }
            else
            {
                sigma[ib] = icur;
                tau[icur] = ib;
                endCol[ib] = ih;
                ib++;
            }
            tabMon[icur]=itMonBeg->_numMonomial;
            icur++;
            itMonBeg=M_mons.findNextBiggest(itMonBeg);
        }
        while(itMonBeg != 0);
        if (icur != width)
        {
            cout << "***pb depliage M_mons dans Transform***" << endl;
            cout << "icur = " << icur << ", width = " << width << endl;
        }

        /* Fill the matrix with a triangular shape */
        itPolBeg=M.findBiggest();
        itTerm=_taggedPolynomialArray[itPolBeg->_numPolynomial].getPolynomialBeginConst();
            
        ih = 0;
        ib = nbPiv;
        
        /* Process first polynomial apart */
        numMonLT=itTerm->getNumMonomial();
        j = c;
        mat.setElement(0,tau[j], itTerm->getCoefficient());
        nb++;
        j++;
        itTerm=itTerm->_next;
        while(itTerm)
        {
            /* Search column */
            numMon = itTerm->getNumMonomial();
            while ( numMon != tabMon[j])
            {
                j++;
            }
            mat.setElement(0, tau[j], itTerm->getCoefficient());
            j++;
            nb++;
            itTerm=itTerm->_next;
        }
        ih++;
        //on garde seulement le lt de pol, on met le reste dans POL_FL
        //if (List[tmp_polEt->numList].poly->next != NULL)
        //{
            //pol_end->next = Pol_FL;
            //Pol_FL = List[tmp_polEt->numList].poly->next;
            //List[tmp_polEt->numList].poly->next = NULL;
        //}
        itPolBeg=M.findNextBiggest(itPolBeg);
        
        /* Process other polynomials */
        while(itPolBeg != 0)
        {
            itTerm=_taggedPolynomialArray[itPolBeg->_numPolynomial].getPolynomialBeginConst();
            
            if(itTerm->getNumMonomial()==numMonLT)
            {
                /* Place the polynomial in the upper part of the matrix */
                mat.setElement(ib, tau[c], itTerm->getCoefficient());
                j = c;
                nb++;
                j++;
                itTerm=itTerm->_next;
                
                while(itTerm)
                {
                    /* Search column */
                    numMon = itTerm->getNumMonomial() ;
                    while(numMon != tabMon[j])
                    {
                        j++;
                    }
                    mat.setElement(ib, tau[j], itTerm->getCoefficient());
                    j++;
                    nb++;
                    itTerm=itTerm->_next;
                }
                ib++;
            }
            else
            {
                /* Place the polynomial in the lower part of the matrix */
                endCol[tau[c]] = ib;
                numMonLT = itTerm->getNumMonomial();
                
                while (numMonLT != tabMon[c])
                {
                    c++;
                }
                
                j = c;
                
                mat.setElement(ih, tau[j], itTerm->getCoefficient());
                nb++;
                j++;
                itTerm=itTerm->_next;
                while(itTerm)
                {
                    /* Search column */
                    numMon=itTerm->getNumMonomial();
                    while (numMon != tabMon[j])
                    {
                        j++;
                    }
                    mat.setElement(ih, tau[j], itTerm->getCoefficient());
                    j++;
                    nb++;
                    itTerm=itTerm->_next;
                }
                ih++;
            }
            itPolBeg=M.findNextBiggest(itPolBeg);

            ////lib du pol de la ligne
            //if (List[tmp_polEt->numList].poly->next != NULL)
            //{
                //pol_end->next = Pol_FL;
                //Pol_FL = List[tmp_polEt->numList].poly->next;
                //List[tmp_polEt->numList].poly->next = NULL;
            //}
        }
        endCol[nbPiv - 1] = ib;
        return ((double)nb) * 100. / ((double)width * (double)height);

    }
    
    template <typename Element>
    Polynomial<Element>
    Ideal<Element>::buildPolynomial (Element * row, int *tabMon, int width, int start, int *tau)
    {
        Polynomial<Element> res;
        NodeList<Element> * pos = res.getPolynomialBegin();
        
        for (int j = start; j < width; j++)
        {
            if (!row[tau[j]].isZero())
            {
                pos=res.emplaceAfter(pos, row[tau[j]], tabMon[j]);
            }
        }
        if(res.isEmpty())
        {
            cout << "Row empty --> see echelonize" << endl;
        }
        return res;
    }
    
    template <typename Element>
    void
    Ideal<Element>::buildPolynomial (Polynomial<Element> & res, Element * row, int *tabMon, int width, int start, int *tau)
    {
        //NodeList<Element> * tmp = 0;
        res.clear();
        NodeList<Element> * pos = res.getPolynomialBegin();
        for (int j = start; j < width; j++)
        {
            if (!row[tau[j]].isZero())
            {
                //pos=res.emplaceOn(pos, row[tau[j]], tabMon[j]);
                //tmp=pos;
                //pos=pos->_next;
                pos=res.emplaceAfter(pos, row[tau[j]], tabMon[j]);
            }
        }
        //res.deleteAfter(tmp);
        if(res.isEmpty())
        {
            cout << "Row empty --> see echelonize" << endl;
        }
    }
    
    template <typename Element>
    void
    Ideal<Element>::preprocessing(int & width, int & height, int & nbPiv) 
    {
        int indexPol;
        int i;
        Monomial quotient;
        quotient.allocate();
        NodeList<Element> const * itTerm;
        NodeAvlMonomial * itmon;
        width = 0;
        
        /* Search the biggest monomial in M_mons which is not a leading monomial */
        itmon=M_mons.findBiggest();
        width++;
        while (itmon != 0 && itmon->_lt == true)
        {
            itmon=M_mons.findNextBiggest(itmon);
            width++;
        }
        while(itmon != 0)
        {
            Monomial const & m1=_monomialArray[itmon->_numMonomial];
            /* Search reducer in the basis */
            for (i = _numGen - 1; i >= 0; i--)
            {
                Monomial const & m2=_monomialArray[_taggedPolynomialArray[_total[_basis[i]]].getLM()];
                if(m1.isDivisible(m2))
                {
                    quotient.setMonomialDivide(m1,m2);
                    /* Reducer found */
                    itmon->_lt=true;
                    nbPiv++;
                    /* Test if the computation of this multiple is not already done */ 
                    indexPol=simplify(quotient, _total[_basis[i]]);
                    /* Add the multiple in M */
                    M.insert(indexPol, (_taggedPolynomialArray[indexPol]).getLM(), (_taggedPolynomialArray[indexPol]).getNbTerm());
                    height++;
                    /* Insert monomials of the new polynomial in M_mons */
                    itTerm=_taggedPolynomialArray[indexPol].getPolynomialBeginConst();
                    itTerm=itTerm->_next;
                    while(itTerm)
                    {
                        M_mons.insert(itTerm->getNumMonomial(), false);
                        itTerm=itTerm->_next;
                    }
                    break;
                }
            }
            /* End search */
            do
            {
                itmon=M_mons.findNextBiggest(itmon);
                width++;
            }
            while (itmon != 0 && itmon->_lt == true);
        }
        width--;
        quotient.erase();
    }
    
    
    
    template <typename Element>
    bool
    Ideal<Element>::postprocessing(Matrix<Element> & matrix, int * tabMon, int * sigma, int * tau, int height, int width, int heightReal, int nbPiv, Stat & stat) 
    {
        /* Iterators */
        NodeAvlPolynomial * itPolBeg = M.findBiggest();
        int num_lt, i;
        for (i = 0; i < nbPiv; i++)
        {
            num_lt = tabMon[sigma[i]];
            if(itPolBeg->_numMonomial != num_lt)
            {
                cout << "Wrong lt in postprocessing " << endl;
            }
            while( (itPolBeg != 0) && (itPolBeg->_numMonomial==num_lt) )
            {
                //_taggedPolynomialArray[itPolBeg->_numPolynomial].setPolynomial(buildPolynomial(matrix.getRow(i), tabMon, width, sigma[i], tau));
                buildPolynomial(_taggedPolynomialArray[itPolBeg->_numPolynomial].getPolynomial(), matrix.getRow(i), tabMon, width, sigma[i], tau);
                itPolBeg=M.findNextBiggest(itPolBeg);
            }
        }
        for (i = nbPiv; i < heightReal; i++)
        {
            /* Create new generators */
            num_lt = tabMon[sigma[i]];
            if (tabMon[sigma[i]] == 0)
            {
                return false;
            }
            if (VERBOSE > 2)
            {
                if (tabMon[sigma[i]] <= _nbVariable)
                {
                    cout << endl << "!! Polynom of degree 1: P[" << _numPol - 1 << " = " << _taggedPolynomialArray[_numPol-1] << " !! " << endl;
                }
            }
            /* Update the set of critical pairs and the current basis */
            _taggedPolynomialArray.emplace_back(buildPolynomial(matrix.getRow(i), tabMon, width, sigma[i], tau));
            if (VERBOSE > 3)
            {
                cout << endl << "_total[" << _numTot << "] = " << _taggedPolynomialArray[_numPol] << endl;
            }
            /* Add the new generator in the basis */
            _total.push_back(_numPol);
            _used.push_back(1);
            update(_numPol, false, stat);
            _numPol++;
            _numTot++;
            stat._cmptNewGen++;
        }
        return true;
    }
    
    
    /* F4 Algorithm */
    
    template <typename Element>
    int 
    Ideal<Element>::f4()
    {
        /* Iterators */
        NodeAvlPolynomial * itPolBeg = 0;
        NodeList<Element> const * itTerm;
        NodeAvlCriticalPair<Element> * itcp1;
        
        /* F4 matrix */
        Matrix<Element> mat;
        
        /* Temporary critical pair */
        CriticalPair<Element> cp1;
        
        /* Filename to print matrices */
        string filename;
        
        int i;
        int step = 0;
        int d;
        int num_lt;
        
        if(VERBOSE > 3)
        {
            cout << "Number of equations: " << _polynomialArray.size() << endl;
            for(typename vector<Polynomial<Element>>::const_iterator it=_polynomialArray.begin(); it != _polynomialArray.end(); ++it)
            {
                cout << *it << endl;
            }
            cout << endl;
        }

        /* For convertion under matrix for */
        int *tabMon;               /* Monomial array */
        int nbPiv;                 /* We set the pivots in the upper part of mat, after nbPiv, polynomials can be some new generators */
        int *tau;                   /* sigma(tau(i))=tau(sigma(i))=i */
        int *sigma;                 /* To get mat under triangular shape, we permute some columns */
        int *startTail;            /* startTail[i] = min{j>=nbPiv : sigma[i]<sigma[j]} */
        int *endCol;               

        /* For preprocessing */
        int height, width, heightReal, index;
        
        /* Percentage of non zero coefficient in mat */
        double sparse;
        
        /* Counters */
        _numGen = 0;             /* Number of polynomials in the groebner basis */
        _numPol = 0;             /* Number of polynomials in _taggedPolynomialArray */
        _numTot = 0;             /* Number of polynomials used to update the basis and the critical pairs set */

        /* Statistic */
        Stat stat;
        
        clock_t start = 0;
        clock_t start2 = 0;
        clock_t start1 = clock ();
        
        clock_t timeClear = 0;
        clock_t timeClearStart = 0;
        clock_t timeAppendMatrixF4 = 0;
        clock_t timeAppendMatrixF4Start = 0;
        clock_t timePreprocessing = 0;
        clock_t timePreprocessingStart = 0;
        clock_t timeTransform = 0;
        clock_t timeTransformStart = 0;
        clock_t timePostprocessing = 0;
        clock_t timePostprocessingStart = 0;
        
        /*step 0 */
        for (size_t i = 0; i < _polynomialArray.size(); i++)
        {
            _polynomialArray[i].normalize();
            _taggedPolynomialArray.emplace_back(_polynomialArray[i]);
            _total.push_back(_numPol);
            _used.push_back(1);

            /* Initialisation : compute all the critical pairs and purge of the basis */
            update(i, true, stat);
            _numPol++;
            _numTot++;
        }
        step++;
        
        /* Main loop on critical pairs */
        while (!_criticalPairSet.isEmpty())
        {
            if (VERBOSE > 0)
            {
                cout << endl << "---------------------------------------" << endl;
                cout << "--------------- STEP " << step << " ---------------" << endl;
                cout << "---------------------------------------" << endl;
            }
            
            //cout << "DEBUG " << endl;
            //cout << "_numPol: " << _numPol << " _taggedPolynomialArray size: " << _taggedPolynomialArray.size() << endl;
            //cout << "_numTot: " << _numTot << " _total size: " << _total.size() << " _used size: " << _used.size() << endl;
            //cout << "_numGen: " << _numGen << " _basis size: " << _basis.size() << endl << endl;
            
            if (VERBOSE > 1)
            {
                start2 = clock ();
            }
            M_mons.reset();
            
            /* Construction of critical pairs with minimal degree */
            height = 0;
            nbPiv = 0;
            stat._nbCpDeg = 0;
            
            if(VERBOSE > 1)
            {
                /* Time spent in appendMatrixF4 */
                timeAppendMatrixF4Start=clock();
            }
            
            /* Critical pair of minimal degree */
            itcp1=_criticalPairSet.findSmallest();
            cp1=itcp1->_cp;
            itcp1=_criticalPairSet.erase(itcp1);
            
            stat._nbCp--;
            d = cp1.getDegree();

            if (VERBOSE > 0)
            {
                cout << "Step degree: " << d << ", Basis length: " << _numGen << ", Pairs queue length " << stat._nbCp+1 << endl << endl;
            }
            if (VERBOSE > 1)
            {
                /* Matrix construction time */
                start = clock ();   
            }

            appendMatrixF4 (cp1, height, nbPiv);
            //recuperation du noeud
            //_used[cp1.getP1()]--;
            //_used[cp1.getP2()]--;
            stat._nbCpDeg++;

            /* Get the other critical pairs of degree d */
            while ( (itcp1 != 0) && (itcp1->_cp.getDegree()==d))
            {
                cp1=itcp1->_cp;
                itcp1=_criticalPairSet.erase(itcp1);
                stat._nbCp--;
                appendMatrixF4 (cp1, height, nbPiv);
                stat._nbCpDeg++;
                //recuperation du noeud de la cp
                //_used[cp1.getP1()]--;
                //_used[cp1.getP2()]--;
            }
            if(VERBOSE > 1)
            {
                timeAppendMatrixF4 +=(clock () - timeAppendMatrixF4Start);
            }
            
            if (VERBOSE > 0)
            {
                cout << "Construction of M: " << endl;
                cout << "Number of selected pairs: " << stat._nbCpDeg << endl;
                cout << "Number of polynomials: " << height << endl;
                cout << "Number of monomials: " << M_mons.size() << endl << endl;
            }
            
            /* Preprocessing of M */
            if(VERBOSE > 1)
            {
                timePreprocessingStart=clock();
            }
            preprocessing(width, height, nbPiv);
            if(VERBOSE > 1)
            {
                timePreprocessing +=(clock () - timePreprocessingStart);
            }
        
            /* Transform M into a matrix */
            if (VERBOSE > 0)
            {
                cout << "Preprocessing of M: " << endl;
                cout << "Height: " << height << ", Width :" << width << ", Number of pivots: " << nbPiv << endl << endl;
            }
            
            mat=Matrix<Element>(height, width);
            tabMon = new int[width];
            tau = new int[width];
            sigma = new int[width];
            startTail = new int[height];
            endCol = new int[width];
            
            /* Time spent in transform */
            if(VERBOSE > 1)
            {
                timeTransformStart = clock();
            }
            sparse = transform (mat, tabMon, nbPiv, tau, sigma, startTail, endCol);
            if(VERBOSE > 1)
            {
                timeTransform +=(clock () - timeTransformStart);
            }
            
            //filename=to_string(step)+"before-echelonize.pgm";
            //printMatrix(mat, tabMon, sigma, filename);
            
            if (VERBOSE > 0)
            {
                cout << "Convert M into a matrix: " << endl;
                cout << "Matrix size: " << height << "x" << width << endl;
                cout << "Matrix density: " << sparse << endl;
                cout << "Construction time: " << (((double)clock () - start) * 1000) / CLOCKS_PER_SEC << " ms" << endl << endl;
            }

            /* Triangularisation of mat */
            mat.setInfo(nbPiv, tau, sigma, startTail, endCol);
            heightReal=mat.echelonize();
            
            //filename=to_string(step)+"after-echelonize.pgm";
            //printMatrix(mat, tabMon, sigma, filename);
            
            if (VERBOSE > 0)
            {
                /* Update time */
                start = clock ();
            }
            if (VERBOSE > 1)
            {
                stat._timePurgeCp = 0;
                stat._timeAddCp = 0;
                stat._timeMajBasis = 0;
            }

            /* Rebuild M from mat */
            /* Count new generators */
            stat._cmptNewGen=0;
            /* Count purged generators */
            stat._cmptGenPurg=0;
            
            /* Time spent in postProcessing */
            if(VERBOSE > 1)
            {
                timePostprocessingStart = clock();
            }
            if(!postprocessing(mat, tabMon, sigma, tau, height, width, heightReal, nbPiv, stat))
            {
                cout << endl << endl << "GROEBNER BASIS : (1)" << endl;
                cout << "---> " << (((double)clock () - start1) * 1000) / CLOCKS_PER_SEC << " ms " << endl << endl << endl;
                
                if(M_mons.size() != (size_t)width)
                {
                    cout << "*** Problem in width computation: size of M_mons = " << M_mons.size() << ", width = " << width << " ***" << endl;
                }
                M_mons.reset();
                if(M.size() != (size_t)height) 
                {
                    cout << "*** Problem in height computation: size of M = " << M.size() << ", height = " << height << " ***" << endl << endl;
                }
                M.reset();
 
                delete[] tabMon;
                delete[] tau;
                delete[] sigma;
                delete[] startTail;
                delete[] endCol;
                return 0;
            }
            if(VERBOSE > 1)
            {
                timePostprocessing+=(clock()-timePostprocessingStart);
            }
            
            if (VERBOSE > 0)
            {
                cout << "Update of _basis and queue of pairs done in " << (((double)clock () - start) * 1000) / CLOCKS_PER_SEC << " ms" << endl;
                if (VERBOSE > 1)
                {
                    cout << "--> " << (stat._timePurgeCp* 1000) / CLOCKS_PER_SEC << " ms for purging of the critical pairs queue" << endl;
                    cout << "--> " << (stat._timeAddCp* 1000) / CLOCKS_PER_SEC << " ms for updating critical pairs " << endl;
                    cout << "--> " << (stat._timeMajBasis* 1000) / CLOCKS_PER_SEC << " ms for updating groebner basis " << endl;
                }
                if (heightReal != height)
                {
                    cout << "** " << height - heightReal << " reductions to zero **" << endl << endl;
                }
            }
            
            /* Reset the AVL of monomials and tagged polynomials */
            timeClearStart=clock();
            M_mons.reset();
            M.reset();
            timeClear+=(clock()-timeClearStart);
            
            if (stat._cmptNewGen != (heightReal - nbPiv))
            {
                cout << "*** erreur dans le comptage des nouveaux generateurs ***" << endl;
            }

            if (VERBOSE > 0)
            {
                cout << "Basis length: " << _numGen << " (" << stat._cmptNewGen << " new gen and " << stat._cmptGenPurg << " purged) " << endl << endl;
            }
                
            if (VERBOSE > 0)
            {
                cout << "Total computation time of step " << step << ": " << (((double)clock () - start2) * 1000) / CLOCKS_PER_SEC << " ms" << endl << endl; 
            }
            step++;
            
            delete[] tabMon;
            delete[] tau;
            delete[] sigma;
            delete[] startTail;
            delete[] endCol;
        }
        /* End of critical pair loop */
        
        if(VERBOSE > 1)
        {
            cout << endl << "---------------------------------------" << endl;
            cout << "Time analysis: " << endl;
            cout << "---> " << (((double)clock () - start1) * 1000) / CLOCKS_PER_SEC << "ms CPU global computation time" << endl;
            cout << "---> " << (((double)timeClear) * 1000) / CLOCKS_PER_SEC << "ms CPU used for clear" << endl;
            cout << "---> " << (((double)timeAppendMatrixF4) * 1000) / CLOCKS_PER_SEC << "ms CPU used for appendMatrixF4" << endl;
            cout << "---> " << (((double)timePreprocessing) * 1000) / CLOCKS_PER_SEC << "ms CPU used for preprocessing" << endl;
            cout << "---> " << (((double)timeTransform) * 1000) / CLOCKS_PER_SEC << "ms CPU used for transform" << endl;
            cout << "---> " << (((double)timePostprocessing) * 1000) / CLOCKS_PER_SEC << "ms CPU used for postprocessing" << endl;
            cout << "---> " << (((double)timeSimplify) * 1000) / CLOCKS_PER_SEC << "ms CPU used for simplify" << endl << endl << endl;
            
            cout << "_numPol: " << _numPol << " _taggedPolynomialArray size: " << _taggedPolynomialArray.size() << endl;
            cout << "_numTot: " << _numTot << " _total size: " << _total.size() << " _used size: " << _used.size() << endl;
            cout << "_numGen: " << _numGen << " _basis size: " << _basis.size() << endl << endl;
        }
        
        /* Reduced the basis */
        if (VERBOSE > 0)
        {
            cout << endl << "---------------------------------------" << endl;
            cout << "Reducing the basis..." << endl;
        }

        width = 0;
        height = 0;
        
        for (i = 0; i < _numGen; i++)
        {
            index=_total[_basis[i]];
            M.insert(index, (_taggedPolynomialArray[index]).getLM(), (_taggedPolynomialArray[index]).getNbTerm());
            itTerm=_taggedPolynomialArray[index].getPolynomialBeginConst();
            M_mons.insert(itTerm->getNumMonomial(), true);
            itTerm=itTerm->_next;
            while(itTerm)
            {
                M_mons.insert(itTerm->getNumMonomial(), false);
                itTerm=itTerm->_next;
            }
            height++;
        }
        
        /* Preprocessing */
        preprocessing(width, height, nbPiv);
        nbPiv = height;
        
        /* Transform M into a matrix */
        if (VERBOSE > 0)
        {
            cout << "Preprocessing of M: " << endl;
            cout << "Height: " << height << ", Width :" << width << ", Number of pivots: " << nbPiv << endl << endl;
        }
            
        mat=Matrix<Element>(height, width);
        tabMon = new int[width];
        tau = new int[width];
        sigma = new int[width];
        startTail = new int[height];
        endCol = new int[width];
        
        sparse = transform (mat, tabMon, nbPiv, tau, sigma, startTail, endCol);
        
        if (VERBOSE > 1)
        {
            cout << "Matrix size: " << height << "x" << width << endl;
            cout << "Matrix density: " << sparse << endl;
            cout << "Construction time: " << (((double)clock () - start) * 1000) / CLOCKS_PER_SEC << " ms" << endl;
        }

        /* Triangularisation of mat */
        mat.setInfo(nbPiv, tau, sigma, startTail, endCol);
        heightReal=mat.echelonize();

        /* Retrieve generators of the minimal basis */
        itPolBeg = M.findBiggest();
        for (i = 0; i < nbPiv; i++)
        {
            num_lt = tabMon[sigma[i]];
            if(itPolBeg->_numMonomial != num_lt)
            {
                cout << "Wrong lt in postprocessing " << endl;
            }
            while( (itPolBeg != 0) && (itPolBeg->_numMonomial==num_lt) )
            {
                //_taggedPolynomialArray[itPolBeg->_numPolynomial].setPolynomial(buildPolynomial(mat.getRow(i), tabMon, width, sigma[i], tau));
                buildPolynomial(_taggedPolynomialArray[itPolBeg->_numPolynomial].getPolynomial(), mat.getRow(i), tabMon, width, sigma[i], tau);
                itPolBeg=M.findNextBiggest(itPolBeg);
            }
        }
        if(M_mons.size() != (size_t)width)
        {
            cout << "*** Problem in width computation ***" << endl;
        }
        M_mons.reset();
        if(M.size() != (size_t)height) 
        {
            cout << "*** Problem in height computation ***" << endl << endl;
        }
        M.reset();

        delete[] tabMon;
        delete[] tau;
        delete[] sigma;
        delete[] startTail;
        delete[] endCol;
        
        cout << "Groebner basis: " << _numGen << " generators. Computed in " << (((double)clock () - start1) * 1000) / CLOCKS_PER_SEC << "ms CPU " << endl << endl << endl;

        return _numGen;
    }

}

#endif // F4_IDEAL_INL
