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
 * \param sizeMonomialArray: Size of the monomial array.
 * \param nbVariable: Number of variable of the polynomial ring.
 * \param polynomialList: List of polynomials under text format.
 * \param nbThread: Number of threads to use.
 * \param verbose: Verbosity level.
 * \return Reduced groebner basis under text format.
 */
std::vector<std::string> groebnerBasisF4(int64_t modulo, int sizeMonomialArray, int nbVariable, std::vector<std::string> variableName, std::vector<std::string> polynomialList, int nbThread, int verbose);

#endif // F4_LIBF4_H
