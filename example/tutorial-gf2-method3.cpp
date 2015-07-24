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
 *  \file tutorial-gf2-method3.cpp
 *  \example tutorial-gf2-method3.cpp
 *  \brief Tutorial with f4 sources use.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include <openf4.h>

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

    // Define element-gf2 tools.
    typedef ElementGF2 eltType;
    
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
    polynomialArray.emplace_back("x0+x1+x2+x3+x4+x5");
    polynomialArray.emplace_back("x0*x1+x1*x2+x2*x3+x3*x4+x0*x5+x4*x5");
    polynomialArray.emplace_back("x0*x1*x2+x1*x2*x3+x2*x3*x4+x0*x1*x5+x0*x4*x5+x3*x4*x5");
    polynomialArray.emplace_back("x0*x1*x2*x3+x1*x2*x3*x4+x0*x1*x2*x5+x0*x1*x4*x5+x0*x3*x4*x5+x2*x3*x4*x5");
    polynomialArray.emplace_back("x0*x1*x2*x3*x4+x0*x1*x2*x3*x5+x0*x1*x2*x4*x5+x0*x1*x3*x4*x5+x0*x2*x3*x4*x5+x1*x2*x3*x4*x5");
    polynomialArray.emplace_back("x0*x1*x2*x3*x4*x5-1");

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
