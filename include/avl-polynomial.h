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
  * \file avl-polynomial.h
  * \brief Declaration of class AvlPolynomial.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON 
  */

#ifndef F4_AVL_POLYNOMIAL_H
#define F4_AVL_POLYNOMIAL_H

#include <iostream>
#include <cassert>
#include <iomanip>
#include "dynamic-array.h"

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \struct NodeAvlPolynomial.
     * Represent a NodeAvlPolynomial of the AVL.
     */
    struct NodeAvlPolynomial
    {        
        public:
            
            /* Constructor */
            
            /**
             * \brief Constructor
             */
            NodeAvlPolynomial();
            
            /* Attributes */
        
            int _numPolynomial;
            int _numMonomial;
            int _nbTerms;
            signed char _bf;
            NodeAvlPolynomial* _parent;
            NodeAvlPolynomial* _left;
            NodeAvlPolynomial* _right;
    };
    
    /**
     * \brief Print the AVL of root p.
     * \param p: Pointer on a NodeAvlPolynomial of an AVL.
     */
    void printNode(NodeAvlPolynomial * p, int indent=0);
    
    
    /**
     * \class AvlPolynomial
     * Represent an avl of triple (number of a polynomial, number of its leading monomial, number of terms).
     */
    class AvlPolynomial
    {        
        public:
            
            /* Constructor */
            
            /**
             * \brief Constructor
             */
            AvlPolynomial();
            
            
            /* Miscellaneous */
            
            /**
             * \brief Print the AVL.
             * \param stream: Stream.
             */
            void printAvlPolynomial(std::ostream & stream) const;
            
            /**
             * \brief Reset the AVL for a new usage, memory is not clear.
             */
            void reset();
            
            /**
             * \brief Get the number of element in the AVL.
             * \return Number of element in the AVL.
             */
            size_t size() const;
            
            /* Insertion */
            
            /**
             * \brief Insert a new polynomial into the AVL.
             * \param numPol: Index of the polynomial.
             * \param numMon: Number of a monomial.
             * \param nbTerms: Number of term of the polynomial.
             * \return 0 if a new polynomial is created.
             * \return 1 if the polynomial already exist.
             */
            int insert(int numPol, int numMon, int nbTerms);
            
            
            /* Search */
            
            /**
             * \brief Find the biggest node of the AVL.
             * \return Pointer on the biggest node.
             */
            NodeAvlPolynomial * findBiggest ();
            
            /**
             * \brief Find the biggest node of the AVL.
             * \return Pointer on the biggest node.
             */
            NodeAvlPolynomial const * findBiggest () const;
            
            /**
             * \brief Find the next biggest node after node.
             * \param node: Pointer on a node.
             * \return Pointer on the next biggest node after node.
             */
            NodeAvlPolynomial * findNextBiggest(NodeAvlPolynomial * node);
            
            /**
             * \brief Find the next biggest node after node.
             * \param node: Pointer on a node.
             * \return Pointer on the next biggest node after node.
             */
            NodeAvlPolynomial const * findNextBiggest(NodeAvlPolynomial const * node) const;
        
        private:
            DynamicArray<NodeAvlPolynomial> _array; /*!< Dynamic array of NodeAvlPolynomial. */
            NodeAvlPolynomial * _it; /*!< Iterator. */
            NodeAvlPolynomial * _root; /*!< Root of the AVL. */
            size_t _size; /*!< Number of node in the AVL. */
            
            
    };
    
    
    /* External operators */
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    template <typename dataType>
    std::ostream & operator<<(std::ostream & stream, AvlPolynomial const & AvlPolynomial);
}

#include "../src/avl-polynomial.inl"

#endif // F4_AVL_POLYNOMIAL_H
