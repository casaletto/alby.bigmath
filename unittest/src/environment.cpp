#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <inttypes.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <vector>
#include <fstream>
#include <iomanip>
#include <assert.h>    
#include <algorithm>
#include <regex>
#include <random>
#include <chrono>
#include <thread>
#include <gmp.h>
#include <mpfr.h>
#include "albybigmath/albybigmath.h"
#include "gtest/gtest.h"
#include "environment.h"

namespace t 
{
	environment* environment::pEnvironment = NULL ;

	environment::environment() : testing::Environment()
	{
		std::cout << "environment::environment()"  << std::endl ;
	}

	environment::~environment() 
	{
		std::cout << "environment::~environment()"  << std::endl ;
	}

	void environment::SetUp() 
	{
		std::cout << "environment::SetUp()"  << std::endl ;
	}

	void environment::TearDown() 
	{
		std::cout << "environment::TearDown()" << std::endl ;
	}

	void environment::set( environment* p ) 
	{
		pEnvironment = p ;
	}
	
	environment* environment::get() 
	{
		return pEnvironment ;
	}

	void environment::hello() 
	{
		std::cout << "environment::hello()" << std::endl ;
	}

} // ns

