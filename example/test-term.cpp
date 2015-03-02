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
 *  \file test-term.cpp
 *  \example test-term.cpp
 *  \brief Term regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
//#include "linbox/field/modular.h"
#include <vector>
//#include "linbox/field/givaro.h"
#include "../include/term.h"

using namespace F4;
using namespace std;
//using namespace LinBox;

int main (int argc, char **argv)
{
    // First we set the number of variable of the polynomial ring.
    Monomial::setNbVariable(4);
    // Then their names:
    string vars[4]={"s1","s2","s3","s4"};
    Monomial::setVariable(vars);
    // Then the weight
    int weight[4]={1,1,1,1};
    Monomial::setWeight(weight);
    // Then the 2D array NB_MONOMIAL:
    Monomial::setNbMonomial(30);
    // Verbose mode
    Monomial::setVerbose(2);
    
    // Create an array of 100 monomials.
    vector<Monomial> monArray(100);
    for(int i=0; i<100; i++)
    {
        monArray[i].intToMonomial(i);
    }
    
    // Term with integer coefficient
    Term<int> t1(-3, monArray[8]);
    cout << "Test Term<int>: " << endl;
    cout << "t1: " << t1 << endl;
    Term<int> t1bis("-7*s1^3*s4^12");
    cout << "t1bis:" << t1bis << endl;
    Term<int> t1bisbis("-7");
    cout << "t1bisbis:" << t1bisbis << endl << endl;
    
    // Term with double coefficient
    Term<double> t2(85.32, monArray[14]);
    cout << "Test Term<double>: " << endl;
    cout << "t2: " << t2 << endl;
    Term<double> t2bis("95.365*s1^2*s3^11*s4^12");
    cout << "t2bis:" << t2bis << endl << endl;
    
    //// Term with modular coefficient (prime finite field)
    //typedef Modular < double >FieldModular;
    //FieldModular field1 (65537);
    //typedef FieldModular::Element elt1;
    //elt1 e1;
    //field1.init(e1, 6);
    //Term<elt1> t3(e1, monArray[16]);
    //cout << "Test Term<Modular<double>::Element>: " << endl;
    //cout << "t3: " << t3 << endl << endl;
    
    //// Term with givaro coefficient (non prime finite field)
    //typedef GivaroGfq FieldGivaro;
    //FieldGivaro field2( 17, 5);
    //typedef FieldGivaro::Element elt2;
    //elt2 e2;
    //field2.init(e2, 545);
    //Term<elt2> t4(e2, monArray[9]);
    //cout << "Test Term<GivaroGfq::Element>: " << endl;
    //cout << "t4: " << t4 << endl << endl;
    
    // Free
    for(int i=0; i<100; i++)
    {
        monArray[i].~Monomial();
    }
    Monomial::freeNbMonomial(20);
    
    t1.~Term();
    t2.~Term();
    t1bis.~Term();
    t1bisbis.~Term();
    t2bis.~Term();
    //t3.~Term();
    //t4.~Term();

    return 0;
}
