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


dnl F4_ENABLE_DEBUG

dnl turn on OpenMP if available

AC_DEFUN([F4_ENABLE_DEBUG],
         [AC_ARG_ENABLE([debug],
                        [AC_HELP_STRING([--enable-debug],
                        [Enable assertion and flag -g])],
                        [with_debug=$enable_debug],
                        [with_debug=no])
          AC_MSG_CHECKING(for Debug mode)
          AS_IF([ test "x$with_debug" != "xno" ],
          [
                DEBUG_FLAGS="-g"
                CXXFLAGS="${CXXFLAGS} ${OMPFLAGS}"
                AC_MSG_RESULT(yes)
                AC_SUBST(DEBUG_FLAGS)],
          [
                DEBUG_FLAGS="-DNDEBUG"
                CXXFLAGS="${CXXFLAGS} ${OMPFLAGS}"
                AC_SUBST(DEBUG_FLAGS)
                AC_MSG_RESULT(no)])
          ]
)
