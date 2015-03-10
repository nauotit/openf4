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
 *  \file test-ideal.cpp
 *  \example test-ideal.cpp
 *  \brief Ideal regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include "../include/ideal.h"

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=2;

int main (int argc, char **argv)
{
    cout << "#########################################################" << endl;
    cout << "#                      TEST IDEAL                       #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Init element-prime tools
    typedef ElementPrime<long> eltType;
    ElementPrime<long>::setModulo(65537);
    
    // Init monomial tools
    Monomial::initMonomial(6,5,4,6);
    
    // Create polynomial array
    vector<Polynomial<eltType>> polynomialArray;
    
    // Fill the polynomial array
    polynomialArray.emplace_back("x0+x1+x2+x3+x4+x5");
    polynomialArray.emplace_back("x0*x1+x1*x2+x2*x3+x3*x4+x0*x5+x4*x5");
    polynomialArray.emplace_back("x0*x1*x2+x1*x2*x3+x2*x3*x4+x0*x1*x5+x0*x4*x5+x3*x4*x5");
    polynomialArray.emplace_back("x0*x1*x2*x3+x1*x2*x3*x4+x0*x1*x2*x5+x0*x1*x4*x5+x0*x3*x4*x5+x2*x3*x4*x5");
    polynomialArray.emplace_back("x0*x1*x2*x3*x4+x0*x1*x2*x3*x5+x0*x1*x2*x4*x5+x0*x1*x3*x4*x5+x0*x2*x3*x4*x5+x1*x2*x3*x4*x5");
    polynomialArray.emplace_back("x0*x1*x2*x3*x4*x5-1");

    // Test Ideal(int nbVariable, int maxDegree, int deg1, int deg2, std::vector<Polynomial<Element>> & polynomialArray);
    cout << "________Test Ideal(std::vector<Polynomial<Element>> & polynomialArray)________" << endl;
    Ideal<eltType> cyclic6(polynomialArray);
    cout << endl;
    
    // Test void f4();
    cout << "________Test f4()________" << endl;
    cyclic6.f4();
    cout << endl;
    
    // Test void printTaggedPolynomialArray();
    cout << "cyclic6: " << endl;
    cyclic6.printTaggedPolynomialArray();
    cout << endl << endl;
    
    // Free monomial tools
    Monomial::freeMonomial();
    
    return 0;
}


