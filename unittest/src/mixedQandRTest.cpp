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
	class mixedQandRTest : public testing::Test {} ;

	TEST_F( mixedQandRTest, crossConversions1 ) 
	{
		abm::R::setSignificantFigures( 10 ) ;
		abm::R::setDebug( false ) ;
		
		// cross conversions between R and Q
		// Q(R)
		// R(Q)
		// R = Q ;
		// Q = R ;

		abm::Q q1 = "22/7"  ;
		abm::R r1 = "3.14" ;

		auto q2 = abm::Q( r1 ) ;
		auto r2 = abm::R( q2 )  ;

		abm::Q q3 ;
		abm::R r3 ;
		
		q3 = r2.toQ() ;
		r3 = q2.toR() ;

		//std::cout << "q1 = " << q1  << std::endl ;
		//std::cout << "r1 = " << r1  << std::endl ;
		//std::cout << "q2 = " << q2  << std::endl ;
		//std::cout << "r2 = " << r2  << std::endl ;
		//std::cout << "q3 = " << q3  << std::endl ;
		//std::cout << "r3 = " << r3  << std::endl ;

		EXPECT_EQ( "+22/7",   q1.toString() ) ;
		EXPECT_EQ( "+3.14",   r1.toString() ) ;
		EXPECT_EQ( "+157/50", q2.toString() ) ;
		EXPECT_EQ( "+3.14",   r2.toString() ) ;
		EXPECT_EQ( "+157/50", q3.toString() ) ;
		EXPECT_EQ( "+3.14",   r3.toString() ) ;
	}

	TEST_F( mixedQandRTest, crossConversions2 ) 
	{
		abm::R::setSignificantFigures( 10 ) ;
		abm::R::setDebug( false ) ;

		// more Q and R math
		// R = r * q, r = q* r, q = q *r, q = r* q

		abm::Q q1 = "22/7" ;
		abm::R r1 = "3.14" ;

		abm::R r2 = r1       * q1.toR() ;
		abm::R r3 = q1.toR() * r1       ;

		abm::Q q2 = r1.toQ() * q1       ;
		abm::Q q3 = q1       * r1.toQ() ;

		//std::cout << "q1 = " << q1 << std::endl ;
		//std::cout << "r1 = " << r1 << std::endl ;
		//std::cout << "q2 = " << q2 << std::endl ;
		//std::cout << "q3 = " << q3 << std::endl ;
		//std::cout << "r2 = " << r2 << std::endl ;
		//std::cout << "r3 = " << r3 << std::endl ;

		EXPECT_EQ( "+22/7",        q1.toString() ) ;
		EXPECT_EQ( "+3.14",        r1.toString() ) ;
		EXPECT_EQ( "+1727/175",    q2.toString() ) ;
		EXPECT_EQ( "+9.868571429", r2.toString() ) ;
		EXPECT_EQ( "+1727/175",    q3.toString() ) ;
		EXPECT_EQ( "+9.868571429", r3.toString() ) ;
	}

	TEST_F( mixedQandRTest, pythagoras1 ) 
	{
		abm::R::setSignificantFigures( 10 ) ;
		abm::R::setDebug( false ) ;
		
		abm::Q a = 3 ;
		abm::Q b = 4 ;

		auto temp = a*a + b*b ;
		auto c    = temp.toR().sqrt().toQ() ; 

		//std::cout << "a = " << a      << std::endl ;
		//std::cout << "b = " << b       << std::endl ;
		//std::cout << "c = " << c       << std::endl ;
		//std::cout << "c = " << c.toR() << std::endl ;

		EXPECT_EQ( "+3",   a.toString() ) ;
		EXPECT_EQ( "+4",   b.toString() ) ;
		EXPECT_EQ( "+5",   c.toString() ) ;
		EXPECT_EQ( "+5.0", c.toR().toString() ) ;
	}

	TEST_F( mixedQandRTest, pythagoras2 ) 
	{
		abm::R::setSignificantFigures( 15 ) ;
		abm::R::setDebug( false ) ;
		
		auto a = abm::Q( 3, "1/100" ) ;
		auto b = abm::Q( 4, "1/100" ) ;

		auto temp = a*a + b*b ;
		auto c    = temp.toR().sqrt().toQ() ; 

		//std::cout << "a = " << a       << std::endl ;
		//std::cout << "b = " << b       << std::endl ;
		//std::cout << "c = " << c       << std::endl ;
		//std::cout << "c = " << c.toR() << std::endl ;

		EXPECT_EQ( "+301/100",                         a.toString() ) ;
		EXPECT_EQ( "+401/100",                         b.toString() ) ;
		EXPECT_EQ( "+501400039888311/100000000000000", c.toString() ) ;
		EXPECT_EQ( "+5.01400039888311",                c.toR().toString() ) ;
	}

} // ns

