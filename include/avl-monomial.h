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
  * \file avl-monomial.h
  * \brief Declaration of class AvlMonomial.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON 
  */

#ifndef F4_AVL_MONOMIAL_H
#define F4_AVL_MONOMIAL_H

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
     * \struct NodeAvlMonomial.
     * Represent a NodeAvlMonomial of the AVL.
     */
    struct NodeAvlMonomial
    {        
        public:
            
            /* Constructor */
            
            /**
             * \brief Constructor
             */
            NodeAvlMonomial();
            
            /* Attributes */
        
            int _numMonomial;
            bool _lt;
            signed char _bf;
            NodeAvlMonomial* _parent;
            NodeAvlMonomial* _left;
            NodeAvlMonomial* _right;
    };
    
    /**
     * \brief Print the AVL of root p.
     * \param p: Pointer on a NodeAvlMonomial of an AVL.
     */
    void printNode(NodeAvlMonomial * p, int indent=0);
    
    
    /**
     * \class AvlMonomial
     * Represent an avl of pair (number of a monomial, is leading monomial).
     */
    class AvlMonomial
    {        
        public:
            
            /* Constructor */
            
            /**
             * \brief Constructor
             */
            AvlMonomial();
            
            
            /* Miscellaneous */
            
            /**
             * \brief Print the AVL.
             * \param stream: Stream.
             */
            void printAvlMonomial(std::ostream & stream=std::cout) const;
            
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
             * \brief If numMon if already in the AVL, update its lt flag, otherwise insert a new node.
             * \param numMon: Number of a monomial.
             * \param lt: true if numMon is a leading monomial, false otherwise.
             * \return 0 if a new NodeAvlMonomial is created.
             * \return 1 if the monomial already exist.
             * \return 2 if the monomial already exist but was not a leading term. In this case its lt flag is set to 1.
             */
            int insert(int numMon, bool lt);
            
            
            /* Search */
            
            /**
             * \brief Find the biggest NodeAvlMonomial of the AVL.
             * \return Pointer on the biggest node.
             */
            NodeAvlMonomial * findBiggest ();
            
            /**
             * \brief Find the biggest NodeAvlMonomial of the AVL.
             * \return Pointer on the biggest node.
             */
            NodeAvlMonomial const * findBiggest () const;
            
            /**
             * \brief Find the next biggest NodeAvlMonomial after node.
             * \param node: Pointer on a node.
             * \return Pointer on the next biggest NodeAvlMonomial after node.
             */
            NodeAvlMonomial * findNextBiggest(NodeAvlMonomial * node);
            
            /**
             * \brief Find the next biggest NodeAvlMonomial after node.
             * \param node: Pointer on a node.
             * \return Pointer on the next biggest NodeAvlMonomial after node.
             */
            NodeAvlMonomial const * findNextBiggest(NodeAvlMonomial const * node) const;
        
        private:
            DynamicArray<NodeAvlMonomial> _array;
            NodeAvlMonomial * _it;
            NodeAvlMonomial * _root;
            size_t _size;
            
            
    };
    
    
    /* External operators */
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    template <typename dataType>
    std::ostream & operator<<(std::ostream & stream, AvlMonomial const & avlMonomial);
}

#include "../src/avl-monomial.inl"

#endif // F4_AVL_MONOMIAL_H
