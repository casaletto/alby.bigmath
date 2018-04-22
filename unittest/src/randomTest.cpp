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
	class randomTest : public testing::Test {} ;

	TEST_F( randomTest, compareMultiplicationByRtoMultiplicationByDouble ) 
	{
		abm::R::setSignificantFigures( 14 ) ;
		abm::R::setDebug( false ) ;

		abm::random rnd ;

		for ( auto i = 1 ; i <= 1000 ; i++ )
		{
			auto r = rnd.next().roundToDecimalPlaces( 1 ) ;

			auto d1 = r * abm::R( "2147483647" ) ;
			d1 = d1.roundToDecimalPlaces( 1 ) ;
			std::string str1 = d1 ;

			auto d2 = std::stod( r ) * 2147483647.0 ;
			auto str2 = abm::stringhlp::printf( 100, "+%.1f", d2 ) ;

			ASSERT_EQ( str1, str2 ) ;
		}
	}

	TEST_F( randomTest, hexSeed ) 
	{
		abm::R::setSignificantFigures( 12 ) ;
		abm::R::setDebug( false ) ;
		
		abm::random rnd( 10, abm::random::hexBytes( 3 ), abm::numberBase::_16 ) ;
		//std::cout << "seed = " << rnd.getSeed() << std::endl ;

		for ( auto i = 1 ; i <= 100 ; i++ )
		{
			auto x = rnd.next() ;
			//std::cout << x << std::endl ;

			ASSERT_TRUE( x <  "1.0" ) ;
			ASSERT_TRUE( x >= "0.0" ) ;
		}
	}

	TEST_F( randomTest, nextInteger ) 
	{
		abm::R::setSignificantFigures( 10 ) ;
		abm::R::setDebug( false ) ;

		abm::random rnd ;
		//std::cout << "seed = " << rnd.getSeed() << std::endl ;

		std::map<unsigned long, unsigned long> map ;

		for ( auto i = 1 ; i <= 6000 ; i++ )
		{
			auto x = rnd.nextInteger( 6 ) ;
		
			ASSERT_GE( x, 1 ) ;
			ASSERT_LE( x, 6 ) ;
		
			map[x]++ ;
		}	
	
		//for ( auto const &i : map )
		//	  std::cout << i.first << " = " << i.second <<std::endl ;
	}

	TEST_F( randomTest, nextReal ) 
	{
		abm::R::setSignificantFigures( 50 ) ;
		abm::R::setDebug( false ) ;

		abm::random rnd ;
		//std::cout << "seed = " << rnd.getSeed() << std::endl ;
		
		for ( auto i = 1 ; i <= 100 ; i++ )
		{
			auto x = rnd.next() ;
			//std::cout << x << std::endl ;

			ASSERT_TRUE( x <  "1.0" ) ;
			ASSERT_TRUE( x >= "0.0" ) ;		
		}
	}

	TEST_F( randomTest, hexBytes ) 
	{
		abm::R::setSignificantFigures( 50 ) ;
		abm::R::setDebug( false ) ;

		abm::random rnd ;
		//std::cout << "seed = " << rnd.getSeed() << std::endl ;
		
		for ( auto i = 1 ; i <= 100 ; i++ )
		{
			auto str = rnd.hexBytes( i ) ;
			//std::cout << str << std::endl ;

			ASSERT_EQ( i*2, str.length() ) ;
		}
	}

	TEST_F( randomTest, nanoSeconds ) 
	{
		abm::R::setSignificantFigures( 50 ) ;
		abm::R::setDebug( false ) ;

		abm::random rnd ;
		//std::cout << "seed = " << rnd.getSeed() << std::endl ;
		
		for ( auto i = 1 ; i <= 100 ; i++ )
		{
			auto str = rnd.nanosecondsSinceEpoch() ;
			//std::cout << str << std::endl ;

			ASSERT_GE( str.length(), 1 ) ;
		}
	}

} // ns

