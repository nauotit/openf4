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
 *  \file test-list-pointer-critical-pair.cpp
 *  \example test-list-pointer-critical-pair.cpp
 *  \brief ListPointerCriticalPair regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "../include/list-pointer-critical-pair.h"

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=2;

int main (int argc, char **argv)
{
    cout << "#########################################################" << endl;
    cout << "#             TEST LIST POINTER CRITICAL PAIR           #" << endl;
    cout << "#########################################################" << endl << endl;
    
    typedef ElementPrime<int> eltType;
    ElementPrime<int>::setModulo(65521);
    
    // Init monomial tools
    MonomialArray monArray(6,10000000,10, 2, 10);
    Term<eltType>::setMonomialArray(&monArray);
    TaggedPolynomial<eltType>::setMonomialArray(&monArray);
    CriticalPair<eltType>::setMonomialArray(&monArray);
    cout << endl;
    
    // Create tagged polynomial array
    vector<TaggedPolynomial<eltType>> List;
    CriticalPair<eltType>::setTaggedPolynomialArray(&List);
    
    // Fill the tagged polynomial array
    List.emplace_back(Polynomial<eltType>("x0+x1+x2+x3+x4+x5"));
    List.emplace_back(Polynomial<eltType>("x0*x1+x1*x2+x2*x3+x3*x4+x0*x5+x4*x5"));
    List.emplace_back(Polynomial<eltType>("x0*x1*x2+x1*x2*x3+x2*x3*x4+x0*x1*x5+x0*x4*x5+x3*x4*x5"));
    List.emplace_back(Polynomial<eltType>("x0*x1*x2*x3+x1*x2*x3*x4+x0*x1*x2*x5+x0*x1*x4*x5+x0*x3*x4*x5+x2*x3*x4*x5"));
    List.emplace_back(Polynomial<eltType>("x3+x1*x2*x3*x4+x2*x5+x4*x5+x2*x3*x4*x5"));
    
    
    // Test ListPointerCriticalPair<eltType>();
    cout << "________Test ListPointerCriticalPair<eltType>()________" << endl;
    ListPointerCriticalPair<eltType> listCp1;
    cout << listCp1 << endl << endl;
    
    // Test void insert(int numMon, bool lt);
    cout << "________Test insert(CriticalPair<eltType> * cp)________" << endl;
    
    DynamicArray<CriticalPair<eltType>> cpArray(100,10,2);
    CriticalPair<eltType> * it = cpArray.getBegin();
    it->setCriticalPair(0,1);
    listCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(0,4);
    listCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(1,3);
    listCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(2,1);
    listCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(4,1);
    listCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(4,3);
    listCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(2,3);
    listCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(0,3);
    listCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(0,1);
    listCp1.insert(it);
    cout << listCp1 << endl << endl;
    
    // Test NodeListPointerCriticalPair<Element> * getRoot();
    cout << "________Test getRoot()________" << endl;
    NodeListPointerCriticalPair<eltType> const * node = listCp1.getRoot();
    cout << "Root: " << *node->_cp << endl << endl;
    
    // Test NodeListPointerCriticalPair<Element> const * getNext(NodeListPointerCriticalPair<Element> const * node) const;
    cout << "________Test getNext(NodeListPointerCriticalPair<Element> const * node)________" << endl;
    node=listCp1.getNext(node);
    cout << "Next node: " << *node->_cp << endl;
    node=listCp1.getNext(node);
    cout << "Next node: " << *node->_cp << endl << endl;
    
    // Test NodeListPointerCriticalPair<Element> const * getNext(NodeListPointerCriticalPair<Element> const * node) const;
    cout << "________Test 2 getNext(NodeListPointerCriticalPair<Element> const * node)________" << endl;
    node = listCp1.getRoot();
    while(node)
    {
        cout << "Next node: " << *node->_cp << endl;
        node=listCp1.getNext(node);
    }
    
    // Test void reset();
    cout << "________Test reset()________" << endl;
    listCp1.reset();
    cout << listCp1 << endl;
    
    cout << "Insert new elements " << endl;
    it = cpArray.getBegin();
    it->setCriticalPair(0,3);
    listCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(0,1);
    listCp1.insert(it);
    cout << listCp1 << endl;
    //node = listCp1.getRoot();
    //cout << "Root: " << *node->_cp << endl;
    //node=listCp1.getNext(node);
    //cout << "Next node: " << *node->_cp << endl;
    //node=listCp1.getNext(node);
    //cout << "Next node: " << *node->_cp << endl;
    //node=listCp1.getNext(node);
    //cout << "Next node: " << *node->_cp << endl << endl;
    
    
    return 0;
}
