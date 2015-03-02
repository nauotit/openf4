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
    // First we set the number of variable of the polynomial ring.
    Monomial::setNbVariable(4);
    // Then their names:
    string vars[4]={"s1","s2","s3","s4"};
    Monomial::setVariable(vars);
    // Then the weight
    int weight[4]={1,1,1,1};
    Monomial::setWeight(weight);
    // Then the 2D array NB_MONOMIAL:
    Monomial::setNbMonomial(30);
    // Verbose mode
    Monomial::setVerbose(2);
    
    // Test constructor from string
    Polynomial<int> p1("2*s1+3*s2+5*s3+1*s4");
    cout << "p1: " << p1 << endl;
    
    Polynomial<int> p2("-2*s1+s2+s3+s4");
    cout << "p2: " << p2 << endl;
    
    Polynomial<int> p3("s1*s2*s3*s4 -1");
    cout << "p3: " << p3 << endl;
    
    p1.~Polynomial();
    p2.~Polynomial();
    p3.~Polynomial();
    
    Monomial::freeNbMonomial(30);
    
    
    
    return 0;
}


