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
 *  \file check-random-16bits.cpp
 *  \example check-random-16bits.cpp
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
    polynomialArray.emplace_back("-37*x1*x3^2 + 39*x0*x3*x4 + 3*x2*x3*x4 - 15*x0*x4^2 - 36*x3*x4^2");
    polynomialArray.emplace_back("-21*x0^2*x2 + 9*x0*x2^2 + 10*x1^2 - 11*x1*x3 + x2");
    polynomialArray.emplace_back("-13*x0*x1*x2 + 27*x0*x2^2 - 36*x0*x1*x3 - 19*x0*x1 - 2*x2^2");
    polynomialArray.emplace_back("x0^2*x1 + 11*x1^3 + 27*x0^2*x2 - 15*x0*x3*x4 + 28*x3*x4^2");
    polynomialArray.emplace_back("24*x1^2*x2 - 19*x0^2*x4 + 34*x1*x3*x4 + 19*x0*x4^2 - 21*x3*x4");
    polynomialArray.emplace_back("18*x0*x1*x2 - 25*x0*x2^2 - 5*x1*x2^2 - 5*x1^2*x3 - 12*x3^2");
    
    //cout << "I=ideal(" << endl;
    //for(size_t i = 0; i < polynomialArray.size()-1; i++)
    //{
        //cout << polynomialArray[i] << "," << endl;
    //}
    //cout << polynomialArray[polynomialArray.size()-1] << ")" << endl;
    
    // Compute a reduce groebner basis
    vector<string> basis= groebnerBasisF4(79, 5, variableName, polynomialArray, 1, 0);
    
    // Fill reference vectors
    vector<string> groebnerBasis;
    //for(size_t i = 0; i < basis.size(); i++)
    //{
        //cout << "groebnerBasis.push_back(\"" << basis[i] << "\");" << endl;
    //}
    groebnerBasis.push_back("(1*x1^1*x3^2)");
    groebnerBasis.push_back("(1*x3^1*x4^3) + (-38*x3^1*x4^2)");
    groebnerBasis.push_back("(1*x0^1*x3^2)");
    groebnerBasis.push_back("(1*x3^3)");
    groebnerBasis.push_back("(1*x0^2*x4^1) + (-33*x3^1*x4^2) + (30*x1^1*x2^1) + (2*x3^2) + (-28*x3^1*x4^1)");
    groebnerBasis.push_back("(1*x1^1*x2^1*x4^1) + (31*x3^1*x4^2)");
    groebnerBasis.push_back("(1*x0^1*x3^1*x4^1) + (35*x3^1*x4^2) + (-31*x1^1*x2^1) + (19*x3^2)");
    groebnerBasis.push_back("(1*x1^1*x3^1*x4^1)");
    groebnerBasis.push_back("(1*x3^2*x4^1)");
    groebnerBasis.push_back("(1*x0^1*x4^2) + (-33*x3^1*x4^2) + (30*x1^1*x2^1) + (2*x3^2)");
    groebnerBasis.push_back("(1*x0^1*x1^1)");
    groebnerBasis.push_back("(1*x1^2) + (-9*x1^1*x3^1) + (8*x2^1)");
    groebnerBasis.push_back("(1*x0^1*x2^1)");
    groebnerBasis.push_back("(1*x2^2)");
    groebnerBasis.push_back("(1*x2^1*x3^1) + (-24*x3^2)");
    
    //cout << "Outputf4=[" << endl;
    //for(size_t i = 0; i < basis.size()-1; i++)
    //{
        //cout << basis[i] << "," << endl;
    //}
    //cout << basis[basis.size()-1] << "]" << endl;

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
        cout << "Test random 16 bits pass" << endl;
        return 0;
    }
    else
    {
        cout << "Test random 16 bits failed" << endl;
        return -1;
    }
}


