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
 *  \file test-avl-pointer-critical-pair.cpp
 *  \example test-avl-pointer-critical-pair.cpp
 *  \brief AvlPointerCriticalPair<eltType> regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "../include/avl-pointer-critical-pair.h"

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=2;

int main (int argc, char **argv)
{
    cout << "#########################################################" << endl;
    cout << "#             TEST AVL POINTER CRITICAL PAIR            #" << endl;
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
    cout << "size of the tagged polynomial array: " << CriticalPair<eltType>::getSizeTaggedPolynomialArray() << endl << endl;
    
    // Fill the tagged polynomial array
    List.emplace_back(Polynomial<eltType>("x0+x1+x2+x3+x4+x5"));
    List.emplace_back(Polynomial<eltType>("x0*x1+x1*x2+x2*x3+x3*x4+x0*x5+x4*x5"));
    List.emplace_back(Polynomial<eltType>("x0*x1*x2+x1*x2*x3+x2*x3*x4+x0*x1*x5+x0*x4*x5+x3*x4*x5"));
    List.emplace_back(Polynomial<eltType>("x0*x1*x2*x3+x1*x2*x3*x4+x0*x1*x2*x5+x0*x1*x4*x5+x0*x3*x4*x5+x2*x3*x4*x5"));
    List.emplace_back(Polynomial<eltType>("x3+x1*x2*x3*x4+x2*x5+x4*x5+x2*x3*x4*x5"));
    
    
    // Test AvlPointerCriticalPair<eltType>();
    cout << "________Test AvlPointerCriticalPair<eltType>()________" << endl;
    AvlPointerCriticalPair<eltType> avlCp1;
    cout << avlCp1 << endl << endl;
    
    // Test int insert(int numMon, bool lt);
    cout << "________Test insert(CriticalPair<eltType> * cp)________" << endl;
    
    DynamicArray<CriticalPair<eltType>> cpArray(100,10,2);
    CriticalPair<eltType> * it = cpArray.getBegin();
    it->setCriticalPair(0,1);
    avlCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(0,4);
    avlCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(1,3);
    avlCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(2,1);
    avlCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(4,1);
    avlCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(4,3);
    avlCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(2,3);
    avlCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(0,3);
    avlCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(0,1);

    cout << "Result of insert: " << avlCp1.insert(it) << endl << "avlCp1: " << endl << avlCp1 << endl << endl;
    
    // Test Node* findBiggest();
    cout << "________Test findBiggest(Node* p)________" << endl;
    NodeAvlPointerCriticalPair<eltType> * tmp = avlCp1.findBiggest();
    cout << "Biggest node: " << *(tmp->_cp) << endl << endl;
    
    // Test Node* findNextBiggest(Node* p);
    cout << "________Test findNextBiggest(Node* p)________" << endl;
    tmp=avlCp1.findNextBiggest(tmp);
    cout << "Next biggest node: " << *tmp->_cp << endl;
    tmp=avlCp1.findNextBiggest(tmp);
    cout << "Next biggest node: " << *tmp->_cp << endl;
    tmp=avlCp1.findNextBiggest(tmp);
    cout << "Next biggest node: " << *tmp->_cp << endl;
    tmp=avlCp1.findNextBiggest(tmp);
    cout << "Next biggest node: " << *tmp->_cp << endl;
    tmp=avlCp1.findNextBiggest(tmp);
    cout << "Next biggest node: " << *tmp->_cp << endl << endl;
    
    // Test Node* findSmallest();
    cout << "________Test findSmallest(Node* p)________" << endl;
    tmp=avlCp1.findSmallest();
    cout << "Smallest node: " << *tmp->_cp << endl << endl;
    
    // Test Node* findNextSmallest(Node* p);
    cout << "________Test findNextSmallest(Node* p)________" << endl;
    tmp=avlCp1.findNextSmallest(tmp);
    cout << "Next smallest node: " << *tmp->_cp << endl;
    tmp=avlCp1.findNextSmallest(tmp);
    cout << "Next smallest node: " << *tmp->_cp << endl;
    tmp=avlCp1.findNextSmallest(tmp);
    cout << "Next smallest node: " << *tmp->_cp << endl;
    tmp=avlCp1.findNextSmallest(tmp);
    cout << "Next smallest node: " << *tmp->_cp << endl;
    tmp=avlCp1.findNextSmallest(tmp);
    cout << "Next smallest node: " << *tmp->_cp << endl << endl;
    
    // Test int size();
    cout << "________Test size()________" << endl;
    cout << "Size of avlCp1: " << avlCp1.size() << endl << endl;
    
    // Test void reset();
    cout << "________Test reset()________" << endl;
    avlCp1.reset();
    cout << "Size of avlCp1: " << avlCp1.size() << endl << endl;
    
    // Test the avl consistency
    cout << "________Test testAVL()________" << endl;
    it = cpArray.getBegin();
    it->setCriticalPair(0,1);
    avlCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(0,4);
    avlCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(1,3);
    avlCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(2,1);
    avlCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(4,1);
    avlCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(4,3);
    avlCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(2,3);
    avlCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(0,3);
    avlCp1.insert(it);
    it=cpArray.getNext(it);
    it->setCriticalPair(0,1);
    
    avlCp1.testAVL();
    cout << endl;
    
    return 0;
}
