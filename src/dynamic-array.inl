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
  * \file dynamic-array.inl
  * \brief Definition of DynamicArray methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_DYNAMIC_ARRAY_INL
#define F4_DYNAMIC_ARRAY_INL

using namespace std;

namespace F4
{
    /* Global variables */
    
    extern int VERBOSE;
    
    
    /* Constructor */
    
    template<typename dataType>
    DynamicArray<dataType>::DynamicArray(int width, int maxHeight):_width(width), _maxHeight(maxHeight), _currentHeight(0), _colIt(0), _rowIt(0)
    {
        _array=new dataType *[maxHeight]();
    }
            
    template<typename dataType>
    DynamicArray<dataType>::DynamicArray(int width, int maxHeight, int initialCapacity):_width(width), _maxHeight(maxHeight), _currentHeight(initialCapacity), _colIt(0), _rowIt(0)
    {
        _array=new dataType *[maxHeight]();
        for(int i=0; i<_currentHeight; i++)
        {
            _array[i]=new dataType[_width]();
        }
    }
    
    
    /* Destructor */
    
    template<typename dataType>
    DynamicArray<dataType>::~DynamicArray()
    {
        for(int i=0; i<_currentHeight; i++)
        {
            if(_array[i])
            {
                delete[] _array[i];
                _array[i]=0;
            }
        }
        delete[] _array;
        _array=0;
    }
    
    
    /* Miscellaneous */
    
    template<typename dataType>
    void
    DynamicArray<dataType>::printDynamicArray(std::ostream & stream) const
    {
        bool print = false;
        stream << "Width = " << _width << ", maximum heigh = " << _maxHeight << ", current height = " << _currentHeight << endl;
        stream << "print dynamic array ?";
        cin >> print;
        if(print)
        {
            for(int i=0; i<_currentHeight; i++)
            {
                for(int j=0; j<_width; j++)
                {
                    stream << _array[i][j] << " ";
                }
                stream << endl;
            }
        }
    }
    
    template<typename dataType>
    void
    DynamicArray<dataType>::reset()
    {
        _colIt=0;
        _rowIt=0;
    }
    
    
    /* Get / Set */
            
    template<typename dataType>
    int
    DynamicArray<dataType>::getWidth()
    {
        return _width;
    }
    
    template<typename dataType>
    int
    DynamicArray<dataType>::getMaxHeight()
    {
        return _maxHeight;
    }
    
    template<typename dataType>
    int
    DynamicArray<dataType>::getCurrentHeight()
    {
        return _currentHeight;
    }
    
    
    /* Access */
    
    template<typename dataType>
    dataType &
    DynamicArray<dataType>::operator[](int index)
    {
        int quotient=index/_width;
        assert(quotient < _maxHeight);
        if(quotient>=_currentHeight)
        {
            for(int i=_currentHeight; i<=quotient; i++)
            {
                _array[i]=new dataType[_width]();
            }
            _currentHeight=quotient+1;
        }
        return _array[quotient][index%_width];
    }
        
    template<typename dataType>
    dataType const & 
    DynamicArray<dataType>::operator[](int index) const
    {
        int quotient=index/_width;
        assert(quotient < _maxHeight);
        if(quotient>=_currentHeight)
        {
            for(int i=_currentHeight; i<=quotient; i++)
            {
                _array[i]=new dataType[_width]();
            }
            _currentHeight=quotient+1;
        }
        return _array[quotient][index%_width];
    }
    
    template<typename dataType>
    dataType * 
    DynamicArray<dataType>::getBegin()
    {
        if(_currentHeight==0)
        {
            _array[0]=new dataType[_width]();
            _currentHeight=1;
        }
        return _array[0];
    }
            
    template<typename dataType>
    dataType * 
    DynamicArray<dataType>::getNext(dataType * data)
    {
        if(_rowIt<_width-1)
        {
            _rowIt++;
            return data+1;
        }
        else
        {
            _colIt++;
            assert(_colIt < _maxHeight);
            if(_currentHeight<=_colIt)
            {
                _array[_colIt]=new dataType[_width]();
                _currentHeight++;
            }
            _rowIt=0;
            return _array[_colIt];
        }
    }
    
    
    /* Operator overload */
    
    template <typename dataType>
    std::ostream & operator<<(std::ostream & stream, DynamicArray<dataType> const & dynamicArray)
    {
        dynamicArray.printDynamicArray(stream);
        return stream;
    }
    
}

#endif // F4_DYNAMIC_ARRAY_INL
