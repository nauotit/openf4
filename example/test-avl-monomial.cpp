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
 *  \file test-avl-monomial.cpp
 *  \example test-avl-monomial.cpp
 *  \brief AvlMonomial regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "../include/avl-monomial.h"

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=2;

int main (int argc, char **argv)
{
    cout << "#########################################################" << endl;
    cout << "#                    TEST AVL MONOMIAL                  #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Test AvlMonomial();
    cout << "________Test AvlMonomial()________" << endl;
    AvlMonomial avlMon1;
    cout << avlMon1 << endl << endl;
    
    // Test int insert(int numMon, bool lt);
    cout << "________Test insert(int numMon, bool lt)________" << endl;
    avlMon1.insert(10, true);
    avlMon1.insert(20, false);
    avlMon1.insert(30, true);
    avlMon1.insert(50, false);
    avlMon1.insert(100, true);
    avlMon1.insert(40, false);
    avlMon1.insert(25, true);
    avlMon1.insert(60, true);
    cout << "Result of insert: " << avlMon1.insert(25, true) << endl << "avlMon1: " << endl << avlMon1 << endl << endl;
    
    // Test Node* findBiggest();
    cout << "________Test findBiggest(Node* p)________" << endl;
    NodeAvlMonomial * tmp = avlMon1.findBiggest();
    cout << "Biggest node: " << tmp->_numMonomial << endl << endl;
    
    // Test Node* findNextBiggest(Node* p);
    cout << "________Test findNextBiggest(Node* p)________" << endl;
    tmp=avlMon1.findNextBiggest(tmp);
    cout << "Next biggest node: " << tmp->_numMonomial << endl;
    tmp=avlMon1.findNextBiggest(tmp);
    cout << "Next biggest node: " << tmp->_numMonomial << endl;
    tmp=avlMon1.findNextBiggest(tmp);
    cout << "Next biggest node: " << tmp->_numMonomial << endl;
    tmp=avlMon1.findNextBiggest(tmp);
    cout << "Next biggest node: " << tmp->_numMonomial << endl;
    tmp=avlMon1.findNextBiggest(tmp);
    cout << "Next biggest node: " << tmp->_numMonomial << endl << endl;
    
    // Test int size();
    cout << "________Test size()________" << endl;
    cout << "Size of avlMon1: " << avlMon1.size() << endl << endl;
    
    // Test void reset();
    cout << "________Test reset()________" << endl;
    avlMon1.reset();
    cout << "Size of avlMon1: " << avlMon1.size() << endl << endl;
    
    // benchmark 
    clock_t start;
    int i=0;
    
    cout << "________Benchmark________" << endl << endl;
    
    for(int k=0; k<10; k++)
    {
        start=clock();
        for(int j=0; j<100000; j++)
        {
            avlMon1.insert(rand()%10000, 0);
        }
        cout << "Time insert 100000 elements with avl: " << ((double)(clock() - start))*1000/CLOCKS_PER_SEC << " ms" << endl << endl;
        
        start=clock();
        i=0;
        tmp=avlMon1.findBiggest();
        i++;
        while(tmp)
        {
            tmp=avlMon1.findNextBiggest(tmp);
            i++;
        }
        cout << "Number of elements: " << i << endl; 
        cout << "Time parcours 10000 elements with avl: " << ((double)(clock() - start))*1000/CLOCKS_PER_SEC << " ms" << endl << endl;
        
        start=clock();
        avlMon1.reset();
        cout << "Time to reset the AVL " << ((double)(clock() - start))*1000/CLOCKS_PER_SEC << " ms" << endl << endl;
    }
    
    return 0;
}
