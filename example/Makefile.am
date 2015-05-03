bin_PROGRAMS = test_monomial test_dynamic_array test_monomial_array test_term test_single_list test_polynomial test_tagged_polynomial
bin_PROGRAMS += test_critical_pair test_list_pointer_critical_pair test_avl_critical_pair test_avl_monomial test_avl_polynomial
bin_PROGRAMS += test_element_prime test_matrix test_ideal
bin_PROGRAMS += check_cyclic6_16bits check_cyclic6_32bits check_cyclic6_64bits
#bin_PROGRAMS += test_libf4 test_openmp /test_fflas_ffpack 

test_monomial_SOURCES = test-monomial.cpp
test_dynamic_array_SOURCES = test-dynamic-array.cpp
test_monomial_array_SOURCES = test-monomial-array.cpp
test_term_SOURCES = test-term.cpp
test_single_list_SOURCES = test-single-list.cpp
test_polynomial_SOURCES = test-polynomial.cpp
test_tagged_polynomial_SOURCES = test-tagged-polynomial.cpp

test_critical_pair_SOURCES = test-critical-pair.cpp
test_list_pointer_critical_pair_SOURCES = test-list-pointer-critical-pair.cpp
test_avl_critical_pair_SOURCES = test-avl-critical-pair.cpp
test_avl_monomial_SOURCES = test-avl-monomial.cpp
test_avl_polynomial_SOURCES = test-avl-polynomial.cpp

test_element_prime_SOURCES = test-element-prime.cpp
test_matrix_SOURCES = test-matrix.cpp
test_ideal_SOURCES = test-ideal.cpp

check_cyclic6_16bits_SOURCES = check-cyclic6-16bits.cpp
check_cyclic6_32bits_SOURCES = check-cyclic6-32bits.cpp
check_cyclic6_64bits_SOURCES = check-cyclic6-64bits.cpp

#test_libf4_SOURCES = test-libf4.cpp
#test_openmp_SOURCES = test-openmp.cpp
#test_fflas_ffpack_SOURCES = test-fflas-ffpack.cpp

AM_CPPFLAGS= -I$(top_srcdir)/include -Wall -funroll-loops -ftree-vectorize -std=c++11 -DNDEBUG -Wno-strict-overflow -fopenmp -march=native
AM_LDFLAGS= -fopenmp -L$(top_builddir)/src -lf4 

TESTS = check_cyclic6_16bits check_cyclic6_32bits check_cyclic6_64bits
