dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(FoscamSearchTool, 1.0.0, [alfredo.pons@gmail.com])

AC_CANONICAL_SYSTEM

# Overrides default g++ flags: -g -O2
if test -z $CXXFLAGS; then
    CXXFLAGS=''
fi

AM_INIT_AUTOMAKE([subdir-objects])

AC_PROG_CXX
# Use the C++ compiler for the following checks
AC_LANG([C++])
# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([string])
AC_CHECK_HEADERS([iostream])
AC_CHECK_HEADERS([fstream])
# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_PID_T
AC_TYPE_SIZE_T

# distribute additional compiler and linker flags among Makefiles
# --> set and change these variables instead of CXXFLAGS or LDFLAGS (for user only)
AC_SUBST([AM_CXXFLAGS])
AC_SUBST([AM_LDFLAGS])

AC_CONFIG_FILES(Makefile)
AC_OUTPUT
