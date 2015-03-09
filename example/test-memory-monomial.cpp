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
 *  \file test-memory-monomial.cpp
 *  \example test-memory-monomial.cpp
 *  \brief Monomial memory regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include "../include/monomial.h"

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=2;

int main (int argc, char **argv)
{
    cout << "#########################################################" << endl;
    cout << "#                  TEST MEMORY MONOMIAL                 #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Init monomial tools
    Monomial::initMonomial(6,5,6,10);
    
    //Monomial m1(100);
    //Monomial m2("x0^2*x1^3*x2^4");
    //cout << "m1: " << m1 << endl;
    //cout << "m2: " << m2 << endl;
    //cout << "num of m2: " << m2.monomialToInt() << endl;
    //cout << "Monmial(num of m2): " << Monomial(m2.monomialToInt()) << endl;
    //cout << "m1 * m2: " << (m1*m2) << endl;
    //cout << "m1 * m2 with tabulated product: " << Monomial(Monomial::multNumMonomial(100,4967)) << endl;
    
    vector<Monomial> MonArray;
    cout << "size of MonArray: " << MonArray.size() << endl << endl;
    
    Monomial mon1(1234567);
    cout << "mon1:" << mon1 << endl;
    cout << "number of mon1: " << mon1.monomialToInt() << endl;
    MonArray = Monomial::getMonomialArray();
    cout << "size of MonArray: " << MonArray.size() << endl;
    cout << "MonArray[1234567]: " << MonArray[1234567] << endl << endl;
    
    Monomial mon2(12345678);
    cout << "mon2:" << mon2 << endl;
    cout << "number of mon2: " << mon2.monomialToInt() << endl;
    MonArray = Monomial::getMonomialArray();
    cout << "size of MonArray: " << MonArray.size() << endl;
    cout << "MonArray[12345678]: " << MonArray[12345678] << endl << endl;
    
    // Free monomial tools
    Monomial::freeMonomial();
    return 0;
}
