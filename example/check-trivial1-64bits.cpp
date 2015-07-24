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
 *  \file check-trivial1-64bits.cpp
 *  \example check-trivial1-64bits.cpp
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
    cout << "#               CHECK TRIVIAL 1 64 BITS                 #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Create polynomial array
    vector<string> polynomialArray;
    
    // Create variable name array
    vector<string> variableName;
    variableName.push_back("x");
    
    // Fill the polynomial array
    polynomialArray.emplace_back("-32567592*x^2 - 134376780*x - 99453050");
    polynomialArray.emplace_back("-102821173*x^2 - 133875255*x + 114754735");
    
    // Compute a reduce groebner basis
    vector<string> basis= groebnerBasisF4(273389687, 1, variableName, polynomialArray, 1, 0);
    
    // Fill reference vectors
    vector<string> groebnerBasis;
    groebnerBasis.push_back("(1*1)");
    
    /* 64 bits */
    bool test = true;
    size_t i = 0;
    while(i < basis.size() && test == true )
    {
        test = test && (groebnerBasis[i].compare(basis[i])==0);
        i++;
    }
    if(test==true)
    {
        cout << "Test trivial1 64 bits pass" << endl;
        return 0;
    }
    else
    {
        cout << "Test trivial1 64 bits failed" << endl;
        return -1;
    }
}


