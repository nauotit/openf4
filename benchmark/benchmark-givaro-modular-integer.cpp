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
 *  \file benchmark-givaro-modular-integer.cpp
 *  \example benchmark-givaro-modular-integer.cpp
 *  \brief Benchmark with integer coefficients using GMP (through Givaro) representation.
 *  \ingroup benchmark
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include <f4.h>

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=0;
#ifdef USE_OPENMP
int F4::NB_THREAD=min(8, omp_get_num_procs());
#else
int F4::NB_THREAD=1;
#endif

// Init element-givaro tools
typedef Givaro::Modular<Givaro::Integer> Field;
Givaro::Integer modulo(Givaro::Integer("115792089237316195423570985008687907853269984665640564039457584007913129640233"));
Field F(modulo);
typedef ElementGivaro<Field> eltType;

int cyclic6F4(bool magma)
{
    cout << "#########################################################" << endl;
    cout << "#                         CYCLIC 6                      #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Init element-givaro-prime tools
    eltType::setField(F);
    
    // Number of generator
    int nbGen;
    
    // Init monomial tools
    Monomial::initMonomial(6);
    
    // Create polynomial array
    vector<Polynomial<eltType>> polCyclic6;
    
    // Fill the polynomial array
    polCyclic6.emplace_back("x0+x1+x2+x3+x4+x5");
    polCyclic6.emplace_back("x0*x1+x1*x2+x2*x3+x3*x4+x0*x5+x4*x5");
    polCyclic6.emplace_back("x0*x1*x2+x1*x2*x3+x2*x3*x4+x0*x1*x5+x0*x4*x5+x3*x4*x5");
    polCyclic6.emplace_back("x0*x1*x2*x3+x1*x2*x3*x4+x0*x1*x2*x5+x0*x1*x4*x5+x0*x3*x4*x5+x2*x3*x4*x5");
    polCyclic6.emplace_back("x0*x1*x2*x3*x4+x0*x1*x2*x3*x5+x0*x1*x2*x4*x5+x0*x1*x3*x4*x5+x0*x2*x3*x4*x5+x1*x2*x3*x4*x5");
    polCyclic6.emplace_back("x0*x1*x2*x3*x4*x5-1");

    // Create cyclic6 ideal;
    Ideal<eltType> cyclic6(polCyclic6, 6, 100000);
    
    // Compute a reduced groebner basis;
    nbGen=cyclic6.f4();
    
    // Print the reduced groebner basis into a file
    if(magma)
    {
        cyclic6.printReducedGroebnerBasis("cyclic6", modulo);
    }
    
    return nbGen;
}

int cyclic7F4(bool magma)
{
    cout << "#########################################################" << endl;
    cout << "#                         CYCLIC 7                      #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Init element-givaro-prime tools
    eltType::setField(F);
    
    // Number of generator
    int nbGen;
    
    // Init monomial tools
    Monomial::initMonomial(7);
    
    // Create polynomial array
    vector<Polynomial<eltType>> polCyclic7;
    
    // Fill the polynomial array
    polCyclic7.emplace_back("x0+x1+x2+x3+x4+x5+x6");
    polCyclic7.emplace_back("x0*x1+x1*x2+x2*x3+x3*x4+x4*x5+x0*x6+x5*x6");
    polCyclic7.emplace_back("x0*x1*x2+x1*x2*x3+x2*x3*x4+x3*x4*x5+x0*x1*x6+x0*x5*x6+x4*x5*x6");
    polCyclic7.emplace_back("x0*x1*x2*x3+x1*x2*x3*x4+x2*x3*x4*x5+x0*x1*x2*x6+x0*x1*x5*x6+x0*x4*x5*x6+x3*x4*x5*x6");
    polCyclic7.emplace_back("x0*x1*x2*x3*x4+x1*x2*x3*x4*x5+x0*x1*x2*x3*x6+x0*x1*x2*x5*x6+x0*x1*x4*x5*x6+x0*x3*x4*x5*x6+x2*x3*x4*x5*x6");
    polCyclic7.emplace_back("x0*x1*x2*x3*x4*x5+x0*x1*x2*x3*x4*x6+x0*x1*x2*x3*x5*x6+x0*x1*x2*x4*x5*x6+x0*x1*x3*x4*x5*x6+x0*x2*x3*x4*x5*x6+x1*x2*x3*x4*x5*x6");
    polCyclic7.emplace_back("x0*x1*x2*x3*x4*x5*x6-1");

    // Create cyclic7 ideal;
    Ideal<eltType> cyclic7(polCyclic7, 7 , 1000000);
    
    // Compute a reduced groebner basis;
    nbGen=cyclic7.f4();
    
    // Print the reduced groebner basis into a file
    if(magma)
    {
        cyclic7.printReducedGroebnerBasis("cyclic7", modulo);
    }
    
    return nbGen;
}

int cyclic8F4(bool magma)
{
    
    cout << "#########################################################" << endl;
    cout << "#                         CYCLIC 8                      #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Init element-givaro-prime tools
    eltType::setField(F);
    
    // Number of generator
    int nbGen;
    
    // Init monomial tools
    Monomial::initMonomial(8);
    
    // Create polynomial array
    vector<Polynomial<eltType>> polCyclic8;
    
    // Fill the polynomial array
    polCyclic8.emplace_back("x0+x1+x2+x3+x4+x5+x6+x7");
    polCyclic8.emplace_back("x0*x1+x1*x2+x2*x3+x3*x4+x4*x5+x5*x6+x0*x7+x6*x7");
    polCyclic8.emplace_back("x0*x1*x2+x1*x2*x3+x2*x3*x4+x3*x4*x5+x4*x5*x6+x0*x1*x7+x0*x6*x7+x5*x6*x7");
    polCyclic8.emplace_back("x0*x1*x2*x3+x1*x2*x3*x4+x2*x3*x4*x5+x3*x4*x5*x6+x0*x1*x2*x7+x0*x1*x6*x7+x0*x5*x6*x7+x4*x5*x6*x7");
    polCyclic8.emplace_back("x0*x1*x2*x3*x4+x1*x2*x3*x4*x5+x2*x3*x4*x5*x6+x0*x1*x2*x3*x7+x0*x1*x2*x6*x7+x0*x1*x5*x6*x7+x0*x4*x5*x6*x7+x3*x4*x5*x6*x7");
    polCyclic8.emplace_back("x0*x1*x2*x3*x4*x5+x1*x2*x3*x4*x5*x6+x0*x1*x2*x3*x4*x7+x0*x1*x2*x3*x6*x7+x0*x1*x2*x5*x6*x7+x0*x1*x4*x5*x6*x7+x0*x3*x4*x5*x6*x7+x2*x3*x4*x5*x6*x7");
    polCyclic8.emplace_back("x0*x1*x2*x3*x4*x5*x6+x0*x1*x2*x3*x4*x5*x7+x0*x1*x2*x3*x4*x6*x7+x0*x1*x2*x3*x5*x6*x7+x0*x1*x2*x4*x5*x6*x7+x0*x1*x3*x4*x5*x6*x7+x0*x2*x3*x4*x5*x6*x7+x1*x2*x3*x4*x5*x6*x7");
    polCyclic8.emplace_back("x0*x1*x2*x3*x4*x5*x6*x7-1");

    // Create cyclic8 ideal;
    Ideal<eltType> cyclic8(polCyclic8, 8, 1000000);
    
    // Compute a reduced groebner basis;
    nbGen=cyclic8.f4();
    
    // Print the reduced groebner basis into a file
    if(magma)
    {
        cyclic8.printReducedGroebnerBasis("cyclic8", modulo);
    }
    
    return nbGen;
}

int cyclic9F4(bool magma)
{
    
    cout << "#########################################################" << endl;
    cout << "#                         CYCLIC 9                      #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Init element-givaro-prime tools
    eltType::setField(F);
    
    // Number of generator
    int nbGen;
    
    // Init monomial tools
    Monomial::initMonomial(9);
    
    // Create polynomial array
    vector<Polynomial<eltType>> polCyclic9;
    
    // Fill the polynomial array
    polCyclic9.emplace_back("x0+x1+x2+x3+x4+x5+x6+x7+x8");
    polCyclic9.emplace_back("x0*x1+x1*x2+x2*x3+x3*x4+x4*x5+x5*x6+x6*x7+x0*x8+x7*x8");
    polCyclic9.emplace_back("x0*x1*x2+x1*x2*x3+x2*x3*x4+x3*x4*x5+x4*x5*x6+x5*x6*x7+x0*x1*x8+x0*x7*x8+x6*x7*x8");
    polCyclic9.emplace_back("x0*x1*x2*x3+x1*x2*x3*x4+x2*x3*x4*x5+x3*x4*x5*x6+x4*x5*x6*x7+x0*x1*x2*x8+x0*x1*x7*x8+x0*x6*x7*x8+x5*x6*x7*x8");
    polCyclic9.emplace_back("x0*x1*x2*x3*x4+x1*x2*x3*x4*x5+x2*x3*x4*x5*x6+x3*x4*x5*x6*x7+x0*x1*x2*x3*x8+x0*x1*x2*x7*x8+x0*x1*x6*x7*x8+x0*x5*x6*x7*x8+x4*x5*x6*x7*x8");
    polCyclic9.emplace_back("x0*x1*x2*x3*x4*x5+x1*x2*x3*x4*x5*x6+x2*x3*x4*x5*x6*x7+x0*x1*x2*x3*x4*x8+x0*x1*x2*x3*x7*x8+x0*x1*x2*x6*x7*x8+x0*x1*x5*x6*x7*x8+x0*x4*x5*x6*x7*x8+x3*x4*x5*x6*x7*x8");
    polCyclic9.emplace_back("x0*x1*x2*x3*x4*x5*x6+x1*x2*x3*x4*x5*x6*x7+x0*x1*x2*x3*x4*x5*x8+x0*x1*x2*x3*x4*x7*x8+x0*x1*x2*x3*x6*x7*x8+x0*x1*x2*x5*x6*x7*x8+x0*x1*x4*x5*x6*x7*x8+x0*x3*x4*x5*x6*x7*x8+x2*x3*x4*x5*x6*x7*x8");
    polCyclic9.emplace_back("x0*x1*x2*x3*x4*x5*x6*x7+x0*x1*x2*x3*x4*x5*x6*x8+x0*x1*x2*x3*x4*x5*x7*x8+x0*x1*x2*x3*x4*x6*x7*x8+x0*x1*x2*x3*x5*x6*x7*x8+x0*x1*x2*x4*x5*x6*x7*x8+x0*x1*x3*x4*x5*x6*x7*x8+x0*x2*x3*x4*x5*x6*x7*x8+x1*x2*x3*x4*x5*x6*x7*x8");
    polCyclic9.emplace_back("x0*x1*x2*x3*x4*x5*x6*x7*x8-1");

    // Create cyclic9 ideal;
    Ideal<eltType> cyclic9(polCyclic9, 9, 20000000);
    
    // Compute a reduced groebner basis;
    nbGen=cyclic9.f4();
    
    // Print the reduced groebner basis into a file
    if(magma)
    {
        cyclic9.printReducedGroebnerBasis("cyclic9", modulo);
    }
    
    return nbGen;
}

int katsura9F4(bool magma)
{
    cout << "#########################################################" << endl;
    cout << "#                         KATSURA 9                     #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Init element-givaro-prime tools
    eltType::setField(F);
    
    // Number of generator
    int nbGen;
    
    // Init monomial tools
    Monomial::initMonomial(9);
    
    // Create polynomial array
    vector<Polynomial<eltType>> polKatsura9;
    
    // Fill the polynomial array
    polKatsura9.emplace_back("x0+2*x1+2*x2+2*x3+2*x4+2*x5+2*x6+2*x7+2*x8-1");
    polKatsura9.emplace_back("x0^2+2*x1^2+2*x2^2+2*x3^2+2*x4^2+2*x5^2+2*x6^2+2*x7^2+2*x8^2-x0");
    polKatsura9.emplace_back("2*x0*x1+2*x1*x2+2*x2*x3+2*x3*x4+2*x4*x5+2*x5*x6+2*x6*x7+2*x7*x8-x1");
    polKatsura9.emplace_back("x1^2+2*x0*x2+2*x1*x3+2*x2*x4+2*x3*x5+2*x4*x6+2*x5*x7+2*x6*x8-x2");
    polKatsura9.emplace_back("2*x1*x2+2*x0*x3+2*x1*x4+2*x2*x5+2*x3*x6+2*x4*x7+2*x5*x8-x3");
    polKatsura9.emplace_back("x2^2+2*x1*x3+2*x0*x4+2*x1*x5+2*x2*x6+2*x3*x7+2*x4*x8-x4");
    polKatsura9.emplace_back("2*x2*x3+2*x1*x4+2*x0*x5+2*x1*x6+2*x2*x7+2*x3*x8-x5");
    polKatsura9.emplace_back("x3^2+2*x2*x4+2*x1*x5+2*x0*x6+2*x1*x7+2*x2*x8-x6");
    polKatsura9.emplace_back("2*x3*x4+2*x2*x5+2*x1*x6+2*x0*x7+2*x1*x8-x7");

    // Create katsura9 ideal;
    Ideal<eltType> katsura9(polKatsura9, 9 ,1000000);
    
    // Compute a reduced groebner basis;
    nbGen=katsura9.f4();
    
    // Print the reduced groebner basis into a file
    if(magma)
    {
        katsura9.printReducedGroebnerBasis("katsura9", modulo);
    }
    
    return nbGen;
}

int katsura10F4(bool magma)
{
    cout << "#########################################################" << endl;
    cout << "#                         KATSURA 10                    #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Init element-givaro-prime tools
    eltType::setField(F);
    
    // Number of generator
    int nbGen;
    
    // Init monomial tools
    Monomial::initMonomial(10);
    
    // Create polynomial array
    vector<Polynomial<eltType>> polKatsura10;
    
    // Fill the polynomial array
    polKatsura10.emplace_back("x0+2*x1+2*x2+2*x3+2*x4+2*x5+2*x6+2*x7+2*x8+2*x9-1");
    polKatsura10.emplace_back("x0^2+2*x1^2+2*x2^2+2*x3^2+2*x4^2+2*x5^2+2*x6^2+2*x7^2+2*x8^2+2*x9^2-x0");
    polKatsura10.emplace_back("2*x0*x1+2*x1*x2+2*x2*x3+2*x3*x4+2*x4*x5+2*x5*x6+2*x6*x7+2*x7*x8+2*x8*x9-x1");
    polKatsura10.emplace_back("x1^2+2*x0*x2+2*x1*x3+2*x2*x4+2*x3*x5+2*x4*x6+2*x5*x7+2*x6*x8+2*x7*x9-x2");
    polKatsura10.emplace_back("2*x1*x2+2*x0*x3+2*x1*x4+2*x2*x5+2*x3*x6+2*x4*x7+2*x5*x8+2*x6*x9-x3");
    polKatsura10.emplace_back("x2^2+2*x1*x3+2*x0*x4+2*x1*x5+2*x2*x6+2*x3*x7+2*x4*x8+2*x5*x9-x4");
    polKatsura10.emplace_back("2*x2*x3+2*x1*x4+2*x0*x5+2*x1*x6+2*x2*x7+2*x3*x8+2*x4*x9-x5");
    polKatsura10.emplace_back("x3^2+2*x2*x4+2*x1*x5+2*x0*x6+2*x1*x7+2*x2*x8+2*x3*x9-x6");
    polKatsura10.emplace_back("2*x3*x4+2*x2*x5+2*x1*x6+2*x0*x7+2*x1*x8+2*x2*x9-x7");
    polKatsura10.emplace_back("x4^2+2*x3*x5+2*x2*x6+2*x1*x7+2*x0*x8+2*x1*x9-x8");

    // Create katsura10 ideal;
    Ideal<eltType> katsura10(polKatsura10, 10, 10000000);
    
    // Compute a reduced groebner basis;
    nbGen=katsura10.f4();
    
    // Print the reduced groebner basis into a file
    if(magma)
    {
        katsura10.printReducedGroebnerBasis("katsura10", modulo);
    }
    return nbGen;
}

int katsura11F4(bool magma)
{
    cout << "#########################################################" << endl;
    cout << "#                         KATSURA 11                    #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Init element-givaro-prime tools
    eltType::setField(F);
    
    // Number of generator
    int nbGen;
    
    // Init monomial tools
    Monomial::initMonomial(11);
    
    // Create polynomial array
    vector<Polynomial<eltType>> polKatsura11;
    
    // Fill the polynomial array
    polKatsura11.emplace_back("x0+2*x1+2*x2+2*x3+2*x4+2*x5+2*x6+2*x7+2*x8+2*x9+2*x10-1");
    polKatsura11.emplace_back("x0^2+2*x1^2+2*x2^2+2*x3^2+2*x4^2+2*x5^2+2*x6^2+2*x7^2+2*x8^2+2*x9^2+2*x10^2-x0");
    polKatsura11.emplace_back("2*x0*x1+2*x1*x2+2*x2*x3+2*x3*x4+2*x4*x5+2*x5*x6+2*x6*x7+2*x7*x8+2*x8*x9+2*x9*x10-x1");
    polKatsura11.emplace_back("x1^2+2*x0*x2+2*x1*x3+2*x2*x4+2*x3*x5+2*x4*x6+2*x5*x7+2*x6*x8+2*x7*x9+2*x8*x10-x2");
    polKatsura11.emplace_back("2*x1*x2+2*x0*x3+2*x1*x4+2*x2*x5+2*x3*x6+2*x4*x7+2*x5*x8+2*x6*x9+2*x7*x10-x3");
    polKatsura11.emplace_back("x2^2+2*x1*x3+2*x0*x4+2*x1*x5+2*x2*x6+2*x3*x7+2*x4*x8+2*x5*x9+2*x6*x10-x4");
    polKatsura11.emplace_back("2*x2*x3+2*x1*x4+2*x0*x5+2*x1*x6+2*x2*x7+2*x3*x8+2*x4*x9+2*x5*x10-x5");
    polKatsura11.emplace_back("x3^2+2*x2*x4+2*x1*x5+2*x0*x6+2*x1*x7+2*x2*x8+2*x3*x9+2*x4*x10-x6");
    polKatsura11.emplace_back("2*x3*x4+2*x2*x5+2*x1*x6+2*x0*x7+2*x1*x8+2*x2*x9+2*x3*x10-x7");
    polKatsura11.emplace_back("x4^2+2*x3*x5+2*x2*x6+2*x1*x7+2*x0*x8+2*x1*x9+2*x2*x10-x8");
    polKatsura11.emplace_back("2*x4*x5+2*x3*x6+2*x2*x7+2*x1*x8+2*x0*x9+2*x1*x10-x9");

    // Create katsura11 ideal;
    Ideal<eltType> katsura11(polKatsura11, 11, 10000000);
    
    // Compute a reduced groebner basis;
    nbGen=katsura11.f4();
    
    // Print the reduced groebner basis into a file
    if(magma)
    {
        katsura11.printReducedGroebnerBasis("katsura11", modulo);
    }
    return nbGen;
}

int katsura12F4(bool magma)
{
    cout << "#########################################################" << endl;
    cout << "#                         KATSURA 12                    #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Init element-givaro-prime tools
    eltType::setField(F);
    
    // Number of generator
    int nbGen;
    
    // Init monomial tools
    Monomial::initMonomial(12);
    
    // Create polynomial array
    vector<Polynomial<eltType>> polKatsura12;
    
    // Fill the polynomial array
    polKatsura12.emplace_back("x0+2*x1+2*x2+2*x3+2*x4+2*x5+2*x6+2*x7+2*x8+2*x9+2*x10+2*x11-1");
    polKatsura12.emplace_back("x0^2+2*x1^2+2*x2^2+2*x3^2+2*x4^2+2*x5^2+2*x6^2+2*x7^2+2*x8^2+2*x9^2+2*x10^2+2*x11^2-x0");
    polKatsura12.emplace_back("2*x0*x1+2*x1*x2+2*x2*x3+2*x3*x4+2*x4*x5+2*x5*x6+2*x6*x7+2*x7*x8+2*x8*x9+2*x9*x10+2*x10*x11-x1");
    polKatsura12.emplace_back("x1^2+2*x0*x2+2*x1*x3+2*x2*x4+2*x3*x5+2*x4*x6+2*x5*x7+2*x6*x8+2*x7*x9+2*x8*x10+2*x9*x11-x2");
    polKatsura12.emplace_back("2*x1*x2+2*x0*x3+2*x1*x4+2*x2*x5+2*x3*x6+2*x4*x7+2*x5*x8+2*x6*x9+2*x7*x10+2*x8*x11-x3");
    polKatsura12.emplace_back("x2^2+2*x1*x3+2*x0*x4+2*x1*x5+2*x2*x6+2*x3*x7+2*x4*x8+2*x5*x9+2*x6*x10+2*x7*x11-x4");
    polKatsura12.emplace_back("2*x2*x3+2*x1*x4+2*x0*x5+2*x1*x6+2*x2*x7+2*x3*x8+2*x4*x9+2*x5*x10+2*x6*x11-x5");
    polKatsura12.emplace_back("x3^2+2*x2*x4+2*x1*x5+2*x0*x6+2*x1*x7+2*x2*x8+2*x3*x9+2*x4*x10+2*x5*x11-x6");
    polKatsura12.emplace_back("2*x3*x4+2*x2*x5+2*x1*x6+2*x0*x7+2*x1*x8+2*x2*x9+2*x3*x10+2*x4*x11-x7");
    polKatsura12.emplace_back("x4^2+2*x3*x5+2*x2*x6+2*x1*x7+2*x0*x8+2*x1*x9+2*x2*x10+2*x3*x11-x8");
    polKatsura12.emplace_back("2*x4*x5+2*x3*x6+2*x2*x7+2*x1*x8+2*x0*x9+2*x1*x10+2*x2*x11-x9");
    polKatsura12.emplace_back("x5^2+2*x4*x6+2*x3*x7+2*x2*x8+2*x1*x9+2*x0*x10+2*x1*x11-x10");

    // Create katsura12 ideal;
    Ideal<eltType> katsura12(polKatsura12, 12, 20000000);
    
    // Compute a reduced groebner basis;
    nbGen=katsura12.f4();
    
    // Print the reduced groebner basis into a file
    if(magma)
    {
        katsura12.printReducedGroebnerBasis("katsura12", modulo);
    }
    
    return nbGen;
}

int randomIdealF4(bool magma)
{
    cout << "#########################################################" << endl;
    cout << "#                          RANDOM 10                    #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Init element-givaro-prime tools
    eltType::setField(F);
    
    // Number of generator
    int nbGen;
    
    // Init monomial tools
    Monomial::initMonomial(6);
    
    // Create polynomial array
    vector<Polynomial<eltType>> polRandomIdeal;
    
    // Fill the polynomial array
    polRandomIdeal.emplace_back("24597339625910113576177812194822250879537888983662139157054688348207021034423*x0*x2^3*x3 + 7151588983918886554522549736197912065523665823784056349692045272366005788565*x0^2*x2*x3^2 + 95599032154676572226640446287059550522243931209485035728481004109380836179795*x0*x1^2*x3*x4 + 80882266569802612115142178105069880712235080346583360326358277892681539845732*x0^3*x3*x5 + 101864944527580784908102973651636073902143046328060199850906610091806947685022*x0*x3^2*x4*x5 + 104729712827144379217380985817333309181450988946645646697114354205618456582492*x0^2*x4*x5^2 + 52302434696683789707660417227753471409142053519740797962753625864564463811375*x1^2*x5^3 + 17351950912516853579762997039599589425266549548666687814496665086694694159586*x0*x1^2*x3 + 57227991936024998238525433049119252484044400932298334640398545161720853774944*x2*x3*x4^2 + 38511682104007724413948279389864784831862930925142964452301117791670531282410*x4");
    polRandomIdeal.emplace_back("86346388292488249693869354105874299384790680682194436292372522278549507768591*x3^2*x4^3 + 8560263876613706064403723240653698444937439375423776730755015899158932842647*x1^2*x3^2*x5 + 114724691048080175315386081552620657520918558817449626896120724453969617140460*x2^2*x3*x4*x5 + 40878117764229528421408904940423898833248553959986663655083414549083339596552*x0*x1*x4^2*x5 + 29331944903965444678929349681346850658980582826770917817437252786162390253711*x2*x4^3*x5 + 87607904220986147695088733307722614252715606105143772697170967808308305165752*x0*x1*x5^3 + 65596215877552473724063874933319504303306707295349647359211407346928426648221*x2*x3*x5^3 + 56669973593023066605257462537515724309040997310759397676506125179995947207805*x1*x2*x3^2 + 89782880725008317979230645836251624558567904255006493194084628222595510888312*x1^2*x5^2 + 103674841782615880557579059147217301083806806039093159135639389165583018130578*x3^2");
    polRandomIdeal.emplace_back("20555372959538263695300487972318050811409584461989901476892596135795399007972*x0*x2^3*x4 + 5934883841580475383464077425056051853720558922314186953741822652041312229861*x0*x1^2*x4^2 + 17710328902511891669230229596735065270173524867878787745829992603487297107510*x2^2*x3*x4^2 + 70404710174534786665778251066204965060179971987897435343713576428374740408256*x0*x4^4 + 58426575736174100224339841770010585175567236430388827167224449807299941566077*x0*x2*x3^2*x5 + 30924715140590657501911767836863937316255060662617400020818103627533478901229*x0^3*x5^2 + 39500461401725546193800195222441711243433837945025353320818490293478989705375*x1^2*x2*x3 + 64240298741364943418471687622389504568349868475893951422615715204540247474855*x0*x4^2*x5 + 65820732534870169140028008687678098817567316157097444187709680681916368484914*x4*x5^3 + 17272453016442962442302752791953060985176759042717911629687645606592891860888*x4*x5");
    polRandomIdeal.emplace_back("12384393892417675961175644242218445795611270141536380862841430355542048945085*x1^4*x3 + 62117470929065963636773146246593970394763704726641029743988220795495717410803*x1^3*x3^2 + 85619266736706628749218187296710103779188326378690946812602186116779762130986*x1*x2^2*x3^2 + 78777699432899971447463849098828646733245461242068819366140165453034019618264*x1*x2^2*x3*x4 + 60532401626170308029709934649599544595568150628715306147854909931133932052790*x0^2*x4^3 + 71822141816384506883608511920275736927595134162667327611607722341197820116110*x0*x2*x4^3 + 37098078751644219974002508996700695086621623357192113467047119767669799270965*x1^2*x2*x4*x5 + 63912960464413836237227794975572970151536793396077872846928677515156238102473*x3*x4^3 + 35312782757171746885185524802919703708611850096516153058825836129727838715106*x2*x4*x5 + 1343217275458213949398887747305351360705055910323149933135594844254487693698*x4*x5");
    polRandomIdeal.emplace_back("28381607648242478091145546569738942138490135373130646389457403625175172311248*x0^2*x1^3 + 97629891473294042452534075850587001679173377545311155140176153692564089928974*x0*x1^2*x2^2 + 26563855492181492863726541015290497720634690978340399702372536173601777578991*x1^2*x2^3 + 94418967799063888112199911973141289579879737901092393135865628433426320213508*x0*x2^3*x3 + 75904322816224886498948320053011705672627274171263473501967112349188186065915*x1^2*x2^2*x4 + 4211364562071041806690191029623605410137554183422577681706484078158419251640*x0^3*x3*x4 + 91613731288563016881346819513246567701509323051875994794659318808230283066460*x1^2*x3*x5^2 + 89803895793131901997696630423649455067510213320346896852691998335464227790294*x0^2*x4^2 + 75236829790691047060918314537432780193922926192907772789500111625658582524194*x0*x1*x4*x5 + 88214290422334784207736225415065448927133778554493575039918313349055750449376*x0*x4^2");
    polRandomIdeal.emplace_back("36819072232725910256455616092735238942832580357061287151935045000104711104411*x0^3*x1*x3 + 92291875768826133686313407982369359745050073458651281392130985753191759709555*x0*x1*x2*x3^2 + 101938393329103051382592541594609110833699156858188605831660754891793011921846*x0*x1*x3*x4*x5 + 78518394770627757449165376995944664714763318337121096642895914042049946334065*x0*x3^3 + 105540139497579157022475500477406241172092810961640031984154318748048515678792*x4^3*x5 + 84774161335942515317743013157128228128841107642095399345126979227940275346840*x1^2*x5 + 28913909478286876522946234334944523118995435566050167225895704836461177828945*x2*x5^2 + 106937289130333317810026636145567706868904407646348007959878422922013786734185*x0*x3 + 63666212440767596437341393306731648918103562050621587961742006659395222409375*x1*x3 + 83996307259878859577055366727974705831495419710797565080759747834770898783875*x5");
    polRandomIdeal.emplace_back("95136961029579226839637332012775663846115938875849099068708963080153370687870*x0^4*x1 + 76661948597477609517006426019266647328314089124644038885570980154181394767045*x0^2*x1*x2^2 + 27648974455310197157642464629672364390288189790420888726061791111455930492175*x0*x1^2*x4^2 + 99920868693778594352975463016494289879012074085347132032153078814030759868224*x2*x3^2*x4^2 + 114576007790549395302027460749852743178287491103989645103656698251762797956277*x0*x1*x2*x5^2 + 43153777207871533863124675741671309793892255338939927520368389402438237387200*x1^2*x2*x5^2 + 110318690252357714779958276568104661106261376891832416580120755279823049887113*x3*x4^2*x5^2 + 45799078731622712232945448991759430123294657671582099449044877222550442558738*x0*x2^2*x4 + 100277677872859926645680483411379280810471168956065420170667425387985565806433*x3^2*x4 + 68644070924152146278996255474255655652298183872273530921674643251905127029128*x4*x5");
    polRandomIdeal.emplace_back("87978767156577336556423273498613521678164709661646440569923905722446974932580*x0*x1^3*x2 + 70199507444825230647493402897761692537994351870483255214231224774601251297974*x0*x1*x4^3 + 10499470273219641798942672785992918744734361231209730859900373933910949161692*x2*x3^3*x5 + 10578305965849220536418224538586043663097136242388818907836369052306903906601*x0*x1*x4^2*x5 + 32249366203262097372573463349641203429995781989381112500573426781212335279118*x0*x1*x2*x3 + 68965782969450373459926970875762316518136291840379380514392013450011450721038*x0*x1*x3*x4 + 106629938451314744237236927474319652055736870796645986260679888340450464841026*x1^2*x4*x5 + 88351726336724052112084554771705971133037039282167216023462500471200318288497*x0*x3*x5^2 + 84046176579642600973999519206384583444257671151834634463273585411955530393954*x0*x1*x4 + 2932552305743391062700434765772653160158777010296451457377134869842474189579*x0*x5");
    polRandomIdeal.emplace_back("96175621691556224386088482294073036284237851574485948577108659192463312510712*x0^2*x2^3 + 16095887211020898803806210526133834612853130933198816810948682148899139349600*x0^2*x3*x4^2 + 98747250666492396295286689772042224509297294109856664554352878419198232617521*x0*x3^3*x5 + 52569893992386578310288654986310745632795983936543823080780536063381889538173*x0*x1^2*x5^2 + 36070712509652751546201022316199583998607010198219874113379048155683684512939*x2*x3^3 + 38459960562537420353680404430137735268833402366364859536583425875504311849535*x4^3*x5 + 113265414726720472996579440938493403137255422517872281489764072963845855836208*x0*x2^2 + 33031201838571091233829098061859824402045327050874566178073169835546536449040*x1^2*x3 + 77060949484187104215934343083327162793888599177091130574481647315933319100248*x0*x3*x4 + 3155394989270135101201445442533082844433454102552047565792654883026176768937*x0*x1");
    polRandomIdeal.emplace_back("100307018005733281728228439480689303268611563644292865992483825902060219306155*x0^2*x2^3 + 105212694999612411994109856290944335059209993707016399450156734493741925982223*x0^2*x1*x3*x4 + 58140815460156743900993549079587138617713837063726348071633359223936496336099*x0*x1*x3^2*x4 + 8951532369766415191105325162452055460388676698962191148548481629695483289115*x1^2*x3*x4^2 + 69954737050315706014137404090624170387633458271507253876540354269572114628457*x0*x3^2*x5^2 + 21769110896144960056125376434972489426599777661038130833468146359769606682708*x2*x4^3 + 88454000542334193985275053321689469577999258427270074292622316785230589464978*x3*x4^3 + 23329368668390090437170212328783556103331009522530474701480630589364702028429*x1*x4*x5^2 + 14452449608795143101201599761577715436126915563168593823066496214782963561358*x2*x5^2 + 88082782885434895653280422218839066097313430921228053271593271806651074773006*x1");

    // Create katsura12 ideal;
    Ideal<eltType> randomIdeal(polRandomIdeal, 6);
    
    // Compute a reduced groebner basis;
    nbGen=randomIdeal.f4();
    
    // Print the reduced groebner basis into a file
    if(magma)
    {
        randomIdeal.printReducedGroebnerBasis("randomIdeal", modulo);
    }
    
    return nbGen;
}



int main (int argc, char **argv)
{
    cout << "#########################################################" << endl;
    cout << "#                     BENCHMARK GMP                     #" << endl;
    cout << "#########################################################" << endl << endl;

    // Time
    chrono::steady_clock::time_point start;
    typedef chrono::duration<int,milli> millisecs_t;
    
    // Number of threads
    cout << NB_THREAD << " threads used " << endl << endl;
    
    // Magma output
    bool magma = false;
    
    // Number of generator
    int nbGen;
    
    // File
    ofstream file("benchmark-big-integer.txt");
    if (file)
    {
        file << "Benchmark for ideal with integer type coefficient." << endl << endl << endl;
    }
    
    start=chrono::steady_clock::now();
    nbGen=randomIdealF4(magma);
    if (file)
    {
        file << "Random 10 : " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms                   (" << nbGen << " generators)" << endl << endl;
    }
    
    //start=chrono::steady_clock::now();
    //nbGen=cyclic6F4(magma);
    //if (file)
    //{
        //file << "Cyclic 6 : " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms                   (" << nbGen << " generators)" << endl << endl;
    //}
    
    //start=chrono::steady_clock::now();
    //nbGen=cyclic7F4(magma);
    //if (file)
    //{
        //file << "Cyclic 7 : " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms                   (" << nbGen << " generators)" << endl << endl;
    //}
    
    start=chrono::steady_clock::now();
    nbGen=cyclic8F4(magma);
    if (file)
    {
        file << "Cyclic 8 : " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms                   (" << nbGen << " generators)" << endl << endl;
    }
    
    //start=chrono::steady_clock::now();
    //nbGen=cyclic9F4(magma);
    //if (file)
    //{
        //file << "Cyclic 9 : " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms                   (" << nbGen << " generators)" << endl << endl;
    //}
    
    //start=chrono::steady_clock::now();
    //nbGen=katsura9F4(magma);
    //if (file)
    //{
        //file << "Katsura 9 : " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms                   (" << nbGen << " generators)" << endl << endl;
    //}
    
    //start=chrono::steady_clock::now();
    //nbGen=katsura10F4(magma);
    //if (file)
    //{
        //file << "Katsura 10 : " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms                   (" << nbGen << " generators)" << endl << endl;
    //}  
    
    //start=chrono::steady_clock::now();
    //nbGen=katsura11F4(magma);
    //if (file)
    //{
        //file << "Katsura 11 : " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms                   (" << nbGen << " generators)" << endl << endl;
    //}
    
    start=chrono::steady_clock::now();
    nbGen=katsura12F4(magma);
    if (file)
    {
        file << "Katsura 12 : " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms                   (" << nbGen << " generators)" << endl << endl;
    }
    
    return 0;
}


