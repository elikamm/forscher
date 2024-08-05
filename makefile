all: build/forscher

test: all
	build/forscher build/test

build/forscher: build/src/web-src.hpp build/src/httplib.hpp
	g++ src/*.cpp -Ibuild/src -std=c++20 -o build/forscher

build/src/web-src.hpp: build/src
	find src/web -type f -exec xxd -i "{}" ";" > build/src/web-src.hpp

build/src/httplib.hpp:
	cp lib/httplib/httplib.h build/src/httplib.hpp

build/src: build
	mkdir -p build/src

build:
	mkdir -p build
