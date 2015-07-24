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
 *  \file check-random-32bits.cpp
 *  \example check-random-32bits.cpp
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
    cout << "#                 CHECK RANDOM 32 BITS                  #" << endl;
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
    polynomialArray.emplace_back("-1404*x0*x3^2 - 1016*x1^2*x4 - 685*x0*x3*x4 - 5497*x0*x2 + 5630*x3^2");
    polynomialArray.emplace_back("-4161*x1^3 - 3864*x0^2*x3 - 2215*x2^2*x3 + 1829*x3*x4^2 + 9365*x0*x4");
    polynomialArray.emplace_back("7840*x0*x1^2 - 2631*x1*x2^2 - 6008*x1^2*x4 + 1736*x2*x3*x4 - 9165*x0*x1");
    polynomialArray.emplace_back("-3750*x2^2*x3 + 7904*x2^2*x4 - 12972*x2*x3*x4 - 7655*x0*x4^2 - 2272*x0^2");
    polynomialArray.emplace_back("12184*x0*x2^2 - 11764*x0*x2*x3 - 8051*x2*x3^2 - 4624*x3^3 - 1134*x0^2");
    polynomialArray.emplace_back("134*x2^3 - 627*x3^3 + 4511*x1^2 - 5536*x0*x4 - 11949*x3");

    // Compute a reduce groebner basis
    vector<string> basis= groebnerBasisF4(26633, 5, variableName, polynomialArray, 1, 0);
    
    // Fill reference vectors
    vector<string> groebnerBasis;
    
    groebnerBasis.push_back("(1*x0^1*x3^2)");
    groebnerBasis.push_back("(1*x1^3) + (1860*x2^2*x4^1) + (-10870*x2^1*x3^1*x4^1) + (-9794*x0^1*x4^2) + (-7790*x3^1*x4^2) + (-2799*x0^2) + (-1532*x0^1*x4^1)");
    groebnerBasis.push_back("(1*x0^1*x1^2) + (8015*x0^1*x3^1)");
    groebnerBasis.push_back("(1*x2^2*x3^1) + (-8965*x2^2*x4^1) + (-10181*x2^1*x3^1*x4^1) + (1529*x0^1*x4^2) + (-7343*x0^2)");
    groebnerBasis.push_back("(1*x0^1*x2^2) + (3458*x0^2)");
    groebnerBasis.push_back("(1*x2^3) + (4605*x1^2) + (-9979*x0^1*x4^1) + (-4263*x3^1)");
    groebnerBasis.push_back("(1*x2^2*x4^2) + (13276*x2^2*x4^1) + (10331*x1^1*x3^1*x4^1) + (-4882*x2^1*x3^1*x4^1) + (4600*x0^1*x4^2) + (1919*x3^1*x4^2) + (-4872*x0^2) + (1067*x0^1*x2^1) + (-792*x1^1*x3^1) + (-7466*x3^2) + (6305*x0^1*x4^1) + (4490*x3^1*x4^1)");
    groebnerBasis.push_back("(1*x1^1*x3^1*x4^2) + (3695*x2^2*x4^1) + (5722*x1^1*x3^1*x4^1) + (-6841*x2^1*x3^1*x4^1) + (958*x0^1*x4^2) + (7578*x3^1*x4^2) + (278*x0^2) + (-8067*x0^1*x2^1) + (-4682*x1^1*x3^1) + (-9300*x3^2) + (4116*x0^1*x4^1) + (1298*x3^1*x4^1)");
    groebnerBasis.push_back("(1*x2^1*x3^1*x4^2) + (3652*x2^2*x4^1) + (1237*x1^1*x3^1*x4^1) + (1404*x2^1*x3^1*x4^1) + (-4978*x0^1*x4^2) + (1601*x3^1*x4^2) + (-1410*x0^2) + (2608*x0^1*x2^1) + (6314*x1^1*x3^1) + (1620*x3^2) + (11139*x0^1*x4^1) + (-10192*x3^1*x4^1)");
    groebnerBasis.push_back("(1*x0^1*x4^3) + (-8972*x2^2*x4^1) + (3787*x1^1*x3^1*x4^1) + (6608*x2^1*x3^1*x4^1) + (1036*x0^1*x4^2) + (4929*x3^1*x4^2) + (4686*x0^2) + (-8620*x0^1*x2^1) + (-9736*x1^1*x3^1) + (6900*x3^2) + (-1316*x0^1*x4^1) + (5910*x3^1*x4^1)");
    groebnerBasis.push_back("(1*x3^1*x4^3) + (-5369*x2^2*x4^1) + (-1216*x1^1*x3^1*x4^1) + (10984*x2^1*x3^1*x4^1) + (-5849*x0^1*x4^2) + (-567*x3^1*x4^2) + (-7367*x0^2) + (-6197*x0^1*x2^1) + (-1421*x1^1*x3^1) + (11387*x3^2) + (7916*x0^1*x4^1) + (4774*x3^1*x4^1)");
    groebnerBasis.push_back("(1*x0^3)");
    groebnerBasis.push_back("(1*x0^2*x1^1)");
    groebnerBasis.push_back("(1*x0^2*x2^1)");
    groebnerBasis.push_back("(1*x0^1*x1^1*x2^1) + (-9849*x2^2*x4^1) + (4471*x1^1*x3^1*x4^1) + (-4817*x2^1*x3^1*x4^1) + (5476*x0^1*x4^2) + (-10728*x3^1*x4^2) + (13223*x0^2) + (-2687*x0^1*x2^1) + (2706*x1^1*x3^1) + (4499*x3^2) + (-10445*x0^1*x4^1) + (-4368*x3^1*x4^1)");
    groebnerBasis.push_back("(1*x1^1*x2^2) + (10608*x2^1*x3^1*x4^1) + (-10838*x0^1*x1^1) + (-3665*x0^1*x2^1) + (-3124*x0^1*x3^1) + (-11261*x3^2)");
    groebnerBasis.push_back("(1*x0^2*x3^1)");
    groebnerBasis.push_back("(1*x0^1*x1^1*x3^1)");
    groebnerBasis.push_back("(1*x1^2*x3^1) + (8001*x2^1*x3^1*x4^1) + (-4372*x0^1*x4^2) + (-4636*x0^2) + (-8877*x0^1*x2^1) + (2533*x3^2) + (1359*x3^1*x4^1)");
    groebnerBasis.push_back("(1*x0^1*x2^1*x3^1)");
    groebnerBasis.push_back("(1*x1^1*x2^1*x3^1) + (8302*x2^1*x3^1*x4^1) + (-5119*x0^1*x4^2) + (-4624*x0^2) + (6657*x0^1*x2^1) + (6134*x3^2) + (781*x3^1*x4^1)");
    groebnerBasis.push_back("(1*x1^1*x3^2)");
    groebnerBasis.push_back("(1*x2^1*x3^2)");
    groebnerBasis.push_back("(1*x3^3)");
    groebnerBasis.push_back("(1*x0^2*x4^1)");
    groebnerBasis.push_back("(1*x0^1*x1^1*x4^1) + (-1717*x2^2*x4^1) + (-12476*x1^1*x3^1*x4^1) + (-13245*x2^1*x3^1*x4^1) + (12856*x0^1*x4^2) + (1034*x3^1*x4^2) + (12410*x0^2) + (8171*x0^1*x2^1) + (4893*x1^1*x3^1) + (4953*x3^2) + (-7578*x0^1*x4^1) + (-2358*x3^1*x4^1)");
    groebnerBasis.push_back("(1*x1^2*x4^1) + (7319*x0^1*x2^1) + (6443*x3^2)");
    groebnerBasis.push_back("(1*x0^1*x2^1*x4^1) + (2361*x2^2*x4^1) + (-11401*x1^1*x3^1*x4^1) + (11956*x2^1*x3^1*x4^1) + (8321*x0^1*x4^2) + (8583*x3^1*x4^2) + (6466*x0^2) + (5762*x0^1*x2^1) + (10660*x1^1*x3^1) + (393*x3^2) + (-1601*x0^1*x4^1) + (684*x3^1*x4^1)");
    groebnerBasis.push_back("(1*x0^1*x3^1*x4^1)");
    groebnerBasis.push_back("(1*x3^2*x4^1)");

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
        cout << "Test random 32 bits pass" << endl;
        return 0;
    }
    else
    {
        cout << "Test random 32 bits failed" << endl;
        return -1;
    }
}


