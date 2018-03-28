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
  
#include <gmp.h>
#include <mpfr.h>

#include "./numberBase.h"
#include "./stringhlp.h"
#include "./stringcat.h"
#include "./numberhlp.h"
#include "./mpfr_t_wrapper.h"
#include "./mpfr.h"
#include "./random.h"

namespace alby::bigmath 
{
    const std::string   random::devUrandomFile = "/dev/urandom" ; 
    const unsigned long random::seedBytes      = 128 ; 
    
	random::~random() // destr
	{
        gmp_randclear( state ) ;
        mpz_clear( seed ) ;
	}

	random::random() // constr
	{
        mpz_init( seed ) ;

        // try to get the seed from ransom, otherwise use the tick count
       	theSeed = hexBytes( seedBytes ) ;            
        if ( theSeed.length() == 0 )
             theSeed = nanosecondsSinceEpoch() ;

        mpz_init_set_str( seed, theSeed.c_str(), 16 ) ; // treat as hex number

        gmp_randinit_default( state ) ;
        gmp_randseed( state, seed ) ;
	}

	random::random( const std::string& aSeed, numberBase theBase )  
    {
        theSeed = aSeed ;

        mpz_init( seed ) ;
        mpz_init_set_str( seed, theSeed.c_str(), (int) theBase ) ;  

        gmp_randinit_default( state ) ;
        gmp_randseed( state, seed ) ;
    }

	random::random( const random& rhs ) // copy constr
	{
		*this = rhs ;
	}

	random&
	random::operator=( const random& rhs ) // =
	{
		if ( this != &rhs )
		{
		}
		return *this ;
	}

    std::string random::getSeed()
    {
        return theSeed ;
    }

    mpfr 
    random::next() // next float [0.0, 1)
    {
        return next( mpfr::getSignificantFigures() ) ;
    }

    mpfr 
    random::next( unsigned long significantDigits )
    {
        mpfr num( "0", significantDigits ) ;

        mpfr_urandomb( mpfr::deref( num ), state ) ;

        return num ;
    }

	std::string 
	random::hexBytes( int bytes ) // hex string of random bytes from /dev/urandom
	{
		std::vector<char> buffer ;
		buffer.resize( bytes ) ;
		std::fill( buffer.begin(), buffer.end(), 0 ) ;

		std::ifstream mystream( devUrandomFile, std::ios::in | std::ios_base::binary ) ;
        if ( ! mystream ) return "" ; // must be on windoze

		mystream.seekg( 0, std::ios_base::beg ) ;
		mystream.read ( buffer.data(), bytes ) ;

		std::string str ;
		for ( auto c : buffer )
			  str += stringhlp::printf( 100, "%02X", (unsigned int) (unsigned char) c ) 	;

		return str ;
	}

    std::string 
    random::nanosecondsSinceEpoch() // nano seconds since c++ time began 
    {
        auto duration = std::chrono::high_resolution_clock::now().time_since_epoch() ;

        auto nanoseconds = std::chrono::duration_cast< std::chrono::nanoseconds >( duration ).count() ;

        auto str = stringcat( nanoseconds ) ;

        return str ;
    }



} // ns