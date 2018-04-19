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

#include "albybigmath/numberBase.h"
#include "albybigmath/stringhlp.h"
#include "albybigmath/stringcat.h"
#include "albybigmath/numberhlp.h"
#include "albybigmath/version.h"

namespace alby::bigmath 
{
    //const std::string version::_version = "0.0.0.0"  ; 
	#include "../../version.inc" 

	version::~version() // destr
	{
        // not implemented
	}

	version::version() // constr
	{
        // not implemented
	}

	version&
	version::operator=( const version& rhs ) // = 
	{
        // not implemented
		if ( this != &rhs )
		{
		}
		return *this ;
	}

	std::string 
	version::getVersion( bool detailed ) 
	{
		auto version = stringhlp::trim( _version ) ;

		if ( ! detailed ) return version ;
		
		return stringcat
		(
			"alby::bigmath version "  , version,			
			"\nGMP version           ", gmp_version,			
			"\nMPFR version          ", mpfr_get_version(),
			"\nMPFR_PREC_MAX         ", MPFR_PREC_MAX,
			"\nMPFR default prec     ", mpfr_get_default_prec() ,
			"\nMPFR min exponent     ", mpfr_get_emin(), 
			"\nMPFR max exponent     ", mpfr_get_emax(), 			
			"\nbits per limb         ", mp_bits_per_limb, 			
			"\nuname                 ", system( "uname -a" ) 
		) ;
	}

	std::string 
	version::system( const std::string& cmd )   
	{
		auto str = cmd + " 2>&1" ;

		std::string result ;

		auto f = ::popen( str.c_str(), "r" ) ;
    	if ( f ) 
		{
			char buffer[ 1000 ] ;

			while ( ! std::feof( f ) )
				if ( std::fgets( buffer, sizeof buffer - 1, f ) != nullptr ) 
					 result.append( buffer ) ;
		}
	    ::pclose( f ) ;

		result = stringhlp::trim( result ) ;
		return result ;
	}

} // ns

