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
 *  \file check-trivial2-32bits.cpp
 *  \example check-trivial2-32bits.cpp
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
    cout << "#               CHECK TRIVIAL2 32 BITS                  #" << endl;
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
    polynomialArray.emplace_back("-2329*x2*x3^2 - 2405*x1*x3*x4 - 2548*x1*x4 + 2649*x2*x4 + 4241*x0");
    polynomialArray.emplace_back("-2928*x0*x2*x3 - 1938*x2*x3^2 - 1059*x3^3 + 2153*x0*x1*x4 - 1905*x2");
    polynomialArray.emplace_back("2350*x1*x3^2 - 4547*x0*x1*x4 - 4045*x1*x2*x4 - 2927*x2*x3*x4 - 2091*x3^2*x4");
    polynomialArray.emplace_back("3037*x0^2*x3 + 1315*x0*x2*x4 + 2366*x2*x3*x4 + 4120*x2^2 + 483");
    polynomialArray.emplace_back("4017*x1^2*x2 + 921*x1*x4^2 + 3977*x3^2 - 3580*x0 + 1746*x1");
    polynomialArray.emplace_back("-3594*x1*x3*x4 - 3463*x2*x4^2 + 4572*x1^2 + 4556*x0*x2 - 1817*x1*x2");
    polynomialArray.emplace_back("-3129*x2^2*x3 - 3315*x2*x4^2 - 2948*x3*x4^2 - 1677*x1*x2 - 3723*x1*x4");
    polynomialArray.emplace_back("3698*x0^2*x3 + 904*x1*x2*x4 - 4005*x1*x3*x4 + 1424*x1*x4 + 2056*x0");
    
    // Compute a reduce groebner basis
    vector<string> basis= groebnerBasisF4(9199, 5, variableName, polynomialArray, 1, 0);
    
    // Fill reference vectors
    vector<string> groebnerBasis;
    groebnerBasis.push_back("(1*1)");

    /* 32 bits */
    bool test = true;
    size_t i = 0;
    while(i < basis.size() && test == true )
    {
        test = test && (groebnerBasis[i].compare(basis[i])==0);
        i++;
    }
    if(test==true)
    {
        cout << "Test trivial2 32 bits pass" << endl;
        return 0;
    }
    else
    {
        cout << "Test trivial2 32 bits failed" << endl;
        return -1;
    }
}


