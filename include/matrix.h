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

#include <iostream>
#include <cassert>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>


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
            
            // Constructor
            
            /**
             * \brief Constructor
             */
            Matrix();
            
            /**
             * \brief Constructor
             * \param height: Height of _matrix.
             * \param width: Width of _matrix.
             */
            Matrix(unsigned int height, unsigned int width);
            
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
            
            
            // Destructor
            
            /**
             * \brief Destructor
             */
            ~Matrix();
            
            
            // Get / Set
            
            /**
             * \brief Modify matrix element.
             * \param row: Row of the element.
             * \param col: Column of the element.
             * \return Reference on the element.
             */
            Element & operator() (unsigned row, unsigned col);
            
            /**
             * \brief Get matrix element.
             * \param row: Row of the element.
             * \param col: Column of the element.
             * \return Element.
             */
            Element operator() (unsigned row, unsigned col) const;
            
            /**
             * \brief Get matrix element.
             * \param row: Row of the element.
             * \param col: Column of the element.
             * \return Element.
             */
            Element getElement(unsigned row, unsigned col) const;
            
            /**
             * \brief Modify matrix element.
             * \param row: Row of the element.
             * \param col: Column of the element.
             * \param element: Element.
             */
            void setElement (unsigned row, unsigned col, Element const & element);
            
            /**
             * \brief Get the row-th row of this.
             * \param row: Index of the row.
             */
            Element * getRow (unsigned row);
            
            /**
             * \brief Get the height of the matrix (number of rows).
             */
            int getHeight();
            
            /**
             * \brief Get the width of the matrix (number of columns).
             */
            int getWidth();
            
            /**
             * \brief Specify the number of pivots.
             */
            void setNbPiv(int nbPiv);
            
            /**
             * \brief Get the number of pivots.
             */
            int getNbPiv();
            
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
            
            
            // Miscellaneous
            
            /**
             * \brief Print the matrix.
             */
            void printMatrix (std::ostream & stream = std::cout) const;
            
            /**
             * \brief Print the matrix.
             */
            void printMatrix (std::string const & filename) const;
            
            /**
             * \brief Test if _matrix(row,col) is zero.
             * \param row: Row of the element.
             * \param col: Column of the element.
             * \return  true if _matrix(row,col) is zero.
             * \return  false otherwise.
             */
            bool isZero(unsigned row, unsigned col) const;
            
            /**
             * \brief Multiply a slice of the row-th row by element.
             * \param numRow: Number of the row.
             * \param element: Element used to multiply each element of the slice.
             * \param start: Beginning of the slice.
             * \param end: End of the slice.
             */
            void multRow(unsigned numRow, Element element, unsigned start, unsigned end);
            
             /**
             * \brief Multiply a slice of the row1-th row by element and add a slice of the row2-th row.
             * \param numRow1: Number of the row. The one to modify.
             * \param numRow2: Number of the row. 
             * \param element: Element used to multiply each element of the slice.
             * \param start: Beginning of the slice.
             * \param end: End of the slice.
             */
            void addMultRow(unsigned numRow1, unsigned numRow2, Element element, unsigned start, unsigned end);
            
            /**
             * \brief Swap a slice of the row1-th row with a slice of the row2-th row.
             * \param numRow1: Number of the row. 
             * \param numRow2: Number of the row. 
             * \param start: Beginning of the slice.
             * \param end: End of the slice.
             */
            void swapRow(unsigned numRow1, unsigned numRow2, unsigned start, unsigned end);
            
            /**
             * \brief Swap a slice of the row1-th row with a slice of the row2-th row.
             * \param numCol1: Number of the column.
             * \param numCol2: Number of the column. 
             * \param start: Beginning of the slice.
             * \param end: End of the slice.
             */
            void swapCol(unsigned numCol1, unsigned numCol2, unsigned start, unsigned end);

            /**
             * \brief Echelonize the matrix mat using the shape of the F4 matrix.
             * \return Height of the echelonized matrix.
             */
            int echelonize ();
            
            
            // Internal operator
            
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
            unsigned int _height; /*!< Height of _matrix. */
            unsigned int _width; /*!< Width of _matrix. */
            int _nbPiv; /*!< Number of pivots. */
            int * _tau; /*!< Permutation, _sigma(_tau(i))=_tau(_sigma(i))=i. _tau[i]=column of the monomial tab_mon[i]. */
            int * _sigma; /*!< _sigma[i]=index in tab_mon of the column i monomial. */
            int * _startTail; /*!< startTail[i]=column of the first possibly non zero coefficient (in line i) after nb_piv if i < nb_piv. Otherwise startTail[i]=0. startTail[i] = min{j>=nb_piv : _igma[i]<_sigma[j]}. */
            int * _endCol; /*!< endCol[i] = end of column i if i < nbPiv. Otherwise endCol[i]=end of column i without taking into account the lines under nbPiv. */
    };
    
    /**
     * \brief Overload the operator <<.
     * \return ostream: Stream.
     */
    template <typename Element>
    std::ostream & operator<<(std::ostream & stream, Matrix<Element> const & matrix);
}

#include "../src/matrix.inl"

#endif // F4_MATRIX_H
