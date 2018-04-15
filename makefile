
default: build

# ------------------------------------------------------------------------------------------

googletest/make/gtest.a:

googletest/make/gtest_main.a:

googletest: googletest/make/gtest.a googletest/make/gtest_main.a
	make -C googletest/make gtest.a
	make -C googletest/make gtest_main.a

# ------------------------------------------------------------------------------------------

albybigmath/lib/libalbybigmath.a:

albybigmath: albybigmath/lib/libalbybigmath.a
	make -C albybigmath

# ------------------------------------------------------------------------------------------

smoketest/bin/smoketest:

smoketest: smoketest/bin/smoketest
	make -C smoketest

# ------------------------------------------------------------------------------------------
	
clean:
	make -C googletest/make clean
	make -C albybigmath clean
	make -C smoketest clean

build: googletest albybigmath smoketest

rebuild: clean build

smoke: build
	smoketest/bin/smoketest

test: build
	unittest/bin/unitest

# ------------------------------------------------------------------------------------------


