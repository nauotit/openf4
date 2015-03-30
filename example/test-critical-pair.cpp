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
#include <vector>
#include "../include/critical-pair.h"

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=2;

int main (int argc, char **argv)
{
    cout << endl;
    cout << "#########################################################" << endl;
    cout << "#                  TEST CRITICAL PAIR                   #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Init element-prime tools
    typedef ElementPrime<long> eltType;
    ElementPrime<long>::setModulo(65537);
    
    // Init monomial tools
    MonomialArray monArray(6,10000000,10, 2, 10);
    Term<eltType>::setMonomialArray(&monArray);
    TaggedPolynomial<eltType>::setMonomialArray(&monArray);
    CriticalPair<eltType>::setMonomialArray(&monArray);
    cout << endl;
    
    // Create tagged polynomial array
    vector<TaggedPolynomial<eltType>> List;
    
    // Test static void setTaggedPolynomialArray(vector<TaggedPolynomial<Element>> * taggedPolynomialArray);
    cout << "________Test setTaggedPolynomialArray(vector<TaggedPolynomial<Element>> * taggedPolynomialArray)________" << endl;
    CriticalPair<eltType>::setTaggedPolynomialArray(&List);
    cout << "size of the tagged polynomial array: " << CriticalPair<eltType>::getSizeTaggedPolynomialArray() << endl << endl;
    
    // Fill the tagged polynomial array
    List.emplace_back(Polynomial<eltType>("x0+x1+x2+x3+x4+x5"));
    List.emplace_back(Polynomial<eltType>("x0*x1+x1*x2+x2*x3+x3*x4+x0*x5+x4*x5"));
    List.emplace_back(Polynomial<eltType>("x0*x1*x2+x1*x2*x3+x2*x3*x4+x0*x1*x5+x0*x4*x5+x3*x4*x5"));
    List.emplace_back(Polynomial<eltType>("x0*x1*x2*x3+x1*x2*x3*x4+x0*x1*x2*x5+x0*x1*x4*x5+x0*x3*x4*x5+x2*x3*x4*x5"));
    List.emplace_back(Polynomial<eltType>("x3+x1*x2*x3*x4+x2*x5+x4*x5+x2*x3*x4*x5"));
    
    // Test static int getSizeTaggedPolynomialArray();
    cout << "________Test getSizeTaggedPolynomialArray()________" << endl;
    cout << "size of the tagged polynomial array: " << CriticalPair<eltType>::getSizeTaggedPolynomialArray() << endl << endl;
    
    // Test CriticalPair();
    cout << "________Test CriticalPair()________" << endl;
    CriticalPair<eltType> cp1;
    cout << "cp1: " << cp1 << endl << endl;
    
    // Test CriticalPair(TaggedPolynomial<Element> const & p1, TaggedPolynomial<Element> const & p2);
    cout << "________Test CriticalPair(TaggedPolynomial<Element> const & p1, TaggedPolynomial<Element> const & p2)________" << endl;
    CriticalPair<eltType> cp2(0,1);
    CriticalPair<eltType> cp3(1,3);
    CriticalPair<eltType> cp4(2,3);
    cout << "cp2: " << cp2 << endl;
    cout << "cp3: " << cp3 << endl;
    cout << "cp4: " << cp4 << endl << endl;
    
    // Test int getP1();
    cout << "________Test getP1()________" << endl;
    cout << cp4.getP1() << endl << endl;
            
    // Test int getP2();
    cout << "________Test getP2()________" << endl;
    cout << cp4.getP2() << endl << endl;
            
    // Test int getLcm();
    cout << "________Test getLcm()________" << endl;
    cout << cp4.getLcm() << endl << endl;
            
    // Test int getU1;
    cout << "________Test getU1()________" << endl;
    cout << cp4.getU1() << endl << endl;
            
    // Test int getU2;
    cout << "________Test getU2()________" << endl;
    cout << cp4.getU2() << endl << endl;
    
    // Test int getDegree() const;
    cout << "________Test getDegree()________" << endl;
    cout << cp4.getDegree() << endl << endl;
    
    // Test bool setCriticalPair(int p1, int p2);
    cout << "________Test setCriticalPair(int p1, int p2)________" << endl;
    cout << "cp1: " << cp1 << endl;
    cout << cp1.setCriticalPair(2,3) << endl;
    cout << "cp1: " << cp1 << endl;
    cout << cp1.setCriticalPair(2,4) << endl; 
    cout << "cp1: " << cp1 << endl << endl;
    
    // Test void printCriticalPair (std::ostream & stream = std::cout) const;
    cout << "________Test printCriticalPair (std::ostream & stream = std::cout)________" << endl;
    cout << "cp1 :";
    cp1.printCriticalPair(cout);
    cout << endl;
    cout << "cp2 :";
    cp2.printCriticalPair(cout);
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
    cout << "________Test copy constructor________" << endl;
    CriticalPair<eltType> cp5(cp4);
    cout << "cp5: " << cp5 << endl << endl;
    
    // Test operator =
    cout << "________Test operator =________" << endl;
    cp4=cp1;
    cout << "cp4: " << cp4 << endl << endl;

    return 0;
}


