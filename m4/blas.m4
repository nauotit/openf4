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


dnl F4_CHECK_BLAS_LIBS

dnl Tests BLAS for and define CBLAS_LIBS

AC_DEFUN([F4_CHECK_BLAS_LIBS],
         [AC_ARG_WITH([blas-libs],
                      [AC_HELP_STRING([--with-blas-libs=<libs>],
                                      [LIBS for BLAS/LAPACK i.e. ('-L/path/to/openblas -lopenblas -Wl,-rpath=/path/to/openblas/lib') or ('-L/path/to/ATLAS -latlas -lcblas -Wl,-rpath=/path/to/ATLAS/lib') ])],
                      [with_blas_libs=$with_blas_libs
                       CBLAS_LIBS=$with_blas_libs],
                      [with_blas_libs=default])
         AS_IF([test "x$with_blas_libs" = xdefault],
               [AC_MSG_CHECKING(for Openblas)
                AC_CHECK_LIB([openblas], 
                             [cblas_daxpy], 
                             [CBLAS_LIBS="-lopenblas -Wl,-rpath=/usr/lib:/usr/local/lib"
                              AC_MSG_RESULT(found)],
                             [AC_MSG_RESULT(not found)
                              AC_MSG_CHECKING(for cblas)
                              AC_CHECK_LIB([cblas],
                                           [cblas_daxpy],
                                           [CBLAS_LIBS="-lcblas -Wl,-rpath=/usr/lib:/usr/local/lib"
                                            AC_MSG_RESULT(found)],
                                           [AC_MSG_RESULT(not found)])
                              AC_MSG_CHECKING(for atlas)
                              AC_CHECK_LIB([alas],
                                           [catlas_caxpby],
                                           [CBLAS_LIBS="${CBLAS_LIBS} -latlas"
                                            AC_MSG_RESULT(found)],
                                           [AC_MSG_RESULT(not found)])])])
         AC_SUBST(CBLAS_LIBS)
         ]
    )


