
default: build

obj/main.o: src/main.cpp 
	g++ -c -Os src/main.cpp -o obj/main.o

obj/mpfr.o: lib/mpfr.cpp lib/mpfr.h 
	g++ -c -Os lib/mpfr.cpp -o obj/mpfr.o

obj/mpfr_t_wrapper.o: lib/mpfr_t_wrapper.cpp lib/mpfr_t_wrapper.h
	g++ -c -Os lib/mpfr_t_wrapper.cpp -o obj/mpfr_t_wrapper.o

obj/stringhlp.o: lib/stringhlp.cpp lib/stringhlp.h 
	g++ -c -Os lib/stringhlp.cpp -o obj/stringhlp.o

obj/numberParser.o: lib/numberParser.cpp lib/numberParser.h 
	g++ -c -Os lib/numberParser.cpp -o obj/numberParser.o

bin/libalbybigmath.a: obj/mpfr.o obj/mpfr_t_wrapper.o obj/stringhlp.o obj/numberParser.o
	ar rvs bin/libalbybigmath.a \
		obj/mpfr.o \
		obj/mpfr_t_wrapper.o \
		obj/stringhlp.o \
		obj/numberParser.o \

bin/mpfrtest: obj/main.o bin/libalbybigmath.a
	g++ -s -static -static-libgcc -static-libstdc++ \
		obj/main.o \
		-L bin \
		-l:libalbybigmath.a \
		-l:libmpfr.a \
		-l:libgmp.a \
		-o bin/mpfrtest \
	#ldd ./mpfrtest
		
clean:
	rm -vf obj/*
	rm -vf bin/*

build: bin/libalbybigmath.a bin/mpfrtest

rebuild: clean build

test: build
	bin/mpfrtest

