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
  * \file single-list.h
  * \brief Declaration of class SingleList.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON 
  */

#ifndef OPENF4_SINGLE_LIST_H
#define OPENF4_SINGLE_LIST_H

/** \cond */
#include "global.h"
#include <iostream>
#include <cassert>
/** \endcond */
#include "term.h"

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    
    /**
     * \struct NodeList.
     * \brief Represent a node of the single chained list.
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
            
            /**
             * \brief Constructor
             */
            NodeList(Term<Element> const & term);
            
            
            /* Get / Set */
            
            /**
             * \brief Get the term of the node.
             * \return Term of the node.
             */
            Term<Element> const & getTerm() const; 
            
            /**
             * \brief Get the number of the monomial of the term.
             * \return Number of the monomial of the term.
             */
            int getNumMonomial() const;
            
            /**
             * \brief Get the coefficient of the term.
             * \return Coefficient of the term.
             */
            Element getCoefficient() const;
            
            /**
             * \brief Set the coefficient of the term.
             * \param element: Coefficient.
             */
            void setCoefficient(Element element);
            
            /**
             * \brief Set the coefficient of the term to one.
             */
            void setCoefficientOne();
            
            /**
             * \brief Set the number of the monomial of the term.
             * \param numMonomial: Number of the monomial of the term.
             */
            void setNumMonomial(int numMonomial);
            
            /* Attributes */
        
            Term<Element> _term; /*!< Term. */
            NodeList * _next; /*!< Pointer on a NodeList. */
    };
    
    /**
     * \class SingleList
     * \brief Represent a single chained list.
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
             
             /**
             * \brief Copy constructor.
             */
             SingleList(SingleList const & toCopy);
             
             /**
             * \brief Move constructor.
             */
             SingleList(SingleList && toCopy);
             
             
             /* Destructor */
             
             /**
              * \brief Destructor.
              */
             ~SingleList();
             
             /**
              * \brief Erase all the terms.
              */
             void clear();
             
             /**
              * \brief Erase all the terms after it, set it->_next to 0.
              * \param it: Pointer on a node.
              */
             void deleteAfter(NodeList<Element> * it);
             
             
             /* Miscellaneous */
             
             /**
              * \brief Return an iterator to the first element.
              * \return Pointer on the first node.
              */
              NodeList<Element> * getBegin() const;
             
             /**
              * \brief Return an iterator before the first element.
              * \return Pointer before the first node.
              */
              NodeList<Element> * getBeforeBegin();
             
             /**
              * \brief Test if the list is empty.
              * \return true if the list is empty.
              * \return false otherwise.
              */
              bool empty() const;
              
              /**
              * \brief Get the number of terms.
              * \return Number of terms.
              */
              int getNbTerms() const;
              
              /**
              * \brief Get the first term of the list.
              * \return First term of the list.
              */
              Term<Element> const & front() const;
             
             /**
              * \brief Construct a term in place at the beginning of the list.
              * \param coefficient: Coefficient of the term. 
              * \param numMonomial: Number of the monomial of the term.
              * \return Pointer on the created node.
              */
              NodeList<Element> * emplaceBegin(Element coefficient, int numMonomial);
             
             /**
              * \brief Construct a term in place after the node pointed by it.
              * \param it: Pointer on a node.
              * \param coefficient: Coefficient of the term. 
              * \param numMonomial: Number of the monomial of the term.
              * \return Pointer on the created node.
              */
              NodeList<Element> * emplaceAfter(NodeList<Element> * it, Element coefficient, int numMonomial);
              
              /**
              * \brief Construct a term in place after the node pointed by it.
              * \param it: Pointer on a node.
              * \param coefficient: Coefficient of the term. 
              * \param numMonomial: Number of the monomial of the term.
              * \return Pointer on the created node.
              */
              NodeList<Element> * emplaceOn(NodeList<Element> * it, Element coefficient, int numMonomial);
              
              /**
              * \brief Construct a term in place at the beginning of the list.
              * \param term: Term to insert.
              * \return Pointer on the created node.
              */
              NodeList<Element> * insertBegin(Term<Element> const & term);
             
             /**
              * \brief Construct a term in place after the node pointed by it.
              * \param it: Pointer on a node.
              * \param term: Term to insert.
              * \return Pointer on the created node.
              */
              NodeList<Element> * insertAfter(NodeList<Element> * it, Term<Element> const & term);
              
             /**
              * \brief Print the list.
              */
              void printList(ostream & stream) const;
               
             /**
              * \brief Remove the first element.
              * \return Pointer on the new first node.
              */
              NodeList<Element> *  popFront();
              
              
              /* Operator overload */
              
            /**
             * \brief Overload the operator =.
             * \param toCopy: List to copy.
             * \return Reference on this.
             */
            SingleList & operator=(SingleList const & toCopy);
            
            /**
             * \brief Overload the operator =.
             * \param toCopy: List to move.
             * \return Reference on this.
             */
            SingleList & operator=(SingleList && toCopy);
               
             
        private:
            
            NodeList<Element> * _list; /*!< Head of the list. */
            NodeList<Element> * _beforeBegin; /*!< Before the head of the list. */
            int _nbTerms; /*!< Number of terms of the list. */
    };
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    template <typename Element>
    std::ostream & operator<<(std::ostream & stream, SingleList<Element> const & list);
}

/** \cond */
#include "../src/single-list.inl"
/** \endcond */

#endif // OPENF4_SINGLE_LIST_H
