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
    Ideal<Element>::Ideal(std::vector<Polynomial<Element>> & polynomialArray): _polynomialArray(polynomialArray)
    {
    }
    
    
    // Destructor
    
    template <typename Element>
    Ideal<Element>::~Ideal()
    {
    }
    
    
    // Miscellaneous
    
    
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
        
        //la matrice F4
        priority_queue<TaggedPolynomial<Element>> M; 
        
        //les monomes intervenant dans M
        priority_queue<Monomial> M_mons; 
        

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
    }

}

#endif // F4_IDEAL_INL
