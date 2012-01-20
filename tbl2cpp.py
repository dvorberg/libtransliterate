#!/usr/bin/env python

import sys, re
from string import *

def pair(line):
    ret = strip(split(line, "//")[0])
    if ret == "":
        return None
    else:
        beta, codepoint = splitfields(ret)

        beta = replace(beta, "\\", "\\\\")
        beta = replace(beta, '"', '\\"')
        
        return beta, int(codepoint, 16)
    
def main():
    pairs = map(pair, sys.stdin.readlines())
    pairs = filter(lambda p: p is not None, pairs)

    for beta, codepoint in pairs:
        print 'container->add_pair("%s",\t0x%04x);' % ( beta, codepoint, )
    
    
main()    
