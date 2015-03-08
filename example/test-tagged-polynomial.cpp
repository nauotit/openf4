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
 *  \file test-tagged-polynomial.cpp
 *  \example test-tagged-polynomial.cpp
 *  \brief TaggedPolynomial regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include "../include/tagged-polynomial.h"

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=2;

int main (int argc, char **argv)
{
    // Init monomial tools
    Monomial::initMonomial(6,5,6,10);
    
    // Test TaggedPolynomial();
    cout << "________Test TaggedPolynomial()________" << endl;
    TaggedPolynomial<int> tp1;
    cout << "tp1: " << tp1 << endl << endl;
    
    // Test TaggedPolynomial(Polynomial<Element> const & polynomial);
    cout << "________Test TaggedPolynomial(Polynomial<Element> & polynomial)________" << endl;
    TaggedPolynomial<int> tp2(Polynomial<int>("x0+x1+x2+x3+x4+x5"));
    TaggedPolynomial<int> tp3(Polynomial<int>("x0*x1+x1*x2+x2*x3+x3*x4+x0*x5+x4*x5"));
    cout << "tp2: " << tp2 << endl;
    cout << "tp3: " << tp3 << endl << endl;
    
    // Test TaggedPolynomial(TaggedPolynomial const & taggedPolynomial);
    cout << "________Test TaggedPolynomial(TaggedPolynomial const & taggedPolynomial)________" << endl;
    TaggedPolynomial<int> tp4(tp3);
    cout << "tp4: " << tp4 << endl << endl;
    
    // Test void printTaggedPolynomial(std::ostream & stream = std::cout) const;
    cout << "________Test printTaggedPolynomial (std::ostream & stream = std::cout)________" << endl;
    cout << "tp2 :";
    tp2.printTaggedPolynomial();
    cout << endl << endl;
    
    // Test int compareTaggedPolynomial(TaggedPolynomial const & taggedPolynomial) const;
    cout << "________Test compareTaggedPolynomial(TaggedPolynomial const & taggedPolynomial)________" << endl;
    cout << tp2.compareTaggedPolynomial(tp3) << endl;
    cout << tp3.compareTaggedPolynomial(tp3) << endl;
    cout << tp3.compareTaggedPolynomial(tp2) << endl << endl;
    
    // Test TaggedPolynomial & operator=(TaggedPolynomial const & taggedPolynomial);
    cout << "________Test operator=(TaggedPolynomial const & taggedPolynomial)________" << endl;
    tp1=tp4;
    cout << "tp1: " << tp1 << endl << endl;
    
    // Test bool operator==(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2);
    cout << "________Test operator==(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2)________" << endl;
    cout << "tp2==tp3 :" << (tp2==tp3) << endl;
    cout << "tp3==tp3 :" << (tp3==tp3) << endl << endl;
    
    // Test bool operator>(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2);
    cout << "________Test operator>(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2)________" << endl;
    cout << "tp2>tp3 :" << (tp2>tp3) << endl;
    cout << "tp3>tp3 :" << (tp3>tp3) << endl;
    cout << "tp3>tp2 :" << (tp3>tp2) << endl << endl;
    
    // Test bool operator>=(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2);
    cout << "________Test operator>=(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2)________" << endl;
    cout << "tp2>=tp3 :" << (tp2>=tp3) << endl;
    cout << "tp3>=tp3 :" << (tp3>=tp3) << endl;
    cout << "tp3>=tp2 :" << (tp3>=tp2) << endl << endl;
    
    // Test bool operator<(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2);
    cout << "________Test operator<(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2)________" << endl;
    cout << "tp2<tp3 :" << (tp2<tp3) << endl;
    cout << "tp3<tp3 :" << (tp3<tp3) << endl;
    cout << "tp3<tp2 :" << (tp3<tp2) << endl << endl;
    
    // Test bool operator<=(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2);
    cout << "________Test operator<=(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2)________" << endl;
    cout << "tp2<=tp3 :" << (tp2<=tp3) << endl;
    cout << "tp3<=tp3 :" << (tp3<=tp3) << endl;
    cout << "tp3<=tp2 :" << (tp3<=tp2) << endl << endl;
    
    // Test static int getSizeTaggedPolynomialArray();
    cout << "________Test getSizeTaggedPolynomialArray()________" << endl;
    cout << "size of TAGGED_POLYNOMIAL_ARRAY: " << TaggedPolynomial<int>::getSizeTaggedPolynomialArray() << endl << endl;
    
    // Test static void insertTaggedPolynomialArray(TaggedPolynomial<Element> & taggedPolynomial);
    cout << "________Test insertTaggedPolynomialArray(TaggedPolynomial<Element> & taggedPolynomial)________" << endl;
    TaggedPolynomial<int>::insertTaggedPolynomialArray(tp1);
    TaggedPolynomial<int>::insertTaggedPolynomialArray(tp2);
    TaggedPolynomial<int>::insertTaggedPolynomialArray(tp3);
    cout << "size of TAGGED_POLYNOMIAL_ARRAY: " << TaggedPolynomial<int>::getSizeTaggedPolynomialArray() << endl << endl;
    
    // Test static TaggedPolynomial<Element> const & getTaggedPolynomialArray(int numTaggedPolynomial);
    cout << "________Test TaggedPolynomial<Element> const & getTaggedPolynomialArray(int numTaggedPolynomial)________" << endl;
    cout << "TAGGED_POLYNOMIAL_ARRAY[0]: " << TaggedPolynomial<int>::getTaggedPolynomialArray(0) << endl;
    cout << "TAGGED_POLYNOMIAL_ARRAY[1]: " << TaggedPolynomial<int>::getTaggedPolynomialArray(1) << endl;
    cout << "TAGGED_POLYNOMIAL_ARRAY[2]: " << TaggedPolynomial<int>::getTaggedPolynomialArray(2) << endl << endl;
    
    // Free monomial tools
    Monomial::freeMonomial();
    
    return 0;
}


