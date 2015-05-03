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
int F4::NB_THREAD=min(1, omp_get_num_procs());

int main (int argc, char **argv)
{
    cout << "#########################################################" << endl;
    cout << "#                      TEST IDEAL                       #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Init element-prime tools
    typedef ElementPrime<int32_t> eltType;
    eltType::setModulo(65521);
    
    cout << "size = " << ((int)1<<(sizeof(int)*8-2)) << endl;
    
    // Init monomial tools
    Monomial::initMonomial(6,5);
    
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
    Ideal<eltType> cyclic6(polynomialArray, 6, 1000000, 10, 2, 10);
    cout << endl;
    
    // Test Polynomial<Element> buildPolynomial (Element * row, int *tab_mon, int largeur, int start, int *tau);
    cout << "________Test buildPolynomial (Element * row, int *tab_mon, int largeur, int start, int *tau)________" << endl;
    int tab_mon[13];
    Monomial tmp1;
    tmp1.allocate();
    tmp1.setMonomial("x0^1*x1^1");
    tab_mon[0]= tmp1.monomialToInt();
    tmp1.setMonomial("x1^2");
    tab_mon[1]= tmp1.monomialToInt();
    tmp1.setMonomial("x1^1*x2^1");
    tab_mon[2]= tmp1.monomialToInt();
    tmp1.setMonomial("x1^1*x3^1");
    tab_mon[3]= tmp1.monomialToInt();
    tmp1.setMonomial("x2^1*x4^1");
    tab_mon[4]= tmp1.monomialToInt();
    tmp1.setMonomial("x1^1*x4^1");
    tab_mon[5]= tmp1.monomialToInt();
    tmp1.setMonomial("x3^1*x4^1");
    tab_mon[6]= tmp1.monomialToInt();
    tmp1.setMonomial("x0^1*x5^1");
    tab_mon[7]= tmp1.monomialToInt();
    tmp1.setMonomial("x1^1*x5^1");
    tab_mon[8]= tmp1.monomialToInt();
    tmp1.setMonomial("x2^1*x5^1");
    tab_mon[9]= tmp1.monomialToInt();
    tmp1.setMonomial("x3^1*x5^1");
    tab_mon[10]= tmp1.monomialToInt();
    tmp1.setMonomial("x4^1*x5^1");
    tab_mon[11]= tmp1.monomialToInt();
    tmp1.setMonomial("x5^2");
    tab_mon[12]= tmp1.monomialToInt();
    
    int tau[13]={ 0 , 2 , 3 , 4 , 5 , 6 , 7 , 1 , 8 , 9 , 10 , 11 , 12 };
    
    Matrix<eltType> Mat("../data/M_text_basic1_cyclic6.txt");
    cout << Mat << endl;
    
    cout << "Polynomial row 0: " << cyclic6.buildPolynomial(Mat.getRow(0), tab_mon, 13, 0, tau) << endl;
    cout << "Polynomial row 1: " << cyclic6.buildPolynomial(Mat.getRow(1), tab_mon, 13, 0, tau) << endl;
    cout << "Polynomial row 2: " << cyclic6.buildPolynomial(Mat.getRow(2), tab_mon, 13, 0, tau) << endl << endl;
    
    // Test void buildPolynomial (Polynomial<Element> & polynomial, Element * row, int *tab_mon, int largeur, int start, int *tau);
    cout << "________Test buildPolynomial (Polynomial<Element> & polynomial, Element * row, int *tab_mon, int largeur, int start, int *tau)________" << endl;
    
    Polynomial<eltType> p1("3*x1");
    Polynomial<eltType> p2, p3;
    cyclic6.buildPolynomial(p1, Mat.getRow(0), tab_mon, 13, 0, tau);
    cyclic6.buildPolynomial(p2, Mat.getRow(1), tab_mon, 13, 0, tau);
    cyclic6.buildPolynomial(p3, Mat.getRow(2), tab_mon, 13, 0, tau);
    cout << "p1 : " << p1 << endl;
    cout << "p2 : " << p2 << endl;
    cout << "p3 : " << p3 << endl << endl;
    
    delete[] Mat.getSigma();
    delete[] Mat.getTau();
    delete[] Mat.getStartTail();
    delete[] Mat.getEndCol();
    
    // Test void f4();
    cout << "________Test f4()________" << endl;
    cyclic6.f4();
    cout << endl;
    
    // Test void printTaggedPolynomialArray();
    cout << "________Test void printTaggedPolynomialArray()________" << endl;
    cout << "cyclic6: " << endl;
    cyclic6.printReducedGroebnerBasis("cyclic6", 65521);
    cout << endl << endl;
    
    // Test std::vector<std::string> getReducedGroebnerBasis() const;
    cout << "________Test std::vector<std::string> getReducedGroebnerBasis()________" << endl;
    vector<string> basis=cyclic6.getReducedGroebnerBasis();
    for(int i=0; i < basis.size(); i++)
    {
        cout << basis[i] << endl;
    }
    cout << endl << endl;
    
    // Free monomial
    tmp1.erase();
    
    return 0;
}


