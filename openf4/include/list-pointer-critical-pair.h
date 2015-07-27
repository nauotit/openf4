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
  * \file list-pointer-critical-pair.h
  * \brief Declaration of class ListPointerCriticalPair.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON 
  */

#ifndef OPENF4_LIST_POINTER_CRITICAL_PAIR_H
#define OPENF4_LIST_POINTER_CRITICAL_PAIR_H

/** \cond */
#include "global.h"
#include <iostream>
#include <cassert>
#include <iomanip>
/** \endcond */
#include "critical-pair.h"

#include <vector>

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    
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
      ListPointerCriticalPair() {}
            
            /* Miscellaneous */
                        
            /**
             * \brief Reset the List for a new usage, memory is not clear.
             */
      void reset() {
	_array.clear();
      }
            
            /**
             * \brief Get the first element of the list.
             */
      size_t size() const { return _array.size(); }
            /* Insertion */
            
            /**
             * \brief Insert the critical pair pointer cp in the list.
             * \param cp: Pointer on a critical pair.
             */
      void insert(CriticalPair<Element> * cp) {
	_array.push_back(cp);
      }

      CriticalPair<Element> *operator[](size_t i) { return _array[i]; }
        
        private:
      vector< CriticalPair<Element> * > _array;
    };
    
}

#endif // OPENF4_LIST_POINTER_CRITICAL_PAIR_H
