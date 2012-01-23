#!/bin/sh -x

. ./runswig.sh

g++ `php-config --includes` -fpic -c transliterate_wrap.cpp
g++ -shared transliterate_wrap.o -ltransliterate -o transliterate.so
