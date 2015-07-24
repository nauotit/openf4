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


dnl F4_CHECK_FFLAS_FFPACK

dnl Test for FFLAS_FFPACK 

AC_DEFUN([F4_CHECK_FFLAS_FFPACK],
[

AC_ARG_WITH([fflas-ffpack],
            [AC_HELP_STRING([--with-fflas-ffpack=<path>|yes], 
                            [Use Fflas-Ffpack library. 
                            This library is optional for F4 compilation.
                            It can be used to improve the efficiency on prime field with a characteristic < 2^23. 
                            If argument is yes or <empty>
                            that means the library is reachable with the standard
                            search path (/usr or /usr/local). Otherwise you give
                            the <path> to the directory which contains the library.
                            Available at "http://linalg.org/projects/fflas-ffpack".
                            ])],
            [if test "$withval" = yes ; then
                FFLAS_FFPACK_HOME_PATH="${DEFAULT_CHECKING_PATH}"
            elif test "$withval" != no ; then
                FFLAS_FFPACK_HOME_PATH="$withval ${DEFAULT_CHECKING_PATH}"
            fi],
            [with_fflas_ffpack=no])


AS_IF([test "x$with_fflas_ffpack" != xno],
      [version_min=20100
        
        dnl Check for Blas
        F4_CHECK_BLAS_LIBS

        dnl Check for existence
        BACKUP_CXXFLAGS=${CXXFLAGS}
        BACKUP_LIBS=${LIBS}

        AC_MSG_CHECKING(for FFLAS-FFPACK >= $version_min)

        for FFLAS_FFPACK_HOME in ${FFLAS_FFPACK_HOME_PATH}
          do
            if test -r "$FFLAS_FFPACK_HOME/include/fflas-ffpack/fflas-ffpack.h" -a -x "$FFLAS_FFPACK_HOME/bin/fflas-ffpack-config"; then

               BLAS_LIBS=`$FFLAS_FFPACK_HOME/bin/fflas-ffpack-config --blas-libs`
               BLAS_CFLAGS=`$FFLAS_FFPACK_HOME/bin/fflas-ffpack-config --cflags`

               if test "x$FFLAS_FFPACK_HOME" != "x/usr" -a "x$FFLAS_FFPACK_HOME" != "x/usr/local"; then
                   FFLAS_FFPACK_CFLAGS="-I${FFLAS_FFPACK_HOME}/include"
               else
                   FFLAS_FFPACK_CFLAGS=
               fi

               CXXFLAGS="${BACKUP_CXXFLAGS} ${FFLAS_FFPACK_CFLAGS} ${BLAS_CFLAGS}"
               LIBS="${BACKUP_LIBS} ${BLAS_LIBS}"

                AC_TRY_LINK([#include "fflas-ffpack/fflas-ffpack.h"],
                            [FFLAS::FFLAS_TRANSPOSE a;],
                            [FF_VER=`$FFLAS_FFPACK_HOME/bin/fflas-ffpack-config --decimal-version`
                             AS_IF([test $FF_VER -ge $version_min],
                                   [ffflasffpack_found="yes"
                                    FFLAS_FFPACK_LOC="$FFLAS_FFPACK_HOME"
                                    break],
                                   [ffflasffpack_found="no"
                                    echo "The minimal required version of FFLAS-FFPACK is $version_min"])
                            ],
                            [ffflasffpack_found="no"
                             ffflasffpack_checked="$checked $FFLAS_FFPACK_HOME"
                             echo 'FFLAS-FFPACK try failed'
                             unset FFLAS_FFPACK_CFLAGS
                             unset FFLAS_FFPACK_LOC
                             unset BLAS_LIBS
                             unset BLAS_CFLAGS
                            ])
               dnl  AC_MSG_RESULT(found in $ffflasffpack_checked ? $ffflasffpack_found)
            else
               fflasflas_found="no"
               dnl  AC_MSG_RESULT(not found at all $FFLAS_FFPACK_HOME : $ffflasffpack_found)
            fi
        done

        if test "x$ffflasffpack_found" = "xyes" ; then
            AC_SUBST(FFLAS_FFPACK_CFLAGS)
            AC_SUBST(FFLAS_FFPACK_LIBS)
            AC_SUBST(FFLAS_FFPACK_LOC)
            AC_SUBST(BLAS_LIBS)
            AC_SUBST(BLAS_CFLAGS)
            AC_DEFINE(HAVE_FFLAS_FFPACK,1,[Define if FFLAS-FFPACK is installed])
            FF_VER=`$FFLAS_FFPACK_LOC/bin/fflas-ffpack-config --decimal-version`
            AC_DEFINE_UNQUOTED(FFLAS_FFPACK_VERSION, $FF_VER ,[what version of FFLAS-FFPACK is installed])
            HAVE_FFLAS_FFPACK=yes
            if test "x$fflasflas_cross" != "xyes"; then
                AC_MSG_RESULT(found)
            else
                AC_MSG_RESULT(unknown)
                echo "WARNING: You appear to be cross compiling, so there is no way to determine"
                echo "whether your FFLAS-FFPACK version is new enough. I am assuming it is."
            fi
            ifelse([$2], , :, [$2])
        elif test -n "$fflasflas_problem"; then
            AC_MSG_RESULT(problem)
            echo "Sorry, your FFLAS-FFPACK version is too old. Disabling."
            ifelse([$3], , :, [$3])
        elif test "x$fflasflas_found" = "xno" ; then
            AC_MSG_RESULT(not found)
            ifelse([$3], , :, [$3])
        fi

        CXXFLAGS=${BACKUP_CXXFLAGS}
        LIBS=${BACKUP_LIBS}
      ])
      
      AM_CONDITIONAL(F4_HAVE_BLAS, test "x$HAVE_BLAS" = "xyes")
      AM_CONDITIONAL(F4_HAVE_LAPACK, test "x$HAVE_LAPACK" = "xyes")
      AM_CONDITIONAL([F4_HAVE_FFLAS_FFPACK], [test x$HAVE_FFLAS_FFPACK = xyes])

])
