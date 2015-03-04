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
#include <vector>
#include "../include/monomial.h"

using namespace F4;
using namespace std;

int main (int argc, char **argv)
{
    // Set verbose mode.
    Monomial::setVerbose(2);
    string vars[8]={"s1","s2","s3","s4","s5","s6","s7","s8"};
    
    int weight[8]={1,1,1,1,1,1,1,1};
    
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
    
    // And their weight (weighted monomial order:
    Monomial::setWeight(weight);
    
    if (Monomial::getWeight()!=0)
    {
        cout << "weight: ";
        for(int i=0; i< Monomial::getNbVariable(); i++)
        {
            cout << Monomial::getWeight()[i] << ", ";
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
    cout << "mon1.reset(): " << mon1 << endl << endl ;
    
    cout << "Test setMonomial() " << endl;
    vector<Monomial> MonArray(4);
    int varlist3[8]={1,1,1,1,1,1,1,1};
    int varlist4[8]={1,1,1,1,1,1,1,2};
    int varlist5[8]={1,1,1,1,1,1,1,3};
    int varlist6[8]={1,1,1,1,1,1,1,4};
    MonArray[0].setMonomial(varlist3);
    MonArray[1].setMonomial(varlist4);
    MonArray[2].setMonomial(varlist5);
    MonArray[3].setMonomial(varlist6);
    cout << "MonArray[0] :" << MonArray[0] << endl;
    cout << "MonArray[1] :" << MonArray[1] << endl;
    cout << "MonArray[2] :" << MonArray[2] << endl;
    cout << "MonArray[3] :" << MonArray[3] << endl << endl;
    
    cout << "Test setNbMonomial() " << endl;
    Monomial::setNbMonomial(20);
    vector<int *> nbMon=Monomial::getNbMonomial();
    for (int i=0; i< 8+1; i++)
    {
        for (int j=0; j< 8+2; j++)
        {
            cout << nbMon[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    cout << "Test intToMonomial() " << endl;
    vector<Monomial> MonArray2(25);
    for (int i=0; i<20; i++)
    {
        MonArray2[i].intToMonomial(i);
        cout << "MonArray2[" << i << "] :" << MonArray2[i] << endl;
    }
    cout << endl;
    
    cout << "Test monomialToInt() " << endl;
    cout << "MonArray2[6].monomialToInt() " << MonArray2[6].monomialToInt() <<endl;
    cout << "mon1.monomialToInt() " << mon1.monomialToInt() << endl;
    cout << mon2 << endl;
    cout << "mon2.monomialToInt() " << mon2.monomialToInt() << endl << endl;
    
    cout << "Test setMonomialArray: " << endl;
    Monomial::setMonomialArray();
    vector<Monomial> vec=Monomial::getMonomialArray();
    for (int i=0; i<30; i++)
    {
        cout << " MONOMIAL_ARRAY["<<i<<"] :" << vec[i] << endl;
    }
    cout << endl;
    
    cout << "Test setTabulatedProduct: " << endl;
    Monomial::setTabulatedProduct(2,10);
    int ** tabProduct=Monomial::getTabulatedProduct();
    for (int i=0; i< 10; i++)
    {
        for (int j=0; j< 10; j++)
        {
            cout << tabProduct[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "tabProduct[3][9]: " << tabProduct[3][9] << endl;
    cout << "MonArray2[3]*MonArray2[9]: " << MonArray2[3]*MonArray2[9] << endl;
    mon1.intToMonomial(tabProduct[3][9]);
    cout << "intToMonomial(tabProduct[3][9]): " << mon1 << endl << endl;
    
    cout << "Test multNumMonomial: " << endl;
    cout << "Monomial::multNumMonomial(10, 100) :" << Monomial::multNumMonomial(10, 100) << endl;
    cout << "Monomial::multNumMonomial(100, 1000) :" << Monomial::multNumMonomial(100, 1000) << endl;
    cout << "Monomial::multNumMonomial(1000, 10000) :" << Monomial::multNumMonomial(1000, 10000) << endl;
    cout << "Monomial::multNumMonomial(10000, 100000) :" << Monomial::multNumMonomial(10000, 100000) << endl << endl;
    
    cout << "Test setMonomial(string s)" << endl;
    string s1="s1*s3^4*s7^2";
    cout << "s1: " << s1 << endl;
    mon1.reset();
    mon1.setMonomial(s1);
    cout << "mon1.setMonomial(s1): " << mon1 << endl;
    string s2="s1^4*s2*s3^4*s7^2*s8^178*s5^2";
    cout << "s2: " << s2 << endl;
    mon2.reset();
    mon2.setMonomial(s2);
    cout << "mon2.setMonomial(s2): " << mon2 << endl;
    string s3="s2*s3^12*s7*s8^178*s5^2";
    cout << "s3: " << s3 << endl;
    Monomial mon6(s3);
    cout << "mon6(s3); " << mon6 << endl << endl;
    
    // Free first TABULATED_PRODUCT, then NB_MONOMIAL.
    Monomial::freeTabulatedProduct();
    Monomial::freeNbMonomial();
    
    return 0;
}


