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
#include "./mpfr.h"
 
namespace alby::bigmath 
{
	unsigned long mpfr::precision10global = mpfr::precision10default ;
	bool          mpfr::debug             = false                    ;

	//----------------------------------------------------------------------------------------------------------------------

	mpfr_t& 
	mpfr::deref( const mpfr& mpfr ) // dereference the important part
	{
		return *( mpfr.p->get() ) ;
	}	

	unsigned long 
	mpfr::getPrecisionLocal()
	{
		return precision10 ;	
	}

	unsigned long 
	mpfr::getPrecision()
	{
		return precision10global ;	
	}

	void 
	mpfr::setPrecision( unsigned long prec10 )
	{
		precision10global = prec10 ;	
	}

	bool 
	mpfr::getDebug()
	{
		return debug ;	
	}

	void 
	mpfr::setDebug( bool theDebug )
	{
		debug = theDebug ;	
	}

	//----------------------------------------------------------------------------------------------------------------------

	void 
	mpfr::init()
	{
		p = nullptr ;
	}

	void 
	mpfr::cleanup()
	{
		if ( p != nullptr )
			 delete p ;		
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr::~mpfr() // destr
	{
		cleanup() ;
	}

	mpfr::mpfr() // constr
	{
		init() ;

		precision10 = precision10global ;

		p = new mpfr_t_wrapper( precision10 ) ; // default 0
	}

	mpfr::mpfr( const mpfr& rhs ) // copy constr
	{
		init() ;

		*this = rhs ;
	}

	mpfr&
	mpfr::operator=( const mpfr& rhs ) // =
	{
		if ( this != &rhs )
		{
			cleanup() ;
			init()    ;

			precision10 = rhs.precision10 ;

			p = new mpfr_t_wrapper( precision10 ) ;

			mpfr_set( deref(*this), deref(rhs), roundingDefault ) ; 
		}
		return *this ;
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr::mpfr( const char* str ) // constr
	{
		init() ;

		precision10 = precision10global ;

		p = new mpfr_t_wrapper( precision10 ) ;

		std::string strScientificNotation ;
		bool ok = numberhlp::toScientificNotation( str, strScientificNotation, precision10 ) ;

		if ( ! ok ) throw std::invalid_argument( stringcat( "Bad number [", str, "]" ) ) ;

		mpfr_set_str( deref(*this), strScientificNotation.c_str(), 10, roundingDefault ) ; 
	}

	mpfr::mpfr( const char* str, int base ) // constr
	{
		init() ;

		precision10 = precision10global ;

		p = new mpfr_t_wrapper( precision10 ) ;

		if ( base != 10  )
		{
			mpfr_set_str( deref(*this), str, base, roundingDefault ) ; 
			return ;
		}

		std::string strScientificNotation ;
		bool ok = numberhlp::toScientificNotation( str, strScientificNotation, precision10 ) ;

		if ( ! ok ) throw std::invalid_argument( stringcat( "Bad number [", str, "]" ) ) ;

		mpfr_set_str( deref(*this), strScientificNotation.c_str(), base, roundingDefault ) ; 
	}

	mpfr::mpfr( const char* str, int base, unsigned long thePrecision10 ) // constr
	{
		init() ;

		precision10 = thePrecision10 ;

		p = new mpfr_t_wrapper( precision10 ) ;

		if ( base != 10 )
		{
			mpfr_set_str( deref(*this), str, base, roundingDefault ) ; 
			return ;
		}

		std::string strScientificNotation ;
		bool ok = numberhlp::toScientificNotation( str, strScientificNotation, precision10 ) ;

		if ( ! ok ) throw std::invalid_argument( stringcat( "Bad number [", str, "]" ) ) ;

		mpfr_set_str( deref(*this), strScientificNotation.c_str(), base, roundingDefault ) ; 
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr::mpfr( const std::string& str ) // constr
	{
		init() ;

		precision10 = precision10global ;

		p = new mpfr_t_wrapper( precision10 ) ;

		std::string strScientificNotation ;
		bool ok = numberhlp::toScientificNotation( str, strScientificNotation, precision10 ) ;

		if ( ! ok ) throw std::invalid_argument( stringcat( "Bad number [", str, "]" ) ) ;

		mpfr_set_str( deref(*this), strScientificNotation.c_str(), 10, roundingDefault ) ; 	
	}

	mpfr::mpfr( const std::string& str, int base ) // constr
	{
		init() ;

		precision10 = precision10global ;

		p = new mpfr_t_wrapper( precision10 ) ;

		if ( base != 10  )
		{
			mpfr_set_str( deref(*this), str.c_str(), base, roundingDefault ) ; 
			return ;
		}
	
		std::string strScientificNotation ;
		bool ok = numberhlp::toScientificNotation( str, strScientificNotation, precision10 ) ;

		if ( ! ok ) throw std::invalid_argument( stringcat( "Bad number [", str, "]" ) ) ;

		mpfr_set_str( deref(*this), strScientificNotation.c_str(), base, roundingDefault ) ; 	
	}

	mpfr::mpfr( const std::string& str, int base, unsigned long thePrecision10 ) // constr
	{
		init() ;

		precision10 = thePrecision10 ;

		p = new mpfr_t_wrapper( precision10 ) ;

		if ( base != 10  )
		{
			mpfr_set_str( deref(*this), str.c_str(), base, roundingDefault ) ; 
			return ;
		}

		std::string strScientificNotation ;
		bool ok = numberhlp::toScientificNotation( str, strScientificNotation, precision10 ) ;

		if ( ! ok ) throw std::invalid_argument( stringcat( "Bad number [", str, "]" ) ) ;

		mpfr_set_str( deref(*this), strScientificNotation.c_str(), base, roundingDefault ) ; 	
	}

	//----------------------------------------------------------------------------------------------------------------------

	std::ostream& 
	operator<<( std::ostream& os, const mpfr& mpfr1 )  
	{  
		os << const_cast<mpfr*>( &mpfr1 )->toString() ;

		return os ;   
	}  

	mpfr::operator 
	std::string() 
    {
        return toString() ;
    }

	mpfr::operator 
	std::string() const
    {
		return const_cast<mpfr*>(this)->toDecimal( false )  ;
    }

	std::string 
	mpfr::toString() // return minumal decimal string
	{
		if ( debug )
			 return p->toString( debug ) ;  

		return toDecimal( false ) ;	 
	}

	//----------------------------------------------------------------------------------------------------------------------

	std::string 
	mpfr::toDecimal( bool fullPrecision ) // default true, false means remove trailing zeros
	{
		std::string result ;

		auto str = p->toString() ;

		if ( fullPrecision )
			 numberhlp::toDecimal( str, result, precision10 ) ;
		else
			 numberhlp::toDecimal( str, result ) ;

		return result ;
	}

	std::string 
	mpfr::toScientificNotation( bool fullPrecision ) // default true, false means remove trailing zeros
	{
		std::string result ;

		auto str = p->toString() ;

		if ( fullPrecision )
			 numberhlp::toScientificNotation( str, result, precision10 ) ;
		else
			 numberhlp::toScientificNotation( str, result ) ;

		return result ;
	}

	//----------------------------------------------------------------------------------------------------------------------
	mpfr 
	operator+( const mpfr& op1, const mpfr& op2 )  
	{  
		// same precision
		if ( op1.precision10 == op2.precision10 )
		{
			mpfr result( "0", 10, op1.precision10 ) ;

			mpfr_add( mpfr::deref(result), mpfr::deref(op1), mpfr::deref(op2), mpfr::roundingDefault ) ;			

			return result ;   
		}

		// different precision, use max precision
		auto maxprec = std::max( op1.precision10, op2.precision10 ) ;

		mpfr result( "0", 10, maxprec ) ;

		mpfr opA( op1, 10, maxprec ) ; 
		mpfr opB( op2, 10, maxprec ) ;

		mpfr_add( mpfr::deref(result), mpfr::deref(opA), mpfr::deref(opB), mpfr::roundingDefault ) ;
	
		return result ;   
	}  

	mpfr& 
	mpfr::operator+=( const mpfr& op2 )  
	{  
		mpfr_add( mpfr::deref(*this), mpfr::deref(*this), mpfr::deref(op2), roundingDefault ) ;

		return *this ;   
	}

	mpfr 
	operator-( const mpfr& op1, const mpfr& op2 )  
	{  
		mpfr result( op1 ) ; 
		
		mpfr_sub( mpfr::deref(result), mpfr::deref(op1), mpfr::deref(op2), mpfr::roundingDefault ) ;

		return result ;   
	}  

	mpfr& 
	mpfr::operator-=( const mpfr& op2 )  
	{  
		mpfr_sub( mpfr::deref(*this), mpfr::deref(*this), mpfr::deref(op2), roundingDefault ) ;

		return *this ;   
	}  

	mpfr 
	operator*( const mpfr& op1, const mpfr& op2 )  
	{  
		mpfr result( op1 ) ; 
		
		mpfr_mul( mpfr::deref(result), mpfr::deref(op1), mpfr::deref(op2), mpfr::roundingDefault ) ;

		return result ;   
	}  

	mpfr& 
	mpfr::operator*=( const mpfr& op2 )  
	{  
		mpfr_mul( mpfr::deref(*this), mpfr::deref(*this), mpfr::deref(op2), roundingDefault ) ;

		return *this ;   
	}  

	mpfr 
	operator/( const mpfr& op1, const mpfr& op2 )  
	{  
		mpfr result( op1 ) ; 
		
		mpfr_div( mpfr::deref(result), mpfr::deref(op1), mpfr::deref(op2), mpfr::roundingDefault ) ;

		return result ;   
	}  

	mpfr& 
	mpfr::operator/=( const mpfr& op2 )  
	{  
		mpfr_div( mpfr::deref(*this), mpfr::deref(*this), mpfr::deref(op2), roundingDefault ) ;

		return *this ;   
	}  

	mpfr 
	operator^( const mpfr& op1, const mpfr& op2 )  
	{  
		mpfr result( op1 ) ;
		
		mpfr_pow( mpfr::deref(result), mpfr::deref(op1), mpfr::deref(op2), mpfr::roundingDefault ) ;

		return result ;   
	}  

	mpfr& 
	mpfr::operator^=( const mpfr& op2 )  
	{  
		mpfr_pow( mpfr::deref(*this), mpfr::deref(*this), mpfr::deref(op2), roundingDefault ) ;

		return *this ;   
	}  

	//----------------------------------------------------------------------------------------------------------------------

	bool 
	operator>( const mpfr& op1, const mpfr& op2 )  
	{  
		//ALBY fix me

		return true ;
	}

	bool 
	operator<( const mpfr& op1, const mpfr& op2 )  
	{  
		//ALBY fix me

		return true ;
	}

	bool 
	operator>=( const mpfr& op1, const mpfr& op2 )  
	{  
		//ALBY fix me

		return true ;
	}

	bool 
	operator<=( const mpfr& op1, const mpfr& op2 )  
	{  
		//ALBY fix me

		return true ;
	}

	bool 
	operator==( const mpfr& op1, const mpfr& op2 )  
	{  
		//ALBY fix me

		return true ;
	}

	bool 
	operator!=( const mpfr& op1, const mpfr& op2 )  
	{  
		//ALBY fix me

		return true ;
	}
	
	//----------------------------------------------------------------------------------------------------------------------

	mpfr 
	mpfr::sin()  
	{
		mpfr result( *this ) ; 

		mpfr_sin( deref(result), deref(*this), roundingDefault ) ;

		return result ;   
	}

	mpfr 
	mpfr::cos()  
	{
		mpfr result( *this ) ; 

		mpfr_cos( deref(result), deref(*this), roundingDefault ) ;

		return result ;   
	}

	mpfr 
	mpfr::tan()  
	{
		mpfr result( *this ) ; 

		mpfr_tan( deref(result), deref(*this), roundingDefault ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr 
	mpfr::pi()  
	{
		mpfr result( *this ) ; 

		mpfr_const_pi( deref(result), roundingDefault ) ;

		return result ;   
	}

	mpfr 
	mpfr::e()  
	{
		mpfr result( *this ) ; 

		mpfr one( "1", 10, precision10 ) ; 

		mpfr_exp( deref(result), deref(one), roundingDefault ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr 
	mpfr::neg()  
	{ 
		mpfr minusone( "-1", 10, precision10 ) ; 

		return *this * minusone ;  
	}

	mpfr 
	mpfr::inv()  
	{ 
		mpfr one( "1", 10, precision10 ) ; 

		return one / *this ;   
	}

	mpfr 
	mpfr::abs()  
	{ 
		mpfr result( *this ) ; 

		mpfr_abs( deref(result), deref(*this), roundingDefault ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr 
	mpfr::exp() 
	{
		mpfr result( *this ) ; 

		mpfr_exp( deref(result), deref(*this), roundingDefault ) ;

		return result ;   
	}

	mpfr 
	mpfr::log() 
	{
		mpfr result( *this ) ; 

		mpfr_log( deref(result), deref(*this), roundingDefault ) ;

		return result ;   
	}

	mpfr 
	mpfr::log2() 
	{
		mpfr result( *this ) ; 

		mpfr_log2( deref(result), deref(*this), roundingDefault ) ;

		return result ;   
	}

	mpfr 
	mpfr::log10() 
	{
		mpfr result( *this ) ; 

		mpfr_log10( deref(result), deref(*this), roundingDefault ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr 
	mpfr::pow2() // 2 ^ this
	{
		mpfr result( *this ) ; 

		mpfr two( "2", 10, precision10 ) ; 

		mpfr_pow( deref(result), deref(two), deref(*this), roundingDefault ) ;

		return result ;   
	}

	mpfr 
	mpfr::pow10() // 10 ^ this
	{
		mpfr result( *this ) ; 

		mpfr ten( "10", 10, precision10 ) ; 

		mpfr_pow( deref(result), deref(ten), deref(*this), roundingDefault ) ;

		return result ;   
	}

	mpfr 
	mpfr::root( const mpfr& op1 ) // the op1-th root of this
	{
		mpfr result( *this ) ; 

		mpfr one( "1", 10, precision10 ) ; 

		mpfr index = one / op1 ;

		mpfr_pow( deref(result), deref(*this), deref(index), roundingDefault ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr 
	mpfr::sqrt() // square root
	{
		mpfr two( "2", 10, precision10 ) ; 

		return root( two ) ;
	}
		
	mpfr 
	mpfr::fact() // factorial n!
	{
		mpfr result( *this ) ; 

		auto n = mpfr_get_ui( deref( floor() ), roundingDefault ) ;

 		mpfr_fac_ui( deref(result), n, roundingDefault ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr 
	mpfr::ceil() 
	{
		mpfr result( *this ) ; 

		mpfr_ceil( deref(result), deref(*this) ) ;

		return result ;   
	}

	mpfr 
	mpfr::floor() 
	{
		mpfr result( *this ) ; 

		mpfr_floor( deref(result), deref(*this) ) ;

		return result ;   
	}

	mpfr 
	mpfr::trunc() 
	{
		mpfr result( *this ) ; 

		mpfr_trunc( deref(result), deref(*this) ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr 
	mpfr::roundDecimalPlaces( unsigned long dp ) // return number rounded to x decimal places
	{
		return mpfr() ; //ALBY to do
	}

	mpfr 
	mpfr::roundSignificantFigures( unsigned long sf ) // return number rounded to x significant figures
	{
		return mpfr() ; //ALBY to do
	}

	//----------------------------------------------------------------------------------------------------------------------

	std::string 
	mpfr::version() 
	{
		return stringcat
		(
			"MPFR library  ",
			mpfr_get_version(),
			"\nMPFR header   ", 
			MPFR_VERSION_STRING,                      
			" (based on ",
			MPFR_VERSION_MAJOR,
			".",
			MPFR_VERSION_MINOR,
			".",
			MPFR_VERSION_PATCHLEVEL,
			")",
			"\nMPFR_PREC_MAX ",
			MPFR_PREC_MAX,
			"\ndefault prec  ",
			mpfr_get_default_prec() ,
			"\nmin exponent  ",
			mpfr_get_emin(), 
			"\nmax exponent  ",
			mpfr_get_emax() 			
		) ;
	}

	std::string 
	mpfr::randomBytes( int bytes ) // hex string of random bytes
	{
		std::vector<char> buffer ;
		buffer.resize( bytes ) ;
		std::fill( buffer.begin(), buffer.end(), 0 ) ;

		auto f = "/dev/urandom" ;
		std::ifstream mystream( f, std::ios::in | std::ios_base::binary ) ;

		mystream.seekg( 0, std::ios_base::beg ) ;
		mystream.read ( buffer.data(), bytes ) ;

		std::string str ;

		for ( auto c : buffer )
			str += stringhlp::printf( 100, "%02X", (unsigned int) (unsigned char) c ) 	;

		return str ;
	}

} // end ns

