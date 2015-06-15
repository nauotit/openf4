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
 *  \file test-tagged-polynomial.cpp
 *  \example test-tagged-polynomial.cpp
 *  \brief TaggedPolynomial regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include "../f4/include/tagged-polynomial.h"


using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=2;
#ifdef USE_OPENMP
int F4::NB_THREAD=min(8, omp_get_num_procs());
#else
int F4::NB_THREAD=1;
#endif

int main (int argc, char **argv)
{
    cout << endl;
    cout << "#########################################################" << endl;
    cout << "#                 TEST TAGGED POLYNOMIAL                #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Init element-prime tools
    typedef ElementPrime<long> eltType;
    ElementPrime<long>::setModulo(65537);
    
    // Init monomial tools
    MonomialArray monArray(6,10000000,10, 2, 10);
    Term<eltType>::setMonomialArray(&monArray);
    TaggedPolynomial<eltType>::setMonomialArray(&monArray);
    cout << endl;
    
    // Test TaggedPolynomial();
    cout << "________Test TaggedPolynomial()________" << endl;
    TaggedPolynomial<eltType> tp1;
    cout << "tp1: " << tp1 << endl << endl;
    
    // Test TaggedPolynomial(Polynomial<Element> const & polynomial);
    cout << "________Test TaggedPolynomial(Polynomial<Element> & polynomial)________" << endl;
    TaggedPolynomial<eltType> tp2(Polynomial<eltType>("x0+x1+x2+x3+x4+x5"));
    TaggedPolynomial<eltType> tp3(Polynomial<eltType>("x0*x1+x1*x2+x2*x3+x3*x4+x0*x5+x4*x5"));
    cout << "tp2: " << tp2 << endl;
    cout << "tp3: " << tp3 << endl << endl;
    
    // Test TaggedPolynomial(TaggedPolynomial const & taggedPolynomial);
    cout << "________Test TaggedPolynomial(TaggedPolynomial const & taggedPolynomial)________" << endl;
    TaggedPolynomial<eltType> tp4(tp3);
    cout << "tp4: " << tp4 << endl << endl;
    
    // Test TaggedPolynomial(TaggedPolynomial  && taggedPolynomial);
    cout << "________Test TaggedPolynomial(TaggedPolynomial  && taggedPolynomial)________" << endl;
    TaggedPolynomial<eltType> tp5(TaggedPolynomial<eltType>(Polynomial<eltType>("3*x0*x1-25*x1*x2+x2*x3+4*x3*x4+x0*x5+x4*x5")));
    cout << "tp5: " << tp5 << endl << endl;
    
    // Test Polynomial<Element> const & getPolynomial() const;
    cout << "________Test getPolynomial()________" << endl;
    cout << "polynomial of tp5: " << tp5.getPolynomial() << endl << endl;
    
    // Test void setPolynomial(Polynomial<Element> && polynomial);
    cout << "________Test setPolynomial(Polynomial<Element> && polynomial)________" << endl;
    tp4.setSimplyrule(0, 1);
    tp4.setSimplyrule(2, 2);
    tp4.setPolynomial(Polynomial<eltType>("x0+x1+x2+x3+x4+x5"));
    cout << "tp4: " << tp4 << endl << endl;
    
    // Test const Term<Element> & getLT(); 
    cout << "________Test getLT()________" << endl;
    cout << "Leading term of tp5: " << tp5.getLT() << endl << endl;
    
    // Test int getLM() const;
    cout << "________Test getLM()________" << endl;
    cout << "Number of the leading monomial of tp5: " << tp5.getLM() << endl << endl;
    
    // Test int getLC() const;
    cout << "________Test getLC()________" << endl;
    cout << "Leading coefficient of tp5: " << tp5.getLC() << endl << endl;
    
    // Test int getNbTerm() const;
    cout << "________Test getNbTerm()________" << endl;
    cout << "Number of terms of tp5: " << tp5.getNbTerm() << endl << endl;
    
    // Test void setSimplyrule(int index, int numPol);
    cout << "________Test setSimplyrule(int index, int numPol)________" << endl;
    tp5.setSimplyrule(0, 3);
    tp5.setSimplyrule(2, 13);
    tp5.setSimplyrule(5, 23);
    tp2.setSimplyrule(2, 10);
    cout << "tp5: " << tp5 << endl << endl;
    
    // Test int getSimplyrule(int index) const;
    cout << "________Test getSimplyrule(int index)________" << endl;
    cout << "simplyrule[2] of tp5: " << tp5.getSimplyrule(2) << endl << endl;
    
    // Test NodeList<Element> * getPolynomialBegin();
    cout << "________Test getPolynomialBegin()________" << endl;
    NodeList<eltType> * itbeg=tp4.getPolynomialBegin();
    while(itbeg)
    {
        cout << itbeg->getNumMonomial() << endl;
        itbeg=itbeg->_next;
    }
    
    // Test void printTaggedPolynomial(std::ostream & stream = std::cout) const;
    cout << "________Test printTaggedPolynomial (std::ostream & stream = std::cout)________" << endl;
    cout << "tp2 :";
    tp2.printTaggedPolynomial(cout);
    cout << endl << endl;
    
    // Test int compareTaggedPolynomial(TaggedPolynomial const & taggedPolynomial) const;
    cout << "________Test compareTaggedPolynomial(TaggedPolynomial const & taggedPolynomial)________" << endl;
    cout << tp2.compareTaggedPolynomial(tp3) << endl;
    cout << tp3.compareTaggedPolynomial(tp3) << endl;
    cout << tp3.compareTaggedPolynomial(tp2) << endl << endl;
    
    // Test bool isEmpty();
    cout << "________Test isEmpty()________" << endl;
    cout << tp1.isEmpty() << endl;
    cout << tp3.isEmpty() << endl << endl;
    
    // Test void resetSimplyrules();
    cout << "________Test resetSimplyrules()________" << endl;
    tp4.resetSimplyrules();
    cout << "tp4: " << tp4 << endl << endl;
    
    // Test void setTaggedPolynomial(TaggedPolynomial const & taggedPolynomial, Monomial const & monomial);
    cout << "________Test setTaggedPolynomial(TaggedPolynomial const & taggedPolynomial, Monomial const & monomial)________" << endl;
    Monomial tmp1;
    tmp1.allocate();
    tmp1.setMonomial("x1^5");
    tp4.setTaggedPolynomial(tp2, tmp1.getVarlist());
    cout << "tp4: " << tp4 << endl << endl; 
    
    // Test TaggedPolynomial & operator=(TaggedPolynomial const & taggedPolynomial);
    cout << "________Test operator=(TaggedPolynomial const & taggedPolynomial)________" << endl;
    tp1=tp4;
    cout << "tp1: " << tp1 << endl << endl;
    
    // Test TaggedPolynomial & operator=(TaggedPolynomial  && taggedPolynomial);
    cout << "________Test operator=(TaggedPolynomial  && taggedPolynomial)________" << endl;
    cout << endl;
    
    // Test TaggedPolynomial & operator=(Polynomial && polynomial);
    tp1=Polynomial<eltType>("-6*x0^6*x1^5*x2^4+x5*x3^2");
    cout << "tp1: " << tp1 << endl << endl;
    
    // Test TaggedPolynomial & operator*=(Monomial const & monomial);
    cout << "________Test operator*=(Monomial const & monomial)________" << endl;
    tmp1.setMonomial("x1*x2");
    tp5*=tmp1;
    cout << "tp5: " << tp5 << endl << endl;
            
    // Test TaggedPolynomial & operator*=(Element element);
    cout << "________Test operator*=(Element element)________" << endl;
    eltType e;
    e = 10;
    tp5*=e;
    cout << "tp5: " << tp5 << endl << endl;
            
    // Test TaggedPolynomial & operator*=(Term<Element> const & term);
    cout << "________Test operator*=(Term<Element> const & term)________" << endl;
    tp5*=Term<eltType>("2*x5^10*x4");
    cout << "tp5: " << tp5 << endl << endl;
    
    // Test bool operator==(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2);
    cout << "________Test operator==(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2)________" << endl;
    cout << "tp2==tp3 :" << (tp2==tp3) << endl;
    cout << "tp3==tp3 :" << (tp3==tp3) << endl << endl;
    
    // Test bool operator>(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2);
    cout << "________Test operator>(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2)________" << endl;
    cout << "tp2>tp3 :" << (tp2>tp3) << endl;
    cout << "tp3>tp3 :" << (tp3>tp3) << endl;
    cout << "tp3>tp2 :" << (tp3>tp2) << endl << endl;
    
    // Test bool operator>=(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2);
    cout << "________Test operator>=(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2)________" << endl;
    cout << "tp2>=tp3 :" << (tp2>=tp3) << endl;
    cout << "tp3>=tp3 :" << (tp3>=tp3) << endl;
    cout << "tp3>=tp2 :" << (tp3>=tp2) << endl << endl;
    
    // Test bool operator<(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2);
    cout << "________Test operator<(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2)________" << endl;
    cout << "tp2<tp3 :" << (tp2<tp3) << endl;
    cout << "tp3<tp3 :" << (tp3<tp3) << endl;
    cout << "tp3<tp2 :" << (tp3<tp2) << endl << endl;
    
    // Test bool operator<=(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2);
    cout << "________Test operator<=(TaggedPolynomial<Element> const & taggedPolynomial1, TaggedPolynomial<Element> const & taggedPolynomial2)________" << endl;
    cout << "tp2<=tp3 :" << (tp2<=tp3) << endl;
    cout << "tp3<=tp3 :" << (tp3<=tp3) << endl;
    cout << "tp3<=tp2 :" << (tp3<=tp2) << endl << endl;
    
    // Test TaggedPolynomial<Element> operator * (Monomial const & monomial, TaggedPolynomial<Element> const & taggedPolynomial);
    cout << "________Test operator * (Monomial const & monomial, TaggedPolynomial<Element> const & taggedPolynomial)________" << endl;
    tmp1.setMonomial("x1^5*x2^5");
    cout << "x1^5*x2^5 * tp2: " << (tmp1*tp2) << endl << endl;
    
    // Test TaggedPolynomial<Element> operator * (TaggedPolynomial<Element> const & taggedPolynomial, Monomial const & monomial);
    cout << "________Test operator * (TaggedPolynomial<Element> const & taggedPolynomial, Monomial const & monomial)________" << endl;
    tmp1.setMonomial("x1^10*x2^5");
    cout << "tp2 * x1^5*x2^5: " << (tp2 * tmp1) << endl << endl;

    // Test TaggedPolynomial<Element> operator * (Element element, TaggedPolynomial<Element> const & taggedPolynomial);
    cout << "________Test operator * (Element element, TaggedPolynomial<Element> const & taggedPolynomial)________" << endl;
    e = -1000;
    cout << "-1000*tp2: " << (e*tp2) << endl << endl;
    
    // Test TaggedPolynomial<Element> operator * (TaggedPolynomial<Element> const & taggedPolynomial, Element element);
    cout << "________Test operator * (TaggedPolynomial<Element> const & taggedPolynomial, Element element)________" << endl;
    cout << "tp2 * (-1000): " << (tp2 * e) << endl << endl;

    // Test TaggedPolynomial<Element> operator * (Term<Element> const & term, TaggedPolynomial<Element> const & taggedPolynomial);
    cout << "________Test operator * (Term<Element> const & term, TaggedPolynomial<Element> const & taggedPolynomial)________" << endl;
    cout << "-1000*x5^10 * tp2: " << (Term<eltType>("-1000*x5^10")*tp2) << endl << endl;
    
    // Test TaggedPolynomial<Element> operator * (TaggedPolynomial<Element> const & taggedPolynomial, Term<Element> const & term);
    cout << "________Test operator * (TaggedPolynomial<Element> const & taggedPolynomial, Term<Element> const & term)_______" << endl;
    cout << "tp2* (-1000)*x5^10: " << (tp2*Term<eltType>("-1000*x5^10")) << endl << endl;
    
    // Free monomial
    tmp1.erase();
    
    return 0;
}


