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
 *  \file test-openmp.cpp
 *  \example test-openmp.cpp
 *  \brief Test of openmp.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */


#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <omp.h>

#define NUM_THREADS 2

using namespace std;

void addMul(int * a, int * b)
{
    for(int i=0; i<100000; i++)
    {
        a[i]+=(b[i]*1000)%65521;
    }
}

int main (int argc, char **argv)
{
    cout << "#########################################################" << endl;
    cout << "#                        TEST OPENMP                    #" << endl;
    cout << "#########################################################" << endl << endl;
    
    int a[100000];
    int b[100000];
    int c[100000];
    int d[100000];
    int e[100000];
    int f[100000];
    int g[100000];
    int h[100000];
    
    int MODULO=65521;
    
    for(int i=0; i<100000; i++)
    {
        a[i]=rand()%MODULO;
        b[i]=rand()%MODULO;
        c[i]=rand()%MODULO;
        d[i]=rand()%MODULO;
        e[i]=rand()%MODULO;
        f[i]=rand()%MODULO;
        g[i]=rand()%MODULO;
        h[i]=rand()%MODULO;
    }
    
    //omp_set_num_threads(NUM_THREADS);
    //clock_t start=clock();
    //#pragma omp parallel shared(a,b,MODULO, mul)
    //for(int j=0; j<20000 ; j++)
    //{
        //#pragma omp for schedule(static, 50000)
        //for(int i=0; i<100000; i++)
        //{
            //a[i]+=(b[i]*mul)%MODULO;
        //}
    //}
    //cout << a[10] << " " << b[100] << endl;
    //cout << "Time to add 2 array: " << ((double)(clock() - start))/CLOCKS_PER_SEC << " ms " << endl;
    
    //#pragma omp parallel
    //{
        //int ID=omp_get_thread_num();
        //cout << "hello " << ID << endl;
    //}
    
    omp_set_num_threads(NUM_THREADS);
    cout << a[10] << " " << b[100] << " " << c[1000] << " " << d[10000] << endl;
    clock_t start=clock();
    #pragma omp parallel
    #pragma omp single nowait
    for(int j=0; j<20000 ; j++)
    {
        #pragma omp task shared(a)
        addMul(a,b);
        
        #pragma omp task shared(c)
        addMul(c,d);
        
        #pragma omp task shared(e)
        addMul(e,f);
        
        #pragma omp task shared(g)
        addMul(g,h);
    }
    cout << a[10] << " " << b[100] << " " << c[1000] << " " << d[10000] << endl;
    cout << "Time to add 2 array: " << ((double)(clock() - start))/CLOCKS_PER_SEC << " ms " << endl;
    
    //cout << "before " << a[10] << " " << b[100] << endl;
    //addMul(a,b,mul);
    //cout << "after " << a[10] << " " << b[100] << endl;
    
    return 0;
}
