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
 *  \file test-polynomial.cpp
 *  \example test-polynomial.cpp
 *  \brief Polynomial regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include "../include/polynomial.h"
#include "../include/element-prime.h"

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=2;

int main (int argc, char **argv)
{
    cout << endl;
    cout << "#########################################################" << endl;
    cout << "#                     TEST POLYNOMIAL                   #" << endl;
    cout << "#########################################################" << endl << endl;
    
    
    // Init monomial tools
    Monomial::initMonomial(6,5,6,10);
    
    // Init element-prime tools
    typedef ElementPrime<long> eltType;
    ElementPrime<long>::setModulo(65537);
            
    // Test Polynomial();
    cout << "________Test Polynomial()________" << endl;
    Polynomial<eltType> p0;
    cout << "p0: " << p0 << endl <<endl;
            
    // Test Polynomial(std::string const s);
    cout << "________Test Polynomial(std::string const s)________" << endl;
    Polynomial<eltType> p1("x0+x1+x2+x3+x4+x5");
    Polynomial<eltType> p2("x0*x1+x1*x2+x2*x3+x3*x4+x0*x5+x4*x5");
    Polynomial<eltType> p3("x0*x1*x2+x1*x2*x3+x2*x3*x4+x0*x1*x5+x0*x4*x5+x3*x4*x5");
    Polynomial<eltType> p4("x0*x1*x2*x3+x1*x2*x3*x4+x0*x1*x2*x5+x0*x1*x4*x5+x0*x3*x4*x5+x2*x3*x4*x5");
    Polynomial<eltType> p5("x0*x1*x2*x3*x4+x0*x1*x2*x3*x5+x0*x1*x2*x4*x5+x0*x1*x3*x4*x5+x0*x2*x3*x4*x5+x1*x2*x3*x4*x5");
    Polynomial<eltType> p6("x0*x1*x2*x3*x4*x5-1");
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p3: " << p3 << endl;
    cout << "p4: " << p4 << endl;
    cout << "p5: " << p5 << endl;
    cout << "p6: " << p6 << endl <<endl;
    
    // Test Polynomial(Polynomial const & polynomial);
    cout << "________Test Polynomial(Polynomial const & polynomial)________" << endl;
    Polynomial<eltType> p7(p3);
    cout << "p7: " << p7 << endl << endl;
            
    // Test ~Polynomial();
    // Automatically called at the end of the scope
    
    // Test void printPolynomial (std::ostream & stream = std::cout) const;
    cout << "________Test printPolynomial (std::ostream & stream = std::cout)________" << endl;
    cout << "p7: ";
    p7.printPolynomial();
    cout << endl << endl;
            
    // Test int getNbTerm();
    cout << "________Test getNbTerm()________" << endl;
    cout << "Number of terms of p5 : " << p5.getNbTerm() << endl << endl;
    
    // Test const Term<Element> & getLT(); 
    cout << "________Test getLT()________" << endl;
    cout << "Leading term of p1: " << p1.getLT() << endl;
    cout << "Leading term of p5: " << p5.getLT() << endl << endl;
    
    // Test int getLM() const;
    cout << "________Test getLM()________" << endl;
    cout << "Number of the leading monomial of p1: " << p1.getLM() << endl;
    cout << "Number of the leading term of p5: " << p5.getLM() << endl << endl;
    
    // Test int getLC() const;
    cout << "________Test getLC()________" << endl;
    cout << "Leading coefficient of p1: " << p1.getLC() << endl;
    cout << "Leading coefficient of p5: " << p5.getLC() << endl << endl;
    
    // Test Element & getCoefficient(int numMon);
    cout << "________Test getCoefficient(int numMon)________" << endl;
    cout << "coefficient of x1*x2*x3*x4 in p4: " << p4.getCoefficient(Monomial("x1*x2*x3*x4").monomialToInt()) << endl ;
    cout << "coefficient of x1*x2 in p4: " << p4.getCoefficient(Monomial("x1*x2").monomialToInt()) << endl << endl ;
    
    // Test void deleteLT();
    cout << "________Test deleteLT()________" << endl;
    p1.deleteLT();
    cout << "p1: " << p1 << endl;
    p6.deleteLT();
    cout << "p6: " << p6 << endl;
    p6.deleteLT();
    cout << "p6: " << p6 << endl;
    p6.deleteLT();
    cout << "p6: " << p6 << endl << endl;
    
    // Test void reset();
    cout << "________Test reset()________" << endl;
    p1.reset();
    cout << "p1: " << p1 << endl << endl;
            
    // Test Polynomial & operator=(Polynomial const & polynomial);
    cout << "________Test operator=(Polynomial const & polynomial)________" << endl;
    Polynomial<eltType> p8;
    p8=p3;
    cout << "p8: " << p8 << endl << endl;
    
    // Test Polynomial & operator*=(Monomial const & monomial);
    cout << "________Test operator*=(Monomial const & monomial);________" << endl;
    p8*=Monomial("x1*x3");
    cout << "p8: " << p8 << endl << endl;
            
    // Test Polynomial & operator*=(Element element);
    cout << "________Test operator*=(Element element)________" << endl;
    p7*=eltType(-566);
    cout << "p7: " << p7 << endl << endl;
            
    // Test Polynomial & operator*=(Term<Element> const & term);
    cout << "________Test operator*=(Term<Element> const & term)________" << endl;
    Polynomial<eltType> p9(p2);
    p9*=Term<eltType>("4*x1*x3");
    cout << "p9: " << p9 << endl << endl;
    
    // Test void normalize();
    cout << "________Test normalize()________" << endl;
    p9.normalize();
    cout << "p9: " << p9 << endl << endl;
    
    // Free monomial tools
    Monomial::freeMonomial();
    
    
    return 0;
}


