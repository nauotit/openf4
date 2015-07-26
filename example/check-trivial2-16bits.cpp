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
 *  \file check-trivial2-16bits.cpp
 *  \example check-trivial2-16bits.cpp
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
    cout << "#               CHECK TRIVIAL2 16 BITS                  #" << endl;
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
    polynomialArray.emplace_back("32*x0*x3^2 - 7*x1*x2*x4 - 38*x3^2*x4 - 7*x0*x4^2 - 24*x0");
    polynomialArray.emplace_back("-2*x1*x3^2 + 35*x0*x1*x4 + 17*x2^2*x4 + 16*x2*x4^2 + 31*x1");
    polynomialArray.emplace_back("-9*x2^3 - 37*x0^2*x4 - 3*x0*x2*x4 - 2*x1*x2 - 4*x0*x4");
    polynomialArray.emplace_back("33*x0^2*x1 - 30*x2^3 + 6*x2^2*x3 - 38*x0^2*x4 + 21*x0*x4");
    polynomialArray.emplace_back("-2*x1^2*x2 - 13*x1*x2^2 + 34*x1^2*x3 + 38*x0*x2*x4 + 26*x4^2");
    polynomialArray.emplace_back("-39*x1^2*x2 - 39*x1^2*x3 - 21*x2^2*x3 - 5*x2^2*x4 - 22");
    polynomialArray.emplace_back("33*x0*x2*x4 - 35*x2^2*x4 + 16*x0*x2 - 14*x0*x3 + 36*x3");
    polynomialArray.emplace_back("34*x1*x2^2 + 36*x0*x3*x4 + 17*x1*x3*x4 + 11*x0*x4^2 + 17*x0*x1");
    polynomialArray.emplace_back("-39*x0^2*x3 + 29*x0*x2*x3 + 19*x0*x4^2 - 37*x1*x2 - 17*x3^2");
    polynomialArray.emplace_back("3*x0^2*x1 + x1^2*x2 - 27*x0*x1 + 15*x2*x3 - 8*x3*x4");
    
    // Compute a reduce groebner basis
    vector<string> basis= groebnerBasisF4(79, 5, variableName, polynomialArray, 1, 1);
    
    // Fill reference vectors
    vector<string> groebnerBasis;
    for(size_t i = 0; i < basis.size(); i++)
    {
        cout << "groebnerBasis.push_back(\"" << basis[i] << "\");" << endl;
    }
    groebnerBasis.push_back("(1*1)");

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
        cout << "Test trivial2 16 bits pass" << endl;
        return 0;
    }
    else
    {
        cout << "Test trivial2 16 bits failed" << endl;
        return -1;
    }
}


