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
	mpfr_t_wrapper::getObjectCount() // static   
	{
		return objectCount ;
	}

	unsigned long 
	mpfr_t_wrapper::calcPrecision2( unsigned long thePrecision10 ) // static
	{
		// the number of binary bits for x decimal places

		auto prec2 = (unsigned long) 
			::ceil( 
				::log2( 
					::pow( 10.0, thePrecision10 + extraPrecision10 ) ) )  ; // add some extra digits for rounding

		return prec2 ;
	}

////////////////////////////////
//ALBY fix me

	std::string 
	mpfr_t_wrapper::toString( bool detailed ) const
	{
		char format[100] ;
		std::sprintf( format, "%%+.%luRE", precision10 ) ; // alt is "%%+.%luRF"

//ALBY change to vector
		char buffer[ precision10 + 100 ] ;
		mpfr_snprintf( buffer, precision10 + 100 - 1 , format, x ) ; // add space for sign, decimal point, terminating zero, exponent

		std::string result ;
		numberhlp::toDecimal( buffer, result, precision10 ) ;

		if ( ! detailed ) return result ;

		return stringcat( result, " [prec ", precision10, "(10) ", precision2, "(2)]" ) ;
	}

	std::ostream& 
	operator<<( std::ostream& os, const mpfr_t_wrapper& rhs )  
	{  
		os << rhs.toString() ;  
		return os ;   
	}  

} // end ns
