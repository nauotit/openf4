AC_PREREQ([2.69])
AC_INIT([openf4], [1.0.0], [titouan.coladon@gmail.com])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror])
AM_PROG_AR
LT_INIT
: ${CXXFLAGS=}

echo "-----------------------------------------------"
echo "               START  F4 CONFIG                "
echo "-----------------------------------------------"

# For macro
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
# Enable c++11
AX_CXX_COMPILE_STDCXX_11([],[mandatory])
# Do compilation tests using CXX and CXXCPP and use extension .C for test programs
AC_LANG([C++])
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_MKDIR_P

# Check 64 or 32 bits architecture
F4_CHECK_OS_64

# Check for vectorisation
F4_ENABLE_OPTIMISATION

# Check for vectorisation
F4_ENABLE_VECTORISATION

# Check for debug mode
F4_ENABLE_DEBUG

# Check if benchmarks must be build
F4_ENABLE_BENCHMARK


# Checks for libraries.

# Set DEFAULT_CHECKING_PATH variable
F4_DEFAULT_PATH

# Check for openmp, to disable the option use --enable-openmp=no
F4_CHECK_OMP

# Check for GIVARO if --with-givaro is provided
F4_CHECK_GIVARO

# Check for FFLAS-FFPACK if --with-fflas-ffpack is provided
F4_CHECK_FFLAS_FFPACK

echo "FLAGS sum up: OMPFLAGS = $OMPFLAGS, DEBUG_FLAG = $DEBUG_FLAGS, OPTIMISATION_FLAGS = $OPTIMISATION_FLAGS, VECTORISATION_FLAGS = $VECTORISATION_FLAGS"
echo "LIBS sum up: GIVARO_LIBS = $GIVARO_LIBS, GMP_LIBS = $GMP_LIBS, CBLAS_LIBS = $CBLAS_LIBS, FFLAS_FFPACK_LIBS = $FFLAS_FFPACK_LIBS"
echo "CFLAGS sum up: GIVARO_CFLAGS = $GIVARO_CFLAGS, GMP_CFLAGS = $GMP_CFLAGS, BLAS_CFLAGS = $BLAS_CFLAGS, FFLAS_FFPACK_CFLAGS = $FFLAS_FFPACK_CFLAGS"

# Checks for header files.
AC_CHECK_HEADERS([string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.

AC_CONFIG_FILES([
 Makefile
 openf4/Makefile
 openf4/include/Makefile
 openf4/src/Makefile
 benchmark/Makefile
 example/Makefile
])

AC_OUTPUT

