/* 
 * Copyright (C) 2015 Antoine Joux, Vanessa Vitse and Titouan Coladon
 * 
 * This file is part of openf4.
 * 
 * openf4 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * openf4 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with openf4.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 *  \file test-monomial-array.cpp
 *  \example test-monomial-array.cpp
 *  \brief MonomialArray regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include <ctime>
#include <chrono>
#include "../openf4/include/monomial-array.h"

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=4;
#ifdef USE_OPENMP
int F4::NB_THREAD=min(8, omp_get_num_procs());
#else
int F4::NB_THREAD=1;
#endif

int main (int argc, char **argv)
{
    cout << endl;
    cout << "#########################################################" << endl;
    cout << "#                   TEST MONOMIAL ARRAY                 #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Time 
    chrono::steady_clock::time_point start;
    typedef chrono::duration<int,milli> millisecs_t;
    
    // Test MonomialArray(int nbVariable);
    cout << "________Test MonomialArray(int nbVariable)________" << endl;
    start=chrono::steady_clock::now();
    MonomialArray monArray1(8, 100000);
    cout << "Time initialisation: " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms" << endl << endl;
             
    // Test MonomialArray(int nbVariable, int degree);
    cout << "________Test MonomialArray(int nbVariable, int degree)________" << endl;
    start=chrono::steady_clock::now();
    MonomialArray monArray2(8, 10000000, 20);
    cout << "Time initialisation: " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms" << endl << endl;
             
    // Test MonomialArray(int nbVariable, int degree, int numMaxLine, int numMaxColumn);
    cout << "________Test MonomialArray(int nbVariable, int degree, int numMaxLine, int numMaxColumn)________" << endl;
    start=chrono::steady_clock::now();
    MonomialArray monArray3(8, 100000000, 20, 4, 11);
    cout << "Time initialisation: " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms" << endl << endl;
    
    // Test Monomial & operator[](int index);
    cout << "________Test Monomial & operator[](int index)________" << endl;
    cout << "Monomial number 100: " << monArray3[100] << endl;   
    cout << "Monomial number 1000: " << monArray3[1000] << endl; 
    cout << "Monomial number 10000: " << monArray3[10000] << endl; 
    cout << "Monomial number 100000: " << monArray3[100000] << endl; 
    cout << "Monomial number 1000000: " << monArray3[1000000] << endl;
    cout << "Monomial number 10000000: " << monArray3[10000000] << endl << endl;
    
    // Test int getNumVarlist(int numMon, int index);
    cout << "________Test getNumVarlist(int numMon, int index)________" << endl;
    Monomial m1;
    m1.allocate();
    m1.setMonomial(10000);
    cout << "varlist[5] of " << m1 << ": " << (int)monArray3.getNumVarlist(10000, 5) << endl; 
    cout << "varlist[6] of " << m1 << ": " << (int)monArray3.getNumVarlist(10000, 6) << endl << endl;
             
    // Test int multNumMonomial(int numMon1, int numMon2);
    cout << "________Test multNumMonomial(int numMon1, int numMon2)________" << endl;
    Monomial m2;
    m2.allocate();
    m2.setMonomial(1000);
    cout << "Monomial(1000) = " << m2 << endl;
    cout << "Monomial(10000) = " << m1 << endl;
    int num=monArray3.multNumMonomial(1000, 10000);
    Monomial m4;
    m4.allocate();
    m4.setMonomial(num);
    cout << "Monomial(1000) * Monomial(10000) = " << m4 << endl;
    
    Monomial m3;
    m3.allocate();
    m3.setMonomial(100);
    cout << "Monomial(100) = " << m3 << endl;
    cout << "Monomial(10000) = " << m1 << endl;
    num=monArray3.multNumMonomial(100, 10000);
    m4.intToMonomial(num);
    cout << "Monomial(100) * Monomial(10000) = " << m4 << endl << endl;
    
    // Free monomials
    m1.erase();
    m2.erase();
    m3.erase();
    m4.erase();
    
    return 0;
}
