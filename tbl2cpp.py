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

import sys, re
from string import *

underscore_re = re.compile(r"(_$)|(__$)")

def underscore_replacer(match):
    space, underscore = match.groups()
    if space is None:
        return "_"
    else:
        return " "

def quote_quote(s):
    s = replace(s, "\\", "\\\\")
    s = replace(s, '"', '\\"')
    return s
    
    
def pair(line):
    ret = strip(split(line, "//")[0])
    if ret == "":
        return None
    else:
        parts = splitfields(ret)
        beta = parts[0]

        beta = underscore_re.sub(underscore_replacer, beta)
        beta = quote_quote(beta)
        
        return beta, map(lambda hex: int(hex, 16), parts[1:])
    
def main():
    print "// DO NOT MODIFY!"
    print "// This file has been automatically generated."
    print
    
    pairs = map(pair, sys.stdin.readlines())
    pairs = filter(lambda p: p is not None, pairs)

    counter = 0
    for beta, codepoints in pairs:
        #u = map(unichr, codepoints)
        #u = join(u, "")
        #utf8 = u.encode("utf-8")
        #utf8 = quote_quote(utf8)
        #, (char *)"%s"
        
        codepoints.append(0)
        codepoints = map(lambda codepoint: "0x%04x" % codepoint, codepoints)
        codepoints = join(codepoints, ", ")
        print 'static uint16_t tpl%i[] = {%s};' % ( counter, codepoints, )
        print 'container->add_pair((char *)"%s", tpl%s);' % (
            beta, counter, )

        counter += 1
    
    
main()    
