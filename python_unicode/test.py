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

from string import *
from transliterate_unicode import *

elohim = "'E:lohiym"
gen1_1 = ("b*:re'+siyt b*ArA' 'E:lohiym 'et ha+s*Amayim w:'et "
          "hA'ArE.s; w:hA'ArE.s hAy:tAh tohU wAbohU w:.ho+sEk: "
          "`al--p*:ney t:hOm w:rU/a.h 'E:lohiym "
          "m:ra.hEpEt `al--p*:ney ham*Ayim;")

def append_greek_betacode(betacode, asterisk):
    for precombined in ( True, False, ):
        append( (u"betacode_greek…(INPUT, precombined=%s, "
                 "asterisk_syntax=%s)") % (repr(precombined), repr(asterisk),),
                betacode,
                betacode_greek_to_unicode(betacode, precombined, asterisk) )
        
def append_cjhebrew(cjhebrew):
    append("cjhebrew_to_unicode",
           cjhebrew,
           cjhebrew_to_unicode(cjhebrew))
    
def main():
    chapter("Betacode Greek")
    append_greek_betacode(r"lo/gos sa/rc e)ge/neto", False)
    append_greek_betacode(r"Swkra/ths", False)
    append_greek_betacode(r"*SWKRA/THS", True)
    append_greek_betacode(r"*S*W*K*R*A*T*H*S", True)
    append_greek_betacode(r"O)/ida ou)de\n ei)dw/s", False)
    append_greek_betacode(r")/Oida ou)de\n ei)dw/s", False)
    append_greek_betacode(r"*)/OIDA OU)DE\N EI)DW/S", True)

    chapter("cjhbrew")
    append_cjhebrew("'E:lohiym")
    append_cjhebrew("""b*:re'+siyt b*ArA' 'E:lohiym 'et ha+s*Amayim w:'et
                       hA'ArE.s; w:hA'ArE.s hAy:tAh tohU wAbohU w:.ho+sEk:
                       `al--p*:ney t:hOm w:rU/a.h 'E:lohiym
                       m:ra.hEpEt `al--p*:ney ham*Ayim;""")


trs = []

def chapter(title):
    trs.append('<tr><td class="title" colspan="4">%s</tr></tr>' % title)

def append(function_name, markup, result):
    if "hebrew" in function_name:
        dir = "rtl"
    else:
        dir = "ltr"
    
    trs.append(u'''\
<tr>
  <td><code>%s</code></td>
  <td><code>%s</code></td>
  <td dir="%s">%s</td>
  <td>%i</td>
</tr>''' % ( function_name, markup, dir, result,
             len(result.encode("utf-16"))/2))


main()

tbody = join(trs, "\n")
    
html = '''<html>
  <head>
    <meta http-equiv="Content-Type" 
          content="string:text/html; charset=UTF-8" />
    <style type="text/css">
      body
      {
         font-family: "CMU Sans Serif", sans-serif;
      }

      table
      {

      }

      td
      {
        vertial-align: top;
        border-top: grey 1px solid;
        padding: 4px;
      }

      td.title
      {
         background-color: grey;
         color: white;
         margin-top: 1em;
      }
    </style>
  </head>
  <body>
    <table cellspacing="0">
      <tbody>    
        %s
      </tbody>
    </table>
  </body>
</html>''' % tbody.encode("utf-8")

print html
