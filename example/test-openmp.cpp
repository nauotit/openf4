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
#include <chrono>
#include <cstdlib>
#include <omp.h>
extern "C"
{
    #include <cblas.h>
}

#define NUM_THREADS 1

using namespace std;

void addMul(int * a, int * b)
{
    for(int i=0; i<100000; i++)
    {
        a[i]+=(b[i]*1000)%65521;
    }
}

//void addMul(float * a, const float * b)
//{
    ////for(int i=0; i<100000; i++)
    ////{
        ////a[i]+=((int)b[i]*1000);
    ////}
    //cblas_saxpy( (const int)100000, (const float)1000, b, (const int)1, a, (const int)1);
//}

void addMul(float * a, float * b)
{
    float *x = (float *)__builtin_assume_aligned(a, 16);
    float *y = (float *)__builtin_assume_aligned(b, 16);
    for(int i=0; i<100000; i++)
    {
        x[i]+=((int)y[i]*1000);
    }
}

int main (int argc, char **argv)
{
    cout << "#########################################################" << endl;
    cout << "#                        TEST OPENMP                    #" << endl;
    cout << "#########################################################" << endl << endl;
    
    float a[100000];
    float b[100000];
    float c[100000];
    float d[100000];
    float e[100000];
    float f[100000];
    float g[100000];
    float h[100000];
    
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
    chrono::steady_clock::time_point start=chrono::steady_clock::now();
    typedef chrono::duration<int,milli> millisecs_t;
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
    cout << "Time to add 2 array: " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms " << endl;
    
    //cout << "before " << a[10] << " " << b[100] << endl;
    //addMul(a,b,mul);
    //cout << "after " << a[10] << " " << b[100] << endl;
    
    return 0;
}
