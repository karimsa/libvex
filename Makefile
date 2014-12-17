# --------------------------------------------------------
# Makefile
# builds all the sources into one header file
# Copyright (C) 2014 Karim Alibhai.
# --------------------------------------------------------

all: src doc

test: .PHONY
	@echo Compiling headers ...
	@echo \#ifndef _LIBVEX_H > test/libvex.h
	@echo \#define _LIBVEX_H >> test/libvex.h
	@echo \#define __TEST_LV__ >> test/libvex.h
	@echo \#include \"test.h\" >> test/libvex.h
	@for i in include/*.h; do cat $$i >> test/libvex.h; done
	@echo \#endif >> test/libvex.h
	@echo Compiling source ...
	@echo \#include \"libvex.h\" > test/libvex.c
	@echo \#ifdef _LIBVEX_H >> test/libvex.c
	@for i in src/*.c; do cat $$i >> test/libvex.c; done
	@echo \#endif >> test/libvex.c
	@echo Compiling object files ...
	@gcc -Itest -c test/libvex.c -o test/libvex.o -Wall

src: .PHONY
	@echo Compiling headers ...
	@echo \#ifndef _LIBVEX_H > libvex.h
	@echo \#define _LIBVEX_H >> libvex.h
	@for i in include/*.h; do cat $$i >> libvex.h; done
	@echo \#endif >> libvex.h
	@echo Compiling sources ...
	@echo \#include "libvex.h" > libvex.c
	@echo \#ifdef _LIBVEX_H >> libvex.c
	@for i in src/*.c; do cat $$i >> libvex.c; done
	@echo \#endif >> libvex.c

doc: src .PHONY
	doxygen

update:
	git pull origin master

.PHONY:

