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
 *  \file tutorial-gf2-extension-method3.cpp
 *  \example tutorial-gf2-extension-method3.cpp
 *  \brief Tutorial with f4 sources use.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include <f4.h>

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=0;
#ifdef USE_OPENMP
int F4::NB_THREAD=omp_get_num_procs();
#else
int F4::NB_THREAD=1;
#endif

int main (int argc, char **argv)
{
    cout << "#########################################################" << endl;
    cout << "#               TUTORIAL WITH SOURCES USE               #" << endl;
    cout << "#########################################################" << endl << endl;

    // Initialize element-gf2-extension tools.
    typedef ElementGF2Extension<uint64_t> eltType;
    eltType::setVariableName("t");
    string modulo= string("t^63 + t^61 + t^57 + t^56 + t^54 + t^51 + t^47 + t^46 + t^45 + t^44 + t^43 + t^42 + t^39 + t^38 + t^35 + t^34 + t^32 + t^31 + t^28 + t^25 + t^24 + t^23 + t^21 + t^19 + t^18 + t^17 + t^15 + t^13 + t^10 + t^8 + t^7 + t^5 + t^2 + t + 1");
    eltType::setModulo(modulo);
    
    // Init monomial tools
    Monomial::initMonomial(6);
    
    // Create variable name array
    string * vars = new string[6];
    for(int i = 0; i < 6; i++)
    {
        vars[i]='x'+to_string(i);
    }
    Monomial::setVariable(vars);
    
    // Create polynomial array
    vector<Polynomial<eltType>> polynomialArray;
    
    // Fill the polynomial array
    polynomialArray.emplace_back("(t+t^3)*x0+(t+t^3)*x1+(t+t^3)*x2+(t+t^3)*x3+(t+t^3)*x4+(t+t^3)*x5");
    polynomialArray.emplace_back("(t+t^3)*x0*x1+(t+t^3)*x1*x2+(t+t^3)*x2*x3+(t+t^3)*x3*x4+(t+t^3)*x0*x5+(t+t^3)*x4*x5");
    polynomialArray.emplace_back("(t+t^3)*x0*x1*x2+(t+t^3)*x1*x2*x3+(t+t^3)*x2*x3*x4+(t+t^3)*x0*x1*x5+(t+t^3)*x0*x4*x5+(t+t^3)*x3*x4*x5");
    polynomialArray.emplace_back("(t+t^3)*x0*x1*x2*x3+(t+t^3)*x1*x2*x3*x4+(t+t^3)*x0*x1*x2*x5+(t+t^3)*x0*x1*x4*x5+(t+t^3)*x0*x3*x4*x5+(t+t^3)*x2*x3*x4*x5");
    polynomialArray.emplace_back("(t+t^3)*x0*x1*x2*x3*x4+(t+t^3)*x0*x1*x2*x3*x5+(t+t^3)*x0*x1*x2*x4*x5+(t+t^3)*x0*x1*x3*x4*x5+(t+t^3)*x0*x2*x3*x4*x5+(t+t^3)*x1*x2*x3*x4*x5");
    polynomialArray.emplace_back("(t+t^3)*x0*x1*x2*x3*x4*x5-1");

    // Create cyclic6 ideal.
    Ideal<eltType> cyclic6(polynomialArray, 6);
    
    // Compute a reduced groebner basis.
    int nbGen=cyclic6.f4();
    cout << "The groebner basis has " << nbGen << " generators " << endl << endl; 
    
    // Get the reduced groebner basis under string format.
    vector<string> basis = cyclic6.getReducedGroebnerBasis();
    
    // Print the reduce groebner basis.
    for(size_t i = 0; i < basis.size(); i++)
    {
        cout << basis[i] << endl;
    }
    
    return 0;
}
