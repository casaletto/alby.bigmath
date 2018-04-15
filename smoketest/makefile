
default: build

# ------------------------------------------------------------------------------------------

obj/main.o: src/main.cpp
	g++ -c -Os -I ../albybigmath/include src/main.cpp -o obj/main.o

bin/smoketest: obj/main.o 
	g++ -s -static -static-libgcc -static-libstdc++ \
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

# ------------------------------------------------------------------------------------------

