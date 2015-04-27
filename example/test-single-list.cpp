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
 *  \file test-single-list.cpp
 *  \example test-single-list.cpp
 *  \brief SingleList regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include <ctime>
#include "../include/single-list.h"

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=3;
int F4::NB_THREAD=min(16, omp_get_num_procs());

int main (int argc, char **argv)
{
    cout << endl;
    cout << "#########################################################" << endl;
    cout << "#                    TEST SINGLE LIST                   #" << endl;
    cout << "#########################################################" << endl << endl;
    
    
    typedef ElementPrime<int> eltType;
    ElementPrime<int>::setModulo(65521);
    
    // Init monomial tools
    MonomialArray monArray(6,10000000,10, 2, 10);
    Term<eltType>::setMonomialArray(&monArray);
    
    
    // Test SingleList();
    cout << "________Test SingleList()________" << endl;
    SingleList<eltType> poly1;
    cout << poly1 << endl << endl;
    
    // Test NodeList<Element> * emplaceBegin( Element coefficient, int numMonomial);
    cout << "________Test emplaceBegin( Element coefficient, int numMonomial)________" << endl;
    eltType e;
    e=1;
    NodeList<eltType> * it=poly1.emplaceBegin(e, 10);
    e=2; 
    it=poly1.emplaceBegin(e, 20);
    e=3;
    it=poly1.emplaceBegin(e, 30);
    e=4;
    it=poly1.emplaceBegin(e, 40);
    e=5;
    it=poly1.emplaceBegin(e, 50);
    cout << poly1 << endl;
    
    // Test NodeList<Element> * emplaceAfter(NodeList<Element> * it, Element coefficient, int numMonomial);
    cout << "________Test emplaceAfter(NodeList<Element> * it, Element coefficient, int numMonomial)________" << endl;
    e=6;
    it=poly1.emplaceAfter(it, e, 60);
    e=7;
    it=poly1.emplaceAfter(it, e, 70);
    cout << poly1 << endl;
    while(it->_next)
    {
        it=it->_next;
    }
    e=8;
    it=poly1.emplaceAfter(it, e, 80);
    e=9;
    it=poly1.emplaceAfter(it, e, 90);
    
    // Test void printList(ostream & stream) const;
    cout << "________Test printList(ostream & stream)________" << endl;
    poly1.printList(cout);
    cout << endl;
    
    // Test NodeList<Element> *  popFront();
    cout << "________Test popFront()________" << endl;
    poly1.popFront();
    cout << poly1 << endl;
    
    // Test NodeList<Element> * insertBegin(Term<Element> const & term);
    cout << "________Test insertBegin(Term<Element> const & term)________" << endl;
    poly1.insertBegin(Term<eltType>("20*x0^1*x1^2*x3^3"));
    poly1.insertBegin(Term<eltType>("30*x4^4*x5^5"));
    cout << poly1 << endl;
    
    // Test NodeList<Element> * insertAfter(NodeList<Element> * it, Term<Element> const & term);
    cout << "________Test insertAfter(NodeList<Element> * it, Term<Element> const & term)________" << endl;
    while(it->_next)
    {
        it=it->_next;
    }
    it=poly1.insertAfter(it, Term<eltType>("20*x0^1*x1^2*x3^3"));
    it=poly1.insertAfter(it, Term<eltType>("30*x4^4*x5^5"));
    cout << poly1 << endl;
    
    // Test NodeList<Element> * getBegin();
    cout << "________Test getBegin()________" << endl;
    SingleList<eltType> poly2;
    it=poly2.getBegin();
    e=1;
    it=poly2.emplaceAfter(it, e, 10);
    e=2;
    it=poly2.emplaceAfter(it, e, 20);
    e=3;
    it=poly2.emplaceAfter(it, e, 30);
    e=4;
    it=poly2.emplaceAfter(it, e, 40);
    cout << poly2 << endl;
    
    // Test bool empty();
    cout << "________Test empty()________" << endl;
    cout << "poly2.empty(): " << poly2.empty() << endl;
    SingleList<eltType> poly3;
    cout << "poly3.empty(): " << poly3.empty() << endl << endl;
    
    // Test Term<Element> const & term front() const;
    cout << "________Test front()________" << endl;
    cout << "First term of poly2: " << poly2.front() << endl << endl;
    
    // Test SingleList(SingleList const & toCopy);
    cout << "________Test SingleList(SingleList const & toCopy)________" << endl;
    SingleList<eltType> poly4(poly2);
    cout << poly4 << endl;
    
    // Test SingleList & operator=(SingleList const & toCopy);
    cout << "________Test operator=(SingleList const & toCopy)________" << endl;
    poly4=poly1;
    cout << "poly4: " <<poly4 << endl;
    SingleList<eltType> poly5;
    poly5=poly4;
    cout << "poly5: " << poly5 << endl;
    
    // Test NodeList<Element> * emplaceOn(NodeList<Element> * it, Element coefficient, int numMonomial);
    cout << "________Test emplaceOn(NodeList<Element> * it, Element coefficient, int numMonomial)________" << endl;
    it=poly5.getBeforeBegin();
    e=100;
    it=poly5.emplaceOn(it, e, 1000);
    e=200;
    it=poly5.emplaceOn(it, e, 2000);
    e=300;
    it=poly5.emplaceOn(it, e, 3000);
    cout << "poly5: " << poly5 << endl;
    
    
    // Test void deleteAfter(NodeList<Element> * it);
    cout << "________Test deleteAfter(NodeList<Element> * it)________" << endl;
    poly5.deleteAfter(it);
    cout << "poly5: " << poly5 << endl;
    
    return 0;
}
