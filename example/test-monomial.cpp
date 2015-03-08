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

// Global variable
int F4::VERBOSE=2;

int main (int argc, char **argv)
{
    //Init monomial tools: 6 variables.
    Monomial::initMonomial(6,10,6,10);
    
    // Test Monomial(); 
    cout << "________Test Monomial()________" << endl;
    Monomial m1;
    cout << "m1: " << m1 << endl;
            
    // Test Monomial(int const * varlist);
    cout << "________Test Monomial(int const * varlist)________" << endl; 
    int varlist1[8]={1,2,1,0,4,3};
    Monomial m2(varlist1);
    cout << "m2: " << m2 << endl << endl;
            
    // Test Monomial(std::string const s);
    cout << "________Test Monomial(std::string const s)________" << endl; 
    Monomial m3("x1*x2^2*x3^3*x4^4*x5^5");
    cout << "m3: "<< m3 << endl << endl;
            
    // Test Monomial(int numMon); 
    cout << "________Test Monomial(int numMon)________" << endl;
    Monomial m4(10000);
    cout << "m4: "<< m4 << endl << endl;
            
    // Test Monomial(Monomial const & toCopy);
    cout << "________Test Monomial(Monomial const & toCopy)________" << endl;
    Monomial m5(m3);
    cout << "m5: "<< m5 << endl << endl;
            
    // Test Monomial(Monomial && toCopy);
    cout << "________Test Monomial(Monomial && toCopy)________" << endl;
    Monomial m6(Monomial(20000));
    cout << "m6: "<< m6 << endl << endl;
             
    // Test ~Monomial();
    // Automatically called at the end of the scope
            
    // Test int getDegree() const;
    cout << "________Test getDegree()________" << endl;
    cout << "degree of m3: " << m3.getDegree() << endl << endl;
            
    // Test int * getVarlist() const;
    cout << "________Test getVarlist()________" << endl;
    cout << "varlist of m3: ";
    int * varlist2=m3.getVarlist();
    for (int i = 0; i < Monomial::getNbVariable(); i++)
    {
        cout << varlist2[i] << " ";
    }
    cout << endl << endl;
            
    // Test void setMonomial(int const * varlist);
    cout << "________Test setMonomial(int const * varlist)________" << endl;
    m6.setMonomial(varlist2);
    cout << "m6: "<< m6 << endl << endl;
            
    // Test void setMonomial(std::string const s);
    cout << "________Test setMonomial(std::string const s)________" << endl;
    m6.setMonomial("x0^9*x2^10*x4^11");
    cout << "m6: "<< m6 << endl << endl;
            
    // Test void intToMonomial(int numMon);
    cout << "________Test intToMonomial(int numMon)________" << endl;
    m6.intToMonomial(20000);
    cout << "m6: "<< m6 << endl << endl;
    
    // static const & Monomial getNumMonomial(int numMon);
    cout << "________Test getNumMonomial(int numMon)________" << endl;
    m5=Monomial::getNumMonomial(200000);
    cout << "m5: "<< m5 << endl << endl;
            
    // Test int monomialToInt() const;
    cout << "________Test monomialToInt()________" << endl;
    cout << m6.monomialToInt() << endl << endl;
            
    // Test void printMonomial (std::ostream & stream = std::cout) const;
    cout << "________Test printMonomial (std::ostream & stream = std::cout)________" << endl;
    cout << "m6 :";
    m6.printMonomial();
    cout << endl << endl;
            
    // Test int compareMonomial(Monomial const & mon) const;
    cout << "________Test compareMonomial(Monomial const & mon)________" << endl;
    cout << Monomial(10000).compareMonomial(Monomial(10001)) << endl;
    cout << Monomial(10000).compareMonomial(Monomial(10000)) << endl;
    cout << Monomial(10001).compareMonomial(Monomial(10000)) << endl << endl;
    
    // Test static int compareNumMonomial(int numMon1, int numMon2);
    cout << "________Test compareNumMonomial(int numMon1, int numMon2)________" << endl;
    cout << Monomial::compareNumMonomial(10000,10001) << endl;
    cout << Monomial::compareNumMonomial(10000,10000) << endl;
    cout << Monomial::compareNumMonomial(10001,10000) << endl << endl;
            
    // Test bool isDivisible(Monomial const & mon) const;
    cout << "________Test isDivisible(Monomial const & mon)________" << endl;
    cout << Monomial(10000).isDivisible(Monomial(5000)) << endl;
    cout << (Monomial(10000)*Monomial(5000)).isDivisible(Monomial(5000)) << endl << endl;
            
    // Test void reset();
    cout << "________Test reset()________" << endl;
    m6.reset();
    cout << "m6: "<< m6 << endl << endl;
            
    // Test Monomial & operator=(Monomial const & mon);
    cout << "________Test operator=(Monomial const & mon)________" << endl;
    m6=m3;
    cout << "m6: "<< m6 << endl << endl;
            
    // Test Monomial & operator=(Monomial && mon);
    cout << "________Test operator=(Monomial && mon)________" << endl;
    m6=Monomial(20000)*Monomial(10000);
    cout << "m6: "<< m6 << endl << endl;
    
    // Test Monomial & operator*=(Monomial const & mon); 
    cout << "________Test operator*=(Monomial const & mon)________" << endl;
    m6*=m3;
    cout << "m6: "<< m6 << endl << endl;
            
    // Test Monomial & operator/=(Monomial const & mon);
    cout << "________Test operator/=(Monomial const & mon)________" << endl; 
    m6/=m3;
    cout << "m6: "<< m6 << endl;
    m6/=Monomial(12345);
    cout << "m6: "<< m6 << endl << endl;
    
    // Test std::ostream & operator<<(std::ostream & stream, Monomial const & mon);
    cout << "________Test operator<<(std::ostream & stream, Monomial const & mon)________" << endl;
    Monomial m7(100000);
    Monomial m8(100001);
    Monomial m9(100002);
    cout << m7 << endl;
    cout << m8 << endl;
    cout << m9 << endl << endl;
    
    // Test bool operator==(Monomial const & mon1, Monomial const & mon2);
    cout << "________Test operator==(Monomial const & mon1, Monomial const & mon2)________" << endl;
    cout << "m7 == m8: " << (m7 == m8) << endl;
    cout << "m7 == m9: " << (m7 == m9) << endl;
    cout << "m7 == m7: " << (m7 == m7) << endl << endl;
    
    // Test bool operator>(Monomial const & mon1, Monomial const & mon2);
    cout << "________Test operator>(Monomial const & mon1, Monomial const & mon2)________" << endl;
    cout << "m7 > m8: " << (m7 > m8) << endl;
    cout << "m9 > m7: " << (m9 > m7) << endl;
    cout << "m7 > m7: " << (m7 > m7) << endl << endl;
    
    // Test bool operator>=(Monomial const & mon1, Monomial const & mon2);
    cout << "________Test operator>=(Monomial const & mon1, Monomial const & mon2)________" << endl;
    cout << "m7 >= m8: " << (m7 >= m8) << endl;
    cout << "m9 >= m7: " << (m9 >= m7) << endl;
    cout << "m7 >= m7: " << (m7 >= m7) << endl << endl;
    
    // Test bool operator<(Monomial const & mon1, Monomial const & mon2);
    cout << "________Test operator<(Monomial const & mon1, Monomial const & mon2)________" << endl;
    cout << "m7 < m8: " << (m7 < m8) << endl;
    cout << "m9 < m7: " << (m9 < m7) << endl;
    cout << "m7 < m7: " << (m7 < m7) << endl << endl;
    
    // Test bool operator<=(Monomial const & mon1, Monomial const & mon2);
    cout << "________Test operator<=(Monomial const & mon1, Monomial const & mon2)________" << endl;
    cout << "m7 <= m8: " << (m7 <= m8) << endl;
    cout << "m9 <= m7: " << (m9 <= m7) << endl;
    cout << "m7 <= m7: " << (m7 <= m7) << endl << endl;
    
    // Test Monomial operator * (Monomial const & mon1, Monomial const & mon2);
    cout << "________Test operator * (Monomial const & mon1, Monomial const & mon2)________" << endl;
    cout << "m7 * m8: " << (m7 * m8) << endl << endl;
    
    // Test Monomial operator / (Monomial const & mon1, Monomial const & mon2);
    cout << "________Test operator / (Monomial const & mon1, Monomial const & mon2)________" << endl;
    cout << "(m7 * m8)/m7 : " << ((m7 * m8)/m7) << endl << endl;
    
    // Free monomial tools
    Monomial::freeMonomial();
    
    return 0;
}


