#!/usr/bin/env python
# -*- mode: python; encoding: utf-8; -*_

## This file is part of libtransliterate
##
## Copyright 2012 by Diedrich Vorberg <diedrich@tux4web.de>
##
## All Rights Reserved.
##
## For more Information on orm see the README and LICENSE file.
##
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
## CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
## INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
## MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
## DISCLAIMED.

"""
setup.py file for libtransliterate_unicode
"""

import sys, os, os.path as op
from distutils.core import setup, Extension

usual_suspects = ( "/usr/local", "/usr", "/opt/local", "/sw", )

base_dir = "/usr/local"
for p in usual_suspects:
    fp = op.join(p, "include", "transliterate.h")
    if op.exists(fp):
        base_dir = p
        break

include_dirs = [ op.join(base_dir, "include"), ]
library_dirs = [ op.join(base_dir, "lib"), ]
    
transliterate_unicode = Extension( "transliterate_unicode",
                                   sources=["transliterate_unicode.cxx",],
                                   include_dirs = include_dirs,
                                   library_dirs = library_dirs,
                                   libraries = ["transliterate"])

setup (name = "transliterate_unicode",
       version = "0.0",
       author      = "Diedrich Vorberg <diedrich@tux4web.de>",
       description = "Wrapper for libtransliterate that returns unicode " +\
           "strings",
       ext_modules = [transliterate_unicode],
       py_modules = ["transliterate_unicode"], 
       )
