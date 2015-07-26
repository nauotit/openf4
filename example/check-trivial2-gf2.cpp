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
 *  \file check-trivial2-gf2.cpp
 *  \example check-trivial2-gf2.cpp
 *  \brief Library check tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include <string>
#include <vector>
#include <libopenf4.h>

using namespace std;

int main (int argc, char **argv)
{
    cout << "#########################################################" << endl;
    cout << "#                 CHECK RANDOM 16 BITS                  #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Create polynomial array
    vector<string> polynomialArray;
    
    // Create variable name array
    vector<string> variableName;
    for(int i = 0; i < 5; i++)
    {
        variableName.push_back('x'+to_string(i));
    }
    
    // Fill the polynomial array
    polynomialArray.emplace_back("x0^2*x1 + x1*x2*x4 + x1*x3*x4 + x4^3");
    polynomialArray.emplace_back("x0*x2*x4 + x0*x4^2");
    polynomialArray.emplace_back("x0*x1^2 + x1^2*x4 + x3*x4^2 + x1*x2 + x1*x4");
    polynomialArray.emplace_back("x2^2");
    polynomialArray.emplace_back("x0*x2*x4 + x3^2*x4 + x0*x4^2 + x3*x4");
    polynomialArray.emplace_back("x0*x1*x4 + x0^2 + x0 + x1");
    polynomialArray.emplace_back("x1*x2^2 + x0*x1*x3 + x2*x3*x4 + x0*x1");
    polynomialArray.emplace_back("x0^2*x3 + x0*x4^2 + x0*x1 + x0*x3");
    polynomialArray.emplace_back("x1^3 + x0*x4^2 + x3*x4");
    polynomialArray.emplace_back("x0^2*x4 + x1*x3*x4");
    polynomialArray.emplace_back("x0^2*x1 + x2");
    polynomialArray.emplace_back("x3");
    polynomialArray.emplace_back("x1*x2^2 + x0*x1*x3");
    polynomialArray.emplace_back("x1*x2*x3 + x2*x3^2");
    polynomialArray.emplace_back("x2^2*x3 + x3^3 + x2*x4^2");
    polynomialArray.emplace_back("x0*x2*x3 + x2*x3*x4 + x1*x3");
    polynomialArray.emplace_back("x1^2*x2 + x1*x3*x4 + x2*x3*x4 + x0*x4^2 + x3^2");
    polynomialArray.emplace_back("x0*x4^2 + x2");
    polynomialArray.emplace_back("x0*x4");
    polynomialArray.emplace_back("x1^3 + x2^3 + x3^2*x4 + x2*x3");
    polynomialArray.emplace_back("x1*x2^2");
    polynomialArray.emplace_back("x3*x4^2");
    polynomialArray.emplace_back("x0^2*x3 + x0*x1*x3 + x0*x2*x3");
    polynomialArray.emplace_back("x2*x3^2 + x3^3 + x3^2");
    polynomialArray.emplace_back("x2^3 + x1*x2*x4");
    polynomialArray.emplace_back("x2");
    polynomialArray.emplace_back("x2^2*x3 + x3*x4 + x4^2");
    polynomialArray.emplace_back("x1^2*x2 + x0*x2*x3 + x3^3 + x2*x4^2");
    polynomialArray.emplace_back("x2^3");
    polynomialArray.emplace_back("x0*x1^2 + x0^2*x2 + x0*x1");
    polynomialArray.emplace_back("x0^2*x1 + x0^2*x4 + x2*x4^2 + x0*x2");
    polynomialArray.emplace_back("x0*x1*x3 + x0*x4 + x1");
    polynomialArray.emplace_back("x3*x4^2");
    polynomialArray.emplace_back("x0^2*x2 + x0*x1*x3 + x0*x3^2 + x1^2");
    polynomialArray.emplace_back("x0*x3*x4 + x3*x4 + x4^2");
    polynomialArray.emplace_back("x1^2*x3 + x4");
    polynomialArray.emplace_back("x1*x2*x3 + x1");
    polynomialArray.emplace_back("x1*x2 + 1");
    polynomialArray.emplace_back("x3^2*x4");
    polynomialArray.emplace_back("x1*x2*x4 + x0*x4 + x2*x4");
    polynomialArray.emplace_back("x1*x2");
    polynomialArray.emplace_back("x3*x4^2 + x1 + x3 + x4");
    polynomialArray.emplace_back("x0*x1^2 + x0");
    polynomialArray.emplace_back("x0*x3 + x2*x3 + 1");
    polynomialArray.emplace_back("x1*x2^2 + x3*x4^2 + x0*x1");
    polynomialArray.emplace_back("x2^3 + x0*x4^2");
    polynomialArray.emplace_back("x1*x3*x4 + x0^2 + 1");
    polynomialArray.emplace_back("x1*x3 + x2*x4 + x4");
    polynomialArray.emplace_back("x3^2*x4 + x1*x2 + x2");
    polynomialArray.emplace_back("x0^2*x4 + x0*x3");
    polynomialArray.emplace_back("x2*x3^2 + x0*x1 + x0*x4 + x4^2");
    polynomialArray.emplace_back("x0*x3");
    polynomialArray.emplace_back("x1^2 + x3");
    polynomialArray.emplace_back("x0^2*x2 + x0*x3^2 + x0*x1*x4 + x4^2");
    polynomialArray.emplace_back("x0^2*x1 + x2*x4^2 + x2");
    polynomialArray.emplace_back("x1^2*x3 + x0*x2*x3");
    polynomialArray.emplace_back("x0*x1*x2 + x1*x3*x4 + x3*x4");
    polynomialArray.emplace_back("x1*x2*x4 + x2");
    polynomialArray.emplace_back("x0*x1*x2 + x4");
    polynomialArray.emplace_back("x0^2*x3 + x0*x3");
    polynomialArray.emplace_back("x2*x3^2 + x2^2*x4 + x0*x4^2 + x1*x2");
    polynomialArray.emplace_back("x1*x3*x4 + x2^2 + x3");
    polynomialArray.emplace_back("x1^2*x3 + x1*x4^2");
    polynomialArray.emplace_back("x2*x4 + 1");
    polynomialArray.emplace_back("x0^2*x4 + x0*x3*x4");
    polynomialArray.emplace_back("x0*x1*x3 + x1*x2*x3 + x0*x3^2 + x2*x3");
    polynomialArray.emplace_back("x1*x2^2 + x0*x3^2");
    polynomialArray.emplace_back("x1*x2*x4");
    polynomialArray.emplace_back("x3^2*x4 + x4^3");
    polynomialArray.emplace_back("x1*x2*x4 + x2^2*x4");
    polynomialArray.emplace_back("x1^3 + x2*x4^2 + x0*x4");
    polynomialArray.emplace_back("x2^2*x3");
    polynomialArray.emplace_back("x0*x1^2 + x1*x4^2 + x3*x4");
    polynomialArray.emplace_back("x0*x1*x2 + x0 + 1");
    polynomialArray.emplace_back("x0*x2*x3 + x2^2*x4 + x0*x3*x4 + x0*x3");
    polynomialArray.emplace_back("x1*x2^2 + x1*x3^2 + x1^2*x4 + x0*x4");
    polynomialArray.emplace_back("x0*x3^2 + x0*x1 + x1*x3");
    polynomialArray.emplace_back("x0*x1*x2 + x2^3");
    polynomialArray.emplace_back("x0*x2^2 + x1*x2*x3 + x0*x3^2 + x0*x2");
    polynomialArray.emplace_back("x1^3 + x3^3 + x0*x2*x4");
    polynomialArray.emplace_back("x1^2*x2 + x0*x2*x4 + x1^2");
    polynomialArray.emplace_back("x1^3 + x0 + x3");
    polynomialArray.emplace_back("x0*x2*x4 + x0*x1 + x3^2");
    polynomialArray.emplace_back("x1*x2*x3 + x1^2*x4 + x4");
    polynomialArray.emplace_back("x0*x3^2 + x2*x4");
    polynomialArray.emplace_back("0");
    polynomialArray.emplace_back("0");
    polynomialArray.emplace_back("x3*x4^2 + x0^2 + x1");
    polynomialArray.emplace_back("x0*x1*x3 + x2*x3*x4 + x4");
    polynomialArray.emplace_back("x2^3 + x0*x3^2 + x1^2*x4 + x2*x3");
    polynomialArray.emplace_back("x0*x4^2 + x2*x4^2");
    polynomialArray.emplace_back("x1*x4^2 + x1*x4 + x4");
    polynomialArray.emplace_back("x2^2");
    polynomialArray.emplace_back("x1^2*x3 + x0*x3*x4 + x1*x4^2 + x1*x4");
    polynomialArray.emplace_back("0");
    polynomialArray.emplace_back("x0*x1*x3 + x1*x3 + x4");
    polynomialArray.emplace_back("x0*x3^2 + x0*x2*x4 + x3*x4^2");
    polynomialArray.emplace_back("x0*x2^2 + x1*x2*x3 + x1*x2*x4");
    polynomialArray.emplace_back("x2^2*x4 + x0^2");
    polynomialArray.emplace_back("x1*x2^2 + x1");
    polynomialArray.emplace_back("x1*x4^2 + x2*x4 + x0");
    polynomialArray.emplace_back("x1*x2^2");
    polynomialArray.emplace_back("x0^2*x1");
    polynomialArray.emplace_back("x2*x3^2 + x0*x2 + x1*x2");
    polynomialArray.emplace_back("x0*x2*x4 + x1*x3*x4 + x2*x4");
    polynomialArray.emplace_back("x1*x3^2 + x2*x3^2 + x0*x3*x4 + x0*x1");
    polynomialArray.emplace_back("x2^3 + x1*x3^2 + x1*x4^2");
    polynomialArray.emplace_back("x2^3 + x2^2*x3");
    polynomialArray.emplace_back("x0*x2^2 + x2*x3^2 + x1*x2*x4 + x2^2");
    polynomialArray.emplace_back("x2*x3^2 + x3*x4^2 + x3*x4");
    polynomialArray.emplace_back("x1*x4^2");
    polynomialArray.emplace_back("x2 + 1");
    polynomialArray.emplace_back("x2^3 + x0*x2*x4 + x4^3");
    polynomialArray.emplace_back("x0^2*x2 + x1^2*x4 + x1*x3*x4 + x2");
    polynomialArray.emplace_back("x0*x1*x3");
    polynomialArray.emplace_back("x2^3 + x1*x2*x3 + x2*x3*x4 + x3*x4");
    polynomialArray.emplace_back("x0^2 + x0*x4");
    polynomialArray.emplace_back("x2*x3*x4");
    polynomialArray.emplace_back("x0*x1*x3 + x0*x2*x4 + x1*x4^2 + x3*x4");
    polynomialArray.emplace_back("0");
    polynomialArray.emplace_back("x0^2 + x3^2");
    polynomialArray.emplace_back("x2^2*x4 + x0*x4");
    polynomialArray.emplace_back("x2^2 + x1 + x3");
    polynomialArray.emplace_back("x1*x4^2 + x4^3");
    polynomialArray.emplace_back("x0*x1*x4");
    polynomialArray.emplace_back("x2^2*x3 + x2*x3^2 + x2*x3");
    polynomialArray.emplace_back("x1*x3^2 + x1*x3*x4 + x0*x3 + x3");
    polynomialArray.emplace_back("x0^2*x3 + x1^2*x4 + x1*x4^2");
    polynomialArray.emplace_back("0");
    polynomialArray.emplace_back("x2*x3*x4");
    polynomialArray.emplace_back("x0*x1*x4 + x0*x2*x4 + x3^2*x4 + x2*x3 + x1*x4");
    polynomialArray.emplace_back("x0^2*x1 + x1*x2*x4");
    polynomialArray.emplace_back("0");
    polynomialArray.emplace_back("x1^2*x4 + x0*x2 + x2*x4");
    polynomialArray.emplace_back("x0*x1*x4 + x2*x3*x4 + x1^2");
    polynomialArray.emplace_back("x4^2");
    polynomialArray.emplace_back("x0*x2*x3");
    polynomialArray.emplace_back("x2^3 + x0*x2*x3 + x0*x3*x4 + x2*x4");
    polynomialArray.emplace_back("x0*x3^2 + x1*x2");
    polynomialArray.emplace_back("x0*x3^2 + x1*x2 + x0*x4 + x2*x4");
    polynomialArray.emplace_back("x1^2*x3");
    polynomialArray.emplace_back("x1*x3^2 + x2^2*x4 + x4^3");
    polynomialArray.emplace_back("x0^2*x1 + x0*x2*x3 + x1*x3 + x1*x4");
    polynomialArray.emplace_back("x3^3 + x0^2 + x0*x3");
    polynomialArray.emplace_back("x1*x3^2 + x0*x2*x4 + x4^3");
    polynomialArray.emplace_back("x3^2");
    polynomialArray.emplace_back("x3^3 + x2*x3");
    polynomialArray.emplace_back("x2^2*x3 + x2*x3^2 + x0*x4");
    polynomialArray.emplace_back("x0^2*x1 + x0*x3");
    polynomialArray.emplace_back("x0*x1^2 + x0*x3^2 + x2*x3");
    polynomialArray.emplace_back("x1^2*x3 + x0*x3^2 + x4^3 + x3*x4");
    polynomialArray.emplace_back("x2^3 + x2^2*x3");
    polynomialArray.emplace_back("x2^2");
    polynomialArray.emplace_back("x1*x2*x3 + x3^3 + x0*x2 + x1*x3");
    polynomialArray.emplace_back("x0*x3*x4");
    polynomialArray.emplace_back("x2*x3 + x2*x4");
    polynomialArray.emplace_back("x0*x2*x4 + x2*x3*x4 + x0^2");
    polynomialArray.emplace_back("x2^2*x3 + x0*x3*x4");
    polynomialArray.emplace_back("x1^2*x2 + x1*x2*x4 + x1^2");
    polynomialArray.emplace_back("x2*x3^2 + x1*x2*x4 + x2^2*x4");
    polynomialArray.emplace_back("x2*x3^2 + x2*x4 + 1");
    polynomialArray.emplace_back("x1*x3^2");
    polynomialArray.emplace_back("x1*x3*x4 + x4");
    polynomialArray.emplace_back("x0^2*x3 + x1*x2*x3 + x3*x4^2 + x3^2");
    polynomialArray.emplace_back("x1^3 + x1*x2^2 + x0*x1*x3 + x1^2*x3");
    polynomialArray.emplace_back("x0*x2*x4 + x3*x4^2");
    polynomialArray.emplace_back("x0*x3^2 + x1*x3^2 + x1*x3*x4 + x2*x3");
    polynomialArray.emplace_back("x1*x2*x3 + x0*x3 + x2*x3 + x1");
    polynomialArray.emplace_back("x0*x3");
    polynomialArray.emplace_back("x0^2*x1 + x0*x3^2 + x1*x3^2 + x0*x1*x4 + x0*x4^2");
    polynomialArray.emplace_back("x3*x4^2 + 1");
    polynomialArray.emplace_back("x0*x3^2 + x3^3 + x2*x3*x4 + x0*x4");
    polynomialArray.emplace_back("x0^2*x4 + x2*x3*x4 + x1");
    polynomialArray.emplace_back("x2^3 + x0*x3^2");
    polynomialArray.emplace_back("x1^2 + x0*x3");
    polynomialArray.emplace_back("x3");
    polynomialArray.emplace_back("x1*x2*x3 + x1*x3^2 + x1*x4^2 + x0");
    polynomialArray.emplace_back("x3^2*x4 + x0*x1 + x2*x4 + x4^2");
    polynomialArray.emplace_back("0");
    polynomialArray.emplace_back("x2*x3");
    polynomialArray.emplace_back("x0*x3^2 + x0^2*x4 + x2*x3*x4 + x1^2");
    polynomialArray.emplace_back("x3^2*x4 + x4^3 + x1*x3");
    polynomialArray.emplace_back("x1^2*x4 + x0*x2");
    polynomialArray.emplace_back("x0*x2^2 + x0*x2*x3 + x0*x1 + x2");
    polynomialArray.emplace_back("x0*x2*x4 + x2*x4^2 + x3");
    polynomialArray.emplace_back("x0*x2^2 + x0*x3^2 + x0*x2");
    polynomialArray.emplace_back("x0*x2*x3 + x2*x3^2 + x0*x3*x4 + x0*x3 + x3*x4");
    polynomialArray.emplace_back("x0^2*x3 + x1*x4^2 + x3");
    polynomialArray.emplace_back("x1*x2*x3 + x3^2*x4 + x2");
    polynomialArray.emplace_back("0");
    polynomialArray.emplace_back("x0^2*x1 + x0^2*x3 + x0*x3");
    polynomialArray.emplace_back("x0^2*x2 + x0*x2*x3 + x2*x3^2 + x1*x3 + x1");
    polynomialArray.emplace_back("x0^2*x1 + x3^3");
    polynomialArray.emplace_back("x0^2*x1 + x2^3 + x3^2 + x1");
    polynomialArray.emplace_back("x0^2*x3 + x1^2*x3");
    polynomialArray.emplace_back("x1*x2^2 + x0 + x4");
    polynomialArray.emplace_back("x2*x3 + x1*x4");
    polynomialArray.emplace_back("x2^3 + x0*x3*x4");
    polynomialArray.emplace_back("x0^2*x2 + x1^2*x3 + x2^2");
    
    // Compute a reduce groebner basis
    vector<string> basis= groebnerBasisGF2F4(5, variableName, polynomialArray, 1, 0);
    
    // Fill reference vectors
    vector<string> groebnerBasis;
    groebnerBasis.push_back("(1*1)");

    /* 8 bits */
    bool test = true;
    size_t i = 0;
    while(i < basis.size() && test == true )
    {
        test = test && (groebnerBasis[i].compare(basis[i])==0);
        i++;
    }
    if(test==true)
    {
        cout << "Test trivial2 gf2 pass" << endl;
        return 0;
    }
    else
    {
        cout << "Test trivial2 gf2 failed" << endl;
        return -1;
    }
}


