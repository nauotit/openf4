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
 *  \file check-trivial1-gf2-extension-32bits.cpp
 *  \example check-trivial1-gf2-extension-32bits.cpp
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
    cout << "#         CHECK TRIVIAL1 GF2 EXTENSION 32 BITS          #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Create polynomial array
    vector<string> polynomialArray;
    
    // Create variable name array
    vector<string> variableName;
    variableName.push_back("x");
    
    // Fill the polynomial array
    polynomialArray.emplace_back("0");
    
    // Compute a reduce groebner basis
    vector<string> basis= groebnerBasisGF2ExtensionF4("k^21 + k^12 + k^11 + k^9 + k^7 + k^6 + k^5 + k^3 + 1", 1, variableName, "k", polynomialArray, 1, 0);
    
    // Fill reference vectors
    vector<string> groebnerBasis;
    groebnerBasis.push_back("((0)*1)");

    /* 16 bits */
    bool test = true;
    size_t i = 0;
    while(i < basis.size() && test == true )
    {
        test = test && (groebnerBasis[i].compare(basis[i])==0);
        i++;
    }
    if(test==true)
    {
        cout << "Test trivial1 gf2 extension 32 bits pass" << endl;
        return 0;
    }
    else
    {
        cout << "Test trivial1 gf2 extension 32 bits failed" << endl;
        return -1;
    }
}


