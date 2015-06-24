# FLAGS

AM_CPPFLAGS= $(OPTIMISATION_FLAGS) $(DEBUG_FLAGS) $(VECTORISATION_FLAGS) -I$(top_srcdir)

AM_LDFLAGS = 

if F4_HAVE_OMP
AM_LDFLAGS+= $(OMPFLAGS)
AM_CPPFLAGS+= $(OMPFLAGS)
endif

if F4_HAVE_GIVARO
AM_LDFLAGS+=$(GIVARO_LIBS) $(GMP_LIBS)
AM_CPPFLAGS+=$(GIVARO_CFLAGS) $(GMP_CFLAGS)
endif

if F4_HAVE_FFLAS_FFPACK
AM_LDFLAGS+=$(CBLAS_LIBS) $(FFLAS_FFPACK_LIBS)
AM_CPPFLAGS+=$(BLAS_CFLAGS) $(FFLAS_FFPACK_CFLAGS)
endif


# Executable

noinst_PROGRAMS = check_cyclic6_16bits check_cyclic6_32bits check_cyclic6_64bits check_cyclic6_gf2_extension_16bits check_cyclic6_gf2_extension_32bits check_cyclic6_gf2_extension_64bits check_cyclic6_gf2
noinst_PROGRAMS += check_random_16bits check_random_32bits check_random_64bits check_random_gf2_extension_16bits check_random_gf2_extension_32bits check_random_gf2_extension_64bits check_aes_gf2_extension_16bits
if F4_HAVE_GIVARO
noinst_PROGRAMS += check_cyclic6_256bits
endif
noinst_PROGRAMS += tutorial_method2 tutorial_method3 tutorial_gf2_method2 tutorial_gf2_method3 tutorial_gf2_extension_method2 tutorial_gf2_extension_method3
if F4_HAVE_GIVARO
noinst_PROGRAMS += tutorial_big_modulo_method2 tutorial_big_modulo_method3
endif


# Souces

check_cyclic6_16bits_SOURCES = check-cyclic6-16bits.cpp
check_cyclic6_16bits_LDADD = $(top_builddir)/openf4/src/libopenf4.la 

check_cyclic6_32bits_SOURCES = check-cyclic6-32bits.cpp
check_cyclic6_32bits_LDADD = $(top_builddir)/openf4/src/libopenf4.la 

check_cyclic6_64bits_SOURCES = check-cyclic6-64bits.cpp
check_cyclic6_64bits_LDADD = $(top_builddir)/openf4/src/libopenf4.la 

check_cyclic6_gf2_SOURCES = check-cyclic6-gf2.cpp
check_cyclic6_gf2_LDADD = $(top_builddir)/openf4/src/libopenf4.la

check_cyclic6_gf2_extension_16bits_SOURCES = check-cyclic6-gf2-extension-16bits.cpp
check_cyclic6_gf2_extension_16bits_LDADD = $(top_builddir)/openf4/src/libopenf4.la 

check_cyclic6_gf2_extension_32bits_SOURCES = check-cyclic6-gf2-extension-32bits.cpp
check_cyclic6_gf2_extension_32bits_LDADD = $(top_builddir)/openf4/src/libopenf4.la 

check_cyclic6_gf2_extension_64bits_SOURCES = check-cyclic6-gf2-extension-64bits.cpp
check_cyclic6_gf2_extension_64bits_LDADD = $(top_builddir)/openf4/src/libopenf4.la 

check_random_16bits_SOURCES=check-random-16bits.cpp
check_random_16bits_LDADD = $(top_builddir)/openf4/src/libopenf4.la 

check_random_32bits_SOURCES=check-random-32bits.cpp
check_random_32bits_LDADD = $(top_builddir)/openf4/src/libopenf4.la

check_random_64bits_SOURCES=check-random-64bits.cpp
check_random_64bits_LDADD = $(top_builddir)/openf4/src/libopenf4.la

check_random_gf2_extension_16bits_SOURCES=check-random-gf2-extension-16bits.cpp
check_random_gf2_extension_16bits_LDADD = $(top_builddir)/openf4/src/libopenf4.la 

check_random_gf2_extension_32bits_SOURCES=check-random-gf2-extension-32bits.cpp
check_random_gf2_extension_32bits_LDADD = $(top_builddir)/openf4/src/libopenf4.la

check_random_gf2_extension_64bits_SOURCES=check-random-gf2-extension-64bits.cpp
check_random_gf2_extension_64bits_LDADD = $(top_builddir)/openf4/src/libopenf4.la

check_aes_gf2_extension_16bits_SOURCES=check-aes-gf2-extension-16bits.cpp
check_aes_gf2_extension_16bits_LDADD = $(top_builddir)/openf4/src/libopenf4.la 

if F4_HAVE_GIVARO
check_cyclic6_256bits_SOURCES = check-cyclic6-256bits.cpp
check_cyclic6_256bits_LDADD = $(top_builddir)/openf4/src/libopenf4.la
endif

tutorial_method2_SOURCES = tutorial-method2.cpp
tutorial_method2_LDADD = $(top_builddir)/openf4/src/libopenf4.la

tutorial_method3_SOURCES = tutorial-method3.cpp

if F4_HAVE_GIVARO
tutorial_big_modulo_method2_SOURCES = tutorial-big-modulo-method2.cpp
tutorial_big_modulo_method2_LDADD = $(top_builddir)/openf4/src/libopenf4.la

tutorial_big_modulo_method3_SOURCES = tutorial-big-modulo-method3.cpp
endif

tutorial_gf2_method2_SOURCES = tutorial-gf2-method2.cpp
tutorial_gf2_method2_LDADD = $(top_builddir)/openf4/src/libopenf4.la

tutorial_gf2_method3_SOURCES = tutorial-gf2-method3.cpp

tutorial_gf2_extension_method2_SOURCES = tutorial-gf2-extension-method2.cpp
tutorial_gf2_extension_method2_LDADD = $(top_builddir)/openf4/src/libopenf4.la

tutorial_gf2_extension_method3_SOURCES = tutorial-gf2-extension-method3.cpp

#noinst_PROGRAMS += test_monomial test_dynamic_array test_monomial_array test_term test_single_list test_polynomial test_tagged_polynomial
#noinst_PROGRAMS += test_critical_pair test_list_pointer_critical_pair test_avl_critical_pair test_avl_monomial test_avl_polynomial
#noinst_PROGRAMS += test_element_prime test_matrix test_ideal test_element_gf2_extension test_libf4

#if F4_HAVE_GIVARO
#noinst_PROGRAMS += test_element_givaro 
#endif

#test_monomial_SOURCES = test-monomial.cpp
#test_dynamic_array_SOURCES = test-dynamic-array.cpp
#test_monomial_array_SOURCES = test-monomial-array.cpp
#test_term_SOURCES = test-term.cpp
#test_single_list_SOURCES = test-single-list.cpp
#test_polynomial_SOURCES = test-polynomial.cpp
#test_tagged_polynomial_SOURCES = test-tagged-polynomial.cpp

#test_critical_pair_SOURCES = test-critical-pair.cpp
#test_list_pointer_critical_pair_SOURCES = test-list-pointer-critical-pair.cpp
#test_avl_critical_pair_SOURCES = test-avl-critical-pair.cpp
#test_avl_monomial_SOURCES = test-avl-monomial.cpp
#test_avl_polynomial_SOURCES = test-avl-polynomial.cpp

#test_element_prime_SOURCES = test-element-prime.cpp
#test_element_gf2_extension_SOURCES = test-element-gf2-extension.cpp
#test_element_givaro_SOURCES = test-element-givaro.cpp
#test_matrix_SOURCES = test-matrix.cpp
#test_ideal_SOURCES = test-ideal.cpp
#test_libf4_SOURCES = test-libf4.cpp


# For check target

TESTS = check_cyclic6_16bits check_cyclic6_32bits check_cyclic6_64bits check_cyclic6_gf2_extension_16bits check_cyclic6_gf2_extension_32bits check_cyclic6_gf2_extension_64bits check_cyclic6_gf2
TESTS += check_random_16bits check_random_32bits check_random_64bits check_random_gf2_extension_16bits check_random_gf2_extension_32bits check_random_gf2_extension_64bits check_aes_gf2_extension_16bits

if F4_HAVE_GIVARO
TESTS += check_cyclic6_256bits
endif
