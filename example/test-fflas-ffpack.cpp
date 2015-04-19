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
 *  \file test-fflas-ffpack.cpp
 *  \example test-fflas-ffpack.cpp
 *  \brief Test of PLUQ.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */


#include <iostream>
#include <iomanip>
#include "../include/matrix-generic.h"

using namespace FFPACK;
using namespace std;
using namespace F4;

int main (int argc, char **argv)
{
    cout << "#########################################################" << endl;
    cout << "#                     TEST FFLAS-FFPACK                 #" << endl;
    cout << "#########################################################" << endl << endl;
    
    // Create a field
    typedef Givaro::ModularBalanced<int> Field;
    Field F(65521);
    
     //// Test Matrix();
    //cout << "________Test Matrix()________" << endl;
    //MatrixGeneric<Field> mat1(F);
    //cout << mat1 << endl;
    
    //// Test Matrix(int height, int width);
    //cout << "________Test Matrix(int height, int width);________" << endl;
    //MatrixGeneric<Field> mat2(F,10,20);
    //cout << mat2 << endl;
    
    // Test Matrix(std::string filename)
    cout << "________Test Matrix(std::string filename)________" << endl;
    MatrixGeneric<Field> mat3(F, "../data/9before-echelonize-cyclic8.txt");
    string filename1="block-cyclic8.pgm";
    mat3.printMatrix(filename1);
    
    //// Test Matrix(std::string filename)
    //cout << "________Test Matrix(std::string filename)________" << endl;
    //MatrixGeneric<Field> mat3(F, "../data/M_text_basic1.txt");
    //cout << mat3 << endl;
    //delete[] mat3.getSigma();
    //delete[] mat3.getTau();
    //delete[] mat3.getStartTail();
    //delete[] mat3.getEndCol();

    // Test int echelonize ();
    cout << "________Test echelonize()________" << endl;
    int rank = mat3.echelonize();
    //cout << mat3 << endl;
    cout << "Rank = " << rank << endl << endl;
    filename1="block-cyclic8-after-echelonize.pgm";
    mat3.printMatrix(filename1);
    
    //vector<MatrixGeneric<Field>> matArray;
    //string filename;
    ////string filename2;
    //for(int i=0; i<38; i++)
    //{
        //filename="../data/"+to_string(i+1)+"before-echelonize-cyclic8.txt";
        //matArray.emplace_back(F, filename);
        ////filename2="../data/M"+to_string(i)+"-before-echelonize-cyclic8.pgm";
        ////matArray[i].printMatrix(filename2);
    //}
    
    //clock_t start = clock();
    //for(size_t i=0; i< matArray.size(); i++)
    //{
        //cout << i << ": ";
        //matArray[i].echelonize();
        ////filename2="../data/M"+to_string(i)+"-after-echelonize-cyclic8.pgm";
        ////matArray[i].printMatrix(filename2);
    //}
    //cout << "time to echenonize " << matArray.size() << " matrix: " << ((double)(clock() - start))/CLOCKS_PER_SEC << " s" << endl << endl;
    
    
    return 0;
}
