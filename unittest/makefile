
default: build

# ------------------------------------------------------------------------------------------

../albybigmath/lib/libalbybigmath.a: 

# ------------------------------------------------------------------------------------------

obj/main.o: src/main.cpp
	$(CXX) -c -Os -I ../albybigmath/include -I ../googletest/include src/main.cpp -o obj/main.o

obj/environment.o: src/environment.cpp
	$(CXX) -c -Os -I ../albybigmath/include -I ../googletest/include src/environment.cpp -o obj/environment.o

obj/versionTest.o: src/versionTest.cpp
	$(CXX) -c -Os -I ../albybigmath/include -I ../googletest/include src/versionTest.cpp -o obj/versionTest.o

obj/randomTest.o: src/randomTest.cpp
	$(CXX) -c -Os -I ../albybigmath/include -I ../googletest/include src/randomTest.cpp -o obj/randomTest.o

bin/unittest: ../albybigmath/lib/libalbybigmath.a obj/main.o obj/environment.o obj/versionTest.o obj/randomTest.o
	$(CXX) -s \
		obj/main.o \
		obj/environment.o \
		obj/versionTest.o \
		obj/randomTest.o \
		-L ../albybigmath/lib \
		-L ../googletest/make \
		-l:libalbybigmath.a \
		-l:libmpfr.a \
		-l:libgmp.a \
		-l:gtest.a \
		-lpthread \
		-o bin/unittest 
	ldd ./bin/unittest

# ------------------------------------------------------------------------------------------
	
clean:
	rm -vf obj/*
	rm -vf bin/*

build: bin/unittest 

rebuild: clean build

test: build
	./bin/unittest --gtest_color=yes $(ARG)

# ------------------------------------------------------------------------------------------
# make test "ARG=--gtest_repeat=2 --gtest_filter=*det*"
# ------------------------------------------------------------------------------------------
