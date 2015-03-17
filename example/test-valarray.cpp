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
#include <cstring>
#include <valarray>
#include <cstdlib>
#include <ctime>
#include <xmmintrin.h>

using namespace std;

int main (int argc, char **argv)
{
    cout << endl;
    cout << "#########################################################" << endl;
    cout << "#                    TEST VALLARAY                      #" << endl;
    cout << "#########################################################" << endl << endl;
    
    int i, j;
    int MODULO=65521;
    clock_t start;
    
    srand(time(0));
    
    valarray<int> v1(10000);
    valarray<int> v2(10000);
    
    int a1[10000];
    int a2[10000];
    
    int * b1 = new int[10000];
    int * b2 = new int[10000];
    
    start=clock();
    for(j=0; j<10000; j++)
    {
        for(i=0; i<10000; i++)
        {
            v1[i]=rand()%MODULO;
            v2[i]=rand()%MODULO;
        }
        v1+=v2;
        v1%=MODULO;
    }
    
    cout << "Time to add 2 valarray: " << ((double)(clock() - start))/CLOCKS_PER_SEC << " s" << endl << endl;
    cout << "v1[100]: " << v1[100] << endl;
    cout << "v2[100]: " << v2[100] << endl << endl;
    
    start=clock();
    for(j=0; j<10000; j++)
    {
        for(i=0; i<10000; i++)
        {
            a1[i]=rand()%MODULO;
            a2[i]=rand()%MODULO;
        }
        for(i=0; i<10000; i++)
        {
            a1[i]+=a2[i];
            a1[i]%=MODULO;
        }
    }
    cout << "Time to add 2 array: " << ((double)(clock() - start))/CLOCKS_PER_SEC << " s" << endl << endl;
    cout << "a1[100]: " << a1[100] << endl;
    cout << "a2[100]: " << a2[100] << endl << endl;
    
    
    typedef int v4si __attribute__ ((vector_size (16)));
    int dataSize=4;
    v4si *dest_vect;
    v4si *vec_vect;
    v4si res;
    
    int largeur=10000;
    int deb=0;
    int mul=1;

    int quotient = (largeur - deb) / dataSize;
    
    start=clock();
    for(j=0; j<10000; j++)
    {
        for(i=0; i<10000; i++)
        {
            b1[i]=rand()%MODULO;
            b2[i]=rand()%MODULO;
        }
        
        for (i = deb; i < (deb + quotient * dataSize); i = i + dataSize)
        {
            dest_vect = (v4si *) (&b1[i]);
            vec_vect = (v4si *) (&b2[i]);
            res = ((*dest_vect) + (*vec_vect)) % MODULO;
            memcpy (b1 + i, &res, dataSize * sizeof (int));
        }
        for (i = (deb + quotient * dataSize); i < largeur; i++)
        {
            b1[i] = (b1[i] + mul * b2[i]) % MODULO;
        }
    }
    cout << "Time to add 2 array with simd: " << ((double)(clock() - start))/CLOCKS_PER_SEC << " s" << endl << endl;
    cout << "b1[100]: " << b1[100] << endl;
    cout << "b2[100]: " << b2[100] << endl;
    
    return 0;
}


