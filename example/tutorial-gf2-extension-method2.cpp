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
 *  \file tutorial-gf2-extension-method2.cpp
 *  \example tutorial-gf2-extension-method2.cpp
 *  \brief Tutorial with f4 library use for GF(2^n) with n < 64.
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
    cout << "#               TUTORIAL WITH LIBRARY USE               #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Create polynomial array.
    vector<string> polynomialArray;
    
    // Create variable name array.
    vector<string> variableName;
    for(int i = 0; i < 6; i++)
    {
        variableName.push_back('x'+to_string(i));
    }
    
    // Fill the polynomial array.
    polynomialArray.emplace_back("(t+t^3)*x0+(t+t^3)*x1+(t+t^3)*x2+(t+t^3)*x3+(t+t^3)*x4+(t+t^3)*x5");
    polynomialArray.emplace_back("(t+t^3)*x0*x1+(t+t^3)*x1*x2+(t+t^3)*x2*x3+(t+t^3)*x3*x4+(t+t^3)*x0*x5+(t+t^3)*x4*x5");
    polynomialArray.emplace_back("(t+t^3)*x0*x1*x2+(t+t^3)*x1*x2*x3+(t+t^3)*x2*x3*x4+(t+t^3)*x0*x1*x5+(t+t^3)*x0*x4*x5+(t+t^3)*x3*x4*x5");
    polynomialArray.emplace_back("(t+t^3)*x0*x1*x2*x3+(t+t^3)*x1*x2*x3*x4+(t+t^3)*x0*x1*x2*x5+(t+t^3)*x0*x1*x4*x5+(t+t^3)*x0*x3*x4*x5+(t+t^3)*x2*x3*x4*x5");
    polynomialArray.emplace_back("(t+t^3)*x0*x1*x2*x3*x4+(t+t^3)*x0*x1*x2*x3*x5+(t+t^3)*x0*x1*x2*x4*x5+(t+t^3)*x0*x1*x3*x4*x5+(t+t^3)*x0*x2*x3*x4*x5+(t+t^3)*x1*x2*x3*x4*x5");
    polynomialArray.emplace_back("(t+t^3)*x0*x1*x2*x3*x4*x5-1");
    
    // Compute a reduce groebner basis.
    vector<string> basis = groebnerBasisGF2ExtensionF4("t^63 + t^61 + t^57 + t^56 + t^54 + t^51 + t^47 + t^46 + t^45 + t^44 + t^43 + t^42 + t^39 + t^38 + t^35 + t^34 + t^32 + t^31 + t^28 + t^25 + t^24 + t^23 + t^21 + t^19 + t^18 + t^17 + t^15 + t^13 + t^10 + t^8 + t^7 + t^5 + t^2 + t + 1", 6, variableName, "t", polynomialArray, 1, 0);
    
    // Print the reduce groebner basis.
    for(size_t i = 0; i < basis.size(); i++)
    {
        cout << basis[i] << endl;
    }
}
