#ACLOCAL_AMFLAGS = -I m4
include_HEADERS = include/ice.hpp
noinst_HEADERS = include/hashClass.hpp

lib_LTLIBRARIES = libice.la
libice_la_SOURCES = \
 src/hash.cc\
 src/ice.cc
libice_la_CPPFLAGS = -I$(top_srcdir)/include


noinst_PROGRAMS = bin/ice_example
bin_ice_example_SOURCES = src/main.cc
bin_ice_example_CPPFLAGS = -I$(top_srcdir)/include
bin_ice_example_LDADD = libice.la
