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
/** \endcond */

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */

#include <set>
#include <unordered_set>

namespace F4
{
  /**
   * \struct NodeAvlMonomial.
   * \brief Represent a node of the AVL of monomials.
   */
  class AvlMonomial;
  
  struct NodeAvlMonomial
  {
  public:
    int _numMonomial;
    bool _lt;
    AvlMonomial *_parent;
    NodeAvlMonomial(AvlMonomial *a): _parent(a) {}
    void setLt();
  };
  
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
  AvlMonomial() : _node(this) {}
            
    /**
     * \brief Reset the AVL for a new usage, memory is not clear.
     */
    void reset() {
      _umon.clear();
      _mon.clear();
      _lt.clear();
    }
            
    /**
     * \brief Get the number of element in the AVL.
     * \return Number of element in the AVL.
     */
    size_t size() const {
      return _umon.size();
    }
            
    /* Insertion */
            
    /**
     * \brief If numMon if already in the AVL, update its lt flag, otherwise insert a new node.
     * \param numMon: Number of a monomial.
     * \param lt: true if numMon is a leading monomial, false otherwise.
     * \return 0 if a new NodeAvlMonomial is created.
     * \return 1 if the monomial already exist.
     * \return 2 if the monomial already exist but was not a leading term. In this case its lt flag is set to 1.
     */
    int insert(int numMon, bool lt) {
      if (_umon.insert(numMon).second == false) {
	if (lt && _lt.insert(numMon).second)
	  return 2;
 	return 1;
      }
      _mon.insert(numMon);
      if (lt)
	_lt.insert(numMon);
      return 0;
    }
            
    /**
     * \brief Find the biggest NodeAvlMonomial of the AVL.
     * \return Pointer on the biggest node.
     */
    NodeAvlMonomial * findBiggest () {
      if (_umon.empty())
	return 0;
      _it = _mon.begin();
      size_t f = *_it;
      _node._numMonomial = f;
      _node._lt = _lt.count(f);
      return &_node;
    }
      
    NodeAvlMonomial * findNextBiggest(const NodeAvlMonomial * node) {
      ++_it;
      if (_it == _mon.end())
	return 0;
      size_t i = *_it;
      _node._numMonomial = i;
      _node._lt = _lt.count(i);
      return &_node;
    }


    void setLt(int n) {
      _lt.insert(n);
    }
    
  private:
    set<int, greater<int>> _mon;
    unordered_set<int> _umon;
    unordered_set<int> _lt;
    set<int, greater<int>>::iterator _it;
    NodeAvlMonomial _node;
  };

  void NodeAvlMonomial::setLt() { _parent->setLt(_numMonomial); }
  
}

#endif // OPENF4_AVL_MONOMIAL_H
