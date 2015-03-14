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
            void printTaggedPolynomialArray();
            
            /**
             * \brief Print M_mons.
             */
            void printMonomialMap();
            
            /**
             * \brief Print M.
             */
            void printTaggedPolynomialSet();
            
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
            void update(int index);
            
            void appendMatrixF4 (CriticalPair<Element> & p, int & h, int & nb_piv);
            
            double transform(Matrix<Element> & Mat, int *tab_mon, int nb_piv, int *tau, int *sigma, int *start_tail, int *end_col);
            
            Polynomial<Element> buildPolynomial (Element * row, int *tab_mon, int largeur, int start, int *tau);
            
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
            
            /* Monomials used in M, decreasing order */
            class cmpMonomial
            {
                public:
                    bool operator()(int a , int b)
                    {
                        return Monomial::compareNumMonomial(a,b) == 1;
                    }
            };
            map<int,bool, cmpMonomial> M_mons; 
            typename map<int,bool>::iterator itmon1;
            
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
