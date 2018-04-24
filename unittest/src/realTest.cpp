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
	class realTest : public testing::Test {} ;

	TEST_F( realTest, extremeExponents ) 
	{
		abm::R::setSignificantFigures( 22 ) ;
		abm::R::setDebug( false ) ; 

		auto a = abm::R( "1.2e10"  ) ;
		auto b = abm::R( "3.4"     ) ;
		auto c = abm::R( "5.6e-10" ) ;	

		auto sum = a + b + c ;

		//std::cout 
		//	<< a << " + " 
		//	<< b << " + " 
		//	<< c << std::endl << std::endl 
		//	<< "= " << sum << std::endl << std::endl 
		//	<< "= " << sum.toScientificNotation() << std::endl << std::endl ;

		EXPECT_EQ( "+12000000003.40000000056",     sum.toString() ) ;
		EXPECT_EQ( "+1.200000000340000000056E+10", sum.toScientificNotation() ) ;

		abm::R::setSignificantFigures( 2002 ) ;

		a = "1.2e1000"  ;
		b = "3.4"       ;
		c = "5.6e-1000" ;	

		sum = a + b + c ;

		//std::cout 
		//	<< a.toScientificNotation() << " + " 
		//	<< b << " + " 
		//	<< c.toScientificNotation() << std::endl << std::endl 
		//	<< "= " << sum << std::endl << std::endl  
		//	<< "= " << sum.toScientificNotation()  << std::endl ;

		std::string str1 = sum ;
		std::string str2 = sum.toScientificNotation() ;
		//std::cout << str1.length() << std::endl ; // 2004
		//std::cout << str2.length() << std::endl ; // 2010

		// 1.2e+2 = +120.
		// 1.3e-2 = .013 
		EXPECT_EQ  ( 1 + 1001 + 1 + 1001, str1.length() ) ;
		EXPECT_TRUE( abm::stringhlp::startsWith( str1, "+120"  ) ) ;
		EXPECT_TRUE( abm::stringhlp::endsWith  ( str1, "056"   ) ) ;
		EXPECT_TRUE( abm::stringhlp::contains  ( str1, "03.40" ) ) ;
		EXPECT_EQ  ( "03.40", abm::stringhlp::substr( str1, 1 + 1001 - 2, 5 ) ) ;

		//  +1.    20...03   40...05  6E+1000 
		//  3      1000      1000     7   
		EXPECT_EQ  ( 3 + 1000 + 1000 + 7, str2.length() ) ;
		EXPECT_TRUE( abm::stringhlp::startsWith( str2, "+1.20"     ) ) ;
		EXPECT_TRUE( abm::stringhlp::endsWith  ( str2, "056E+1000" ) ) ;
		EXPECT_TRUE( abm::stringhlp::contains  ( str2, "0340"      ) ) ;
		EXPECT_EQ  ( "0340", abm::stringhlp::substr( str2, 3 + 1000 - 2, 4 ) ) ;
	}

	TEST_F( realTest, oppositeOperations1 ) 
	{
		abm::R::setSignificantFigures( 2 ) ;
		abm::R::setDebug( false ) ; 
		
		abm::R k( "125.0234", 20 ) ;
		abm::R l( "3.12345" , 20 ) ;
		//std::cout << "k            = " << k << std::endl ;
		//std::cout << "l            = " << l << std::endl ;
		//std::cout << "k root l     = " << k.root(l) << ", " << k.root(l).toFraction() << std::endl ;
		//std::cout << "l root k     = " << l.root(k) << ", " << l.root(k).toFraction() << std::endl ;

		auto x1 = k.root(l) ^ l ;
		auto y1 = l.root(k) ^ k ;
		//std::cout << "k root l ^ l = " << x1 << ", " << x1.toFraction() << std::endl ;
		//std::cout << "l root k ^ k = " << y1 << ", " << y1.toFraction() << std::endl ;		

		EXPECT_EQ( "+125.0234", k.toString() ) ;
		EXPECT_EQ( "+3.12345",  l.toString() ) ;

		EXPECT_EQ( "+625117/5000", k.toFraction() ) ;
		EXPECT_EQ( "+62469/20000", l.toFraction() ) ;

		EXPECT_EQ( 20, x1.getSignificantFiguresLocal() ) ;
		EXPECT_EQ( 20, y1.getSignificantFiguresLocal() ) ;
	}

	TEST_F( realTest, oppositeOperations2 ) 
	{
		abm::R::setSignificantFigures( 2 ) ;
		abm::R::setDebug( false ) ; 
		
		abm::R k( "125.0234", 20 ) ;
		abm::R l( "3.12345" , 10 ) ;
		//std::cout << "k            = " << k << std::endl ;
		//std::cout << "l            = " << l << std::endl ;
		//std::cout << "k root l     = " << k.root(l) << ", " << k.root(l).toFraction() << std::endl ;
		//std::cout << "l root k     = " << l.root(k) << ", " << l.root(k).toFraction() << std::endl ;

		auto x1 = k.root(l) ^ l ;
		auto y1 = l.root(k) ^ k ;
		//std::cout << "k root l ^ l = " << x1 << ", " << x1.toFraction() << std::endl ;
		//std::cout << "l root k ^ k = " << y1 << ", " << y1.toFraction() << std::endl ;		

		EXPECT_EQ( "+125.0234", k.toString() ) ;
		EXPECT_EQ( "+3.12345",  l.toString() ) ;

		EXPECT_EQ( "+625117/5000", k.toFraction() ) ;
		EXPECT_EQ( "+62469/20000", l.toFraction() ) ;

		EXPECT_EQ( 20, x1.getSignificantFiguresLocal() ) ;
		EXPECT_EQ( 20, y1.getSignificantFiguresLocal() ) ;	
	}

	TEST_F( realTest, oppositeOperations3 ) 
	{
		abm::R::setSignificantFigures( 2 ) ;
		abm::R::setDebug( false ) ; 
		
		abm::R k( "125.0234", 10 ) ;
		abm::R l( "3.12345" , 20 ) ;
		//std::cout << "k            = " << k << std::endl ;
		//std::cout << "l            = " << l << std::endl ;
		//std::cout << "k root l     = " << k.root(l) << ", " << k.root(l).toFraction() << std::endl ;
		//std::cout << "l root k     = " << l.root(k) << ", " << l.root(k).toFraction() << std::endl ;

		auto x1 = k.root(l) ^ l ;
		auto y1 = l.root(k) ^ k ;
		//std::cout << "k root l ^ l = " << x1 << ", " << x1.toFraction() << std::endl ;
		//std::cout << "l root k ^ k = " << y1 << ", " << y1.toFraction() << std::endl ;		

		EXPECT_EQ( "+125.0234", k.toString() ) ;
		EXPECT_EQ( "+3.12345",  l.toString() ) ;

		EXPECT_EQ( "+625117/5000", k.toFraction() ) ;
		EXPECT_EQ( "+62469/20000", l.toFraction() ) ;

		EXPECT_EQ( 20, x1.getSignificantFiguresLocal() ) ;
		EXPECT_EQ( 20, y1.getSignificantFiguresLocal() ) ;
	}

	TEST_F( realTest, compare ) 
	{
		abm::R::setSignificantFigures( 10 ) ;
		abm::R::setDebug( false ) ; 
		
		abm::R a = abm::Q( "+5/12" ).toR() ; // a > b
		abm::R b = abm::Q( "+1/6"  ).toR() ;

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

		b = a + abm::Q( "+1/1000000000000000000000" ).toR() ; // a < b
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

	TEST_F( realTest, validReals ) 
	{
		std::vector<std::string> rng =
		{
			"3.14e34",
			"-3.14e34",
			"+3.14e34",
			"3.14e+34",
			"-3.14e+34",
			"+3.14e+34",
			"3.14e-34",
			"-3.14e-34",
			"+3.14e-34",
			"3.14e0",
			"-3.14e0",
			"+3.14e0",
			"3.14e+0",
			"-3.14e+0",
			"+3.14e+0",
			"3.14e-0",
			"-3.14e-0",
			"+3.14e-0",
			"3.14",
			"-3.14",
			"+3.14",
			"3",
			"-3",
			"+3",
			"0",
			"-0",
			"+0"
			"0000000000.0000000000000",
			"-000000000000.0000000",
			"+0000000000.0000000000",
			"0000000000.0000000000000e0000000",
			"-000000000000.0000000e000000000000",
			"+0000000000.0000000000e00000000000",
			
			"00000000001234560000000.000000000076543200000000e0000000000089765000000",
			"+00000000001234560000000.000000000076543200000000e-0000000000089765000000",
			"-00000000001234560000000.000000000076543200000000e+0000000000089765000000",

			"00000000001234560000000.000000000076543200000000",
			"+00000000001234560000000.000000000076543200000000",
			"-00000000001234560000000.000000000076543200000000",

			"0",
			"000",
			"00000000",
			"00000e000000000000",
		} ;

		for ( auto& str : rng )
		{
			auto b = abm::R( str ) ;
		} ;
	}

	TEST_F( realTest, invalidReals ) 
	{
		std::vector<std::string> rng =
		{
			"",
			"fred",
			"12345.678.",
			"12345.678.1",
			"12345....678.",
			"12345....678....",
			".0",
			".",
			"34e45.44",
			"34e45.....44",
			"   232356wq ",
			"+3.14ee-0",
			".1232",
			".1232e232.22222",
		} ;

		for ( auto& str : rng )
		{
			EXPECT_ANY_THROW
			({
				auto b = abm::R( str ) ;
			});
		} ;
	}
	
	TEST_F( realTest, base16 ) 
	{
		abm::R::setSignificantFigures( 50 ) ;
		abm::R::setDebug( false ) ; 
		
		auto u = abm::R( "-FFee.100", abm::R::getSignificantFigures(), abm::numberBase::_16 ) ;
		//std::cout << u << std::endl ;

		auto v = abm::R( "FFFF.FFFF", abm::R::getSignificantFigures(), abm::numberBase::_16 ) ;
		//std::cout << v << std::endl ;

		EXPECT_EQ( "-65518.0625",             u.toString() ) ;
		EXPECT_EQ( "+65535.9999847412109375", v.toString() ) ;
	}

	TEST_F( realTest, base2 ) 
	{
		abm::R::setSignificantFigures( 50 ) ;
		abm::R::setDebug( false ) ; 

		auto v = abm::R( "-11111111.01", abm::R::getSignificantFigures(), abm::numberBase::_2 ) ;
		//std::cout << v << std::endl ;

		EXPECT_EQ( "-255.25", v.toString() ) ;
	}
	
	TEST_F( realTest, roundingDecimalPlaces ) 
	{
		abm::R::setSignificantFigures( 50 ) ;
		abm::R::setDebug( false ) ; 

		abm::R x = "123456.12345678901234567890" ;

		auto z = x.roundToDecimalPlaces( 50 ) ;
		EXPECT_EQ( "+123456.1234567890123456789", z ) ;

		z = x.roundToDecimalPlaces( 22 ) ;
		EXPECT_EQ( "+123456.1234567890123456789", z ) ;

		z = x.roundToDecimalPlaces( 21 ) ;
		EXPECT_EQ( "+123456.1234567890123456789", z ) ;
		
		z = x.roundToDecimalPlaces( 20 ) ;
		EXPECT_EQ( "+123456.1234567890123456789", z ) ;

		z = x.roundToDecimalPlaces( 19 ) ;
		EXPECT_EQ( "+123456.1234567890123456789", z ) ;

		z = x.roundToDecimalPlaces( 18 ) ;
		EXPECT_EQ( "+123456.123456789012345679", z ) ;

		z = x.roundToDecimalPlaces( 17 ) ;
		EXPECT_EQ( "+123456.12345678901234568", z ) ;

		z = x.roundToDecimalPlaces( 16 ) ;
		EXPECT_EQ( "+123456.1234567890123457", z ) ;

		z = x.roundToDecimalPlaces( 15 ) ;
		EXPECT_EQ( "+123456.123456789012346", z ) ;

		z = x.roundToDecimalPlaces( 14 ) ;
		EXPECT_EQ( "+123456.12345678901235", z ) ;

		z = x.roundToDecimalPlaces( 13 ) ;
		EXPECT_EQ( "+123456.1234567890123", z ) ;

		z = x.roundToDecimalPlaces( 12 ) ;
		EXPECT_EQ( "+123456.123456789012", z ) ;

		z = x.roundToDecimalPlaces( 11 ) ;
		EXPECT_EQ( "+123456.12345678901", z ) ;

		z = x.roundToDecimalPlaces( 10 ) ;
		EXPECT_EQ( "+123456.1234567890", z ) ;

		z = x.roundToDecimalPlaces( 9 ) ;
		EXPECT_EQ( "+123456.123456789", z ) ;

		z = x.roundToDecimalPlaces( 8 ) ;
		EXPECT_EQ( "+123456.12345679", z ) ;

		z = x.roundToDecimalPlaces( 7 ) ;
		EXPECT_EQ( "+123456.1234568", z ) ;

		z = x.roundToDecimalPlaces( 6 ) ;
		EXPECT_EQ( "+123456.123457", z ) ;

		z = x.roundToDecimalPlaces( 5 ) ;
		EXPECT_EQ( "+123456.12346", z ) ;
		
		z = x.roundToDecimalPlaces( 4 ) ;
		EXPECT_EQ( "+123456.1235", z ) ;
		
		z = x.roundToDecimalPlaces( 3 ) ;
		EXPECT_EQ( "+123456.123", z ) ;
		
		z = x.roundToDecimalPlaces( 2 ) ;
		EXPECT_EQ( "+123456.12", z ) ;

		z = x.roundToDecimalPlaces( 1 ) ;
		EXPECT_EQ( "+123456.1", z ) ;
		
		z = x.roundToDecimalPlaces( 0 ) ;
		EXPECT_EQ( "+123456.0", z ) ;	

		x = "123456.100000000000000000000000001" ;
		z = x.roundToDecimalPlaces( 10 ) ;
		EXPECT_EQ( "+123456.1000000000", z ) ;			
	}

	TEST_F( realTest, roundingSignificantFigures ) 
	{
		abm::R::setSignificantFigures( 50 ) ;
		abm::R::setDebug( false ) ; 

		abm::R x = "123456.12345678901234567890" ;

		auto z = x.toSignificantFigures( 50 ) ;
		EXPECT_EQ( "+1.2345612345678901234567890000000000000000000000000E+5", z ) ;

		z = x.toSignificantFigures( 28 ) ;
		EXPECT_EQ( "+1.234561234567890123456789000E+5", z ) ;

		z = x.toSignificantFigures( 27 ) ;
		EXPECT_EQ( "+1.23456123456789012345678900E+5", z ) ;

		z = x.toSignificantFigures( 26 ) ;
		EXPECT_EQ( "+1.2345612345678901234567890E+5", z ) ;

		z = x.toSignificantFigures( 25 ) ;
		EXPECT_EQ( "+1.234561234567890123456789E+5", z ) ;

		z = x.toSignificantFigures( 24 ) ;
		EXPECT_EQ( "+1.23456123456789012345679E+5", z ) ;

		z = x.toSignificantFigures( 23 ) ;
		EXPECT_EQ( "+1.2345612345678901234568E+5", z ) ;

		z = x.toSignificantFigures( 22 ) ;
		EXPECT_EQ( "+1.234561234567890123457E+5", z ) ;

		z = x.toSignificantFigures( 21 ) ;
		EXPECT_EQ( "+1.23456123456789012346E+5", z ) ;

		z = x.toSignificantFigures( 20 ) ;
		EXPECT_EQ( "+1.2345612345678901235E+5", z ) ;

		z = x.toSignificantFigures( 19 ) ;
		EXPECT_EQ( "+1.234561234567890123E+5", z ) ;

		z = x.toSignificantFigures( 18 ) ;
		EXPECT_EQ( "+1.23456123456789012E+5", z ) ;

		z = x.toSignificantFigures( 17 ) ;
		EXPECT_EQ( "+1.2345612345678901E+5", z ) ;

		z = x.toSignificantFigures( 16 ) ;
		EXPECT_EQ( "+1.234561234567890E+5", z ) ;

		z = x.toSignificantFigures( 15 ) ;
		EXPECT_EQ( "+1.23456123456789E+5", z ) ;

		z = x.toSignificantFigures( 14 ) ;
		EXPECT_EQ( "+1.2345612345679E+5", z ) ;

		z = x.toSignificantFigures( 13 ) ;
		EXPECT_EQ( "+1.234561234568E+5", z ) ;

		z = x.toSignificantFigures( 12 ) ;
		EXPECT_EQ( "+1.23456123457E+5", z ) ;

		z = x.toSignificantFigures( 11 ) ;
		EXPECT_EQ( "+1.2345612346E+5", z ) ;

		z = x.toSignificantFigures( 10 ) ;
		EXPECT_EQ( "+1.234561235E+5", z ) ;

		z = x.toSignificantFigures( 9 ) ;
		EXPECT_EQ( "+1.23456123E+5", z ) ;

		z = x.toSignificantFigures( 8 ) ;
		EXPECT_EQ( "+1.2345612E+5", z ) ;

		z = x.toSignificantFigures( 7 ) ;
		EXPECT_EQ( "+1.234561E+5", z ) ;

		z = x.toSignificantFigures( 6 ) ;
		EXPECT_EQ( "+1.23456E+5", z ) ;

		z = x.toSignificantFigures( 5 ) ;
		EXPECT_EQ( "+1.2346E+5", z ) ;

		z = x.toSignificantFigures( 4 ) ;
		EXPECT_EQ( "+1.235E+5", z ) ;

		z = x.toSignificantFigures( 3 ) ;
		EXPECT_EQ( "+1.23E+5", z ) ;

		z = x.toSignificantFigures( 2 ) ;
		EXPECT_EQ( "+1.2E+5", z ) ;

		z = x.toSignificantFigures( 1 ) ;
		EXPECT_EQ( "+1.0E+5", z ) ;
	}

} // ns

