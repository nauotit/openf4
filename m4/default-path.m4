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


dnl OPENF4_DEFAULT_PATH

dnl Specify default path variables for Givaro and FFLAS_FFPACK  

AC_DEFUN([OPENF4_DEFAULT_PATH],
[

AC_ARG_WITH([default],
            [AC_HELP_STRING([--with-default=<path>], 
                            [Add <path> to the default path for external package
                            checking. Set as default with /usr and /usr/local.
                            ])],
            [if test "$withval" = yes ; then
                echo "Default path = /usr /usr/local "
                DEFAULT_CHECKING_PATH="/usr /usr/local "
            else
                echo "Default path (updated) = $withval /usr /usr/local "
                DEFAULT_CHECKING_PATH="$withval /usr /usr/local "
            fi
            ],
            [
                echo "Default path = /usr /usr/local "
                DEFAULT_CHECKING_PATH="/usr /usr/local "
            ])


GMP_HOME_PATH="${DEFAULT_CHECKING_PATH}"
GIVARO_HOME_PATH="${DEFAULT_CHECKING_PATH}"
FFLAS_FFPACK_HOME_PATH="${DEFAULT_CHECKING_PATH}"
])
