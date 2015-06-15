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
 *  \file test-element-givaro.cpp
 *  \example test-element-givaro.cpp
 *  \brief ElementGivaro regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include <vector>
#include "../f4/include/element-givaro.h"

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=2;

int main (int argc, char **argv)
{
    cout << endl;
    cout << "#########################################################" << endl;
    cout << "#                  TEST ELEMENT GIVARO                  #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Init element-givaro tools
    //typedef Givaro::Modular<Givaro::Log16> Field;
    //int modulo=8209;

    typedef Givaro::Modular<Givaro::Integer> Field;
    Givaro::Integer modulo(Givaro::Integer("115792089237316195423570985008687907853269984665640564039457584007913129640233"));

    Field F(modulo);
    typedef ElementGivaro<Field> eltType;
    eltType::setField(F);
    
    // Test ElementGivaro & operator=(int element);
    cout << "________Test operator=(int element)________" << endl;
    eltType e1;
    e1=123;
    cout << "e1 = " << e1 << endl << endl;
    
    // Test ElementGivaro & operator=(typename Field::Element element);
    cout << "________Test operator=(typename Field::Element element)________" << endl;
    eltType e2;
    e2=e1._element;
    cout << "e2 = " << e2 << endl << endl;
    
    // Test ElementGivaro & operator*=(ElementGivaro const & mult);
    cout << "________Test operator*=(ElementGivaro const & mult)________" << endl; 
    e2*=e1;
    cout << "e2 = " << e2 << endl << endl;
    
    // Test ElementGivaro & operator-=(ElementGivaro const & element);
    cout << "________Test operator-=(ElementGivaro const & element)________" << endl;
    e2-=e1;
    cout << "e2 = " << e2 << endl << endl;
    
    // Test ElementGivaro<Field> & addMult(ElementGivaro<Field> const & element, ElementGivaro<Field> const & mult);
    cout << "________Test addMult(ElementGivaro<Field> const & element, ElementGivaro<Field> const & mult)________" << endl;
    eltType e3;
    e1=10;
    e2=20;
    e3=5;
    e3.addMult(e1,e2);
    cout << "e3 = " << e3 << endl << endl;
    
    // Test ElementGivaro<Field> & inverse();
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
    
    // Test operator * (ElementGivaro<Field> const & element1, ElementGivaro<Field> const & element2);
    cout << "________Test operator * (ElementGivaro<Field> const & element1, ElementGivaro<Field> const & element2)________" << endl;
    cout << "e1 *e2 = " << (e1*e2) << endl << endl;
    
    // Test operator - (ElementGivaro<Field> const & element);
    cout << "________Test operator - (ElementGivaro<Field> const & element)________" << endl;
    cout << "-e3 = " << (-e3) << endl << endl;
    
    return 0;
}
