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

	mpfr_t_wrapper::mpfr_t_wrapper( unsigned long theSigFig10 )
	{
		sigFig10 = theSigFig10 ;
		sigFig2  = calcSignificantFigures2( sigFig10 ) ;

		mpfr_init2 ( x, (mpfr_prec_t) sigFig2 ) ;                
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
	mpfr_t_wrapper::getSignificantFigures10() 
	{
		return sigFig10 ;
	}

	unsigned long 
	mpfr_t_wrapper::getSignificantFigures2()  
	{
		return sigFig2 ;
	}

	unsigned long 
	mpfr_t_wrapper::getObjectCount() 
	{
		return objectCount ;
	}

	unsigned long 
	mpfr_t_wrapper::calcSignificantFigures2( unsigned long theSigFig10 ) 
	{
		// the number of binary bits for x decimal places
		//
		// sig fig base 2 = log2( pow( 10, sig fig base 10 ) ) ;
		
		mpfr_t i ;

		mpfr_init2    ( i, 100 ) ;                
		mpfr_ui_pow_ui( i, 10, theSigFig10 + extraSigFig10, MPFR_RNDN ) ;
		mpfr_log2     ( i, i, MPFR_RNDN ) ;

		auto sf2 = mpfr_get_ui( i, MPFR_RNDN ) ;
		mpfr_clear( i ) ; 

		sf2++ ;
		return sf2 ;
	}

	std::string 
	mpfr_t_wrapper::toString( bool debug ) // return full decimal
	{
		static const unsigned long extraBytes = 100 ; // add space for sign, decimal point, terminating zero, exponent, etc

		char format[50] ;
		std::sprintf( format, "%%+.%luRE", sigFig10 ) ; // exponential format, alternative decimal format "%%+.%luRF"

		std::vector<char> buffer ;
		buffer.resize( sigFig10 + extraBytes + 2 ) ;
		std::fill( buffer.begin(), buffer.end(), 0 ) ;

		mpfr_snprintf( buffer.data(), sigFig10 + extraBytes, format, x ) ; 

		std::string result ;
		numberhlp::toDecimal( buffer.data(), result, sigFig10 ) ;

		if ( ! debug ) return result ;

		return stringcat( result, " [sf ", sigFig10, "(10), ", sigFig2, "(2), len ", result.length(), " ]" ) ;
	}

} // end ns
