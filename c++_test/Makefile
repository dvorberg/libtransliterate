include ../flags.mak

PROGS=beta2unicode.c++ unicode2beta.c++
OBJS=$(PROGS:%.c++=%.o) 

all: $(PROGS:%.c++=%) thelib

%.o: %.c++
	libtool --mode=compile $(CXX) $(CFLAGS) -c -o $@ $<

%: %.o	$(OBJS) 
	libtool --mode=link $(CXX) $(CFLAGS) $(LDFLAGS) \
		-L.. -ltransliterate -o $@ $<

thelib:
	cd ..; make


depend:
	$(CXX) -MM $(PROGS) >> depend

clean:
	rm -f $(PROGS:%.c++=%)

