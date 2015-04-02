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
  * \file avl-pointer-critical-pair.h
  * \brief Declaration of class AvlPointerCriticalPair.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON 
  */

#ifndef F4_AVL_POINTER_CRITICAL_PAIR_H
#define F4_AVL_POINTER_CRITICAL_PAIR_H

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
     * \struct NodeAvlPointerCriticalPair.
     * Represent a NodeAvlPointerCriticalPair of the AVL.
     */
    template<typename Element>
    struct NodeAvlPointerCriticalPair
    {        
        public:
            
            /* Constructor */
            
            /**
             * \brief Constructor
             */
            NodeAvlPointerCriticalPair();
            
            /* Attributes */
        
            CriticalPair<Element> * _cp;
            signed char _bf;
            NodeAvlPointerCriticalPair* _parent;
            NodeAvlPointerCriticalPair* _left;
            NodeAvlPointerCriticalPair* _right;
    };
    
    /**
     * \brief Print the AVL of root p.
     * \param p: Pointer on a NodeAvlPointerCriticalPair of an AVL.
     */
    template<typename Element>
    void printNode(NodeAvlPointerCriticalPair<Element> * p, int indent=0);
    
    
    /**
     * \class AvlPointerCriticalPair
     * Represent an AVL of pointers on critical pairs.
     */
    template<typename Element>
    class AvlPointerCriticalPair
    {        
        public:
            
            /* Constructor */
            
            /**
             * \brief Constructor
             */
            AvlPointerCriticalPair();
            
            
            /* Miscellaneous */
            
            /**
             * \brief Print the AVL.
             * \param stream: Stream.
             */
            void printAvlCriticalPair(std::ostream & stream) const;
            
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
            
            /**
             * \brief Test the consistency of the AVL.
             */
            void testAVL();
            
            /* Insertion */
            
            /**
             * \brief Insert the critical pair pointer cp in the AVL.
             * \param cp: Pointer on a critical pair.
             * \return 0 if a new NodeAvlPointerCriticalPair is created.
             * \return 1 if the node already exist.
             */
            int insert(CriticalPair<Element> * cp);
            
            
            /* Search */
            
            /**
             * \brief Find the biggest NodeAvlPointerCriticalPair of the AVL.
             * \return Pointer on the biggest node.
             */
            NodeAvlPointerCriticalPair<Element> * findBiggest ();
            
            /**
             * \brief Find the biggest NodeAvlPointerCriticalPair of the AVL.
             * \return Pointer on the biggest node.
             */
            NodeAvlPointerCriticalPair<Element> const * findBiggest () const;
            
            /**
             * \brief Find the next biggest NodeAvlPointerCriticalPair after node.
             * \param node: Pointer on a node.
             * \return Pointer on the next biggest NodeAvlPointerCriticalPair after node.
             */
            NodeAvlPointerCriticalPair<Element> * findNextBiggest(NodeAvlPointerCriticalPair<Element> * node);
            
            /**
             * \brief Find the next biggest NodeAvlPointerCriticalPair after node.
             * \param node: Pointer on a node.
             * \return Pointer on the next biggest NodeAvlPointerCriticalPair after node.
             */
            NodeAvlPointerCriticalPair<Element> const * findNextBiggest(NodeAvlPointerCriticalPair<Element> const * node) const;
            
            /**
             * \brief Find the smallest NodeAvlPointerCriticalPair of the AVL.
             * \return Pointer on the smallest node.
             */
            NodeAvlPointerCriticalPair<Element> * findSmallest ();
            
            /**
             * \brief Find the smallest NodeAvlPointerCriticalPair of the AVL.
             * \return Pointer on the smallest node.
             */
            NodeAvlPointerCriticalPair<Element> const * findSmallest () const;
            
            /**
             * \brief Find the next smallest NodeAvlPointerCriticalPair after node.
             * \param node: Pointer on a node.
             * \return Pointer on the next smallest NodeAvlPointerCriticalPair after node.
             */
            NodeAvlPointerCriticalPair<Element> * findNextSmallest(NodeAvlPointerCriticalPair<Element> * node);
            
            /**
             * \brief Find the next smallest NodeAvlPointerCriticalPair after node.
             * \param node: Pointer on a node.
             * \return Pointer on the next smallest NodeAvlPointerCriticalPair after node.
             */
            NodeAvlPointerCriticalPair<Element> const * findNextSmallest(NodeAvlPointerCriticalPair<Element> const * node) const;
        
        private:
            DynamicArray<NodeAvlPointerCriticalPair<Element>> _array; /*!< Dynamic array of NodeAvlPointerCriticalPair. */
            NodeAvlPointerCriticalPair<Element> * _it; /*!< Iterator. */
            NodeAvlPointerCriticalPair<Element> * _root; /*!< Root of the AVL. */
            size_t _size; /*!< Number of node in the AVL. */
            
            
    };
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    template <typename Element>
    std::ostream & operator<<(std::ostream & stream, AvlPointerCriticalPair<Element> const & avlCriticalPair);
}

#include "../src/avl-pointer-critical-pair.inl"

#endif // F4_AVL_POINTER_CRITICAL_PAIR_H
