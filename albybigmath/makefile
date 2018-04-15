
default: build

# ------------------------------------------------------------------------------------------

obj/R.o: src/R.cpp include/albybigmath/*.h 
	g++ -c -Os -I include src/R.cpp -o obj/R.o

obj/mpfr_t_wrapper.o: src/mpfr_t_wrapper.cpp include/albybigmath/*.h
	g++ -c -Os -I include src/mpfr_t_wrapper.cpp -o obj/mpfr_t_wrapper.o

obj/Q.o: src/Q.cpp include/albybigmath/*.h 
	g++ -c -Os -I include src/Q.cpp -o obj/Q.o

obj/mpq_t_wrapper.o: src/mpq_t_wrapper.cpp include/albybigmath/*.h
	g++ -c -Os -I include src/mpq_t_wrapper.cpp -o obj/mpq_t_wrapper.o

obj/stringhlp.o: src/stringhlp.cpp include/albybigmath/*.h 
	g++ -c -Os -I include src/stringhlp.cpp -o obj/stringhlp.o

obj/numberhlp.o: src/numberhlp.cpp include/albybigmath/*.h 
	g++ -c -Os -I include src/numberhlp.cpp -o obj/numberhlp.o

obj/random.o: src/random.cpp include/albybigmath/*.h 
	g++ -c -Os -I include src/random.cpp -o obj/random.o

obj/pi.o: src/pi.cpp include/albybigmath/*.h 
	g++ -c -Os -I include src/pi.cpp -o obj/pi.o

obj/version.o: src/version.cpp include/albybigmath/*.h 
	g++ -c -Os -I include src/version.cpp -o obj/version.o

lib/libalbybigmath.a: obj/R.o obj/mpfr_t_wrapper.o obj/Q.o obj/mpq_t_wrapper.o obj/stringhlp.o obj/numberhlp.o obj/random.o obj/pi.o obj/version.o
	ar rvs lib/libalbybigmath.a \
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
	
clean:
	rm -vf obj/*
	rm -vf lib/*

build: lib/libalbybigmath.a 

rebuild: clean build

# ------------------------------------------------------------------------------------------


