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
 *  \file benchmark-short.cpp
 *  \example benchmark-short.cpp
 *  \brief Benchmark with integer 16 bits coefficients.
 *  \ingroup benchmark
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include <openf4.h>

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=0;
#ifdef USE_OPENMP
int F4::NB_THREAD=min(8, omp_get_num_procs());
#else
int F4::NB_THREAD=1;
#endif

// Init element-prime tools
typedef ElementPrime<int16_t> eltType;
int modulo=251;

int cyclic6F4(bool magma)
{
    cout << "#########################################################" << endl;
    cout << "#                         CYCLIC 6                      #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Init element-prime tools
    eltType::setModulo(modulo);
    
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
    
    // Init element-prime tools
    eltType::setModulo(modulo);
    
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
    
    // Init element-prime tools
    eltType::setModulo(modulo);
    
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
    
    // Init element-prime tools
    eltType::setModulo(modulo);
    
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
    
    // Init element-prime tools
    eltType::setModulo(modulo);
    
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
    
    // Init element-prime tools
    eltType::setModulo(modulo);
    
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
    
    // Init element-prime tools
    eltType::setModulo(modulo);
    
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
    
    // Init element-prime tools
    eltType::setModulo(modulo);
    
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
    
    // Init element-prime tools
    eltType::setModulo(modulo);
    
    // Number of generator
    int nbGen;
    
    // Init monomial tools
    Monomial::initMonomial(6);
    
    // Create polynomial array
    vector<Polynomial<eltType>> polRandomIdeal;
    
    // Fill the polynomial array
    polRandomIdeal.emplace_back("-60*x0^3*x1^2 - 100*x2^4*x3 + 100*x0^2*x3^2*x4 - 88*x1*x3^2*x4^2 - 115*x1*x2*x3*x5^2 - 17*x2*x3*x4*x5^2 - 55*x4^4 - 36*x1*x3^2*x5 - 59*x2*x3^2*x5 - 78*x1*x2*x4");
    polRandomIdeal.emplace_back("54*x1^2*x2^3 + 61*x3^5 + 18*x1^3*x3*x4 + 69*x1*x3^3*x4 + 17*x0^2*x2*x4^2 + 49*x0*x1*x3*x4*x5 + 18*x2*x3*x5^3 - 90*x0*x1*x3^2 - 65*x0 - 44*x3");
    polRandomIdeal.emplace_back("-29*x0*x2^2*x3*x4 + 48*x0*x2*x3*x4^2 + 109*x0*x3*x4^2*x5 - 85*x0*x1*x3*x5^2 - 86*x0*x3^2*x4 + 95*x1^2*x4^2 + 109*x1^2*x2*x5 + 26*x0^2*x5 + 110*x0^2 + 103*x1^2");
    polRandomIdeal.emplace_back("-6*x2^3*x3^2 + 13*x0*x1*x2*x3*x4 - 45*x2^3*x3*x4 + 99*x1^2*x2^2*x5 - 57*x0^3*x4*x5 + 31*x0^2*x2*x4*x5 + 55*x0*x2^2*x5^2 + 114*x0^2*x2*x5 - 46*x2^2*x5 + 83*x2*x5^2");
    polRandomIdeal.emplace_back("-101*x0*x1^4 - 9*x1^2*x2^2*x3 + x4^5 + 75*x2*x4*x5^3 - 3*x0^2*x1*x2 - 104*x0*x1*x3*x4 - 68*x0*x2*x3*x4 - 64*x1^2*x3 - 54*x5^2");
    polRandomIdeal.emplace_back("-105*x0^2*x4^3 + 83*x1^2*x3^2*x5 + 48*x2*x3^3*x5 + 23*x1*x4^3*x5 - 82*x0*x1*x5^3 - 77*x2^2*x4*x5 + 84*x1*x2*x5^2 - 14*x0^2*x2 + 75*x3^2*x4 - 91*x1*x5^2");
    polRandomIdeal.emplace_back("-59*x0*x1^2*x2^2 - 62*x0*x1*x2^2*x3 - 104*x0*x1*x3*x4*x5 + 65*x0*x1*x2^2 - 95*x0^2*x3^2 - 60*x1^2*x4^2 - 6*x2*x4^3 + 119*x1*x3*x5^2 + 67*x2^3 - 52*x2*x5^2");
    polRandomIdeal.emplace_back("32*x2^2*x3^3 - 70*x0*x1^2*x4^2 + 88*x0^4*x5 + 39*x0*x1*x3^2*x5 + 57*x1*x2*x3*x5^2 + 117*x1*x4^2*x5^2 - 105*x0*x1*x2^2 + 69*x1*x2*x5^2 - 119*x0*x5^3 + 86*x0*x1*x3");
    polRandomIdeal.emplace_back("65*x1^3*x3^2 - 114*x0^2*x1*x2*x4 - 69*x0*x3^3*x4 - 84*x1^2*x4^3 + 43*x1^3*x4*x5 - 120*x1^3*x5^2 + 58*x0*x1^2*x3 - 61*x1*x2^2*x3 - 76*x1*x2^2*x4 - 46*x2*x3^2*x5");
    polRandomIdeal.emplace_back("43*x1^4*x3 + 35*x2*x3*x4*x5^2 + 85*x0*x4*x5^3 + 48*x1*x2^2*x3 - 2*x1*x2*x3^2 - 52*x1^2*x3*x4 - 30*x1^2*x3*x5 + 11*x0*x3^2*x5 + 34*x0*x2*x4 - 3*x1*x3*x4");

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
    cout << "#                     BENCHMARK SHORT                   #" << endl;
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
    ofstream file("benchmark-short.txt");
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


