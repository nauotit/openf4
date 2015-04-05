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
    cout << endl;
    cout << "#########################################################" << endl;
    cout << "#                      TEST MONOMIAL                    #" << endl;
    cout << "#########################################################" << endl << endl;
    
    //Init monomial tools: 6 variables.
    Monomial::initMonomial(11, 10);
    
    // Test Monomial(); 
    cout << "________Test Monomial()________" << endl;
    Monomial m1;
    m1.allocate();
    cout << "m1: " << m1 << endl << endl;
            
    // Test void setMonomial(int const * varlist);
    cout << "________Test setMonomial(int const * varlist)________" << endl; 
    uint8_t varlist1[11]={1,2,1,0,4,3,1,2,3,4,5};
    Monomial m2;
    m2.allocate();
    m2.setMonomial(varlist1);
    cout << "m2: " << m2 << endl << endl;
            
    // Test void setMonomial(std::string const s);
    cout << "________Test setMonomial(std::string const s)________" << endl; 
    Monomial m3;
    m3.allocate();
    m3.setMonomial("x10^2");
    cout << "m3: "<< m3 << endl << endl;
            
    // Test void setMonomial(int numMon); 
    cout << "________Test setMonomial(int numMon)________" << endl;
    Monomial m4;
    m4.allocate();
    m4.setMonomial(10000);
    cout << "m4: "<< m4 << endl << endl;
    
    // Test void setMonomial(Monomial const & mon);
    cout << "________Test setMonomial(Monomial const & mon)________" << endl;
    m4.setMonomial(m3);
    cout << "m4: "<< m4 << endl << endl;
            
    // Test Monomial & operator=(Monomial const & mon);
    cout << "________Test operator=(Monomial const & mon)________" << endl;
    Monomial m5;
    m5.allocate();
    m5=m3;
    cout << "m5: "<< m5 << endl << endl;
            
    // Test int getDegree() const;
    cout << "________Test getDegree()________" << endl;
    cout << "degree of m3: " << m3.getDegree() << endl << endl;
            
    // Test int * getVarlist() const;
    cout << "________Test getVarlist()________" << endl;
    cout << "varlist of m3: ";
    uint8_t const * varlist2=m3.getVarlist();
    for (int i = 0; i < Monomial::getNbVariable(); i++)
    {
        cout << (int)varlist2[i] << " ";
    }
    cout << endl << endl;
    
    // Test int getVarlist(int index) const;
    cout << "________Test getVarlist(int index)________" << endl;
    cout << "varlist[2] of m3: " << (int)m3.getVarlist(2) << endl << endl;
            
    // Test void setMonomial(int const * varlist);
    cout << "________Test setMonomial(int const * varlist)________" << endl;
    Monomial m6;
    m6.allocate();
    m6.setMonomial(varlist2);
    cout << "m6: "<< m6 << endl << endl;
            
    // Test void setMonomial(std::string const s);
    cout << "________Test setMonomial(std::string const s)________" << endl;
    m6.setMonomial("x0^9*x2^10*x4^11");
    cout << "m6: "<< m6 << endl << endl;
    
    // Test void setMonomialMultiply(Monomial const & mon1, Monomial const & mon2);
    cout << "________Test setMonomialMultiply(Monomial const & mon1, Monomial const & mon2)________" << endl;
    Monomial tmp1;
    tmp1.allocate();
    tmp1.setMonomial("x0^3*x1^4");
    Monomial tmp2;
    tmp2.allocate();
    tmp2.setMonomial("x1^2*x8^6");
    m6.setMonomialMultiply(tmp1, tmp2);
    cout << "m6: "<< m6 << endl << endl;
            
    // Test void intToMonomial(int numMon);
    cout << "________Test intToMonomial(int numMon)________" << endl;
    m6.intToMonomial(20000);
    cout << "m6: "<< m6 << endl << endl;
            
    // Test int monomialToInt() const;
    cout << "________Test monomialToInt()________" << endl;
    cout << m6.monomialToInt() << endl << endl;
            
    // Test void printMonomial (std::ostream & stream = std::cout) const;
    cout << "________Test printMonomial (std::ostream & stream = std::cout)________" << endl;
    cout << "m6 :";
    m6.printMonomial(cout);
    cout << endl << endl;
            
    // Test int compareMonomial(Monomial const & mon) const;
    cout << "________Test compareMonomial(Monomial const & mon)________" << endl;
    tmp1.setMonomial(10000);
    tmp2.setMonomial(10001);
    cout <<tmp1.compareMonomial(tmp2) << endl;
    tmp1.setMonomial(10000);
    tmp2.setMonomial(10000);
    cout << tmp1.compareMonomial(tmp2) << endl;
    tmp1.setMonomial(10001);
    tmp2.setMonomial(10000);
    cout <<tmp1.compareMonomial(tmp2) << endl << endl;
    
    cout << "________Test compareMonomial(Monomial const & mon)________" << endl;
    tmp1.setMonomial("x0^2*x3*x5^6");
    tmp2.setMonomial("x0^6*x3*x5^6");
    cout << tmp1.compareMonomial(tmp2) << endl << endl;
    
    // Test static int compareNumMonomial(int numMon1, int numMon2);
    cout << "________Test compareNumMonomial(int numMon1, int numMon2)________" << endl;
    cout << Monomial::compareNumMonomial(10000,10001) << endl;
    cout << Monomial::compareNumMonomial(10000,10000) << endl;
    cout << Monomial::compareNumMonomial(10001,10000) << endl << endl;
            
    // Test bool isDivisible(Monomial const & mon) const;
    cout << "________Test isDivisible(Monomial const & mon)________" << endl;
    tmp1.setMonomial(10000);
    tmp2.setMonomial(5000);
    cout << tmp1.isDivisible(tmp2) << endl;
    Monomial tmp3;
    tmp3.allocate();
    tmp3.setMonomialMultiply(tmp1,tmp2);
    cout << tmp3.isDivisible(tmp2) << endl << endl;
            
    // Test void reset();
    cout << "________Test reset()________" << endl;
    m6.reset();
    cout << "m6: "<< m6 << endl << endl;
            
    // Test Monomial & operator=(Monomial const & mon);
    cout << "________Test operator=(Monomial const & mon)________" << endl;
    m6=m3;
    cout << "m6: "<< m6 << endl << endl;
            
    // Test Monomial & operator=(Monomial && mon);
    cout << "________Test operator=(Monomial && mon)________" << endl << endl;
    
    // Test Monomial & operator*=(Monomial const & mon); 
    cout << "________Test operator*=(Monomial const & mon)________" << endl;
    m6*=m3;
    cout << "m6: "<< m6 << endl << endl;
    
    // Test friend int multiplyMonomial(Monomial const & mon1, Monomial const & mon2);
    cout << "________Test multiplyMonomial(Monomial const & mon1, Monomial const & mon2)________" << endl;
    tmp1.setMonomial(multiplyMonomial(m3, m6));
    cout << "Number of m6 * m3: " << multiplyMonomial(m3, m6) << ", " << tmp1 << endl << endl;
    
    // Test Monomial & operator/=(Monomial const & mon);
    cout << "________Test operator/=(Monomial const & mon)________" << endl; 
    m6/=m3;
    cout << "m6: "<< m6 << endl;
    tmp1.setMonomial(12345);
    m6/=tmp1;
    cout << "m6: "<< m6 << endl << endl;
    
    // Test std::ostream & operator<<(std::ostream & stream, Monomial const & mon);
    cout << "________Test operator<<(std::ostream & stream, Monomial const & mon)________" << endl;
    Monomial m7;
    m7.allocate();
    m7.setMonomial(100000);
    Monomial m8;
    m8.allocate();
    m8.setMonomial(100001);
    Monomial m9;
    m9.allocate();
    m9.setMonomial(100002);
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
    
    // Test void setMonomialMultiply(Monomial const & mon1, Monomial const & mon2);
    cout << "________Test setMonomialMultiply(Monomial const & mon1, Monomial const & mon2)________" << endl;
    tmp1.setMonomialMultiply(m7,m8);
    cout << "m7 * m8: " << tmp1 << endl << endl;
    
    // Test void setMonomialDivide(Monomial const & mon1, Monomial const & mon2);
    cout << "________Test setMonomialDivide(Monomial const & mon1, Monomial const & mon2)________" << endl;
    tmp2.setMonomialDivide(tmp1,m7);
    cout << "(m7 * m8)/m7 : " << tmp2 << endl << endl;
    
    // Free monomial
    m1.erase();
    m2.erase();
    m3.erase();
    m4.erase();
    m5.erase();
    m6.erase();
    m7.erase();
    m8.erase();
    m9.erase();
    tmp1.erase();
    tmp2.erase();
    tmp3.erase();
    
    // Free monomial tools
    Monomial::freeMonomial();
    
    return 0;
}


