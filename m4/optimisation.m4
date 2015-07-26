dnl Copyright (C) 2015 Antoine Joux, Vanessa Vitse and Titouan Coladon
 
dnl This file is part of openf4.

dnl openf4 is free software: you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation, either version 3 of the License, or
dnl (at your option) any later version.

dnl openf4 is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.

dnl You should have received a copy of the GNU General Public License
dnl along with openf4.  If not, see <http://www.gnu.org/licenses/>.


dnl OPENF4_ENABLE_OPTIMISATION

dnl turn on Optimisation (default is yes)

AC_DEFUN([OPENF4_ENABLE_OPTIMISATION],
         [AC_ARG_ENABLE([optimisation],
                        [AC_HELP_STRING([--enable-optimisation],
                        [Use g++ optimisation (-O3),
                         default=yes])],
                        [with_optimisation=$enable_optimisation],
                        [with_optimisation=yes])
          AC_MSG_CHECKING(for Optimisation)
          AS_IF([ test "x$with_optimisation" != "xno" ],
          [
                OPTIMISATION_FLAGS="-O3 -Wall -Wno-strict-overflow -funroll-loops -ftree-vectorize"
                CXXFLAGS="${CXXFLAGS} ${OMPFLAGS}"
                AC_MSG_RESULT(yes)
                AC_SUBST(OPTIMISATION_FLAGS)],
           [
                OPTIMISATION_FLAGS="-Wall -Wno-strict-overflow"
                CXXFLAGS="${CXXFLAGS} ${OMPFLAGS}"
                AC_SUBST(OPTIMISATION_FLAGS)
                AC_MSG_RESULT(no)])
         ]
)
