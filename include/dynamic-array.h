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
  * \file dynamic-array.h
  * \brief Declaration of class DynamicArray.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON 
  */

#ifndef F4_DYNAMIC_ARRAY_H
#define F4_DYNAMIC_ARRAY_H

#include <iostream>
#include <cassert>

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \class DynamicArray
     * Represent a dynamic array whose the width is fixed, the memory is allocated by blocs.
     */
    template <typename dataType>
    class DynamicArray
    {        
        public:
            
            // Constructor
            
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
            
            
            // Destructor
            
            /**
             * \brief Destructor.
             */
            ~DynamicArray();
            
            
            // Miscellaneous
            
            void printDynamicArray(std::ostream & stream=std::cout) const;
            
            
            // Access
            
            dataType & operator[](int index);
            
            dataType const & operator[](int index) const;
            
            dataType * getBegin();
            
            dataType * getNext(dataType * data);
            
            
        private:
            
            int _width;
            int _maxHeight;
            int _currentHeight;
            
            int _colIt;
            int _rowIt;
            dataType ** _array;
        
    };
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    template <typename dataType>
    std::ostream & operator<<(std::ostream & stream, DynamicArray<dataType> const & dynamicArray);
    
}

#include "../src/dynamic-array.inl"

#endif // F4_DYNAMIC_ARRAY_H
