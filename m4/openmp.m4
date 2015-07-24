dnl Copyright (c) 2011 FFLAS-FFPACK
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

dnl F4_CHECK_OMP

dnl turn on OpenMP if available

AC_DEFUN([F4_CHECK_OMP],
         [AC_ARG_ENABLE([openmp],
                        [AC_HELP_STRING([--enable-openmp],
                        [Use OpenMP (parallel computation),
                         default=yes])],
                        [with_omp=$enable_openmp],
                        [with_omp=yes ])
          AC_MSG_CHECKING(for OpenMP)
          AS_IF([ test "x$with_omp" != "xno" ],
          [
                BACKUP_CXXFLAGS=${CXXFLAGS}
                OMPFLAGS="-fopenmp"
                CXXFLAGS="${BACKUP_CXXFLAGS} ${OMPFLAGS}"
                AC_TRY_RUN([#include <omp.h>
                            int main() {
                                int p = omp_get_num_threads();
                                return 0;
                            }],
                            [omp_found="yes"],
                            [omp_found="no"],
                            [echo "cross compiling...disabling"
                             omp_found="no"])
                AS_IF([test "x$omp_found" = "xyes"],
                      [AC_DEFINE(USE_OPENMP,1,[Define if OMP is available])
                       AC_SUBST(OMPFLAGS)
                       AC_MSG_RESULT(yes)
                       HAVE_OMP=yes],
                      [OMPFLAGS=
                       AC_SUBST(OMPFLAGS)
                       AC_MSG_RESULT(no)])
                      CXXFLAGS=${BACKUP_CXXFLAGS}
            ],
            [AC_MSG_RESULT(no)])
         ]
         AM_CONDITIONAL(F4_HAVE_OMP, test "x$HAVE_OMP" = "xyes")
)
