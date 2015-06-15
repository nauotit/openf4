SUBDIRS = f4 example
if F4_HAVE_BENCHMARK
SUBDIRS += benchmark
endif

dist_doc_DAT = README
ACLOCAL_AMFLAGS=-I m4
EXTRA_DIST = doc

include_HEADERS= f4.h libf4.h

pkgincludesubdir=$(pkgincludedir)/include
pkgincludesub_HEADERS = config.h


