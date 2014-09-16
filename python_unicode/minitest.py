from transliterate_unicode import cjhebrew_to_unicode, betacode_greek_to_unicode

def testg(s):
    print repr(s), repr(betacode_greek_to_unicode(s, True)), \
        betacode_greek_to_unicode(s, True)

def test(s):
    print repr(s), repr(cjhebrew_to_unicode(s)), cjhebrew_to_unicode(s)

test("'")
test("'bg")
test("'E:mEt")

print

testg("lo/gos")
