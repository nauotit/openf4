AC_INIT(f4, 1.0.0, titouan.coladon@gmail.com)
AC_CONFIG_SRCDIR([src/libf4.cpp])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror])
AM_PROG_AR
LT_INIT
: ${CXXFLAGS= -O3}
AC_PROG_CXX

echo "-----------------------------------------------"
echo "               START  F4 CONFIG                "
echo "-----------------------------------------------"

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 benchmark/Makefile
 src/Makefile
 example/Makefile
])
AC_OUTPUT
