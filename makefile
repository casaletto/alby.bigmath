
default: build

# ------------------------------------------------------------------------------------------

obj/mpfr.o: lib/mpfr.cpp lib/*.h 
	g++ -c -Os lib/mpfr.cpp -o obj/mpfr.o

obj/mpfr_t_wrapper.o: lib/mpfr_t_wrapper.cpp lib/*.h
	g++ -c -Os lib/mpfr_t_wrapper.cpp -o obj/mpfr_t_wrapper.o

obj/stringhlp.o: lib/stringhlp.cpp lib/*.h 
	g++ -c -Os lib/stringhlp.cpp -o obj/stringhlp.o

obj/numberhlp.o: lib/numberhlp.cpp lib/*.h 
	g++ -c -Os lib/numberhlp.cpp -o obj/numberhlp.o

bin/libalbybigmath.a: obj/mpfr.o obj/mpfr_t_wrapper.o obj/stringhlp.o obj/numberhlp.o
	ar rvs bin/libalbybigmath.a \
		obj/mpfr.o \
		obj/mpfr_t_wrapper.o \
		obj/stringhlp.o \
		obj/numberhlp.o \

# ------------------------------------------------------------------------------------------

obj/main.o: src/main.cpp lib/*.h
	g++ -c -Os src/main.cpp -o obj/main.o

bin/mpfrtest: obj/main.o bin/libalbybigmath.a
	g++ -s -static -static-libgcc -static-libstdc++ \
		obj/main.o \
		-L bin \
		-l:libalbybigmath.a \
		-l:libmpfr.a \
		-l:libgmp.a \
		-o bin/mpfrtest \
	#ldd ./mpfrtest

# ------------------------------------------------------------------------------------------
	
clean:
	rm -vf obj/*
	rm -vf bin/*

build: bin/mpfrtest

rebuild: clean build

test: build
	bin/mpfrtest

