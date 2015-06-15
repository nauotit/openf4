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


dnl F4_CHECK_GIVARO

dnl Test for Givaro and define GIVARO_CFLAGS and GIVARO_LIBS

AC_DEFUN([F4_CHECK_GIVARO],
[

AC_ARG_WITH([givaro],
            [AC_HELP_STRING([--with-givaro=<path>|yes], 
                            [Use Givaro library. 
                            This library is optional for F4 compilation.
                            It can be used to compute Groebner basis over prime finite field of characteristic > 2^32. 
                            It can be used to compute Groebner basis over non prime finite field. 
                            If argument is yes or <empty>
                            that means the library is reachable with the standard
                            search path (/usr or /usr/local). Otherwise you give
                            the <path> to the directory which contains the library.
                            ])],
            [if test "$withval" = yes ; then
                GIVARO_HOME_PATH="${DEFAULT_CHECKING_PATH}"
            elif test "$withval" != no ; then
                GIVARO_HOME_PATH="$withval ${DEFAULT_CHECKING_PATH}"
            fi],
            [with_givaro=no])

AS_IF([test "x$with_givaro" != xno],
      [version_min=30901
      
       F4_CHECK_GMP(,,[echo '*******************************************************************************'
                       echo ' ERROR: GMP not found!'
                       echo
                       echo ' GMP library compiled with --enable-cxx is required for this library to compile.'
                       echo ' Please make sure GMP is installed and specify its location with the option'
                       echo ' --with-gmp=<prefix> when running configure.'
                       echo '*******************************************************************************'
                       exit 1])

        dnl Check for existence
        BACKUP_CXXFLAGS=${CXXFLAGS}
        BACKUP_LIBS=${LIBS}

        AC_MSG_CHECKING(for GIVARO >= $version_min)

        for GIVARO_HOME in ${GIVARO_HOME_PATH}
          do
            if test -r "$GIVARO_HOME/include/givaro/givconfig.h"; then
                if test "x$GIVARO_HOME" != "x/usr" -a "x$GIVARO_HOME" != "x/usr/local"; then
                    GIVARO_CFLAGS="-I${GIVARO_HOME}/include"
                    GIVARO_LIBS="-L${GIVARO_HOME}/lib -lgivaro"
                else
                    GIVARO_CFLAGS=
                    GIVARO_LIBS="-lgivaro"
                fi
                CXXFLAGS="${BACKUP_CXXFLAGS} ${GIVARO_CFLAGS} ${GMP_CFLAGS}"
                LIBS="${BACKUP_LIBS} ${GIVARO_LIBS} ${GMP_LIBS}"

                AC_TRY_LINK([#include <givaro/givinteger.h>],
                            [Givaro::Integer a;],
                            [AC_TRY_RUN([#include <givaro/givconfig.h>
                                        int main () 
                                        {if (GIVARO_VERSION < $version_min || GIVARO_VERSION>0x030000) return -1; else return 0; /* old version of Givaro are defined as hexa 0x03yyzz*/ }],
                                        [givaro_found="yes"
                                         break],
                                        [givaro_problem="$problem $GIVARO_HOME"
                                         echo "The minimal required version of Givaro is $version_min"
                                         unset GIVARO_CFLAGS
                                         unset GIVARO_LIBS ],
                                         [givaro_found="yes"
                                          givaro_cross="yes"
                                          break])],
                            [givaro_found="no"
                             givaro_checked="$checked $GIVARO_HOME"
                             echo 'Givaro try failed'
                             unset GIVARO_CFLAGS
                             unset GIVARO_LIBS])
            else
                givaro_found="no"
            fi
        done

        if test "x$givaro_found" = "xyes" ; then
            AC_SUBST(GIVARO_CFLAGS)
            AC_SUBST(GIVARO_LIBS)
            dnl  echo $GIVARO_CFLAGS $GIVARO_LIBS
            AC_DEFINE(HAVE_GIVARO,1,[Define if GIVARO is installed])
            HAVE_GIVARO=yes
            if test "x$givaro_cross" != "xyes"; then
                AC_MSG_RESULT(found)
            else
                AC_MSG_RESULT(unknown)
                echo "WARNING: You appear to be cross compiling, so there is no way to determine"
                echo "whether your GIVARO version is new enough. I am assuming it is."
            fi
            ifelse([$2], , :, [$2])
        elif test -n "$givaro_problem"; then
            AC_MSG_RESULT(problem)
            echo "Sorry, your GIVARO version is too old. Disabling."
            ifelse([$3], , :, [$3])
        elif test "x$givaro_found" = "xno" ; then
            AC_MSG_RESULT(not found)
            ifelse([$3], , :, [$3])
        fi

        CXXFLAGS=${BACKUP_CXXFLAGS}
        LIBS=${BACKUP_LIBS}
      ])
      
      AM_CONDITIONAL(F4_HAVE_GIVARO, test "x$HAVE_GIVARO" = "xyes")

])
