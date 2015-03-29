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
 *  \file test-element-prime.cpp
 *  \example test-element-prime.cpp
 *  \brief ElementPrime regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include <vector>
#include "../include/element-prime.h"

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=2;

int main (int argc, char **argv)
{
    cout << endl;
    cout << "#########################################################" << endl;
    cout << "#                  TEST ELEMENT PRIME                   #" << endl;
    cout << "#########################################################" << endl << endl;
    
    typedef long baseType;
    
    // Test static void setModulo(unsigned int modulo);
    cout << "________Test setModulo(unsigned int modulo)________" << endl;
    ElementPrime<baseType>::setModulo(65537);
    cout << endl;
            
    // Test static unsigned int getModulo();
    cout << "________Test getModulo()________" << endl;
    cout << "Modulo: " << ElementPrime<baseType>::getModulo() << endl << endl;
    
    // Test ElementPrime(baseType element);
    cout << "________Test ElementPrime(baseType element)________" << endl;
    ElementPrime<baseType> elt1=100;
    ElementPrime<baseType> elt2=1000;
    ElementPrime<baseType> elt3=10000;
    ElementPrime<baseType> elt4=100000;
    cout << "elt1: " << elt1 << endl;
    cout << "elt2: " << elt2 << endl;
    cout << "elt3: " << elt3 << endl;
    cout << "elt4: " << elt4 << endl << endl;
    
    // Test void printElementPrime (std::ostream & stream = std::cout) const
    cout << "________Test printElementPrime (std::ostream & stream = std::cout)________" << endl;
    cout << "elt4: ";
    elt4.printElementPrime(cout);
    cout << endl << endl;
    
    // Test void modulo ();
    cout << "________Test modulo ()________" << endl;
    ElementPrime<baseType> e0(4);
    e0*=elt3;
    cout << "e0 = " << e0 << endl;
    e0.modulo();
    cout << "e0.modulo() = " << e0 << endl << endl;
    
    // Test ElementPrime<baseType>::addMult(ElementPrime<baseType> & element, ElementPrime<baseType> & mult)
    cout << "________Test addMult(ElementPrime<baseType> & element, ElementPrime<baseType> & mult)________" << endl;
    e0.addMult(elt3, elt1);
    cout << "e0 = " << e0 << endl << endl; 

    // Test void inverse ();
    cout << "________Test inverse ()________" << endl;
    cout << "inverse of elt1: " << elt1.inverse() << endl;
    cout << "inverse of elt2: " << elt2.inverse() << endl;
    cout << "inverse of elt3: " << elt3.inverse() << endl;
    cout << "inverse of elt4: " << elt4.inverse() << endl << endl;
    
    // Test ElementPrime & operator=(ElementPrime const & element);
    cout << "________Test operator=(ElementPrime const & element)________" << endl;
    elt1=elt2;
    cout << "elt1: " << elt1 << endl << endl;
            
    // Test ElementPrime & operator=(baseType element);
    cout << "________Test operator=(baseType element)________" << endl;
    elt1=-1;
    cout << "elt1: " << elt1 << endl << endl;
            
    // Test ElementPrime & operator+=(ElementPrime const & element); 
    cout << "________Test operator+=(ElementPrime const & element)________" << endl;
    elt1+=200;
    cout << "elt1: " << elt1 << endl << endl;
            
    // Test ElementPrime & operator-=(ElementPrime const & element); 
    cout << "________Test operator-=(ElementPrime const & element)________" << endl;
    elt1-=2000;
    cout << "elt1: " << elt1 << endl << endl;
            
    // Test ElementPrime & operator*=(ElementPrime const & element); 
    cout << "________Test operator*=(ElementPrime const & element)________" << endl;
    ElementPrime<baseType> elt5=elt1.inverse();
    ElementPrime<baseType> elt6=elt2.inverse();
    ElementPrime<baseType> elt7=elt3.inverse();
    ElementPrime<baseType> elt8=elt4.inverse();
    elt5*=elt1;
    elt6*=elt2;
    elt7*=elt3;
    elt8*=elt4;
    cout << "elt5: " << elt5 << endl;
    cout << "elt6: " << elt6 << endl;
    cout << "elt7: " << elt7 << endl;
    cout << "elt8: " << elt8 << endl << endl;
    
    vector <ElementPrime<baseType> > vec;
    for(size_t i=1; i<100002; i++)
    {
        if(i!=ElementPrime<baseType>::getModulo())
        {
            vec.push_back(ElementPrime<baseType>(i*1000));
        }
    }
    clock_t start = clock();
    for(size_t i=0; i< vec.size(); i++)
    {
        vec[i]=vec[i].inverse();
    }
    cout << "time to inverse " << vec.size() << " elements: " << (clock() - start) << endl << endl;
    
            
    // Test ElementPrime & operator/=(ElementPrime element); 
    cout << "________Test operator/=(ElementPrime element)________" << endl;
    ElementPrime<baseType> elt9=elt1;
    elt9/=1000;
    cout << "elt1: " << elt1 << endl;
    cout << "elt9: " << elt9 << endl << endl;
    
    // Test ElementPrime<baseType> operator * (ElementPrime<baseType> const & element1, ElementPrime<baseType> const & element2);
    cout << "________Test operator * (ElementPrime<baseType> const & element1, ElementPrime<baseType> const & element2)________" << endl;
    cout << "elt9*1000: " << (elt9*ElementPrime<baseType>(1000)) << endl << endl; 
    
    // Test ElementPrime<baseType> operator / (ElementPrime<baseType> const & element1, ElementPrime<baseType> const & element2);
    cout << "________Test operator / (ElementPrime<baseType> const & element1, ElementPrime<baseType> const & element2)________" << endl;
    cout << "elt1/1000: " << (elt1/ElementPrime<baseType>(1000)) << endl << endl;
    
    // Test ElementPrime<baseType> operator + (ElementPrime<baseType> const & element1, ElementPrime<baseType> const & element2);
    cout << "________Test operator + (ElementPrime<baseType> const & element1, ElementPrime<baseType> const & element2)________" << endl;
    cout << "elt1+elt4: " << (elt1+elt4) << endl << endl;
    
    // Test ElementPrime<baseType> operator - (ElementPrime<baseType> const & element1, ElementPrime<baseType> const & element2);
    cout << "________Test operator - (ElementPrime<baseType> const & element1, ElementPrime<baseType> const & element2)________" << endl;
    cout << "elt1-elt4: " << (elt1-elt4) << endl << endl;
    
    // Test ElementPrime<baseType> operator - (ElementPrime<baseType> const & element);
    cout << "________Test operator - (ElementPrime<baseType> const & element)________" << endl;
    cout << "-elt4: " << (-elt4) << endl << endl;
    
    // Test bool isEqual(ElementPrime const & element) const;
    cout << "________Test isEqual(ElementPrime const & element)________" << endl;
    cout << ElementPrime<baseType>(1000).isEqual(ElementPrime<baseType>(2000)) << endl;
    cout << ElementPrime<baseType>(1000).isEqual(ElementPrime<baseType>(1000 - 65537)) << endl;
    cout << ElementPrime<baseType>(1000).isEqual(ElementPrime<baseType>(1000)) << endl << endl;
            
    // Test bool isEqual(baseType element) const;
    cout << "________Test isEqual(baseType element)________" << endl;
    cout << ElementPrime<baseType>(1000).isEqual(2000) << endl;
    cout << ElementPrime<baseType>(1000).isEqual(1000 - 65537) << endl;
    cout << ElementPrime<baseType>(1000).isEqual(1000) << endl << endl;
            
    // Test bool isZero() const;
    cout << "________Test isZero()________" << endl;
    cout << ElementPrime<baseType>(1000).isZero() << endl;
    cout << ElementPrime<baseType>(0).isZero() << endl << endl;
    
    // Test bool isOne() const;
    cout << "________Test isOne()________" << endl;
    cout << ElementPrime<baseType>(1000).isOne() << endl;
    cout << ElementPrime<baseType>(1).isOne() << endl << endl;
    
    // Test void setZero();
    cout << "________Test setZero()________" << endl;
    elt4.setZero();
    cout << elt4 << endl << endl;
            
    // Test void setOne();
    cout << "________Test setOne()________" << endl;
    elt4.setOne();
    cout << elt4 << endl << endl;
            
    return 0;
}


