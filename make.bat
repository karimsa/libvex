@ECHO OFF
REM --------------------------------------------------------
REM make.bat -- builds all the sources into one header file
REM 
REM Copyright (C) 2014 Karim Alibhai.
REM --------------------------------------------------------

ECHO.Compiling headers ...
ECHO.#ifndef __LIBVEX_H>libvex.h
ECHO.#define __LIBVEX_H>>libvex.h
FOR /F "tokens=*" %%F in ('dir /b include\*.h') DO TYPE include\%%F >>libvex.h
ECHO.#endif __LIBVEX_H>>libvex.h

ECHO.Compiling source ...
ECHO.#ifdef __LIBVEX_H>libvex.c
ECHO.#define __LIBVEX_H>>libvex.c
FOR /F "tokens=*" %%F in ('dir /b src\*.c') DO TYPE src\%%F >>libvex.c
ECHO.#endif __LIBVEX_H>>libvex.c

GOTO :EOF