
default: build

main.o: main.cpp 
	g++ -c -Os main.cpp 

mpfr.o: mpfr.cpp mpfr.h 
	g++ -c -Os mpfr.cpp 

mpfr_t_wrapper.o: mpfr_t_wrapper.cpp mpfr_t_wrapper.h
	g++ -c -Os mpfr_t_wrapper.cpp 

mpfrtest: main.o mpfr.o mpfr_t_wrapper.o
	g++ -s -o \
		mpfrtest \
		main.o mpfr.o mpfr_t_wrapper.o \
		-static -static-libgcc -static-libstdc++ \
		-l:libmpfr.a -l:libgmp.a -l:libgmpxx.a
clean:
	rm -vf *.o mpfrtest

build: mpfrtest

rebuild: clean build

run: build
	./mpfrtest


#g++ -s -o mpfrtest main.o -lmpfr -lgmp -lgmpxx 
#ls -alth
#ldd ./mpfrtest

