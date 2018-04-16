
default: build

# ------------------------------------------------------------------------------------------

../albybigmath/lib/libalbybigmath.a:

# ------------------------------------------------------------------------------------------

obj/main.o: src/main.cpp
	g++ -c -Os -I ../albybigmath/include src/main.cpp -o obj/main.o

bin/unittest: obj/main.o ../albybigmath/lib/libalbybigmath.a
	g++ -s -static -static-libgcc -static-libstdc++ \
		obj/main.o \
		-L ../albybigmath/lib \
		-l:libalbybigmath.a \
		-l:libmpfr.a \
		-l:libgmp.a \
		-o bin/unittest \
	#ldd ./bin/unittest

# ------------------------------------------------------------------------------------------
	
clean:
	rm -vf obj/*
	rm -vf bin/*

build: bin/unittest 

rebuild: clean build

test: build
	./bin/unittest

# ------------------------------------------------------------------------------------------

