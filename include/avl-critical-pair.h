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
  * \file avl-critical-pair.h
  * \brief Declaration of class AvlCriticalPair.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON 
  */

#ifndef F4_AVL_CRITICAL_PAIR_H
#define F4_AVL_CRITICAL_PAIR_H

#include <iostream>
#include <cassert>
#include <iomanip>
#include "critical-pair.h"
#include "dynamic-array.h"

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \struct NodeAvlCriticalPair.
     * Represent a NodeAvlCriticalPair of the AVL.
     */
    template<typename Element>
    struct NodeAvlCriticalPair
    {        
        public:
            
            /* Constructor */
            
            /**
             * \brief Constructor
             */
            NodeAvlCriticalPair();
            
            /* Attributes */
        
            CriticalPair<Element> _cp;
            signed char _bf;
            NodeAvlCriticalPair* _parent;
            NodeAvlCriticalPair* _left;
            NodeAvlCriticalPair* _right;
    };
    
    /**
     * \brief Print the AVL of root p.
     * \param p: Pointer on a NodeAvlCriticalPair of an AVL.
     */
    template<typename Element>
    void printNode(NodeAvlCriticalPair<Element> * p, int indent=0);
    
    
    /**
     * \class AvlCriticalPair
     * Represent an avl of pair (number of a monomial, is leading monomial).
     */
    template<typename Element>
    class AvlCriticalPair
    {        
        public:
            
            /* Constructor */
            
            /**
             * \brief Constructor
             */
            AvlCriticalPair();
            
            
            /* Miscellaneous */
            
            /**
             * \brief Print the AVL.
             * \param stream: Stream.
             */
            void printAvlCriticalPair(std::ostream & stream=std::cout) const;
            
            /**
             * \brief Reset the AVL for a new usage, memory is not clear.
             */
            void reset();
            
            /**
             * \brief Get the number of element in the AVL.
             * \return Number of element in the AVL.
             */
            size_t size() const;
            
            /**
             * \brief Test if the AVL is empty.
             * \return true if the AVL is empty.
             * \return false otherwise.
             */
            bool isEmpty() const;
            
            void testAVL();
            
            /* Insertion */
            
            /**
             * \brief If numMon if already in the AVL, update its lt flag, otherwise insert a new node.
             * \param numMon: Number of a monomial.
             * \param lt: true if numMon is a leading monomial, false otherwise.
             * \return 0 if a new NodeAvlCriticalPair is created.
             * \return 1 if the monomial already exist.
             * \return 2 if the monomial already exist but was not a leading term. In this case its lt flag is set to 1.
             */
            int insert(CriticalPair<Element> cp);
            
            
            /* Deletion */
            
            /**
             * \brief Delete the node pointed by node from the AVL.
             * \pre node belongs to the avl, if node = 0, the AVL is clear.
             * \param node: Pointer on a node.
             * \return Pointer the deleted node.
             */
            NodeAvlCriticalPair<Element> * erase(NodeAvlCriticalPair<Element> * node);
            
            
            /* Search */
            
            /**
             * \brief Find the biggest NodeAvlCriticalPair of the AVL.
             * \return Pointer on the biggest node.
             */
            NodeAvlCriticalPair<Element> * findBiggest ();
            
            /**
             * \brief Find the biggest NodeAvlCriticalPair of the AVL.
             * \return Pointer on the biggest node.
             */
            NodeAvlCriticalPair<Element> const * findBiggest () const;
            
            /**
             * \brief Find the next biggest NodeAvlCriticalPair after node.
             * \param node: Pointer on a node.
             * \return Pointer on the next biggest NodeAvlCriticalPair after node.
             */
            NodeAvlCriticalPair<Element> * findNextBiggest(NodeAvlCriticalPair<Element> * node);
            
            /**
             * \brief Find the next biggest NodeAvlCriticalPair after node.
             * \param node: Pointer on a node.
             * \return Pointer on the next biggest NodeAvlCriticalPair after node.
             */
            NodeAvlCriticalPair<Element> const * findNextBiggest(NodeAvlCriticalPair<Element> const * node) const;
            
            /**
             * \brief Find the smallest NodeAvlCriticalPair of the AVL.
             * \return Pointer on the smallest node.
             */
            NodeAvlCriticalPair<Element> * findSmallest ();
            
            /**
             * \brief Find the smallest NodeAvlCriticalPair of the AVL.
             * \return Pointer on the smallest node.
             */
            NodeAvlCriticalPair<Element> const * findSmallest () const;
            
            /**
             * \brief Find the next smallest NodeAvlCriticalPair after node.
             * \param node: Pointer on a node.
             * \return Pointer on the next smallest NodeAvlCriticalPair after node.
             */
            NodeAvlCriticalPair<Element> * findNextSmallest(NodeAvlCriticalPair<Element> * node);
            
            /**
             * \brief Find the next smallest NodeAvlCriticalPair after node.
             * \param node: Pointer on a node.
             * \return Pointer on the next smallest NodeAvlCriticalPair after node.
             */
            NodeAvlCriticalPair<Element> const * findNextSmallest(NodeAvlCriticalPair<Element> const * node) const;
        
        private:
            DynamicArray<NodeAvlCriticalPair<Element>> _array;
            NodeAvlCriticalPair<Element> * _it;
            NodeAvlCriticalPair<Element> * _root;
            size_t _size;
            
            
    };
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    template <typename Element>
    std::ostream & operator<<(std::ostream & stream, AvlCriticalPair<Element> const & avlCriticalPair);
}

#include "../src/avl-critical-pair.inl"

#endif // F4_AVL_CRITICAL_PAIR_H
