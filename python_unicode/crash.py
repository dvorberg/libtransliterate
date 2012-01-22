import transliterate_unicode
u = transliterate_unicode.cjhebrew_to_unicode(
    "b*:re'+siyt b*ArA' 'E:lohiym 'et ha+s*Amayim w:'et ")
print u.encode("utf-8")
