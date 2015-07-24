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
  * \file dynamic-array.h
  * \brief Declaration of class DynamicArray.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON 
  */

#ifndef OPENF4_DYNAMIC_ARRAY_H
#define OPENF4_DYNAMIC_ARRAY_H

/** \cond */
#include "global.h"
#include <iostream>
#include <cassert>
/** \endcond */

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \class DynamicArray
     * \brief Represent a dynamic array whose the width is fixed, the memory is allocated by blocs.
     */
    template <typename dataType>
    class DynamicArray
    {        
        public:
            
            /* Constructor */
            
            /**
             * \brief Constructor.
             * \param width: Width of the array (size of a memory block).
             * \param maxHeight: Maximum height of the dynamic array. The maximal capacity of this array will be width * maxHeight.
             */
            DynamicArray(int width, int maxHeight);
            
            /**
             * \brief Constructor.
             * \param width: Width of the array (size of a memory block).
             * \param maxHeight: Maximum height of the dynamic array. The maximal capacity of this array will be width * maxHeight.
             * \param initialCapacity: initial number of allocated rows.
             */
            DynamicArray(int width, int maxHeight, int initialCapacity);
            
            
            /* Destructor */
            
            /**
             * \brief Destructor.
             */
            ~DynamicArray();
            
            
            /* Miscellaneous */
            
            /**
             * \brief Print the dynamic array.
             */
            void printDynamicArray(std::ostream & stream=std::cout) const;
            
            /**
             * \brief Reset the dynamic array, do not free the memory.
             */
            void reset();
            
            
            /* Get / Set */
            
            /**
             * \brief Get the width of the dynamic array.
             */
            int getWidth();
            
            /**
             * \brief Get the maximum height of the dynamic array.
             */
            int getMaxHeight();
            
            /**
             * \brief Get the current height of the dynamic array.
             */
            int getCurrentHeight();
            
            
            /* Access */
            
            /**
             * \brief Overload the operator [].
             * \return Reference on a cell of the dynamic array.
             */
            dataType & operator[](int index);
            
            /**
             * \brief Overload the operator [].
             * \return Reference on a cell of the dynamic array.
             */
            dataType const & operator[](int index) const;
            
            /**
             * \brief Get an iterator to the beginning of the array.
             * \return Pointer on a cell of the dynamic array.
             */
            dataType * getBegin();
            
            /**
             * \brief Get an iterator to next data after data.
             * \param data: Pointer on a cell of the dynamic array.
             * \return Pointer on a cell of the dynamic array.
             */
            dataType * getNext(dataType * data);
            
            
        private:
            
            int _width; /*!< Width of the 2D array */
            int _maxHeight; /*!< Maximum height of the 2D array */
            int _currentHeight; /*!< Number of allocated rows in the 2D array */
            
            int _colIt; /*!< Column iterator */
            int _rowIt; /*!< Row iterator */
            dataType ** _array; /*!< 2 dimensionnal array */
        
    };
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    template <typename dataType>
    std::ostream & operator<<(std::ostream & stream, DynamicArray<dataType> const & dynamicArray);
    
}

/** \cond */
#include "../src/dynamic-array.inl"
/** \endcond */

#endif // OPENF4_DYNAMIC_ARRAY_H
