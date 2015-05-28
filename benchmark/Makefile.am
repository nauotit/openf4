AM_CPPFLAGS= -Wall -funroll-loops -ftree-vectorize -std=c++11 -DNDEBUG -Wno-strict-overflow -fopenmp -march=native 
#AM_LDFLAGS= -fopenmp
AM_LDFLAGS=-lgivaro -lcblas -latlas -lgmp -lgmpxx -fopenmp

noinst_PROGRAMS = benchmark_short benchmark_int benchmark_long benchmark_semaev benchmark_givaro_modular_log16 benchmark_givaro_modular_integer benchmark_gf2_extension
benchmark_short_SOURCES = benchmark-short.cpp
benchmark_int_SOURCES = benchmark-int.cpp
benchmark_long_SOURCES = benchmark-long.cpp
benchmark_semaev_SOURCES = benchmark-semaev.cpp
benchmark_givaro_modular_log16_SOURCES = benchmark-givaro-modular-log16.cpp
benchmark_givaro_modular_integer_SOURCES = benchmark-givaro-modular-integer.cpp
benchmark_gf2_extension_SOURCES = benchmark-gf2-extension.cpp
