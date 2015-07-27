/* 
 * Copyright (C) 2015 Antoine Joux, Vanessa Vitse and Titouan Coladon
 * 
 * This file is part of openf4.
 * 
 * openf4 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * openf4 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with openf4.  If not, see <http://www.gnu.org/licenses/>.
 */

  /**
  * \file avl-polynomial.h
  * \brief Declaration of class AvlPolynomial.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON 
  */

#ifndef OPENF4_AVL_POLYNOMIAL_H
#define OPENF4_AVL_POLYNOMIAL_H

/** \cond */
#include "global.h"
#include <iostream>
#include <cassert>
#include <iomanip>
/** \endcond */
#include <set>

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \struct NodeAvlPolynomial.
     * \brief Represent a node of the AVL of polynomial.
     */
    struct NodeAvlPolynomial
    {        
        public:
            /* Constructor */
            
            /**
             * \brief Constructor
             */
      NodeAvlPolynomial() {}
            /* Attributes */
      NodeAvlPolynomial(int p, int m, int t)
	: _numPolynomial(p), _numMonomial(m), _nbTerms(t) {}
      
      int _numPolynomial; /*!< Index of a tagged polynomial. */
      int _numMonomial; /*!< Number of the leading monomial of the tagged polynomial. */
      int _nbTerms; /*!< Number of terms of the tagged polynomial. */

      bool operator>(const NodeAvlPolynomial &other) const {
	if (_numMonomial > other._numMonomial)
	  return true;
	if (_numMonomial < other._numMonomial)
	  return false;
	if (_nbTerms > other._nbTerms)
	  return true;
	if (_nbTerms < other._nbTerms)
	  return false;
	if (_numPolynomial > other._numPolynomial)
	  return true;
	if (_numPolynomial < other._numPolynomial)
	  return false;
	// equal
	return false;
      }
    };
        
    
    /**
     * \class AvlPolynomial
     * \brief Represent an avl of triple (number of a polynomial, number of its leading monomial, number of terms).
     */
    class AvlPolynomial
    {        
        public:
            
            /* Constructor */
            
            /**
             * \brief Constructor
             */
      AvlPolynomial() {}
            
            
            /* Miscellaneous */
                        
            /**
             * \brief Reset the AVL for a new usage, memory is not clear.
             */
      void reset() { _set.clear(); }
            
            /**
             * \brief Get the number of element in the AVL.
             * \return Number of element in the AVL.
             */
      size_t size() const { return _set.size(); }
            
            /* Insertion */
            
            /**
             * \brief Insert a new polynomial into the AVL.
             * \param numPol: Index of the polynomial.
             * \param numMon: Number of a monomial.
             * \param nbTerms: Number of term of the polynomial.
             * \return 0 if a new polynomial is created.
             * \return 1 if the polynomial already exist.
             */
      int insert(int numPol, int numMon, int nbTerms) {
	auto t = _set.emplace(numPol, numMon, nbTerms);
	if (t.second)
	  return 0;
	return 1;
      }
            
            
            /* Search */
            
            /**
             * \brief Find the biggest node of the AVL.
             * \return Pointer on the biggest node.
             */
      NodeAvlPolynomial * findBiggest () {
	_i = _set.begin();
	if (_i == _set.end())
	  return 0;
	else
	  return const_cast<NodeAvlPolynomial *>(&*_i);
      }
            
            /**
             * \brief Find the next biggest node after node.
             * \param node: Pointer on a node.
             * \return Pointer on the next biggest node after node.
             */
      NodeAvlPolynomial * findNextBiggest(const NodeAvlPolynomial * node) {
	++_i;
	if (_i == _set.end())
	  return 0;
	else
	  return const_cast<NodeAvlPolynomial *>(&*_i);
      }
        
        private:
      set<NodeAvlPolynomial, greater<NodeAvlPolynomial>> _set;
      typename set<NodeAvlPolynomial, greater<NodeAvlPolynomial>>::iterator _i; /*!< Iterator. */
    };
    
}

#endif // OPENF4_AVL_POLYNOMIAL_H
