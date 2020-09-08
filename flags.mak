# -*- mode: makefile; coding: utf-8; -*-

UNAME := $(shell uname)

CFLAGS=-g -pipe
LDFLAGS=-pipe

ifeq ($(UNAME), Darwin)
CFLAGS+=-arch x86_64
LDFLAGS+=-arch x86_64
LIBTOOL=glibtool
else
LIBTOOL=libtool
endif
