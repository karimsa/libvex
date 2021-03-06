@ECHO OFF
REM --------------------------------------------------------
REM make.bat -- builds all the sources into one header file
REM 
REM Copyright (C) 2014 Karim Alibhai.
REM --------------------------------------------------------

IF "%1" == "doc" (GOTO :DOC)
IF "%1" == "update" (GOTO :UPDATE)
IF "%1" == "test" (GOTO :TEST)

ECHO.Compiling headers ...
ECHO.#ifndef _LIBVEX_H>libvex.h
ECHO.#define _LIBVEX_H>>libvex.h
ECHO.>>libvex.h
ECHO.// import easyC API>>libvex.h
ECHO.#include "API.h">>libvex.h
FOR /F "tokens=*" %%F in ('dir /b include\*.h') DO TYPE include\%%F >>libvex.h
ECHO.#endif>>libvex.h

ECHO.Compiling source ...
ECHO.#include "libvex.h">libvex.c
ECHO.#ifdef _LIBVEX_H>>libvex.c
FOR /F "tokens=*" %%F in ('dir /b lib\*.c') DO TYPE src\%%F >>libvex.c
ECHO.#endif>>libvex.c

GOTO :EOF

:TEST
ECHO.Compiling headers ...
ECHO.#ifndef _LIBVEX_H>test\libvex.h
ECHO.#define _LIBVEX_H>>test\libvex.h
ECHO.#define __TEST_LV__>>test\libvex.h
ECHO.#include "test.h">>test\libvex.h
FOR /F "tokens=*" %%F in ('dir /b include\*.h') DO TYPE include\%%F >>test\libvex.h
ECHO.#endif>>test\libvex.h
ECHO.Compiling source ...
ECHO.#include "libvex.h">test\libvex.c
ECHO.#ifdef _LIBVEX_H>>test\libvex.c
FOR /F "tokens=*" %%F in ('dir /b lib\*.c') DO TYPE src\%%F >>test\libvex.c
ECHO.#endif>>test\libvex.c
ECHO.Compiling object files ...
gcc -Itest -c test/libvex.c -o test/libvex.o -Wall
GOTO :EOF

:DOC
doxygen
GOTO :EOF

:UPDATE
git pull origin master
GOTO :EOF
