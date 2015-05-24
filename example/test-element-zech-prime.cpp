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
 *  \file test-element-zech-prime.cpp
 *  \example test-element-zech-prime.cpp
 *  \brief ElementZechPrime regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include <vector>
#include "../include/element-zech-prime.h"

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=2;

int main (int argc, char **argv)
{
    cout << endl;
    cout << "#########################################################" << endl;
    cout << "#              TEST ELEMENT ZECH PRIME                  #" << endl;
    cout << "#########################################################" << endl << endl;
    
    typedef Givaro::Modular<Givaro::Log16, Givaro::Log16> Field;
    int modulo=8209;
    Field F(modulo);
    typedef ElementZechPrime<Field> eltType;
    eltType::setField(F);
    
    // Test ElementZechPrime & operator=(int element);
    cout << "________Test operator=(int element)________" << endl;
    eltType e1;
    e1=123;
    cout << "e1 = " << e1 << endl << endl;
    
    // Test ElementZechPrime & operator=(typename Field::Element element);
    cout << "________Test operator=(typename Field::Element element)________" << endl;
    eltType e2;
    e2=e1._element;
    cout << "e2 = " << e2 << endl << endl;
    
    // Test ElementZechPrime & operator*=(ElementZechPrime const & mult);
    cout << "________Test operator*=(ElementZechPrime const & mult)________" << endl; 
    e2*=e1;
    cout << "e2 = " << e2 << endl << endl;
    
    // Test ElementZechPrime & operator-=(ElementZechPrime const & element);
    cout << "________Test operator-=(ElementZechPrime const & element)________" << endl;
    e2-=e1;
    cout << "e2 = " << e2 << endl << endl;
    
    // Test ElementZechPrime<Field> & addMult(ElementZechPrime<Field> const & element, ElementZechPrime<Field> const & mult);
    cout << "________Test addMult(ElementZechPrime<Field> const & element, ElementZechPrime<Field> const & mult)________" << endl;
    eltType e3;
    e1=10;
    e2=20;
    e3=5;
    e3.addMult(e1,e2);
    cout << "e3 = " << e3 << endl << endl;
    
    // Test ElementZechPrime<Field> & inverse();
    cout << "________Test inverse()________" << endl;
    e3.inverse();
    cout << "e3 = " << e3 << endl << endl;
    
    // Test void printElementPrime (std::ostream & stream) const;
    cout << "________Test printElementPrime (std::ostream & stream)________" << endl;
    cout << "e3: ";
    e3.printElementPrime(cout);
    cout << endl << endl;
    
    // Test bool isZero() const;
    cout << "________Test isZero()________" << endl;
    cout << "e3==0: " << e3.isZero() << endl << endl;
    
    // Test bool isOne() const;
    cout << "________Test isOne()________" << endl;
    cout << "e3==1: " << e3.isOne() << endl << endl;
    
    // Test void setZero();
    cout << "________Test setZero()________" << endl;
    e3.setZero();
    cout << "e3==0: " << e3.isZero() << endl << endl;
    
    // Test void setOne();
    cout << "________Test setOne()________" << endl;
    e3.setOne();
    cout << "e3==1: " << e3.isOne() << endl << endl;
    
    // Test operator * (ElementZechPrime<Field> const & element1, ElementZechPrime<Field> const & element2);
    cout << "________Test operator * (ElementZechPrime<Field> const & element1, ElementZechPrime<Field> const & element2)________" << endl;
    cout << "e1 *e2 = " << (e1*e2) << endl << endl;
    
    // Test operator - (ElementZechPrime<Field> const & element);
    cout << "________Test operator - (ElementZechPrime<Field> const & element)________" << endl;
    cout << "-e3 = " << (-e3) << endl << endl;
    
    return 0;
}
