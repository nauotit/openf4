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
 *  \file check-random-64bits.cpp
 *  \example check-random-64bits.cpp
 *  \brief Library check tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include <string>
#include <vector>
#include <libf4.h>

using namespace std;

int main (int argc, char **argv)
{
    cout << "#########################################################" << endl;
    cout << "#                 CHECK RANDOM 64 BITS                  #" << endl;
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
    polynomialArray.emplace_back("-67903332*x0*x2^2 + 75795853*x0*x3^2 - 77876537*x0^2 - 68654934*x1 - 110666967");
    polynomialArray.emplace_back("-86462958*x0^2*x1 - 156974227*x0^2*x2 + 94227320*x0^2 - 121068676*x1*x3 + 383807976*x2*x4");
    polynomialArray.emplace_back("-350205823*x1^2*x4 - 209659308*x1*x3*x4 - 161169513*x0*x2 + 257797958*x1*x4 - 208472984*x4");
    polynomialArray.emplace_back("-230331186*x0*x1*x2 + 301656182*x2^3 + 151924179*x1^2*x3 + 36652593*x0*x4^2 - 5590016*x3*x4^2");
    polynomialArray.emplace_back("296066009*x2^2*x3 - 170271076*x0*x1*x4 + 199165238*x0*x4^2 + 313864578*x0^2 + 397526485*x4^2");
    polynomialArray.emplace_back("203697918*x0*x1*x3 - 167650883*x2^2*x4 + 37458212*x2*x3 - 9502594*x3^2 + 194478864*x4^2");
    
    // Compute a reduce groebner basis
    vector<string> basis= groebnerBasisF4(805922797LL, 5, variableName, polynomialArray, 1, 0);
    
    // Fill reference vectors
    vector<string> groebnerBasis;
    groebnerBasis.push_back("(1*x2^3) + (-102475207*x3^1) + (-355538109*x4^1)");
    groebnerBasis.push_back("(1*x0^2)");
    groebnerBasis.push_back("(1*x0^1*x2^1) + (-267894235*x4^1)");
    groebnerBasis.push_back("(1*x0^1*x3^1)");
    groebnerBasis.push_back("(1*x2^1*x3^1)");
    groebnerBasis.push_back("(1*x3^2)");
    groebnerBasis.push_back("(1*x0^1*x4^1)");
    groebnerBasis.push_back("(1*x2^1*x4^1) + (-249211079*x3^1)");
    groebnerBasis.push_back("(1*x3^1*x4^1)");
    groebnerBasis.push_back("(1*x4^2)");
    groebnerBasis.push_back("(1*x1^1) + (169143356*x3^1) + (-377176632*1)");

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
        cout << "Test random 64 bits pass" << endl;
        return 0;
    }
    else
    {
        cout << "Test random 64 bits failed" << endl;
        return -1;
    }
}


