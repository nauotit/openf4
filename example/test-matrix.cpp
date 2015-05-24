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
 *  \file test-matrix.cpp
 *  \example test-matrix.cpp
 *  \brief Matrix regression tests.
 *  \ingroup examples
 *  \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
 */

#include <iostream>
#include <vector>
#include "../include/matrix.h"
#include "../include/element-prime.h"
#include "../include/element-zech-prime.h"

using namespace F4;
using namespace std;

// Global variable
int F4::VERBOSE=2;
int F4::NB_THREAD=min(1, omp_get_num_procs());

int main (int argc, char **argv)
{
    cout << endl;
    cout << "#########################################################" << endl;
    cout << "#                    TEST MATRIX                        #" << endl;
    cout << "#########################################################" << endl << endl;
    
    typedef ElementPrime<int> eltType;
    ElementPrime<int>::setModulo(65521);
    
    //typedef Givaro::Modular<Givaro::Log16, Givaro::Log16> Field;
    //int modulo=8209;
    //Field F(modulo);
    //typedef ElementZechPrime<Field> eltType;
    //eltType::setField(F);
    
    // Test Matrix();
    cout << "________Test Matrix()________" << endl;
    Matrix<eltType> mat1;
    cout << mat1 << endl;
    
    // Test Matrix(int height, int width);
    cout << "________Test Matrix(int height, int width);________" << endl;
    Matrix<eltType> mat2(10,20);
    cout << mat2 << endl;
    
    // Test Matrix(std::string filename)
    cout << "________Test Matrix(std::string filename)________" << endl;
    Matrix<eltType> mat3("../data/M_text_basic1.txt");
    cout << mat3 << endl;
    
    
    // Test Element & operator() (unsigned row, unsigned col);
    cout << "________Test operator() (unsigned row, unsigned col)________" << endl;
    for(int i=0; i<10; i++)
    {
        mat2(i, i) = i;
        mat2(i, i+5) = i+5;
    }
    cout << mat2 << endl;
              
    // Test Element operator() (unsigned row, unsigned col) const;
    cout << "________Test operator() (unsigned row, unsigned col) const________" << endl;
    cout << "mat2(5,5): "<< mat2(5,5) << endl;
    cout << "mat2(5,7): " << mat2(5,7) << endl;
    cout << "mat2(7,5): " << mat2(7,5) << endl << endl;
            
    // Test void setElement (unsigned row, unsigned col, Element const & element);
    cout << "________Test setElement (unsigned row, unsigned col, Element const & element)________" << endl;
    eltType e0;
    e0=20;
    for(int i=0; i<10; i++)
    {
        mat2.setElement(i, 9-i, e0);
    }
    cout << mat2 << endl;
    
    // Test Element getElement(unsigned row, unsigned col) const;
    cout << "________Test getElement(unsigned row, unsigned col)________" << endl;
    cout << "mat2(5,5): "<< mat2.getElement(5,5) << endl;
    cout << "mat2(5,7): " << mat2.getElement(5,7) << endl;
    cout << "mat2(7,5): " << mat2.getElement(7,5) << endl << endl;
    
    // Test Element const * getRow (unsigned row) const;
    cout << "________Test operator() getRow (unsigned row) const________" << endl;
    eltType * row4=mat2.getRow(4);
    for(int i=0; i< mat2.getWidth(); i++)
    {
        cout << " " << row4[i] << " ";
    }
    cout << endl << endl;
    
    // Test int getHeight();
    cout << "________Test getHeight()________" << endl;
    cout << "Height of mat2: " << mat2.getHeight() << endl << endl;
    
    // Test int getWidth();
    cout << "________Test getWidth()________" << endl;
    cout << "Width of mat2: " << mat2.getWidth() << endl << endl;
    
    // Test void setNbPiv(int nbPiv);
    cout << "________Test setNbPiv(int nbPiv)________" << endl;
    mat2.setNbPiv(4);
    cout << endl;
            
    // Test int getNbPiv();
    cout << "________Test getNbPiv()________" << endl;
    cout << "Number of pivot of mat2: " << mat2.getNbPiv() << endl << endl;
            
    // Test void setTau(int * tau);
    cout << "________Test setTau(int * tau)________" << endl;
    int tau[20]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    mat2.setTau(tau);
    cout << endl;
    
    // Test int * getTau();
    cout << "________Test getTau()________" << endl;
    cout << "tau of mat2: ";
    for(int i=0; i< mat2.getWidth(); i++)
    {
        cout << mat2.getTau()[i] << ", ";
    }
    cout << endl << endl;
            
    // Test void setSigma(int * sigma);
    cout << "________Test setSigma(int * sigma)________" << endl;
    int sigma[20]={19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};
    mat2.setSigma(sigma);
    cout << endl;
            
    // Test int * getSigma();
    cout << "________Test getSigma()________" << endl;
    cout << "sigma of mat2: ";
    for(int i=0; i< mat2.getWidth(); i++)
    {
        cout << mat2.getSigma()[i] << ", ";
    }
    cout << endl << endl;
            
    // Test void setStartTail(int * startTail);
    cout << "________Test setStartTail(int * startTail)________" << endl;
    int startTail[10]={4,4,4,5,5,6,7,7,9,9};
    mat2.setStartTail(startTail);
    cout << endl;
            
    // Test int * getStartTail();
    cout << "________Test getStartTail()________" << endl;
    cout << "startTail of mat2: ";
    for(int i=0; i< mat2.getHeight(); i++)
    {
        cout << mat2.getStartTail()[i] << ", ";
    }
    cout << endl << endl;
            
    // Test void setEndCol(int * encCol);
    cout << "________Test setEndCol(int * encCol)________" << endl;
    int endCol[20]={7,8,9,9,9,2,4,5,6,8,9,9,9,9,9,9,9,9,9,9};
    mat2.setEndCol(endCol);
    cout << endl;
            
    // Test int * getEndCol();
    cout << "________Test getEndCol()________" << endl;
    cout << "endCol of mat2: ";
    for(int i=0; i< mat2.getWidth(); i++)
    {
        cout << mat2.getEndCol()[i] << ", ";
    }
    cout << endl << endl;
    
    // Test void printMatrix (std::ostream & stream = std::cout) const;
    cout << "________Test printMatrix (std::ostream & stream = std::cout)________" << endl;
    cout << "mat2: " << endl;
    mat2.printMatrix(cout);
    cout << endl;
    
    //// Test void normalizeRow(int numRow, int start, int end);
    //cout << "________Test normalizeRow(int numRow, int start, int end)________" << endl;
    //mat2.normalizeRow(mat2.getRow(4), 0, mat2.getWidth());
    //mat2.normalizeRow(mat2.getRow(8), 10, mat2.getWidth());
    //cout << mat2 << endl;
    
    // void multRow(Element * row, Element const & element, int start, int end);
    cout << "________Test multRow(Element * row, Element const & element, int start, int end)________" << endl;
    eltType e1, e2;
    e1=10;
    e2=5;
    mat2.multRow(mat2.getRow(4), e1, 0, mat2.getWidth());
    mat2.multRow(mat2.getRow(8), e2, 10, mat2.getWidth());
    cout << mat2 << endl;
    
    // Test addMultRow(Element * row1, Element * row2, Element element, int start, int end);
    cout << "________Test addMultRow(Element * row1, Element * row2, Element element, int start, int end)________" << endl;
    
    mat2.addMultRow(mat2.getRow(0), mat2.getRow(1), e1, 0, mat2.getWidth());
    mat2.addMultRow(mat2.getRow(9), mat2.getRow(1), e2, 5, mat2.getWidth());
    cout << mat2 << endl;
    
    // Test void swapRow(int numRow1, int numRow2);
    cout << "________Test swapRow(int numRow1, int numRow2)________" << endl;
    mat2.swapRow(1, 5);
    cout << mat2 << endl;
    
    // Test void swapCol(int numCol1, int numCol2, int start, int end);
    cout << "________Test swapCol(int numCol1, int numCol2, int start, int end)________" << endl;
    mat2.swapCol(1, 10, 0, mat2.getHeight());
    cout << mat2 << endl;
    
    // Test int echelonize ();
    cout << "________Test echelonize()________" << endl;
    mat3.echelonize();
    cout << mat3 << endl;
    
    //// Cyclic 8
    //vector<Matrix<eltType>> matArray;
    //string filename;
    //string filename2;
    //for(int i=0; i<38; i++)
    //{
        //filename="../data/"+to_string(i+1)+"before-echelonize-cyclic8.txt";
        //matArray.emplace_back(filename);
        ////filename2="../data/M"+to_string(i)+"_text_basic.pgm";
        ////matArray[i].printMatrix(filename2);
    //}
    
    //chrono::steady_clock::time_point start=chrono::steady_clock::now();
    //typedef chrono::duration<int,milli> millisecs_t;
    
    //ofstream fileCyclic8("time-cyclic8.txt");
    //chrono::steady_clock::time_point start1;
    //for(size_t i=0; i< matArray.size(); i++)
    //{
        //cout << i << ": ";
        //start1=chrono::steady_clock::now();
        //matArray[i].echelonize();
        //fileCyclic8 << i << " " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start1).count() << endl;
        ////filename2="../data/M"+to_string(i)+"_text_echelonized.pgm";
        ////matArray[i].printMatrix(filename2);
    //}
    //fileCyclic8.close();
    //cout << "time to echenonize " << matArray.size() << " matrix: " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms" << endl << endl;
    
    //matArray.clear();
    
    //// Semaev 16
    //for(int i=0; i<29; i++)
    //{
        //filename="../data/"+to_string(i+1)+"before-echelonize-semaev.txt";
        //matArray.emplace_back(filename);
    //}
    
    //start=chrono::steady_clock::now();
    
    //ofstream fileSemaev("time-semaev16.txt");
    //for(size_t i=0; i< matArray.size(); i++)
    //{
        //cout << i << ": ";
        //start1=chrono::steady_clock::now();
        //matArray[i].echelonize();
        //fileSemaev << i << " " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start1).count() << endl;
    //}
    //fileSemaev.close();
    //cout << "time to echenonize " << matArray.size() << " matrix: " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms" << endl << endl;
    
    //matArray.clear();
    
    //// Katsura 12
    //for(int i=0; i<12; i++)
    //{
        //filename="../data/"+to_string(i+1)+"before-echelonize-katsura12.txt";
        //matArray.emplace_back(filename);
    //}
    
    //start=chrono::steady_clock::now();
    
    //for(size_t i=0; i< matArray.size(); i++)
    //{
        //cout << i << ": ";
        //matArray[i].echelonize();
    //}
    //cout << "time to echenonize " << matArray.size() << " matrix: " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms" << endl << endl;
    
    //// Test Matrix(std::string filename)
    //cout << "________Test Matrix(std::string filename)________" << endl;
    //Matrix<eltType> mat3("../data/20before-echelonize-cyclic8.txt");
    //Matrix<eltType> mat4("../data/15before-echelonize-semaev.txt");
    //string filename1="cyclic8.pgm";
    //mat3.printMatrix(filename1);

    //// Test int echelonize ();
    //cout << "________Test echelonize()________" << endl;
    //int rank = mat3.echelonize();
    //cout << "Rank = " << rank << endl << endl;
    //rank = mat4.echelonize();
    //cout << "Rank = " << rank << endl << endl;
    //filename1="cyclic8-after-echelonize.pgm";
    //mat3.printMatrix(filename1);
    
    return 0;
}


