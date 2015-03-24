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
#include <set>
#include <tuple>
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
    
    // Test order 
    cout << "________Test order, numPol fixed________" << endl;
    avlPol1.reset();
    avlPol1.insert(10, 20, 5);
    avlPol1.insert(10, 20, 10);
    avlPol1.insert(10, 30, 10);
    avlPol1.insert(10, 40, 10);
    cout << avlPol1 << endl << endl;
    tmp = avlPol1.findBiggest();
    cout << "Biggest node: numMon = " << tmp->_numMonomial << ", nbTerm = " << tmp->_nbTerms << ", numPol = " << tmp->_numPolynomial << endl;
    tmp=avlPol1.findNextBiggest(tmp);
    cout << "Next biggest node: numMon = " << tmp->_numMonomial << ", nbTerm = " << tmp->_nbTerms << ", numPol = " << tmp->_numPolynomial << endl;
    tmp=avlPol1.findNextBiggest(tmp);
    cout << "Next biggest node: numMon = " << tmp->_numMonomial << ", nbTerm = " << tmp->_nbTerms << ", numPol = " << tmp->_numPolynomial << endl;
    tmp=avlPol1.findNextBiggest(tmp);
    cout << "Next biggest node: numMon = " << tmp->_numMonomial << ", nbTerm = " << tmp->_nbTerms << ", numPol = " << tmp->_numPolynomial << endl << endl;
    tmp = avlPol1.findNextBiggest(tmp);
    if(tmp!=0)
    {
        cout << "tmp not nil" << endl;
    }
    else
    {
        cout << "tmp nil" << endl;
    }
    
    cout << "________Test order, numMon fixed________" << endl;
    avlPol1.reset();
    avlPol1.insert(10, 20, 5);
    avlPol1.insert(10, 20, 10);
    avlPol1.insert(20, 20, 20);
    avlPol1.insert(30, 20, 20);
    cout << avlPol1 << endl << endl;
    tmp = avlPol1.findBiggest();
    cout << "Biggest node: numMon = " << tmp->_numMonomial << ", nbTerm = " << tmp->_nbTerms << ", numPol = " << tmp->_numPolynomial << endl;
    tmp=avlPol1.findNextBiggest(tmp);
    cout << "Next biggest node: numMon = " << tmp->_numMonomial << ", nbTerm = " << tmp->_nbTerms << ", numPol = " << tmp->_numPolynomial << endl;
    tmp=avlPol1.findNextBiggest(tmp);
    cout << "Next biggest node: numMon = " << tmp->_numMonomial << ", nbTerm = " << tmp->_nbTerms << ", numPol = " << tmp->_numPolynomial << endl;
    tmp=avlPol1.findNextBiggest(tmp);
    cout << "Next biggest node: numMon = " << tmp->_numMonomial << ", nbTerm = " << tmp->_nbTerms << ", numPol = " << tmp->_numPolynomial << endl << endl;
    tmp = avlPol1.findNextBiggest(tmp);
    if(tmp!=0)
    {
        cout << "tmp not nil" << endl;
    }
    else
    {
        cout << "tmp nil" << endl;
    }
    
    cout << "________Test order, nbTerms fixed________" << endl;
    avlPol1.reset();
    avlPol1.insert(10, 20, 10);
    avlPol1.insert(20, 20, 10);
    avlPol1.insert(30, 30, 10);
    avlPol1.insert(30, 40, 10);
    cout << avlPol1 << endl << endl;
    tmp = avlPol1.findBiggest();
    cout << "Biggest node: numMon = " << tmp->_numMonomial << ", nbTerm = " << tmp->_nbTerms << ", numPol = " << tmp->_numPolynomial << endl;
    tmp=avlPol1.findNextBiggest(tmp);
    cout << "Next biggest node: numMon = " << tmp->_numMonomial << ", nbTerm = " << tmp->_nbTerms << ", numPol = " << tmp->_numPolynomial << endl;
    tmp=avlPol1.findNextBiggest(tmp);
    cout << "Next biggest node: numMon = " << tmp->_numMonomial << ", nbTerm = " << tmp->_nbTerms << ", numPol = " << tmp->_numPolynomial << endl;
    tmp=avlPol1.findNextBiggest(tmp);
    cout << "Next biggest node: numMon = " << tmp->_numMonomial << ", nbTerm = " << tmp->_nbTerms << ", numPol = " << tmp->_numPolynomial << endl << endl;
    tmp = avlPol1.findNextBiggest(tmp);
    if(tmp!=0)
    {
        cout << "tmp not nil" << endl;
    }
    else
    {
        cout << "tmp nil" << endl;
    }
    
    
    // benchmark 
    clock_t start;
    int i=0;
    
    cout << "________Benchmark________" << endl << endl;
    
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
        tmp=avlPol1.findNextBiggest(tmp);
        i++;
        while(tmp)
        {
            tmp=avlPol1.findNextBiggest(tmp);
            i++;
        }
        cout << "Number of elements: " << i << ", avlPol1.size() = " << avlPol1.size() << endl; 
        cout << "Time parcours 10000 elements with avl: " << ((double)(clock() - start))*1000/CLOCKS_PER_SEC << " ms" << endl << endl;
        
        start=clock();
        avlPol1.reset();
        cout << "Time to reset the AVL " << ((double)(clock() - start))*1000/CLOCKS_PER_SEC << " ms" << endl << endl;
    }
    
    // comparison with set
    cout << "________Comparison with set________" << endl << endl;

    struct cmpTaggedPolynomial
    {
        public:
            bool operator()(std::tuple<int, int, int> const & a , std::tuple<int, int, int> const & b)
            {
                
                if( std::get<1>(a) > std::get<1>(b) )
                { 
                    return true;
                }
                else if (std::get<1>(a) < std::get<1>(b) )
                {
                    return false;
                }
                else if (std::get<2>(a) > std::get<2>(b) )
                {
                    return true;
                }
                else if (std::get<2>(a) < std::get<2>(b) )
                {
                    return false;
                }
                else if (std::get<0>(a) > std::get<0>(b))
                {
                    return true;
                }
                else if (std::get<0>(a) < std::get<0>(b))
                {
                    return false;
                }
                else
                {
                    return false;
                }
            }
    };
    set<std::tuple<int, int, int>, cmpTaggedPolynomial> s;
    typename set<tuple<int, int, int>>::const_iterator itPolBeg;
    
    int a, b, c;
    start=clock();
    for(int j=0; j<100000; j++)
    {
        a=rand()%1000;
        b=rand()%10000;
        c=rand()%100;
        avlPol1.insert(a, b, c);
        s.emplace(a, b, c);
    }
    cout << "Number of elements in avl: " << avlPol1.size() << endl; 
    cout << "Number of elements in set: " << s.size() << endl;
    s.clear();
    
    start=clock();
    for(int j=0; j<100000; j++)
    {
        s.emplace(rand()%1000, rand()%10000, rand()%100);
    }
    cout << "Time insert 100000 elements with set: " << ((double)(clock() - start))*1000/CLOCKS_PER_SEC << " ms" << endl << endl;
    
    start=clock();
    i=0;
    itPolBeg=s.begin();
    while(itPolBeg!=s.end())
    {
        itPolBeg++;
        i++;
    }
    cout << "Number of elements: " << i << ", s.size() = " << s.size() << endl; 
    cout << "Time parcours 10000 elements with avl: " << ((double)(clock() - start))*1000/CLOCKS_PER_SEC << " ms" << endl << endl;
    
    start=clock();
    s.clear();
    cout << "Time to reset the AVL " << ((double)(clock() - start))*1000/CLOCKS_PER_SEC << " ms" << endl << endl;

    
    
    return 0;
}
