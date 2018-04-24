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
	class rationalTest : public testing::Test {} ;

	TEST_F( rationalTest, basicMath1 ) 
	{
		// 5/49 + 3/21 - 6/25 = 6/1225 
		auto a = abm::Q( "5/49" ) + "3/21" - "6/25" ;
		//std::cout << "a = " << a << std::endl ;
		EXPECT_EQ( "+6/1225", a.toString() ) ;
		
		// 2 2/3 + 1 1/4 - 5/6 = 37/12
		auto b = abm::Q( 2,"2/3" ) + abm::Q( 1,"1/4" ) - "5/6" ;
		//std::cout << "b = " << b << std::endl ;
		EXPECT_EQ( "+37/12", b.toString() ) ;

		// ( 3 - 2/3 ) / 5/6 = 14/5
		auto c = ( abm::Q(3) - "2/3" ) / "5/6" ;
		//std::cout << "c = " << c << std::endl ;
		EXPECT_EQ( "+14/5", c.toString() ) ;

		// 1 2/7 / 5 = 9/35
		auto d = abm::Q( 1,"2/7" ) / 5 ;
		//std::cout << "d = " << d << std::endl ;
		EXPECT_EQ( "+9/35", d.toString() ) ;

		// 1 2/3 / ( 1 1/4 * 4 2/5 ) = 10/33
		auto e = abm::Q( 1,"2/3" ) / ( abm::Q( 1,"1/4" ) * abm::Q( 4,"2/5" ) ) ;
		//std::cout << "e = "             << e << std::endl ;
		//std::cout << "e numerator   = " << e.numerator()   << std::endl ;
		//std::cout << "e denominator = " << e.denominator() << std::endl ;
		EXPECT_EQ( "+10/33", e.toString() ) ;
		EXPECT_EQ( "+10", e.numerator() ) ;
		EXPECT_EQ( "+33", e.denominator() ) ;

		e *= -1 ;	
		//std::cout << "e = "             << e << std::endl ;
		//std::cout << "e numerator   = " << e.numerator()   << std::endl ;
		//std::cout << "e denominator = " << e.denominator() << std::endl ;
		EXPECT_EQ( "-10/33", e.toString() ) ;
		EXPECT_EQ( "-10", e.numerator() ) ;
		EXPECT_EQ( "+33", e.denominator() ) ;
	}

	TEST_F( rationalTest, basicMath2 ) 
	{
		abm::Q a = "  2 / 8   " ;
		abm::Q b = " -  2 0 / 3    0 " ;

		auto c = a + b ;
		auto d = a - b ;
		auto e = a * b ;
		auto f = a / b ;

		//std::cout << "a = " << a << std::endl ;
		//std::cout << "b = " << b << std::endl ;
		//std::cout << "c = " << c << std::endl ;
		//std::cout << "d = " << d << std::endl ;
		//std::cout << "e = " << e << std::endl ;
		//std::cout << "f = " << f << std::endl ;

		EXPECT_EQ( "+1/4"  , a.toString() ) ;
		EXPECT_EQ( "-2/3"  , b.toString() ) ;
		EXPECT_EQ( "-5/12" , c.toString() ) ;
		EXPECT_EQ( "+11/12", d.toString() ) ;
		EXPECT_EQ( "-1/6"  , e.toString() ) ;
		EXPECT_EQ( "-3/8"  , f.toString() ) ;

		c += a ;
		//std::cout << "c = " << c << std::endl ;
		EXPECT_EQ( "-1/6" , c.toString() ) ;

		c -= a ;
		//std::cout << "c = " << c << std::endl ;
		EXPECT_EQ( "-5/12" , c.toString() ) ;

		c *= a ;
		//std::cout << "c = " << c << std::endl ;
		EXPECT_EQ( "-5/48" , c.toString() ) ;

		c /= a ;
		//std::cout << "c = " << c << std::endl ;
		EXPECT_EQ( "-5/12" , c.toString() ) ;

		auto g = c.inv() ;
		auto h = c.neg() ;
		auto i = c.abs() ;
		auto j = c.neg().abs() ;

		//std::cout << "g = " << g << std::endl ;
		//std::cout << "h = " << h << std::endl ;
		//std::cout << "i = " << i << std::endl ;
		//std::cout << "j = " << j << std::endl ;

		EXPECT_EQ( "-12/5" , g.toString() ) ;
		EXPECT_EQ( "+5/12" , h.toString() ) ;
		EXPECT_EQ( "+5/12" , i.toString() ) ;
		EXPECT_EQ( "+5/12" , j.toString() ) ;
	}

	TEST_F( rationalTest, compare ) 
	{
		abm::Q a = "+5/12" ; // a > b
		abm::Q b = "+1/6"  ;

		EXPECT_FALSE( a == b ) ;
		EXPECT_TRUE ( a != b ) ;
		EXPECT_FALSE( a <  b ) ;
		EXPECT_FALSE( a <= b ) ;
		EXPECT_TRUE ( a >  b ) ;
		EXPECT_TRUE ( a >= b ) ;

		b = a  ; // a == b
		EXPECT_TRUE ( a == b ) ;
		EXPECT_FALSE( a != b ) ;
		EXPECT_FALSE( a <  b ) ;
		EXPECT_TRUE ( a <= b ) ;
		EXPECT_FALSE( a >  b ) ;
		EXPECT_TRUE ( a >= b ) ;

		b = a + "+1/1000000000000000000000" ; // a < b
		EXPECT_FALSE ( a == b ) ;
		EXPECT_TRUE  ( a != b ) ;
		EXPECT_TRUE  ( a <  b ) ;
		EXPECT_TRUE  ( a <= b ) ;
		EXPECT_FALSE ( a >  b ) ;
		EXPECT_FALSE ( a >= b ) ;

		a *= -1 ; // a < b
		EXPECT_FALSE ( a == b ) ;
		EXPECT_TRUE  ( a != b ) ;
		EXPECT_TRUE  ( a <  b ) ;
		EXPECT_TRUE  ( a <= b ) ;
		EXPECT_FALSE ( a >  b ) ;
		EXPECT_FALSE ( a >= b ) ;

		b *= -1 ; // a > b
		EXPECT_FALSE( a == b ) ; 
		EXPECT_TRUE ( a != b ) ;
		EXPECT_FALSE( a <  b ) ;
		EXPECT_FALSE( a <= b ) ;
		EXPECT_TRUE ( a >  b ) ;
		EXPECT_TRUE ( a >= b ) ;
	}

} // ns


