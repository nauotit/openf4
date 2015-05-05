/* 
 * Copyright (C) 2010 Antoine Joux and Vanessa Vitse 

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 */

/**
 *  \file libf4.cpp
 *  \brief Compute a grevlex groebner groebner basis of the input.
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */
 
#ifndef F4_LIBF4_CPP
#define F4_LIBF4_CPP

#include <iostream>
#include <sstream>
#include "../include/libf4.h"
#include "../include/ideal.h"

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=0;
int F4::NB_THREAD=1;

typedef ElementPrime<int16_t> eltType1;
typedef ElementPrime<int32_t> eltType2;
typedef ElementPrime<int64_t> eltType3;

vector<string> groebnerBasisF4(int64_t modulo, int sizeMonomialArray, int nbVariable, vector<string> variableName, vector<string> polynomialList, int nbThread, int verbose)
{
    F4::NB_THREAD = min(nbThread, omp_get_num_procs());
    F4::VERBOSE = verbose;

    int degree = 11;
    int tabulatedProductSize[2]={2,10};
    
    // Init monomial tools
    Monomial::initMonomial(nbVariable, degree);
    string * vars = new string[nbVariable];
    for(int i = 0; i< nbVariable; i++)
    {
        vars[i]=variableName[i];
    }
    Monomial::setVariable(vars);
    
    if(modulo <= 251)
    {
        // Init element-prime tools
        eltType1::setModulo((int16_t)modulo);
        
        // Create polynomial array
        vector<Polynomial<eltType1>> polynomialArray;
        
        // Fill the polynomial array
        for(size_t i=0; i< polynomialList.size(); i++)
        {
            polynomialArray.emplace_back(polynomialList[i]);
        }

        // Create ideal;
        Ideal<eltType1> ideal(polynomialArray, nbVariable, sizeMonomialArray, degree, tabulatedProductSize[0], tabulatedProductSize[1]);
        
        // Compute a reduced groebner basis;
        ideal.f4();
        
        // Return the reduced groebner basis
        return ideal.getReducedGroebnerBasis();
    }
    else if(modulo <= 65521)
    {
        // Init element-prime tools
        eltType2::setModulo((int32_t)modulo);
        
        // Create polynomial array
        vector<Polynomial<eltType2>> polynomialArray;
        
        // Fill the polynomial array
        for(size_t i=0; i< polynomialList.size(); i++)
        {
            polynomialArray.emplace_back(polynomialList[i]);
        }

        // Create ideal;
        Ideal<eltType2> ideal(polynomialArray, nbVariable, sizeMonomialArray, degree, tabulatedProductSize[0], tabulatedProductSize[1]);
        
        // Compute a reduced groebner basis;
        ideal.f4();
        
        // Return the reduced groebner basis
        return ideal.getReducedGroebnerBasis();
    }
    else
    {
       // Init element-prime tools
        eltType3::setModulo(modulo);
        
        // Create polynomial array
        vector<Polynomial<eltType3>> polynomialArray;
        
        // Fill the polynomial array
        for(size_t i=0; i< polynomialList.size(); i++)
        {
            polynomialArray.emplace_back(polynomialList[i]);
        }

        // Create ideal;
        Ideal<eltType3> ideal(polynomialArray, nbVariable, sizeMonomialArray, degree, tabulatedProductSize[0], tabulatedProductSize[1]);
        
        // Compute a reduced groebner basis;
        ideal.f4();
        
        // Return the reduced groebner basis
        return ideal.getReducedGroebnerBasis();
    }
}

#endif // F4_LIBF4_CPP

