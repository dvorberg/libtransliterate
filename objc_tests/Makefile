include ../flags.mak

PROGS=cj2unicode.mm
OBJS=$(PROGS:%.mm=%.o) 

all: $(PROGS:%.mm=%) thelib

%: %.mm 
	libtool --mode=link gcc $(CFLAGS) -framework Foundation \
		-L.. -ltransliterate -o $@ $<

thelib:
	cd ..; make

depend:
	$(CXX) -MM $(PROGS) >> depend

clean:
	rm -f $(PROGS:%.mm=%)

