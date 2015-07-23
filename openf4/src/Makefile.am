# FLAGS

AM_CPPFLAGS= $(OPTIMISATION_FLAGS) $(DEBUG_FLAGS) $(VECTORISATION_FLAGS) -I$(top_srcdir)

AM_LDFLAGS = 

if OPENF4_HAVE_OMP
AM_LDFLAGS+= $(OMPFLAGS)
AM_CPPFLAGS+= $(OMPFLAGS)
endif

if OPENF4_HAVE_GIVARO
AM_LDFLAGS+=$(GIVARO_LIBS) $(GMP_LIBS)
AM_CPPFLAGS+=$(GIVARO_CFLAGS) $(GMP_CFLAGS)
endif

if OPENF4_HAVE_FFLAS_FFPACK
AM_LDFLAGS+=$(CBLAS_LIBS) $(FFLAS_FFPACK_LIBS)
AM_CPPFLAGS+=$(BLAS_CFLAGS) $(FFLAS_FFPACK_CFLAGS)
endif


# Library 

lib_LTLIBRARIES = libopenf4.la
libopenf4_la_SOURCES = libopenf4.cpp $(top_srcdir)/libopenf4.h

# Header to distribute

pkgincludesubdir=$(pkgincludedir)/src

pkgincludesub_HEADERS = element-gf2-extension.inl libopenf4.cpp single-list.inl specialisation-simd-gf2-extension.inl
pkgincludesub_HEADERS += element-gf2.inl matrix.inl specialisation-echelonize-fflas-ffpack.inl specialisation-simd-prime.inl
pkgincludesub_HEADERS += element-givaro.inl monomial-array.inl specialisation-echelonize-gf2-extension.inl tagged-polynomial.inl
pkgincludesub_HEADERS += critical-pair.inl element-prime.inl monomial.inl specialisation-echelonize-gf2.inl term.inl
pkgincludesub_HEADERS += ideal.inl polynomial.inl specialisation-echelonize-prime.inl

