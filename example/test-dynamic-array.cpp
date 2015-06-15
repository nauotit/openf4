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
 *  \file test-dynamic-array.cpp
 *  \example test-dynamic-array.cpp
 *  \brief DynamicArray regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include "../f4/include/dynamic-array.h"

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=2;

int main (int argc, char **argv)
{
    cout << "#########################################################" << endl;
    cout << "#                    TEST DYNAMIC ARRAY                 #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Test DynamicArray(int width, int maxHeight);
    cout << "________Test DynamicArray(int width, int maxHeight)________" << endl;
    DynamicArray<int> da1(1000,10);
    cout << endl << endl;
    
    
    // Test DynamicArray(int width, int maxHeight, int initialCapacity);
    cout << "________Test DynamicArray(int width, int maxHeight, int initialCapacity)________" << endl;
    DynamicArray<int> da2(1000,10,3);
    cout << endl << endl;
    
    // Test dataType & operator[](int index);
    cout << "________Test dataType & operator[](int index)________" << endl;
    DynamicArray<int> da3(20,10,3);
    da3[0]=1;
    da3[1]=2;
    da3[19]=20;
    da3[25]=26;
    da3[50]=51;
    da3[65]=66;
    da3[165]=166;
    //da3[210]=211; // assert failed -> maxHeight not sufficient
    cout << "da3 : " << da3 << endl << endl;
    
    // Test dataType * getBegin();
    cout << "________Test getBegin()________" << endl;
    int * it = da3.getBegin();
    cout << "First element of da3: " << *it << endl << endl;
    
    // Test getNext(dataType * data);
    cout << "________Test getNext(dataType * data)________" << endl;
    while(*it != 166)
    {
        if(*it)
        {
            cout << *it << " ";
        }
        it=da3.getNext(it);
    }
    cout << endl << endl;
    
    // Test int getWidth();
    cout << "________Test getWidth()________" << endl;
    cout << "Width = " << da3.getWidth() << endl << endl;
            
    // Test int getMaxHeight();
    cout << "________Test getMaxHeight()________" << endl;
    cout << "Maximum height = " << da3.getMaxHeight() << endl << endl;
            
    // Test int getCurrentHeight();
    cout << "________Test getCurrentHeight()________" << endl;
    cout << "Current height = " << da3.getCurrentHeight() << endl << endl;
    
    // Test void reset();
    cout << "________Test reset()________" << endl;
    da3.reset();
    cout << endl << endl;
    
    return 0;
}
