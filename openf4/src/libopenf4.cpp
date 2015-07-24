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
 *  \file libopenf4.cpp
 *  \brief Compute a grevlex groebner groebner basis of the input.
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */
 
#ifndef OPENF4_LIBF4_CPP
#define OPENF4_LIBF4_CPP

/** \cond */
#include <iostream>
#include <sstream>
#include <algorithm>
/** \endcond */
#include <libopenf4.h>
#include "../include/ideal.h"

using namespace F4;
using namespace std;

/* Global variables */
int F4::VERBOSE=0;
int F4::NB_THREAD=1;

typedef ElementPrime<int16_t> eltType1;
typedef ElementPrime<int32_t> eltType2;
typedef ElementPrime<int64_t> eltType3;

vector<string> groebnerBasisF4(int64_t modulo, int nbVariable, vector<string> variableName, vector<string> polynomialList, int nbThread, int verbose)
{
    #ifdef USE_OPENMP
    F4::NB_THREAD=min(nbThread, omp_get_num_procs());
    #else
    F4::NB_THREAD=1;
    #endif
    F4::VERBOSE = verbose;
    
    /* Init monomial tools */
    Monomial::initMonomial(nbVariable);
    string * vars = new string[nbVariable];
    for(int i = 0; i< nbVariable; i++)
    {
        vars[i]=variableName[i];
    }
    Monomial::setVariable(vars);
    
    if(modulo <= 251)
    {
        /* Init element-prime tools */
        eltType1::setModulo((int16_t)modulo);
        
        /* Create polynomial array */
        vector<Polynomial<eltType1>> polynomialArray;
        
        /* Fill the polynomial array */
        for(size_t i=0; i< polynomialList.size(); i++)
        {
            polynomialArray.emplace_back(polynomialList[i]);
        }

        /* Create ideal */
        Ideal<eltType1> ideal(polynomialArray, nbVariable);
        
        /* Compute a reduced groebner basis */
        ideal.f4();
        
        /* Return the reduced groebner basis */
        return ideal.getReducedGroebnerBasis();
    }
    else if(modulo <= 65521)
    {
        /* Init element-prime tools */
        eltType2::setModulo((int32_t)modulo);
        
        /* Create polynomial array */
        vector<Polynomial<eltType2>> polynomialArray;
        
        /* Fill the polynomial array */
        for(size_t i=0; i< polynomialList.size(); i++)
        {
            polynomialArray.emplace_back(polynomialList[i]);
        }

        /* Create ideal */
        Ideal<eltType2> ideal(polynomialArray, nbVariable);
        
        /* Compute a reduced groebner basis */
        ideal.f4();
        
        /* Return the reduced groebner basis */
        return ideal.getReducedGroebnerBasis();
    }
    else if (modulo <= 4294967291LL)
    {
        /* Init element-prime tools */
        eltType3::setModulo(modulo);
        
        /* Create polynomial array */
        vector<Polynomial<eltType3>> polynomialArray;
        
        /* Fill the polynomial array */
        for(size_t i=0; i< polynomialList.size(); i++)
        {
            polynomialArray.emplace_back(polynomialList[i]);
        }

        /* Create ideal */
        Ideal<eltType3> ideal(polynomialArray, nbVariable);
        
        /* Compute a reduced groebner basis */
        ideal.f4();
        
        /* Return the reduced groebner basis */
        return ideal.getReducedGroebnerBasis();
    }
    else
    {
        cout << "Use groebnerBasisGivaroIntegerF4 for modulo > 4294967291" << endl;
        vector<string> resNul;
        return resNul;
    }
}


vector<string> groebnerBasisGF2F4(int nbVariable, vector<string> variableName, vector<string> polynomialList, int nbThread, int verbose)
{
    #ifdef USE_OPENMP
    F4::NB_THREAD=min(nbThread, omp_get_num_procs());
    #else
    F4::NB_THREAD=1;
    #endif
    F4::VERBOSE = verbose;
    
    /* Init monomial tools */
    Monomial::initMonomial(nbVariable);
    string * vars = new string[nbVariable];
    for(int i = 0; i< nbVariable; i++)
    {
        vars[i]=variableName[i];
    }
    Monomial::setVariable(vars);
    
    /* Define GF2 element type */
    typedef ElementGF2 eltType;
    
    /* Create polynomial array */
    vector<Polynomial<eltType>> polynomialArray;
    
    /* Fill the polynomial array */
    for(size_t i=0; i< polynomialList.size(); i++)
    {
        polynomialArray.emplace_back(polynomialList[i]);
    }

    /* Create ideal */
    Ideal<eltType> ideal(polynomialArray, nbVariable);
    
    /* Compute a reduced groebner basis */
    ideal.f4();
    
    /* Return the reduced groebner basis */
    return ideal.getReducedGroebnerBasis();
}


typedef ElementGF2Extension<uint16_t> eltType4;
typedef ElementGF2Extension<uint32_t> eltType5;
typedef ElementGF2Extension<uint64_t> eltType6;

vector<string> groebnerBasisGF2ExtensionF4(string modulo, int nbVariable, vector<string> variableName, string polyVarName, vector<string> polynomialList, int nbThread, int verbose)
{
    #ifdef USE_OPENMP
    F4::NB_THREAD=min(nbThread, omp_get_num_procs());
    #else
    F4::NB_THREAD=1;
    #endif
    F4::VERBOSE = verbose;
    
    /* Init monomial tools */
    Monomial::initMonomial(nbVariable);
    string * vars = new string[nbVariable];
    for(int i = 0; i< nbVariable; i++)
    {
        vars[i]=variableName[i];
    }
    Monomial::setVariable(vars);
    
    /* Find the extension degree from modulo */
    eltType6::setVariableName(polyVarName);
    eltType6::setModulo(modulo);
    int nbBitMask=eltType6::getMaskBit();
    
    if(nbBitMask < 16)
    {
        /* Init element-prime tools */
        eltType4::setVariableName(polyVarName);
        eltType4::setModulo(modulo);
        
        /* Create polynomial array */
        vector<Polynomial<eltType4>> polynomialArray;
        
        /* Fill the polynomial array */
        for(size_t i=0; i< polynomialList.size(); i++)
        {
            polynomialArray.emplace_back(polynomialList[i]);
        }

        /* Create ideal */
        Ideal<eltType4> ideal(polynomialArray, nbVariable);
        
        /* Compute a reduced groebner basis */
        ideal.f4();
        
        /* Return the reduced groebner basis */
        return ideal.getReducedGroebnerBasis();
    }
    else if(nbBitMask < 32)
    {
        /* Init element-prime tools */
        eltType5::setVariableName(polyVarName);
        eltType5::setModulo(modulo);
        
        /* Create polynomial array */
        vector<Polynomial<eltType5>> polynomialArray;
        
        /* Fill the polynomial array */
        for(size_t i=0; i< polynomialList.size(); i++)
        {
            polynomialArray.emplace_back(polynomialList[i]);
        }

        /* Create ideal */
        Ideal<eltType5> ideal(polynomialArray, nbVariable);
        
        /* Compute a reduced groebner basis */
        ideal.f4();
        
        /* Return the reduced groebner basis */
        return ideal.getReducedGroebnerBasis();
    }
    else if(nbBitMask < 64)
    {
        /* Create polynomial array */
        vector<Polynomial<eltType6>> polynomialArray;

        /* Fill the polynomial array */
        for(size_t i=0; i< polynomialList.size(); i++)
        {
            polynomialArray.emplace_back(polynomialList[i]);
        }

        /* Create ideal */
        Ideal<eltType6> ideal(polynomialArray, nbVariable);

        /* Compute a reduced groebner basis */
        ideal.f4();

        /* Return the reduced groebner basis */
        return ideal.getReducedGroebnerBasis();
    }
    else
    {
        cout << "Impossible for the moment to compute in GF(2^n) with n > 63" << endl;
        vector<string> resNul;
        return resNul;
    }
}

#ifdef HAVE_GIVARO
vector<string> groebnerBasisGivaroIntegerF4(string modulo, int nbVariable, vector<string> variableName, vector<string> polynomialList, int nbThread, int verbose)
{
    #ifdef USE_OPENMP
    F4::NB_THREAD=min(nbThread, omp_get_num_procs());
    #else
    F4::NB_THREAD=1;
    #endif
    F4::VERBOSE = verbose;
    
    /* Init monomial tools */
    Monomial::initMonomial(nbVariable);
    string * vars = new string[nbVariable];
    for(int i = 0; i< nbVariable; i++)
    {
        vars[i]=variableName[i];
    }
    Monomial::setVariable(vars);
    
    /* Init element-prime tools */
    typedef Givaro::Modular<Givaro::Integer> Field;
    Givaro::Integer mod(Givaro::Integer(modulo.c_str()));
    Field F(mod);
    typedef ElementGivaro<Field> eltType;
    eltType::setField(F);
    
    /* Create polynomial array */
    vector<Polynomial<eltType>> polynomialArray;
    
    /* Fill the polynomial array */
    for(size_t i=0; i< polynomialList.size(); i++)
    {
        polynomialArray.emplace_back(polynomialList[i]);
    }

    /* Create ideal */
    Ideal<eltType> ideal(polynomialArray, nbVariable);
    
    /* Compute a reduced groebner basis */
    ideal.f4();
    
    /* Return the reduced groebner basis */
    return ideal.getReducedGroebnerBasis();
}
#endif // HAVE_GIVARO


#endif // OPENF4_LIBF4_CPP

