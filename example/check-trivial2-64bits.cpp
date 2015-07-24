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
 *  \file check-trivial2-64bits.cpp
 *  \example check-trivial2-64bits.cpp
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
    cout << "#              CHECK TRIVIAL 2 64 BITS                  #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Create polynomial array
    vector<string> polynomialArray;
    
    // Create variable name array
    vector<string> variableName;
    for(int i = 0; i < 3; i++)
    {
        variableName.push_back('x'+to_string(i));
    }
    
    // Fill the polynomial array
    polynomialArray.emplace_back("-381588408*x0^2 + 476686997*x2^2 - 462809584*x0 + 257786256*x2 - 114361905");
    polynomialArray.emplace_back("-165319008*x0^2 + 74443335*x0*x2 - 139862633*x2^2 - 274498434*x0 + 48302322");
    polynomialArray.emplace_back("-462665673*x0^2 + 458273559*x2^2 - 602419172*x0 + 103972832*x2 - 383910315");
    
    // Compute a reduce groebner basis
    vector<string> basis= groebnerBasisF4(1217734367, 3, variableName, polynomialArray, 1, 0);
    
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
        cout << "Test trivial2 64 bits pass" << endl;
        return 0;
    }
    else
    {
        cout << "Test trivial2 64 bits failed" << endl;
        return -1;
    }
}


