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
    Ideal<Element>::Ideal(std::vector<Polynomial<Element>> & polynomialArray): _polynomialArray(polynomialArray), _nbVariable(Monomial::getNbVariable()), NumPol(0), NumTot(0), NumGen(0)
    {
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
        cout << "NumGen: " << NumGen << endl;
    }
    
    template <typename Element>
    int
    Ideal<Element>::simplify (Monomial const & u, int numList) 
    {
        int i, j, k, numList_prev;
        //for (i = 0; i < _nbVariable; i++)
        //{
            //tmp_mon->varlist[i] = u.varlist[i];
        //}
        //tmp_mon->deg = u.deg;
        
        numList_prev = numList;
        
        int const * varlistU = u.getVarlist();
        int varlistTmp[_nbVariable];
        
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
                    //List[NumPol].poly = NULL;
                    //for (k = 0; k < NBVARS; k++)
                        //List[NumPol].simplyrules[k] = -1;
                    
                    // Insert a new "empty" tagged polynomial in _taggedPolynomialArray
                    _taggedPolynomialArray.emplace_back();
                    
                    numList = NumPol;
                    NumPol++;
                }
            }
        }
        if (_taggedPolynomialArray[numList].isEmpty())
        {
            //le produit n'existe pas => on le cree
            //List[numList].poly 
                //MultMonPol (Mon_to_Int (*tmp_mon), List[numList_prev].poly);
            //List[numList].nb_terms = List[numList_prev].nb_terms;
            _taggedPolynomialArray[numList]=_taggedPolynomialArray[numList_prev]*Monomial(varlistTmp);
        }
        return numList;
    }
    
    
    // F4 Algorithm
    
    template <typename Element>
    void 
    Ideal<Element>::f4()
    {
        // Specify the tagged polynomial array used by the CriticalPair class.
        CriticalPair<Element>::setTaggedPolynomialArray(&_taggedPolynomialArray);
        
        long i, j, k;
        
        // nbre de paires critiques en attente de traitement
        int nbCP = 0;
        
        CriticalPair<Element> sp;

        int step = 0;
        int d;
        int nbCP_d;
        int NBEQN=_polynomialArray.size();
        if(VERBOSE > 1)
        {
            cout << "Number of equations: " << NBEQN << endl;
        }
        
        //la matrice F4
        set<TaggedPolynomial<Element>> M; 
        
        //les monomes intervenant dans M
        set<Monomial> M_mons; 
        
        // critical pairs sets
        set<CriticalPair<Element>> criticalPairSet;
        set<CriticalPair<Element>> P0;
        set<CriticalPair<Element>> P1;
        set<CriticalPair<Element>> P2;
        

        //pour la mise sous forme matricielle
        int *tab_mon;
        int nb_piv;                 //on met en partie haute de Mat les pivots, a partir de nb_piv ce sont d'eventuels nouveaux generateurs
        int *tau;                   //sigma(tau(i))=tau(sigma(i))=i
        int *sigma;                 //pour avoir Mat sous forme triangulaire
        int *start_tail;            //start_tail[i] = min{j>=nb_piv : sig[i]<sig[j]}
        int *end_col;

        //pour le preprocessing
        int hauteur, largeur, alloc_largeur, div_trouve, hauteur_reelle;
        Monomial quotient;
        Monomial lt_f;
        Monomial lt_g;
        
        // Percentage of non zero coefficient in Mat
        double sparse;

        //pour la maj finale
        int cmpt_newgen = 0;
        int cmpt_genpurg = 0;
        int num_lt;

        //NumGen = 0;
        //NumPol = 0;
        //NumTot = 0;

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
            NumPol++;

            /*Initialisation : on calcule toutes les paires critiques */
            //purge de CP
            
            //cp_node = AVL_Pair_FindSmallest (CP);
            //while (cp_node != NULL)
            
            typename set<CriticalPair<Element>>::iterator itcp1 = criticalPairSet.begin();
            typename set<CriticalPair<Element>>::iterator itcp2 = criticalPairSet.begin();
            
            CriticalPair<Element> cp1;
            CriticalPair<Element> cp2;
            CriticalPair<Element> cp3;
            
            
            while(itcp1 != criticalPairSet.end())
            {
                int div, strct1, strct2;
                div = 1;
                strct1 = 0;
                strct2 = 0;
                
                lt_f=Monomial::getNumMonomial(_taggedPolynomialArray[GTotal[itcp1->getP1()]].getLM());
                lt_g=Monomial::getNumMonomial(_taggedPolynomialArray[GTotal[itcp1->getP2()]].getLM());
                
                for (j = 0; j < _nbVariable && div; j++)
                {
                    if(Monomial::getNumVarlist(_taggedPolynomialArray[NumPol - 1].getLM(), j) < Monomial::getNumVarlist(itcp1->getLcm(),j) )
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
                        if (Monomial::getNumVarlist(_taggedPolynomialArray[NumPol - 1].getLM(), j) > Monomial::getNumVarlist(itcp1->getLcm(),j) )
                        {
                            div=0;
                        }
                    }
                }
                
                //cp2 = AVL_Pair_FindNextSmallest (cp_node);
                itcp2=itcp1;
                ++itcp2;
                if (div && strct1 && strct2)
                {
                    cp1=*itcp1;
                    cp2=*itcp2;
                    
                    GUsed[itcp1->getP1()]--;
                    GUsed[itcp1->getP2()]--;
                    nbCP--;
                    criticalPairSet.erase(itcp1);
                }
                ++itcp1;
            }

            //calcul des paires critiques
            for (j = 0; j < NumGen; j++)
            {
                if (!sp.setCriticalPair(i, Gbasis[j]))
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
                
                //cp_node verifie crit2 ?
                div_trouve = 0;
                
                //parcours P0
                itcp2=P0.begin();
                while (itcp2 != P0.end() && !div_trouve)
                {
                    if (Monomial::getNumMonomial(cp1.getLcm()).isDivisible(Monomial::getNumMonomial(itcp2->getLcm())))
                    {
                        div_trouve = 1;
                    }
                    ++itcp2;
                }
                
                //parcours P1
                itcp2=P1.begin();
                while (itcp2 != P1.end() && !div_trouve)
                {
                    if (Monomial::getNumMonomial(cp1.getLcm()).isDivisible(Monomial::getNumMonomial(itcp2->getLcm())))
                    {
                        div_trouve = 1;
                    }
                    ++itcp2;
                }
                
                //parcours P2
                itcp2=P2.begin();
                while (itcp2 != P2.end() && !div_trouve)
                {
                    if (Monomial::getNumMonomial(cp1.getLcm()).isDivisible(Monomial::getNumMonomial(itcp2->getLcm())))
                    {
                        div_trouve = 1;
                    }
                    ++itcp2;
                }
                if (div_trouve)
                {
                    // TODO
                }
                else
                {
                    //ajout dans P2
                    P2.insert(cp1);
                }
            }
            
            //CP <- CP U P2
            itcp1=P2.begin();
            while (itcp1 !=P2.end())
            {
                GUsed[itcp1->getP1()]++;
                GUsed[itcp1->getP2()]++;
                //P2 = P2->fils0;
                //AVL_Pair_Insert (&CP, cp_node, &Compare);
                criticalPairSet.insert(*itcp1);
                P2.erase(itcp1);
                ++itcp1;
                nbCP++;
            }
            
            //liberation de P0
            if (!P0.empty())
            {
                P0.clear();
            }                       //fin de calcul de paires 

            /* purge des generateurs */
            div_trouve = 0;
            lt_f=Monomial::getNumMonomial(_taggedPolynomialArray[NumPol-1].getLM());
            for (j = 0; j < NumGen; j++)
            {
                if (lt_f.isDivisible(Monomial::getNumMonomial(_taggedPolynomialArray[Gbasis[j]].getLM())))
                {
                    div_trouve = 1;
                    GUsed[i]--;
                    break;
                }
            }
            if (!div_trouve)
            {
                //Ajout du polynome dans Gbasis
                //Gbasis[NumGen] = NumPol - 1;
                Gbasis.push_back(NumPol - 1);
                NumGen++;
                //purge des elmt de Gbasis par le nouveau
                for (j = 0; j < NumGen - 1; j++)
                {
                    if (Monomial::getNumMonomial(_taggedPolynomialArray[Gbasis[j]].getLM()).isDivisible(lt_f))
                    { 
                        GUsed[Gbasis[j]]--;
                        for (k = j; k < NumGen - 1; k++)
                        {
                            Gbasis[k] = Gbasis[k + 1];
                        }
                        NumGen--;
                        j--;
                    }
                }
            }
        }
        step++;
        NumTot = NBEQN;
    }

}

#endif // F4_IDEAL_INL
