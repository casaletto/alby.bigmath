
default: build


# ------------------------------------------------------------------------------------------

googletest/make/gtest.a:

googletest/make/gtest_main.a:

googletest: googletest/make/gtest.a googletest/make/gtest_main.a
	make -C googletest/make gtest.a
	make -C googletest/make gtest_main.a

# ------------------------------------------------------------------------------------------

obj/R.o: lib/R.cpp lib/*.h 
	g++ -c -Os lib/R.cpp -o obj/R.o

obj/mpfr_t_wrapper.o: lib/mpfr_t_wrapper.cpp lib/*.h
	g++ -c -Os lib/mpfr_t_wrapper.cpp -o obj/mpfr_t_wrapper.o

obj/Q.o: lib/Q.cpp lib/*.h 
	g++ -c -Os lib/Q.cpp -o obj/Q.o

obj/mpq_t_wrapper.o: lib/mpq_t_wrapper.cpp lib/*.h
	g++ -c -Os lib/mpq_t_wrapper.cpp -o obj/mpq_t_wrapper.o

obj/stringhlp.o: lib/stringhlp.cpp lib/*.h 
	g++ -c -Os lib/stringhlp.cpp -o obj/stringhlp.o

obj/numberhlp.o: lib/numberhlp.cpp lib/*.h 
	g++ -c -Os lib/numberhlp.cpp -o obj/numberhlp.o

obj/random.o: lib/random.cpp lib/*.h 
	g++ -c -Os lib/random.cpp -o obj/random.o

obj/pi.o: lib/pi.cpp lib/*.h 
	g++ -c -Os lib/pi.cpp -o obj/pi.o

obj/version.o: lib/version.cpp lib/*.h 
	g++ -c -Os lib/version.cpp -o obj/version.o

bin/libalbybigmath.a: obj/R.o obj/mpfr_t_wrapper.o obj/Q.o obj/mpq_t_wrapper.o  obj/stringhlp.o obj/numberhlp.o obj/random.o obj/pi.o obj/version.o
	ar rvs bin/libalbybigmath.a \
		obj/R.o \
		obj/mpfr_t_wrapper.o \
		obj/Q.o \
		obj/mpq_t_wrapper.o \
		obj/stringhlp.o \
		obj/numberhlp.o \
		obj/random.o \
		obj/pi.o \
		obj/version.o \

# ------------------------------------------------------------------------------------------

obj/main.o: src/main.cpp lib/*.h
	g++ -c -Os src/main.cpp -o obj/main.o

bin/mpfrtest: bin/libalbybigmath.a obj/main.o 
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
	make -C googletest/make clean
	rm -vf obj/*
	rm -vf bin/*

build: googletest bin/mpfrtest

rebuild: clean build

test: build
	bin/mpfrtest

# ------------------------------------------------------------------------------------------
