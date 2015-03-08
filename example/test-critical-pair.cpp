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
 *  \file test-critical-pair.cpp
 *  \example test-critical-pair.cpp
 *  \brief CriticalPair regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include "../include/critical-pair.h"

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=2;

int main (int argc, char **argv)
{
    // Init monomial tools
    Monomial::initMonomial(6,5,6,10);
    
    // Init tagged polynomial array
    TaggedPolynomial<int>::insertTaggedPolynomialArray(TaggedPolynomial<int>(Polynomial<int>("x0+x1+x2+x3+x4+x5")));
    TaggedPolynomial<int>::insertTaggedPolynomialArray(TaggedPolynomial<int>(Polynomial<int>("x0*x1+x1*x2+x2*x3+x3*x4+x0*x5+x4*x5")));
    TaggedPolynomial<int>::insertTaggedPolynomialArray(TaggedPolynomial<int>(Polynomial<int>("x0*x1*x2+x1*x2*x3+x2*x3*x4+x0*x1*x5+x0*x4*x5+x3*x4*x5")));
    TaggedPolynomial<int>::insertTaggedPolynomialArray(TaggedPolynomial<int>(Polynomial<int>("x0*x1*x2*x3+x1*x2*x3*x4+x0*x1*x2*x5+x0*x1*x4*x5+x0*x3*x4*x5+x2*x3*x4*x5")));
    
    // Test CriticalPair();
    cout << "________Test CriticalPair()________" << endl;
    CriticalPair<int> cp1;
    cout << "cp1: " << cp1 << endl << endl;
    
    // Test CriticalPair(TaggedPolynomial<Element> const & p1, TaggedPolynomial<Element> const & p2);
    cout << "________Test CriticalPair(TaggedPolynomial<Element> const & p1, TaggedPolynomial<Element> const & p2)________" << endl;
    CriticalPair<int> cp2(0,1);
    CriticalPair<int> cp3(1,3);
    CriticalPair<int> cp4(2,3);
    cout << "cp2: " << cp2 << endl;
    cout << "cp3: " << cp3 << endl;
    cout << "cp4: " << cp4 << endl << endl;
    
    // Test void printCriticalPair (std::ostream & stream = std::cout) const;
    cout << "________Test printCriticalPair (std::ostream & stream = std::cout)________" << endl;
    cout << "cp1 :";
    cp1.printCriticalPair();
    cout << endl;
    cout << "cp2 :";
    cp2.printCriticalPair();
    cout << endl << endl;
    
    // Test int compareCriticalPair (CriticalPair const & criticalPair) const;
    cout << "________Test compareCriticalPair (CriticalPair const & criticalPair)________" << endl;
    cout << cp2.compareCriticalPair(cp3) << endl;
    cout << cp3.compareCriticalPair(cp3) << endl;
    cout << cp3.compareCriticalPair(cp2) << endl << endl;
    
    // Test bool operator==(CriticalPair<Element> const & criticalPair1, CriticalPair<Element> const & criticalPair2);
    cout << "________Test operator==(CriticalPair<Element> const & criticalPair1, CriticalPair<Element> const & criticalPair2)________" << endl;
    cout << "cp2 == cp3: " << (cp2==cp3) << endl;
    cout << "cp3 == cp4: " << (cp3==cp4) << endl;
    cout << "cp3 == cp3: " << (cp3==cp3) << endl << endl;
    
    // Test bool operator>(CriticalPair<Element> const & criticalPair1, CriticalPair<Element> const & criticalPair2);
    cout << "________Test operator>(CriticalPair<Element> const & criticalPair1, CriticalPair<Element> const & criticalPair2)________" << endl;
    cout << "cp2 > cp3: " << (cp2>cp3) << endl;
    cout << "cp3 > cp4: " << (cp3>cp4) << endl;
    cout << "cp3 > cp3: " << (cp3>cp3) << endl << endl;
    
    // Test bool operator>=(CriticalPair<Element> const & criticalPair1, CriticalPair<Element> const & criticalPair2);
    cout << "________Test operator>=(CriticalPair<Element> const & criticalPair1, CriticalPair<Element> const & criticalPair2)________" << endl;
    cout << "cp2 >= cp3: " << (cp2>=cp3) << endl;
    cout << "cp3 >= cp4: " << (cp3>=cp4) << endl;
    cout << "cp3 >= cp3: " << (cp3>=cp3) << endl << endl;
    
    // Test bool operator<(CriticalPair<Element> const & criticalPair1, CriticalPair<Element> const & criticalPair2);
    cout << "________Test operator<(CriticalPair<Element> const & criticalPair1, CriticalPair<Element> const & criticalPair2)________" << endl;
    cout << "cp2 < cp3: " << (cp2<cp3) << endl;
    cout << "cp3 < cp4: " << (cp3<cp4) << endl;
    cout << "cp3 < cp3: " << (cp3<cp3) << endl << endl;
    
    // Test bool operator<=(CriticalPair<Element> const & criticalPair1, CriticalPair<Element> const & criticalPair2);
    cout << "________Test operator<=(CriticalPair<Element> const & criticalPair1, CriticalPair<Element> const & criticalPair2)________" << endl;
    cout << "cp2 <= cp3: " << (cp2<=cp3) << endl;
    cout << "cp3 <= cp4: " << (cp3<=cp4) << endl;
    cout << "cp3 <= cp3: " << (cp3<=cp3) << endl << endl;
    
    // Test copy constructor
    cout << "________Test generated copy constructor________" << endl;
    CriticalPair<int> cp5(cp4);
    cout << "cp5: " << cp5 << endl << endl;
    
    // Test operator =
    cout << "________Test generated operator=________" << endl;
    cp5=cp1;
    cout << "cp5: " << cp5 << endl << endl;
    
    
    // Free monomial tools
    Monomial::freeMonomial();

    return 0;
}


