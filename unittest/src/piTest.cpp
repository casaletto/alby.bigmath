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

namespace t
{
	class piTest : public testing::Test {} ;

	TEST_F( piTest, nilakantha ) 
	{
		abm::R::setSignificantFigures( 15 ) ;
		abm::R::setDebug( false ) ;

		auto pi = abm::pi::nilakantha( 5000 ) ;
		//std::cout << pi << std::endl ;	

		EXPECT_TRUE( abm::stringhlp::startsWith( pi, "+3.14159265358" ) ) ;
	}

	TEST_F( piTest, ramanujan ) 
	{
		// n = 100, 1432 dp
		// pi = +3.1415926535897932384626433..............42699227967823547816360093417216412199245 

		abm::R::setSignificantFigures( 1500 ) ;
		abm::R::setDebug( false ) ;

		auto pi = abm::pi::ramanujan( 100 ) ;
		//std::cout << pi << std::endl ;
		
		std::string str = abm::stringhlp::left( pi, 1432 + 3 ) ;
		//std::cout << str << std::endl ;
		//std::cout << str.length() << std::endl ;

		EXPECT_EQ( 1435, str.length() ) ;
		EXPECT_TRUE( abm::stringhlp::startsWith( str, "+3.1415926535897932384626433"              ) ) ;
		EXPECT_TRUE( abm::stringhlp::endsWith  ( str, "42699227967823547816360093417216412199245" ) ) ;
	}

	TEST_F( piTest, nonic ) 
	{
		// n = 4, dp = 1984
		// pi = +3.141592653589793238462...50471237137869609563643719172874677646575739624138908658326459958

		abm::R::setSignificantFigures( 1985 ) ;
		abm::R::setDebug( false ) ;

		auto pi = abm::pi::nonic( 4 ) ;
		//std::cout << pi << std::endl ;
		//std::cout << pi.toString().length() << std::endl ;

		EXPECT_EQ( 1987, pi.toString().length() ) ;
		EXPECT_TRUE( abm::stringhlp::startsWith( pi, "+3.141592653589793238462"                                          ) ) ;
		EXPECT_TRUE( abm::stringhlp::endsWith  ( pi, "50471237137869609563643719172874677646575739624138908658326459958" ) ) ;
	}

	TEST_F( piTest, calculatePiToOneMillionDecimalPlacesAndDoItTenMillionTimes ) 
	{
		for ( int i = 1; i <= 1E7 ; i++ ) // calculate 10 million times
			  piTest_nonic_Test() ;
	}


} // ns

