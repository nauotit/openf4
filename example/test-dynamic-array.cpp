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
 *  \file test-dynamic-array.cpp
 *  \example test-dynamic-array.cpp
 *  \brief DynamicArray regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include "../include/dynamic-array.h"

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
    
    return 0;
}
