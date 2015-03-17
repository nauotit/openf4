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
  * \file ideal.h
  * \brief Declaration of class Ideal.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_IDEAL_H
#define F4_IDEAL_H

#include <iostream>
#include <set>
#include <map>
#include "critical-pair.h"
#include "matrix.h"

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    template <typename Element>
    class TaggedPolynomialIndex
    {
        public:
        
            // Static methods
            
            /**
             * \brief Set the array of tagged polynomial to use.
             * \param taggedPolynomialArray: Address of the array.
             */
            static void setTaggedPolynomialArray(vector<TaggedPolynomial<Element>> * taggedPolynomialArray);
            
            
            // Constructor
            
            TaggedPolynomialIndex(int index):_index(index)
            {
            }
            
            TaggedPolynomialIndex():_index(-1)
            {
            }
            
            // Get / Set
            
            int getIndex() const
            {
                return _index;
            }
            
            void setIndex(int index)
            {
                _index=index;
            }
            
            // Miscellaneous
            
            int compareTaggedPolynomialIndex(TaggedPolynomialIndex const & index) const
            {
                int res=((*TAGGEG_POLYNOMIAL_ARRAY)[_index]).compareTaggedPolynomial((*TAGGEG_POLYNOMIAL_ARRAY)[index._index]);
                if (res==0)
                {
                    if (_index > index._index)
                    {
                        return 1;
                    }
                    else if (_index < index._index)
                    {
                        return -1;
                    }
                }
                return res;
            }
            
        private: 
            int _index;
            
            static std::vector<TaggedPolynomial<Element>> * TAGGEG_POLYNOMIAL_ARRAY; /*!< Pointer on a dynamic array of TaggedPolynomial */
    };
    
    template <typename Element>
    vector<TaggedPolynomial<Element>> * TaggedPolynomialIndex<Element>::TAGGEG_POLYNOMIAL_ARRAY=0;
    
    template <typename Element>
    void
    TaggedPolynomialIndex<Element>::setTaggedPolynomialArray(vector<TaggedPolynomial<Element>> * taggedPolynomialArray)
    {
        TAGGEG_POLYNOMIAL_ARRAY=taggedPolynomialArray;
    }
    
    
    /**
     * \class Ideal
     * Represent an ideal.
     */
    template <typename Element>
    class Ideal
    {
        public:
            
            // Constructor
            
            /**
             * \brief Constructor.
             * \param polynomialArray: Array of polynomials.
             */
            Ideal(std::vector<Polynomial<Element>> & polynomialArray);
            
            
            // Destructor 
            
            /**
             * \brief Destructor.
             */
            ~Ideal();
            
            
            // Miscellaneous
            
            /**
             * \brief Print _taggedPolynomialArray.
             */
            void printInfo() const;
            
            /**
             * \brief Print printReducedGroebnerBasis.
             */
            void printReducedGroebnerBasis() const;
            
            /**
             * \brief Print M_mons.
             */
            void printMonomialMap() const;
            
            /**
             * \brief Print M.
             */
            void printTaggedPolynomialSet() const;
            
            /**
             * \brief Print Mat.
             */
            void printMatrix (Matrix<Element> & Mat, int *tab_mon, int *sigma, string const & filename) const;
            
            /**
             * \brief Simplify the product u*(_taggedPolynomialArray[numList].poly) by another polynomial with the same leading term but with less terms in its tail.
             * \param u: Number of a monomial.
             * \param numList: Index of a tagged polynomial in _taggedPolynomialArray.
             * \return Index of the simplified polynomial in the array Mon_Tab.
             */
            int simplify (int u, int numList);
            
            /**
             * \brief Update the set of critical pair and the current basis.
             * \param index: Index of a tagged polynomial in _taggedPolynomialArray.
             */
            void update(int index, int & cmpt_genpurg, double &time_purgeCP, double & time_addCP, double & time_majBasis);
            
            /**
             * \brief Update M and M_mons with the critical pair p.
             * \param p: Critical pair.
             * \param h: Height of the F4 matrix.
             * \param nb_piv: Number of pivots in the the F4 matrix.
             */
            void appendMatrixF4 (CriticalPair<Element> & p, int & h, int & nb_piv);
            
            /**
             * \brief Transform M and M_mons into an almost tringular matrix.
             * \param Mat: Matrix to fill.
             * \param tab_mon: Array of monomials involved in M.
             * \param nb_piv: Number of pivots in the the F4 matrix.
             * \param tau: tau[i]=column of the monomial tab_mon[i].
             * \param sigma: sigma[i]=index in tab_mon of the column i monomial.
             * \param start_tail: start_tail[i]=column of the first possibly non zero coefficient (in line i) after nb_piv if i < nb_piv. Otherwise start_tail[i]=0.
             * \param end_col: end_col[i] = end of column i if i < nb_piv. Otherwise end_col[i]=end of column i without taking into account the lines under nb_piv.
             * \return Percentage of non zero coefficients in Mat.
             */
            double transform(Matrix<Element> & Mat, int *tab_mon, int nb_piv, int *tau, int *sigma, int *start_tail, int *end_col);
            
            /**
             * \brief Build a polynomial from a row of the F4 matrix.
             * \param tab_mon: Array of monomials involved in M.
             * \param largeur: End of the row.
             * \param start: Beginning of the row.
             * \param tau: tau[i]=column of the monomial tab_mon[i].
             */
            Polynomial<Element> buildPolynomial (Element * row, int *tab_mon, int largeur, int start, int *tau);
            
            /**
             * \brief Add polynomials to M in order to reduced queue of current polynomials.
             * \param largeur: Width of the F4 matrix (number of monomials).
             * \param height: Height of the F4 matrix (number of polynomials).
             * \param nb_piv: Number of pivots in the the F4 matrix.
             */
            void preprocessing(int & largeur, int & hauteur, int & nb_piv);
            
            // F4 Algorithm
            
            /**
             * \brief Compute a groebner basis of this using the F4 algorithm.
             */
            int f4();
            
            
            
        private:
            std::vector<Polynomial<Element>> _polynomialArray; /*!< Array of polynomials */
            int _nbVariable; /*!< Number of variables of the polynomial ring. */
            int NumPol; /*!< TODO : suppress */
            int NumTot; /*!< TODO : suppress */
            int NumGen; /*!< TODO : suppress */
            int nbCP; /*!< TODO : suppress */ // nbre de paires critiques en attente de traitement
            std::vector<int> GTotal;
            std::vector<int> GUsed;
            std::vector<int> Gbasis;
            std::vector<TaggedPolynomial<Element>> _taggedPolynomialArray; /*!< Array of tagged polynomials */
            set<CriticalPair<Element>> _criticalPairSet; /*!< Set of critical pairs */
            map<int,bool, std::greater<int>> M_mons; /*!< Monomials used in M, decreasing order */
            
            /* F4 Matrix = set of tagged polynomial index, decreasing order */ 
            struct cmpTaggedPolynomial
            {
                public:
                    bool operator()(TaggedPolynomialIndex<Element> const & a , TaggedPolynomialIndex<Element> const & b)
                    {
                        return a.compareTaggedPolynomialIndex(b) == 1;
                    }
            };
            set<TaggedPolynomialIndex<Element>, cmpTaggedPolynomial> M;
    };
}

#include "../src/ideal.inl"

#endif // F4_IDEAL_H
