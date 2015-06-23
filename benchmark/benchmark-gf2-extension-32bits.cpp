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
 *  \file benchmark-gf2-extension-32bits.cpp
 *  \example benchmark-gf2-extension-32bits.cpp
 *  \brief Benchmark with coefficients in GF(2^n).
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
typedef ElementGF2Extension<uint32_t> eltType;
uint32_t modulo=0x80000009;


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
    polCyclic6.emplace_back("(t+t^3)*x0+(t+t^3)*x1+(t+t^3)*x2+(t+t^3)*x3+(t+t^3)*x4+(t+t^3)*x5");
    polCyclic6.emplace_back("(t+t^3)*x0*x1+(t+t^3)*x1*x2+(t+t^3)*x2*x3+(t+t^3)*x3*x4+(t+t^3)*x0*x5+(t+t^3)*x4*x5");
    polCyclic6.emplace_back("(t+t^3)*x0*x1*x2+(t+t^3)*x1*x2*x3+(t+t^3)*x2*x3*x4+(t+t^3)*x0*x1*x5+(t+t^3)*x0*x4*x5+(t+t^3)*x3*x4*x5");
    polCyclic6.emplace_back("(t+t^3)*x0*x1*x2*x3+(t+t^3)*x1*x2*x3*x4+(t+t^3)*x0*x1*x2*x5+(t+t^3)*x0*x1*x4*x5+(t+t^3)*x0*x3*x4*x5+(t+t^3)*x2*x3*x4*x5");
    polCyclic6.emplace_back("(t+t^3)*x0*x1*x2*x3*x4+(t+t^3)*x0*x1*x2*x3*x5+(t+t^3)*x0*x1*x2*x4*x5+(t+t^3)*x0*x1*x3*x4*x5+(t+t^3)*x0*x2*x3*x4*x5+(t+t^3)*x1*x2*x3*x4*x5");
    polCyclic6.emplace_back("(t+t^3)*x0*x1*x2*x3*x4*x5-1");

    // Create cyclic6 ideal;
    Ideal<eltType> cyclic6(polCyclic6, 6, 100000);
    
    // Compute a reduced groebner basis;
    nbGen=cyclic6.f4();
    
    // Print the reduced groebner basis into a file
    if(magma)
    {
        cyclic6.printReducedGroebnerBasis("cyclic6", eltType::getModulo());
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
    polCyclic7.emplace_back("(t+t^3)*x0+(t+t^3)*x1+(t+t^3)*x2+(t+t^3)*x3+(t+t^3)*x4+(t+t^3)*x5+(t+t^3)*x6");
    polCyclic7.emplace_back("(t+t^3)*x0*x1+(t+t^3)*x1*x2+(t+t^3)*x2*x3+(t+t^3)*x3*x4+(t+t^3)*x4*x5+(t+t^3)*x0*x6+(t+t^3)*x5*x6");
    polCyclic7.emplace_back("(t+t^3)*x0*x1*x2+(t+t^3)*x1*x2*x3+(t+t^3)*x2*x3*x4+(t+t^3)*x3*x4*x5+(t+t^3)*x0*x1*x6+(t+t^3)*x0*x5*x6+(t+t^3)*x4*x5*x6");
    polCyclic7.emplace_back("(t+t^3)*x0*x1*x2*x3+(t+t^3)*x1*x2*x3*x4+(t+t^3)*x2*x3*x4*x5+(t+t^3)*x0*x1*x2*x6+(t+t^3)*x0*x1*x5*x6+(t+t^3)*x0*x4*x5*x6+(t+t^3)*x3*x4*x5*x6");
    polCyclic7.emplace_back("(t+t^3)*x0*x1*x2*x3*x4+(t+t^3)*x1*x2*x3*x4*x5+(t+t^3)*x0*x1*x2*x3*x6+(t+t^3)*x0*x1*x2*x5*x6+(t+t^3)*x0*x1*x4*x5*x6+(t+t^3)*x0*x3*x4*x5*x6+(t+t^3)*x2*x3*x4*x5*x6");
    polCyclic7.emplace_back("(t+t^3)*x0*x1*x2*x3*x4*x5+(t+t^3)*x0*x1*x2*x3*x4*x6+(t+t^3)*x0*x1*x2*x3*x5*x6+(t+t^3)*x0*x1*x2*x4*x5*x6+(t+t^3)*x0*x1*x3*x4*x5*x6+(t+t^3)*x0*x2*x3*x4*x5*x6+(t+t^3)*x1*x2*x3*x4*x5*x6");
    polCyclic7.emplace_back("(t+t^3)*x0*x1*x2*x3*x4*x5*x6-1");

    // Create cyclic7 ideal;
    Ideal<eltType> cyclic7(polCyclic7, 7 , 1000000);
    
    // Compute a reduced groebner basis;
    nbGen=cyclic7.f4();
    
    // Print the reduced groebner basis into a file
    if(magma)
    {
        cyclic7.printReducedGroebnerBasis("cyclic7", eltType::getModulo());
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
    polCyclic8.emplace_back("(t+t^3)*x0+(t+t^3)*x1+(t+t^3)*x2+(t+t^3)*x3+(t+t^3)*x4+(t+t^3)*x5+(t+t^3)*x6+(t+t^3)*x7");
    polCyclic8.emplace_back("(t+t^3)*x0*x1+(t+t^3)*x1*x2+(t+t^3)*x2*x3+(t+t^3)*x3*x4+(t+t^3)*x4*x5+(t+t^3)*x5*x6+(t+t^3)*x0*x7+(t+t^3)*x6*x7");
    polCyclic8.emplace_back("(t+t^3)*x0*x1*x2+(t+t^3)*x1*x2*x3+(t+t^3)*x2*x3*x4+(t+t^3)*x3*x4*x5+(t+t^3)*x4*x5*x6+(t+t^3)*x0*x1*x7+(t+t^3)*x0*x6*x7+(t+t^3)*x5*x6*x7");
    polCyclic8.emplace_back("(t+t^3)*x0*x1*x2*x3+(t+t^3)*x1*x2*x3*x4+(t+t^3)*x2*x3*x4*x5+(t+t^3)*x3*x4*x5*x6+(t+t^3)*x0*x1*x2*x7+(t+t^3)*x0*x1*x6*x7+(t+t^3)*x0*x5*x6*x7+(t+t^3)*x4*x5*x6*x7");
    polCyclic8.emplace_back("(t+t^3)*x0*x1*x2*x3*x4+(t+t^3)*x1*x2*x3*x4*x5+(t+t^3)*x2*x3*x4*x5*x6+(t+t^3)*x0*x1*x2*x3*x7+(t+t^3)*x0*x1*x2*x6*x7+(t+t^3)*x0*x1*x5*x6*x7+(t+t^3)*x0*x4*x5*x6*x7+(t+t^3)*x3*x4*x5*x6*x7");
    polCyclic8.emplace_back("(t+t^3)*x0*x1*x2*x3*x4*x5+(t+t^3)*x1*x2*x3*x4*x5*x6+(t+t^3)*x0*x1*x2*x3*x4*x7+(t+t^3)*x0*x1*x2*x3*x6*x7+(t+t^3)*x0*x1*x2*x5*x6*x7+(t+t^3)*x0*x1*x4*x5*x6*x7+(t+t^3)*x0*x3*x4*x5*x6*x7+(t+t^3)*x2*x3*x4*x5*x6*x7");
    polCyclic8.emplace_back("(t+t^3)*x0*x1*x2*x3*x4*x5*x6+(t+t^3)*x0*x1*x2*x3*x4*x5*x7+(t+t^3)*x0*x1*x2*x3*x4*x6*x7+(t+t^3)*x0*x1*x2*x3*x5*x6*x7+(t+t^3)*x0*x1*x2*x4*x5*x6*x7+(t+t^3)*x0*x1*x3*x4*x5*x6*x7+(t+t^3)*x0*x2*x3*x4*x5*x6*x7+(t+t^3)*x1*x2*x3*x4*x5*x6*x7");
    polCyclic8.emplace_back("(t+t^3)*x0*x1*x2*x3*x4*x5*x6*x7-1");

    // Create cyclic8 ideal;
    Ideal<eltType> cyclic8(polCyclic8, 8, 1000000);
    
    // Compute a reduced groebner basis;
    nbGen=cyclic8.f4();
    
    // Print the reduced groebner basis into a file
    if(magma)
    {
        cyclic8.printReducedGroebnerBasis("cyclic8", eltType::getModulo());
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
    polCyclic9.emplace_back("(t+t^3)*x0+(t+t^3)*x1+(t+t^3)*x2+(t+t^3)*x3+(t+t^3)*x4+(t+t^3)*x5+(t+t^3)*x6+(t+t^3)*x7+(t+t^3)*x8");
    polCyclic9.emplace_back("(t+t^3)*x0*x1+(t+t^3)*x1*x2+(t+t^3)*x2*x3+(t+t^3)*x3*x4+(t+t^3)*x4*x5+(t+t^3)*x5*x6+(t+t^3)*x6*x7+(t+t^3)*x0*x8+(t+t^3)*x7*x8");
    polCyclic9.emplace_back("(t+t^3)*x0*x1*x2+(t+t^3)*x1*x2*x3+(t+t^3)*x2*x3*x4+(t+t^3)*x3*x4*x5+(t+t^3)*x4*x5*x6+(t+t^3)*x5*x6*x7+(t+t^3)*x0*x1*x8+(t+t^3)*x0*x7*x8+(t+t^3)*x6*x7*x8");
    polCyclic9.emplace_back("(t+t^3)*x0*x1*x2*x3+(t+t^3)*x1*x2*x3*x4+(t+t^3)*x2*x3*x4*x5+(t+t^3)*x3*x4*x5*x6+(t+t^3)*x4*x5*x6*x7+(t+t^3)*x0*x1*x2*x8+(t+t^3)*x0*x1*x7*x8+(t+t^3)*x0*x6*x7*x8+(t+t^3)*x5*x6*x7*x8");
    polCyclic9.emplace_back("(t+t^3)*x0*x1*x2*x3*x4+(t+t^3)*x1*x2*x3*x4*x5+(t+t^3)*x2*x3*x4*x5*x6+(t+t^3)*x3*x4*x5*x6*x7+(t+t^3)*x0*x1*x2*x3*x8+(t+t^3)*x0*x1*x2*x7*x8+(t+t^3)*x0*x1*x6*x7*x8+(t+t^3)*x0*x5*x6*x7*x8+(t+t^3)*x4*x5*x6*x7*x8");
    polCyclic9.emplace_back("(t+t^3)*x0*x1*x2*x3*x4*x5+(t+t^3)*x1*x2*x3*x4*x5*x6+(t+t^3)*x2*x3*x4*x5*x6*x7+(t+t^3)*x0*x1*x2*x3*x4*x8+(t+t^3)*x0*x1*x2*x3*x7*x8+(t+t^3)*x0*x1*x2*x6*x7*x8+(t+t^3)*x0*x1*x5*x6*x7*x8+(t+t^3)*x0*x4*x5*x6*x7*x8+(t+t^3)*x3*x4*x5*x6*x7*x8");
    polCyclic9.emplace_back("(t+t^3)*x0*x1*x2*x3*x4*x5*x6+(t+t^3)*x1*x2*x3*x4*x5*x6*x7+(t+t^3)*x0*x1*x2*x3*x4*x5*x8+(t+t^3)*x0*x1*x2*x3*x4*x7*x8+(t+t^3)*x0*x1*x2*x3*x6*x7*x8+(t+t^3)*x0*x1*x2*x5*x6*x7*x8+(t+t^3)*x0*x1*x4*x5*x6*x7*x8+(t+t^3)*x0*x3*x4*x5*x6*x7*x8+(t+t^3)*x2*x3*x4*x5*x6*x7*x8");
    polCyclic9.emplace_back("(t+t^3)*x0*x1*x2*x3*x4*x5*x6*x7+(t+t^3)*x0*x1*x2*x3*x4*x5*x6*x8+(t+t^3)*x0*x1*x2*x3*x4*x5*x7*x8+(t+t^3)*x0*x1*x2*x3*x4*x6*x7*x8+(t+t^3)*x0*x1*x2*x3*x5*x6*x7*x8+(t+t^3)*x0*x1*x2*x4*x5*x6*x7*x8+(t+t^3)*x0*x1*x3*x4*x5*x6*x7*x8+(t+t^3)*x0*x2*x3*x4*x5*x6*x7*x8+(t+t^3)*x1*x2*x3*x4*x5*x6*x7*x8");
    polCyclic9.emplace_back("(t+t^3)*x0*x1*x2*x3*x4*x5*x6*x7*x8-1");

    // Create cyclic9 ideal;
    Ideal<eltType> cyclic9(polCyclic9, 9, 20000000);
    
    // Compute a reduced groebner basis;
    nbGen=cyclic9.f4();
    
    // Print the reduced groebner basis into a file
    if(magma)
    {
        cyclic9.printReducedGroebnerBasis("cyclic9", eltType::getModulo());
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
    polRandomIdeal.emplace_back("(t^30 + t^29 + t^27 + t^26 + t^24 + t^20 + t^19 + t^18 + t^17 + t^16 + t^15 + t^14 + t^11 + t^9 + t^6 + t^4 + t^3 + t^2 + 1)*x0*x1^3*x2 + (t^29 + t^27 + t^26 + t^21 + t^20 + t^18 + t^16 + t^15 + t^11 + t^8 + t^7 + t^5 + t^2 + t)*x2*x3^4 + (t^30 + t^29 + t^28 + t^27 + t^26 + t^25 + t^22 + t^21 + t^20 + t^17 + t^16 + t^14 + t^13 + t^10 + t^9 + t^8 + t + 1)*x4^5 + (t^28 + t^27 + t^21 + t^18 + t^15 + t^12 + t^11 + t^10 + t^8 + t^7 + t^4 + t^2 + t)*x1*x2^2*x3*x5 + (t^30 + t^27 + t^25 + t^22 + t^21 + t^20 + t^18 + t^16 + t^14 + t^11 + t^7 + t^5 + t^4 + t^3 + t^2 + t + 1)*x1*x3^3*x5 + (t^28 + t^25 + t^24 + t^23 + t^22 + t^19 + t^18 + t^17 + t^16 + t^14 + t^13 + t^9 + t^8 + t^6 + t^4 + t^2 + 1)*x0^2*x1^2 + (t^29 + t^25 + t^24 + t^23 + t^20 + t^16 + t^13 + t^11 + t^10 + t^9 + t^8 + t^7 + t^6 + t^5 + t^3)*x2*x3^3 + (t^29 + t^26 + t^25 + t^24 + t^22 + t^20 + t^19 + t^16 + t^14 + t^13 + t^12 + t^11 + t^9 + t^8 + t^3 + t^2 + t + 1)*x1*x2*x4*x5 + (t^28 + t^25 + t^22 + t^21 + t^20 + t^19 + t^16 + t^15 + t^14 + t^13 + t^11 + t^9 + t^8 + t^5 + t^4 + t^2 + t + 1)*x4^2*x5 + (t^29 + t^26 + t^25 + t^24 + t^22 + t^21 + t^18 + t^17 + t^15 + t^14 + t^12 + t^11 + t^8 + t^7 + t^6 + t^5 + t^4 + t^3 + t^2 + 1)*x0*x1");
    polRandomIdeal.emplace_back("(t^30 + t^28 + t^25 + t^24 + t^22 + t^21 + t^20 + t^19 + t^18 + t^17 + t^13 + t^12 + t^10 + t^8 + t^7 + t^6 + t^5 + t^4 + t^3 + t^2 + 1)*x0*x1^3*x2 + (t^30 + t^28 + t^27 + t^22 + t^21 + t^20 + t^18 + t^17 + t^15 + t^14 + t^11 + t^10 + t^9 + t^6 + t^5 + t^4 + t^2 + t + 1)*x0^2*x1*x3*x5 + (t^28 + t^24 + t^19 + t^10 + t^3 + t)*x0*x1*x2*x5^2 + (t^26 + t^25 + t^24 + t^23 + t^20 + t^18 + t^17 + t^16 + t^15 + t^14 + t^9 + t^8 + t^7 + t^6 + t^5 + t^4 + t)*x0^2*x1*x4 + (t^28 + t^27 + t^20 + t^16 + t^13 + t^11 + t^9 + t^8 + t^7 + t^6 + t^5 + t^4 + t^3 + t^2 + t + 1)*x1*x3*x5^2 + (t^30 + t^29 + t^28 + t^27 + t^25 + t^18 + t^17 + t^16 + t^15 + t^13 + t^12 + t^5 + t^3 + t)*x2*x3*x5^2 + (t^30 + t^29 + t^28 + t^27 + t^26 + t^24 + t^20 + t^17 + t^13 + t^12 + t^10 + t^9 + t^8 + t^6 + t^4 + t^3 + t^2 + 1)*x0^2*x1 + (t^28 + t^27 + t^26 + t^25 + t^24 + t^22 + t^21 + t^19 + t^17 + t^16 + t^15 + t^12 + t^9 + t^4 + t^2 + t + 1)*x0^2*x3 + (t^25 + t^24 + t^21 + t^20 + t^19 + t^18 + t^17 + t^15 + t^11 + t^10 + t^7 + t^3 + t + 1)*x0*x4 + (t^30 + t^28 + t^23 + t^22 + t^19 + t^18 + t^17 + t^15 + t^13 + t^12 + t^10 + t^9 + t^8 + t^7 + t^6 + t^4 + t + 1)*x3");
    polRandomIdeal.emplace_back("(t^30 + t^29 + t^28 + t^25 + t^24 + t^23 + t^22 + t^21 + t^19 + t^11 + t^9 + t^6 + t^2)*x0*x1^2*x2*x3 + (t^30 + t^29 + t^28 + t^26 + t^25 + t^24 + t^23 + t^21 + t^19 + t^17 + t^16 + t^11 + t^10 + t^5 + t^4 + 1)*x2^4*x4 + (t^30 + t^27 + t^24 + t^23 + t^21 + t^18 + t^17 + t^16 + t^14 + t^12 + t^9 + t^8 + t^4 + t^3 + t^2 + t + 1)*x0*x2*x3^2*x4 + (t^30 + t^29 + t^26 + t^24 + t^22 + t^21 + t^18 + t^17 + t^8 + t^7 + t^5 + t^4 + t^3 + 1)*x1^2*x4^2*x5 + (t^30 + t^29 + t^27 + t^25 + t^24 + t^21 + t^20 + t^19 + t^18 + t^17 + t^16 + t^15 + t^14 + t^12 + t^10 + t^8 + t^7 + t^3 + t^2 + t)*x0^3*x5^2 + (t^26 + t^25 + t^21 + t^20 + t^18 + t^17 + t^16 + t^15 + t^11 + t^8 + t^7 + t^5 + t^3)*x0*x1^2*x5^2 + (t^29 + t^28 + t^27 + t^24 + t^20 + t^17 + t^15 + t^12 + t^11 + t^7 + t^5 + t^4 + t)*x0*x1^2*x3 + (t^28 + t^27 + t^25 + t^22 + t^19 + t^18 + t^15 + t^14 + t^12 + t^10 + t^8 + t^7 + t^4 + t^2)*x0^2*x1*x4 + (t^30 + t^28 + t^26 + t^25 + t^24 + t^23 + t^21 + t^20 + t^19 + t^17 + t^14 + t^13 + t^12 + t^11 + t^9 + t^8 + t^6 + t^5 + t^4 + t^3 + t^2 + t + 1)*x4*x5^3 + (t^25 + t^24 + t^23 + t^20 + t^13 + t^11 + t^9 + t^8 + t^7 + t^5 + t^4 + t^3 + t^2 + t)*x1^2");
    polRandomIdeal.emplace_back("(t^29 + t^23 + t^22 + t^16 + t^15 + t^13 + t^10 + t^9 + t^8 + t^5 + t + 1)*x0*x1^2*x3^2 + (t^28 + t^27 + t^24 + t^23 + t^22 + t^19 + t^18 + t^16 + t^10 + t^9 + t^8 + t^7 + t^5 + t^2 + t + 1)*x2^2*x3^3 + (t^24 + t^22 + t^18 + t^17 + t^16 + t^15 + t^12 + t^11 + t^9 + t^8 + t^7 + t^6 + t^3 + t)*x0^2*x2*x5^2 + (t^29 + t^27 + t^26 + t^25 + t^24 + t^23 + t^22 + t^20 + t^18 + t^14 + t^12 + t^11 + t^9 + t^8 + t^7 + t^6 + t^5 + t^3 + 1)*x3^3*x5 + (t^30 + t^28 + t^26 + t^25 + t^24 + t^21 + t^17 + t^16 + t^15 + t^14 + t^13 + t^10 + t^7 + t^6 + t^5 + t^2 + 1)*x2*x4^2*x5 + (t^28 + t^24 + t^23 + t^22 + t^21 + t^20 + t^19 + t^17 + t^9 + t^8 + t^7 + t^6 + t^4 + t)*x1*x2*x5^2 + (t^27 + t^26 + t^24 + t^23 + t^21 + t^17 + t^16 + t^14 + t^13 + t^11 + t^6 + t)*x1*x3^2 + (t^29 + t^27 + t^26 + t^25 + t^24 + t^18 + t^17 + t^15 + t^14 + t^13 + t^8 + t^7 + t^2)*x2*x4^2 + (t^26 + t^24 + t^22 + t^21 + t^17 + t^16 + t^12 + t^9 + t^7 + t^5 + t^3 + t^2 + t + 1)*x2*x5^2 + (t^28 + t^26 + t^23 + t^22 + t^21 + t^20 + t^19 + t^18 + t^11 + t^4 + t^3 + 1)*x4*x5^2");
    polRandomIdeal.emplace_back("(t^29 + t^25 + t^20 + t^19 + t^18 + t^17 + t^16 + t^15 + t^14 + t^12 + t^9 + t^7 + t^3 + t)*x0^3*x2*x5 + (t^29 + t^28 + t^26 + t^23 + t^21 + t^17 + t^16 + t^15 + t^14 + t^10 + t^9 + t^6 + t^4 + t^2 + t + 1)*x0*x1^2*x2*x5 + (t^29 + t^28 + t^27 + t^23 + t^22 + t^21 + t^19 + t^18 + t^17 + t^16 + t^15 + t^14 + t^13 + t^12 + t^9 + t^8 + t^7 + t^6 + t^5 + t^3 + t^2)*x2*x3^3*x5 + (t^30 + t^29 + t^25 + t^22 + t^15 + t^12 + t^11 + t^10 + t^9 + t^4 + t^3 + t)*x2^2*x3*x4*x5 + (t^29 + t^26 + t^25 + t^20 + t^19 + t^17 + t^16 + t^15 + t^14 + t^13 + t^8 + t^5 + t^3 + t^2 + t)*x3*x4^3*x5 + (t^28 + t^27 + t^23 + t^20 + t^19 + t^18 + t^17 + t^16 + t^15 + t^13 + t^12 + t^11 + t^8 + t^3 + t^2 + t + 1)*x3^2*x5^3 + (t^30 + t^25 + t^24 + t^22 + t^21 + t^19 + t^18 + t^16 + t^13 + t^12 + t^8 + t^7 + t^5 + t)*x1*x2*x3*x5 + (t^28 + t^24 + t^23 + t^22 + t^20 + t^17 + t^16 + t^14 + t^13 + t^12 + t^10 + t^9 + t^8 + t^7 + t^4 + t^3 + t^2 + t + 1)*x0^2*x5 + (t^30 + t^28 + t^27 + t^26 + t^22 + t^21 + t^18 + t^15 + t^14 + t^13 + t^11 + t^10 + t^9 + t^8 + t^6 + t^3 + 1)*x2^2*x5 + (t^29 + t^28 + t^26 + t^25 + t^21 + t^20 + t^19 + t^18 + t^16 + t^15 + t^13 + t^11 + t^10 + t^8 + t^4 + t^3 + t^2 + t + 1)*x4^2*x5");
    polRandomIdeal.emplace_back("(t^30 + t^28 + t^26 + t^25 + t^24 + t^23 + t^22 + t^20 + t^19 + t^18 + t^17 + t^16 + t^15 + t^10 + t^8 + t^6 + t^2 + 1)*x0*x1^2*x2^2 + (t^28 + t^26 + t^17 + t^14 + t^13 + t^11 + t^10 + t^8 + t^5 + t^3 + t^2 + t)*x0^3*x3^2 + (t^30 + t^29 + t^27 + t^26 + t^25 + t^23 + t^18 + t^17 + t^15 + t^13 + t^11 + t^9 + t^8 + t^7 + t^6 + t^5 + t^4 + t)*x1*x3^4 + (t^28 + t^27 + t^23 + t^22 + t^21 + t^19 + t^18 + t^17 + t^15 + t^13 + t^11 + t^9 + t^7 + t^6 + t^2 + 1)*x3^2*x4^3 + (t^30 + t^29 + t^28 + t^27 + t^26 + t^24 + t^23 + t^21 + t^19 + t^16 + t^13 + t^10 + t^9 + t^8 + t^7 + t^6 + t^5 + t^4 + t^3 + t^2 + 1)*x3^3*x5^2 + (t^30 + t^29 + t^25 + t^23 + t^22 + t^21 + t^20 + t^19 + t^16 + t^14 + t^13 + t^11 + t^9 + t^8 + t^7 + t^3 + t^2 + t + 1)*x0^2*x4*x5^2 + (t^29 + t^28 + t^27 + t^25 + t^20 + t^19 + t^18 + t^17 + t^16 + t^15 + t^14 + t^13 + t^11 + t^10 + t^9 + t^8 + t^5 + t^4 + t^3 + t)*x2^2*x3^2 + (t^30 + t^29 + t^27 + t^22 + t^21 + t^20 + t^19 + t^18 + t^17 + t^16 + t^15 + t^13 + t^9 + t^8 + t^7 + t^4 + t + 1)*x1*x2*x3*x4 + (t^29 + t^28 + t^24 + t^21 + t^19 + t^18 + t^11 + t^10 + t^6 + t^5 + t^3 + t + 1)*x0^2*x4*x5 + (t^27 + t^23 + t^21 + t^19 + t^18 + t^15 + t^14 + t^13 + t^12 + t^11 + t^9 + t^8 + t^6 + t^5 + t^4 + t^3 + 1)*x2*x3*x5");
    polRandomIdeal.emplace_back("(t^28 + t^26 + t^24 + t^18 + t^16 + t^14 + t^13 + t^9 + t^8 + t^7 + t^5 + t^4 + t^2 + t + 1)*x0*x2*x3*x4*x5 + (t^30 + t^27 + t^25 + t^22 + t^21 + t^19 + t^18 + t^17 + t^16 + t^15 + t^14 + t^13 + t^11 + t^10 + t^9 + t^8 + t^6 + t^5 + t^4 + 1)*x0*x1*x4^2*x5 + (t^26 + t^25 + t^24 + t^23 + t^22 + t^20 + t^19 + t^18 + t^17 + t^12 + t^10 + t^6 + t^5 + t^2)*x0*x1^2*x5^2 + (t^30 + t^29 + t^28 + t^27 + t^25 + t^24 + t^23 + t^22 + t^19 + t^18 + t^15 + t^13 + t^12 + t^10 + t^8 + t^7 + t^6 + t)*x0*x3^2*x5^2 + (t^30 + t^29 + t^26 + t^25 + t^24 + t^22 + t^21 + t^19 + t^18 + t^16 + t^15 + t^12 + t^10 + t^8 + t^5 + t^3 + t^2)*x0*x5^4 + (t^28 + t^27 + t^25 + t^24 + t^19 + t^18 + t^14 + t^12 + t^11 + t^8 + t^7 + t^5 + t^4 + t^3 + 1)*x2*x5^4 + (t^30 + t^26 + t^25 + t^20 + t^19 + t^15 + t^14 + t^13 + t^12 + t^11 + t^10 + t^8 + t^6 + t^4 + t^2)*x1*x4*x5^2 + (t^30 + t^28 + t^25 + t^24 + t^23 + t^22 + t^21 + t^20 + t^19 + t^18 + t^17 + t^16 + t^14 + t^11 + t^9 + t^6 + t^3 + t^2 + 1)*x0*x1*x3 + (t^30 + t^29 + t^26 + t^20 + t^19 + t^18 + t^17 + t^16 + t^15 + t^14 + t^13 + t^11 + t^10 + t^9 + t^8 + t^6 + t^4)*x2*x3^2 + (t^30 + t^28 + t^26 + t^24 + t^22 + t^21 + t^20 + t^13 + t^11 + t^9 + t^8 + t^6 + t^5 + t^4 + t^3 + 1)*x2*x3");
    polRandomIdeal.emplace_back("(t^27 + t^26 + t^25 + t^22 + t^21 + t^19 + t^13 + t^12 + t^8 + t^5 + t^4 + t + 1)*x0*x1^3*x3 + (t^30 + t^29 + t^28 + t^26 + t^25 + t^24 + t^20 + t^14 + t^12 + t^11 + t^10 + t^9 + t^8 + t^7 + t^6 + t^3 + t^2 + t + 1)*x0^2*x2*x3*x5 + (t^30 + t^28 + t^27 + t^26 + t^24 + t^23 + t^21 + t^20 + t^18 + t^16 + t^15 + t^14 + t^12 + t^11 + t^7 + t)*x2*x3^2*x4*x5 + (t^30 + t^29 + t^27 + t^20 + t^19 + t^18 + t^17 + t^16 + t^15 + t^14 + t^13 + t^12 + t^10 + t^9 + t^8 + t^6 + t^5 + t^4 + t^3 + t + 1)*x2*x3*x4^2 + (t^30 + t^28 + t^26 + t^25 + t^24 + t^20 + t^18 + t^15 + t^10 + t^8 + t^5 + t^4 + t^3 + 1)*x1^3*x5 + (t^30 + t^27 + t^26 + t^21 + t^19 + t^18 + t^16 + t^14 + t^12 + t^7 + 1)*x0^2*x3*x5 + (t^26 + t^25 + t^23 + t^21 + t^20 + t^18 + t^15 + t^13 + t^8 + t^7 + t^6 + t^5 + t^4 + t^3 + t^2)*x1*x3*x4*x5 + (t^28 + t^26 + t^25 + t^23 + t^20 + t^18 + t^17 + t^16 + t^15 + t^14 + t^11 + t^7 + t^6 + t^5 + t^4 + t^3 + t + 1)*x0^2*x5^2 + (t^30 + t^28 + t^25 + t^24 + t^21 + t^19 + t^18 + t^17 + t^12 + t^5 + t^4 + t^3)*x5^2 + (t^29 + t^28 + t^27 + t^26 + t^25 + t^22 + t^21 + t^20 + t^18 + t^17 + t^16 + t^15 + t^14 + t^13 + t^11 + t^9 + t^8 + t^3 + t^2 + t)*x1");
    polRandomIdeal.emplace_back("(t^29 + t^27 + t^25 + t^22 + t^21 + t^20 + t^19 + t^17 + t^16 + t^15 + t^12 + t^11 + t^10 + t^9 + t^8 + t^7 + t^5 + t^3 + t^2 + t)*x0^3*x1^2 + (t^30 + t^27 + t^26 + t^25 + t^23 + t^21 + t^20 + t^16 + t^15 + t^14 + t^12 + t^8 + t^7 + t^6 + t^4 + t^3 + 1)*x0^2*x4^3 + (t^29 + t^28 + t^27 + t^26 + t^24 + t^20 + t^18 + t^17 + t^12 + t^9 + t^7 + t^4 + t^3 + t)*x1*x3^2*x5^2 + (t^28 + t^27 + t^26 + t^22 + t^20 + t^19 + t^17 + t^15 + t^12 + t^9 + t^7 + t^3 + t^2 + t)*x1*x5^4 + (t^28 + t^24 + t^23 + t^22 + t^19 + t^17 + t^16 + t^15 + t^11 + t^9 + t^6 + t^5 + t^4 + 1)*x0^3*x1 + (t^30 + t^29 + t^28 + t^22 + t^21 + t^20 + t^18 + t^16 + t^13 + t^12 + t^11 + t^8 + t^4 + t + 1)*x0*x2*x3^2 + (t^30 + t^28 + t^26 + t^25 + t^23 + t^22 + t^21 + t^18 + t^16 + t^15 + t^14 + t^13 + t^11 + t^9 + t^8 + t^5 + t^4 + t^3 + t^2)*x0*x1*x3*x5 + (t^30 + t^29 + t^28 + t^27 + t^26 + t^23 + t^22 + t^21 + t^20 + t^18 + t^16 + t^15 + t^14 + t^11 + t^8 + t^7 + t^6 + t^5 + t^3 + t^2 + t + 1)*x0*x1*x2 + (t^29 + t^28 + t^27 + t^26 + t^23 + t^21 + t^19 + t^17 + t^16 + t^13 + t^10 + t^9 + t^6 + t^5 + t^3 + 1)*x0*x2*x3 + (t^30 + t^28 + t^19 + t^18 + t^16 + t^15 + t^11 + t^8 + t^6 + t^4 + t^2 + 1)*x0*x4*x5");
    polRandomIdeal.emplace_back("(t^30 + t^26 + t^20 + t^18 + t^17 + t^16 + t^15 + t^11 + t^9 + t^6 + t^5 + t^4 + t^3 + 1)*x0^2*x2^2*x3 + (t^27 + t^24 + t^23 + t^16 + t^14 + t^12 + t^5 + t^3)*x0^2*x4^2*x5 + (t^30 + t^29 + t^28 + t^26 + t^25 + t^24 + t^23 + t^21 + t^20 + t^17 + t^15 + t^11 + t^9 + t^8 + t^6 + t^4 + t^3)*x1*x3*x4^2*x5 + (t^30 + t^27 + t^24 + t^23 + t^21 + t^20 + t^12 + t^10 + t^8 + t^2 + 1)*x5^5 + (t^30 + t^28 + t^26 + t^24 + t^23 + t^22 + t^21 + t^19 + t^17 + t^15 + t^14 + t^13 + t^12 + t^8 + t^7 + t^6 + t^5 + t^3 + t)*x1*x2^3 + (t^30 + t^29 + t^28 + t^26 + t^25 + t^24 + t^22 + t^20 + t^19 + t^18 + t^17 + t^13 + t^12 + t^10 + t^9 + t^7 + t^6 + t^5 + t^3 + t)*x0*x1*x2*x3 + (t^30 + t^28 + t^26 + t^23 + t^21 + t^18 + t^17 + t^16 + t^15 + t^14 + t^13 + t^12 + t^11 + t^9 + t^7 + t^6 + t^3 + t + 1)*x1*x2^2*x5 + (t^28 + t^27 + t^26 + t^20 + t^15 + t^14 + t^12 + t^9 + t^7 + t^5 + t^2 + t + 1)*x0^2*x4 + (t^29 + t^26 + t^25 + t^21 + t^20 + t^19 + t^18 + t^15 + t^14 + t^13 + t^9 + t^7 + t^5 + 1)*x1^2 + (t^30 + t^29 + t^28 + t^25 + t^21 + t^20 + t^19 + t^18 + t^15 + t^13 + t^9 + t^7 + t^6 + t^5 + t^3 + t)*x4");

    // Create katsura12 ideal;
    Ideal<eltType> randomIdeal(polRandomIdeal, 6);
    
    // Compute a reduced groebner basis;
    nbGen=randomIdeal.f4();
    
    // Print the reduced groebner basis into a file
    if(magma)
    {
        randomIdeal.printReducedGroebnerBasis("randomIdeal", eltType::getModulo());
    }
    
    return nbGen;
}

int main (int argc, char **argv)
{
    cout << "#########################################################" << endl;
    cout << "#                   BENCHMARK GF(2^n)                   #" << endl;
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
    ofstream file("benchmark-gf2-32bits.txt");
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
    
    
    return 0;
}


