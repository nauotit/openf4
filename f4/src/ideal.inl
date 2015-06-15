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
    Ideal<Element>::Ideal(std::vector<Polynomial<Element>> & polynomialArray, int nbVariable, int capacity, int degree): _polynomialArray(polynomialArray), _nbVariable(Monomial::getNbVariable()), _numPol(0), _numTot(0), _numGen(0), _monomialArray(nbVariable, capacity, degree), _cpArray(1000, 20,1)
    {
        /* Share the monomial array. */
        Term<Element>::setMonomialArray(&_monomialArray);
        TaggedPolynomial<Element>::setMonomialArray(&_monomialArray);
        CriticalPair<Element>::setMonomialArray(&_monomialArray);
        /* Share the tagged polynomial array. */
        CriticalPair<Element>::setTaggedPolynomialArray(&_taggedPolynomialArray);
        
        _taggedPolynomialArray.reserve(50000);
        _total.reserve(10000);
        _basis.reserve(1000);
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
    vector<string>
    Ideal<Element>::getReducedGroebnerBasis() const
    {
        ostringstream stream;
        vector<string> basis;
        for(int i = 0; i < _numGen; i++)
        {
            stream << _taggedPolynomialArray[_total[_basis[i]]].getPolynomialConst();
            basis.push_back(stream.str());
            stream.str("");
            stream.clear();
        }
        return basis;
    }
    
    template <typename Element>
    void
    Ideal<Element>::printReducedGroebnerBasis(string const filename, int64_t modulo) const
    {
        ofstream file(filename);
        if (file)
        {
            file << "FF:=FiniteField(" << (uint64_t)modulo << ");" << endl;
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
        NodeAvlMonomial const * itMonBeg = _matMons.findBiggest();
        while(itMonBeg != 0)
        {
            cout << itMonBeg->_numMonomial << ", lt = " << itMonBeg->_lt << endl;
            itMonBeg=_matMons.findNextBiggest(itMonBeg);
        }
        cout << endl << endl;
    }
            
    template <typename Element>
    void
    Ideal<Element>::printTaggedPolynomialAvl() const
    {
        cout << endl << "------------------- Tagged polynomial index AVL -------------------------" << endl;
        
        NodeAvlPolynomial const * itPolBeg = _matPols.findBiggest(); 
        while(itPolBeg != 0)
        {
            cout << "_numPol = " << itPolBeg->_numPolynomial << ", NumLM = " << itPolBeg->_numMonomial << ", Number of terms = " << itPolBeg->_nbTerms << endl;
            itPolBeg=_matPols.findNextBiggest(itPolBeg);
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
        
        int numList_prev = numList;
        int i, j, k;
        uint8_t const * varlistU = u.getVarlist();
        
        uint8_t varlistTmp[_nbVariable];
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
            /* Product does not exist => we create it. */
            _taggedPolynomialArray[numList].setTaggedPolynomial(_taggedPolynomialArray[numList_prev], varlistTmp);
        }
        
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
                /* Suppress the critical pair */
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
        
        CriticalPair<Element> * cp1=0;
        CriticalPair<Element> * it = _cpArray.getBegin();

        /* Computation of critical pairs */ 
        for (j = _basis.size(); j > 0; j--)
        {
            if (!it->setCriticalPair(index, _total[_basis[j-1]]))
            {
                _cpSet0.insert(it);
            }
            else
            {
                _cpSet1.insert(it);
            }
            it=_cpArray.getNext(it);
        }

        
        NodeListPointerCriticalPair<Element> const * itpcp1;
        NodeListPointerCriticalPair<Element> const * itpcp2 = 0;
        
        itpcp1=_cpSet1.getRoot();
        while(itpcp1 != 0)
        {
            cp1=(itpcp1->_cp);
            itpcp1=_cpSet1.getNext(itpcp1);
            
            /* Test if cp1 verifies criteria 2 */
            divisorFound = false;
            
            /* Scan _cpSet0 */
            itpcp2=_cpSet0.getRoot();
            while (itpcp2 != 0 && !divisorFound)
            {
                if ((cp1->getLcm()).isDivisible(itpcp2->_cp->getLcm()))
                {
                    divisorFound = true;
                }
                itpcp2=_cpSet0.getNext(itpcp2);
            }
            
            /* Scan _cpSet1 */
            itpcp2=itpcp1;
            while (itpcp2 != 0 && !divisorFound)
            {
                if ((cp1->getLcm()).isDivisible(itpcp2->_cp->getLcm()))
                {
                    divisorFound = true;
                }
                itpcp2=_cpSet1.getNext(itpcp2);
            }
            
            /* Scan _cpSet2 */
            itpcp2=_cpSet2.getRoot();
            while (itpcp2 != 0 && !divisorFound)
            {
                if ((cp1->getLcm()).isDivisible(itpcp2->_cp->getLcm()))
                {
                    divisorFound = true;
                }
                itpcp2=_cpSet2.getNext(itpcp2);
            }
            if (!divisorFound)
            {
                /* Add cp1 to _cpSet2 */
                _cpSet2.insert(cp1);
            }
        }
        _cpSet1.reset();
        
        /* CP <- CP U _cpSet2 */
        itpcp1=_cpSet2.getRoot();
        while(itpcp1!=0)
        { 
            _criticalPairSet.insert(*itpcp1->_cp);
            itpcp1=_cpSet2.getNext(itpcp1);
            stat._nbCp++;
        }
        _cpSet2.reset();
        
        /* Free _cpSet0 */
        _cpSet0.reset();
        
        /* Reset the dynamic array of critical pair */
        _cpArray.reset();
        
        
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
        
        if(_matPols.insert(u1p1, (_taggedPolynomialArray[u1p1]).getLM(), (_taggedPolynomialArray[u1p1]).getNbTerm())!=1)
        {
            /* If u1p1 is not already in _matPols we insert its monomials in M_Mons */
            itTerm=_taggedPolynomialArray[u1p1].getPolynomialBeginConst();

            if(_matMons.insert(itTerm->getNumMonomial(), true) != 1)
            {
                nbPiv++;
            }
            itTerm=itTerm->_next;
            while(itTerm)
            {
                /* Insert the other monomials */
                _matMons.insert(itTerm->getNumMonomial(), false);
                itTerm=itTerm->_next;
            }
            h++;
        }
        
        int u2p2=simplify(p.getU2(), p.getP2());
        
        if(_matPols.insert(u2p2, (_taggedPolynomialArray[u2p2]).getLM(), (_taggedPolynomialArray[u2p2]).getNbTerm())!=1)
        {
            /* If u2p2 is not already in _matPols we insert its monomials in M_Mons */
            itTerm=_taggedPolynomialArray[u2p2].getPolynomialBeginConst();
            _matMons.insert(itTerm->getNumMonomial(), true);
            itTerm=itTerm->_next;
            while(itTerm)
            {
                /* Insert the other monomials */
                _matMons.insert(itTerm->getNumMonomial(), false);
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
        
        /* Iterators on _matMons, _matPols, and polynomials */
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

        /* We take the biggest monomial of _matMons */
        itMonBeg=_matMons.findBiggest();
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
            itMonBeg=_matMons.findNextBiggest(itMonBeg);
        }
        while(itMonBeg != 0);
        if (icur != width)
        {
            cout << "***pb depliage _matMons dans Transform***" << endl;
            cout << "icur = " << icur << ", width = " << width << endl;
            cout << "Input polynomials must not have two different terms with the same monomial" << endl;
        }

        /* Fill the matrix with a triangular shape */
        itPolBeg=_matPols.findBiggest();
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
        itPolBeg=_matPols.findNextBiggest(itPolBeg);
        
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
            itPolBeg=_matPols.findNextBiggest(itPolBeg);
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
        NodeList<Element> * pos = res.getPolynomialBeforeBegin();
        for (int j = start; j < width; j++)
        {
            if (!row[tau[j]].isZero())
            {
                pos=res.emplaceOn(pos, row[tau[j]], tabMon[j]);
            }
        }
        res.deleteAfter(pos);
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
        
        /* Search the biggest monomial in _matMons which is not a leading monomial */
        itmon=_matMons.findBiggest();
        width++;
        while (itmon != 0 && itmon->_lt == true)
        {
            itmon=_matMons.findNextBiggest(itmon);
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
                    /* Add the multiple in _matPols */
                    _matPols.insert(indexPol, (_taggedPolynomialArray[indexPol]).getLM(), (_taggedPolynomialArray[indexPol]).getNbTerm());
                    height++;
                    /* Insert monomials of the new polynomial in _matMons */
                    itTerm=_taggedPolynomialArray[indexPol].getPolynomialBeginConst();
                    itTerm=itTerm->_next;
                    while(itTerm)
                    {
                        _matMons.insert(itTerm->getNumMonomial(), false);
                        itTerm=itTerm->_next;
                    }
                    break;
                }
            }
            /* End search */
            do
            {
                itmon=_matMons.findNextBiggest(itmon);
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
        NodeAvlPolynomial * itPolBeg = _matPols.findBiggest();
        clock_t startMajBasis = clock();
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
                buildPolynomial(_taggedPolynomialArray[itPolBeg->_numPolynomial].getPolynomial(), matrix.getRow(i), tabMon, width, sigma[i], tau);
                itPolBeg=_matPols.findNextBiggest(itPolBeg);
            }
        }
        if (VERBOSE > 1)
        {
            stat._timeMajBasis +=(clock () - startMajBasis);
        }
        for (i = nbPiv; i < heightReal; i++)
        {
            /* Create new generators */
            if (VERBOSE > 1)
            {
                startMajBasis = clock();
            }
            num_lt = tabMon[sigma[i]];
            if (tabMon[sigma[i]] == 0)
            {
                return false;
            }
            if (VERBOSE > 3)
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
            if (VERBOSE > 1)
            {
                stat._timeMajBasis +=(clock () - startMajBasis);
            }
            /* Add the new generator in the basis */
            _total.push_back(_numPol);
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
        int *tabMon;               /* Monomial array (indexes) */
        int nbPiv;                 /* We set the pivots in the upper part of mat, after nbPiv, polynomials can be some new generators */
        int *tau;                  /* sigma(tau(i))=tau(sigma(i))=i */
        int *sigma;                /* To get mat under triangular shape, we permute some columns */
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
        //ofstream fileSize("matrix-size.txt");
        
        chrono::steady_clock::time_point start, start1, start2;
        typedef chrono::duration<int,milli> millisecs_t;
        start1 = chrono::steady_clock::now();
        millisecs_t timeAppendMatrixF4 = millisecs_t::zero();
        chrono::steady_clock::time_point timeAppendMatrixF4Start;
        millisecs_t timePreprocessing = millisecs_t::zero();
        chrono::steady_clock::time_point timePreprocessingStart;
        millisecs_t timeTransform = millisecs_t::zero();
        chrono::steady_clock::time_point timeTransformStart;
        millisecs_t timePostprocessing = millisecs_t::zero();
        chrono::steady_clock::time_point timePostprocessingStart;
        
        /*step 0 */
        for (size_t i = 0; i < _polynomialArray.size(); i++)
        {
            _polynomialArray[i].normalize();
            _taggedPolynomialArray.emplace_back(_polynomialArray[i]);
            _total.push_back(_numPol);

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
            
            if (VERBOSE > 0)
            {
                start2 = chrono::steady_clock::now();
            }
            _matMons.reset();
            
            /* Construction of critical pairs with minimal degree */
            height = 0;
            nbPiv = 0;
            stat._nbCpDeg = 0;
            
            if(VERBOSE > 1)
            {
                /* Time spent in appendMatrixF4 */
                timeAppendMatrixF4Start=chrono::steady_clock::now();
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
                
                /* Matrix construction time */
                start = chrono::steady_clock::now();   
            }

            appendMatrixF4 (cp1, height, nbPiv);
            stat._nbCpDeg++;

            /* Get the other critical pairs of degree d */
            while ( (itcp1 != 0) && (itcp1->_cp.getDegree()==d))
            {
                cp1=itcp1->_cp;
                itcp1=_criticalPairSet.erase(itcp1);
                stat._nbCp--;
                appendMatrixF4 (cp1, height, nbPiv);
                stat._nbCpDeg++;
            }
            if(VERBOSE > 1)
            {
                timeAppendMatrixF4 +=chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-timeAppendMatrixF4Start);
            }
            
            if (VERBOSE > 0)
            {
                cout << "Construction of _matPols: " << endl;
                cout << "Number of selected pairs: " << stat._nbCpDeg << endl;
                cout << "Number of polynomials: " << height << endl;
                cout << "Number of monomials: " << _matMons.size() << endl << endl;
            }
            
            /* Preprocessing of _matPols */
            if(VERBOSE > 1)
            {
                timePreprocessingStart=chrono::steady_clock::now();
            }
            preprocessing(width, height, nbPiv);
            if(VERBOSE > 1)
            {
                timePreprocessing += chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-timePreprocessingStart);
            }
        
            /* Transform _matPols into a matrix */
            if (VERBOSE > 0)
            {
                cout << "Preprocessing of _matPols: " << endl;
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
                timeTransformStart = chrono::steady_clock::now();
            }
            sparse = transform (mat, tabMon, nbPiv, tau, sigma, startTail, endCol);
            if(VERBOSE > 1)
            {
                timeTransform += chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-timeTransformStart);
            }
            
            //filename=to_string(step)+"before-echelonize.pgm";
            //printMatrix(mat, tabMon, sigma, filename);
            
            if (VERBOSE > 0)
            {
                cout << "Convert _matPols into a matrix: " << endl;
                cout << "Matrix size: " << height << "x" << width << endl;
                cout << "Matrix density: " << sparse << endl;
                cout << "Construction time: " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms" << endl << endl;
            }
            //fileSize << "Height: " << height << ", Width: " << width << ", Number of pivots: " << nbPiv << endl;

            /* Triangularisation of mat */
            mat.setInfo(nbPiv, tau, sigma, startTail, endCol);
            heightReal=mat.echelonize();
            
            //filename=to_string(step)+"after-echelonize.pgm";
            //printMatrix(mat, tabMon, sigma, filename);
            
            if (VERBOSE > 0)
            {
                /* Update time */
                start = chrono::steady_clock::now();
            }
            if (VERBOSE > 1)
            {
                stat._timePurgeCp = 0;
                stat._timeAddCp = 0;
                stat._timeMajBasis = 0;
            }

            /* Rebuild _matPols from mat */
            /* Count new generators */
            stat._cmptNewGen=0;
            /* Count purged generators */
            stat._cmptGenPurg=0;
            
            /* Time spent in postProcessing */
            if(VERBOSE > 1)
            {
                timePostprocessingStart = chrono::steady_clock::now();
            }
            if(!postprocessing(mat, tabMon, sigma, tau, height, width, heightReal, nbPiv, stat))
            {
                cout << endl << endl << "GROEBNER BASIS : (1)" << endl;
                cout << "---> " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start1).count() << " ms " << endl << endl << endl;
                
                if(_matMons.size() != (size_t)width)
                {
                    cout << "*** Problem in width computation: size of _matMons = " << _matMons.size() << ", width = " << width << " ***" << endl;
                }
                _matMons.reset();
                if(_matPols.size() != (size_t)height) 
                {
                    cout << "*** Problem in height computation: size of _matPols = " << _matPols.size() << ", height = " << height << " ***" << endl << endl;
                }
                _matPols.reset();
 
                delete[] tabMon;
                delete[] tau;
                delete[] sigma;
                delete[] startTail;
                delete[] endCol;
                return 0;
            }
            if(VERBOSE > 1)
            {
                timePostprocessing+=chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-timePostprocessingStart);
            }
            
            if (VERBOSE > 0)
            {
                cout << "Update of _basis and queue of pairs done in " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms" << endl;
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
            _matMons.reset();
            _matPols.reset();
            
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
                cout << "Total computation time of step " << step << ": " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start2).count() << " ms" << endl << endl; 
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
            cout << "---> " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start1).count() << "ms CPU global computation time" << endl;
            cout << "---> " << timeAppendMatrixF4.count() << "ms CPU used for appendMatrixF4" << endl;
            cout << "---> " << timePreprocessing.count() << "ms CPU used for preprocessing" << endl;
            cout << "---> " << timeTransform.count() << "ms CPU used for transform" << endl;
            cout << "---> " << timePostprocessing.count() << "ms CPU used for postprocessing" << endl;
            
            cout << "_numPol: " << _numPol << " _taggedPolynomialArray size: " << _taggedPolynomialArray.size() << endl;
            cout << "_numTot: " << _numTot << " _total size: " << _total.size() << endl;
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
            _matPols.insert(index, (_taggedPolynomialArray[index]).getLM(), (_taggedPolynomialArray[index]).getNbTerm());
            itTerm=_taggedPolynomialArray[index].getPolynomialBeginConst();
            _matMons.insert(itTerm->getNumMonomial(), true);
            itTerm=itTerm->_next;
            while(itTerm)
            {
                _matMons.insert(itTerm->getNumMonomial(), false);
                itTerm=itTerm->_next;
            }
            height++;
        }
        
        /* Preprocessing */
        preprocessing(width, height, nbPiv);
        nbPiv = height;
        
        /* Transform _matPols into a matrix */
        if (VERBOSE > 0)
        {
            cout << "Preprocessing of _matPols: " << endl;
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
            cout << "Construction time: " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms" << endl;
        }

        /* Triangularisation of mat */
        mat.setInfo(nbPiv, tau, sigma, startTail, endCol);
        heightReal=mat.echelonize();

        /* Retrieve generators of the minimal basis */
        itPolBeg = _matPols.findBiggest();
        for (i = 0; i < nbPiv; i++)
        {
            num_lt = tabMon[sigma[i]];
            if(itPolBeg->_numMonomial != num_lt)
            {
                cout << "Wrong lt in postprocessing " << endl;
            }
            while( (itPolBeg != 0) && (itPolBeg->_numMonomial==num_lt) )
            {
                buildPolynomial(_taggedPolynomialArray[itPolBeg->_numPolynomial].getPolynomial(), mat.getRow(i), tabMon, width, sigma[i], tau);
                itPolBeg=_matPols.findNextBiggest(itPolBeg);
            }
        }
        if(_matMons.size() != (size_t)width)
        {
            cout << "*** Problem in width computation ***" << endl;
        }
        _matMons.reset();
        if(_matPols.size() != (size_t)height) 
        {
            cout << "*** Problem in height computation ***" << endl << endl;
        }
        _matPols.reset();

        delete[] tabMon;
        delete[] tau;
        delete[] sigma;
        delete[] startTail;
        delete[] endCol;
        
        if(VERBOSE > 0)
        {
            cout << "Groebner basis: " << _numGen << " generators. Computed in " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start1).count() << "ms CPU " << endl << endl << endl;
        }
        return _numGen;
    }

}

#endif // F4_IDEAL_INL
