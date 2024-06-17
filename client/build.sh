#!/bin/sh

x86_64-w64-mingw32-windres forscher.rc -O coff -o forscher.res

x86_64-w64-mingw32-g++ src/*.cpp forscher.res -lws2_32 -mwindows -static -o forscher.exe