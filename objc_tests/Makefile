include ../flags.mak

PROGS=cj2unicode.mm greek_case.mm
OBJS=$(PROGS:%.mm=%.o) 

all: $(PROGS:%.mm=%) thelib

#%.o: %.mm 
#	libtool --mode=compile gcc $(CFLAGS) -I.. -g -c -o $@ $<

%: %.mm
	libtool --mode=link gcc -g -framework Foundation \
		-L../ -ltransliterate -I.. -o $@ $<


thelib:
	cd ..; make

depend:
	$(CXX) -MM $(PROGS) >> depend

clean:
	rm -f $(PROGS:%.mm=%)
	rm -R -f .libs
	rm -f *.lo
	rm out.html

