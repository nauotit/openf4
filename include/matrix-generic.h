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
  * \file matrix-generic.h
  * \brief Declaration of class MatrixGeneric.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_MATRIX_GENERIC_H
#define F4_MATRIX_GENERIC_H

/** \cond */
#include <iostream>
#include <cassert>
#include <ctime>
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>
#include <givaro/modular-balanced.h>
#include <fflas-ffpack/ffpack/ffpack.h>
#include <fflas-ffpack/utils/Matio.h>
/** \endcond */

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \class MatrixGeneric
     * Represent a matrix under fflas-ffpack format.
     */
    template <class Field>
    class MatrixGeneric
    {
        public:
            
            /* Constructor */
            
            /**
             * \brief Constructor
             * \param f: Base field.
             */
            MatrixGeneric(Field & f);
            
            /**
             * \brief Constructor
             * \param f: Base field.
             * \param height: Height of _matrix.
             * \param width: Width of _matrix.
             */
            MatrixGeneric(Field & f, int height, int width);
            
            /**
             * \brief Constructor
             * \param f: Base field.
             * \param filename: Name of a matrix file.
             */
            MatrixGeneric(Field & f, std::string const & filename);
            
            /**
             * \brief Copy constructor
             * \param matrix: MatrixGeneric.
             */
            MatrixGeneric(MatrixGeneric const & matrix);
            
            /**
             * \brief Move constructor
             * \param matrix: MatrixGeneric.
             */
            MatrixGeneric(MatrixGeneric && matrix);
            
            
            /* Destructor */
            
            /**
             * \brief Destructor
             */
            ~MatrixGeneric();
            
            /**
             * \brief Delete _startTail, _endCol, _sigma, _tau.
             */
            void erase();
            
            
            ///* Get / Set */
            
            ///**
             //* \brief Modify matrix element.
             //* \param row: Row of the element.
             //* \param col: Column of the element.
             //* \return Reference on the element.
             //*/
            //Field::Element & operator() (int row, int col);
            
            ///**
             //* \brief Get matrix element.
             //* \param row: Row of the element.
             //* \param col: Column of the element.
             //* \return Element.
             //*/
            //Field::Element operator() (int row, int col) const;
            
            ///**
             //* \brief Get matrix element.
             //* \param row: Row of the element.
             //* \param col: Column of the element.
             //* \return Element.
             //*/
            //Field::Element getElement(int row, int col) const;
            
            ///**
             //* \brief Modify matrix element.
             //* \param row: Row of the element.
             //* \param col: Column of the element.
             //* \param element: Element.
             //*/
            //void setElement (int row, int col, Field::Element const & element);
            
            ///**
             //* \brief Get the row-th row of this.
             //* \param row: Index of the row.
             //*/
            //Field::Element * getRow (int row);
            
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
             * \brief Test if _matrix(row,col) is zero.
             * \param row: Row of the element.
             * \param col: Column of the element.
             * \return  true if _matrix(row,col) is zero.
             * \return  false otherwise.
             */
            bool isZero(int row, int col) const;

            /**
             * \brief Echelonize the matrix mat using the shape of the F4 matrix.
             * \return Height of the echelonized matrix.
             */
            int echelonize ();
            
            
            ///* Internal operator */
            
            ///**
             //* \brief Overload the operator =.
             //* \pre The static variable MODULO must be set beforehand.
             //* \param matrix: MatrixGeneric to copy.
             //* \return Reference on this.
             //*/
            //MatrixGeneric & operator=(MatrixGeneric const & matrix);
            
            ///**
             //* \brief Overload the operator = (move assignment). Used when mon is unnamed (only copy the pointer).
             //* \pre The static variable MODULO must be set beforehand.
             //* \param matrix: MatrixGeneric to copy.
             //* \return Reference on this.
             //*/
            //MatrixGeneric & operator=(MatrixGeneric && matrix);
            
        private:
            typename Field::Element * _matrix; /*!< Macaulay matrix */
            typename Field::Element * _A; /*!< Upper left */
            typename Field::Element * _B; /*!< Upper right */
            typename Field::Element * _C; /*!< Lower left */
            typename Field::Element * _D; /*!< Lower right */
            Field _F; /*!< Base field */
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
    std::ostream & operator<<(std::ostream & stream, MatrixGeneric<Element> const & matrix);
}

#include "../src/matrix-generic.inl"

#endif // F4_MATRIX_GENERIC_H
