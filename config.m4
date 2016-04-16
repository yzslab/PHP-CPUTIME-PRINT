dnl $Id$
dnl config.m4 for extension cputime

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(cputime, for cputime support,
dnl Make sure that the comment is aligned:
dnl [  --with-cputime             Include cputime support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(cputime, whether to enable cputime support,
dnl Make sure that the comment is aligned:
[  --enable-cputime           Enable cputime support])

if test "$PHP_CPUTIME" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-cputime -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/cputime.h"  # you most likely want to change this
  dnl if test -r $PHP_CPUTIME/$SEARCH_FOR; then # path given as parameter
  dnl   CPUTIME_DIR=$PHP_CPUTIME
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for cputime files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       CPUTIME_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$CPUTIME_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the cputime distribution])
  dnl fi

  dnl # --with-cputime -> add include path
  dnl PHP_ADD_INCLUDE($CPUTIME_DIR/include)

  dnl # --with-cputime -> check for lib and symbol presence
  dnl LIBNAME=cputime # you may want to change this
  dnl LIBSYMBOL=cputime # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $CPUTIME_DIR/$PHP_LIBDIR, CPUTIME_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_CPUTIMELIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong cputime lib version or lib not found])
  dnl ],[
  dnl   -L$CPUTIME_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(CPUTIME_SHARED_LIBADD)

  PHP_NEW_EXTENSION(cputime, cputime.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
