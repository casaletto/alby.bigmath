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
#include "./mpfr.h"
 
namespace alby::bigmath 
{
	unsigned long mpfr::sigFig10global = mpfr::sigFig10default ;
	bool          mpfr::debug          = false                 ;

	//----------------------------------------------------------------------------------------------------------------------

	mpfr_t& 
	mpfr::deref( const mpfr& mpfr ) // dereference the important part
	{
		return *( mpfr.p->get() ) ;
	}	

	unsigned long 
	mpfr::getSignificantFiguresLocal()
	{
		return sigFig10 ;	
	}

	unsigned long 
	mpfr::getSignificantFigures()
	{
		return sigFig10global ;	
	}

	void 
	mpfr::setSignificantFigures( unsigned long theSigFig10 )
	{
		sigFig10global = theSigFig10 ;	
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

		sigFig10 = sigFig10global ;

		p = new mpfr_t_wrapper( sigFig10 ) ; // default 0
	}

	mpfr::mpfr( const mpfr& rhs ) // copy constr
	{
		init() ;

		*this = rhs ;
	}

	mpfr::mpfr( const mpfr& rhs, unsigned long theSigFig10 ) // constr
	{
		init() ;

		sigFig10 = theSigFig10 ;

		p = new mpfr_t_wrapper( sigFig10 ) ;

		mpfr_set( deref(*this), deref(rhs), roundingDefault ) ; 
	}

	mpfr&
	mpfr::operator=( const mpfr& rhs ) // =
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

	//----------------------------------------------------------------------------------------------------------------------

	mpfr::mpfr( const char* str ) // constr
	{
		init() ;

		sigFig10 = sigFig10global ;

		p = new mpfr_t_wrapper( sigFig10 ) ;

		std::string strScientificNotation ;
		auto ok = numberhlp::toScientificNotation( str, strScientificNotation, sigFig10 ) ;

		if ( ! ok ) throw std::invalid_argument( stringcat( "Bad number [", str, "]" ) ) ;

		mpfr_set_str( deref(*this), strScientificNotation.c_str(), 10, roundingDefault ) ; 
	}

	mpfr::mpfr( const char* str, unsigned long theSigFig10, numberBase base ) // constr
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

	mpfr::mpfr( const std::string& str ) // constr
	{
		init() ;

		sigFig10 = sigFig10global ;

		p = new mpfr_t_wrapper( sigFig10 ) ;

		std::string strScientificNotation ;
		auto ok = numberhlp::toScientificNotation( str, strScientificNotation, sigFig10 ) ;

		if ( ! ok ) throw std::invalid_argument( stringcat( "Bad number [", str, "]" ) ) ;

		mpfr_set_str( deref(*this), strScientificNotation.c_str(), 10, roundingDefault ) ; 	
	}

	mpfr::mpfr( const std::string& str, unsigned long theSigFig10, numberBase base ) // constr
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

	std::ostream& 
	operator<<( std::ostream& os, const mpfr& rhs )  
	{  
		os << const_cast<mpfr*>( &rhs )->toString() ;

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
		return const_cast<mpfr*>( this )->toDecimal( false )  ;
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
	mpfr::toDecimal( bool allSigFig ) // default false, false means remove trailing zeros
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
	mpfr::toScientificNotation( bool allSigFig ) // default false, false means remove trailing zeros
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
	mpfr::toSignificantFigures( unsigned long theSigFig10 ) 
	{
		auto t = roundToSignificantFigures( theSigFig10 ) ;

		auto str = t.toScientificNotation() ;

		std::string strResult ;
		auto ok = numberhlp::scientificNotationExtend( str, strResult, theSigFig10 ) ;

		if ( ! ok ) throw std::invalid_argument( stringcat( "Bad number [", str, "]" ) ) ;

		return strResult ;
	}

	mpfr 
	mpfr::roundToSignificantFigures( unsigned long theSigFig10 ) 
	{
		auto str = p->toString() ;

		std::string strResult ;
		auto ok = numberhlp::toScientificNotation( str, strResult, theSigFig10 ) ;

		if ( ! ok ) throw std::invalid_argument( stringcat( "Bad number [", str, "]" ) ) ;

		auto result = mpfr( strResult, sigFig10 ) ;

		return result ;
	}

	std::string 
	mpfr::toDecimalPlaces( unsigned long theDecimalPlaces ) 
	{
		auto str = p->toString() ;

		std::string strResult ;
		auto ok = numberhlp::decimalPlacesExtend( str, strResult, theDecimalPlaces ) ;

		if ( ! ok ) throw std::invalid_argument( stringcat( "Bad number [", str, "]" ) ) ;

		return strResult ;
	}

	mpfr 
	mpfr::roundToDecimalPlaces( unsigned long theDecimalPlaces ) 
	{
		auto str = toDecimalPlaces( theDecimalPlaces ) ;

		mpfr result( str, sigFig10 ) ;

		return result ;
	}

	std::string 
	mpfr::toFraction( bool reduce ) 
	{
		// return gmp compatibile fraction as string

		std::string numerator   ;
		std::string denominator ;

		return toFraction( numerator, denominator, reduce ) ;
	}	

	std::string 
	mpfr::toFraction( std::string& numerator, std::string& denominator, bool bReduce ) 
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

	std::string 
	mpfr::reduce( const std::string& rational )
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

	mpfr 
	operator+( const mpfr& op1, const mpfr& op2 )  
	{ 
		auto maxsf = std::max( op1.sigFig10, op2.sigFig10 ) ;

		mpfr result( "0", maxsf ) ;

		mpfr_add( 
			mpfr::deref( result ), 
			mpfr::deref( op1.sigFig10 == maxsf ? op1 : mpfr( op1, maxsf ) ),
			mpfr::deref( op2.sigFig10 == maxsf ? op2 : mpfr( op2, maxsf ) ), 
			mpfr::roundingDefault ) ;

		return result ;   
	}  

	mpfr& 
	mpfr::operator+=( const mpfr& op2 )  
	{  
		auto maxsf = std::max( sigFig10, op2.sigFig10 ) ;

		mpfr result( "0", maxsf ) ;

		mpfr_add( 
			mpfr::deref( result ), 
			mpfr::deref( sigFig10     == maxsf ? *this : mpfr( *this, maxsf ) ),
			mpfr::deref( op2.sigFig10 == maxsf ? op2   : mpfr( op2,   maxsf ) ), 
			mpfr::roundingDefault ) ;

		*this = result ;
		return *this ;   
	}

	mpfr 
	operator-( const mpfr& op1, const mpfr& op2 )  
	{  
		auto maxsf = std::max( op1.sigFig10, op2.sigFig10 ) ;

		mpfr result( "0", maxsf ) ;

		mpfr_sub( 
			mpfr::deref( result ), 
			mpfr::deref( op1.sigFig10 == maxsf ? op1 : mpfr( op1, maxsf ) ),
			mpfr::deref( op2.sigFig10 == maxsf ? op2 : mpfr( op2, maxsf ) ), 
			mpfr::roundingDefault ) ;

		return result ;   
	}  

	mpfr& 
	mpfr::operator-=( const mpfr& op2 )  
	{  
		auto maxsf = std::max( sigFig10, op2.sigFig10 ) ;

		mpfr result( "0", maxsf ) ;

		mpfr_sub( 
			mpfr::deref( result ), 
			mpfr::deref( sigFig10     == maxsf ? *this : mpfr( *this, maxsf ) ),
			mpfr::deref( op2.sigFig10 == maxsf ? op2   : mpfr( op2,   maxsf ) ), 
			mpfr::roundingDefault ) ;

		*this = result ;
		return *this ;   	
	}  

	mpfr 
	operator*( const mpfr& op1, const mpfr& op2 )  
	{ 
		auto maxsf = std::max( op1.sigFig10, op2.sigFig10 ) ;

		mpfr result( "0", maxsf ) ;

		mpfr_mul( 
			mpfr::deref( result ), 
			mpfr::deref( op1.sigFig10 == maxsf ? op1 : mpfr( op1, maxsf ) ),
			mpfr::deref( op2.sigFig10 == maxsf ? op2 : mpfr( op2, maxsf ) ), 
			mpfr::roundingDefault ) ;

		return result ;   
	}  

	mpfr& 
	mpfr::operator*=( const mpfr& op2 )  
	{  
		auto maxsf = std::max( sigFig10, op2.sigFig10 ) ;

		mpfr result( "0", maxsf ) ;

		mpfr_mul( 
			mpfr::deref( result ), 
			mpfr::deref( sigFig10     == maxsf ? *this : mpfr( *this, maxsf ) ),
			mpfr::deref( op2.sigFig10 == maxsf ? op2   : mpfr( op2,   maxsf ) ), 
			mpfr::roundingDefault ) ;

		*this = result ;
		return *this ;   	
	}  

	mpfr 
	operator/( const mpfr& op1, const mpfr& op2 )  
	{  
		auto maxsf = std::max( op1.sigFig10, op2.sigFig10 ) ;

		mpfr result( "0", maxsf ) ;

		mpfr_div( 
			mpfr::deref( result ), 
			mpfr::deref( op1.sigFig10 == maxsf ? op1 : mpfr( op1, maxsf ) ),
			mpfr::deref( op2.sigFig10 == maxsf ? op2 : mpfr( op2, maxsf ) ), 
			mpfr::roundingDefault ) ;

		return result ;   
	}  

	mpfr& 
	mpfr::operator/=( const mpfr& op2 )  
	{  
		auto maxsf = std::max( sigFig10, op2.sigFig10 ) ;

		mpfr result( "0", maxsf ) ;

		mpfr_div( 
			mpfr::deref( result ), 
			mpfr::deref( sigFig10     == maxsf ? *this : mpfr( *this, maxsf ) ),
			mpfr::deref( op2.sigFig10 == maxsf ? op2   : mpfr( op2,   maxsf ) ), 
			mpfr::roundingDefault ) ;

		*this = result ;
		return *this ;   	
	}  

	mpfr 
	operator^( const mpfr& op1, const mpfr& op2 )  
	{  
		auto maxsf = std::max( op1.sigFig10, op2.sigFig10 ) ;

		mpfr result( "0", maxsf ) ;

		mpfr_pow( 
			mpfr::deref( result ), 
			mpfr::deref( op1.sigFig10 == maxsf ? op1 : mpfr( op1, maxsf ) ),
			mpfr::deref( op2.sigFig10 == maxsf ? op2 : mpfr( op2, maxsf ) ), 
			mpfr::roundingDefault ) ;

		return result ;   		
	}  

	mpfr& 
	mpfr::operator^=( const mpfr& op2 )  
	{  
		auto maxsf = std::max( sigFig10, op2.sigFig10 ) ;

		mpfr result( "0", maxsf ) ;

		mpfr_pow( 
			mpfr::deref( result ), 
			mpfr::deref( sigFig10     == maxsf ? *this : mpfr( *this, maxsf ) ),
			mpfr::deref( op2.sigFig10 == maxsf ? op2   : mpfr( op2,   maxsf ) ), 
			mpfr::roundingDefault ) ;

		*this = result ;
		return *this ;   		
	}  

	//----------------------------------------------------------------------------------------------------------------------

	void
	mpfr::compare( const mpfr& op1, const mpfr& op2, bool& equal, bool& moreThan, bool& lessThan ) 
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
	operator>( const mpfr& op1, const mpfr& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		mpfr::compare( op1, op2, equal, moreThan, lessThan )  ;

		return moreThan ;
	}

	bool 
	operator<( const mpfr& op1, const mpfr& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		mpfr::compare( op1, op2, equal, moreThan, lessThan )  ;

		return lessThan ;
	}

	bool 
	operator>=( const mpfr& op1, const mpfr& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		mpfr::compare( op1, op2, equal, moreThan, lessThan )  ;

		return moreThan || equal ;
	}

	bool 
	operator<=( const mpfr& op1, const mpfr& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		mpfr::compare( op1, op2, equal, moreThan, lessThan )  ;

		return lessThan || equal ;
	}

	bool 
	operator==( const mpfr& op1, const mpfr& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		mpfr::compare( op1, op2, equal, moreThan, lessThan )  ;

		return equal ;
	}

	bool 
	operator!=( const mpfr& op1, const mpfr& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		mpfr::compare( op1, op2, equal, moreThan, lessThan )  ;

		return ! equal ;
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

		mpfr one( "1", sigFig10 ) ; 

		mpfr_exp( deref(result), deref(one), roundingDefault ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr 
	mpfr::neg()  
	{ 
		mpfr minusone( "-1", sigFig10 ) ; 

		return *this * minusone ;  
	}

	mpfr 
	mpfr::inv()  
	{ 
		mpfr one( "1", sigFig10 ) ; 

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

		mpfr two( "2", sigFig10 ) ; 

		mpfr_pow( deref(result), deref(two), deref(*this), roundingDefault ) ;

		return result ;   
	}

	mpfr 
	mpfr::pow10() // 10 ^ this
	{
		mpfr result( *this ) ; 

		mpfr ten( "10", sigFig10 ) ; 

		mpfr_pow( deref(result), deref(ten), deref(*this), roundingDefault ) ;

		return result ;   
	}

	mpfr 
	mpfr::root( const mpfr& op1 ) // the op1-th root of this
	{
		auto maxsf = std::max( sigFig10, op1.sigFig10 ) ;

		mpfr result( *this, maxsf ) ;
		mpfr one   ( "1",   maxsf ) ; 

		mpfr index = one / op1 ;

		mpfr_pow( 
			mpfr::deref( result ), 
			mpfr::deref( result ),
			mpfr::deref( index  ), 
			mpfr::roundingDefault ) ;

		return result ;   		
	}

	mpfr 
	mpfr::sqrt() // square root
	{
		mpfr two( "2", sigFig10 ) ; 

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

	std::string 
	mpfr::version() 
	{
		return stringcat
		(
			"GMP version       ",			gmp_version,			
			"\nMPFR version      ",			mpfr_get_version(),
			"\nMPFR_PREC_MAX     ",			MPFR_PREC_MAX,
			"\nMPFR default prec ",			mpfr_get_default_prec() ,
			"\nMPFR min exponent ",			mpfr_get_emin(), 
			"\nMPFR max exponent ",			mpfr_get_emax(), 			
			"\nbits per limb     ",			mp_bits_per_limb 			
		) ;
	}

} // end ns

