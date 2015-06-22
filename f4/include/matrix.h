/* 
 * Copyright (C) 2015 Antoine Joux, Vanessa Vitse and Titouan Coladon
 * 
 * This file is part of F4.
 * 
 * F4 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * F4 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with F4.  If not, see <http://www.gnu.org/licenses/>.
 */

  /**
  * \file matrix.h
  * \brief Declaration of class Matrix.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_MATRIX_H
#define F4_MATRIX_H

/** \cond */
#include "global.h"
#include <iostream>
#include <cassert>
#include <ctime>
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>

#ifdef USE_OPENMP
#include <omp.h>
#endif // USE_OPENMP

#ifdef HAVE_FFLAS_FFPACK
#include <givaro/modular-balanced.h>
#include <fflas-ffpack/ffpack/ffpack.h>
#include <fflas-ffpack/fflas/fflas.h>
#endif // HAVE_FFLAS_FFPACK
/** \endcond */

#include "element-prime.h"
#include "element-gf2.h"
#include "element-gf2-extension.h"

#ifdef HAVE_GIVARO
#include "element-givaro.h"
#endif // HAVE_GIVARO

#ifdef HAVE_SSE2
#include <emmintrin.h>
#endif // HAVE_SSE2

#ifdef HAVE_SSE4_1
#include <smmintrin.h>
#endif // HAVE_SSE4_1

#ifdef HAVE_SSE4_2
#include <nmmintrin.h>
#endif // HAVE_SSE4_2

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \class Matrix
     * \brief Represent a matrix.
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
             * \brief Print the matrix in a format readable by sage.
             */
            void printMatrixSage(std::string const & filename) const;
            
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
             * \brief Specialisation of normalizeRow for ElementPrime type.
             * \param row: Row to normalize.
             * \param start: Beginning of the slice.
             * \param end: End of the slice.
             */
            void normalizeRowPrime(Element * row, int start, int end);
            
            /**
             * \brief Specialisation of normalizeRow for ElementGF2Extension type.
             * \param row: Row to normalize.
             * \param start: Beginning of the slice.
             * \param end: End of the slice.
             */
            void normalizeRowGF2Extension(Element * row, int start, int end);
            
            /**
             * \brief Multiply a slice of the row-th row by element.
             * \param row: Row of the matrix. 
             * \param element: Element used to multiply each element of the slice.
             * \param start: Beginning of the slice.
             * \param end: End of the slice.
             */
            void multRow(Element * row, Element const & element, int start, int end);
            
            /**
             * \brief Specialisation of multRow for ElementPrime type.
             * \param row: Row of the matrix. 
             * \param element: Element used to multiply each element of the slice.
             * \param start: Beginning of the slice.
             * \param end: End of the slice.
             */
            void multRowPrime(Element * row, Element const & element, int start, int end);
            
            /**
             * \brief Specialisation of multRow for ElementGF2Extension type.
             * \param row: Row of the matrix. 
             * \param element: Element used to multiply each element of the slice.
             * \param start: Beginning of the slice.
             * \param end: End of the slice.
             */
            void multRowGF2Extension(Element * row, Element const & element, int start, int end);
            
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
             * \brief Specialisation of addMultRow for ElementPrime type.
             * \param row1: Row of the matrix. The one to modify.
             * \param row2: Row of the matrix. 
             * \param element: Element used to multiply each element of the slice.
             * \param start: Beginning of the slice.
             * \param end: End of the slice.
             */
            void addMultRowPrime(Element * row1, Element * row2, Element element, int start, int end);
            
            /**
             * \brief Specialisation of addMultRow for ElementGF2Extension type.
             * \param row1: Row of the matrix. The one to modify.
             * \param row2: Row of the matrix. 
             * \param element: Element used to multiply each element of the slice.
             * \param start: Beginning of the slice.
             * \param end: End of the slice.
             */
            void addMultRowGF2Extension(Element * row1, Element * row2, Element element, int start, int end);
            
            /**
             * \brief dest1 += mult1 * vec, dest2 += mult2 * vec.
             * \param dest1: Row of the matrix to modify.
             * \param dest2: Row of the matrix to modify.
             * \param mult1: Element used to multiply each element of the slice.
             * \param mult2: Element used to multiply each element of the slice.
             * \param vec: Row of the matrix to add.
             * \param start: Beginning of the slice.
             * \param end: End of the slice.
             */
            void doubleAddMultRowGF2Extension(Element * dest1, Element * dest2, Element mult1, Element mult2, Element * vec, int start, int end);
            
            /**
             * \brief dest1 += mult1 * vec, dest2 += mult2 * vec, dest3 += mult3 * vec.
             * \param dest1: Row of the matrix to modify.
             * \param dest2: Row of the matrix to modify.
             * \param dest3: Row of the matrix to modify.
             * \param mult1: Element used to multiply each element of the slice.
             * \param mult2: Element used to multiply each element of the slice.
             * \param mult3: Element used to multiply each element of the slice.
             * \param vec: Row of the matrix to add.
             * \param start: Beginning of the slice.
             * \param end: End of the slice.
             */
            void tripleAddMultRowGF2Extension(Element * dest1, Element * dest2, Element * dest3, Element mult1, Element mult2, Element mult3, Element * vec, int start, int end);
            
            /**
             * \brief dest1 += mult1 * vec, dest2 += mult2 * vec, dest3 += mult3 * vec, dest4 += mult4 * vec.
             * \param dest1: Row of the matrix to modify.
             * \param dest2: Row of the matrix to modify.
             * \param dest3: Row of the matrix to modify.
             * \param dest4: Row of the matrix to modify.
             * \param mult1: Element used to multiply each element of the slice.
             * \param mult2: Element used to multiply each element of the slice.
             * \param mult3: Element used to multiply each element of the slice.
             * \param mult4: Element used to multiply each element of the slice.
             * \param vec: Row of the matrix to add.
             * \param start: Beginning of the slice.
             * \param end: End of the slice.
             */
            void quadAddMultRowGF2Extension(Element * dest1, Element * dest2, Element * dest3, Element * dest4, Element mult1, Element mult2, Element mult3, Element mult4, Element * vec, int start, int end);
            
            /**
             * \brief dest1 += mult1 * vec, dest2 += mult2 * vec, dest3 += mult3 * vec, dest4 += mult4 * vec, dest5 += mult5 * vec, dest6 += mult6 * vec, dest7 += mult7 * vec, dest8 += mult8 * vec.
             * \param dest1: Row of the matrix to modify.
             * \param dest2: Row of the matrix to modify.
             * \param dest3: Row of the matrix to modify.
             * \param dest4: Row of the matrix to modify.
             * \param dest5: Row of the matrix to modify.
             * \param dest6: Row of the matrix to modify.
             * \param dest7: Row of the matrix to modify.
             * \param dest8: Row of the matrix to modify.
             * \param mult1: Element used to multiply each element of the slice.
             * \param mult2: Element used to multiply each element of the slice.
             * \param mult3: Element used to multiply each element of the slice.
             * \param mult4: Element used to multiply each element of the slice.
             * \param mult5: Element used to multiply each element of the slice.
             * \param mult6: Element used to multiply each element of the slice.
             * \param mult7: Element used to multiply each element of the slice.
             * \param mult8: Element used to multiply each element of the slice.
             * \param vec: Row of the matrix to add.
             * \param start: Beginning of the slice.
             * \param end: End of the slice.
             */
            void octAddMultRowGF2Extension(Element * dest1, Element * dest2, Element * dest3, Element * dest4, Element * dest5, Element * dest6, Element * dest7, Element * dest8, Element mult1, Element mult2, Element mult3, Element mult4, Element mult5, Element mult6, Element mult7, Element mult8, Element * vec, int start, int end);
            
            /**
             * \brief Use octAddMultRowGF2Extension, quadAddMultRowGF2Extension, tripleAddMultRowGF2Extension, doubleAddMultRowGF2Extension and addMultRowGF2Extension to suppress elements in column ll+dec from row startL2 to row endL2 using multiple of row ll.
             * \param ll: Pivot row.
             * \param dec: Gap between ll and modified column. 
             * \param startL2: First row to modify (set 0 in _matrix[startL2][ll+dec]).
             * \param endL2: Last row to modify is endL2-1 (set 0 in _matrix[endL2-1][ll+dec]).
             * \param start: Beginning of the slice to modify.
             * \param end: End of the slice.
             */
            void groupAddMultRowGF2Extension(int ll, int dec, int startL2, int endL2, int start, int end);
            
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
             * \brief Echelonize the left slice of the matrix using FFLAS-FFPACK routines.
             * \return Height of the echelonized matrix.
             */
            int echelonizeRight (chrono::duration<int,milli> & tmp_ech_db, chrono::duration<int,milli> & tmp_ech_dh);
            
            /**
             * \brief Echelonize the matrix using the shape of the F4 matrix.
             * \return Height of the echelonized matrix.
             */
            int echelonize ();
            
            /**
             * \brief Specialisation of echelonize for ElementPrime Type, use lazy arithmetic.
             * \return Height of the echelonized matrix.
             */
            int echelonizePrime ();
            
            /**
             * \brief Specialisation of echelonize for ElementGF2Extension Type.
             * \return Height of the echelonized matrix.
             */
            int echelonizeGF2Extension ();
            
            
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
            Element ** _matrix; /*!< "Macaulay" matrix */
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

/** \cond */
#include "../src/matrix.inl"
/** \endcond */

#endif // F4_MATRIX_H
