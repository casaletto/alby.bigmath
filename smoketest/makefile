
default: build

# ------------------------------------------------------------------------------------------

../albybigmath/lib/libalbybigmath.a:

# ------------------------------------------------------------------------------------------

obj/main.o: src/main.cpp
	$(CXX) -c -Os -I ../albybigmath/include src/main.cpp -o obj/main.o

bin/smoketest: obj/main.o ../albybigmath/lib/libalbybigmath.a
	$(CXX) -s -static -static-libgcc -static-libstdc++ \
		obj/main.o \
		-L ../albybigmath/lib \
		-l:libalbybigmath.a \
		-l:libmpfr.a \
		-l:libgmp.a \
		-o bin/smoketest \
	#ldd ./bin/smoketest

# ------------------------------------------------------------------------------------------
	
clean:
	rm -vf obj/*
	rm -vf bin/*

build: bin/smoketest 

rebuild: clean build

smoke: build
	./bin/smoketest

version: build
	./bin/smoketest --version

# ------------------------------------------------------------------------------------------

