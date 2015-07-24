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
 *  \file check-aes-gf2-extension-16bits.cpp
 *  \example check-aes-gf2-extension-16bits.cpp
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
    cout << "#                   CHECK AES 2^4 BITS                  #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Create polynomial array
    vector<string> polynomialArray;
    
    // Create variable name array
    vector<string> variableName;
    variableName.push_back("k100");
    variableName.push_back("k101");
    variableName.push_back("k102");
    variableName.push_back("k103");
    variableName.push_back("x100");
    variableName.push_back("x101");
    variableName.push_back("x102");
    variableName.push_back("x103");
    variableName.push_back("w100");
    variableName.push_back("w101");
    variableName.push_back("w102");
    variableName.push_back("w103");
    variableName.push_back("s000");
    variableName.push_back("s001");
    variableName.push_back("s002");
    variableName.push_back("s003");
    variableName.push_back("k000");
    variableName.push_back("k001");
    variableName.push_back("k002");
    variableName.push_back("k003");
    
    // Fill the polynomial array
    polynomialArray.emplace_back("w101 + k001 + (a^2 + a)");
    polynomialArray.emplace_back("w102 + k002 + (a^2 + a + 1)");
    polynomialArray.emplace_back("w103 + k003 + (a^2 + a)");
    polynomialArray.emplace_back("k000^2 + k001");
    polynomialArray.emplace_back("k001^2 + k002");
    polynomialArray.emplace_back("k002^2 + k003");
    polynomialArray.emplace_back("k003^2 + k000");
    polynomialArray.emplace_back("k100 + (a^2 + 1)*x100 + x101 + (a^3 + a^2)*x102 + (a^2 + 1)*x103 + (a^3 + a + 1)");
    polynomialArray.emplace_back("k101 + (a)*x100 + (a)*x101 + x102 + (a^3 + a^2 + a + 1)*x103 + (a^3 + 1)");
    polynomialArray.emplace_back("k102 + (a^3 + a)*x100 + (a^2)*x101 + (a^2)*x102 + x103 + (a^3 + a^2 + 1)");
    polynomialArray.emplace_back("k103 + x100 + (a^3)*x101 + (a + 1)*x102 + (a + 1)*x103 + (a^3 + a^2 + a)");
    polynomialArray.emplace_back("x100*w100 + 1");
    polynomialArray.emplace_back("x101*w101 + 1");
    polynomialArray.emplace_back("x102*w102 + 1");
    polynomialArray.emplace_back("x103*w103 + 1");
    polynomialArray.emplace_back("x100^2 + x101");
    polynomialArray.emplace_back("x101^2 + x102");
    polynomialArray.emplace_back("x102^2 + x103");
    polynomialArray.emplace_back("x103^2 + x100");
    polynomialArray.emplace_back("w100^2 + w101");
    polynomialArray.emplace_back("w101^2 + w102");
    polynomialArray.emplace_back("w102^2 + w103");
    polynomialArray.emplace_back("w103^2 + w100");
    polynomialArray.emplace_back("k100 + (a^2 + 1)*s000 + s001 + (a^3 + a^2)*s002 + (a^2 + 1)*s003 + (a^2 + a + 1)");
    polynomialArray.emplace_back("k101 + (a)*s000 + (a)*s001 + s002 + (a^3 + a^2 + a + 1)*s003 + (a^2 + a)");
    polynomialArray.emplace_back("k102 + (a^3 + a)*s000 + (a^2)*s001 + (a^2)*s002 + s003 + (a^2 + a + 1)");
    polynomialArray.emplace_back("k103 + s000 + (a^3)*s001 + (a + 1)*s002 + (a + 1)*s003 + (a^2 + a)");
    polynomialArray.emplace_back("k100^2 + k101");
    polynomialArray.emplace_back("k101^2 + k102");
    polynomialArray.emplace_back("k102^2 + k103");
    polynomialArray.emplace_back("k103^2 + k100");
    polynomialArray.emplace_back("s000^2 + s001");
    polynomialArray.emplace_back("s001^2 + s002");
    polynomialArray.emplace_back("s002^2 + s003");
    polynomialArray.emplace_back("s003^2 + s000");
    polynomialArray.emplace_back("s000*k000 + 1");
    polynomialArray.emplace_back("s001*k001 + 1");
    polynomialArray.emplace_back("s002*k002 + 1");
    polynomialArray.emplace_back("s003*k003 + 1");
    
    // Compute a reduce groebner basis
    vector<string> basis= groebnerBasisGF2ExtensionF4("a^4+a+1", 20, variableName, "a", polynomialArray, 1, 0);
    
    // Fill reference vectors
    vector<string> groebnerBasis;
    groebnerBasis.push_back("((+1)*w101^1) + ((+1)*k003^1) + ((a^2+a)*1)");
    groebnerBasis.push_back("((+1)*w102^1) + ((a^2+a)*k003^1)");
    groebnerBasis.push_back("((+1)*w103^1) + ((+1)*k003^1) + ((a^2+a)*1)");
    groebnerBasis.push_back("((+1)*k003^2) + ((a^2+a)*k003^1) + ((a^2+a+1)*1)");
    groebnerBasis.push_back("((+1)*k100^1) + ((+a)*k003^1) + ((a^3)*1)");
    groebnerBasis.push_back("((+1)*k101^1) + ((a^3+a+1)*k003^1) + ((+a+1)*1)");
    groebnerBasis.push_back("((+1)*k102^1) + ((+a+1)*k003^1) + ((a^3+a^2+a+1)*1)");
    groebnerBasis.push_back("((+1)*k103^1) + ((a^3+a^2+1)*k003^1) + ((+a)*1)");
    groebnerBasis.push_back("((+1)*x100^1) + ((+1)*k003^1) + ((a^2+a)*1)");
    groebnerBasis.push_back("((+1)*x101^1) + ((a^2+a)*k003^1)");
    groebnerBasis.push_back("((+1)*x102^1) + ((+1)*k003^1) + ((a^2+a)*1)");
    groebnerBasis.push_back("((+1)*x103^1) + ((a^2+a)*k003^1)");
    groebnerBasis.push_back("((+1)*w100^1) + ((a^2+a)*k003^1)");
    groebnerBasis.push_back("((+1)*s001^1) + ((a^2+a)*k003^1) + ((a^2+a+1)*1)");
    groebnerBasis.push_back("((+1)*s002^1) + ((+1)*k003^1)");
    groebnerBasis.push_back("((+1)*s003^1) + ((a^2+a)*k003^1) + ((a^2+a+1)*1)");
    groebnerBasis.push_back("((+1)*s000^1) + ((+1)*k003^1)");
    groebnerBasis.push_back("((+1)*k000^1) + ((a^2+a)*k003^1) + ((a^2+a+1)*1)");
    groebnerBasis.push_back("((+1)*k001^1) + ((+1)*k003^1)");
    groebnerBasis.push_back("((+1)*k002^1) + ((a^2+a)*k003^1) + ((a^2+a+1)*1)");

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
        cout << "Test aes GF(2^4) bits pass" << endl;
        return 0;
    }
    else
    {
        cout << "Test aes GF(2^4) bits failed" << endl;
        return -1;
    }
}


