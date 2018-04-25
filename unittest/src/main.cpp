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

namespace abm = alby::bigmath ; 

int main( int argc, char** argv )
{
	int rc = 1 ;
	std::cout << "[BEGIN] main()" << std::endl ;

	try
	{
	  	testing::InitGoogleTest( &argc, argv ) ;
		t::environment::init() ;

  		rc = RUN_ALL_TESTS() ;		
	}
	catch( const std::exception& ex )
	{
		std::cout << "EXCEPTION: " << ex.what() << std::endl ;
	}
	catch( ... )
	{
		std::cout << "EXCEPTION: ..." << std::endl ;
	}

	std::cout << abm::stringcat( "[FINISH] main() rc [", rc, "]" ) << std::endl ;
	return rc ;	
}

