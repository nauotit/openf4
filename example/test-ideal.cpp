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
 *  \file test-ideal.cpp
 *  \example test-ideal.cpp
 *  \brief Ideal regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include "../include/ideal.h"

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=3;

int main (int argc, char **argv)
{
    cout << "#########################################################" << endl;
    cout << "#                      TEST IDEAL                       #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Init element-prime tools
    typedef ElementPrime<long> eltType;
    ElementPrime<long>::setModulo(65537);
    
    // Init monomial tools
    Monomial::initMonomial(6,5,5,10);
    
    // Create polynomial array
    vector<Polynomial<eltType>> polynomialArray;
    
    // Fill the polynomial array
    polynomialArray.emplace_back("x0+x1+x2+x3+x4+x5");
    polynomialArray.emplace_back("x0*x1+x1*x2+x2*x3+x3*x4+x0*x5+x4*x5");
    polynomialArray.emplace_back("x0*x1*x2+x1*x2*x3+x2*x3*x4+x0*x1*x5+x0*x4*x5+x3*x4*x5");
    polynomialArray.emplace_back("x0*x1*x2*x3+x1*x2*x3*x4+x0*x1*x2*x5+x0*x1*x4*x5+x0*x3*x4*x5+x2*x3*x4*x5");
    polynomialArray.emplace_back("x0*x1*x2*x3*x4+x0*x1*x2*x3*x5+x0*x1*x2*x4*x5+x0*x1*x3*x4*x5+x0*x2*x3*x4*x5+x1*x2*x3*x4*x5");
    polynomialArray.emplace_back("x0*x1*x2*x3*x4*x5-1");

    // Test Ideal(int nbVariable, int maxDegree, int deg1, int deg2, std::vector<Polynomial<Element>> & polynomialArray);
    cout << "________Test Ideal(std::vector<Polynomial<Element>> & polynomialArray)________" << endl;
    Ideal<eltType> cyclic6(polynomialArray);
    cout << endl;
    
    // Test Polynomial<Element> buildPolynomial (Element * row, int *tab_mon, int largeur, int start, int *tau);
    cout << "________Test buildPolynomial (Element * row, int *tab_mon, int largeur, int start, int *tau)________" << endl;
    int tab_mon[13];
    tab_mon[0]= Monomial("x0^1*x1^1").monomialToInt();
    tab_mon[1]= Monomial("x1^2").monomialToInt();
    tab_mon[2]= Monomial("x1^1*x2^1").monomialToInt();
    tab_mon[3]= Monomial("x1^1*x3^1").monomialToInt();
    tab_mon[4]= Monomial("x2^1*x4^1").monomialToInt();
    tab_mon[5]= Monomial("x1^1*x4^1").monomialToInt();
    tab_mon[6]= Monomial("x3^1*x4^1").monomialToInt();
    tab_mon[7]= Monomial("x0^1*x5^1").monomialToInt();
    tab_mon[8]= Monomial("x1^1*x5^1").monomialToInt();
    tab_mon[9]= Monomial("x2^1*x5^1").monomialToInt();
    tab_mon[10]= Monomial("x3^1*x5^1").monomialToInt();
    tab_mon[11]= Monomial("x4^1*x5^1").monomialToInt();
    tab_mon[12]= Monomial("x5^2").monomialToInt();
    
    int tau[13]={ 0 , 2 , 3 , 4 , 5 , 6 , 7 , 1 , 8 , 9 , 10 , 11 , 12 };
    
    Matrix<eltType> Mat("../data/M_text_basic1_cyclic6.txt");
    cout << Mat << endl;
    
    cout << "Polynomial row 0: " << cyclic6.buildPolynomial(Mat.getRow(0), tab_mon, 13, 0, tau) << endl;
    cout << "Polynomial row 1: " << cyclic6.buildPolynomial(Mat.getRow(1), tab_mon, 13, 0, tau) << endl;
    cout << "Polynomial row 2: " << cyclic6.buildPolynomial(Mat.getRow(2), tab_mon, 13, 0, tau) << endl << endl;
    
    // Test DEBUG *
    TaggedPolynomial<eltType> tp(Polynomial<eltType>("1*x2^3*x4^1*x5^4 + 56886*x1^1*x2^1*x4^2*x5^4 + 9618*x2^2*x4^2*x5^4 + 9966*x1^1*x3^1*x4^2*x5^4 + 14561*x2^1*x3^1*x4^2*x5^4 + 53889*x3^2*x4^2*x5^4 + 35066*x1^1*x4^3*x5^4 + 44683*x2^1*x4^3*x5^4 + 18048*x3^1*x4^3*x5^4 + 35066*x4^4*x5^4 + 57861*x1^1*x2^1*x3^1*x5^5 + 45316*x2^2*x3^1*x5^5 + 45316*x2^1*x3^2*x5^5 + 27413*x1^1*x2^1*x4^1*x5^5 + 44736*x2^2*x4^1*x5^5 + 10568*x1^1*x3^1*x4^1*x5^5 + 63076*x2^1*x3^1*x4^1*x5^5 + 10568*x3^2*x4^1*x5^5 + 22305*x1^1*x4^2*x5^5 + 11119*x2^1*x4^2*x5^5 + 61073*x3^1*x4^2*x5^5 + 39103*x4^3*x5^5 + 27897*x1^1*x2^1*x5^6 + 20221*x2^2*x5^6 + 20221*x1^1*x3^1*x5^6 + 27897*x2^1*x3^1*x5^6 + 20221*x3^2*x5^6 + 49510*x1^1*x4^1*x5^6 + 48929*x2^1*x4^1*x5^6 + 34983*x3^1*x4^1*x5^6 + 54493*x4^2*x5^6 + 12545*x1^1*x5^7 + 32766*x2^1*x5^7 + 32766*x3^1*x5^7 + 4194*x4^1*x5^7 + 12545*x5^8 + 37336*x1^1*x2^1 + 21968*x2^2 + 51283*x1^1*x3^1 + 4573*x2^1*x3^1 + 2097*x3^2 + 48702*x1^1*x4^1 + 64395*x2^1*x4^1 + 44531*x3^1*x4^1 + 11756*x4^2 + 56737*x1^1*x5^1 + 2713*x2^1*x5^1 + 31641*x3^1*x5^1 + 31630*x4^1*x5^1 + 48100*x5^2"));
    tp.setSimplyrule(2, 405);
    tp.setSimplyrule(3, 400);
    tp.setSimplyrule(4, 385);
    cout << "tp: " << tp << endl << endl;
    Monomial mon("x2^1");
    cout << "mon: " << mon << endl << endl;
    
    cout << "mon*tp: " << (tp*mon) << endl << endl;
    
    TaggedPolynomial<eltType> tpempty;
    cout << "tpempty: " << tpempty << endl;
    tpempty=tp*mon;
    cout << "tpempty: " << tpempty << endl << endl;
    
    // Test void f4();
    cout << "________Test f4()________" << endl;
    cyclic6.f4();
    cout << endl;
    
    // Test void printTaggedPolynomialArray();
    cout << "cyclic6: " << endl;
    cyclic6.printTaggedPolynomialArray();
    cout << endl << endl;
    
    // Free monomial tools
    Monomial::freeMonomial();
    
    return 0;
}


