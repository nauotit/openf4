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
    int varlist1[8]={1,2,1,0,4,3,2,2};
    Monomial mon1(8, varlist1);
    
    int varlist2[8]={5,5,0,0,4,7,2,2};
    Monomial mon2(8, varlist2);
    
    cout << "Test operator <<" << endl;

    cout << "mon1:" << mon1 << endl ;
    cout << "mon2:" << mon2 << endl << endl ;
    
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
    cout << "mon2:" << mon2 << endl ;
    cout << "mon3:" << mon3 << endl << endl ;
    
    cout << "Test operator =" << endl;
    
    mon3=mon1;
    cout << "mon1:" << mon1 << endl ;
    cout << "mon3:" << mon3 << endl << endl ;
    
    mon1.~Monomial();
    mon2.~Monomial();
    mon3.~Monomial();
    return 0;
}


