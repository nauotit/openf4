AM_CPPFLAGS= -Wall -funroll-loops -ftree-vectorize -std=c++11 -DNDEBUG -Wno-strict-overflow -fopenmp -march=native
AM_LDFLAGS= -fopenmp

noinst_PROGRAMS = benchmark_short benchmark_int benchmark_long benchmark_semaev
benchmark_short_SOURCES = benchmark-short.cpp
benchmark_int_SOURCES = benchmark-int.cpp
benchmark_long_SOURCES = benchmark-long.cpp
benchmark_semaev_SOURCES = benchmark-semaev.cpp
