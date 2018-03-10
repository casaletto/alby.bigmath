
default: build

obj/main.o: src/main.cpp 
	g++ -c -Os src/main.cpp -o obj/main.o

obj/mpfr.o: src/mpfr.cpp src/mpfr.h 
	g++ -c -Os src/mpfr.cpp -o obj/mpfr.o

obj/mpfr_t_wrapper.o: src/mpfr_t_wrapper.cpp src/mpfr_t_wrapper.h
	g++ -c -Os src/mpfr_t_wrapper.cpp -o obj/mpfr_t_wrapper.o

obj/stringhlp.o: src/stringhlp.cpp src/stringhlp.h 
	g++ -c -Os src/stringhlp.cpp -o obj/stringhlp.o

bin/mpfrtest: obj/main.o obj/mpfr.o obj/mpfr_t_wrapper.o obj/stringhlp.o
	g++ -s -o \
		bin/mpfrtest \
		obj/main.o \
		obj/mpfr.o \
		obj/mpfr_t_wrapper.o \
		obj/stringhlp.o \
		-static -static-libgcc -static-libstdc++ \
		-l:libmpfr.a -l:libgmp.a 
	#ldd ./mpfrtest
		
clean:
	rm -vf obj/*.o 
	rm -vf bin/mpfrtest

build: bin/mpfrtest

rebuild: clean build

test: build
	bin/mpfrtest

