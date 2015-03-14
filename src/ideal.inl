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
    // Constructor
    
    template <typename Element>
    Ideal<Element>::Ideal(std::vector<Polynomial<Element>> & polynomialArray): _polynomialArray(polynomialArray), _nbVariable(Monomial::getNbVariable()), NumPol(0), NumTot(0), NumGen(0), nbCP(0)
    {
        _taggedPolynomialArray.reserve(1000);
        GTotal.reserve(1000);
        Gbasis.reserve(100);
    }
    
    
    // Destructor
    
    template <typename Element>
    Ideal<Element>::~Ideal()
    {
    }
    
    
    // Miscellaneous
    
    template <typename Element>
    void
    Ideal<Element>::printTaggedPolynomialArray()
    {
        int i=0;
        cout << "_taggedPolynomialArray: " << NumPol << endl;
        typename vector<TaggedPolynomial<Element>>::const_iterator it;
        for(it=_taggedPolynomialArray.begin(); it != _taggedPolynomialArray.end(); ++it)
        {
            cout << i << ": " << endl << *it << endl;
            i++;
        }
        cout << endl;
        
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
        
        cout << "NumPol: " << NumPol << endl;
        cout << "NumTot: " << NumTot << endl;
        cout << "NumGen: " << NumGen << endl << endl << endl;
    }
    
    template <typename Element>
    void
    Ideal<Element>::printMonomialMap()
    {
        cout << endl << "------------------- Monomial Map -------------------------" << endl;
        typename map<int,bool>::const_iterator itMonBeg;
        for(itMonBeg=M_mons.begin(); itMonBeg != M_mons.end(); ++itMonBeg)
        {
            cout << "Monomial number: " <<  itMonBeg->first << ": " << Monomial::getNumMonomial(itMonBeg->first) << ", lt = " << itMonBeg->second << endl;
        }
        cout << endl << endl;
    }
            
    template <typename Element>
    void
    Ideal<Element>::printTaggedPolynomialSet()
    {
        cout << endl << "------------------- Tagged polynomial index set -------------------------" << endl;
        typename set<TaggedPolynomialIndex<Element>>::const_iterator itPolBeg;
        for(itPolBeg=M.begin(); itPolBeg != M.end(); ++itPolBeg)
        {
            cout << "Tagged polynomial number: " <<  itPolBeg->getIndex() << ": " << _taggedPolynomialArray[itPolBeg->getIndex()].getPolynomial() << endl;
        }
        cout << endl << endl;
    }
    
    template <typename Element>
    int
    Ideal<Element>::simplify (int u, int numList) 
    {
        //cout << "--------------- simplify input---------------------" << endl;
        //cout << numList << ": " << _taggedPolynomialArray[numList]  << endl;
        //cout << numList << " x " << u  << ": " << (_taggedPolynomialArray[numList] * Monomial(u)) << endl << endl;
        
        int i, j, k, numList_prev;
        
        numList_prev = numList;
        
        int const * varlistU = Monomial::getNumMonomial(u).getVarlist();
        
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
                    //cout << "Simplify new numList" << numList << endl << endl;
                    //cout << ": " << _taggedPolynomialArray[numList]  << endl;
                    if (!_taggedPolynomialArray[numList].isEmpty())
                    {
                        numList_prev = numList;
                        //tmp_mon->varlist[i] = u.varlist[i] - j;
                        //tmp_mon->deg = u.deg - j * weight[i];
                        varlistTmp[i]=varlistU[i]-j;
                        
                        for (k = i + 1; k < _nbVariable; k++)
                        {
                            //tmp_mon->varlist[k] = 0;
                            //tmp_mon->deg -= u.varlist[k] * weight[k];
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
            // le produit n'existe pas => on le cree
            _taggedPolynomialArray[numList]=(_taggedPolynomialArray[numList_prev]*Monomial(varlistTmp));
            _taggedPolynomialArray[numList].resetSimplyrules();
        }
        //cout << "--------------- simplify output---------------------" << endl;
        //cout << numList << ": " << _taggedPolynomialArray[numList] << endl << endl;
        return numList;
    }
    
    template <typename Element>
    void 
    Ideal<Element>::update(int index)
    {
        int j, k; 
        int div_trouve;
        
        set<CriticalPair<Element>> P0;
        set<CriticalPair<Element>> P1;
        set<CriticalPair<Element>> P2;
        
        typename set<CriticalPair<Element>>::iterator itcp1 = _criticalPairSet.begin();
        typename set<CriticalPair<Element>>::iterator itcp2;
        
        CriticalPair<Element> cp1;
        CriticalPair<Element> sp;
        
        Monomial lt_f;
        Monomial lt_g;
        
        /* Strict divisibility criteria to avoid the problem of "eliminate 2 critical pairs over 3" */
        while(itcp1 != _criticalPairSet.end())
        {
            int div, strct1, strct2;
            div = 1;
            strct1 = 0;
            strct2 = 0;
            
            //lt_f=Monomial::getNumMonomial(_taggedPolynomialArray[GTotal[itcp1->getP1()]].getLM());
            //lt_g=Monomial::getNumMonomial(_taggedPolynomialArray[GTotal[itcp1->getP2()]].getLM());
            lt_f=Monomial::getNumMonomial(_taggedPolynomialArray[itcp1->getP1()].getLM());
            lt_g=Monomial::getNumMonomial(_taggedPolynomialArray[itcp1->getP2()].getLM());
            
            for (j = 0; j < _nbVariable && div; j++)
            {
                if(Monomial::getNumVarlist(_taggedPolynomialArray[index].getLM(), j) < Monomial::getNumVarlist(itcp1->getLcm(),j) )
                {
                    if(lt_f.getVarlist(j) < lt_g.getVarlist(j))
                    {
                        strct1 = 1;
                    }
                    else if (lt_f.getVarlist(j) > lt_g.getVarlist(j))
                    {
                        strct2 = 1;
                    }
                }
                else
                {
                    if (Monomial::getNumVarlist(_taggedPolynomialArray[index].getLM(), j) > Monomial::getNumVarlist(itcp1->getLcm(),j) )
                    {
                        div=0;
                    }
                }
            }
            
            if (div && strct1 && strct2)
            {
                /* Suppress the critical pair */
                GUsed[itcp1->getP1()]--;
                GUsed[itcp1->getP2()]--;
                nbCP--;
                itcp1=_criticalPairSet.erase(itcp1);
            }
            else
            {
                ++itcp1;
            }
        }

        /* Computation of critical pairs */ 
        //for (j = 0; j < NumGen; j++)
        for (j = 0; j < Gbasis.size(); j++)
        {
            //if (!sp.setCriticalPair(index, Gbasis[j]))
            if (!sp.setCriticalPair(index, GTotal[Gbasis[j]]))
            {
                P0.insert(sp);
            }
            else
            {
                P1.insert(sp);
            }
        }
        
        itcp1=P1.begin();
        while (!P1.empty())
        {
            cp1 = *itcp1;
            itcp1=P1.erase(itcp1);
            
            /* Test if cp1 verify criteria 2 */
            div_trouve = 0;
            
            /* Scan P0 */
            itcp2=P0.begin();
            while (itcp2 != P0.end() && !div_trouve)
            {
                if (Monomial::getNumMonomial(cp1.getLcm()).isDivisible(Monomial::getNumMonomial(itcp2->getLcm())))
                {
                    div_trouve = 1;
                }
                ++itcp2;
            }
            
            /* Scan P1 */
            itcp2=P1.begin();
            while (itcp2 != P1.end() && !div_trouve)
            {
                if (Monomial::getNumMonomial(cp1.getLcm()).isDivisible(Monomial::getNumMonomial(itcp2->getLcm())))
                {
                    div_trouve = 1;
                }
                ++itcp2;
            }
            
            /* Scan P2 */
            itcp2=P2.begin();
            while (itcp2 != P2.end() && !div_trouve)
            {
                if (Monomial::getNumMonomial(cp1.getLcm()).isDivisible(Monomial::getNumMonomial(itcp2->getLcm())))
                {
                    div_trouve = 1;
                }
                ++itcp2;
            }
            if (!div_trouve)
            {
                /* Add cp1 to P2 */
                P2.insert(cp1);
            }
        }
        
        /* CP <- CP U P2 */
        itcp1=P2.begin();
        while (!P2.empty())
        {
            GUsed[itcp1->getP1()]++;
            GUsed[itcp1->getP2()]++;
            _criticalPairSet.insert(*itcp1);
            itcp1=P2.erase(itcp1);
            nbCP++;
        }
        
        /* Free P0 */
        if (!P0.empty())
        {
            P0.clear();
        }                       
        /* End of critical pair computation */

        /* Purge of generators */
        div_trouve = 0;
        lt_f=Monomial::getNumMonomial(_taggedPolynomialArray[index].getLM());
        //for (j = 0; j < NumGen; j++)
        for (j = 0; j < Gbasis.size(); j++)
        {
            //if (lt_f.isDivisible(Monomial::getNumMonomial(_taggedPolynomialArray[Gbasis[j]].getLM())))
            if (lt_f.isDivisible(Monomial::getNumMonomial(_taggedPolynomialArray[GTotal[Gbasis[j]]].getLM())))
            {
                div_trouve = 1;
                GUsed[index]--;
                break;
            }
        }
        if (!div_trouve)
        {
            /* Add the polynomial in Gbasis */
            
            
            Gbasis.push_back(NumTot);
            
            
            //Gbasis.push_back(index);
            NumGen++;
            /* purge of Gbasis by the new polynomial */
            //for (j = 0; j < NumGen - 1; j++)
            for (j = 0; j < Gbasis.size()-1; j++)
            {
                //if (Monomial::getNumMonomial(_taggedPolynomialArray[Gbasis[j]].getLM()).isDivisible(lt_f))
                if (Monomial::getNumMonomial(_taggedPolynomialArray[GTotal[Gbasis[j]]].getLM()).isDivisible(lt_f))
                { 
                    //GUsed[Gbasis[j]]--;
                    GUsed[GTotal[Gbasis[j]]]--;
                    
                    
                    //for (k = j; k < NumGen - 1; k++)
                    //for (k = j; k < Gbasis.size()-1; k++)
                    //{
                        //Gbasis[k] = Gbasis[k + 1];
                    //}
                    Gbasis.erase(Gbasis.begin()+j);
                    NumGen--;
                    j--;
                }
            }
        }
    }
    
    template <typename Element>
    void 
    Ideal<Element>::appendMatrixF4 (CriticalPair<Element> & p, int & h, int & nb_piv)
    {
        typename forward_list<Term<Element>>::const_iterator itbeg, itend;
        
        //int u1p1=simplify(p.getU1(), GTotal[p.getP1()]);
        int u1p1=simplify(p.getU1(), p.getP1());
        
        //cout << "APPEND MATRIX F4 ----------> cp = " << p << endl;
        
        //cout << "-------------- u1p1 ----------------: " << u1p1 << ": " << _taggedPolynomialArray[u1p1] << endl;
        
        //if(M.insert(TaggedPolynomialIndex<Element>(u1p1)).second)
        if(M.emplace(u1p1).second)
        {
            //cout << "-------------- u1p1 ---------> inserted " << endl;
            
            /* If u1p1 is not already in M we insert its monomials in M_Mons */
            itbeg=_taggedPolynomialArray[u1p1].getPolynomialBegin();
            itend=_taggedPolynomialArray[u1p1].getPolynomialEnd();
            
            if(M_mons.emplace(pair<int,bool>(itbeg->getNumMonomial(), true)).second)
            {
                nb_piv++;
            }
            ++itbeg;
            while(itbeg!=itend)
            {
                M_mons.emplace(pair<int,bool>(itbeg->getNumMonomial(), false));
                ++itbeg;
            }
            h++;
        }
        
        //int u2p2=simplify(p.getU2(), GTotal[p.getP2()]);
        int u2p2=simplify(p.getU2(), p.getP2());
        
        //cout << "-------------- u2p2 --------------: " << u2p2 << ": " << _taggedPolynomialArray[u2p2] << endl;
        
        //if(M.insert(TaggedPolynomialIndex<Element>(u2p2)).second)
        if(M.emplace(u2p2).second)
        {
            //cout << "-------------- u2p2 ---------> inserted " << endl;
            
            /* If u2p2 is not already in M we insert its monomials in M_Mons */
            itbeg=_taggedPolynomialArray[u2p2].getPolynomialBegin();
            itend=_taggedPolynomialArray[u2p2].getPolynomialEnd();
            
            if(M_mons.emplace(pair<int,bool>(itbeg->getNumMonomial(), true)).second)
            {
                //nb_piv++;
            }
            ++itbeg;
            while(itbeg!=itend)
            {
                M_mons.emplace(pair<int,bool>(itbeg->getNumMonomial(), false));
                ++itbeg;
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
        int nb = 0;                 //pour la sparsitude
        int icur, ih, ib, j;
        int c = 0;                  //colonne du dernier lt
        
        /* Iterators on M_mons, M, and polynomials */
        typename map<int,bool>::const_iterator itMonBeg, itMonEnd;
        //typename set<TaggedPolynomial<Element>>::const_iterator itPolBeg, itPolEnd;
        typename set<TaggedPolynomialIndex<Element>>::const_iterator itPolBeg, itPolEnd;
        typename forward_list<Term<Element>>::const_iterator itTermBeg, itTermEnd;
        
        //cout << "transform: " << endl;
        //printMonomialMap();
        //printTaggedPolynomialSet();
        
        /* Temporary */
        int numMon;

        //depliage de l'AVL de monomes en un tableau
        ih = 0;
        ib = nb_piv;
        icur = 0;
        //AVL_Mon *tmp_mon;

        // We take the biggest monomial of M_mons
        //tmp_mon = AVL_Mon_FindSmallest (M_mons);
        
        itMonBeg=M_mons.begin();
        itMonEnd=M_mons.end();
        do
        {
            if (itMonBeg->second == true)
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
            //tab_mon[icur] = tmp_mon->num;
            
            tab_mon[icur]=itMonBeg->first;
            icur++;
            ++itMonBeg;
        }
        while(itMonBeg != itMonEnd);
        //while ((tmp_mon = AVL_Mon_FindNextSmallest (tmp_mon)) != NULL);
        if (icur != largeur)
        {
            cout << "***pb depliage M_mons dans Transform***" << endl;
        }

        //remplissage de la matrice Mat sous forme triangulaire
        
        itPolBeg=M.begin();
        itPolEnd=M.end();
        
        itTermBeg=_taggedPolynomialArray[itPolBeg->getIndex()].getPolynomialBegin();
        itTermEnd=_taggedPolynomialArray[itPolBeg->getIndex()].getPolynomialEnd();
                
        ih = 0;
        ib = nb_piv;
        //AVL_PolEt *tmp_polEt;
        int numMonLT;
        //polynom pol, pol_end;
        //pol_end = NULL;
        //premier pol traite a part
        //tmp_polEt = AVL_PolEt_FindSmallest (M);
        //pol = List[tmp_polEt->numList].poly;
        //num_monLT = pol->data.numMon;
        numMonLT=itTermBeg->getNumMonomial();
        /*while (num_monLT != tab_mon[c])
           c++; */
        j = c;
        //Mat[0][tau[j]] = (pol->data.coeff);
        Mat.setElement(0,tau[j], itTermBeg->getCoefficient() );
        nb++;
        j++;
        //pol_end = pol;
        //pol = pol->next;
        ++itTermBeg;
        //while (pol != NULL)
        while(itTermBeg != itTermEnd)
        {
            //recherche de la colonne
            numMon = itTermBeg->getNumMonomial();
            while ( numMon != tab_mon[j])
            {
                j++;
            }
            //Mat[0][tau[j]] = (pol->data.coeff);
            Mat.setElement(0, tau[j], itTermBeg->getCoefficient());
            j++;
            nb++;
            //pol_end = pol;

            //pol = pol->next;
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
        
        ++itPolBeg;

        //traitement des autres polynomes
        //while ((tmp_polEt = AVL_PolEt_FindNextSmallest (tmp_polEt)) != NULL)
        while(itPolBeg != itPolEnd)
        {
            itTermBeg=_taggedPolynomialArray[itPolBeg->getIndex()].getPolynomialBegin();
            itTermEnd=_taggedPolynomialArray[itPolBeg->getIndex()].getPolynomialEnd();
            
            //pol = List[tmp_polEt->numList].poly;
            //if (pol->data.numMon == num_monLT)
            if(itTermBeg->getNumMonomial()==numMonLT)
            {
                //on met pol dans M_bas
                //Mat[ib][tau[c]] = (pol->data.coeff);
                Mat.setElement(ib, tau[c], itTermBeg->getCoefficient());
                j = c;
                nb++;
                j++;
                //pol_end = pol;
                //pol = pol->next;
                ++itTermBeg;
                //while (pol != NULL)
                
                while(itTermBeg!=itTermEnd)
                {
                    //recherche de la colonne
                    //while (pol->data.numMon != tab_mon[j])
                    numMon = itTermBeg->getNumMonomial() ;
                    while(numMon != tab_mon[j])
                    {
                        j++;
                    }
                    //Mat[ib][tau[j]] = (pol->data.coeff);
                    Mat.setElement(ib, tau[j], itTermBeg->getCoefficient());
                    j++;
                    nb++;
                    //pol = pol->next;
                    ++itTermBeg;
                }
                ib++;
            }
            else
            {
                //on met pol dans M_haut
                end_col[tau[c]] = ib;
                numMonLT = itTermBeg->getNumMonomial();
                
                while (numMonLT != tab_mon[c])
                {
                    c++;
                }
                
                j = c;
                //Mat[ih][tau[j]] = (pol->data.coeff);
                
                Mat.setElement(ih, tau[j], itTermBeg->getCoefficient());
                nb++;
                j++;
                //pol_end = pol;
                //pol = pol->next;
                ++itTermBeg;
                //while (pol != NULL)
                while(itTermBeg != itTermEnd)
                {
                    //recherche de la colonne
                    numMon=itTermBeg->getNumMonomial();
                    while (numMon != tab_mon[j])
                    {
                        j++;
                    }
                    
                    //Mat[ih][tau[j]] = (pol->data.coeff);
                    Mat.setElement(ih, tau[j], itTermBeg->getCoefficient());
                    j++;
                    nb++;
                    //pol_end = pol;

                    //pol = pol->next;
                    ++itTermBeg;
                }
                ih++;
            }
            
            ++itPolBeg;

            ////lib du pol de la ligne
            //if (List[tmp_polEt->numList].poly->next != NULL)
            //{
                //pol_end->next = Pol_FL;
                //Pol_FL = List[tmp_polEt->numList].poly->next;
                //List[tmp_polEt->numList].poly->next = NULL;
            //}
        }
        //M.clear();
        //M_mons.clear();
        end_col[nb_piv - 1] = ib;
        return ((double)nb) * 100. / ((double)largeur * (double)hauteur);

    }
    
    template <typename Element>
    Polynomial<Element>
    Ideal<Element>::buildPolynomial (Element * row, int *tab_mon, int largeur, int start, int *tau)
    {
        //(*dest) = NULL;
        Polynomial<Element> res;
        typename forward_list<Term<Element>>::const_iterator pos=res.getPolynomialBeforeBegin();
        int nb_terms = 0;
        //polynom fin = *dest;
        
        for (int j = start; j < largeur; j++)
        {
            if (!row[tau[j]].isZero())
            {
                //if (*dest == NULL)
                //{
                    //CheckTerms;
                    //*dest = Pol_FL;
    //#ifdef CHECK
                    //NBTERMS++;
    //#endif
                    //nb_terms++;
                    //Pol_FL = (*dest)->next;
                    //fin = *dest;

    //#ifdef STATS
                    //stats.max_terms_tmp++;
    //#endif // STATS

                //}
                //else
                //{
                    //CheckTerms fin->next = Pol_FL;
    //#ifdef CHECK
                    //NBTERMS++;
    //#endif
                    //nb_terms++;
                    //fin = fin->next;
                    //Pol_FL = fin->next;

    //#ifdef STATS
                    //stats.max_terms_tmp++;
    //#endif // STATS
                //}
                //fin->data.numMon = tab_mon[j];
                //fin->data.coeff = ligne[tau[j]];
                
                pos=res.emplaceAfter(pos, row[tau[j]], tab_mon[j]);
            }
        }
        //if (fin != NULL)
            //fin->next = NULL;
    //#ifdef CHECK
        //else
        //{
            //fprintf (stderr, "ligne nulle !!\n");
        //}
    //#endif
        //return nb_terms;
        return res;
    }
    
    
    // F4 Algorithm
    
    template <typename Element>
    int 
    Ideal<Element>::f4()
    {
        // Specify the tagged polynomial array used by the TaggedPolynomialIndex class.
        TaggedPolynomialIndex<Element>::setTaggedPolynomialArray(&_taggedPolynomialArray);
        
        // Specify the tagged polynomial array used by the CriticalPair class.
        CriticalPair<Element>::setTaggedPolynomialArray(&_taggedPolynomialArray);
        typename forward_list<Term<Element>>::const_iterator itbeg, itend;
        
        typename set<CriticalPair<Element>>::iterator itcp1;
        CriticalPair<Element> cp1;
        
        /* Iterators on M_mons, M, and polynomials */
        typename map<int,bool>::const_iterator itMonBeg, itMonEnd;
        typename set<TaggedPolynomialIndex<Element>>::const_iterator itPolBeg, itPolEnd;
        typename forward_list<Term<Element>>::const_iterator itTermBeg, itTermEnd;
        
        long i, j, k;

        int step = 0;
        int d;
        int nbCP_d;
        int NBEQN=_polynomialArray.size();
        
        if(VERBOSE > 1)
        {
            cout << "Number of equations: " << NBEQN << endl;
        }

        //pour la mise sous forme matricielle
        int *tab_mon;
        int nb_piv;                 //on met en partie haute de Mat les pivots, a partir de nb_piv ce sont d'eventuels nouveaux generateurs
        int *tau;                   //sigma(tau(i))=tau(sigma(i))=i
        int *sigma;                 //pour avoir Mat sous forme triangulaire
        int *start_tail;            //start_tail[i] = min{j>=nb_piv : sig[i]<sig[j]}
        int *end_col;

        //pour le preprocessing
        int hauteur, largeur, alloc_largeur, div_trouve, hauteur_reelle, quotient;
        Monomial lt_f;
        Monomial lt_g;
        Monomial m1, m2;
        
        // Percentage of non zero coefficient in Mat
        double sparse;

        //pour la maj finale
        int cmpt_newgen = 0;
        int cmpt_genpurg = 0;
        int num_lt;

        NumGen = 0;
        NumPol = 0;
        NumTot = 0;

        double time_purgeCP = 0;
        double time_addCP = 0;
        double time_majBasis = 0;
        clock_t start_purgeCP = 0;
        clock_t start_addCP = 0;
        clock_t start_majBasis = 0;
        clock_t start = 0;
        clock_t start2 = 0;
        clock_t start1 = clock ();

        //Mat = (INTTYPE **) calloc (MAXROWS, sizeof (INTTYPE *));
        //tab_mon = (int *)calloc (MAXCOLS, sizeof (int));
        //tau = (int *)calloc (MAXCOLS, sizeof (int));
        //sigma = (int *)calloc (MAXCOLS, sizeof (int));
        //start_tail = (int *)calloc (MAXROWS, sizeof (int));
        //end_col = (int *)calloc (MAXCOLS, sizeof (int));
        
        /*step 0 */
        for (i = 0; i < NBEQN; i++)
        {
            _polynomialArray[i].normalize();
            _taggedPolynomialArray.emplace_back(_polynomialArray[i]);
            //GTotal[i] = NumPol;
            GTotal.push_back(NumPol);
            
            //GUsed[i] = 1;
            GUsed.push_back(1);
            
            
            /*Initialisation : on calcule toutes les paires critiques */
            //purge de CP
            update(i);
            
            NumPol++;
            NumTot++;
        }
        step++;
        //NumTot = NBEQN;
        
        ///* Main loop on critical pairs */
        while (!_criticalPairSet.empty())
        {
            if (VERBOSE > 0)
            {
                cout << endl << "----------------------" << endl;
                cout << endl << "----- STEP " << step << " -----" << endl;
            }
            
            if (VERBOSE > 1)
            {
                start2 = clock ();
            }
            M_mons.clear();
            hauteur = 0;
            nb_piv = 0;
            /*construction des paires critiques de deg min */
            nbCP_d = 0;
            //cp_node = AVL_Pair_FindDeleteSmallest (&CP);    //cp de deg min
            itcp1=_criticalPairSet.begin();
            cp1=*itcp1;
            itcp1=_criticalPairSet.erase(itcp1);
            
            nbCP--;
            d = cp1.getDegree();

            if (VERBOSE > 0)
            {
                cout << "Step degree: " << d << ", Basis length: " << NumGen << ", Pairs queue length " << nbCP +1 << endl;
            }
            if (VERBOSE > 1)
            {
                //tmp de calcul de la matrice
                start = clock ();   
            }

            //appendMatrixF4 (cp1, M, M_mons, hauteur, nb_piv);
            appendMatrixF4 (cp1, hauteur, nb_piv);
            //recuperation du noeud
            GUsed[cp1.getP1()]--;
            GUsed[cp1.getP2()]--;
            
            //cp_node->fils0 = AVL_CP_FL;
            //AVL_CP_FL = cp_node;
            
            nbCP_d++;

            //recuperation des autres paires de degre d
            while ( (itcp1->getDegree()==d)  && (itcp1 != _criticalPairSet.end()))
            {
                //cp_node = AVL_Pair_FindDeleteSmallestd (&CP, d);
                cp1=*itcp1;
                
                itcp1=_criticalPairSet.erase(itcp1);
            
                nbCP--;
                //if (cp_node == NULL)
                //{
                    //nbCP++;
                    //break;          //cp de deg d toutes traitees
                //}
                //appendMatrixF4 (cp1, M, M_mons, hauteur, nb_piv);
                appendMatrixF4 (cp1, hauteur, nb_piv);
                nbCP_d++;
                //recuperation du noeud de la cp
                GUsed[cp1.getP1()]--;
                GUsed[cp1.getP2()]--;
                //cp_node->fils0 = AVL_CP_FL;
                //AVL_CP_FL = cp_node;

            }
            if (VERBOSE > 0)
            {
                cout << "Number of selected pairs: " << nbCP_d << endl;
                if (VERBOSE > 1)
                {
                    cout << endl << "Number of polynomials: " << hauteur << endl;
                    //largeur = AVL_Mon_FL - AVL_Mon_FL0;
                    cout << "Number of monomials: " << M_mons.size() << endl;
                }
                cout << endl << "Preprocessing of M" << endl;
            }
            
            /* preprocessing de M */
            largeur = 0;
            /* recherche du plus grand monome dans M_mons qui n'est pas un lt */
            //mon_node = AVL_Mon_FindSmallest (M_mons);
            itmon1=M_mons.begin();
            
            largeur++;
            while (itmon1 != M_mons.end() && itmon1->second == true)
            {
                //mon_node = AVL_Mon_FindNextSmallest (mon_node);
                ++itmon1;
                largeur++;
            }
            //while (mon_node != NULL)
            while(itmon1 != M_mons.end())
            {
                //recherche des reducteurs dans G
                for (i = NumGen - 1; i >= 0; i--)
                {
                    //if (Divides2
                        //(Mon_Tab[List[GTotal[Gbasis[i]]].poly->data.numMon],
                         //Mon_Tab[mon_node->num], &quotient))
                    
                    m1=Monomial::getNumMonomial(itmon1->first);
                    m2=Monomial::getNumMonomial(_taggedPolynomialArray[GTotal[Gbasis[i]]].getLM());
                    if(m1.isDivisible(m2))
                    {
                        quotient=(m1/m2).monomialToInt();
                        //reducteur trouve dans G
                        //mon_node->lt = 1;
                        itmon1->second=true;
                        nb_piv++;
                        //ajout dans M
                        //CheckPolEt tmp_polEt = AVL_PolEt_FL;
                        //AVL_PolEt_FL++;
                        //on teste si le calcul de ce multiple n'est pas deja fait
                        //tmp_polEt->numList =
                            //Simplify (quotient, GTotal[Gbasis[i]], &mon_inter);
                        
                        if (step==9)
                        {
                            cout << "i: " << i << ", Gbasis[i]: " << Gbasis[i] << " GTotal[Gbasis[i]]: " << GTotal[Gbasis[i]] << endl;
                        }
                        
                        int indexPol=simplify(quotient, GTotal[Gbasis[i]]);
                        //AVL_PolEt_Insert (&M, tmp_polEt, &ComparePolEtLT);
                        
                        M.emplace(indexPol);
                        
                        hauteur++;
                        //insertion des monomes du nouveau pol dans M_mons
                        //InsertMonPol (List[tmp_polEt->numList].poly->next, &M_mons);
                        
                        itbeg=_taggedPolynomialArray[indexPol].getPolynomialBegin();
                        itend=_taggedPolynomialArray[indexPol].getPolynomialEnd();
                        
                        ++itbeg;
                        while(itbeg!=itend)
                        {
                            M_mons.emplace(itbeg->getNumMonomial(), false);
                            ++itbeg;
                        }
                        break;
                    }
                }                  
                //fin recherche diviseur dans G
                do
                {
                    //mon_node = AVL_Mon_FindNextSmallest (mon_node);
                    ++itmon1;
                    largeur++;
                }
                while (itmon1 != M_mons.end() && itmon1->second == true);
            }
            largeur--;
            /*transformation de M sous forme de tableaux */
            
            //alloc_largeur = ROUND_MEM * ((largeur + ROUND_MEM - 1) / ROUND_MEM);

            //for (i = 0; i < hauteur; i++)
            //{
                //Mat[i] = (INTTYPE *) calloc (alloc_largeur, sizeof (INTTYPE));
                //if (Mat[i] == NULL)
                //{
                    //fprintf (stderr, "***pb alloc Mat***\n");
                    //exit (-1);
                //}
            //}
            
            cout << "Height: " << hauteur << ", Width :" << largeur << ", Number of pivots: " << nb_piv << endl;
            
            Matrix<Element> Mat(hauteur, largeur);
            tab_mon = new int[largeur];
            tau = new int[largeur];
            sigma = new int[largeur];
            start_tail = new int[hauteur];
            end_col = new int[largeur];
            
            sparse = transform (Mat, tab_mon, nb_piv, tau, sigma, start_tail, end_col);
            
            //cout << "DEBUG: Matrix before echelonize" << endl << Mat <<endl;
            
            if (VERBOSE > 1)
            {
                cout << "Matrix size: " << hauteur << "x" << largeur << endl;
                cout << "Matrix density: " << sparse << endl;
                cout << "Construction time: " << (((double)clock () - start) * 1000) / CLOCKS_PER_SEC << " ms" << endl;
            }

            /* triangularisation of Mat */
            Mat.setInfo(nb_piv, tau, sigma, start_tail, end_col);
            
            //hauteur_reelle =
                //BasicGauss (Mat, hauteur, largeur, nb_piv, tau, sigma, start_tail,
                            //end_col);
            hauteur_reelle=Mat.echelonize();
            
            //cout << "DEBUG: Matrix after echelonize " << endl << Mat <<endl;
            
            if (VERBOSE > 0)
            {
                cout << "Update of Gbasis and queue of pairs: " << endl;
                start = clock ();
            }
            if (VERBOSE > 1)
            {
                time_purgeCP = 0;
                time_addCP = 0;
                time_majBasis = 0;
                start_majBasis = clock ();
            }

            /*on reconstruit M a partir de Mat */
            cmpt_newgen = 0;        //comptage des nouveaux generateurs
            cmpt_genpurg = 0;       //comptage des generateurs purges
            
            
            //tmp_polEt = AVL_PolEt_FindDeleteSmallest (&M);
            for (i = 0; i < nb_piv; i++)
            {
                num_lt = tab_mon[sigma[i]];
    //#ifdef CHECK
                //if (tmp_polEt == NULL
                    //|| List[tmp_polEt->numList].poly->data.numMon != num_lt)
                //{
                    //fprintf (stderr, "Wrong lt in postprocessing\n");
                    //exit (1);
                //}
    //#endif
                
                //while (tmp_polEt != NULL
                       //&& List[tmp_polEt->numList].poly->data.numMon == num_lt)
                //{
                    //DeletePol (&List[tmp_polEt->numList].poly);
                    //List[tmp_polEt->numList].nb_terms
                        //= BuildPol (Mat[i], tab_mon, largeur, sigma[i],
                                    //&List[tmp_polEt->numList].poly, tau);
                    //tmp_polEt = AVL_PolEt_FindDeleteSmallest (&M);
                //}
                
                itPolBeg=M.begin();
                itPolEnd=M.end();
                while( (itPolBeg != itPolEnd) && (_taggedPolynomialArray[itPolBeg->getIndex()].getLM()==num_lt) )
                {
                    (_taggedPolynomialArray[itPolBeg->getIndex()]).setPolynomial(buildPolynomial(Mat.getRow(i), tab_mon, largeur, sigma[i], tau));
                    itPolBeg=M.erase(itPolBeg);
                }
            }
            if (VERBOSE > 1)
            {
                time_majBasis += (((double)clock () - start_majBasis) * 1000) / CLOCKS_PER_SEC;
            }
            for (i = nb_piv; i < hauteur_reelle; i++)
            {
                //creation des nveaux generateurs
                if (VERBOSE > 1)
                {
                    start_majBasis = clock ();
                }
                
                num_lt = tab_mon[sigma[i]];
                
                //CheckNumPol List[NumPol].nb_terms =
                    //BuildPol (Mat[i], tab_mon, largeur, sigma[i],
                              //&List[NumPol].poly,
                              //tau);
                
                _taggedPolynomialArray.emplace_back(buildPolynomial(Mat.getRow(i), tab_mon, largeur, sigma[i], tau));
                
                //for (j = 0; j < NBVARS; j++)
                    //List[NumPol].simplyrules[j] = -1;
                
                //ajout du nouveau gen dans la base
                if (VERBOSE > 2)
                {
                    cout << endl << "GTotal[" << NumTot << "] = " << _taggedPolynomialArray[NumPol] << endl;
                }

                //GTotal[NumTot] = NumPol;
                GTotal.push_back(NumPol);
                GUsed[NumTot] = 1;
                //Gbasis[NumGen] = NumTot;
                
                update(NumPol);
                
                //Gbasis.push_back(NumTot);
                NumPol++;
                NumTot++;
                //NumGen++;
                cmpt_newgen++;      //nv gen
                
                if (tab_mon[sigma[i]] == 0)
                {
                    cout << endl << endl << "GROEBNER BASIS : (1)" << endl;
                    cout << "---> " << (((double)clock () - start1) * 1000) / CLOCKS_PER_SEC << " ms " << endl << endl << endl;

                    ////Gestion memoire
                    //if (AVL_Mon_FL - AVL_Mon_FL0 != largeur)
                        //fprintf (stderr, "***pb dans le compte de largeur***\n");
                    //AVL_Mon_FL = AVL_Mon_FL0;
                    //if (AVL_PolEt_FL - AVL_PolEt_FL0 != hauteur)
                        //fprintf (stderr, "***pb dans le compte de hauteur***\n");
                    //AVL_PolEt_FL = AVL_PolEt_FL0;
                    //while (CP != NULL)
                    //{
                        //cp_node = AVL_Pair_FindDeleteSmallest (&CP);
                        //cp_node->fils0 = AVL_CP_FL;
                        //AVL_CP_FL = cp_node;

    //#ifdef STATS
                        //if ((AVL_CP_FL - AVL_CP_FL0) > stats.max_cp)
                        //{
                            //stats.max_cp = (AVL_CP_FL - AVL_CP_FL0);
                        //}
    //#endif // STATS

                    //}
                    //for (i = 0; i < hauteur; i++)
                        //free (Mat[i]);
                    //free (Mat);
                    //free (tab_mon);
                    //free (tau);
                    //free (sigma);
                    //free (start_tail);
                    //free (end_col);
                    //free (sp.lcm.varlist);
                    //free (sp.u1.varlist);
                    //free (sp.u2.varlist);
                    //free (mon_inter.varlist);
                    //free (quotient.varlist);
                    
                    delete[] tab_mon;
                    delete[] tau;
                    delete[] sigma;
                    delete[] start_tail;
                    delete[] end_col;
                    
                    return 0;
                }
                
                if (VERBOSE > 0)
                {
                    if (tab_mon[sigma[i]] <= _nbVariable)
                    {
                        cout << endl << "!! Polynom of degree 1: P[" << NumPol - 1 << " = " << _taggedPolynomialArray[NumPol-1] << " !! " << endl;
                    }
                }

                if (VERBOSE > 1)
                {
                    time_majBasis +=(((double)clock () - start_majBasis) * 1000) / CLOCKS_PER_SEC;
                }
                
                /* Update the set of critical pairs and the current basis */
                
                //cout << "DEGUG -----------------------> NumPol = " << NumPol << ", size of tpa: " << _taggedPolynomialArray.size() << endl;
                //cout << "DEGUG -----------------------> NumGen = " << NumGen << ", size of Gbasis: " << Gbasis.size() << endl;
                //cout << "DEGUG -----------------------> NumTot = " << NumTot << ", size of GTotal: " << GTotal.size() << endl << endl;
                //update(NumPol-1);
                
                if (VERBOSE > 0)
                {
                    cout << "Update done in " << (((double)clock () - start) * 1000) / CLOCKS_PER_SEC << " ms" << endl;
                    if (hauteur_reelle != hauteur)
                    {
                        cout << "** " << hauteur - hauteur_reelle << " reductions to zero **\n" << endl;
                    }
                }
            }
                
            step++;
            if (VERBOSE > 1)
            {
                cout << "--> Total computation time of step " << step << (((double)clock () - start2) * 1000) / CLOCKS_PER_SEC << " ms" << endl; 
            }
        }
        /* End of critical pair loop */
        
        cout << "---> " << (((double)clock () - start1) * 1000) / CLOCKS_PER_SEC << "ms CPU " << endl << endl << endl;
    }

}

#endif // F4_IDEAL_INL
