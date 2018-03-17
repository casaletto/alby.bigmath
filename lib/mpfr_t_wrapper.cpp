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

#include <gmp.h>
#include <mpfr.h>

#include "./stringhlp.h"
#include "./stringcat.h"
#include "./numberhlp.h"
#include "./mpfr_t_wrapper.h"

namespace alby::bigmath 
{
	unsigned long mpfr_t_wrapper::objectCount = 0 ;

	mpfr_t_wrapper::~mpfr_t_wrapper()
	{
		mpfr_clear( x ) ; 

		objectCount-- ;
		//std::cout << "mpfr_t_wrapper destr " << *this << std::endl ;
	}

	mpfr_t_wrapper::mpfr_t_wrapper( unsigned long thePrecision10 )
	{
		precision10 = thePrecision10 ;
		precision2  = calcPrecision2( precision10 ) ;

		mpfr_init2 ( x, (mpfr_prec_t) precision2 ) ;                
		mpfr_set_ui( x, 0, MPFR_RNDN ) ; 

		objectCount++ ;
		//std::cout << "mpfr_t_wrapper constr " << *this << std::endl ; 
	}

	mpfr_t* 
	mpfr_t_wrapper::get()
	{
		return &x ;
	}

	unsigned long 
	mpfr_t_wrapper::getPrecision10() 
	{
		return precision10 ;
	}

	unsigned long 
	mpfr_t_wrapper::getPrecision2()  
	{
		return precision2 ;
	}

	unsigned long 
	mpfr_t_wrapper::getObjectCount() 
	{
		return objectCount ;
	}

	unsigned long 
	mpfr_t_wrapper::calcPrecision2( unsigned long thePrecision10 ) 
	{
		// the number of binary bits for x decimal places
		//
		// precision2 = log2( pow( 10, precision10 ) ) ;
		//

		mpfr_t prec ;
		mpfr_init2    ( prec, 100 ) ;                
		mpfr_ui_pow_ui( prec, 10, thePrecision10 + extraPrecision10, MPFR_RNDN ) ;
		mpfr_log2     ( prec, prec, MPFR_RNDN ) ;

		unsigned long prec2 = mpfr_get_ui( prec, MPFR_RNDN ) ;
		mpfr_clear( prec ) ; 

		return prec2++ ;
	}

	std::string 
	mpfr_t_wrapper::toString( bool debug ) // return full decimal
	{
		static const unsigned long extraBytes = 100 ; // add space for sign, decimal point, terminating zero, exponent, etc

		char format[50] ;
		std::sprintf( format, "%%+.%luRE", precision10 ) ; // exponential format, alternative decimal format "%%+.%luRF"

		std::vector<char> buffer ;
		buffer.resize( precision10 + extraBytes + 2 ) ;
		std::fill( buffer.begin(), buffer.end(), 0 ) ;

		mpfr_snprintf( buffer.data(), precision10 + extraBytes, format, x ) ; 

		std::string result ;
		numberhlp::toDecimal( buffer.data(), result, precision10 ) ;

		if ( ! debug ) return result ;

		return stringcat( result, " [prec ", precision10, "(10), ", precision2, "(2), len ", result.length(), " ]" ) ;
	}

} // end ns
