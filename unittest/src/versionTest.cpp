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
	class versionTest : public testing::Test 
	{
		protected:
			static void SetUpTestCase() 
			{
				std::cout << "VersionTest::SetUpTestCase()" << std::endl ;
			}

			static void TearDownTestCase() 
			{
				std::cout << "VersionTest::TearDownTestCase()" << std::endl ;
			}

			virtual void SetUp() 
			{ 
				testing::Test::SetUp() ;
				std::cout << "VersionTest::SetUp()" << std::endl ;
			}

			virtual void TearDown() 
			{ 
				std::cout << "VersionTest::TearDown()" << std::endl ;
				testing::Test::TearDown() ;              
			}

			void hello()
			{				
				std::cout << "VersionTest::hello()" << std::endl ;
			}
	} ;

	TEST_F( versionTest, simple ) 
	{
		auto str = abm::version::getVersion()  ;		

		EXPECT_GT( str.length(), 0 ) ;

		EXPECT_FALSE( abm::stringhlp::contains( str, "version" ) ) ;

	}

	TEST_F( versionTest, detailed ) 
	{
		auto str = abm::version::getVersion( true )  ;		

		EXPECT_GT( str.length(), 0 ) ;

		EXPECT_TRUE( abm::stringhlp::contains( str, "version" ) ) ;
	}

	TEST_F( versionTest, hello ) 
	{
		hello() ;
		environment::get()->hello() ;
	}

} // ns

