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

/** \cond */
#include <iostream>
/** \endcond */
#include "matrix.h"
#include "avl-monomial.h"
#include "avl-polynomial.h"
#include "avl-critical-pair.h"
#include "list-pointer-critical-pair.h"

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    
    struct Stat
    {
        int _nbCp;
        int _nbCpDeg;
        int _cmptGenPurg;
        int _cmptNewGen;
        clock_t _timePurgeCp;
        clock_t _timeAddCp;
        clock_t _timeMajBasis;
        
        Stat():_nbCp(0), _nbCpDeg(0), _cmptGenPurg(0), _cmptNewGen(0), _timePurgeCp(0), _timeAddCp(0), _timeMajBasis(0)
        {
        }
    };
    
    /**
     * \class Ideal
     * Represent an ideal.
     */
    template <typename Element>
    class Ideal
    {
        public:
            
            /* Constructor */
            
            /**
             * \brief Constructor.
             * \param polynomialArray: Array of polynomials.
             * \param nbVariable: Number of variable of the polynomial ring.
             * \param degree: Initialise the monomial array up to monomial of degree "degree". 
             * \param deg1: Maximum degree of row tabulated monomials.
             * \param deg2: Maximum degree of column tabulated monomials.
             */
            Ideal(std::vector<Polynomial<Element>> & polynomialArray, int nbVariable, int capacity, int degree, int deg1, int deg2);
            
            
            /* Destructor */ 
            
            /**
             * \brief Destructor.
             */
            ~Ideal();
            
            
            /* Miscellaneous */
            
            /**
             * \brief Print _taggedPolynomialArray.
             */
            void printInfo() const;
            
            /**
             * \brief Print the reduced Groebner basis.
             */
            void printReducedGroebnerBasis(bool printBasis=false) const;
            
            /**
             * \brief Get the reduced Groebner basis as a vector of string.
             */
            std::vector<std::string> getReducedGroebnerBasis() const;
            
            /**
             * \brief Print the reduced Groebner basis in a file.
             */
            void printReducedGroebnerBasis(string const filename, long modulo) const;
            
            /**
             * \brief Print _matMons.
             */
            void printMonomialAvl() const;
            
            /**
             * \brief Print _matPols.
             */
            void printTaggedPolynomialAvl() const;
            
            /**
             * \brief Print mat.
             */
            void printMatrix (Matrix<Element> & mat, int *tabMon, int *sigma, string const & filename);
            
            
            /* Algorithms */
            
            /**
             * \brief Simplify the product u*(_taggedPolynomialArray[numList].poly) by another polynomial with the same leading term but with less terms in its tail.
             * \param u: Number of a monomial.
             * \param numList: Index of a tagged polynomial in _taggedPolynomialArray.
             * \return Index of the simplified polynomial in the array Mon_Tab.
             */
            int simplify (Monomial const & u, int numList);
            
            /**
             * \brief Update the set of critical pair and the current basis.
             * \param index: Index of a tagged polynomial in _taggedPolynomialArray.
             */
            void update(int index, bool purge, Stat & stat);
            
            /**
             * \brief Update _matPols and _matMons with the critical pair p.
             * \param p: Critical pair.
             * \param h: Height of the F4 matrix.
             * \param nbPiv: Number of pivots in the the F4 matrix.
             */
            void appendMatrixF4 (CriticalPair<Element> & p, int & h, int & nbPiv);
            
            /**
             * \brief Transform _matPols and _matMons into an almost tringular matrix.
             * \param mat: Matrix to fill.
             * \param tabMon: Array of monomials involved in _matPols.
             * \param nbPiv: Number of pivots in the the F4 matrix.
             * \param tau: tau[i]=column of the monomial tabMon[i].
             * \param sigma: sigma[i]=index in tabMon of the column i monomial.
             * \param startTail: startTail[i]=column of the first possibly non zero coefficient (in line i) after nbPiv if i < nbPiv. Otherwise startTail[i]=0.
             * \param endCol: endCol[i] = end of column i if i < nbPiv. Otherwise endCol[i]=end of column i without taking into account the lines under nbPiv.
             * \return Percentage of non zero coefficients in mat.
             */
            double transform(Matrix<Element> & mat, int *tabMon, int nbPiv, int *tau, int *sigma, int *startTail, int *endCol);
            
            /**
             * \brief Build a polynomial from a row of the F4 matrix.
             * \param tabMon: Array of monomials involved in _matPols.
             * \param width: End of the row.
             * \param start: Beginning of the row.
             * \param tau: tau[i]=column of the monomial tabMon[i].
             * \return Build polynomial.
             */
            Polynomial<Element> buildPolynomial (Element * row, int *tabMon, int width, int start, int *tau);
            
            /**
             * \brief Build a polynomial from a row of the F4 matrix.
             * \param res: Resulting polynomial.
             * \param tabMon: Array of monomials involved in _matPols.
             * \param width: End of the row.
             * \param start: Beginning of the row.
             * \param tau: tau[i]=column of the monomial tabMon[i].
             */
            void buildPolynomial (Polynomial<Element> & res, Element * row, int *tabMon, int width, int start, int *tau);
            
            /**
             * \brief Add polynomials to _matPols in order to reduced queue of current polynomials.
             * \param width: Width of the F4 matrix (number of monomials).
             * \param height: Height of the F4 matrix (number of polynomials).
             * \param nbPiv: Number of pivots in the the F4 matrix.
             */
            void preprocessing(int & width, int & height, int & nbPiv);
            
            /**
             * \brief Rebuild _matPols from mat, update the basis and the set of critical pairs.
             * \param mat: Matrix to fill.
             * \param tabMon: Array of monomials involved in _matPols.
             * \param sigma: sigma[i]=index in tabMon of the column i monomial.
             * \param tau: tau[i]=column of the monomial tabMon[i].
             * \param height: Height of the matrix before echelonize.
             * \param width: Width of the matrix before echelonize.
             * \param heightReal: Height of the matrix after echelonize.
             * \param nbPiv: Number of pivots in the the F4 matrix.
             * \return false if the computation end with a trivial groebner basis (1).
             * \return true otherwise.
             */
            bool postprocessing(Matrix<Element> & matrix, int * tabMon, int * sigma, int * tau, int height, int width, int heightReal, int nbPiv, Stat & stat);
            
            
            /* F4 Algorithm */
            
            /**
             * \brief Compute a groebner basis of this using the F4 algorithm.
             * \return Number of generators of the groebner basis.
             */
            int f4();
            
            
            
        private:
            std::vector<Polynomial<Element>> _polynomialArray; /*!< Array of polynomials */
            int _nbVariable; /*!< Number of variables of the polynomial ring. */
            int _numPol; /*!< Size of _taggedPolynomialArray */
            int _numTot; /*!< Size of _total */
            int _numGen; /*!< Size of _basis */
            std::vector<int> _total;
            std::vector<int> _used;
            std::vector<int> _basis;
            std::vector<TaggedPolynomial<Element>> _taggedPolynomialArray; /*!< Array of tagged polynomials */
            MonomialArray _monomialArray; /*!< Array of monomials, endow with a tabulated product 2D array */
            AvlCriticalPair<Element> _criticalPairSet; /*!< Set of critical pairs */
            ListPointerCriticalPair<Element> _cpSet0; /*!< List of pointers on critical pairs for update */
            ListPointerCriticalPair<Element> _cpSet1; /*!< List of pointers on critical pairs for update */
            ListPointerCriticalPair<Element> _cpSet2; /*!< List of pointers on critical pairs for update */
            DynamicArray<CriticalPair<Element>> _cpArray; /*!< Dynamic array of critical pairs used in _cpSet0, _cpSet1 and _cpSet2. */
            AvlMonomial _matMons; /*!< Monomials used in _matPols, AVL of pair (numMon, lt) decreasing order */
            AvlPolynomial _matPols; /*!< F4 Matrix = AVL of triple (tagged polynomial index, numLM, nbTerms), decreasing order */ 
    };
}

#include "../src/ideal.inl"

#endif // F4_IDEAL_H
