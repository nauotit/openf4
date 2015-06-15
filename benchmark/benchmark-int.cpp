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
 *  \file benchmark-int.cpp
 *  \example benchmark-int.cpp
 *  \brief Benchmark with integer 32 bits coefficients.
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

// Init element-prime tools
typedef ElementPrime<int32_t> eltType;
int modulo=65521;

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
    polRandomIdeal.emplace_back("-25655*x1^2*x2^2*x4 - 27093*x0*x2*x3*x5^2 + 15696*x5^5 - 31611*x0*x1^3 + 10089*x0^3*x2 - 2759*x1^2*x3^2 + 3186*x1*x3^2*x4 - 7916*x1*x2^2*x5 + 16867*x1*x4^2*x5 - 26502*x2^2*x4");
    polRandomIdeal.emplace_back("24757*x2^4*x3 + 13532*x0*x1*x2*x3^2 - 32273*x2^2*x3^3 + 24976*x2*x3^4 + 6577*x0*x2^3*x5 - 14251*x1*x3^2*x4*x5 + 8633*x0*x3*x4^2 + 18508*x0*x4^3 + 12700*x1*x2*x5^2 + 21103*x1*x5");
    polRandomIdeal.emplace_back("-14089*x0^2*x2^3 + 6374*x0*x1^2*x3^2 - 11572*x2^3*x3^2 + 17253*x0^3*x1*x4 - 26476*x2*x3*x4^3 - 5794*x2*x4^3*x5 - 9292*x0^3*x1 + 9740*x0^3*x2 - 9633*x0^2*x5^2 + 15791*x4");
    polRandomIdeal.emplace_back("520*x0^2*x1*x3*x5 - 29475*x3^4*x5 + 19553*x1*x4^3*x5 - 23508*x0*x3^2*x5^2 - 5914*x0^2*x4*x5^2 - 1142*x0*x2*x4*x5 + 18000*x0*x2*x3 + 9342*x2*x3^2 + 8761*x0^2*x5 + 19293*x2*x5");
    polRandomIdeal.emplace_back("-29406*x0^4*x1 - 6933*x1*x2^4 - 16593*x1^2*x2*x3^2 - 12720*x1*x3^4 - 8580*x4*x5^4 - 17076*x1^2*x3*x4 + 24339*x0*x2*x3*x4 + 7722*x1*x3*x4^2 - 14196*x1*x2*x3 - 15797*x1^2*x5");
    polRandomIdeal.emplace_back("31060*x0^3*x1*x2 - 6848*x2*x3^3*x5 - 17952*x1*x3*x4^2*x5 + 24428*x0*x2*x3*x5^2 + 20435*x0^4 - 20926*x1^2*x2*x3 + 18778*x2^2*x3^2 + 24106*x2*x4^3 - 11252*x5^4 - 20128*x2*x3");
    polRandomIdeal.emplace_back("2175*x0^3*x4^2 + 24248*x0^2*x3*x4*x5 - 25078*x0*x2*x3*x4*x5 + 17127*x0*x3^2*x4*x5 + 16204*x3^2*x4*x5^2 + 3683*x0*x1*x2*x3 + 14115*x1*x4^2*x5 - 32337*x0^2*x1 - 17348*x1^2*x5 + 3481*x1*x4");
    polRandomIdeal.emplace_back("-10922*x2^3*x3^2 + 11055*x2^2*x3^3 - 24940*x2^2*x3*x5^2 - 2405*x2*x5^4 - 26339*x1*x2*x3^2 - 4489*x0*x3^2*x5 + 2022*x1*x3*x4*x5 + 6254*x3*x4^2*x5 + 19234*x1^2*x3 + 28792*x2*x4*x5");
    polRandomIdeal.emplace_back("-30691*x0^2*x2*x3^2 + 6407*x0*x2*x4^3 + 30127*x1*x4^4 + 20623*x2*x3*x4^2*x5 + 14919*x0*x3^2*x5^2 + 11410*x1^2*x4^2 + 11040*x0*x2*x4^2 - 23568*x4*x5^3 + 12549*x1^2*x3 - 19452*x2^2*x3");
    polRandomIdeal.emplace_back("-21749*x0^3*x1^2 + 31426*x2^3*x4^2 + 24770*x3^2*x4^3 - 8527*x0^3*x1*x5 - 24637*x0^2*x1*x3*x5 - 12368*x0*x1*x2*x3*x5 + 12346*x1*x2^2*x3*x5 - 27520*x0*x5^4 - 8249*x1^2*x3*x4 - 4866*x0*x2*x3*x4");
    
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

int randomIdealExampleF4(bool magma)
{
    cout << "#########################################################" << endl;
    cout << "#                          RANDOM 4                    #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Init element-prime tools
    eltType::setModulo(11);
    
    // Number of generator
    int nbGen;
    
    // Init monomial tools
    Monomial::initMonomial(4);
    
    // Create polynomial array
    vector<Polynomial<eltType>> polRandomIdeal;
    
    // Fill the polynomial array
    polRandomIdeal.emplace_back("x1+2*x2+3*x3");
    polRandomIdeal.emplace_back("4*x0+5*x1+6*x2+7*x3");
    polRandomIdeal.emplace_back("8*x0*x1+9*x1*x2+10*x2*x3");


    // Create katsura12 ideal;
    Ideal<eltType> randomIdeal(polRandomIdeal, 4);
    
    // Compute a reduced groebner basis;
    nbGen=randomIdeal.f4();
    
    // Print the reduced groebner basis into a file
    if(magma)
    {
        randomIdeal.printReducedGroebnerBasis("randomIdeal4", modulo);
    }
    
    randomIdeal.printReducedGroebnerBasis(true);
    
    return nbGen;
}

int main (int argc, char **argv)
{
    cout << "#########################################################" << endl;
    cout << "#                     BENCHMARK INT                     #" << endl;
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
    ofstream file("benchmark-int.txt");
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
    //nbGen=randomIdealExampleF4(magma);
    //if (file)
    //{
        //file << "Random example : " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms                   (" << nbGen << " generators)" << endl << endl;
    //}
    
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


