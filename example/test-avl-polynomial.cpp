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
 *  \file test-avl-polynomial.cpp
 *  \example test-avl-polynomial.cpp
 *  \brief AvlPolynomial regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "../include/avl-polynomial.h"

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=2;

int main (int argc, char **argv)
{
    cout << "#########################################################" << endl;
    cout << "#                    TEST AVL POLYNOMIAL                #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Test AvlPolynomial();
    cout << "________Test AvlPolynomial()________" << endl;
    AvlPolynomial avlPol1;
    cout << avlPol1 << endl << endl;
    
    // Test int insert(int numPol, int numMon, int nbTerms);
    cout << "________Test insert(int numPol, int numMon, int nbTerms)________" << endl;
    avlPol1.insert(10, 20, 5);
    avlPol1.insert(20, 200, 10);
    avlPol1.insert(30, 1, 1);
    avlPol1.insert(50, 100, 10);
    avlPol1.insert(100, 100, 10);
    avlPol1.insert(40, 100, 5);
    avlPol1.insert(25, 4, 20);
    avlPol1.insert(60, 4, 30);
    cout << "Result of insert: " << avlPol1.insert(25, 10, 100) << endl << "avlPol1: " << endl << avlPol1 << endl << endl;
    
    // Test Node* findBiggest();
    cout << "________Test findBiggest(Node* p)________" << endl;
    NodeAvlPolynomial * tmp = avlPol1.findBiggest();
    cout << "Biggest node: " << tmp->_numMonomial << endl << endl;
    
    // Test Node* findNextBiggest(Node* p);
    cout << "________Test findNextBiggest(Node* p)________" << endl;
    tmp=avlPol1.findNextBiggest(tmp);
    cout << "Next biggest node: numMon = " << tmp->_numMonomial << ", nbTerm = " << tmp->_nbTerms << ", numPol = " << tmp->_numPolynomial << endl;
    tmp=avlPol1.findNextBiggest(tmp);
    cout << "Next biggest node: numMon = " << tmp->_numMonomial << ", nbTerm = " << tmp->_nbTerms << ", numPol = " << tmp->_numPolynomial << endl;
    tmp=avlPol1.findNextBiggest(tmp);
    cout << "Next biggest node: numMon = " << tmp->_numMonomial << ", nbTerm = " << tmp->_nbTerms << ", numPol = " << tmp->_numPolynomial << endl;
    tmp=avlPol1.findNextBiggest(tmp);
    cout << "Next biggest node: numMon = " << tmp->_numMonomial << ", nbTerm = " << tmp->_nbTerms << ", numPol = " << tmp->_numPolynomial << endl;
    tmp=avlPol1.findNextBiggest(tmp);
    cout << "Next biggest node: numMon = " << tmp->_numMonomial << ", nbTerm = " << tmp->_nbTerms << ", numPol = " << tmp->_numPolynomial << endl << endl;
    
    // Test int size();
    cout << "________Test size()________" << endl;
    cout << "Size of avlPol1: " << avlPol1.size() << endl << endl;
    
    // Test void reset();
    cout << "________Test reset()________" << endl;
    avlPol1.reset();
    cout << "Size of avlPol1: " << avlPol1.size() << endl << endl;
    
    // benchmark 
    clock_t start;
    int i=0;
    
    cout << "________Benchmark insert(int numMon, bool lt)________" << endl << endl;
    
    for(int k=0; k<10; k++)
    {
        start=clock();
        for(int j=0; j<100000; j++)
        {
            avlPol1.insert(rand()%1000, rand()%10000, rand()%100);
        }
        cout << "Time insert 100000 elements with avl: " << ((double)(clock() - start))*1000/CLOCKS_PER_SEC << " ms" << endl << endl;
        
        start=clock();
        i=0;
        tmp=avlPol1.findBiggest();
        i++;
        while(tmp)
        {
            tmp=avlPol1.findNextBiggest(tmp);
            i++;
        }
        cout << "Number of elements: " << i << endl; 
        cout << "Time parcours 10000 elements with avl: " << ((double)(clock() - start))*1000/CLOCKS_PER_SEC << " ms" << endl << endl;
        
        start=clock();
        avlPol1.reset();
        cout << "Time to reset the AVL " << ((double)(clock() - start))*1000/CLOCKS_PER_SEC << " ms" << endl << endl;
    }
    
    return 0;
}
