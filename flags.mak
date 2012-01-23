# -*- mode: makefile; coding: utf-8; -*-

UNAME := $(shell uname)

CFLAGS=-g -pipe
LDFLAGS=-pipe

ifeq ($(UNAME), Darwin)
CFLAGS+=-arch i386 -arch x86_64
LDFLAGS+=-arch=i386 -arch x86_64
endif