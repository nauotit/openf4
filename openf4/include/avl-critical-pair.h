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
  * \file avl-critical-pair.h
  * \brief Declaration of class AvlCriticalPair.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON 
  */

#ifndef OPENF4_AVL_CRITICAL_PAIR_H
#define OPENF4_AVL_CRITICAL_PAIR_H

/** \cond */
#include "global.h"
#include <iostream>
#include <cassert>
#include <iomanip>
/** \endcond */
#include "critical-pair.h"
#include "dynamic-array.h"

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \struct NodeAvlCriticalPair.
     * \brief Represent a node of the AVL of critical pairs.
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
        
            CriticalPair<Element> _cp; /*!< Critical pair. */
            signed char _bf; /*!< Balance factor. */
            NodeAvlCriticalPair* _parent; /*!< Pointer on the parent node. */
            NodeAvlCriticalPair* _left; /*!< Pointer on the left child node. */
            NodeAvlCriticalPair* _right; /*!< Pointer on the right child node. */
    };
    
    /**
     * \brief Print the AVL of root p.
     * \param p: Pointer on a node of the AVL.
     */
    template<typename Element>
    void printNode(NodeAvlCriticalPair<Element> * p, int indent=0);
    
    
    /**
     * \class AvlCriticalPair
     * \brief Represent an avl of critical pair.
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
             * \brief Test if the AVL is consistent.
             */
            void testAVL();
            
            /* Insertion */
            
            /**
             * \brief Insert the critical pair cp in the AVL.
             * \param cp: Critical pair
             * \param lt: true if numMon is a leading monomial, false otherwise.
             * \return 0 if a new NodeAvlCriticalPair is created.
             * \return 1 if cp already exist in the AVL.
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
            DynamicArray<NodeAvlCriticalPair<Element>> _array; /*!< Dynamic array of NodeAvlCriticalPair. */
            NodeAvlCriticalPair<Element> * _it; /*!< Iterator. */
            NodeAvlCriticalPair<Element> * _root; /*!< Root of the AVL. */
            size_t _size; /*!< Number of node in the AVL. */
            
            
    };
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    template <typename Element>
    std::ostream & operator<<(std::ostream & stream, AvlCriticalPair<Element> const & avlCriticalPair);
}

/** \cond */
#include "../src/avl-critical-pair.inl"
/** \endcond */

#endif // OPENF4_AVL_CRITICAL_PAIR_H
