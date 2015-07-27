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
#include "dynamic-array.h"

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
            NodeAvlPolynomial();
            /* Attributes */
        
            int _numPolynomial; /*!< Index of a tagged polynomial. */
            int _numMonomial; /*!< Number of the leading monomial of the tagged polynomial. */
            int _nbTerms; /*!< Number of terms of the tagged polynomial. */
            signed char _bf; /*!< Balance factor. */
            NodeAvlPolynomial* _parent; /*!< Pointer on the parent node. */
            NodeAvlPolynomial* _left; /*!< Pointer on the left child node. */
            NodeAvlPolynomial* _right; /*!< Pointer on the right child node. */
    };
    
    /**
     * \brief Print the AVL of root p.
     * \param p: Pointer on a node of the AVL.
     */
    void printNode(NodeAvlPolynomial * p, int indent=0);
    
    
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

/** \cond */
#include "../src/avl-polynomial.inl"
/** \endcond */

#endif // OPENF4_AVL_POLYNOMIAL_H
