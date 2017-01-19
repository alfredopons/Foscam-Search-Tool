clean-local:
	rm -rf $(top_srcdir)/doc/*
	rm -rf $(top_srcdir)/autom4te.cache/*
	rm -rf $(top_srcdir)/*.tar.gz
	rm -f $(top_srcdir)/*.map $(top_srcdir)/*.sym

# additional include paths necessary to compile the C++ library
AM_CPPFLAGS = -std=c++11
AM_CXXFLAGS = -I$(top_srcdir)/src @AM_CXXFLAGS@ -O2 -Wall -Wextra
AM_CXXFLAGS += -pipe $(DEPS_CFLAGS) $(CFLAGS) 

BIN = src/FoscamSearch.cpp
BIN += src/main.cpp

bin_PROGRAMS=bin/foscam-search-tool
bin_foscam_search_tool_SOURCES=$(BIN)

