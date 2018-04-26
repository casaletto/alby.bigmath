
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

obj/piTest.o: src/piTest.cpp
	$(CXX) -c -Os -I ../albybigmath/include -I ../googletest/include src/piTest.cpp -o obj/piTest.o

obj/rationalTest.o: src/rationalTest.cpp
	$(CXX) -c -Os -I ../albybigmath/include -I ../googletest/include src/rationalTest.cpp -o obj/rationalTest.o

obj/realTest.o: src/realTest.cpp
	$(CXX) -c -Os -I ../albybigmath/include -I ../googletest/include src/realTest.cpp -o obj/realTest.o

obj/mixedQandRTest.o: src/mixedQandRTest.cpp
	$(CXX) -c -Os -I ../albybigmath/include -I ../googletest/include src/mixedQandRTest.cpp -o obj/mixedQandRTest.o

bin/unittest: ../albybigmath/lib/libalbybigmath.a \
obj/main.o obj/environment.o obj/versionTest.o obj/randomTest.o obj/piTest.o obj/rationalTest.o obj/realTest.o obj/mixedQandRTest.o
	$(CXX) -s -static -static-libgcc -static-libstdc++\
		obj/main.o \
		obj/environment.o \
		obj/versionTest.o \
		obj/randomTest.o \
		obj/piTest.o \
		obj/rationalTest.o \
		obj/realTest.o \
		obj/mixedQandRTest.o \
		-L ../albybigmath/lib \
		-L ../googletest/make \
		-l:libalbybigmath.a \
		-l:libmpfr.a \
		-l:libgmp.a \
		-l:gtest.a \
		-o bin/unittest 
	ldd ./bin/unittest || true

# ------------------------------------------------------------------------------------------
	
clean:
	rm -vf obj/*
	rm -vf bin/*

build: bin/unittest 

rebuild: clean build

test: build
	./bin/unittest --gtest_color=yes $(ARG)

# ------------------------------------------------------------------------------------------
# make test "ARG=--gtest_shuffle --gtest_repeat=10"
# make test "ARG=--gtest_shuffle --gtest_repeat=2 --gtest_filter=*det*"
# ------------------------------------------------------------------------------------------
