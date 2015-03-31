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
 *  \file test-single-list.cpp
 *  \example test-single-list.cpp
 *  \brief SingleList regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include <ctime>
#include "../include/single-list.h"

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=3;

int main (int argc, char **argv)
{
    cout << endl;
    cout << "#########################################################" << endl;
    cout << "#                    TEST SINGLE LIST                   #" << endl;
    cout << "#########################################################" << endl << endl;
    
    
    typedef ElementPrime<int> eltType;
    ElementPrime<int>::setModulo(65521);
    
    // Init monomial tools
    MonomialArray monArray(6,10000000,10, 2, 10);
    Term<eltType>::setMonomialArray(&monArray);
    
    
    // Test SingleList();
    cout << "________Test SingleList()________" << endl;
    SingleList<eltType> poly1;
    
    // Test NodeList<Element> * emplaceBegin( Element coefficient, int numMonomial);
    cout << "________Test emplaceBegin( Element coefficient, int numMonomial)________" << endl;
    NodeList<eltType> * it=poly1.emplaceBegin(1, 10);
    it=poly1.emplaceAfter(it, 2, 20);
    it=poly1.emplaceAfter(it, 3, 30);
    
    // Test void printList(ostream & stream) const;
    cout << "________Test printList(ostream & stream)________" << endl;
    poly1.printList(cout);
    
    
    return 0;
}
