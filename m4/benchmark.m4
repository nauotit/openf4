dnl Copyright (C) 2015 Antoine Joux, Vanessa Vitse and Titouan Coladon
 
dnl This file is part of F4.

dnl F4 is free software: you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation, either version 3 of the License, or
dnl (at your option) any later version.

dnl F4 is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.

dnl You should have received a copy of the GNU General Public License
dnl along with F4.  If not, see <http://www.gnu.org/licenses/>.


dnl F4_ENABLE_BENCHMARK

dnl Build benchmark

AC_DEFUN([F4_ENABLE_BENCHMARK],
[
    AC_ARG_ENABLE([benchmark],
                  [AC_HELP_STRING([--enable-benchmark],
                                  [Build benchmarks])],
                  [with_benchmark=$enable_benchmark],
                  [with_benchmark=no])

    AM_CONDITIONAL([F4_HAVE_BENCHMARK], [test x$with_benchmark != xno])
])
