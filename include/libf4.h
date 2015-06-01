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
  * \file libf4.h
  * \brief Declaration of library methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_LIBF4_H
#define F4_LIBF4_H

#include <iostream>
#include <string>
#include <vector>

/**
 * \brief Compute a reduced groebner basis of the ideal defined by the list of polynomials polynomialList.
 * \param modulo: Characteristic of the base field.
 * \param degree: Initial degree. Allow to speed up the computation if you have an idea of the maximum monomial degree used.
 * \param nbVariable: Number of variable of the polynomial ring.
 * \param variableName: Array of variable names used to describe the monomials.
 * \param polynomialList: List of polynomials under text format.
 * \param nbThread: Number of threads to use.
 * \param verbose: Verbosity level.
 * \return Reduced groebner basis under text format.
 */
std::vector<std::string> groebnerBasisF4(int64_t modulo, int degree, int nbVariable, std::vector<std::string> variableName, std::vector<std::string> polynomialList, int nbThread, int verbose);

/**
 * \brief Compute a reduced groebner basis of the ideal defined by the list of polynomials polynomialList.
 * \param modulo: String representing the irreducible polynomial used to create the finite field (GF(2^n)=GF2[polyVarName]/modulo)
 * \param degree: Initial degree. Allow to speed up the computation if you have an idea of the maximum monomial degree used.
 * \param nbVariable: Number of variable of the polynomial ring.
 * \param variableName: Array of variable names used to describe the monomials.
 * \param polyVarName: Name of the variable used to describe the polynomial ring GF2[polyVarName].
 * \param polynomialList: List of polynomials under text format.
 * \param nbThread: Number of threads to use.
 * \param verbose: Verbosity level.
 * \return Reduced groebner basis under text format.
 */
std::vector<std::string> groebnerBasisGF2ExtensionF4(std::string modulo, int degree, int nbVariable, std::vector<std::string> variableName, std::string polyVarName, std::vector<std::string> polynomialList, int nbThread, int verbose);

/**
 * \brief Compute a reduced groebner basis of the ideal defined by the list of polynomials polynomialList. Use only if modulo > 4294967291, otherwise use groebnerBasisF4.
 * \param modulo: Characteristic of the base field under string representation.
 * \param degree: Initial degree. Allow to speed up the computation if you have an idea of the maximum monomial degree used.
 * \param nbVariable: Number of variable of the polynomial ring.
 * \param variableName: Array of variable names used to describe the monomials.
 * \param polynomialList: List of polynomials under text format.
 * \param nbThread: Number of threads to use.
 * \param verbose: Verbosity level.
 * \return Reduced groebner basis under text format.
 */
std::vector<std::string> groebnerBasisGivaroIntegerF4(std::string modulo, int degree, int nbVariable, std::vector<std::string> variableName, std::vector<std::string> polynomialList, int nbThread, int verbose);

#endif // F4_LIBF4_H
