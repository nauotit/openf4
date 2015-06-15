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

noinst_PROGRAMS = benchmark_short benchmark_int benchmark_long benchmark_semaev benchmark_gf2 benchmark_gf2_extension_16_bits benchmark_gf2_extension_32_bits benchmark_gf2_extension_64_bits
if F4_HAVE_GIVARO
noinst_PROGRAMS += benchmark_givaro_modular_integer benchmark_givaro_gfq benchmark_givaro_modular_log16
endif


# Sources

benchmark_short_SOURCES = benchmark-short.cpp
benchmark_int_SOURCES = benchmark-int.cpp
benchmark_long_SOURCES = benchmark-long.cpp
benchmark_semaev_SOURCES = benchmark-semaev.cpp
benchmark_gf2_SOURCES = benchmark-gf2.cpp
benchmark_gf2_extension_16_bits_SOURCES = benchmark-gf2-extension-16bits.cpp
benchmark_gf2_extension_32_bits_SOURCES = benchmark-gf2-extension-32bits.cpp
benchmark_gf2_extension_64_bits_SOURCES = benchmark-gf2-extension-64bits.cpp

if F4_HAVE_GIVARO
benchmark_givaro_modular_integer_SOURCES = benchmark-givaro-modular-integer.cpp
benchmark_givaro_gfq_SOURCES = benchmark-givaro-gfq.cpp
benchmark_givaro_modular_log16_SOURCES = benchmark-givaro-modular-log16.cpp
endif

