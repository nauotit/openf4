AM_CPPFLAGS= -Wall -funroll-loops -ftree-vectorize -std=c++11 -DNDEBUG -Wno-strict-overflow -fopenmp -march=native
AM_LDFLAGS= -fopenmp

lib_LTLIBRARIES = libf4.la
libf4_la_SOURCES = libf4.cpp $(top_srcdir)/include/libf4.h
include_HEADERS = $(top_srcdir)/include/libf4.h
