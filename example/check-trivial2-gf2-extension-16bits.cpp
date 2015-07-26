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
 *  \file check-trivial2-gf2-extension-16bits.cpp
 *  \example check-trivial2-gf2-extension-16bits.cpp
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
    cout << "#         CHECK TRIVIAL2 GF2 EXTENSION 16 BITS          #" << endl;
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
    polynomialArray.emplace_back("(u^7 + u^5 + u^3 + 1)*x0*x1*x2 + (u^11 + u^8 + u^6 + u^5 + u^4 + u^2 + u)*x2^3 + (u^8 + u^6 + u^4 + u^3)*x0*x1*x3 + (u^12 + u^11 + u^10 + u^9 + u^8 + u^7 + u^2 + u + 1)*x0*x2*x4 + (u^7 + u^3)*x2");
    polynomialArray.emplace_back("(u^12 + u^11 + u^10 + u^8 + u^7 + u^2 + u + 1)*x2^2*x3 + (u^10 + u^9 + u^5 + u^4 + u^3 + u^2 + u)*x0*x3 + (u^11 + u^10 + u^7 + u^6 + u + 1)*x1 + (u^12 + u^11 + u^10 + u^9 + u^8 + u^7 + u^6 + u^5 + u^3)*x2 + (u^10 + u^9 + u^6 + u^5 + u^4 + u^2)*x3");
    polynomialArray.emplace_back("(u^11 + u^10 + u^9 + u^8 + u^6 + u^4)*x0*x2*x3 + (u^11 + u^3 + 1)*x0*x2*x4 + (u^12 + u^10 + u^8 + u^7 + u^4 + u)*x3^2*x4 + (u^12 + u^10 + u^7 + u^6 + u^5 + u^4)*x0*x4^2 + (u^9 + u^6 + u^5 + u^3 + u + 1)*x0*x4");
    polynomialArray.emplace_back("(u^10 + u^8 + u^7 + u^5 + u^3)*x2*x3^2 + (u^12 + u^11 + u^10 + u^9 + u^8 + u^5 + u^4 + u + 1)*x0^2*x4 + (u^11 + u^9 + u^7 + u^6 + u^5 + u^3 + u^2 + u + 1)*x0*x4^2 + (u^11 + u^9 + u^8 + u^5 + u^4 + u^3 + 1)*x3^2 + (u^11 + u^9 + u^8 + u^3 + u^2)*x2");
    polynomialArray.emplace_back("(u^12 + u^10 + u^6 + u^5 + u^4 + u^3 + 1)*x2^2*x3 + (u^10 + u^9 + u^7 + u^5 + u^4 + u^3 + u + 1)*x1*x2*x4 + (u^11 + u^10 + u^9 + u^6 + u^2 + u)*x1*x4^2 + (u^12 + u^11 + u^10 + u^6 + u^4 + u^2 + 1)*x3^2 + (u^11 + u^9 + u^7 + u^6 + u^4 + u^3 + u^2 + u + 1)*x3*x4");
    polynomialArray.emplace_back("(u^12 + u^9 + u^8 + u^6 + u^5 + u^2 + u + 1)*x0*x3^2 + (u^8 + u^7 + u^5 + u^3 + u + 1)*x0*x2*x4 + (u^12 + u^9 + u^8 + u^7 + u^4 + u^3 + u^2 + 1)*x1*x3 + (u^10 + u^9 + u^8 + u^6 + u^5 + u^4 + u^3 + 1)*x0*x4 + (u^11 + u^9 + u^6 + u^4 + u^2)*x1");
    polynomialArray.emplace_back("(u^12 + u^9 + u^7 + u^6 + u^5 + u^4 + u)*x2^2*x3 + (u^12 + u^9 + u^8 + u^6 + u^5 + u^4 + 1)*x0*x2*x4 + (u^8 + u^7 + u^5 + u^4)*x2*x3*x4 + (u^10 + u^9 + u^8 + u^6 + u^5 + u^3 + u^2 + u + 1)*x3^2 + (u^5 + u^4 + u^3 + u + 1)*x4^2");
    polynomialArray.emplace_back("(u^12 + u^9 + u^6 + u^4 + u^3 + u + 1)*x0^2*x3 + (u^12 + u^11 + u^9 + u^3 + u^2 + u + 1)*x0*x1*x3 + (u^11 + u^10 + u^9 + u^3)*x3^3 + (u^11 + u^10 + u^8 + u^7 + u^6 + u^4 + u^3 + u + 1)*x0*x3*x4 + (u^10 + u^9 + u^6 + u^5 + u^4 + u^3 + 1)*x4^3");
    polynomialArray.emplace_back("(u^7 + u^6 + u^5 + u^4 + u^2 + 1)*x0*x2^2 + (u^12 + u^7 + u^5 + u^2)*x0*x2*x4 + (u^11 + u^7 + u^5 + u^4 + 1)*x0*x4^2 + (u^12 + u^8 + u^7 + u^5 + u^4 + u)*x1*x4^2 + (u^12 + u^7 + u^6 + u^4 + u^2 + u + 1)*x2*x4^2");
    polynomialArray.emplace_back("(u^9 + u^7 + u^3 + u^2)*x0*x3^2 + (u^12 + u^10 + u^6 + u^5 + u^4 + u^3)*x3^2*x4 + (u^12 + u^8 + u^7 + u^4 + u^3 + u + 1)*x0^2 + (u^12 + u^10 + u^9 + u^8 + u^7 + u^6 + u^3 + u + 1)*x2 + (u^10 + u^8 + u^6 + u^4 + u + 1)*x3");
    polynomialArray.emplace_back("(u^12 + u^11 + u^10 + u^9 + u^5 + u^4 + u^3 + u^2 + u)*x2*x3^2 + (u^12 + u^10 + u^9 + u^8 + u^7 + u^6 + u^4 + u)*x0*x2*x4 + (u^9 + u^8 + u^7 + u^4 + u^2 + u + 1)*x2*x4^2 + (u^12 + u^11 + u^9 + u^8 + u^7 + u^4 + u^2 + u)*x3*x4^2 + (u^10 + u^9 + u^7 + u^5 + u^4 + u^3 + u + 1)*x0*x4");
    polynomialArray.emplace_back("(u^11 + u^10 + u^9 + u^8 + u^6 + u^4 + u^3 + u^2)*x0^2*x1 + (u^11 + u^10 + u^5 + u^4 + u^3 + u^2)*x0^2*x2 + (u^12 + u^9 + u^8 + u^5 + u^4 + u^2 + u)*x1*x3^2 + (u^9 + u^7 + u^6 + u^4 + u^3 + u^2 + u + 1)*x3^3 + (u^10 + u^9 + u^7 + u^6 + u^5 + u^3 + u)*x0*x4^2");
    polynomialArray.emplace_back("(u^11 + u^10 + u^9 + u^7 + u^6 + u^4 + u)*x0*x1*x2 + (u^11 + u^10 + u^9 + u^8 + u^7 + u^4 + u^3 + u + 1)*x3^2*x4 + (u^9 + u^4 + u^2)*x2*x4^2 + (u^12 + u^9 + u^7 + u^4 + u^3 + u^2)*x1^2 + (u^12 + u^11 + u^10 + u^9 + u^7 + u^6 + u^5 + u^3 + u^2)*x2^2");
    polynomialArray.emplace_back("(u^10 + u^8 + u^6 + u^3 + u^2 + u + 1)*x1*x2^2 + (u^12 + u^11 + u^9 + u^8 + u^7 + u^3 + u)*x0*x2*x3 + (u^10 + u^8 + u^7 + u^4 + 1)*x2*x3*x4 + (u^12 + u^10 + u^9 + u^8 + u^5 + u^4 + u^3 + 1)*x0*x2 + (u^12 + u^11 + u^10 + u^8 + u^5 + u^4 + u^3 + 1)*x3^2");
    polynomialArray.emplace_back("(u^11 + u^10 + u^8 + u^7 + u^5 + u^4 + u^3 + u^2 + 1)*x0*x2*x3 + (u^11 + u^10 + u^9 + u^8 + u^7 + u^6 + u^3)*x0*x2*x4 + (u^12 + u^11 + u^9 + u^8 + u^7 + u^5 + u^4 + u^3)*x0^2 + (u^12 + u^10 + u^8 + u^7 + u^5 + u^3 + 1)*x2^2 + (u^11 + u^9 + u^8 + u^5 + u^3 + u^2 + u + 1)*x0*x3");
    polynomialArray.emplace_back("(u^10 + u^8 + u^5 + u^4 + u + 1)*x0*x2*x3 + (u^12 + u^7 + u^2 + u)*x3^2*x4 + (u^12 + u^7 + u^3 + u + 1)*x3^2 + (u^12 + u^10 + u^9 + u^6 + u^5 + u^3 + u^2)*x1 + (u^12 + u^9 + u^6 + u^5 + u^4 + u^3 + u^2)*x2");
    polynomialArray.emplace_back("(u^12 + u^8 + u^7 + u^6 + u^2 + 1)*x2^3 + (u^12 + u^4 + u^3 + u^2 + u + 1)*x0*x1*x3 + (u^10 + u^8 + u^3)*x1*x2*x4 + (u^8 + u^7 + u^4 + u^3 + u)*x2^2*x4 + (u^12 + u^10 + u^9 + u^8 + u^7 + u^5 + u^3 + 1)*x0*x1");
    polynomialArray.emplace_back("(u^10 + u^9 + u^8 + u^7 + u^5 + u^4 + u^2 + u)*x3^3 + (u^12 + u^10 + u^6 + u^5 + u^2 + u + 1)*x2*x4^2 + (u^11 + u^10 + u^8 + u^6 + u^3 + u)*x0^2 + (u^10 + u^9 + u^7 + u^3 + u + 1)*x4^2 + (u^12 + u^11 + u^9 + u^8 + u^7 + u^2)*x0");
    polynomialArray.emplace_back("(u^12 + u^11 + u^10 + u^7 + u^6 + u^4 + u^3 + u^2)*x2^3 + (u^12 + u^11 + u^8 + u^7 + u^3 + u)*x1^2*x3 + (u^11 + u^6 + u^2 + u + 1)*x1*x3^2 + (u^9 + u^6 + u^4 + 1)*x0*x2*x4 + (u^9 + u^8 + u^5 + u^3)*x2^2*x4");
    polynomialArray.emplace_back("(u^9 + u^7 + u^6 + u^4 + u^3)*x1^2*x2 + (u^11 + u^10 + u^9 + u^8 + u^7 + u^5 + u^2 + u)*x2^2*x3 + (u^12 + u^9 + u^4 + u + 1)*x2*x3^2 + (u^12 + u^10 + u^9 + u^7 + u^6 + u^3 + u^2 + u)*x0^2*x4 + (u^12 + u^11 + u^9 + u^7 + u^5 + u^4 + u^3)*x3");
    polynomialArray.emplace_back("(u^10 + u^9 + u^8 + u^5 + u^3 + u)*x0^2*x3 + (u^12 + u^11 + u^6 + u^4 + u^3 + u)*x0*x2*x3 + (u^12 + u^11 + u^10 + u^8 + u^4 + u^3 + 1)*x0*x2 + (u^11 + u^6 + u^5 + u^3 + u^2)*x2*x3 + (u^11 + u^10 + u^7 + u^5 + u^4 + u^3)*x0");
    polynomialArray.emplace_back("(u^12 + u^11 + u^10 + u^9 + u^8 + u^7 + u^5 + u^3 + u + 1)*x0^2*x3 + (u^12 + u^11 + u^9 + u^8 + u^6 + u^3 + u + 1)*x2*x3*x4 + (u^12 + u^11 + u^9 + u^8 + u^7 + u^4 + u^3 + u^2)*x3*x4^2 + (u^10 + u^9 + u^7 + u^6 + u^5 + u^3 + u^2)*x1*x2 + (u^10 + u^6 + u^2)*x2");
    polynomialArray.emplace_back("(u^12 + u^11 + u^6 + u^4 + 1)*x0*x1^2 + (u^12 + u^9 + u^8 + u^6 + u^2 + u + 1)*x0^2*x2 + (u^12 + u^9 + u^7 + u^5 + u^4 + u^3 + u^2 + u + 1)*x1^2*x3 + (u^10 + u^8 + u^7 + u^6 + u^4 + 1)*x2*x4 + (u^11 + u^10 + u^7 + u^5 + u^2 + u)*x0");
    polynomialArray.emplace_back("(u^10 + u^9 + u^7 + u^5 + 1)*x0^2*x3 + (u^10 + u^9 + u^8 + u^7 + u^6 + u^5 + u^4 + u^2 + u)*x1^2*x3 + (u^11 + u^10 + u^9 + u^7 + u^6 + u^5 + u^2 + u + 1)*x0*x3^2 + (u^12 + u^11 + u^10 + u^9 + u^7 + u^6 + u^5 + u^3 + u^2 + 1)*x0^2*x4 + (u^12 + u^10 + u^8 + u^7 + u^6)*x2*x4");
    polynomialArray.emplace_back("(u^12 + u^11 + u^8 + u^7 + u^5 + u^2)*x0^2*x1 + (u^11 + u^10 + u^8 + u^6 + u^3 + u^2 + u + 1)*x0*x1*x4 + (u^12 + u^11 + u^8 + u^6 + u^5 + u^3 + 1)*x0*x1 + (u^12 + u^7 + u^6 + u^4 + u^3 + u^2 + 1)*x4^2 + (u^12 + u^11 + u^10 + u^9 + u^8 + u + 1)*x4");
    polynomialArray.emplace_back("(u^12 + u^11 + u^8 + u^6 + u^5 + u^4 + 1)*x0*x2^2 + (u^12 + u^11 + u^10 + u^8 + u^7 + u^6 + u^4 + 1)*x2*x3^2 + (u^12 + u^10 + u^9 + u^7 + u^5 + u^4 + u^3 + 1)*x3^2*x4 + (u^7 + u^5 + u^3 + u)*x2*x3 + (u^12 + u^11 + u^10 + u^8 + u^7 + u^5 + u^4 + u^3 + u + 1)*x3*x4");
    polynomialArray.emplace_back("(u^12 + u^11 + u^8 + u^6 + 1)*x0*x3^2 + (u^12 + u^11 + u^10 + u^8 + u^6 + u^5 + u^4 + u^3 + u + 1)*x1^2 + (u^12 + u^11 + u^10 + u^9 + u^8 + u^5 + u)*x4^2 + (u^12 + u^10 + u^9 + u^7 + u^4 + u^2)*x1 + (u^8 + u^5 + u^3 + u^2 + u)");
    polynomialArray.emplace_back("(u^11 + u^10 + u^7 + u^6 + 1)*x1^2*x3 + (u^12 + u^8 + u^7 + u^3 + u)*x1*x2*x3 + (u^12 + u^9 + u^8 + u^6 + u^5 + u^3 + u^2 + u)*x1*x3*x4 + (u^12 + u^10 + u^6 + u^5 + u^2 + u + 1)*x0 + (u^12 + u^11 + u^10 + u^9 + u^8 + u^5 + u^3 + u)*x2");
    polynomialArray.emplace_back("(u^10 + u^9 + u^7 + u^5 + u^2)*x2^3 + (u^8 + u^6 + u^5 + u^3)*x0*x1*x3 + (u^11 + u^10 + u^8 + u^7 + u^3 + 1)*x0*x2*x4 + (u^11 + u^10 + u^9 + u^8 + u^7 + u^6 + u^4 + u + 1)*x1*x2*x4 + (u^12 + u^3 + u^2)*x2*x4");
    polynomialArray.emplace_back("(u^11 + u^9 + u^7 + u^5 + u^3 + u^2)*x0^2*x2 + (u^11 + u^10 + u^8 + u^6 + u^5)*x2*x3^2 + (u^12 + u^9 + u^8 + u^7 + u^5 + u^4 + u^3)*x0*x4^2 + (u^9 + u^5 + u^4 + u^3 + u + 1)*x0*x2 + (u^11 + u^7 + u^5 + u^4 + u^3 + u^2 + u + 1)*x0");
    polynomialArray.emplace_back("(u^12 + u^11 + u^10 + u^8 + u^7 + u^6 + u^5 + u^2 + u)*x0^2*x4 + (u^12 + u^10 + u^9 + u^5 + u^3 + u^2 + u + 1)*x0*x2*x4 + (u^11 + u^10 + u^8 + u^5 + u^4 + u^3)*x1*x3 + (u^8 + u^6 + u^5 + u^4 + u^2 + u)*x1*x4 + (u^12 + u^10 + u^9 + u^8 + u^3 + 1)*x3");
    polynomialArray.emplace_back("(u^11 + u^9 + u^6 + u^4 + u^3)*x0*x2^2 + (u^11 + u^10 + u^6 + u^5 + u^3 + 1)*x0*x1 + (u^12 + u^11 + u^10 + u^9 + u^8 + u^6 + u^5 + u^2)*x1*x2 + (u^12 + u^10 + u^9 + u^7)*x3*x4 + (u^10 + u^9 + u^7 + u^6 + u^5 + u^4 + u^3 + u)*x2");
    polynomialArray.emplace_back("(u^3 + u^2)*x1*x2*x3 + (u^12 + u^6 + u^5)*x1^2*x4 + (u^11 + u^8 + u^6 + u^4)*x0*x2*x4 + (u^11 + u^10 + u^9 + u^8 + u^5 + u^3 + 1)*x0*x4^2 + (u^11 + u^10 + u^8 + u^7 + u^6 + u^5 + u^2 + 1)*x1*x4");
    polynomialArray.emplace_back("(u^12 + u^11 + u^10 + u^4 + u^3 + u)*x1^3 + (u^12 + u^9 + u^7 + u^6 + u^5 + u^4)*x0*x2*x3 + (u^12 + u^10 + u^8 + u^7 + u^5 + u)*x1*x3*x4 + (u^9 + u^8 + u^4 + u^3 + u^2 + 1)*x0*x3 + (u^8 + u^6 + u)*x3*x4");
    polynomialArray.emplace_back("(u^11 + u^10 + u^9 + u^8 + u^6 + u^5 + u^4 + u^2 + u)*x0*x1^2 + (u^12 + u^9 + u^8 + u^7 + u^6 + u^4 + u^3 + u^2 + 1)*x0^2*x2 + (u^12 + u^10 + u^8 + u^6 + u^4 + u^3)*x0*x1*x2 + (u^12 + u^11 + u^10 + u^8 + u^7 + u^4 + 1)*x1*x2^2 + (u^12 + u^11 + u^9 + u^5 + u^3 + 1)*x0*x2*x3");
    polynomialArray.emplace_back("(u^7 + u^5 + u^3 + 1)*x0^2*x2 + (u^12 + u^11 + u^10 + u^8 + u^7 + u^6 + u^5 + u^4 + u^3 + u^2 + u + 1)*x2*x3*x4 + (u^8 + u^6 + u^5 + u^4 + u^3 + u^2 + u)*x3^2*x4 + (u^11 + u^10 + u^8 + u^6 + u^5 + u^3 + 1)*x0*x2 + (u^12 + u^11 + u^10 + u^9 + u^6 + u^5 + u^3 + u^2 + 1)*x0*x4");
    polynomialArray.emplace_back("(u^9 + u^6 + u^2 + 1)*x0*x2^2 + (u^9 + u^8 + u^7 + u^6 + u^4 + u^3 + u^2 + 1)*x1*x2^2 + (u^12 + u^11 + u^10 + u^9 + u^8 + u^7 + u^4 + u^3 + u)*x0^2*x4 + (u^12 + u^10 + u^9 + u^8 + u^5 + u^3 + u)*x3^2*x4 + (u^11 + u^10 + u^9 + u^6 + u^3 + 1)*x1*x4^2");
    polynomialArray.emplace_back("(u^12 + u^10 + u^8 + u^7 + u^5 + u)*x0*x3^2 + (u^12 + u^11 + u^10 + u^5 + u^4 + u^2)*x3^3 + (u^12 + u^8 + u^7 + u^5 + u^4 + u^3 + u + 1)*x2*x4 + (u^12 + u^10 + u^9 + u^8 + u^7 + u^6 + u^2 + u)*x3 + (u^12 + u^11 + u^8 + u^6 + u^5 + u^4 + u^2 + u)");
    polynomialArray.emplace_back("(u^12 + u^11 + u^8 + u^6 + u^4 + u^2 + u)*x1^3 + (u^12 + u^10 + u^8 + u + 1)*x0*x4^2 + (u^12 + u^11 + u^10 + u^9 + u^8 + u^6 + u^4 + u^3 + u)*x1*x2 + (u^12 + u^10 + u^8 + 1)*x1*x4 + (u^9 + u^8 + u^7 + u^6 + u^5 + u^2 + u + 1)*x2*x4");
    polynomialArray.emplace_back("(u^12 + u^8 + u^7 + u^5 + u^2 + u + 1)*x0*x1*x2 + (u^9 + u^5 + u^4 + u^2 + u)*x0*x3*x4 + (u^12 + u^11 + u^10 + u^9 + u^8 + u^6 + u^3 + 1)*x0^2 + (u^11 + u^9 + u^8 + u^6 + u^5 + u^4 + u^2 + u + 1)*x0 + (u^10 + u^9 + u^8 + u^7 + u^6 + u^2 + u + 1)*x2");
    polynomialArray.emplace_back("(u^11 + u^10 + u^8 + u)*x0*x1^2 + (u^10 + u^8 + u^7 + u^6 + u^5 + u^4 + u^2 + u)*x1^2*x2 + (u^11 + u^10 + u^9 + u^6 + u^3 + u^2 + u)*x0^2*x3 + (u^11 + u^9 + u^8 + u^5 + u^2 + u + 1)*x3^3 + (u^11 + u^9 + u^5 + u^3 + u^2 + u)*x0*x2*x4");
    polynomialArray.emplace_back("(u^12 + u^10 + u^8 + u^7 + u^6 + u^4 + u^3 + 1)*x1^2*x2 + (u^12 + u^10 + u^6 + u^4 + u^2 + u)*x1*x2*x4 + (u^10 + u^9 + u^7 + u^6 + u^5 + u^3 + u^2)*x2*x3*x4 + (u^12 + u^11 + u^9 + u^7 + u^6 + u^4 + u^3 + u^2 + 1)*x3*x4^2 + (u^11 + u^10 + u^8 + u^7 + u^6 + u^5 + u^4 + u^2)*x4^3");
    polynomialArray.emplace_back("(u^12 + u^11 + u^10 + u^9 + u^7 + u^6 + u^3 + 1)*x0^2*x1 + (u^11 + u^3 + u^2 + u + 1)*x0^2*x3 + (u^12 + u^9 + u^6 + u^5 + u^4 + u^3 + u)*x0*x2*x3 + (u^12 + u^11 + u^10 + u^7 + u^6 + u^4 + u^3 + u)*x2^2*x4 + (u^12 + u^10 + u^7 + u^5 + u^3)*x0*x4");
    polynomialArray.emplace_back("(u^12 + u^11 + u^9 + u^7 + u^4 + u^3 + u^2)*x0^2*x4 + (u^12 + u^10 + u^9 + u^7 + u^5 + u^3 + u^2)*x1^2 + (u^12 + u^11 + u^9 + u^8 + u^7 + u^6 + u^4 + u^3 + 1)*x3^2 + (u^10 + u^3 + u^2 + 1)*x0*x4 + (u^11 + u^9 + u^7 + u^5 + u^4 + u^3 + u^2 + u)*x2");
    polynomialArray.emplace_back("(u^12 + u^11 + u^10 + u^9 + u^6 + u^5 + u^3 + u^2 + u)*x0^2*x3 + (u^12 + u^11 + u^9 + u^5 + u^3 + u^2)*x1^2*x4 + (u^12 + u^9 + u^7 + u^6 + u^5 + u^4 + u^3 + 1)*x2*x4^2 + (u^12 + u^11 + u^9 + u^8 + u^7 + u^4 + 1)*x3*x4^2 + (u^9 + u^7 + u^5 + u^4 + u^3)*x1");
    polynomialArray.emplace_back("(u^12 + u^9 + u^8 + u^7 + u^5 + u^4 + u)*x2*x3^2 + (u^12 + u^10 + u^8 + u^7 + u^6 + u^4)*x0*x1*x4 + (u^10 + u^8 + u^7 + u^6 + u^5 + u^4 + u^2)*x4^3 + (u^10 + u^9 + u^8 + u^7 + u^4 + u^2 + u + 1)*x0^2 + (u^12 + u^11 + u^10 + u^7 + u^5 + u)*x1");
    polynomialArray.emplace_back("(u^12 + u^11 + u^8 + u^7 + u^6)*x1*x2*x3 + (u^12 + u^11 + u^10 + u^9 + u^6 + u^5 + u^3 + u + 1)*x1^2*x4 + (u^12 + u^10 + u^7 + u^6 + u^3 + u)*x2*x3*x4 + (u^10 + u^8 + u^5 + u^4 + u^3 + u^2 + u)*x4^3 + (u^11 + u^10 + u^7 + u^5 + u^2 + 1)*x3");
    polynomialArray.emplace_back("(u^12 + u^10 + u^8 + u^5 + u^4 + u^2 + 1)*x0^2*x2 + (u^11 + u^8 + u^7 + u^6 + u^2 + u)*x1^2*x4 + (u^12 + u^11 + u^10 + u^7 + u^6 + u^4 + u^3 + u^2 + 1)*x3^2*x4 + (u^11 + u^10 + u^7 + u^6 + u)*x2*x4 + (u^12 + u^10 + u^8 + u^7 + u^4)*x3*x4");
    polynomialArray.emplace_back("(u^12 + u^10 + u^7 + u^6 + u^5 + u^3 + u^2 + 1)*x3^3 + (u^12 + u^11 + u^6 + u^5 + u^3 + u^2 + 1)*x0*x4^2 + (u^12 + u^11 + u^10 + u^8 + u^3 + u)*x0*x3 + (u^10 + u^9 + u^7 + u^4 + u^2 + u)*x3*x4 + (u^9 + u^7 + u^6 + u^5 + u^3)*x4");
    polynomialArray.emplace_back("(u^12 + u^9 + u^8 + u^6 + u^4 + u^3 + 1)*x1^2*x2 + (u^9 + u^6 + u^3 + 1)*x3*x4^2 + (u^11 + u^9 + u^8 + u^6 + u^5)*x3^2 + (u^12 + u^7 + u^6 + u^4 + u^3 + 1)*x3*x4 + (u^12 + u^5 + u^4 + u + 1)*x4");
    polynomialArray.emplace_back("(u^11 + u^10 + u^9 + u^8 + u^3 + u)*x0*x1^2 + (u^11 + u^9 + u^7 + u^6 + u^5 + u^4 + u^2 + 1)*x1*x2^2 + (u^10 + u^9)*x0^2*x3 + (u^12 + u^4 + u^3 + 1)*x3 + (u^10 + u^8 + u^7 + u^2 + u + 1)*x4");
    polynomialArray.emplace_back("(u^12 + u^11 + u^10 + u^8 + u^7 + u + 1)*x0^2*x3 + (u^9 + u^7 + u^6 + u^3 + u^2 + u + 1)*x1*x2*x3 + (u^11 + u^8 + u^6 + u^4 + u^3 + 1)*x0*x1*x4 + (u^12 + u^11 + u^9 + u^5 + u^4 + u^2 + u)*x0*x3 + (u^12 + u^11 + u^9 + u^7 + u^6 + u^2 + u)*x0*x4");
    polynomialArray.emplace_back("(u^10 + u^6 + u^5 + u^4 + u^3)*x0*x2^2 + (u^8 + u^5 + u + 1)*x0^2*x4 + (u^12 + u^8 + u^6 + u^5 + u^4 + u^3 + u^2 + 1)*x1^2*x4 + (u^12 + u^11 + u^10 + u^9 + u^8 + u^7 + u^6 + u^5 + u^3 + u)*x2*x4^2 + (u^12 + u^11 + u^10 + u^8 + u^5)*x1*x3");
    polynomialArray.emplace_back("(u^12 + u^8 + u^6 + u^4 + u^3 + u^2 + u)*x0*x1^2 + (u^11 + u^10 + u^9 + u^8 + u^7 + u^5 + u^4 + u^3 + u + 1)*x1^3 + (u^12 + u^10 + u^9 + u^7 + u^6 + u^2 + u)*x1*x4^2 + (u^12 + u^10 + u^8 + u^6 + u^4 + u + 1)*x3*x4^2 + (u^11 + u^10 + u^8 + u^7 + u^6 + u^5 + u^4 + u^3 + u)*x1");
    polynomialArray.emplace_back("(u^12 + u^10 + u^9 + u^7 + u^5 + u^3 + 1)*x1^3 + (u^11 + u^10 + u^9 + u^8 + u^6 + u^5 + u + 1)*x4^3 + (u^10 + u^8 + u^7 + u^6 + 1)*x0^2 + (u^11 + u^10 + u^9 + u^7 + u^6 + u^3 + u^2 + 1)*x1*x4 + (u^12 + u^11 + u^10 + u^9 + u^8 + u^7 + u^6 + u^4)*x2");
    polynomialArray.emplace_back("(u^11 + u^10 + u^5 + u^4 + u^2 + u)*x1^3 + (u^12 + u^11 + u^10 + u^9 + u^5 + u^4 + u)*x0^2*x2 + (u^12 + u^8 + u^6 + u^4 + u^2 + 1)*x1*x2^2 + (u^12 + u^11 + u^7 + u^6 + u^5 + u^4 + u^3 + u)*x2^2*x3 + (u^11 + u^9 + u^7 + u^6 + u^5 + u^4 + u^2 + u)*x2*x3");
    polynomialArray.emplace_back("(u^11 + u^5 + u^2)*x0*x2*x3 + (u^10 + u^9 + u^5 + u^4 + u^3 + 1)*x3^3 + (u^12 + u^6 + u^5 + 1)*x0^2*x4 + (u^9 + u^6 + u^4 + u + 1)*x0*x3 + (u^6 + u^3 + u + 1)*x3");
    polynomialArray.emplace_back("(u^10 + u^9 + u^8 + u^5 + u^4 + u^2 + 1)*x1^2*x3 + (u^12 + u^10 + u^8 + u^7 + u^5 + u^4 + u^2 + u + 1)*x3^2*x4 + (u^10 + u^9 + u^4 + u^3 + u^2)*x2*x4^2 + (u^12 + u^9 + u^8 + u^6 + u^5 + u + 1)*x3*x4^2 + (u^12 + u^10 + u^6 + u^4 + u^3 + u^2 + u)*x0*x3");
    polynomialArray.emplace_back("(u^12 + u^6 + u^4 + u^3 + u^2)*x0^2*x3 + (u^10 + u^9 + u^8 + u^7 + u^5 + u^4 + u^2)*x1^2*x3 + (u^12 + u^8 + u^7 + u^6 + u^5 + u^4 + u^3 + u + 1)*x1*x2*x4 + (u^11 + u^8 + u^7 + u^5 + u^2 + 1)*x1*x3 + (u^12 + u^11 + u^7 + u^6 + u^4 + u^2 + u)*x4");
    polynomialArray.emplace_back("(u^11 + u^10 + u^9 + u^7 + u^4 + u^3 + u^2)*x1^3 + (u^12 + u^10 + u^7 + u^5 + u^3)*x0*x2^2 + (u^12 + u^11 + u^10 + u^7 + u^5 + u^2)*x0*x1*x3 + (u^12 + u^9 + u^8 + u^7 + u^6 + u^4 + u^3 + u)*x2 + (u^12 + u^11 + u^10 + u^9 + u^6 + u^5 + u^2 + 1)");
    
    // Compute a reduce groebner basis
    vector<string> basis= groebnerBasisGF2ExtensionF4("u^13 + u^12 + u^10 + u^7 + u^4 + u^3 + 1", 5, variableName, "u", polynomialArray, 1, 0);
    
    // Fill reference vectors
    vector<string> groebnerBasis;
    groebnerBasis.push_back("((+1)*1)");

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
        cout << "Test trivial2 gf2 extension 16 bits pass" << endl;
        return 0;
    }
    else
    {
        cout << "Test trivial2 gf2 extension 16 bits failed" << endl;
        return -1;
    }
}


