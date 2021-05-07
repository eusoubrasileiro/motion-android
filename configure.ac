AC_INIT(libmotion, esyscmd(['./scripts/version.sh']))
AC_CONFIG_SRCDIR([src/motion.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_PROG_LIBTOOL
AC_PROG_INSTALL
AC_PROG_CC
AM_INIT_AUTOMAKE([subdir-objects foreign])
AC_GNU_SOURCE
AC_CANONICAL_HOST

##############################################################################
###  Check additional system headers
##############################################################################
AC_CHECK_HEADERS(stdio.h stdlib.h sys/time.h sys/wait.h \
    sys/ioctl.h sys/mman.h sys/param.h sys/socket.h stdarg.h \
    fcntl.h time.h signal.h limits.h errno.h assert.h netdb.h \
    ctype.h regex.h math.h locale.h dirent.h ctype.h \
    arpa/inet.h netinet/in.h termios.h,,[
    AC_MSG_ERROR([Required system headers do not exist.])
  ]
)

##############################################################################
###  Check pkg-config  - Required.  Needed to get lib paths/info
##############################################################################
AC_CHECK_PROG([PKGCONFIG],[pkg-config],[yes],[no])
AS_IF([test "${PKGCONFIG}" = "no" ],[
    AC_MSG_ERROR([Required package 'pkg-config' not found, please check motion_guide.html and install necessary dependencies.])
  ]
)

##############################################################################
###  Check pthread
##############################################################################
AC_CHECK_HEADERS(pthread.h,,AC_MSG_ERROR([pthread is required.]))
TEMP_CFLAGS="-D_THREAD_SAFE"
LIBS="$LIBS -pthread "

##############################################################################
###  Check JPG - Required.  Needed for image processing
##############################################################################
AC_CHECK_HEADERS(setjmp.h jerror.h jpeglib.h,[JPGS="yes"],[JPGS="no"])
AC_MSG_CHECKING(jpg libraries)
AC_MSG_RESULT($JPGS)
AS_IF([test "${JPGS}" = "yes" ], [
    AS_IF([pkg-config libjpeg ], [
        TEMP_CFLAGS="$TEMP_CFLAGS "`pkg-config --cflags libjpeg`
        TEMP_LIBS="$TEMP_LIBS "`pkg-config --libs libjpeg`
      ],[
        TEMP_LIBS="$TEMP_LIBS -ljpeg"
      ]
    )
  ],[
    AC_MSG_ERROR([Required package libjpeg-dev not found, please check motion_guide.html and install necessary dependencies])
  ]
)
##############################################################################
###  Check libmicrohttpd - Required.  Needed for stream/webcontrol
##############################################################################
AC_CHECK_HEADERS(microhttpd.h,[MHTTP="yes"],[MHTTP="no"])
AC_MSG_CHECKING(libmicrohttpd libraries)
AC_MSG_RESULT($MHTTP)
AS_IF([test "${MHTTP}" = "yes" ], [
    TEMP_CFLAGS="$TEMP_CFLAGS "`pkg-config --cflags libmicrohttpd`
    TEMP_LIBS="$TEMP_LIBS "`pkg-config --libs libmicrohttpd`
  ],[
    AC_MSG_ERROR([Required package libmicrohttpd-dev not found, please check motion_guide.html and install necessary dependencies])
  ]
)

##############################################################################
###  Check setting/getting thread names
##############################################################################
AC_CHECK_HEADERS(pthread_np.h,[PTHREAD_NP="yes"],[PTHREAD_NP="no"])

AC_MSG_CHECKING([for pthread_setname_np])
AC_LINK_IFELSE(
  [AC_LANG_PROGRAM([#include <pthread.h>], [pthread_setname_np(pthread_self(), "name")])
  ],[
    AC_DEFINE([HAVE_PTHREAD_SETNAME_NP], [1], [Define if you have pthread_setname_np function.])
    PTHREAD_SETNAME_NP="yes"
    AC_MSG_RESULT([yes])
  ],[
    PTHREAD_SETNAME_NP="no"
    AC_MSG_RESULT([no])
  ]
)

AC_MSG_CHECKING([for pthread_getname_np])
AC_LINK_IFELSE(
  [AC_LANG_PROGRAM([#include <pthread.h>], [pthread_getname_np(pthread_self(), NULL, 0)])
  ],[
    AC_DEFINE([HAVE_PTHREAD_GETNAME_NP], [1], [Define if you have pthread_getname_np function.])
    PTHREAD_GETNAME_NP="yes"
    AC_MSG_RESULT([yes])
  ],[
    PTHREAD_GETNAME_NP="no"
    AC_MSG_RESULT([no])
  ]
)

##############################################################################
###  Check for ffmpeg - Optional.
##############################################################################
FFMPEG_VER="--"
AC_ARG_WITH([ffmpeg],
  AS_HELP_STRING([--with-ffmpeg[=DIR]],[Build with FFMPEG support]),
  [FFMPEG=$withval],
  [FFMPEG="yes"]
)

AC_SUBST(AM_CFLAGS, "$TEMP_CFLAGS")
LIBS="$LIBS $TEMP_LIBS"
AC_SUBST(AM_LDFLAGS, "$TEMP_LDFLAGS")

AC_CONFIG_FILES([
	Makefile
	src/Makefile
])

#AC_ENABLE_SHARED
#AC_DISABLE_STATIC
LT_PREREQ([2.4])
LT_INIT

AC_OUTPUT

##############################################################################
###  Report results to user
##############################################################################
echo ""
echo "   **************************"
echo "      Configure status       "
echo "      ${PACKAGE_NAME} ${PACKAGE_VERSION}"
echo "   **************************"
echo
echo "CFLAGS: $TEMP_CFLAGS $CFLAGS"
echo
echo "LIBS: $LIBS"
echo
echo "LDFLAGS: $TEMP_LDFLAGS $LDFLAGS"
echo
echo
echo "OS                  : $host_os"
echo "pthread_np          : $PTHREAD_NP"
echo "pthread_setname_np  : $PTHREAD_SETNAME_NP"
echo "pthread_getname_np  : $PTHREAD_GETNAME_NP"
echo "XSI error           : $XSI_STRERROR"
echo "webp support        : $WEBP"
echo "V4L2 support        : $V4L2"
echo "BKTR support        : $BKTR"
echo "MMAL support        : $MMAL"
echo "FFmpeg support      : $FFMPEG"
echo "libavformat version : $FFMPEG_VER"
echo "SQLite3 support     : $SQLITE3"
echo "MYSQL support       : $MYSQL"
echo "PostgreSQL support  : $PGSQL"
echo "MariaDB support     : $MARIADB"
echo
echo  "Install prefix:       $prefix"
echo
