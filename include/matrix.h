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
  * \file matrix.h
  * \brief Declaration of class Matrix.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_MATRIX_H
#define F4_MATRIX_H

/** \cond */
#include <iostream>
#include <cassert>
#include <ctime>
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>
#include <omp.h>
/** \endcond */

#include "element-prime.h"

#define SSE2
#ifdef SSE2
#include <xmmintrin.h>
#endif // SSE2

//#define SSE4
#ifdef SSE4
#include <xmmintrin.h>
#include <smmintrin.h>
#endif // SSE4

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \class Matrix
     * Represent a matrix.
     */
    template <typename Element>
    class Matrix
    {
        public:
            
            /* Constructor */
            
            /**
             * \brief Constructor
             */
            Matrix();
            
            /**
             * \brief Constructor
             * \param height: Height of _matrix.
             * \param width: Width of _matrix.
             */
            Matrix(int height, int width);
            
            /**
             * \brief Constructor
             * \param filename: Name of a matrix file.
             */
            Matrix(std::string const & filename);
            
            /**
             * \brief Copy constructor
             * \param matrix: Matrix.
             */
            Matrix(Matrix const & matrix);
            
            /**
             * \brief Move constructor
             * \param matrix: Matrix.
             */
            Matrix(Matrix && matrix);
            
            
            /* Destructor */
            
            /**
             * \brief Destructor
             */
            ~Matrix();
            
            
            /* Get / Set */
            
            /**
             * \brief Modify matrix element.
             * \param row: Row of the element.
             * \param col: Column of the element.
             * \return Reference on the element.
             */
            Element & operator() (int row, int col);
            
            /**
             * \brief Get matrix element.
             * \param row: Row of the element.
             * \param col: Column of the element.
             * \return Element.
             */
            Element operator() (int row, int col) const;
            
            /**
             * \brief Get matrix element.
             * \param row: Row of the element.
             * \param col: Column of the element.
             * \return Element.
             */
            Element getElement(int row, int col) const;
            
            /**
             * \brief Modify matrix element.
             * \param row: Row of the element.
             * \param col: Column of the element.
             * \param element: Element.
             */
            void setElement (int row, int col, Element const & element);
            
            /**
             * \brief Get the row-th row of this.
             * \param row: Index of the row.
             */
            Element * getRow (int row);
            
            /**
             * \brief Get the height of the matrix (number of rows).
             */
            int getHeight() const;
            
            /**
             * \brief Get the width of the matrix (number of columns).
             */
            int getWidth() const;
            
            /**
             * \brief Specify the number of pivots.
             */
            void setNbPiv(int nbPiv);
            
            /**
             * \brief Get the number of pivots.
             */
            int getNbPiv() const;
            
            /**
             * \brief Specify the permutation _tau.
             */
            void setTau(int * tau);
            
            /**
             * \brief Get the permutation _tau.
             */
            int * getTau();
            
            /**
             * \brief Specify the permutation _sigma.
             */
            void setSigma(int * sigma);
            
            /**
             * \brief Get the permutation _sigma.
             */
            int * getSigma();
            
            /**
             * \brief Specify the array _startTail.
             */
            void setStartTail(int * startTail);
            
            /**
             * \brief Get the array _startTail.
             */
            int * getStartTail();
            
            /**
             * \brief Specify the array _endCol.
             */
            void setEndCol(int * encCol);
            
            /**
             * \brief Get the array _endCol.
             */
            int * getEndCol();
            
            /**
             * \brief Set the informations required by echelonize.
             */
            void setInfo(int nbPiv, int *tau, int *sigma, int * startTail, int * endCol);
            
            
            /* Miscellaneous */
            
            /**
             * \brief Print the matrix.
             */
            void printMatrix (std::ostream & stream) const;
            
            /**
             * \brief Print the matrix.
             */
            void printMatrix (std::string const & filename) const;
            
            /**
             * \brief Print the matrix in a format readable by constructor.
             */
            void printMatrixTxt (std::string const & filename) const;
            
            /**
             * \brief Test if _matrix(row,col) is zero.
             * \param row: Row of the element.
             * \param col: Column of the element.
             * \return  true if _matrix(row,col) is zero.
             * \return  false otherwise.
             */
            bool isZero(int row, int col) const;
            
            /**
             * \brief Normalize a slice of the row-th row.
             * \param row: Row to normalize.
             * \param start: Beginning of the slice.
             * \param end: End of the slice.
             */
            void normalizeRow(Element * row, int start, int end);
            
            /**
             * \brief Multiply a slice of the row-th row by element.
             * \param row: Row of the matrix. 
             * \param element: Element used to multiply each element of the slice.
             * \param start: Beginning of the slice.
             * \param end: End of the slice.
             */
            void multRow(Element * row, Element const & element, int start, int end);
            
             /**
             * \brief Multiply a slice of the row1-th row by element and add a slice of the row2-th row.
             * \param row1: Row of the matrix. The one to modify.
             * \param row2: Row of the matrix. 
             * \param element: Element used to multiply each element of the slice.
             * \param start: Beginning of the slice.
             * \param end: End of the slice.
             */
            void addMultRow(Element * row1, Element * row2, Element element, int start, int end);
            
            /**
             * \brief Swap a slice of the row1-th row with a slice of the row2-th row.
             * \param numRow1: Number of the row. 
             * \param numRow2: Number of the row. 
             */
            void swapRow(int numRow1, int numRow2);
            
            /**
             * \brief Swap a slice of the row1-th row with a slice of the row2-th row.
             * \param numCol1: Number of the column.
             * \param numCol2: Number of the column. 
             * \param start: Beginning of the slice.
             * \param end: End of the slice.
             */
            void swapCol(int numCol1, int numCol2, int start, int end);

            /**
             * \brief Echelonize the matrix mat using the shape of the F4 matrix.
             * \return Height of the echelonized matrix.
             */
            int echelonize ();
            
            
            /* Internal operator */
            
            /**
             * \brief Overload the operator =.
             * \pre The static variable MODULO must be set beforehand.
             * \param matrix: Matrix to copy.
             * \return Reference on this.
             */
            Matrix & operator=(Matrix const & matrix);
            
            /**
             * \brief Overload the operator = (move assignment). Used when mon is unnamed (only copy the pointer).
             * \pre The static variable MODULO must be set beforehand.
             * \param matrix: Matrix to copy.
             * \return Reference on this.
             */
            Matrix & operator=(Matrix && matrix);
            
        private:
            Element ** _matrix; /*!< Macaulay matrix */
            int _height; /*!< Height of _matrix. */
            int _width; /*!< Width of _matrix. */
            int _nbPiv; /*!< Number of pivots. */
            int * _tau; /*!< Permutation, _sigma(_tau(i))=_tau(_sigma(i))=i. _tau[i]=column of the monomial tab_mon[i]. */
            int * _sigma; /*!< _sigma[i]=index in tab_mon of the column i monomial. */
            int * _startTail; /*!< startTail[i]=column of the first possibly non zero coefficient (in line i) after nb_piv if i < nb_piv. Otherwise startTail[i]=0. startTail[i] = min{j>=nb_piv : _igma[i]<_sigma[j]}. */
            int * _endCol; /*!< endCol[i] = end of column i if i < nbPiv. Otherwise endCol[i]=end of column i without taking into account the lines under nbPiv. */
    };
    
    
    /* Internal operator */
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    template <typename Element>
    std::ostream & operator<<(std::ostream & stream, Matrix<Element> const & matrix);
}

#include "../src/matrix.inl"

#endif // F4_MATRIX_H
