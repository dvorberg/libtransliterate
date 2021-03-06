include flags.mak

RELEASE=0.1

# The sources for the library
SRCS=betacode_greek.c++ betacode_coptic.c++ betacode_hebrew.c++ \
	cjhebrew.c++ conversion.c++
OBJS=$(SRCS:%.c++=%.o) code_tables.o

CODE_LISTS=greek_asterisk.tbl greek_case.tbl\
	greek_precombined_case.tbl greek_precombined_asterisk.tbl\
	hebrew.tbl\
	coptic.tbl\
	specials.tbl\
	cjhebrew.tbl
CODE_CXX=$(CODE_LISTS:%.tbl=%.inc)

all: code_tables.o libtransliterate.la 

%.o: %.c++
	${LIBTOOL} --mode=compile --tag CXX $(CXX) $(CFLAGS) -Werror -c -o $@ $<


%.inc: %.tbl tbl2cpp.py
	python2 tbl2cpp.py < $< > $@

libtransliterate.la: $(OBJS)
	${LIBTOOL} --mode=link --tag CXX \
		g++ $(CFLAGS) -o libtransliterate.la -release $(RELEASE) \
			-rpath /usr/local/lib $(OBJS:%.o=%.lo)

code_tables.o: code_tables.c++ tbl2cpp.py $(CODE_CXX)

install: transliterate.h libtransliterate.la
	${LIBTOOL} --mode=install install -c libtransliterate.la \
		/usr/local/lib/libtransliterate.la

	install -c transliterate.h /usr/local/include/transliterate.h

ifeq ($(UNAME), Linux)
	ldconfig
endif

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


