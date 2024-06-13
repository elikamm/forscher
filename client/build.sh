#!/bin/sh

i686-w64-mingw32-windres forscher.rc -O coff -o forscher.res

i686-w64-mingw32-g++ *.cpp forscher.res -lws2_32 -static -o forscher.exe