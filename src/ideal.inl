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
    Ideal<Element>::Ideal(std::vector<Polynomial<Element>> & polynomialArray): _polynomialArray(polynomialArray), _nbVariable(Monomial::getNbVariable()), NumPol(0), NumTot(0), NumGen(0), nbCP(0)
    {
        _taggedPolynomialArray.reserve(40000);
        GTotal.reserve(10000);
        Gbasis.reserve(1000);
        GUsed.reserve(10000);
        
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
        cout << "GTotal: ";
        for(vector<int>:: const_iterator it=GTotal.begin(); it != GTotal.end(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
        
        cout << "GUsed: ";
        for(vector<int>:: const_iterator it=GUsed.begin(); it != GUsed.end(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
        
        cout << "Gbasis: ";
        for(vector<int>:: const_iterator it=Gbasis.begin(); it != Gbasis.end(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
        cout << "GTotal[Gbasis]: ";
        for(vector<int>:: const_iterator it=Gbasis.begin(); it != Gbasis.end(); ++it)
        {
            cout << GTotal[*it] << " ";
        }
        cout << endl;
        
        cout << "NumPol: " << NumPol << endl;
        cout << "NumTot: " << NumTot << endl;
        cout << "NumGen: " << NumGen << endl << endl << endl;
    }
    
    template <typename Element>
    void
    Ideal<Element>::printReducedGroebnerBasis(bool printBasis) const
    {
        cout << "Gbasis: ";
        for(vector<int>:: const_iterator it=Gbasis.begin(); it != Gbasis.end(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
        cout << "GTotal[Gbasis]: ";
        for(vector<int>:: const_iterator it=Gbasis.begin(); it != Gbasis.end(); ++it)
        {
            cout << GTotal[*it] << " ";
        }
        cout << endl;
        
        if(printBasis)
        { 
            for(vector<int>:: const_iterator it=Gbasis.begin(); it != Gbasis.end(); ++it)
            {
                cout << GTotal[*it] << ": " << _taggedPolynomialArray[GTotal[*it]] << endl << endl;
            }
        }
    }
    
    template <typename Element>
    void
    Ideal<Element>::printMonomialMap() const
    {
        cout << endl << "------------------- Monomial Map -------------------------" << endl;
        NodeAvlMonomial * itMonBeg = M_mons.findBiggest();
        while(itMonBeg= itMonBeg != 0)
        {
            cout << itMonBeg->_numMonomial << ", lt = " << itMonBeg->_lt << endl;
            itMonBeg=M_mons.findNextBiggest(itMonBeg);
        }
        cout << endl << endl;
    }
            
    template <typename Element>
    void
    Ideal<Element>::printTaggedPolynomialSet() const
    {
        cout << endl << "------------------- Tagged polynomial index set -------------------------" << endl;
        
        NodeAvlPolynomial * itPolBeg = M.findBiggest(); 
        while(itPolBeg != 0)
        {
            cout << "NumPol = " << itPolBeg->_numPolynomial << ", NumLM = " << itPolBeg->_numMonomial << ", Number of terms = " << itPolBeg->_nbTerms << endl;
            itPolBeg=M.findNextBiggest(itPolBeg);
        }
    }
    
    template <typename Element>
    void
    Ideal<Element>::printMatrix (Matrix<Element> & Mat, int *tab_mon, int *sigma, string const & filename) const
    {
        ofstream file(filename);
        int d;
        const string color[7] = { " 0 0 0 ", " 0 0 1 ", " 0 1 0 ", " 0 1 1 ", " 1 0 0 ", " 1 0 1 ", " 1 1 0 "};

        if (file)
        {
            file << "P3" << endl << Mat.getWidth() << " " << Mat.getHeight() << endl << 1 << endl;
            int i, j;
            for (i = 0; i < Mat.getHeight(); i++)
            {
                for (j = 0; j < Mat.getWidth(); j++)
                {
                    if (!Mat.isZero(i,j))
                    {
                        d=Monomial::getNumMonomial(tab_mon[sigma[j]]).getDegree();
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
                    _taggedPolynomialArray[numList].setSimplyrule(i, NumPol);
                    
                    /* Insert a new "empty" tagged polynomial in _taggedPolynomialArray */
                    _taggedPolynomialArray.emplace_back();
                    numList = NumPol;
                    NumPol++;
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
    Ideal<Element>::update(int index, int & cmpt_genpurg, double & time_purgeCP, double & time_addCP, double & time_majBasis, bool purge)
    {
        size_t j; 
        bool div_trouve, div, strct1, strct2;
        clock_t start_purgeCP = 0;
        clock_t start_addCP = 0;
        clock_t start_majBasis = 0;
        
        NodeAvlCriticalPair<Element> * itcp1 = _criticalPairSet.findSmallest();
        NodeAvlCriticalPair<Element> * itcp2 = 0;
        
        CriticalPair<Element> cp1;
        CriticalPair<Element> sp;
        
        Monomial lt_f;
        Monomial lt_g;
        Monomial lcm;
        
        /* Strict divisibility criteria to avoid the problem of "eliminate 2 critical pairs over 3" */
        if (VERBOSE > 1)
        {
            start_purgeCP = clock ();
        }
        while(itcp1 != 0)
        {
            div = true;
            strct1 = false;
            strct2 = false;
            
            lt_f=Monomial::getNumMonomial(_taggedPolynomialArray[itcp1->_cp.getP1()].getLM());
            lt_g=Monomial::getNumMonomial(_taggedPolynomialArray[itcp1->_cp.getP2()].getLM());
            
            lcm=itcp1->_cp.getLcm();
            
            for (j = 0; j < (size_t)_nbVariable && div; j++)
            {
                if(Monomial::getNumVarlist(_taggedPolynomialArray[index].getLM(), j) < lcm.getVarlist(j) )
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
                    if (Monomial::getNumVarlist(_taggedPolynomialArray[index].getLM(), j) > lcm.getVarlist(j) )
                    {
                        div=false;
                    }
                }
            }
            
            if (div && strct1 && strct2)
            {
                /* Suppress the critical pair */
                //GUsed[itcp1->getP1()]--;
                //GUsed[itcp1->getP2()]--;
                nbCP--;
                itcp1=_criticalPairSet.erase(itcp1);
                
            }
            else
            {
                itcp1=_criticalPairSet.findNextSmallest(itcp1);
            }
        }
        
        if (VERBOSE > 1)
        {
            time_purgeCP += (((double)clock () - start_purgeCP) * 1000) / CLOCKS_PER_SEC;
            start_addCP = clock ();
        }

        /* Computation of critical pairs */ 
        for (j = 0; j < Gbasis.size(); j++)
        {
            if (!sp.setCriticalPair(index, GTotal[Gbasis[j]]))
            {
                P0.insert(sp);
            }
            else
            {
                P1.insert(sp);
            }
        }
        
        itcp1=P1.findSmallest();
        while(itcp1 != 0)
        {
            cp1=itcp1->_cp;
            itcp1=P1.findNextSmallest(itcp1);
            
            /* Test if cp1 verifies criteria 2 */
            div_trouve = false;
            
            /* Scan P0 */
            itcp2=P0.findSmallest();
            while (itcp2 != 0 && !div_trouve)
            {
                if ((cp1.getLcm()).isDivisible(itcp2->_cp.getLcm()))
                {
                    div_trouve = true;
                }
                itcp2=P0.findNextSmallest(itcp2);
            }
            
            /* Scan P1 */
            itcp2=itcp1;
            while (itcp2 != 0 && !div_trouve)
            {
                if ((cp1.getLcm()).isDivisible(itcp2->_cp.getLcm()))
                {
                    div_trouve = true;
                }
                itcp2=P1.findNextSmallest(itcp2);
            }
            
            /* Scan P2 */
            itcp2=P2.findSmallest();
            while (itcp2 != 0 && !div_trouve)
            {
                if ((cp1.getLcm()).isDivisible(itcp2->_cp.getLcm()))
                {
                    div_trouve = true;
                }
                itcp2=P2.findNextSmallest(itcp2);
            }
            if (!div_trouve)
            {
                /* Add cp1 to P2 */
                P2.insert(cp1);
            }
        }
        P1.reset();
        
        /* CP <- CP U P2 */
        itcp1=P2.findSmallest();
        while(itcp1!=0)
        { 
            //GUsed[itcp1->getP1()]++;
            //GUsed[itcp1->getP2()]++;
            _criticalPairSet.insert(itcp1->_cp);
            itcp1=P2.findNextSmallest(itcp1);
            nbCP++;
        }
        P2.reset();
        
        /* Free P0 */
        P0.reset();
        
        if (VERBOSE > 1)
        {
            time_addCP +=(((double)clock () - start_addCP) * 1000) / CLOCKS_PER_SEC;
            start_majBasis = clock ();
        }
        /* End of critical pair computation */
        
        if(purge)
        {
            /* Purge of generators */
            div_trouve = false;
            lt_f=Monomial::getNumMonomial(_taggedPolynomialArray[index].getLM());
            for (j = 0; j < Gbasis.size(); j++)
            {
                if (lt_f.isDivisible(Monomial::getNumMonomial(_taggedPolynomialArray[GTotal[Gbasis[j]]].getLM())))
                {
                    div_trouve = true;
                    //GUsed[index]--;
                    break;
                }
            }
            if (!div_trouve)
            {
                /* Add the polynomial in Gbasis */
                Gbasis.push_back(NumTot);
                NumGen++;
                /* purge of Gbasis by the new polynomial */
                for (j = 0; j < Gbasis.size()-1; j++)
                {
                    if (Monomial::getNumMonomial(_taggedPolynomialArray[GTotal[Gbasis[j]]].getLM()).isDivisible(lt_f))
                    { 
                        //GUsed[GTotal[Gbasis[j]]]--;
                        Gbasis.erase(Gbasis.begin()+j);
                        NumGen--;
                        cmpt_genpurg++;
                        j--;
                    }
                }
            }
        }
        else
        {
            lt_f=Monomial::getNumMonomial(_taggedPolynomialArray[index].getLM());
            /* Add the polynomial in Gbasis */
            Gbasis.push_back(NumTot);
            NumGen++;
            /* Purge of Gbasis by the new polynomial */
            for (j = 0; j < Gbasis.size()-1; j++)
            {
                if (Monomial::getNumMonomial(_taggedPolynomialArray[GTotal[Gbasis[j]]].getLM()).isDivisible(lt_f))
                { 
                    //GUsed[GTotal[Gbasis[j]]]--;
                    Gbasis.erase(Gbasis.begin()+j);
                    NumGen--;
                    cmpt_genpurg++;
                    j--;
                }
            }
        }
        if (VERBOSE > 1)
        {
            time_majBasis +=(((double)clock () - start_majBasis) * 1000) / CLOCKS_PER_SEC;
        }
        
    }
    
    template <typename Element>
    void 
    Ideal<Element>::appendMatrixF4 (CriticalPair<Element> & p, int & h, int & nb_piv)
    {
        typename forward_list<Term<Element>>::const_iterator itTermBeg, itTermEnd;
        
        int u1p1=simplify(p.getU1(), p.getP1()); 
        
        if(M.insert(u1p1, (_taggedPolynomialArray[u1p1]).getLM(), (_taggedPolynomialArray[u1p1]).getNbTerm())!=1)
        {
            /* If u1p1 is not already in M we insert its monomials in M_Mons */
            itTermBeg=_taggedPolynomialArray[u1p1].getPolynomialBegin();
            itTermEnd=_taggedPolynomialArray[u1p1].getPolynomialEnd();

            if(M_mons.insert(itTermBeg->getNumMonomial(), true) != 1)
            {
                nb_piv++;
            }
            ++itTermBeg;
            while(itTermBeg!=itTermEnd)
            {
                /* Insert the other monomials */
                M_mons.insert(itTermBeg->getNumMonomial(), false);
                ++itTermBeg;
            }
            h++;
        }
        
        int u2p2=simplify(p.getU2(), p.getP2());
        
        if(M.insert(u2p2, (_taggedPolynomialArray[u2p2]).getLM(), (_taggedPolynomialArray[u2p2]).getNbTerm())!=1)
        {
            /* If u2p2 is not already in M we insert its monomials in M_Mons */
            itTermBeg=_taggedPolynomialArray[u2p2].getPolynomialBegin();
            itTermEnd=_taggedPolynomialArray[u2p2].getPolynomialEnd();
            
            M_mons.insert(itTermBeg->getNumMonomial(), true);

            ++itTermBeg;
            while(itTermBeg!=itTermEnd)
            {
                /* Insert the other monomials */
                M_mons.insert(itTermBeg->getNumMonomial(), false);
                ++itTermBeg;
            }
            h++;
        }
    }
    
    template <typename Element>
    double 
    Ideal<Element>::transform(Matrix<Element> & Mat, int *tab_mon, int nb_piv, int *tau, int *sigma, int *start_tail, int *end_col)
    {
        int hauteur=Mat.getHeight();
        int largeur=Mat.getWidth();
        int nb = 0;                 /* for sparsitude */
        int icur, ih, ib, j;
        int c = 0;                  /* Column of the last lt */
        
        /* Iterators on M_mons, M, and polynomials */
        NodeAvlMonomial * itMonBeg = 0;
        NodeAvlPolynomial * itPolBeg = 0;
        typename forward_list<Term<Element>>::const_iterator itTermBeg, itTermEnd;
        
        /* Temporary */
        int numMon;
        int numMonLT;

        /* Unroll the AVL of monomial into an array */
        ih = 0;
        ib = nb_piv;
        icur = 0;

        /* We take the biggest monomial of M_mons */
        itMonBeg=M_mons.findBiggest();
        do
        {
            if (itMonBeg->_lt == true)
            {
                sigma[ih] = icur;
                tau[icur] = ih;
                start_tail[ih] = ib;
                ih++;
            }
            else
            {
                sigma[ib] = icur;
                tau[icur] = ib;
                end_col[ib] = ih;
                ib++;
            }
            tab_mon[icur]=itMonBeg->_numMonomial;
            icur++;
            itMonBeg=M_mons.findNextBiggest(itMonBeg);
        }
        while(itMonBeg != 0);
        if (icur != largeur)
        {
            cout << "***pb depliage M_mons dans Transform***" << endl;
            cout << "icur = " << icur << ", largeur = " << largeur << endl;
        }

        /* Fill the matrix with a triangular shape */
        itPolBeg=M.findBiggest();
        itTermBeg=_taggedPolynomialArray[itPolBeg->_numPolynomial].getPolynomialBegin();
        itTermEnd=_taggedPolynomialArray[itPolBeg->_numPolynomial].getPolynomialEnd();
            
        ih = 0;
        ib = nb_piv;
        
        /* Process first polynomial apart */
        numMonLT=itTermBeg->getNumMonomial();
        j = c;
        Mat.setElement(0,tau[j], itTermBeg->getCoefficient());
        nb++;
        j++;
        ++itTermBeg;
        while(itTermBeg != itTermEnd)
        {
            /* Search column */
            numMon = itTermBeg->getNumMonomial();
            while ( numMon != tab_mon[j])
            {
                j++;
            }
            Mat.setElement(0, tau[j], itTermBeg->getCoefficient());
            j++;
            nb++;
            ++itTermBeg;
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
            itTermBeg=_taggedPolynomialArray[itPolBeg->_numPolynomial].getPolynomialBegin();
            itTermEnd=_taggedPolynomialArray[itPolBeg->_numPolynomial].getPolynomialEnd();
            
            if(itTermBeg->getNumMonomial()==numMonLT)
            {
                /* Place the polynomial in the upper part of the matrix */
                Mat.setElement(ib, tau[c], itTermBeg->getCoefficient());
                j = c;
                nb++;
                j++;
                ++itTermBeg;
                
                while(itTermBeg!=itTermEnd)
                {
                    /* Search column */
                    numMon = itTermBeg->getNumMonomial() ;
                    while(numMon != tab_mon[j])
                    {
                        j++;
                    }
                    Mat.setElement(ib, tau[j], itTermBeg->getCoefficient());
                    j++;
                    nb++;
                    ++itTermBeg;
                }
                ib++;
            }
            else
            {
                /* Place the polynomial in the lower part of the matrix */
                end_col[tau[c]] = ib;
                numMonLT = itTermBeg->getNumMonomial();
                
                while (numMonLT != tab_mon[c])
                {
                    c++;
                }
                
                j = c;
                
                Mat.setElement(ih, tau[j], itTermBeg->getCoefficient());
                nb++;
                j++;
                ++itTermBeg;
                while(itTermBeg != itTermEnd)
                {
                    /* Search column */
                    numMon=itTermBeg->getNumMonomial();
                    while (numMon != tab_mon[j])
                    {
                        j++;
                    }
                    Mat.setElement(ih, tau[j], itTermBeg->getCoefficient());
                    j++;
                    nb++;
                    ++itTermBeg;
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
        end_col[nb_piv - 1] = ib;
        return ((double)nb) * 100. / ((double)largeur * (double)hauteur);

    }
    
    template <typename Element>
    Polynomial<Element>
    Ideal<Element>::buildPolynomial (Element * row, int *tab_mon, int largeur, int start, int *tau)
    {
        Polynomial<Element> res;
        typename forward_list<Term<Element>>::const_iterator pos=res.getPolynomialBeforeBegin();
        
        for (int j = start; j < largeur; j++)
        {
            if (!row[tau[j]].isZero())
            {
                pos=res.emplaceAfter(pos, row[tau[j]], tab_mon[j]);
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
    Ideal<Element>::preprocessing(int & largeur, int & hauteur, int & nb_piv) 
    {
        int indexPol;
        int i;
        Monomial m1, m2, quotient;
        typename forward_list<Term<Element>>::const_iterator itTermBeg, itTermEnd;
        NodeAvlMonomial * itmon;
        largeur = 0;
        
        /* Seach the biggest monomial in M_mons which is not a leading monomial */
        itmon=M_mons.findBiggest();
        largeur++;
        while (itmon != 0 && itmon->_lt == true)
        {
            itmon=M_mons.findNextBiggest(itmon);
            largeur++;
        }
        while(itmon != 0)
        {
            /* Search reducer in the basis */
            for (i = NumGen - 1; i >= 0; i--)
            {
                m1=Monomial::getNumMonomial(itmon->_numMonomial);
                m2=Monomial::getNumMonomial(_taggedPolynomialArray[GTotal[Gbasis[i]]].getLM());
                if(m1.isDivisible(m2))
                {
                    quotient=(m1/m2);
                    /* Reducer found */
                    itmon->_lt=true;
                    nb_piv++;
                    /* Test if the computation of this multiple is not already done */ 
                    indexPol=simplify(quotient, GTotal[Gbasis[i]]);
                    /* Add the multiple in M */
                    M.insert(indexPol, (_taggedPolynomialArray[indexPol]).getLM(), (_taggedPolynomialArray[indexPol]).getNbTerm());
                    hauteur++;
                    /* Insert monomials of the new polynomial in M_mons */
                    itTermBeg=_taggedPolynomialArray[indexPol].getPolynomialBegin();
                    itTermEnd=_taggedPolynomialArray[indexPol].getPolynomialEnd();
                    ++itTermBeg;
                    while(itTermBeg!=itTermEnd)
                    {
                        M_mons.insert(itTermBeg->getNumMonomial(), false);
                        ++itTermBeg;
                    }
                    break;
                }
            }
            /* End search */
            do
            {
                itmon=M_mons.findNextBiggest(itmon);
                largeur++;
            }
            while (itmon != 0 && itmon->_lt == true);
        }
        largeur--;
    }
    
    
    
    template <typename Element>
    bool
    Ideal<Element>::postprocessing(Matrix<Element> & matrix, int * tab_mon, int * sigma, int * tau, int hauteur, int largeur, int hauteur_reelle, int nb_piv, int & cmpt_genpurg, int & cmpt_newgen, double & time_purgeCP, double & time_addCP, double & time_majBasis) 
    {
        /* Iterators */
        NodeAvlPolynomial * itPolBeg = M.findBiggest();
        int num_lt, i;
        for (i = 0; i < nb_piv; i++)
        {
            num_lt = tab_mon[sigma[i]];
            if(itPolBeg->_numMonomial != num_lt)
            {
                cout << "Wrong lt in postprocessing " << endl;
            }
            while( (itPolBeg != 0) && (itPolBeg->_numMonomial==num_lt) )
            {
                _taggedPolynomialArray[itPolBeg->_numPolynomial].setPolynomial(buildPolynomial(matrix.getRow(i), tab_mon, largeur, sigma[i], tau));
                itPolBeg=M.findNextBiggest(itPolBeg);
            }
        }
        for (i = nb_piv; i < hauteur_reelle; i++)
        {
            /* Create new generators */
            num_lt = tab_mon[sigma[i]];
            if (tab_mon[sigma[i]] == 0)
            {
                return false;
            }
            if (VERBOSE > 2)
            {
                if (tab_mon[sigma[i]] <= _nbVariable)
                {
                    cout << endl << "!! Polynom of degree 1: P[" << NumPol - 1 << " = " << _taggedPolynomialArray[NumPol-1] << " !! " << endl;
                }
            }
            /* Update the set of critical pairs and the current basis */
            _taggedPolynomialArray.emplace_back(buildPolynomial(matrix.getRow(i), tab_mon, largeur, sigma[i], tau));
            if (VERBOSE > 3)
            {
                cout << endl << "GTotal[" << NumTot << "] = " << _taggedPolynomialArray[NumPol] << endl;
            }
            /* Add the new generator in the basis */
            GTotal.push_back(NumPol);
            GUsed.push_back(1);
            update(NumPol, cmpt_genpurg, time_purgeCP, time_addCP, time_majBasis, false);
            NumPol++;
            NumTot++;
            cmpt_newgen++;      //nv gen
        }
        return true;
    }
    
    // F4 Algorithm
    
    template <typename Element>
    int 
    Ideal<Element>::f4()
    {
        // Specify the tagged polynomial array used by the CriticalPair class.
        CriticalPair<Element>::setTaggedPolynomialArray(&_taggedPolynomialArray);
        
        /* Iterators */
        NodeAvlPolynomial * itPolBeg = 0;
        typename forward_list<Term<Element>>::const_iterator itTermBeg, itTermEnd;
        NodeAvlCriticalPair<Element> * itcp1;
        
        /* F4 matrix */
        Matrix<Element> Mat;
        
        /* Temporary critical pair */
        CriticalPair<Element> cp1;
        
        /* Filename to print matrices */
        string filename;
        
        int i;
        int step = 0;
        int d;
        int nbCP_d;
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
        int *tab_mon;               /* Monomial array */
        int nb_piv;                 /* We set the pivots in the upper part of Mat, after nb_piv, polynomials can be some new generators */
        int *tau;                   /* sigma(tau(i))=tau(sigma(i))=i */
        int *sigma;                 /* To get Mat under triangular shape, we permute some columns */
        int *start_tail;            /* start_tail[i] = min{j>=nb_piv : sigma[i]<sigma[j]} */
        int *end_col;               

        /* For preprocessing */
        int hauteur, largeur, hauteur_reelle, index;
        Monomial lt_f;
        Monomial lt_g;
        Monomial m1, m2;
        
        /* Percentage of non zero coefficient in Mat */
        double sparse;
        
        /* Counters */
        NumGen = 0;             /* Number of polynomials in the groebner basis */
        NumPol = 0;             /* Number of polynomials in _taggedPolynomialArray */
        NumTot = 0;             /* Number of polynomials used to update the basis and the critical pairs set */

        /* Statistic */
        int cmpt_newgen = 0;
        int cmpt_genpurg = 0;

        double time_purgeCP = 0;
        double time_addCP = 0;
        double time_majBasis = 0;
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
            GTotal.push_back(NumPol);
            GUsed.push_back(1);

            /* Initialisation : compute all the critical pairs and purge of the basis */
            update(i, cmpt_genpurg, time_purgeCP, time_addCP, time_majBasis, true);
            NumPol++;
            NumTot++;
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
            //cout << "NumPol: " << NumPol << " _taggedPolynomialArray size: " << _taggedPolynomialArray.size() << endl;
            //cout << "NumTot: " << NumTot << " GTotal size: " << GTotal.size() << " GUsed size: " << GUsed.size() << endl;
            //cout << "NumGen: " << NumGen << " Gbasis size: " << Gbasis.size() << endl << endl;
            
            if (VERBOSE > 1)
            {
                start2 = clock ();
            }
            M_mons.reset();
            
            /* Construction of critical pairs with minimal degree */
            hauteur = 0;
            nb_piv = 0;
            nbCP_d = 0;
            
            if(VERBOSE > 1)
            {
                /* Time spent in appendMatrixF4 */
                timeAppendMatrixF4Start=clock();
            }
            
            /* Critical pair of minimal degree */
            itcp1=_criticalPairSet.findSmallest();
            cp1=itcp1->_cp;
            itcp1=_criticalPairSet.erase(itcp1);
            
            nbCP--;
            d = cp1.getDegree();

            if (VERBOSE > 0)
            {
                cout << "Step degree: " << d << ", Basis length: " << NumGen << ", Pairs queue length " << nbCP +1 << endl << endl;
            }
            if (VERBOSE > 1)
            {
                // Matrix construction time
                start = clock ();   
            }

            appendMatrixF4 (cp1, hauteur, nb_piv);
            //recuperation du noeud
            //GUsed[cp1.getP1()]--;
            //GUsed[cp1.getP2()]--;
            nbCP_d++;

            /* Get the other critical pairs of degree d */
            while ( (itcp1 != 0) && (itcp1->_cp.getDegree()==d))
            {
                cp1=itcp1->_cp;
                itcp1=_criticalPairSet.erase(itcp1);
                nbCP--;
                appendMatrixF4 (cp1, hauteur, nb_piv);
                nbCP_d++;
                //recuperation du noeud de la cp
                //GUsed[cp1.getP1()]--;
                //GUsed[cp1.getP2()]--;
            }
            if(VERBOSE > 1)
            {
                timeAppendMatrixF4 +=(clock () - timeAppendMatrixF4Start);
            }
            
            if (VERBOSE > 0)
            {
                cout << "Construction of M: " << endl;
                cout << "Number of selected pairs: " << nbCP_d << endl;
                cout << "Number of polynomials: " << hauteur << endl;
                cout << "Number of monomials: " << M_mons.size() << endl << endl;
            }
            
            /* Preprocessing of M */
            if(VERBOSE > 1)
            {
                timePreprocessingStart=clock();
            }
            preprocessing(largeur, hauteur, nb_piv);
            if(VERBOSE > 1)
            {
                timePreprocessing +=(clock () - timePreprocessingStart);
            }
        
            /* Transform M into a matrix */
            if (VERBOSE > 0)
            {
                cout << "Preprocessing of M: " << endl;
                cout << "Height: " << hauteur << ", Width :" << largeur << ", Number of pivots: " << nb_piv << endl << endl;
            }
            
            Mat=Matrix<Element>(hauteur, largeur);
            tab_mon = new int[largeur];
            tau = new int[largeur];
            sigma = new int[largeur];
            start_tail = new int[hauteur];
            end_col = new int[largeur];
            
            /* Time spent in transform */
            if(VERBOSE > 1)
            {
                timeTransformStart = clock();
            }
            sparse = transform (Mat, tab_mon, nb_piv, tau, sigma, start_tail, end_col);
            if(VERBOSE > 1)
            {
                timeTransform +=(clock () - timeTransformStart);
            }
            
            //filename=to_string(step)+"before-echelonize.pgm";
            //printMatrix(Mat, tab_mon, sigma, filename);
            
            if (VERBOSE > 0)
            {
                cout << "Convert M into a matrix: " << endl;
                cout << "Matrix size: " << hauteur << "x" << largeur << endl;
                cout << "Matrix density: " << sparse << endl;
                cout << "Construction time: " << (((double)clock () - start) * 1000) / CLOCKS_PER_SEC << " ms" << endl << endl;
            }

            /* Triangularisation of Mat */
            Mat.setInfo(nb_piv, tau, sigma, start_tail, end_col);
            hauteur_reelle=Mat.echelonize();
            
            //filename=to_string(step)+"after-echelonize.pgm";
            //printMatrix(Mat, tab_mon, sigma, filename);
            
            if (VERBOSE > 0)
            {
                /* Update time */
                start = clock ();
            }
            if (VERBOSE > 1)
            {
                time_purgeCP = 0;
                time_addCP = 0;
                time_majBasis = 0;
                //start_majBasis = clock ();
            }

            /* Rebuild M from Mat */
            cmpt_newgen = 0;        /* count new generators */
            cmpt_genpurg = 0;       /* count purged generators */
            
            /* Time spent in postProcessing */
            if(VERBOSE > 1)
            {
                timePostprocessingStart = clock();
            }
            if(!postprocessing(Mat, tab_mon, sigma, tau, hauteur, largeur, hauteur_reelle, nb_piv, cmpt_genpurg, cmpt_newgen, time_purgeCP, time_addCP, time_majBasis))
            {
                cout << endl << endl << "GROEBNER BASIS : (1)" << endl;
                cout << "---> " << (((double)clock () - start1) * 1000) / CLOCKS_PER_SEC << " ms " << endl << endl << endl;
                
                if(M_mons.size() != (size_t)largeur)
                {
                    cout << "*** Problem in width computation: size of M_mons = " << M_mons.size() << ", width = " << largeur << " ***" << endl;
                }
                M_mons.reset();
                if(M.size() != (size_t)hauteur) 
                {
                    cout << "*** Problem in height computation: size of M = " << M.size() << ", height = " << hauteur << " ***" << endl << endl;
                }
                M.reset();
 
                delete[] tab_mon;
                delete[] tau;
                delete[] sigma;
                delete[] start_tail;
                delete[] end_col;
                return 0;
            }
            if(VERBOSE > 1)
            {
                timePostprocessing+=(clock()-timePostprocessingStart);
            }
            
            if (VERBOSE > 0)
            {
                cout << "Update of Gbasis and queue of pairs done in " << (((double)clock () - start) * 1000) / CLOCKS_PER_SEC << " ms" << endl;
                if (VERBOSE > 1)
                {
                    cout << "--> " << time_purgeCP << " ms for purging of the pairs queue" << endl;
                    cout << "--> " << time_addCP << " ms for updating CP " << endl;
                    cout << "--> " << time_majBasis << " ms for updating Gbasis " << endl;
                }
                if (hauteur_reelle != hauteur)
                {
                    cout << "** " << hauteur - hauteur_reelle << " reductions to zero **" << endl << endl;
                }
            }
            
            /* Reset the AVL of monomials and tagged polynomials */
            timeClearStart=clock();
            M_mons.reset();
            M.reset();
            timeClear+=(clock()-timeClearStart);
            
            if (cmpt_newgen != (hauteur_reelle - nb_piv))
            {
                cout << "*** erreur dans le comptage des nouveaux generateurs ***" << endl;
            }

            if (VERBOSE > 0)
            {
                cout << "Basis length: " << NumGen << " (" << cmpt_newgen << " new gen and " << cmpt_genpurg << " purged) " << endl << endl;
            }
                
            if (VERBOSE > 0)
            {
                cout << "Total computation time of step " << step << ": " << (((double)clock () - start2) * 1000) / CLOCKS_PER_SEC << " ms" << endl << endl; 
            }
            step++;
            
            delete[] tab_mon;
            delete[] tau;
            delete[] sigma;
            delete[] start_tail;
            delete[] end_col;
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
            
            cout << "NumPol: " << NumPol << " _taggedPolynomialArray size: " << _taggedPolynomialArray.size() << endl;
            cout << "NumTot: " << NumTot << " GTotal size: " << GTotal.size() << " GUsed size: " << GUsed.size() << endl;
            cout << "NumGen: " << NumGen << " Gbasis size: " << Gbasis.size() << endl << endl;
        }
        
        /* Reduced the basis */
        if (VERBOSE > 0)
        {
            cout << endl << "---------------------------------------" << endl;
            cout << "Reducing the basis..." << endl;;
        }

        largeur = 0;
        hauteur = 0;
        
        for (i = 0; i < NumGen; i++)
        {
            index=GTotal[Gbasis[i]];
            M.insert(index, (_taggedPolynomialArray[index]).getLM(), (_taggedPolynomialArray[index]).getNbTerm());
            
            itTermBeg=_taggedPolynomialArray[index].getPolynomialBegin();
            itTermEnd=_taggedPolynomialArray[index].getPolynomialEnd();
            
            M_mons.insert(itTermBeg->getNumMonomial(), true);
            
            ++itTermBeg;
            while(itTermBeg!=itTermEnd)
            {
                M_mons.insert(itTermBeg->getNumMonomial(), false);
                ++itTermBeg;
            }
            hauteur++;
        }
        
        /* Preprocessing */
        preprocessing(largeur, hauteur, nb_piv);
        nb_piv = hauteur;

        /* Transformation de M sous forme de tableaux */
        cout << "Height: " << hauteur << ", Width :" << largeur << ", Number of pivots: " << nb_piv << endl;
            
        Mat=Matrix<Element>(hauteur, largeur);
        tab_mon = new int[largeur];
        tau = new int[largeur];
        sigma = new int[largeur];
        start_tail = new int[hauteur];
        end_col = new int[largeur];
        
        sparse = transform (Mat, tab_mon, nb_piv, tau, sigma, start_tail, end_col);
        
        if (VERBOSE > 1)
        {
            cout << "Matrix size: " << hauteur << "x" << largeur << endl;
            cout << "Matrix density: " << sparse << endl;
            cout << "Construction time: " << (((double)clock () - start) * 1000) / CLOCKS_PER_SEC << " ms" << endl;
        }

        /* Triangularisation of Mat */
        Mat.setInfo(nb_piv, tau, sigma, start_tail, end_col);
        hauteur_reelle=Mat.echelonize();

        // recuperation des generateurs de la base minimale
        itPolBeg = M.findBiggest();
        for (i = 0; i < nb_piv; i++)
        {
            num_lt = tab_mon[sigma[i]];
            if(itPolBeg->_numMonomial != num_lt)
            {
                cout << "Wrong lt in postprocessing " << endl;
            }
            while( (itPolBeg != 0) && (itPolBeg->_numMonomial==num_lt) )
            {
                _taggedPolynomialArray[itPolBeg->_numPolynomial].setPolynomial(buildPolynomial(Mat.getRow(i), tab_mon, largeur, sigma[i], tau));
                itPolBeg=M.findNextBiggest(itPolBeg);
            }
        }
        if(M_mons.size() != (size_t)largeur)
        {
            cout << "*** Problem in width computation ***" << endl;
        }
        M_mons.reset();
        if(M.size() != (size_t)hauteur) 
        {
            cout << "*** Problem in height computation ***" << endl << endl;
        }
        M.reset();

        delete[] tab_mon;
        delete[] tau;
        delete[] sigma;
        delete[] start_tail;
        delete[] end_col;

        return NumGen;
    }

}

#endif // F4_IDEAL_INL
