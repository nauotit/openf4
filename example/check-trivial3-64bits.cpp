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
 *  \file check-trivial3-64bits.cpp
 *  \example check-trivial3-64bits.cpp
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
    cout << "#              CHECK TRIVIAL 3 64 BITS                  #" << endl;
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
    polynomialArray.emplace_back("-7253051*x1^2 + 52764828*x1*x2 - 1593629*x2^2 - 30491382*x1*x4 - 15421743");
    polynomialArray.emplace_back("2778386*x1^2 + 46128944*x2^2 - 28328699*x2*x3 + 35619408*x1*x4 - 47336793*x4^2");
    polynomialArray.emplace_back("50713151*x1^2 + 33804903*x1*x3 + 4639379*x3*x4 - 29371044*x1 - 55622885*x4");
    polynomialArray.emplace_back("-17812925*x1*x2 - 60567702*x3^2 - 17218643*x2*x4 + 15189711*x1 + 683651*x4");
    polynomialArray.emplace_back("42755489*x1*x3 - 60418193*x2*x4 + 56537689*x4^2 - 6152933*x3 + 53988116");
    
    // Compute a reduce groebner basis
    vector<string> basis= groebnerBasisF4(143107493, 5, variableName, polynomialArray, 1, 0);
    
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
        cout << "Test trivial3 64 bits pass" << endl;
        return 0;
    }
    else
    {
        cout << "Test trivial3 64 bits failed" << endl;
        return -1;
    }
}


