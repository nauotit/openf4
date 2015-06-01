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
 *  \file benchmark-givaro-gfq.cpp
 *  \example benchmark-givaro-gfq.cpp
 *  \brief Benchmark with polynomial coefficients using Givaro representation.
 *  \ingroup benchmark
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include "../include/ideal.h"

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=0;
int F4::NB_THREAD=min(2, omp_get_num_procs());

// Init element-givaro tools
typedef Givaro::GFqDom<long> Field;
Field::Residu_t modulo=19;
unsigned long expo = 5;
Field F(modulo, expo);
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
    Monomial::initMonomial(6,11);
    
    // Create polynomial array
    vector<Polynomial<eltType>> polCyclic6;
    
    // Fill the polynomial array
    polCyclic6.emplace_back("(t^3+t)*x0+(t^3+t)*x1+(t^3+t)*x2+(t^3+t)*x3+(t^3+t)*x4+(t^3+t)*x5");
    polCyclic6.emplace_back("(t^3+t)*x0*x1+(t^3+t)*x1*x2+(t^3+t)*x2*x3+(t^3+t)*x3*x4+(t^3+t)*x0*x5+(t^3+t)*x4*x5");
    polCyclic6.emplace_back("(t^3+t)*x0*x1*x2+(t^3+t)*x1*x2*x3+(t^3+t)*x2*x3*x4+(t^3+t)*x0*x1*x5+(t^3+t)*x0*x4*x5+(t^3+t)*x3*x4*x5");
    polCyclic6.emplace_back("(t^3+t)*x0*x1*x2*x3+(t^3+t)*x1*x2*x3*x4+(t^3+t)*x0*x1*x2*x5+(t^3+t)*x0*x1*x4*x5+(t^3+t)*x0*x3*x4*x5+(t^3+t)*x2*x3*x4*x5");
    polCyclic6.emplace_back("(t^3+t)*x0*x1*x2*x3*x4+(t^3+t)*x0*x1*x2*x3*x5+(t^3+t)*x0*x1*x2*x4*x5+(t^3+t)*x0*x1*x3*x4*x5+(t^3+t)*x0*x2*x3*x4*x5+(t^3+t)*x1*x2*x3*x4*x5");
    polCyclic6.emplace_back("(t^3+t)*x0*x1*x2*x3*x4*x5-1");

    // Create cyclic6 ideal;
    Ideal<eltType> cyclic6(polCyclic6, 6, 100000, 11, 2, 10);
    
    // Compute a reduced groebner basis;
    nbGen=cyclic6.f4();
    
    // Print the reduced groebner basis into a file
    if(magma)
    {
        cyclic6.printReducedGroebnerBasis("cyclic6", modulo);
    }
    
    cyclic6.printReducedGroebnerBasis(true);
    
    return nbGen;
}

int cyclic7F4(bool magma)
{
    cout << "#########################################################" << endl;
    cout << "#                         CYCLIC 7                      #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Init element-zech-prime tools
    eltType::setField(F);
    
    // Number of generator
    int nbGen;
    
    // Init monomial tools
    Monomial::initMonomial(7,13);
    
    // Create polynomial array
    vector<Polynomial<eltType>> polCyclic7;
    
    // Fill the polynomial array
    polCyclic7.emplace_back("(t^3+t)*x0+(t^3+t)*x1+(t^3+t)*x2+(t^3+t)*x3+(t^3+t)*x4+(t^3+t)*x5+(t^3+t)*x6");
    polCyclic7.emplace_back("(t^3+t)*x0*x1+(t^3+t)*x1*x2+(t^3+t)*x2*x3+(t^3+t)*x3*x4+(t^3+t)*x4*x5+(t^3+t)*x0*x6+(t^3+t)*x5*x6");
    polCyclic7.emplace_back("(t^3+t)*x0*x1*x2+(t^3+t)*x1*x2*x3+(t^3+t)*x2*x3*x4+(t^3+t)*x3*x4*x5+(t^3+t)*x0*x1*x6+(t^3+t)*x0*x5*x6+(t^3+t)*x4*x5*x6");
    polCyclic7.emplace_back("(t^3+t)*x0*x1*x2*x3+(t^3+t)*x1*x2*x3*x4+(t^3+t)*x2*x3*x4*x5+(t^3+t)*x0*x1*x2*x6+(t^3+t)*x0*x1*x5*x6+(t^3+t)*x0*x4*x5*x6+(t^3+t)*x3*x4*x5*x6");
    polCyclic7.emplace_back("(t^3+t)*x0*x1*x2*x3*x4+(t^3+t)*x1*x2*x3*x4*x5+(t^3+t)*x0*x1*x2*x3*x6+(t^3+t)*x0*x1*x2*x5*x6+(t^3+t)*x0*x1*x4*x5*x6+(t^3+t)*x0*x3*x4*x5*x6+(t^3+t)*x2*x3*x4*x5*x6");
    polCyclic7.emplace_back("(t^3+t)*x0*x1*x2*x3*x4*x5+(t^3+t)*x0*x1*x2*x3*x4*x6+(t^3+t)*x0*x1*x2*x3*x5*x6+(t^3+t)*x0*x1*x2*x4*x5*x6+(t^3+t)*x0*x1*x3*x4*x5*x6+(t^3+t)*x0*x2*x3*x4*x5*x6+(t^3+t)*x1*x2*x3*x4*x5*x6");
    polCyclic7.emplace_back("(t^3+t)*x0*x1*x2*x3*x4*x5*x6-1");

    // Create cyclic7 ideal;
    Ideal<eltType> cyclic7(polCyclic7, 7 , 1000000, 13, 2, 12);
    
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
    
    // Init element-zech-prime tools
    eltType::setField(F);
    
    // Number of generator
    int nbGen;
    
    // Init monomial tools
    Monomial::initMonomial(8,15);
    
    // Create polynomial array
    vector<Polynomial<eltType>> polCyclic8;
    
    // Fill the polynomial array
    polCyclic8.emplace_back("(t^3+t)*x0+(t^3+t)*x1+(t^3+t)*x2+(t^3+t)*x3+(t^3+t)*x4+(t^3+t)*x5+(t^3+t)*x6+(t^3+t)*x7");
    polCyclic8.emplace_back("(t^3+t)*x0*x1+(t^3+t)*x1*x2+(t^3+t)*x2*x3+(t^3+t)*x3*x4+(t^3+t)*x4*x5+(t^3+t)*x5*x6+(t^3+t)*x0*x7+(t^3+t)*x6*x7");
    polCyclic8.emplace_back("(t^3+t)*x0*x1*x2+(t^3+t)*x1*x2*x3+(t^3+t)*x2*x3*x4+(t^3+t)*x3*x4*x5+(t^3+t)*x4*x5*x6+(t^3+t)*x0*x1*x7+(t^3+t)*x0*x6*x7+(t^3+t)*x5*x6*x7");
    polCyclic8.emplace_back("(t^3+t)*x0*x1*x2*x3+(t^3+t)*x1*x2*x3*x4+(t^3+t)*x2*x3*x4*x5+(t^3+t)*x3*x4*x5*x6+(t^3+t)*x0*x1*x2*x7+(t^3+t)*x0*x1*x6*x7+(t^3+t)*x0*x5*x6*x7+(t^3+t)*x4*x5*x6*x7");
    polCyclic8.emplace_back("(t^3+t)*x0*x1*x2*x3*x4+(t^3+t)*x1*x2*x3*x4*x5+(t^3+t)*x2*x3*x4*x5*x6+(t^3+t)*x0*x1*x2*x3*x7+(t^3+t)*x0*x1*x2*x6*x7+(t^3+t)*x0*x1*x5*x6*x7+(t^3+t)*x0*x4*x5*x6*x7+(t^3+t)*x3*x4*x5*x6*x7");
    polCyclic8.emplace_back("(t^3+t)*x0*x1*x2*x3*x4*x5+(t^3+t)*x1*x2*x3*x4*x5*x6+(t^3+t)*x0*x1*x2*x3*x4*x7+(t^3+t)*x0*x1*x2*x3*x6*x7+(t^3+t)*x0*x1*x2*x5*x6*x7+(t^3+t)*x0*x1*x4*x5*x6*x7+(t^3+t)*x0*x3*x4*x5*x6*x7+(t^3+t)*x2*x3*x4*x5*x6*x7");
    polCyclic8.emplace_back("(t^3+t)*x0*x1*x2*x3*x4*x5*x6+(t^3+t)*x0*x1*x2*x3*x4*x5*x7+(t^3+t)*x0*x1*x2*x3*x4*x6*x7+(t^3+t)*x0*x1*x2*x3*x5*x6*x7+(t^3+t)*x0*x1*x2*x4*x5*x6*x7+(t^3+t)*x0*x1*x3*x4*x5*x6*x7+(t^3+t)*x0*x2*x3*x4*x5*x6*x7+(t^3+t)*x1*x2*x3*x4*x5*x6*x7");
    polCyclic8.emplace_back("(t^3+t)*x0*x1*x2*x3*x4*x5*x6*x7-1");

    // Create cyclic8 ideal;
    Ideal<eltType> cyclic8(polCyclic8, 8, 1000000, 15, 2, 14);
    
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
    
    // Init element-zech-prime tools
    eltType::setField(F);
    
    // Number of generator
    int nbGen;
    
    // Init monomial tools
    Monomial::initMonomial(9,17);
    
    // Create polynomial array
    vector<Polynomial<eltType>> polCyclic9;
    
    // Fill the polynomial array
    polCyclic9.emplace_back("(t^3+t)*x0+(t^3+t)*x1+(t^3+t)*x2+(t^3+t)*x3+(t^3+t)*x4+(t^3+t)*x5+(t^3+t)*x6+(t^3+t)*x7+(t^3+t)*x8");
    polCyclic9.emplace_back("(t^3+t)*x0*x1+(t^3+t)*x1*x2+(t^3+t)*x2*x3+(t^3+t)*x3*x4+(t^3+t)*x4*x5+(t^3+t)*x5*x6+(t^3+t)*x6*x7+(t^3+t)*x0*x8+(t^3+t)*x7*x8");
    polCyclic9.emplace_back("(t^3+t)*x0*x1*x2+(t^3+t)*x1*x2*x3+(t^3+t)*x2*x3*x4+(t^3+t)*x3*x4*x5+(t^3+t)*x4*x5*x6+(t^3+t)*x5*x6*x7+(t^3+t)*x0*x1*x8+(t^3+t)*x0*x7*x8+(t^3+t)*x6*x7*x8");
    polCyclic9.emplace_back("(t^3+t)*x0*x1*x2*x3+(t^3+t)*x1*x2*x3*x4+(t^3+t)*x2*x3*x4*x5+(t^3+t)*x3*x4*x5*x6+(t^3+t)*x4*x5*x6*x7+(t^3+t)*x0*x1*x2*x8+(t^3+t)*x0*x1*x7*x8+(t^3+t)*x0*x6*x7*x8+(t^3+t)*x5*x6*x7*x8");
    polCyclic9.emplace_back("(t^3+t)*x0*x1*x2*x3*x4+(t^3+t)*x1*x2*x3*x4*x5+(t^3+t)*x2*x3*x4*x5*x6+(t^3+t)*x3*x4*x5*x6*x7+(t^3+t)*x0*x1*x2*x3*x8+(t^3+t)*x0*x1*x2*x7*x8+(t^3+t)*x0*x1*x6*x7*x8+(t^3+t)*x0*x5*x6*x7*x8+(t^3+t)*x4*x5*x6*x7*x8");
    polCyclic9.emplace_back("(t^3+t)*x0*x1*x2*x3*x4*x5+(t^3+t)*x1*x2*x3*x4*x5*x6+(t^3+t)*x2*x3*x4*x5*x6*x7+(t^3+t)*x0*x1*x2*x3*x4*x8+(t^3+t)*x0*x1*x2*x3*x7*x8+(t^3+t)*x0*x1*x2*x6*x7*x8+(t^3+t)*x0*x1*x5*x6*x7*x8+(t^3+t)*x0*x4*x5*x6*x7*x8+(t^3+t)*x3*x4*x5*x6*x7*x8");
    polCyclic9.emplace_back("(t^3+t)*x0*x1*x2*x3*x4*x5*x6+(t^3+t)*x1*x2*x3*x4*x5*x6*x7+(t^3+t)*x0*x1*x2*x3*x4*x5*x8+(t^3+t)*x0*x1*x2*x3*x4*x7*x8+(t^3+t)*x0*x1*x2*x3*x6*x7*x8+(t^3+t)*x0*x1*x2*x5*x6*x7*x8+(t^3+t)*x0*x1*x4*x5*x6*x7*x8+(t^3+t)*x0*x3*x4*x5*x6*x7*x8+(t^3+t)*x2*x3*x4*x5*x6*x7*x8");
    polCyclic9.emplace_back("(t^3+t)*x0*x1*x2*x3*x4*x5*x6*x7+(t^3+t)*x0*x1*x2*x3*x4*x5*x6*x8+(t^3+t)*x0*x1*x2*x3*x4*x5*x7*x8+(t^3+t)*x0*x1*x2*x3*x4*x6*x7*x8+(t^3+t)*x0*x1*x2*x3*x5*x6*x7*x8+(t^3+t)*x0*x1*x2*x4*x5*x6*x7*x8+(t^3+t)*x0*x1*x3*x4*x5*x6*x7*x8+(t^3+t)*x0*x2*x3*x4*x5*x6*x7*x8+(t^3+t)*x1*x2*x3*x4*x5*x6*x7*x8");
    polCyclic9.emplace_back("(t^3+t)*x0*x1*x2*x3*x4*x5*x6*x7*x8-1");

    // Create cyclic9 ideal;
    Ideal<eltType> cyclic9(polCyclic9, 9, 20000000, 17, 2, 16);
    
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
    
    // Init element-zech-prime tools
    eltType::setField(F);
    
    // Number of generator
    int nbGen;
    
    // Init monomial tools
    Monomial::initMonomial(9,11);
    
    // Create polynomial array
    vector<Polynomial<eltType>> polKatsura9;
    
    // Fill the polynomial array
    polKatsura9.emplace_back("(t^3+t)*x0+2*x1+2*x2+2*x3+2*x4+2*x5+2*x6+2*x7+2*x8-1");
    polKatsura9.emplace_back("(t^3+t)*x0^2+2*x1^2+2*x2^2+2*x3^2+2*x4^2+2*x5^2+2*x6^2+2*x7^2+2*x8^2-x0");
    polKatsura9.emplace_back("(2*t^3+2*t)*x0*x1+2*x1*x2+2*x2*x3+2*x3*x4+2*x4*x5+2*x5*x6+2*x6*x7+2*x7*x8-x1");
    polKatsura9.emplace_back("(t^3+t)*x1^2+2*x0*x2+2*x1*x3+2*x2*x4+2*x3*x5+2*x4*x6+2*x5*x7+2*x6*x8-x2");
    polKatsura9.emplace_back("(2*t^3+2*t)*x1*x2+2*x0*x3+2*x1*x4+2*x2*x5+2*x3*x6+2*x4*x7+2*x5*x8-x3");
    polKatsura9.emplace_back("(t^3+t)*x2^2+2*x1*x3+2*x0*x4+2*x1*x5+2*x2*x6+2*x3*x7+2*x4*x8-x4");
    polKatsura9.emplace_back("(2*t^3+2*t)*x2*x3+2*x1*x4+2*x0*x5+2*x1*x6+2*x2*x7+2*x3*x8-x5");
    polKatsura9.emplace_back("(t^3+t)*x3^2+2*x2*x4+2*x1*x5+2*x0*x6+2*x1*x7+2*x2*x8-x6");
    polKatsura9.emplace_back("(2*t^3+2*t)*x3*x4+2*x2*x5+2*x1*x6+2*x0*x7+2*x1*x8-x7");

    // Create katsura9 ideal;
    Ideal<eltType> katsura9(polKatsura9, 9 ,1000000, 11, 2, 10);
    
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
    
    // Init element-zech-prime tools
    eltType::setField(F);
    
    // Number of generator
    int nbGen;
    
    // Init monomial tools
    Monomial::initMonomial(10,12);
    
    // Create polynomial array
    vector<Polynomial<eltType>> polKatsura10;
    
    // Fill the polynomial array
    polKatsura10.emplace_back("(t^3+t)*x0+2*x1+2*x2+2*x3+2*x4+2*x5+2*x6+2*x7+2*x8+2*x9-1");
    polKatsura10.emplace_back("(t^3+t)*x0^2+2*x1^2+2*x2^2+2*x3^2+2*x4^2+2*x5^2+2*x6^2+2*x7^2+2*x8^2+2*x9^2-x0");
    polKatsura10.emplace_back("(2*t^3+2*t)*x0*x1+2*x1*x2+2*x2*x3+2*x3*x4+2*x4*x5+2*x5*x6+2*x6*x7+2*x7*x8+2*x8*x9-x1");
    polKatsura10.emplace_back("(t^3+t)*x1^2+2*x0*x2+2*x1*x3+2*x2*x4+2*x3*x5+2*x4*x6+2*x5*x7+2*x6*x8+2*x7*x9-x2");
    polKatsura10.emplace_back("(2*t^3+2*t)*x1*x2+2*x0*x3+2*x1*x4+2*x2*x5+2*x3*x6+2*x4*x7+2*x5*x8+2*x6*x9-x3");
    polKatsura10.emplace_back("(t^3+t)*x2^2+2*x1*x3+2*x0*x4+2*x1*x5+2*x2*x6+2*x3*x7+2*x4*x8+2*x5*x9-x4");
    polKatsura10.emplace_back("(2*t^3+2*t)*x2*x3+2*x1*x4+2*x0*x5+2*x1*x6+2*x2*x7+2*x3*x8+2*x4*x9-x5");
    polKatsura10.emplace_back("(t^3+t)*x3^2+2*x2*x4+2*x1*x5+2*x0*x6+2*x1*x7+2*x2*x8+2*x3*x9-x6");
    polKatsura10.emplace_back("(2*t^3+2*t)*x3*x4+2*x2*x5+2*x1*x6+2*x0*x7+2*x1*x8+2*x2*x9-x7");
    polKatsura10.emplace_back("(t^3+t)*x4^2+2*x3*x5+2*x2*x6+2*x1*x7+2*x0*x8+2*x1*x9-x8");

    // Create katsura10 ideal;
    Ideal<eltType> katsura10(polKatsura10, 10, 10000000, 12, 2, 11);
    
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
    
    // Init element-zech-prime tools
    eltType::setField(F);
    
    // Number of generator
    int nbGen;
    
    // Init monomial tools
    Monomial::initMonomial(11,13);
    
    // Create polynomial array
    vector<Polynomial<eltType>> polKatsura11;
    
    // Fill the polynomial array
    polKatsura11.emplace_back("(t^3+t)*x0+2*x1+2*x2+2*x3+2*x4+2*x5+2*x6+2*x7+2*x8+2*x9+2*x10-1");
    polKatsura11.emplace_back("(t^3+t)*x0^2+2*x1^2+2*x2^2+2*x3^2+2*x4^2+2*x5^2+2*x6^2+2*x7^2+2*x8^2+2*x9^2+2*x10^2-x0");
    polKatsura11.emplace_back("(2*t^3+2*t)*x0*x1+2*x1*x2+2*x2*x3+2*x3*x4+2*x4*x5+2*x5*x6+2*x6*x7+2*x7*x8+2*x8*x9+2*x9*x10-x1");
    polKatsura11.emplace_back("(t^3+t)*x1^2+2*x0*x2+2*x1*x3+2*x2*x4+2*x3*x5+2*x4*x6+2*x5*x7+2*x6*x8+2*x7*x9+2*x8*x10-x2");
    polKatsura11.emplace_back("(2*t^3+2*t)*x1*x2+2*x0*x3+2*x1*x4+2*x2*x5+2*x3*x6+2*x4*x7+2*x5*x8+2*x6*x9+2*x7*x10-x3");
    polKatsura11.emplace_back("(t^3+t)*x2^2+2*x1*x3+2*x0*x4+2*x1*x5+2*x2*x6+2*x3*x7+2*x4*x8+2*x5*x9+2*x6*x10-x4");
    polKatsura11.emplace_back("(2*t^3+2*t)*x2*x3+2*x1*x4+2*x0*x5+2*x1*x6+2*x2*x7+2*x3*x8+2*x4*x9+2*x5*x10-x5");
    polKatsura11.emplace_back("(t^3+t)*x3^2+2*x2*x4+2*x1*x5+2*x0*x6+2*x1*x7+2*x2*x8+2*x3*x9+2*x4*x10-x6");
    polKatsura11.emplace_back("(2*t^3+2*t)*x3*x4+2*x2*x5+2*x1*x6+2*x0*x7+2*x1*x8+2*x2*x9+2*x3*x10-x7");
    polKatsura11.emplace_back("(t^3+t)*x4^2+2*x3*x5+2*x2*x6+2*x1*x7+2*x0*x8+2*x1*x9+2*x2*x10-x8");
    polKatsura11.emplace_back("(2*t^3+2*t)*x4*x5+2*x3*x6+2*x2*x7+2*x1*x8+2*x0*x9+2*x1*x10-x9");

    // Create katsura11 ideal;
    Ideal<eltType> katsura11(polKatsura11, 11, 10000000, 13, 2, 12);
    
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
    
    // Init element-zech-prime tools
    eltType::setField(F);
    
    // Number of generator
    int nbGen;
    
    // Init monomial tools
    Monomial::initMonomial(12,14);
    
    // Create polynomial array
    vector<Polynomial<eltType>> polKatsura12;
    
    // Fill the polynomial array
    polKatsura12.emplace_back("(t^3+t)*x0+2*x1+2*x2+2*x3+2*x4+2*x5+2*x6+2*x7+2*x8+2*x9+2*x10+2*x11-1");
    polKatsura12.emplace_back("(t^3+t)*x0^2+2*x1^2+2*x2^2+2*x3^2+2*x4^2+2*x5^2+2*x6^2+2*x7^2+2*x8^2+2*x9^2+2*x10^2+2*x11^2-x0");
    polKatsura12.emplace_back("(2*t^3+2*t)*x0*x1+2*x1*x2+2*x2*x3+2*x3*x4+2*x4*x5+2*x5*x6+2*x6*x7+2*x7*x8+2*x8*x9+2*x9*x10+2*x10*x11-x1");
    polKatsura12.emplace_back("(t^3+t)*x1^2+2*x0*x2+2*x1*x3+2*x2*x4+2*x3*x5+2*x4*x6+2*x5*x7+2*x6*x8+2*x7*x9+2*x8*x10+2*x9*x11-x2");
    polKatsura12.emplace_back("(2*t^3+2*t)*x1*x2+2*x0*x3+2*x1*x4+2*x2*x5+2*x3*x6+2*x4*x7+2*x5*x8+2*x6*x9+2*x7*x10+2*x8*x11-x3");
    polKatsura12.emplace_back("(t^3+t)*x2^2+2*x1*x3+2*x0*x4+2*x1*x5+2*x2*x6+2*x3*x7+2*x4*x8+2*x5*x9+2*x6*x10+2*x7*x11-x4");
    polKatsura12.emplace_back("(2*t^3+2*t)*x2*x3+2*x1*x4+2*x0*x5+2*x1*x6+2*x2*x7+2*x3*x8+2*x4*x9+2*x5*x10+2*x6*x11-x5");
    polKatsura12.emplace_back("(t^3+t)*x3^2+2*x2*x4+2*x1*x5+2*x0*x6+2*x1*x7+2*x2*x8+2*x3*x9+2*x4*x10+2*x5*x11-x6");
    polKatsura12.emplace_back("(2*t^3+2*t)*x3*x4+2*x2*x5+2*x1*x6+2*x0*x7+2*x1*x8+2*x2*x9+2*x3*x10+2*x4*x11-x7");
    polKatsura12.emplace_back("(t^3+t)*x4^2+2*x3*x5+2*x2*x6+2*x1*x7+2*x0*x8+2*x1*x9+2*x2*x10+2*x3*x11-x8");
    polKatsura12.emplace_back("(2*t^3+2*t)*x4*x5+2*x3*x6+2*x2*x7+2*x1*x8+2*x0*x9+2*x1*x10+2*x2*x11-x9");
    polKatsura12.emplace_back("(t^3+t)*x5^2+2*x4*x6+2*x3*x7+2*x2*x8+2*x1*x9+2*x0*x10+2*x1*x11-x10");

    // Create katsura12 ideal;
    Ideal<eltType> katsura12(polKatsura12, 12, 20000000, 14, 2, 13);
    
    // Compute a reduced groebner basis;
    nbGen=katsura12.f4();
    
    // Print the reduced groebner basis into a file
    if(magma)
    {
        katsura12.printReducedGroebnerBasis("katsura12", modulo);
    }
    
    return nbGen;
}

int main (int argc, char **argv)
{
    cout << "#########################################################" << endl;
    cout << "#                 BENCHMARK GIVARO GFQ                  #" << endl;
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
    ofstream file("benchmark-givaro-gfq.txt");
    if (file)
    {
        file << "Benchmark for ideal with givaro GFq type coefficient." << endl << endl << endl;
    }
    
    start=chrono::steady_clock::now();
    nbGen=cyclic6F4(magma);
    if (file)
    {
        file << "Cyclic 6 : " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms                   (" << nbGen << " generators)" << endl << endl;
    }
    
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
    
    start=chrono::steady_clock::now();
    nbGen=katsura9F4(magma);
    if (file)
    {
        file << "Katsura 9 : " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms                   (" << nbGen << " generators)" << endl << endl;
    }
    
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
    
    //start=chrono::steady_clock::now();
    //nbGen=katsura12F4(magma);
    //if (file)
    //{
        //file << "Katsura 12 : " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms                   (" << nbGen << " generators)" << endl << endl;
    //}
    
    return 0;
}


