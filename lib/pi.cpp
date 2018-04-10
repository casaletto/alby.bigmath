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

#include "./numberBase.h"
#include "./stringhlp.h"
#include "./stringcat.h"
#include "./numberhlp.h"
#include "./mpfr_t_wrapper.h"
#include "./R.h"
#include "./random.h"
#include "./pi.h"

namespace alby::bigmath 
{
	pi::~pi() // destr
	{
	}

	pi::pi() // constr
	{
	}

	pi::pi( const pi& rhs ) // copy constr
	{
        // not implemented
		*this = rhs ;
	}

	pi&
	pi::operator=( const pi& rhs ) // =
	{
        // not implemented
		if ( this != &rhs )
		{
		}
		return *this ;
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr 
	pi::nilakantha( unsigned long N ) 
	{
		mpfr pi ;

		auto plus = true ;

		for ( unsigned long n = 2 ; n <= N * 2 ; n += 2 )
		{
			auto term = nilakantha_term( n ) ; 

			pi = plus ? pi + term : pi - term ;

			plus = ! plus ;	 
		}

		pi += 3 ; 
			
		return pi ;
	}
	
	mpfr 
	pi::nilakantha_term( unsigned long n )
	{
		static mpfr _4 = 4 ;

		mpfr _n = n ;

		return _4 / ( _n * ( _n+1 ) * ( _n+2 ) ) ;
	}
	
	//----------------------------------------------------------------------------------------------------------------------

	mpfr 
	pi::ramanujan( unsigned long N ) 
	{
		auto factorial = mpfr::factorialMap( N * 6 ) ;

		mpfr pi ;

		auto plus = true ;

		for ( unsigned long n = 0 ; n <= N ; n++ )
		{
			auto term = ramanujan_term( n, factorial ) ; 

			pi = plus ? pi + term : pi - term ;

			plus = ! plus ;
		}

		pi *= 12 ;
		pi  = pi.inv() ;

		return pi ;
	}

	mpfr 
	pi::ramanujan_term( unsigned long n, std::map<unsigned long, mpfr>& factorial ) 
	{
		static mpfr _3   = 3      ;
		static mpfr _6   = 6      ;
		static mpfr _1_5 = "1.5"  ;

		static mpfr a = 13591409  ;
		static mpfr b = 545140134 ;
		static mpfr c = 640320    ;

		mpfr _n = n   ;
		mpfr num, den ;

		num  = factorial[ 6*n ]    ;
		num *= a + _n*b            ;

		den  = factorial[ n ] ^ _3 ;
		den *= factorial[ 3*n ]    ; 
		den *= c ^ ( _n*3 + _1_5 ) ;

		return num / den ;
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr 
	pi::nonic( unsigned long N ) 
	{
		nonic_term_t t0 ; 

		t0.a = mpfr(1) / 3 ;
		t0.r = ( mpfr(3).sqrt() - 1 ) / 2 ;

		t0.s  = 1 - ( t0.r ^ 3 ) ;
		t0.s ^= mpfr(1) / 3 ;

		auto prev = t0 ;
		auto t    = t0 ;

		for ( unsigned long n = 1 ; n <= N ; n++ )
		{
			t = nonic_term( n, prev ) ; 
			prev = t ;
		}

		return t.a.inv() ;
	}

	pi::nonic_term_t 
	pi::nonic_term( unsigned long n, nonic_term_t& prev ) // calculate term n
	{
		nonic_term_t t ; 
	
		t.t = 1 + 2 * prev.r ;
		
		t.u  = 9 * prev.r * ( 1 + prev.r + ( prev.r ^ 2 ) ) ;
		t.u ^= mpfr(1) / 3 ; 

		t.v = ( t.t ^ 2 ) + t.t * t.u + ( t.u ^ 2 ) ;

		t.w  = 1 + prev.s + ( prev.s ^ 2 ) ;
		t.w *= 27 / t.v ;

		t.a  = t.w * prev.a ;
		t.a += ( 3 ^ mpfr( 2 * (n-1) - 1 ) ) * ( 1 - t.w ) ;

		t.s  = ( 1 - prev.r ) ^ 3 ;
		t.s /= ( t.t + 2 * t.u ) * t.v ;

		t.r  = 1 - ( t.s ^ 3 ) ;
		t.r ^= mpfr(1) / 3 ; 
	
		return t ;
	}

} // ns
