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
 *  \file test-monomial.cpp
 *  \example test-monomial.cpp
 *  \brief Monomial regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include <string>
#include "../include/monomial.h"

using namespace F4;
using namespace std;

int main (int argc, char **argv)
{
    string vars[8]={"s1","s2","s3","s4","s5","s6","s7","s8"};
    
    // In a first time we need to set the number of variables of the polynomial ring.
    Monomial::setNbVariable(8);
    
    // And eventually their names.
    Monomial::setVariable(vars);
    
    if (Monomial::getVariable()!=0)
    {
        // Then the class Monomial will use these variable:
        cout << "Used variables: ";
        for(int i=0; i< Monomial::getNbVariable(); i++)
        {
            cout << Monomial::getVariable()[i] << ", ";
        }
        cout << endl << endl;
    }
    
    // Then we can create some monomials.
    int varlist1[8]={1,2,1,0,4,3,2,2};
    Monomial mon1(varlist1);
    
    int varlist2[8]={5,5,0,0,4,7,2,2};
    Monomial mon2(varlist2);
    
    cout << "Test operator <<" << endl;

    cout << "mon1: " << mon1 << endl ;
    cout << "mon2: " << mon2 << endl << endl ;
    
    cout << "Test comparison operators " << endl;
    
    cout << "mon1 == mon2: " << (mon1==mon2) << endl;
    cout << "mon1 < mon2: " << (mon1<mon2) << endl;
    cout << "mon1 > mon2: " << (mon1>mon2) << endl;
    
    cout << "mon1 == mon1: " << (mon1==mon1) << endl;
    cout << "mon1 < mon1: " << (mon1<mon1) << endl;
    cout << "mon1 > mon1: " << (mon1>mon1) << endl;
    cout << "mon1 >= mon1: " << (mon1>=mon1) << endl;
    cout << "mon1 <= mon1: " << (mon1<=mon1) << endl << endl;
    
    cout << "Test copy constructor" << endl;
    Monomial mon3(mon2);
    cout << "mon2: " << mon2 << endl ;
    cout << "mon3: " << mon3 << endl << endl ;
    
    cout << "Test operator =" << endl;
    
    mon3=mon1;
    cout << "mon1:" << mon1 << endl ;
    cout << "mon3:" << mon3 << endl << endl ;
    
    cout << "Test operator *=" << endl;
    cout << "mon2: " << mon2 << endl ;
    cout << "mon3: " << mon3 << endl ;
    cout << "mon2*=mon3: " << (mon2*=mon3) << endl << endl;
    
    cout << "Test operator *" << endl;
    cout << "mon1: " << mon2 << endl ;
    cout << "mon2: " << mon3 << endl ;
    Monomial mon4=mon1*mon2;
    cout << "mon1*mon2: " << mon4 << endl << endl;
    
    cout << "Test operator /=" << endl;
    cout << "mon2: " << mon2 << endl ;
    cout << "mon3: " << mon3 << endl ;
    cout << "mon3/mon2: " << (mon3/=mon2) << endl ; // mon3 is not modified because mon2 does not divide mon3.
    cout << "mon2/=mon3: " << (mon2/=mon3) << endl << endl;
    
    cout << "Test operator /" << endl;
    cout << "mon1: " << mon1 << endl ;
    cout << "mon2: " << mon2 << endl ;
    cout << "mon1*=mon2: " << (mon1*=mon2) << endl;
    Monomial mon5=mon1/mon2;
    cout << "mon1/mon2: " << mon5 << endl << endl;
    
    cout << "Test isDivisible " << endl;
    cout << "mon1: " << mon1 << endl ;
    cout << "mon1*=mon2: " << (mon1*=mon2) << endl;
    cout << "mon2.isDivisible(mon1): " << mon2.isDivisible(mon1) << endl;
    cout << "mon1.isDivisible(mon2): " << mon1.isDivisible(mon2) << endl << endl;
    
    cout << "Test reset " << endl;
    mon1.reset();
    cout << "mon1.reset(): " << mon1 << endl ;
    
    mon1.~Monomial();
    mon2.~Monomial();
    mon3.~Monomial();
    mon4.~Monomial();
    mon5.~Monomial();
    return 0;
}


