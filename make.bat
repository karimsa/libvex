@ECHO OFF
REM --------------------------------------------------------
REM make.bat -- builds all the sources into one header file
REM 
REM Copyright (C) 2014 Karim Alibhai.
REM --------------------------------------------------------

IF "%1" == "doc" (GOTO :DOC)
IF "%1" == "update" (GOTO :UPDATE)

ECHO.Compiling headers ...
ECHO.#ifndef _LIBVEX_H>libvex.h
ECHO.#define _LIBVEX_H>>libvex.h
FOR /F "tokens=*" %%F in ('dir /b include\*.h') DO TYPE include\%%F >>libvex.h
ECHO.#endif>>libvex.h

ECHO.Compiling source ...
ECHO.#include "libvex.h">libvex.c
ECHO.#ifdef _LIBVEX_H>>libvex.c
FOR /F "tokens=*" %%F in ('dir /b src\*.c') DO TYPE src\%%F >>libvex.c
ECHO.#endif>>libvex.c

GOTO :EOF

:DOC
doxygen
GOTO :EOF

:UPDATE
git pull origin master
GOTO :EOF
