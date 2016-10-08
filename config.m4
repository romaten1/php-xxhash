dnl $Id$
dnl config.m4 for extension xxhash

PHP_ARG_ENABLE(xxhash, whether to enable xxhash support,
[  --enable-xxhash            Enable xxhash support])

if test "$PHP_XXHASH" != "no"; then
  PHP_NEW_EXTENSION(xxhash, php_xxhash.c, $ext_shared)
fi
