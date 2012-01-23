from transliterate import *

def reverse(utf8):
    u = unicode(utf8, "utf-8")
    return u[::-1]
    
print "Betacode Greek"
print betacode_greek_to_utf8("lo/gos")
print

print "Betacode Hebrew"
print betacode_hebrew_to_utf8("Alhym2")

# You need to rtl yourself
print reverse(betacode_hebrew_to_utf8("Alhym2"))
print

print "cjhebrew"
print cjhebrew_to_utf8("'E:lohiym")

# dito.
print reverse(cjhebrew_to_utf8("'E:lohiym"))
