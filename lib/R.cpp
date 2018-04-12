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
#include "./mpq_t_wrapper.h"
#include "./Q.h"
#include "./mpfr_t_wrapper.h"
#include "./R.h"
 
namespace alby::bigmath 
{
	unsigned long R::sigFig10global = R::sigFig10default ;
	bool          R::debug          = false              ;

	//----------------------------------------------------------------------------------------------------------------------

	mpfr_t& 
	R::deref( const R& r ) // dereference the important part
	{
		return *( r.p->get() ) ;
	}	

	unsigned long 
	R::getSignificantFiguresLocal()
	{
		return sigFig10 ;	
	}

	unsigned long 
	R::getSignificantFigures()
	{
		return sigFig10global ;	
	}

	void 
	R::setSignificantFigures( unsigned long theSigFig10 )
	{
		sigFig10global = theSigFig10 ;	
	}

	bool 
	R::getDebug()
	{
		return debug ;	
	}

	void 
	R::setDebug( bool theDebug )
	{
		debug = theDebug ;	
	}

	//----------------------------------------------------------------------------------------------------------------------

	void 
	R::init()
	{
		p = nullptr ;
	}

	void 
	R::cleanup()
	{
		if ( p != nullptr )
			 delete p ;		
	}

	//----------------------------------------------------------------------------------------------------------------------

	R::~R() // destr
	{
		cleanup() ;
	}

	R::R() // constr
	{
		init() ;

		sigFig10 = sigFig10global ;

		p = new mpfr_t_wrapper( sigFig10 ) ; // default 0
	}

	R::R( const R& rhs ) // copy constr
	{
		init() ;

		*this = rhs ;
	}

	R::R( const R& rhs, unsigned long theSigFig10 ) // constr
	{
		init() ;

		sigFig10 = theSigFig10 ;

		p = new mpfr_t_wrapper( sigFig10 ) ;

		mpfr_set( deref(*this), deref(rhs), roundingDefault ) ; 
	}

	R&
	R::operator=( const R& rhs ) // =
	{
		if ( this != &rhs )
		{
			cleanup() ;
			init()    ;

			sigFig10 = rhs.sigFig10 ;

			p = new mpfr_t_wrapper( sigFig10 ) ;

			mpfr_set( deref(*this), deref(rhs), roundingDefault ) ; 
		}
		return *this ;
	}

	R::R( long l ) // constr
	{
		init() ;

		sigFig10 = sigFig10global ;

		p = new mpfr_t_wrapper( sigFig10 ) ;

		auto str = std::to_string( l ) ;

		mpfr_set_str( deref(*this), str.c_str(), 10, roundingDefault ) ; 
	}

	//----------------------------------------------------------------------------------------------------------------------

	R::R( const char* str ) // constr
	{
		init() ;

		sigFig10 = sigFig10global ;

		p = new mpfr_t_wrapper( sigFig10 ) ;

		std::string strScientificNotation ;
		auto ok = numberhlp::toScientificNotation( str, strScientificNotation, sigFig10 ) ;

		if ( ! ok ) throw std::invalid_argument( stringcat( "Bad number [", str, "]" ) ) ;

		mpfr_set_str( deref(*this), strScientificNotation.c_str(), 10, roundingDefault ) ; 
	}

	R::R( const char* str, unsigned long theSigFig10, numberBase base ) // constr
	{
		init() ;

		sigFig10 = theSigFig10 ;

		p = new mpfr_t_wrapper( sigFig10 ) ;

		if ( base != numberBase::_10 )
		{
			mpfr_set_str( deref(*this), str, (int) base, roundingDefault ) ; 
			return ;
		}

		std::string strScientificNotation ;
		auto ok = numberhlp::toScientificNotation( str, strScientificNotation, sigFig10 ) ;

		if ( ! ok ) throw std::invalid_argument( stringcat( "Bad number [", str, "]" ) ) ;

		mpfr_set_str( deref(*this), strScientificNotation.c_str(), (int) base, roundingDefault ) ; 
	}

	//----------------------------------------------------------------------------------------------------------------------

	R::R( const std::string& str ) // constr
	{
		init() ;

		sigFig10 = sigFig10global ;

		p = new mpfr_t_wrapper( sigFig10 ) ;

		std::string strScientificNotation ;
		auto ok = numberhlp::toScientificNotation( str, strScientificNotation, sigFig10 ) ;

		if ( ! ok ) throw std::invalid_argument( stringcat( "Bad number [", str, "]" ) ) ;

		mpfr_set_str( deref(*this), strScientificNotation.c_str(), 10, roundingDefault ) ; 	
	}

	R::R( const std::string& str, unsigned long theSigFig10, numberBase base ) // constr
	{
		init() ;

		sigFig10 = theSigFig10 ;

		p = new mpfr_t_wrapper( sigFig10 ) ;

		if ( base != numberBase::_10 )
		{
			mpfr_set_str( deref(*this), str.c_str(), (int) base, roundingDefault ) ; 
			return ;
		}

		std::string strScientificNotation ;
		auto ok = numberhlp::toScientificNotation( str, strScientificNotation, sigFig10 ) ;

		if ( ! ok ) throw std::invalid_argument( stringcat( "Bad number [", str, "]" ) ) ;

		mpfr_set_str( deref(*this), strScientificNotation.c_str(), (int) base, roundingDefault ) ; 	
	}

	//----------------------------------------------------------------------------------------------------------------------

	R::R( const Q& rhs ) // explicit constructor
	{
		init() ;

		sigFig10 = sigFig10global ;

		p = new mpfr_t_wrapper( sigFig10 ) ;

		std::string str = rhs ;

		std::string numerator, denominator, sign ;

		auto ok = numberhlp::splitRational( str, numerator, denominator, sign ) ;

		if ( ! ok ) throw std::invalid_argument( stringcat( "Bad number [", str, "]" ) ) ;

		*this = R( sign + numerator ) / R( denominator ) ;
	}

	R::R( const Q& rhs, unsigned long theSigFig10 ) // explicit constructor
	{
		init() ;

		sigFig10 = theSigFig10 ;

		p = new mpfr_t_wrapper( sigFig10 ) ;

		std::string str = rhs ;

		std::string numerator, denominator, sign ;

		auto ok = numberhlp::splitRational( str, numerator, denominator, sign ) ;

		if ( ! ok ) throw std::invalid_argument( stringcat( "Bad number [", str, "]" ) ) ;

		*this = R( sign + numerator ) / R( denominator ) ;
	}

	//----------------------------------------------------------------------------------------------------------------------

	std::ostream& 
	operator<<( std::ostream& os, const R& rhs )  
	{  
		os << const_cast<R*>( &rhs )->toString() ;

		return os ;   
	}  

	R::operator 
	std::string() 
    {
        return toString() ;
    }

	R::operator 
	std::string() const
    {
		return const_cast<R*>( this )->toDecimal( false )  ;
    }

	std::string 
	R::toString() // return minumal decimal string
	{
		if ( debug )
			 return p->toString( debug ) ;  

		return toDecimal( false ) ;	 
	}

	//----------------------------------------------------------------------------------------------------------------------

	std::string 
	R::toDecimal( bool allSigFig ) // default false, false means remove trailing zeros
	{
		std::string result ;

		auto str = p->toString() ;

		if ( allSigFig )
			 numberhlp::toDecimal( str, result, sigFig10 ) ;
		else
			 numberhlp::toDecimal( str, result ) ;

		return result ;
	}

	std::string 
	R::toScientificNotation( bool allSigFig ) // default false, false means remove trailing zeros
	{
		std::string result ;

		auto str = p->toString() ;

		if ( allSigFig )
			 numberhlp::toScientificNotation( str, result, sigFig10 ) ;
		else
			 numberhlp::toScientificNotation( str, result ) ;

		return result ;
	}

	std::string 
	R::toSignificantFigures( unsigned long theSigFig10 ) 
	{
		auto t = roundToSignificantFigures( theSigFig10 ) ;

		auto str = t.toScientificNotation() ;

		std::string strResult ;
		auto ok = numberhlp::scientificNotationExtend( str, strResult, theSigFig10 ) ;

		if ( ! ok ) throw std::invalid_argument( stringcat( "Bad number [", str, "]" ) ) ;

		return strResult ;
	}

	R 
	R::roundToSignificantFigures( unsigned long theSigFig10 ) 
	{
		auto str = p->toString() ;

		std::string strResult ;
		auto ok = numberhlp::toScientificNotation( str, strResult, theSigFig10 ) ;

		if ( ! ok ) throw std::invalid_argument( stringcat( "Bad number [", str, "]" ) ) ;

		auto result = R( strResult, sigFig10 ) ;

		return result ;
	}

	std::string 
	R::toDecimalPlaces( unsigned long theDecimalPlaces ) 
	{
		auto str = p->toString() ;

		std::string strResult ;
		auto ok = numberhlp::decimalPlacesExtend( str, strResult, theDecimalPlaces ) ;

		if ( ! ok ) throw std::invalid_argument( stringcat( "Bad number [", str, "]" ) ) ;

		return strResult ;
	}

	R 
	R::roundToDecimalPlaces( unsigned long theDecimalPlaces ) 
	{
		auto str = toDecimalPlaces( theDecimalPlaces ) ;

		R result( str, sigFig10 ) ;

		return result ;
	}

	std::string 
	R::toFraction( bool reduce ) 
	{
		// return gmp compatibile fraction as string

		std::string numerator   ;
		std::string denominator ;

		return toFraction( numerator, denominator, reduce ) ;
	}	

	std::string 
	R::toFraction( std::string& numerator, std::string& denominator, bool bReduce ) 
	{
		// return gmp compatibile fraction as string

		auto str = toDecimal() ;

		auto ok = numberhlp::toNumeratorDenominator( str, numerator, denominator ) ;

		if ( ! ok ) throw std::invalid_argument( stringcat( "Bad number [", str, "]" ) ) ;

		auto rational = numerator + "/" + stringhlp::substr( denominator, 1 ) ;

		if ( ! bReduce ) return rational ;

		if ( stringhlp::startsWith( rational, "+" ) )
			 rational = stringhlp::substr( rational, 1 ) ;

		return reduce( rational ) ; 
	}			

	Q 
	R::toQ()
	{
		return Q( *this ) ;
	}

	//----------------------------------------------------------------------------------------------------------------------
 
	std::string 
	R::reduce( const std::string& rational )
	{
		// initialise mpq rational
		mpq_t r ;
		mpq_init( r ) ;

		// set the value from a xxx/yyyy string
		mpq_set_str( r, rational.c_str(), 10 ) ;

		// do the actual reduction
 		mpq_canonicalize( r ) ;

		// read the reduced value
		auto p = mpq_get_str( nullptr, 10, r ) ;
		std::string result = p ;

		// free memory
		void (*free)( void *, size_t ) ;
		mp_get_memory_functions( nullptr, nullptr, &free ) ;
		free( p, std::strlen( p ) + 1 ) ;

		mpq_clear( r ) ;

		auto sign = stringhlp::left( result, 1 ) ;

		if ( sign != "-" ) 
		     result = "+" + result ;

		return result ;
	}

	//----------------------------------------------------------------------------------------------------------------------

	R 
	operator+( const R& op1, const R& op2 )  
	{ 
		auto maxsf = std::max( op1.sigFig10, op2.sigFig10 ) ;

		R result( "0", maxsf ) ;

		mpfr_add( 
			R::deref( result ), 
			R::deref( op1.sigFig10 == maxsf ? op1 : R( op1, maxsf ) ),
			R::deref( op2.sigFig10 == maxsf ? op2 : R( op2, maxsf ) ), 
			R::roundingDefault ) ;

		return result ;   
	}  

	R& 
	R::operator+=( const R& op2 )  
	{  
		auto maxsf = std::max( sigFig10, op2.sigFig10 ) ;

		R result( "0", maxsf ) ;

		mpfr_add( 
			R::deref( result ), 
			R::deref( sigFig10     == maxsf ? *this : R( *this, maxsf ) ),
			R::deref( op2.sigFig10 == maxsf ? op2   : R( op2,   maxsf ) ), 
			R::roundingDefault ) ;

		*this = result ;
		return *this ;   
	}

	R 
	operator-( const R& op1, const R& op2 )  
	{  
		auto maxsf = std::max( op1.sigFig10, op2.sigFig10 ) ;

		R result( "0", maxsf ) ;

		mpfr_sub( 
			R::deref( result ), 
			R::deref( op1.sigFig10 == maxsf ? op1 : R( op1, maxsf ) ),
			R::deref( op2.sigFig10 == maxsf ? op2 : R( op2, maxsf ) ), 
			R::roundingDefault ) ;

		return result ;   
	}  

	R& 
	R::operator-=( const R& op2 )  
	{  
		auto maxsf = std::max( sigFig10, op2.sigFig10 ) ;

		R result( "0", maxsf ) ;

		mpfr_sub( 
			R::deref( result ), 
			R::deref( sigFig10     == maxsf ? *this : R( *this, maxsf ) ),
			R::deref( op2.sigFig10 == maxsf ? op2   : R( op2,   maxsf ) ), 
			R::roundingDefault ) ;

		*this = result ;
		return *this ;   	
	}  

	R 
	operator*( const R& op1, const R& op2 )  
	{ 
		auto maxsf = std::max( op1.sigFig10, op2.sigFig10 ) ;

		R result( "0", maxsf ) ;

		mpfr_mul( 
			R::deref( result ), 
			R::deref( op1.sigFig10 == maxsf ? op1 : R( op1, maxsf ) ),
			R::deref( op2.sigFig10 == maxsf ? op2 : R( op2, maxsf ) ), 
			R::roundingDefault ) ;

		return result ;   
	}  

	R& 
	R::operator*=( const R& op2 )  
	{  
		auto maxsf = std::max( sigFig10, op2.sigFig10 ) ;

		R result( "0", maxsf ) ;

		mpfr_mul( 
			R::deref( result ), 
			R::deref( sigFig10     == maxsf ? *this : R( *this, maxsf ) ),
			R::deref( op2.sigFig10 == maxsf ? op2   : R( op2,   maxsf ) ), 
			R::roundingDefault ) ;

		*this = result ;
		return *this ;   	
	}  

	R 
	operator/( const R& op1, const R& op2 )  
	{  
		auto maxsf = std::max( op1.sigFig10, op2.sigFig10 ) ;

		R result( "0", maxsf ) ;

		mpfr_div( 
			R::deref( result ), 
			R::deref( op1.sigFig10 == maxsf ? op1 : R( op1, maxsf ) ),
			R::deref( op2.sigFig10 == maxsf ? op2 : R( op2, maxsf ) ), 
			R::roundingDefault ) ;

		return result ;   
	}  

	R& 
	R::operator/=( const R& op2 )  
	{  
		auto maxsf = std::max( sigFig10, op2.sigFig10 ) ;

		R result( "0", maxsf ) ;

		mpfr_div( 
			R::deref( result ), 
			R::deref( sigFig10     == maxsf ? *this : R( *this, maxsf ) ),
			R::deref( op2.sigFig10 == maxsf ? op2   : R( op2,   maxsf ) ), 
			R::roundingDefault ) ;

		*this = result ;
		return *this ;   	
	}  

	R 
	operator^( const R& op1, const R& op2 )  
	{  
		auto maxsf = std::max( op1.sigFig10, op2.sigFig10 ) ;

		R result( "0", maxsf ) ;

		mpfr_pow( 
			R::deref( result ), 
			R::deref( op1.sigFig10 == maxsf ? op1 : R( op1, maxsf ) ),
			R::deref( op2.sigFig10 == maxsf ? op2 : R( op2, maxsf ) ), 
			R::roundingDefault ) ;

		return result ;   		
	}  

	R& 
	R::operator^=( const R& op2 )  
	{  
		auto maxsf = std::max( sigFig10, op2.sigFig10 ) ;

		R result( "0", maxsf ) ;

		mpfr_pow( 
			R::deref( result ), 
			R::deref( sigFig10     == maxsf ? *this : R( *this, maxsf ) ),
			R::deref( op2.sigFig10 == maxsf ? op2   : R( op2,   maxsf ) ), 
			R::roundingDefault ) ;

		*this = result ;
		return *this ;   		
	}  

	//----------------------------------------------------------------------------------------------------------------------

	void
	R::compare( const R& op1, const R& op2, bool& equal, bool& moreThan, bool& lessThan ) 
	{
		equal    = false ;
		moreThan = false ;
		lessThan = false ;

		auto result = op1 - op2 ;

		equal    = result.toDecimal() == "+0.0"  ;
		lessThan = stringhlp::left( result.toDecimal(), 1 ) == "-" ; 
		moreThan = (! lessThan) && (! equal) ;
	}

	bool 
	operator>( const R& op1, const R& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		R::compare( op1, op2, equal, moreThan, lessThan )  ;

		return moreThan ;
	}

	bool 
	operator<( const R& op1, const R& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		R::compare( op1, op2, equal, moreThan, lessThan )  ;

		return lessThan ;
	}

	bool 
	operator>=( const R& op1, const R& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		R::compare( op1, op2, equal, moreThan, lessThan )  ;

		return moreThan || equal ;
	}

	bool 
	operator<=( const R& op1, const R& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		R::compare( op1, op2, equal, moreThan, lessThan )  ;

		return lessThan || equal ;
	}

	bool 
	operator==( const R& op1, const R& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		R::compare( op1, op2, equal, moreThan, lessThan )  ;

		return equal ;
	}

	bool 
	operator!=( const R& op1, const R& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		R::compare( op1, op2, equal, moreThan, lessThan )  ;

		return ! equal ;
	}
	
	//----------------------------------------------------------------------------------------------------------------------

	R 
	R::sin()  
	{
		R result( *this ) ; 

		mpfr_sin( deref(result), deref(*this), roundingDefault ) ;

		return result ;   
	}

	R 
	R::cos()  
	{
		R result( *this ) ; 

		mpfr_cos( deref(result), deref(*this), roundingDefault ) ;

		return result ;   
	}

	R 
	R::tan()  
	{
		R result( *this ) ; 

		mpfr_tan( deref(result), deref(*this), roundingDefault ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	R 
	R::pi()  
	{
		R result( *this ) ; 

		mpfr_const_pi( deref(result), roundingDefault ) ;

		return result ;   
	}

	R 
	R::e()  
	{
		R result( *this ) ; 

		R one( "1", sigFig10 ) ; 

		mpfr_exp( deref(result), deref(one), roundingDefault ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	R 
	R::neg()  
	{ 
		R minusone( "-1", sigFig10 ) ; 

		return *this * minusone ;  
	}

	R 
	R::inv()  
	{ 
		R one( "1", sigFig10 ) ; 

		return one / *this ;   
	}

	R 
	R::abs()  
	{ 
		R result( *this ) ; 

		mpfr_abs( deref(result), deref(*this), roundingDefault ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	R 
	R::exp() 
	{
		R result( *this ) ; 

		mpfr_exp( deref(result), deref(*this), roundingDefault ) ;

		return result ;   
	}

	R 
	R::log() 
	{
		R result( *this ) ; 

		mpfr_log( deref(result), deref(*this), roundingDefault ) ;

		return result ;   
	}

	R 
	R::log2() 
	{
		R result( *this ) ; 

		mpfr_log2( deref(result), deref(*this), roundingDefault ) ;

		return result ;   
	}

	R 
	R::log10() 
	{
		R result( *this ) ; 

		mpfr_log10( deref(result), deref(*this), roundingDefault ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	R 
	R::pow2() // 2 ^ this
	{
		R result( *this ) ; 

		R two( "2", sigFig10 ) ; 

		mpfr_pow( deref(result), deref(two), deref(*this), roundingDefault ) ;

		return result ;   
	}

	R 
	R::pow10() // 10 ^ this
	{
		R result( *this ) ; 

		R ten( "10", sigFig10 ) ; 

		mpfr_pow( deref(result), deref(ten), deref(*this), roundingDefault ) ;

		return result ;   
	}

	R 
	R::root( const R& op1 ) // the op1-th root of this
	{
		auto maxsf = std::max( sigFig10, op1.sigFig10 ) ;

		R result( *this, maxsf ) ;
		R one   ( "1",   maxsf ) ; 

		R index = one / op1 ;

		mpfr_pow( 
			R::deref( result ), 
			R::deref( result ),
			R::deref( index  ), 
			R::roundingDefault ) ;

		return result ;   		
	}

	R 
	R::sqrt() // square root
	{
		R two( "2", sigFig10 ) ; 

		return root( two ) ;
	}
		
	R 
	R::fact() // factorial n!
	{
		R result( *this ) ; 

		auto n = mpfr_get_ui( deref( floor() ), roundingDefault ) ;

 		mpfr_fac_ui( deref(result), n, roundingDefault ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	R 
	R::ceil() 
	{
		R result( *this ) ; 

		mpfr_ceil( deref(result), deref(*this) ) ;

		return result ;   
	}

	R 
	R::floor() 
	{
		R result( *this ) ; 

		mpfr_floor( deref(result), deref(*this) ) ;

		return result ;   
	}

	R 
	R::trunc() 
	{
		R result( *this ) ; 

		mpfr_trunc( deref(result), deref(*this) ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	std::map<unsigned long, R> 
	R::factorialMap( unsigned long n )
	{
		std::map<unsigned long, R> map ;

		map[0] = 1 ;

		for ( unsigned long i = 1 ; i <= n ; i++ )
		{
			map[i] = map[i-1] * i ;
		}

		return map ;
	}

	//----------------------------------------------------------------------------------------------------------------------
	
} // end ns

