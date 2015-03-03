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
 *  \file test-polynomial.cpp
 *  \example test-polynomial.cpp
 *  \brief Polynomial regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include "../include/polynomial.h"

using namespace F4;
using namespace std;

int main (int argc, char **argv)
{
    // Init monomial tools
    Monomial::initMonomial(6,5,6,10,2);
    
    // Test constructor from string
    cout << "Test constructor from string " << endl;
    Polynomial<int> p1("x0+x1+x2+x3+x4+x5");
    Polynomial<int> p2("x0*x1+x1*x2+x2*x3+x3*x4+x0*x5+x4*x5");
    Polynomial<int> p3("x0*x1*x2+x1*x2*x3+x2*x3*x4+x0*x1*x5+x0*x4*x5+x3*x4*x5");
    Polynomial<int> p4("x0*x1*x2*x3+x1*x2*x3*x4+x0*x1*x2*x5+x0*x1*x4*x5+x0*x3*x4*x5+x2*x3*x4*x5");
    Polynomial<int> p5("x0*x1*x2*x3*x4+x0*x1*x2*x3*x5+x0*x1*x2*x4*x5+x0*x1*x3*x4*x5+x0*x2*x3*x4*x5+x1*x2*x3*x4*x5");
    Polynomial<int> p6("x0*x1*x2*x3*x4*x5-1");
    
    cout << "Polynomial<int> p1(\"x0+x1+x2+x3+x4+x5\"): " << endl; 
    cout << "p1: " << p1 << endl;
    cout << "Polynomial<int> p2(\"x0*x1+x1*x2+x2*x3+x3*x4+x0*x5+x4*x5\"): " << endl;
    cout << "p2: " << p2 << endl;
    cout << "Polynomial<int> p3(\"x0*x1*x2+x1*x2*x3+x2*x3*x4+x0*x1*x5+x0*x4*x5+x3*x4*x5\"): " << endl;
    cout << "p3: " << p3 << endl;
    cout << "Polynomial<int> p4(\"x0*x1*x2*x3+x1*x2*x3*x4+x0*x1*x2*x5+x0*x1*x4*x5+x0*x3*x4*x5+x2*x3*x4*x5\"): " << endl;
    cout << "p4: " << p4 << endl;
    cout << "Polynomial<int> p5(\"x0*x1*x2*x3*x4+x0*x1*x2*x3*x5+x0*x1*x2*x4*x5+x0*x1*x3*x4*x5+x0*x2*x3*x4*x5+x1*x2*x3*x4*x5\"): " << endl;
    cout << "p5: " << p5 << endl;
    cout << "Polynomial<int> p6(\"x0*x1*x2*x3*x4*x5-1\"): " << endl;
    cout << "p6: " << p6 << endl <<endl;
    
    // Test copy constructor 
    cout << "Test copy constructor " << endl;
    Polynomial<int> p7(p3);
    cout << "Polynomial<int> p7(p3) : " << p7 << endl << endl;
    
    // Test operator =
    cout << "Test operator = " << endl;
    Polynomial<int> p8;
    p8=p3;
    cout << "p8 : " << p8 << endl << endl;
    
    // Test getNbTerm(): 
    cout << "Test getNbTerm " << endl;
    cout << "p5.getNbTerm() : " << p5.getNbTerm() << endl << endl;
    
    // Free 
    p1.~Polynomial();
    p2.~Polynomial();
    p3.~Polynomial();
    p4.~Polynomial();
    p5.~Polynomial();
    p6.~Polynomial();
    p7.~Polynomial();
    p8.~Polynomial();
    
    Monomial::freeMonomial();
    
    
    return 0;
}


