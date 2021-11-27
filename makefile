# ------------------------------------------------------------------------------------------

default: build

# ------------------------------------------------------------------------------------------

clean:
	make -C googletest/make clean
	make -C albybigmath clean
	make -C smoketest clean
	make -C unittest clean

build: 
	make -C googletest/make gtest.a
	make -C googletest/make gtest_main.a
	make -C albybigmath 
	make -C smoketest 
	make -C unittest 

rebuild: clean build

# ------------------------------------------------------------------------------------------

smoke: build
	make -C smoketest smoke > /dev/null

smoke2: build
	make -C smoketest smoke

test: build
	make -C unittest test

version: build
	make -C smoketest version

buildversion:
	echo "const std::string version::_version = \"`cat version.txt`.${GITHUB_RUN_NUMBER}\" ;" > version.inc

# ------------------------------------------------------------------------------------------

