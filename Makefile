include flags.mak

# The sources for the library
SRCS=betacode_utf8.c++ betacode_utf16.c++ cjhebrew.c++

# Test programs (these won't be installed)

OBJS=$(SRCS:%.c++=%.o) code_tables.o

CODE_LISTS=coptic.tbl greek_asterisk.tbl greek_case.tbl\
	latin.tbl specials.tbl\
	greek_precombined_case.tbl greek_precombined_asterisk.tbl\
	cjhebrew.tbl
CODE_CXX=$(CODE_LISTS:%.tbl=%.inc)

all: code_tables.o libtransliterate.la 

%.o: %.c++
	libtool --mode=compile $(CXX) $(CFLAGS) -c -o $@ $<

%.inc: %.tbl
	python tbl2cpp.py < $< > $@

libtransliterate.la: $(OBJS)
	libtool --mode=link gcc $(CFLAGS) -o libtransliterate.la \
		-rpath /usr/local/lib $(OBJS:%.o=%.lo)

code_tables.o: code_tables.c++ tbl2cpp.py $(CODE_CXX)

install: transliterate.h libtransliterate.la
	libtool --mode=install install -c libtransliterate.la \
		/usr/local/lib/libtransliterate.la

	install -c transliterate.h /usr/local/include/transliterate.h

depend: 
	rm -f depend
	$(CXX) -MM $(SRCS) > depend

clean:
	rm -f *.o
	rm -f *.inc
	rm -f depend

	rm -f *.lo
	rm -R -f .libs
	rm -f *.la	

-include depend


