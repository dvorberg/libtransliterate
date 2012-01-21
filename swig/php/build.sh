#!/bin/sh -x

. ./runswig.sh

libtool --mode=compile \
    g++ `php-config --includes` -c transliterate_wrap.cpp
libtool --mode=link \
    g++ `php-config --ldflags` transliterate_wrap.o -o libphp_transliterate.la
    