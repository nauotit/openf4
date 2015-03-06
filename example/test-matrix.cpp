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
#include "../include/matrix.h"

using namespace F4;
using namespace std;

int main (int argc, char **argv)
{
    // Test Matrix();
    cout << "________Test Matrix()________" << endl;
    Matrix<int> mat1;
    
    // Test Matrix(int height, int width);
    cout << "________Test Matrix(int height, int width);________" << endl;
    Matrix<int> mat2(10000,10000);
    

    return 0;
}


