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
  * \file list.h
  * \brief Declaration of class SingleList.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON 
  */

#ifndef F4_SINGLE_LIST_H
#define F4_SINGLE_LIST_H

#include <iostream>
#include <cassert>

#include "term.h"

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    
    /**
     * \struct NodeList.
     * Represent a node of the single chained list.
     */
    template <typename Element>
    struct NodeList
    {        
        public:
            
            /* Constructor */
            
            /**
             * \brief Constructor
             */
            NodeList();
            
             /**
             * \brief Constructor
             */
            NodeList(Element coefficient, int numMonomial);
            
            /* Attributes */
        
            Term<Element> _term;
            NodeList * _next;
    };
    
    /**
     * \class SingleList
     * Represent a single chained list.
     */
    template <typename Element>
    class SingleList
    {        
        public:
            
            /* Constructor */
            
            /**
             * \brief Constructor.
             */
             SingleList();
             
             
             /* Destructor */
             
             /**
              * \brief Destructor.
              */
             ~SingleList();
             
             
             /* Miscellaneous */
             
             /**
              * \brief Construct a term in place at the beginning of the list.
              * \param coefficient: Coefficient of the term. 
              * \param numMonomial: Number of the monomial of the term.
              * \return Pointer on the created node.
              */
              NodeList<Element> * emplaceBegin( Element coefficient, int numMonomial);
             
             /**
              * \brief Construct a term in place after the node pointed by it.
              * \param it: Pointer on a node.
              * \param coefficient: Coefficient of the term. 
              * \param numMonomial: Number of the monomial of the term.
              * \return Pointer on the created node.
              */
              NodeList<Element> * emplaceAfter(NodeList<Element> * it, Element coefficient, int numMonomial);
              
              /**
               * \brief Print the list.
               */
               void printList(ostream & stream) const;
               
             
        private:
            
            NodeList<Element> * _list; /* Head of the list. */
    };
    
    
}

#include "../src/single-list.inl"

#endif // F4_SINGLE_LIST_H
