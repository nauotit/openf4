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
 *  \file check-cyclic6-gf2-extension-16bits.cpp
 *  \example check-cyclic6-gf2-extension-16bits.cpp
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
    cout << "#           CHECK CYCLIC6 16 BITS ON GF(2^n)            #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Create polynomial array
    vector<string> polynomialArray;
    
    // Create variable name array
    vector<string> variableName;
    for(int i = 0; i < 6; i++)
    {
        variableName.push_back('x'+to_string(i));
    }
    
    // Fill the polynomial array    
    polynomialArray.emplace_back("(t+t^3)*x0+(t+t^3)*x1+(t+t^3)*x2+(t+t^3)*x3+(t+t^3)*x4+(t+t^3)*x5");
    polynomialArray.emplace_back("(t+t^3)*x0*x1+(t+t^3)*x1*x2+(t+t^3)*x2*x3+(t+t^3)*x3*x4+(t+t^3)*x0*x5+(t+t^3)*x4*x5");
    polynomialArray.emplace_back("(t+t^3)*x0*x1*x2+(t+t^3)*x1*x2*x3+(t+t^3)*x2*x3*x4+(t+t^3)*x0*x1*x5+(t+t^3)*x0*x4*x5+(t+t^3)*x3*x4*x5");
    polynomialArray.emplace_back("(t+t^3)*x0*x1*x2*x3+(t+t^3)*x1*x2*x3*x4+(t+t^3)*x0*x1*x2*x5+(t+t^3)*x0*x1*x4*x5+(t+t^3)*x0*x3*x4*x5+(t+t^3)*x2*x3*x4*x5");
    polynomialArray.emplace_back("(t+t^3)*x0*x1*x2*x3*x4+(t+t^3)*x0*x1*x2*x3*x5+(t+t^3)*x0*x1*x2*x4*x5+(t+t^3)*x0*x1*x3*x4*x5+(t+t^3)*x0*x2*x3*x4*x5+(t+t^3)*x1*x2*x3*x4*x5");
    polynomialArray.emplace_back("(t+t^3)*x0*x1*x2*x3*x4*x5-1");
    
    // Compute a reduce groebner basis
    vector<string> basisShort = groebnerBasisGF2ExtensionF4("t^15 + t^13 + t^8 + t^5 + t^2 + t + 1", 6, variableName, "t", polynomialArray, 1, 0);
    
    // Fill reference vectors
    vector<string> groebnerBasisCyclic6Short;
    
    //for(size_t i = 0; i < basisShort.size(); i++)
    //{
        //cout << "groebnerBasisCyclic6Short.push_back(\"" << basisShort[i] << "\");" << endl;
    //}
    
    groebnerBasisCyclic6Short.push_back("((+1)*x0^1) + ((+1)*x1^1) + ((+1)*x2^1) + ((+1)*x3^1) + ((+1)*x4^1) + ((+1)*x5^1)");
    groebnerBasisCyclic6Short.push_back("((+1)*x1^2) + ((+1)*x1^1*x3^1) + ((+1)*x2^1*x3^1) + ((+1)*x1^1*x4^1) + ((+1)*x3^1*x4^1) + ((+1)*x2^1*x5^1) + ((+1)*x3^1*x5^1) + ((+1)*x5^2)");
    groebnerBasisCyclic6Short.push_back("((+1)*x2^1*x3^3*x5^4) + ((+1)*x2^1*x3^2*x5^5) + ((+1)*x3^3*x5^5) + ((+1)*x3^2*x5^6) + ((t^12+t^5+t^3+t^2+t+1)*x2^1*x3^1) + ((t^12+t^5+t^3+t^2+t+1)*x2^1*x5^1) + ((t^12+t^5+t^3+t^2+t+1)*x3^1*x5^1) + ((t^12+t^5+t^3+t^2+t+1)*x5^2)");
    groebnerBasisCyclic6Short.push_back("((+1)*x1^1*x2^1) + ((+1)*x2^2) + ((+1)*x1^1*x3^1) + ((+1)*x2^1*x3^1) + ((+1)*x1^1*x4^1) + ((+1)*x2^1*x4^1) + ((+1)*x3^1*x4^1) + ((+1)*x4^2) + ((+1)*x1^1*x5^1) + ((+1)*x2^1*x5^1) + ((+1)*x3^1*x5^1) + ((+1)*x4^1*x5^1)");
    groebnerBasisCyclic6Short.push_back("((+1)*x2^3) + ((+1)*x2^2*x5^1) + ((+1)*x2^1*x5^2) + ((+1)*x5^3)");
    groebnerBasisCyclic6Short.push_back("((+1)*x2^2*x3^1) + ((+1)*x2^1*x3^1*x4^1) + ((+1)*x2^2*x5^1) + ((+1)*x2^1*x3^1*x5^1) + ((+1)*x2^1*x4^1*x5^1) + ((+1)*x3^1*x4^1*x5^1) + ((+1)*x2^1*x5^2) + ((+1)*x4^1*x5^2)");
    groebnerBasisCyclic6Short.push_back("((+1)*x1^1*x3^3) + ((+1)*x2^1*x3^3) + ((+1)*x3^3*x4^1) + ((+1)*x1^1*x4^3) + ((+1)*x4^4) + ((+1)*x1^1*x3^2*x5^1) + ((+1)*x2^1*x3^2*x5^1) + ((+1)*x3^3*x5^1) + ((+1)*x3^2*x4^1*x5^1) + ((+1)*x1^1*x4^2*x5^1) + ((+1)*x4^3*x5^1) + ((+1)*x1^1*x3^1*x5^2) + ((+1)*x2^1*x3^1*x5^2) + ((+1)*x3^2*x5^2) + ((+1)*x1^1*x4^1*x5^2) + ((+1)*x3^1*x4^1*x5^2) + ((+1)*x4^2*x5^2) + ((+1)*x2^1*x5^3) + ((+1)*x3^1*x5^3) + ((+1)*x5^4)");
    groebnerBasisCyclic6Short.push_back("((+1)*x1^1*x3^2*x5^4) + ((+1)*x2^2*x4^1*x5^4) + ((+1)*x2^1*x3^1*x4^1*x5^4) + ((+1)*x3^2*x4^1*x5^4) + ((+1)*x1^1*x4^2*x5^4) + ((+1)*x2^1*x4^2*x5^4) + ((+1)*x4^3*x5^4) + ((+1)*x2^2*x5^5) + ((+1)*x2^1*x3^1*x5^5) + ((+1)*x2^1*x4^1*x5^5) + ((+1)*x3^1*x4^1*x5^5) + ((+1)*x4^2*x5^5) + ((+1)*x2^1*x5^6) + ((+1)*x3^1*x5^6) + ((t^12+t^5+t^3+t^2+t+1)*x2^1) + ((t^12+t^5+t^3+t^2+t+1)*x5^1)");
    groebnerBasisCyclic6Short.push_back("((+1)*x2^1*x4^3*x5^4) + ((+1)*x2^1*x4^2*x5^5) + ((+1)*x4^3*x5^5) + ((+1)*x4^2*x5^6) + ((t^12+t^5+t^3+t^2+t+1)*x2^1*x4^1) + ((t^12+t^5+t^3+t^2+t+1)*x2^1*x5^1) + ((t^12+t^5+t^3+t^2+t+1)*x4^1*x5^1) + ((t^12+t^5+t^3+t^2+t+1)*x5^2)");
    groebnerBasisCyclic6Short.push_back("((+1)*x2^1*x3^2*x5^6) + ((+1)*x2^1*x4^2*x5^6) + ((+1)*x3^2*x5^7) + ((+1)*x4^2*x5^7) + ((+1)*x2^1*x5^8) + ((+1)*x5^9) + ((t^12+t^5+t^3+t^2+t+1)*x1^1*x3^2) + ((t^12+t^5+t^3+t^2+t+1)*x2^1*x3^2) + ((t^12+t^5+t^3+t^2+t+1)*x2^2*x4^1) + ((t^12+t^5+t^3+t^2+t+1)*x2^1*x3^1*x4^1) + ((t^12+t^5+t^3+t^2+t+1)*x3^2*x4^1) + ((t^12+t^5+t^3+t^2+t+1)*x1^1*x4^2) + ((t^12+t^5+t^3+t^2+t+1)*x4^3) + ((t^12+t^5+t^3+t^2+t+1)*x2^2*x5^1) + ((t^12+t^5+t^3+t^2+t+1)*x2^1*x3^1*x5^1) + ((t^12+t^5+t^3+t^2+t+1)*x3^2*x5^1) + ((t^12+t^5+t^3+t^2+t+1)*x2^1*x4^1*x5^1) + ((t^12+t^5+t^3+t^2+t+1)*x3^1*x4^1*x5^1) + ((t^12+t^5+t^3+t^2+t+1)*x2^1*x5^2) + ((t^12+t^5+t^3+t^2+t+1)*x3^1*x5^2)");
    groebnerBasisCyclic6Short.push_back("((+1)*x1^1*x3^1*x4^1) + ((+1)*x1^1*x4^2) + ((+1)*x3^1*x4^2) + ((+1)*x4^3) + ((+1)*x1^1*x3^1*x5^1) + ((+1)*x1^1*x4^1*x5^1) + ((+1)*x3^1*x4^1*x5^1) + ((+1)*x4^2*x5^1)");
    groebnerBasisCyclic6Short.push_back("((+1)*x2^1*x3^2*x4^1) + ((+1)*x2^1*x3^2*x5^1) + ((+1)*x3^2*x4^1*x5^1) + ((+1)*x3^2*x5^2) + ((+1)*x2^1*x4^1*x5^2) + ((+1)*x2^1*x5^3) + ((+1)*x4^1*x5^3) + ((+1)*x5^4)");
    groebnerBasisCyclic6Short.push_back("((+1)*x2^2*x4^2) + ((+1)*x2^2*x5^2) + ((+1)*x4^2*x5^2) + ((+1)*x5^4)");
    groebnerBasisCyclic6Short.push_back("((+1)*x2^1*x3^1*x4^2) + ((+1)*x2^1*x4^2*x5^1) + ((+1)*x3^1*x4^2*x5^1) + ((+1)*x2^1*x3^1*x5^2) + ((+1)*x4^2*x5^2) + ((+1)*x2^1*x5^3) + ((+1)*x3^1*x5^3) + ((+1)*x5^4)");
    groebnerBasisCyclic6Short.push_back("((+1)*x3^2*x4^2*x5^2) + ((+1)*x1^1*x3^1*x5^4) + ((+1)*x2^1*x3^1*x5^4) + ((+1)*x1^1*x4^1*x5^4) + ((+1)*x3^1*x4^1*x5^4) + ((+1)*x4^2*x5^4) + ((+1)*x2^1*x5^5) + ((+1)*x3^1*x5^5) + ((+1)*x5^6) + ((t^12+t^5+t^3+t^2+t+1)*1)");
    groebnerBasisCyclic6Short.push_back("((+1)*x1^1*x4^4*x5^2) + ((+1)*x4^5*x5^2) + ((+1)*x2^2*x4^1*x5^4) + ((+1)*x2^1*x3^1*x4^1*x5^4) + ((+1)*x2^1*x4^2*x5^4) + ((+1)*x2^2*x5^5) + ((+1)*x2^1*x3^1*x5^5) + ((+1)*x2^1*x4^1*x5^5) + ((+1)*x3^1*x4^1*x5^5) + ((+1)*x4^2*x5^5) + ((+1)*x2^1*x5^6) + ((+1)*x3^1*x5^6) + ((t^12+t^5+t^3+t^2+t+1)*x1^1) + ((t^12+t^5+t^3+t^2+t+1)*x2^1) + ((t^12+t^5+t^3+t^2+t+1)*x4^1) + ((t^12+t^5+t^3+t^2+t+1)*x5^1)");
    groebnerBasisCyclic6Short.push_back("((+1)*x2^2*x5^6) + ((+1)*x5^8) + ((t^12+t^5+t^3+t^2+t+1)*x2^2) + ((t^12+t^5+t^3+t^2+t+1)*x5^2)");
    groebnerBasisCyclic6Short.push_back("((+1)*x1^1*x3^1*x5^6) + ((+1)*x2^1*x3^1*x5^6) + ((+1)*x1^1*x4^1*x5^6) + ((+1)*x3^1*x4^1*x5^6) + ((+1)*x4^2*x5^6) + ((+1)*x2^1*x5^7) + ((+1)*x3^1*x5^7) + ((+1)*x5^8) + ((t^12+t^5+t^3+t^2+t+1)*x1^1*x3^1) + ((t^12+t^5+t^3+t^2+t+1)*x2^1*x3^1) + ((t^12+t^5+t^3+t^2+t+1)*x1^1*x4^1) + ((t^12+t^5+t^3+t^2+t+1)*x3^1*x4^1) + ((t^12+t^5+t^3+t^2+t+1)*x4^2) + ((t^12+t^5+t^3+t^2+t+1)*x2^1*x5^1) + ((t^12+t^5+t^3+t^2+t+1)*x3^1*x5^1) + ((t^12+t^5+t^3+t^2+t+1)*x5^2)");
    groebnerBasisCyclic6Short.push_back("((+1)*x2^1*x3^1*x4^1*x5^6) + ((+1)*x2^1*x3^1*x5^7) + ((+1)*x2^1*x4^1*x5^7) + ((+1)*x3^1*x4^1*x5^7) + ((+1)*x2^1*x5^8) + ((+1)*x3^1*x5^8) + ((+1)*x4^1*x5^8) + ((+1)*x5^9) + ((t^12+t^5+t^3+t^2+t+1)*x2^1*x3^1*x4^1) + ((t^12+t^5+t^3+t^2+t+1)*x2^1*x3^1*x5^1) + ((t^12+t^5+t^3+t^2+t+1)*x2^1*x4^1*x5^1) + ((t^12+t^5+t^3+t^2+t+1)*x3^1*x4^1*x5^1) + ((t^12+t^5+t^3+t^2+t+1)*x2^1*x5^2) + ((t^12+t^5+t^3+t^2+t+1)*x3^1*x5^2) + ((t^12+t^5+t^3+t^2+t+1)*x4^1*x5^2) + ((t^12+t^5+t^3+t^2+t+1)*x5^3)");
        
    /* 16 bits */
    bool testCyclic6 = true;
    size_t i = 0;
    while(i < basisShort.size() && testCyclic6 == true )
    {
        testCyclic6 = testCyclic6 && (groebnerBasisCyclic6Short[i].compare(basisShort[i])==0);
        i++;
    }
    if(testCyclic6==true)
    {
        cout << "Test cyclic6 GF(2^15) on 16 bits pass" << endl;
        return 0;
    }
    else
    {
        cout << "Test cyclic6 GF(2^15) on 16 bits failed" << endl;
        return -1;
    }
}


