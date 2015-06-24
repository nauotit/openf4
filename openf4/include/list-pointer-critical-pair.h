/* 
 * Copyright (C) 2015 Antoine Joux, Vanessa Vitse and Titouan Coladon
 * 
 * This file is part of F4.
 * 
 * F4 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * F4 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with F4.  If not, see <http://www.gnu.org/licenses/>.
 */

  /**
  * \file list-pointer-critical-pair.h
  * \brief Declaration of class ListPointerCriticalPair.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON 
  */

#ifndef F4_LIST_POINTER_CRITICAL_PAIR_H
#define F4_LIST_POINTER_CRITICAL_PAIR_H

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
     * \struct NodeListPointerCriticalPair.
     * \brief Represent a node of the list.
     */
    template<typename Element>
    struct NodeListPointerCriticalPair
    {        
        public:
            
            /* Constructor */
            
            /**
             * \brief Constructor
             */
            NodeListPointerCriticalPair();
            
            /* Attributes */
        
            CriticalPair<Element> * _cp; /*!< Pointer on a critical pair */
            NodeListPointerCriticalPair * _next; /*!< Pointer on the next node. */
    };
    
    
    /**
     * \class ListPointerCriticalPair
     * \brief Represent an AVL of pointers on critical pairs.
     */
    template<typename Element>
    class ListPointerCriticalPair
    {        
        public:
            
            /* Constructor */
            
            /**
             * \brief Constructor
             */
            ListPointerCriticalPair();
            
            
            /* Miscellaneous */
            
            /**
             * \brief Print the List.
             * \param stream: Stream.
             */
            void printListCriticalPair(std::ostream & stream) const;
            
            /**
             * \brief Reset the List for a new usage, memory is not clear.
             */
            void reset();
            
            /**
             * \brief Get the first element of the list.
             */
            NodeListPointerCriticalPair<Element> const * getRoot() const;
            
            /* Insertion */
            
            /**
             * \brief Insert the critical pair pointer cp in the list.
             * \param cp: Pointer on a critical pair.
             */
            void insert(CriticalPair<Element> * cp);
            
            
            /* Access */
            
            /**
             * \brief Get the next NodeListPointerCriticalPair after node.
             * \param node: Pointer on a node.
             * \return Pointer on the next NodeListPointerCriticalPair after node.
             */
            NodeListPointerCriticalPair<Element> const * getNext(NodeListPointerCriticalPair<Element> const * node) const;
        
        private:
            DynamicArray<NodeListPointerCriticalPair<Element>> _array; /*!< Dynamic array of NodeListPointerCriticalPair. */
            NodeListPointerCriticalPair<Element> * _it; /*!< Iterator. */
            NodeListPointerCriticalPair<Element> * _root; /*!< Root of the List. */
            
            
    };
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    template <typename Element>
    std::ostream & operator<<(std::ostream & stream, ListPointerCriticalPair<Element> const & avlCriticalPair);
}

/** \cond */
#include "../src/list-pointer-critical-pair.inl"
/** \endcond */

#endif // F4_LIST_POINTER_CRITICAL_PAIR_H
