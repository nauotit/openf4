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
  * \file avl-monomial.h
  * \brief Declaration of class AvlMonomial.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON 
  */

#ifndef OPENF4_AVL_MONOMIAL_H
#define OPENF4_AVL_MONOMIAL_H

/** \cond */
#include "global.h"
#include <iostream>
#include <cassert>
#include <iomanip>
#include <unordered_set>
/** \endcond */
#include "dynamic-array.h"

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \struct NodeAvlMonomial.
     * \brief Represent a node of the AVL of monomials.
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
        
            int _numMonomial; /*!< Number of a monomial. */
            bool _lt; /*!< True if the monomial is a leading term. */
            signed char _bf; /*!< Balance factor. */
            NodeAvlMonomial* _parent; /*!< Pointer on the parent node. */
            NodeAvlMonomial* _left; /*!< Pointer on the left child node. */
            NodeAvlMonomial* _right; /*!< Pointer on the right child node. */
    };
    
    /**
     * \brief Print the AVL of root p.
     * \param p: Pointer on a node of the AVL.
     */
    void printNode(NodeAvlMonomial * p, int indent=0);
    
    
    /**
     * \class AvlMonomial
     * \brief Represent an avl of pair (number of a monomial, is leading monomial).
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
            void printAvlMonomial(std::ostream & stream) const;
            
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
             * \brief Add numMon to the unordered set _lt.
             * \param numMon: Number of a monomial.
             */
            void setLT(int numMon);
            
            
            /* Insertion */
            
            /**
             * \brief If numMon is already in the AVL, update its lt flag, otherwise insert a new node.
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
             * \brief Find the next biggest NodeAvlMonomial after node.
             * \param node: Pointer on a node.
             * \return Pointer on the next biggest NodeAvlMonomial after node.
             */
            NodeAvlMonomial * findNextBiggest(NodeAvlMonomial * node);
        
        private:
            DynamicArray<NodeAvlMonomial> _array; /*!< Dynamic array of NodeAvlMonomial. */
            unordered_set<int> _umon; /*!< Unorder set of monomial number to test membership */
            unordered_set<int> _lt; /*!< Unorder set of lt to test membership */
            NodeAvlMonomial * _it; /*!< Iterator. */
            NodeAvlMonomial * _root; /*!< Root of the AVL. */
    };
    
    
    /* External operators */
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    template <typename dataType>
    std::ostream & operator<<(std::ostream & stream, AvlMonomial const & avlMonomial);
}

/** \cond */
#include "../src/avl-monomial.inl"
/** \endcond */

#endif // OPENF4_AVL_MONOMIAL_H
