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
 *  \file check-random-gf2-extension-32bits.cpp
 *  \example check-random-gf2-extension-32bits.cpp
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
    cout << "#            CHECK RANDOM GF(2^24) BITS                 #" << endl;
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
    polynomialArray.emplace_back("(t^22 + t^21 + t^20 + t^17 + t^9 + t^8 + t^7 + t^6 + t^2 + t)*x1^3*x2 + (t^23 + t^21 + t^20 + t^19 + t^14 + t^11 + t^9 + t^8 + t^7 + t^5 + t^3 + 1)*x0^3*x4 + (t^21 + t^20 + t^16 + t^13 + t^8 + t^7 + t^5 + t^4 + 1)*x1^2*x3 + (t^22 + t^21 + t^20 + t^17 + t^14 + t^13 + t^11 + t^7 + t^6 + t)*x1*x3 + (t^22 + t^21 + t^19 + t^18 + t^16 + t^12 + t^9 + t^8 + t^6 + t^4 + t + 1)*x4");
    polynomialArray.emplace_back("(t^23 + t^22 + t^20 + t^17 + t^16 + t^14 + t^12 + t^9 + t^7 + t^6 + t^4 + t^3 + t + 1)*x1^2*x2*x3 + (t^23 + t^22 + t^19 + t^18 + t^17 + t^14 + t^12 + t^10 + t^8 + t^7 + t^5 + t^3 + t)*x0^2*x2*x4 + (t^23 + t^21 + t^18 + t^17 + t^13 + t^12 + t^11 + t^9 + t^6 + t^5 + t^3 + t^2 + t)*x0*x2*x4 + (t^16 + t^12 + t^10 + t^9 + t^7 + t^5 + t^4 + t)*x0*x4^2 + (t^22 + t^19 + t^18 + t^17 + t^15 + t^13 + t^11 + t^9 + t^4 + t^2 + t)*x1*x4");
    polynomialArray.emplace_back("(t^22 + t^21 + t^18 + t^17 + t^16 + t^14 + t^13 + t^11 + t^10 + t^8 + t^6 + t^5 + t + 1)*x0*x1^2*x2 + (t^21 + t^20 + t^19 + t^17 + t^14 + t^11 + t^7 + t^5 + t^4 + t^2 + t + 1)*x0*x1*x2 + (t^20 + t^18 + t^17 + t^16 + t^13 + t^11 + t^10 + t^9 + t^7 + t^5 + t^4 + t + 1)*x1*x2^2 + (t^22 + t^19 + t^13 + t^11 + t^10 + t^8 + t^6 + t^5 + t^4)*x2^2*x4 + (t^22 + t^20 + t^18 + t^16 + t^15 + t^14 + t^12 + t^11 + t^5)*x2*x4^2");
    polynomialArray.emplace_back("(t^22 + t^21 + t^20 + t^19 + t^16 + t^14 + t^13 + t^12 + t^11 + t^9 + t^6 + t^4)*x0^2*x1*x2 + (t^23 + t^22 + t^19 + t^18 + t^16 + t^12 + t^10 + t^9 + t^5 + t^4 + t^3 + t^2 + t)*x1^3*x3 + (t^22 + t^21 + t^18 + t^13 + t^12 + t^10 + t^8 + t^6 + t^5 + t^3)*x0*x2*x3^2 + (t^23 + t^21 + t^19 + t^15 + t^14 + t^10 + t^9 + t^8 + t^7 + t^5 + t^4 + t^3 + t^2 + t + 1)*x3^2*x4^2 + (t^23 + t^22 + t^19 + t^16 + t^15 + t^14 + t^12 + t^11 + t^9 + t^5 + t^4 + t^2 + t + 1)*x0*x2");
    polynomialArray.emplace_back("(t^23 + t^21 + t^20 + t^19 + t^16 + t^15 + t^13 + t^11 + t^8 + t^6 + t^4 + t^3 + t^2 + 1)*x3^4 + (t^22 + t^21 + t^20 + t^18 + t^17 + t^16 + t^15 + t^11 + t^10 + t^6 + t^4 + t^3)*x0^2*x3*x4 + (t^23 + t^22 + t^21 + t^20 + t^18 + t^17 + t^14 + t^13 + t^11 + t^7 + t^6 + t^4 + t^3 + t^2 + t)*x3^2*x4^2 + (t^18 + t^17 + t^15 + t^13 + t^10 + t^8 + t^7 + t^6 + t^4 + t^3 + 1)*x1*x4^3 + (t^23 + t^21 + t^17 + t^16 + t^15 + t^11 + t^9 + t^8 + t^7 + t^4)*x4");
    polynomialArray.emplace_back("(t^23 + t^20 + t^19 + t^15 + t^13 + t^11 + t^9 + t^7 + t^6 + t^5 + t^4 + t^3 + t + 1)*x0*x3^3 + (t^20 + t^18 + t^17 + t^16 + t^14 + t^13 + t^11 + t^10 + t^9 + t^7 + t^6 + t^2 + t)*x2*x3^2*x4 + (t^23 + t^20 + t^19 + t^16 + t^12 + t^10 + t^9 + t^8 + t^5 + 1)*x1*x4^3 + (t^22 + t^17 + t^16 + t^15 + t^12 + t^11 + t^7 + t^6 + t^3 + t)*x0*x1^2 + (t^19 + t^17 + t^16 + t^14 + t^13 + t^8 + t^7 + t^6 + t^5 + t^4 + t^2 + 1)*x0*x2*x4");
    
    // Compute a reduce groebner basis
    vector<string> basis= groebnerBasisGF2ExtensionF4("t^24 + t^22 + t^21 + t^19 + t^14 + t^13 + t^11 + t^6 + t^5 + t^3 + t^2 + t + 1", 5, variableName, "t", polynomialArray, 1, 0);
    
    // Fill reference vectors
    vector<string> groebnerBasis;
    groebnerBasis.push_back("((+1)*x1^3*x2^1) + ((t^23+t^22+t^21+t^20+t^15+t^13+t^12+t^11+t^10+t^8+t^7+t^6+t^4+1)*x1^2*x3^1) + ((t^23+t^21+t^20+t^18+t^17+t^15+t^13+t^12+t^10+t^9+t^6+t^5+t^3+t^2+1)*x1^1*x3^1) + ((t^22+t^21+t^20+t^17+t^15+t^14+t^10+t^9+t^8+t^4)*x4^1)");
    groebnerBasis.push_back("((+1)*x3^4) + ((t^20+t^19+t^17+t^15+t^14+t^13+t^12+t^11+t^9+t^8+t^4+t^3+t^2+1)*x4^1)");
    groebnerBasis.push_back("((+1)*x0^1*x3^3) + ((t^23+t^22+t^20+t^17+t^16+t^15+t^13+t^12+t^11+t^9+t^8+t^6+t^5+t^4+t^3+t^2+1)*x2^1*x3^2*x4^1) + ((t^23+t^21+t^19+t^17+t^16+t^14+t^13+t^12+t^11+t^10+t^7+t^4+t^2+t+1)*x0^1*x1^2)");
    groebnerBasis.push_back("((+1)*x0^1*x1^3)");
    groebnerBasis.push_back("((+1)*x1^2*x2^2)");
    groebnerBasis.push_back("((+1)*x1^1*x2^3)");
    groebnerBasis.push_back("((+1)*x1^3*x3^1) + ((t^22+t^17+t^14+t^11+t^8+t^6+t^5+t^3+t+1)*x0^1*x2^1)");
    groebnerBasis.push_back("((+1)*x3^3*x4^1)");
    groebnerBasis.push_back("((+1)*x0^2*x2^1)");
    groebnerBasis.push_back("((+1)*x0^1*x1^1*x2^1) + ((t^23+t^22+t^21+t^20+t^19+t^15+t^13+t^10+t^9+t^8+t^7+t^5+t^4+t^3+t+1)*x1^1*x2^2)");
    groebnerBasis.push_back("((+1)*x0^1*x2^2)");
    groebnerBasis.push_back("((+1)*x0^1*x2^1*x3^1)");
    groebnerBasis.push_back("((+1)*x1^1*x2^1*x3^1) + ((t^20+t^18+t^17+t^16+t^8+t^5+t^3+t^2+1)*x2^1*x4^1)");
    groebnerBasis.push_back("((+1)*x1^1*x3^2) + ((t^20+t^18+t^17+t^16+t^8+t^5+t^3+t^2+1)*x3^1*x4^1)");
    groebnerBasis.push_back("((+1)*x2^2*x4^1)");
    groebnerBasis.push_back("((+1)*x1^1*x4^1)");
    groebnerBasis.push_back("((+1)*x4^2)");
    groebnerBasis.push_back("((+1)*x0^1*x4^1)");
    groebnerBasis.push_back("((+1)*x0^1*x1^1*x3^1)");

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
        cout << "Test random gf2 extension 32 bits pass" << endl;
        return 0;
    }
    else
    {
        cout << "Test random gf2 extension 32 bits failed" << endl;
        return -1;
    }
}


