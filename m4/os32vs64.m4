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


dnl F4_CHECK_OS_64

dnl Check if the architecture is 32 or 64 bits.

AC_DEFUN([F4_CHECK_OS_64],
         [AC_MSG_CHECKING(for OS type)
          AC_CHECK_SIZEOF([long])
          AS_IF([test "$ac_cv_sizeof_long" -eq 8],
                 [AC_DEFINE([OS_64_BIT], 1, [Define if the size of a long is 64 bits.])
                  AC_MSG_RESULT(64 bits)],
                 [AC_DEFINE([OS_32_BIT], 1, [Define if the size of a long is 32 bits.])
                  AC_MSG_RESULT(32 bits)])]
)

 
