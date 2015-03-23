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
 *  \file test-valarray.cpp
 *  \example test-valarray.cpp
 *  \brief Matrix valarray regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <set>

#include "../include/avl.h"

using namespace std;
using namespace F4;

int main (int argc, char **argv)
{
    cout << endl;
    cout << "#########################################################" << endl;
    cout << "#                         TEST AVL                      #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Test Node(keyType k);
    cout << "________Test Node(keyType k)________" << endl;
    Node<int> n1(10);
    printNode(&n1);
    cout << endl << endl;
    
    // Test Node* insert(Node<keyType>* p, keyType k);
    cout << "________Test insert(Node<keyType>* p, keyType k)________" << endl;
    srand(time(0));
    Node<int> * root=0;
    for(int j=0; j<100; j++)
    {
        root=insert(root, rand()%1000);
    }
    printNode(root);
    
    // Test Node<keyType>* findSmallest(Node<keyType>* p);
    cout << "________Test findSmallest(Node<keyType>* p)________" << endl;
    Node<int> * tmp = findSmallest(root);
    cout << "Smallest node: " << tmp->_key << endl << endl;
    
    // Test Node<keyType>* findNextSmallest(Node<keyType>* p);
    cout << "________Test findNextSmallest(Node<keyType>* p)________" << endl;
    tmp=findNextSmallest(tmp);
    cout << "Next smallest node: " << tmp->_key << endl;
    tmp=findNextSmallest(tmp);
    cout << "Next smallest node: " << tmp->_key << endl;
    tmp=findNextSmallest(tmp);
    cout << "Next smallest node: " << tmp->_key << endl;
    tmp=findNextSmallest(tmp);
    cout << "Next smallest node: " << tmp->_key << endl;
    tmp=findNextSmallest(tmp);
    cout << "Next smallest node: " << tmp->_key << endl << endl;
    
    // Test void clear(Node<keyType>* p);
    cout << "________Test clear(Node<keyType>* p)________" << endl;
    //clear(root);
    //printNode(root);
    
    // benchmark 
    clock_t start;
    int i;
    
    cout << "______________AVL______________" << endl << endl;
    
    start=clock();
    for(int j=0; j<100000; j++)
    {
        root=insert(root, rand()%10000);
    }
    cout << "Time insert 100000 elements with avl: " << ((double)(clock() - start))*1000/CLOCKS_PER_SEC << " ms" << endl << endl;
    
    start=clock();
    i=0;
    tmp=findSmallest(root);
    i++;
    while(tmp)
    {
        tmp=findNextSmallest(tmp);
        i++;
    }
    cout << "Number of elements: " << i << endl; 
    cout << "Time parcours 10000 elements with avl: " << ((double)(clock() - start))*1000/CLOCKS_PER_SEC << " ms" << endl << endl;
    
    start=clock();
    clear(root);
    cout << "Time clear 100000 elements with avl: " << ((double)(clock() - start))*1000/CLOCKS_PER_SEC << " ms" << endl << endl;
    
    
    cout << "______________set______________" << endl << endl;
    set<int> s;
    start=clock();
    for(int j=0; j<100000; j++)
    {
        s.emplace(rand()%10000);
    }
    cout << "Time insert 100000 elements with set: " << ((double)(clock() - start))*1000/CLOCKS_PER_SEC << " ms" << endl << endl;
    
    start=clock();
    i=0;
    for(set<int>::const_iterator it=s.begin(); it!=s.end(); ++it)
    {
        i++;
    }
    cout << "Number of elements: " << i << endl; 
    cout << "Time parcours 10000 elements with set: " << ((double)(clock() - start))*1000/CLOCKS_PER_SEC << " ms" << endl << endl;
    
    start=clock();
    s.clear();
    cout << "Time clear 100000 elements with set: " << ((double)(clock() - start))*1000/CLOCKS_PER_SEC << " ms" << endl << endl;
    
    return 0;
}
