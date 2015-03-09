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
#include "linbox/field/modular.h"
#include <vector>
#include "linbox/field/givaro.h"
#include "../include/term.h"

using namespace F4;
using namespace std;
using namespace LinBox;

// Global variable
int F4::VERBOSE=2;

int main (int argc, char **argv)
{
    cout << endl;
    cout << "#########################################################" << endl;
    cout << "#                       TEST TERM                       #" << endl;
    cout << "#########################################################" << endl << endl;
    
    //Init monomial tools: 6 variables.
    Monomial::initMonomial(6,10,6,10);
    cout << endl;
    
    // Test Term()
    cout << "________Test Term()________" << endl;
    Term<int> t1;
    Term<double> t2;
    cout << "t1: " << t1 << endl;
    cout << "t2: " << t2 << endl << endl;
    
    // Test Term(Element coeff, Monomial const & mon)
    cout << "________Test Term(Element coeff, Monomial const & mon)________" << endl;
    Term<int> t3(123, Monomial("x0^2*x1^3*x2^4"));
    Term<double> t4(123.456, Monomial("x0^2*x1^3*x2^4*x5"));
    cout << "t3: " << t3 << endl;
    cout << "t4: " << t4 << endl << endl;
    
    // Test Term(Element coeff, int numMon);
    cout << "________Test Term(Element coeff, int numMon)________" << endl;
    Term<int> t5(123, Monomial("x0^2*x1^3*x2^4").monomialToInt());
    Term<double> t6(123.456, Monomial("x0^2*x1^3*x2^4*x5").monomialToInt());
    cout << "t5: " << t5 << endl;
    cout << "t6: " << t6 << endl << endl;
            
    // Test Term(std::string const s);
    cout << "________Test Term(std::string const s)________" << endl;
    Term<int> t7("123*x0^2*x1^3*x2^4");
    Term<double> t8("123.456*x0^2*x1^3*x2^4*x5");
    cout << "t7: " << t7 << endl;
    cout << "t8: " << t8 << endl << endl;
            
    // Test Term(Term const & toCopy);
    cout << "________Test Term(Term const & toCopy)________" << endl;
    Term<int> t9(t7);
    Term<double> t10(t8);
    cout << "t9: " << t9 << endl;
    cout << "t10: " << t10 << endl << endl;
            
    // Test ~Term();
    // Usefull only if Element use dynamic allocation. 
            
    // Test Element getCoefficient() const;
    cout << "________Test getCoefficient()________" << endl;
    cout << "Coefficient of t9: " << t9.getCoefficient() << endl;
    cout << "Coefficient of t10: " << t10.getCoefficient() << endl << endl;
            
    // Test void setCoefficient(Element coeff);
    cout << "________Test setCoefficient(Element coeff)________" << endl;
    t9.setCoefficient(456);
    t10.setCoefficient(456.789);
    cout << "t9: " << t9 << endl;
    cout << "t10: " << t10 << endl << endl;
            
    // Test int getNumMonomial() const;
    cout << "________Test getNumMonomial()________" << endl;
    cout << t9.getNumMonomial() << " which match monomial: " << Monomial(t9.getNumMonomial()) << endl;
    cout << t10.getNumMonomial() << " which match monomial: " << Monomial(t10.getNumMonomial()) << endl << endl;
            
    // Test void setNumMonomial(int numMon);
    cout << "________Test setNumMonomial(int numMon)________" << endl;
    t9.setNumMonomial(10000);
    t10.setNumMonomial(20000);
    cout << "t9: " << t9 << endl;
    cout << "t10: " << t10 << endl << endl;
            
    // Test void setTerm(std::string const s);
    cout << "________Test setTerm(std::string const s)________" << endl;
    t9.setTerm("-123*x1*x2^2*x3^3*x4^4*x5^5");
    t10.setTerm("-123.456*x1*x2^2*x3^3*x4^4*x5^5");
    cout << "t9: " << t9 << endl;
    cout << "t10: " << t10 << endl << endl;
            
    // Test void printTerm (std::ostream & stream = std::cout) const;
    cout << "________Test printTerm (std::ostream & stream = std::cout)________" << endl;
    t9.printTerm();
    cout << endl;
    t10.printTerm();
    cout << endl << endl;
            
    // Test Element readCoefficient(std::string const s);
    cout << "________Test readCoefficient(std::string const s)________" << endl;
    t3.readCoefficient("-123*x1*x2^2*x3^3*x4^4*x5^5");
    cout << t3 << endl;
    t4.readCoefficient("-123.456*x1*x2^2*x3^3*x4^4*x5^5");
    cout << t4 << endl << endl;
            
    // Test Term & operator=(Term const & term);
    cout << "________Test operator=(Term const & term)________" << endl;
    t9=t3;
    t10=t4;
    cout << "t9: " << t9 << endl;
    cout << "t10: " << t10 << endl << endl;
            
    // Test Term & operator*=(Monomial const & monomial);
    cout << "________Test operator*=(Monomial const & monomial)________" << endl;
    t9*=Monomial(10000);
    t10*=Monomial(20000);
    cout << "t9 multiply by "<< Monomial(10000) << ": " << t9 << endl;
    cout << "t10 multiply by " << Monomial(20000) <<": " << t10 << endl << endl;
    
    // Test Term & operator*=(Element element);
    cout << "________Test operator*=(Element element)________" << endl;
    t9*=1000;
    t10*=2000;
    cout << "t9 multiply by "<< 1000 << ": " << t9 << endl;
    cout << "t10 multiply by " << 2000 <<": " << t10 << endl << endl;
    
    // Test Term & operator*=(Term const & term);
    cout << "________Test operator*=(Term const & term)________" << endl;
    cout << "t9: " << t9 << endl;
    cout << "t7: " << t7 << endl;
    t9*=t7;
    cout << "t9 multiplied by t7: "<< t9 << endl << endl;
    
    // Test Term & operator/=(Monomial const & monomial);
    cout << "________Test operator/=(Monomial const & monomial)________" << endl;
    t10/=Monomial(20000);
    cout << "t10 divided by " << Monomial(20000) <<": " << t10 << endl;
    t10/=Monomial(200000);
    cout << "t10 divided by " << Monomial(200000) <<": " << t10 << endl << endl;
            
    // Test Term & operator/=(int numMon);
    cout << "________Test operator/=(int numMon)________" << endl;
    t10/=100;
    cout << "t10 divided by " << 100 <<": " << t10 << endl << endl;
            
    // Test Term & operator/=(Term const & term);
    cout << "________Test operator/=(Term const & term)________" << endl;
    cout << "t9: " << t9 << endl;
    cout << "t7: " << t7 << endl;
    t9/=t7;
    cout << "t9 divided by t7: "<< t9 << endl << endl;
    
    // Test Term<Element> operator * (Monomial const & mon, Term<Element> const & term);
    cout << "________Test operator * (Monomial const & mon, Term<Element> const & term)________" << endl;
    cout << Monomial(100) << " * " << t7 << ": " << (Monomial(100)*t7) << endl;
    cout << t7 << " * " << Monomial(100) << ": " << (t7*Monomial(100)) << endl << endl;
    
    // Test Term operator * (Term const & term1, Term const & term2);
    cout << "________Test operator * (Term const & term1, Term const & term2)________" << endl;
    cout << "t9: " << t9 << endl;
    cout << "t7: " << t7 << endl;
    cout << "t9 * t7: "<< (t9 * t7) << endl << endl;
    
    // Test Term<Element> operator / (Term<Element> const & term, Monomial const & mon);
    cout << "________operator / (Term<Element> const & term, Monomial const & mon)________" << endl;
    cout << "t9: " << t9 << endl;
    Monomial m1(1234);
    cout << "m1: " << m1 << endl;
    cout << "t9 / m1: "<< (t9 / m1) << endl;
    m1=Monomial(100);
    cout << "m1: " << m1 << endl;
    cout << "t9 / m1: "<< (t9 / m1) << endl << endl;
    
    // Test Term operator / (Term const & term1, Term const & term2);
    cout << "________Test operator / (Term const & term1, Term const & term2)________" << endl;
    cout << "t9: " << t9 << endl;
    cout << "t7: " << t7 << endl;
    cout << "t9 / t7: "<< (t9 / t7) << endl << endl;
    
    // Test Linbox compatibility :
    // Term with modular coefficient (prime finite field)
    cout << "________Test Term(Element coeff, int numMon) with Modular________" << endl;
    typedef Modular < double >FieldModular;
    FieldModular field1 (65537);
    typedef FieldModular::Element elt1;
    elt1 e1;
    field1.init(e1, 123456789);
    Term<elt1> t11(e1, Monomial(123456));
    cout << "t12: " << t11 << endl << endl;
    
    // Term with givaro coefficient (non prime finite field)
    cout << "________Test Term(Element coeff, int numMon) with GivaroGfq________" << endl;
    typedef GivaroGfq FieldGivaro;
    FieldGivaro field2(17, 5);
    typedef FieldGivaro::Element elt2;
    elt2 e2;
    field2.init(e2, 545);
    Term<elt2> t12(e2, Monomial(123456));
    cout << "t12: " << t12 << endl << endl;
    
    // Free monomial tools
    Monomial::freeMonomial();

    return 0;
}
