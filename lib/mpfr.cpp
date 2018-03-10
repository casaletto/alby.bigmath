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
#include <gmp.h>
#include <mpfr.h>

#include "./stringhlp.h"
#include "./stringcat.h"
#include "./mpfr_t_wrapper.h"
#include "./mpfr.h"
 
namespace alby::bigmath 
{
	unsigned long mpfr::precision10global = mpfr::precision10default ;
	mpfr_rnd_t    mpfr::roundingGlobal    = mpfr::roundingDefault    ;

	//----------------------------------------------------------------------------------------------------------------------

	unsigned long 
	mpfr::getPrecisionLocal()
	{
		return precision10local ;	
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

	//----------------------------------------------------------------------------------------------------------------------

	mpfr_rnd_t 
	mpfr::getRoundingLocal()
	{
		return roundingLocal ;
	}

	mpfr_rnd_t 
	mpfr::getRounding()
	{
		return roundingGlobal ;	
	}

	void 
	mpfr::setRounding( mpfr_rnd_t rnd )
	{
		roundingGlobal = rnd ;	
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

	mpfr&
	mpfr::operator=( const mpfr& rhs ) // =
	{
		if ( this != &rhs )
		{
			cleanup() ;
			init()    ;

			precision10local = rhs.precision10local ;
			roundingLocal    = rhs.roundingLocal  ;

			p = new mpfr_t_wrapper( precision10local ) ;

			mpfr_set( deref(*this), deref(rhs), roundingLocal ) ; 
		}
		return *this ;
	}

	mpfr::mpfr( const mpfr& rhs ) // copy constr
	{
		init() ;

		*this = rhs ;
	}

	mpfr::mpfr() // constr
	{
		init() ;

		precision10local = precision10global ;
		roundingLocal    = roundingGlobal    ;

		p = new mpfr_t_wrapper( precision10local ) ; // default 0
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr::mpfr( unsigned long thePrecision10, mpfr_rnd_t theRounding ) // constr
	{
		init() ;

		precision10local = thePrecision10 ;
		roundingLocal    = theRounding    ;

		p = new mpfr_t_wrapper( precision10local ) ; // default 0
	}

	mpfr::mpfr( const mpfr& rhs, unsigned long thePrecision10, mpfr_rnd_t theRounding  ) // constr
	{
		init() ;

		precision10local = thePrecision10 ;
		roundingLocal    = theRounding    ;

		p = new mpfr_t_wrapper( precision10local ) ; // default 0

		mpfr_set( deref(*this), deref(rhs), roundingLocal ) ; 
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr::mpfr( const char* str, int base ) // constr
	{
		init() ;

		precision10local = precision10global ;
		roundingLocal    = roundingGlobal    ;

		p = new mpfr_t_wrapper( precision10local ) ;

		mpfr_set_str( deref(*this), str, base, roundingLocal ) ; 
	}

	mpfr::mpfr( const char* str, unsigned long thePrecision10, mpfr_rnd_t theRounding, int base  ) // constr
	{
		init() ;

		precision10local = thePrecision10 ;
		roundingLocal    = theRounding   ;

		p = new mpfr_t_wrapper( precision10local ) ;

		mpfr_set_str( deref(*this), str, base, roundingLocal ) ; 
	}
 
	mpfr::mpfr( const std::string& str, int base ) // constr
	{
		init() ;

		precision10local = precision10global ;
		roundingLocal    = roundingGlobal    ;

		p = new mpfr_t_wrapper( precision10local ) ;

		mpfr_set_str( deref(*this), str.c_str(), base, roundingLocal ) ; 	
	}

	mpfr::mpfr( const std::string& str, unsigned long thePrecision10, mpfr_rnd_t theRounding, int base ) // constr
	{
		init() ;

		precision10local = thePrecision10 ;
		roundingLocal    = theRounding    ;

		p = new mpfr_t_wrapper( precision10local ) ;

		mpfr_set_str( deref(*this), str.c_str(), base, roundingLocal ) ; 	
	}

	//----------------------------------------------------------------------------------------------------------------------

	std::ostream& 
	operator<<( std::ostream& os, const mpfr& mpfr )  
	{  
		os << mpfr.toString() ;  
		return os ;   
	}  

	mpfr 
	operator+( const mpfr& op1, const mpfr& op2 )  
	{  
		mpfr result( op1.precision10local, op1.roundingLocal ) ;
		
		mpfr_add( mpfr::deref(result), mpfr::deref(op1), mpfr::deref(op2), op1.roundingLocal ) ;

		return result ;   
	}  

	mpfr& 
	mpfr::operator+=( const mpfr& op2 )  
	{  
		mpfr_add( mpfr::deref(*this), mpfr::deref(*this), mpfr::deref(op2), roundingLocal ) ;

		return *this ;   
	}

	mpfr 
	operator-( const mpfr& op1, const mpfr& op2 )  
	{  
		mpfr result( op1.precision10local, op1.roundingLocal ) ;
		
		mpfr_sub( mpfr::deref(result), mpfr::deref(op1), mpfr::deref(op2), op1.roundingLocal ) ;

		return result ;   
	}  

	mpfr& 
	mpfr::operator-=( const mpfr& op2 )  
	{  
		mpfr_sub( mpfr::deref(*this), mpfr::deref(*this), mpfr::deref(op2), roundingLocal ) ;

		return *this ;   
	}  

	mpfr 
	operator*( const mpfr& op1, const mpfr& op2 )  
	{  
		mpfr result( op1.precision10local, op1.roundingLocal ) ;
		
		mpfr_mul( mpfr::deref(result), mpfr::deref(op1), mpfr::deref(op2), op1.roundingLocal ) ;

		return result ;   
	}  

	mpfr& 
	mpfr::operator*=( const mpfr& op2 )  
	{  
		mpfr_mul( mpfr::deref(*this), mpfr::deref(*this), mpfr::deref(op2), roundingLocal ) ;

		return *this ;   
	}  

	mpfr 
	operator/( const mpfr& op1, const mpfr& op2 )  
	{  
		mpfr result( op1.precision10local, op1.roundingLocal ) ;
		
		mpfr_div( mpfr::deref(result), mpfr::deref(op1), mpfr::deref(op2), op1.roundingLocal ) ;

		return result ;   
	}  

	mpfr& 
	mpfr::operator/=( const mpfr& op2 )  
	{  
		mpfr_div( mpfr::deref(*this), mpfr::deref(*this), mpfr::deref(op2), roundingLocal ) ;

		return *this ;   
	}  

	mpfr 
	operator^( const mpfr& op1, const mpfr& op2 )  
	{  
		mpfr result( op1.precision10local, op1.roundingLocal ) ;
		
		mpfr_pow( mpfr::deref(result), mpfr::deref(op1), mpfr::deref(op2), op1.roundingLocal ) ;

		return result ;   
	}  

	mpfr& 
	mpfr::operator^=( const mpfr& op2 )  
	{  
		mpfr_pow( mpfr::deref(*this), mpfr::deref(*this), mpfr::deref(op2), roundingLocal ) ;

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
		mpfr result( precision10local, roundingLocal ) ;

		mpfr_sin( deref(result), deref(*this), roundingLocal ) ;

		return result ;   
	}

	mpfr 
	mpfr::cos()  
	{
		mpfr result( precision10local, roundingLocal ) ;

		mpfr_cos( deref(result), deref(*this), roundingLocal ) ;

		return result ;   
	}

	mpfr 
	mpfr::tan()  
	{
		mpfr result( precision10local, roundingLocal ) ;

		mpfr_tan( deref(result), deref(*this), roundingLocal ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr 
	mpfr::pi()  
	{
		mpfr result( precision10local, roundingLocal ) ;

		mpfr_const_pi( deref(result), roundingLocal ) ;

		return result ;   
	}

	mpfr 
	mpfr::e()  
	{
		mpfr result( precision10local, roundingLocal ) ;
		mpfr one = "1.0" ;                                   //ALBY test precision

		mpfr_exp( deref(result), deref(one), roundingLocal ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr 
	mpfr::neg()  
	{ 
		return *this * mpfr( "-1.0" ) ;  
	}

	mpfr 
	mpfr::inv()  
	{ 
		return mpfr( "1.0" ) / *this ;   
	}

	mpfr 
	mpfr::abs()  
	{ 
		mpfr result( precision10local, roundingLocal ) ;

		mpfr_abs( deref(result), deref(*this), roundingLocal ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr 
	mpfr::exp() 
	{
		mpfr result( precision10local, roundingLocal ) ;

		mpfr_exp( deref(result), deref(*this), roundingLocal ) ;

		return result ;   
	}

	mpfr 
	mpfr::log() 
	{
		mpfr result( precision10local, roundingLocal ) ;

		mpfr_log( deref(result), deref(*this), roundingLocal ) ;

		return result ;   
	}

	mpfr 
	mpfr::log2() 
	{
		mpfr result( precision10local, roundingLocal ) ;

		mpfr_log2( deref(result), deref(*this), roundingLocal ) ;

		return result ;   
	}

	mpfr 
	mpfr::log10() 
	{
		mpfr result( precision10local, roundingLocal ) ;

		mpfr_log10( deref(result), deref(*this), roundingLocal ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr 
	mpfr::pow2() // 2 ^ this
	{
		mpfr result( precision10local, roundingLocal ) ;

		mpfr two = "2.0" ;                                   //ALBY test precision

		mpfr_pow( deref(result), deref(two), deref(*this), roundingLocal ) ;

		return result ;   
	}

	mpfr 
	mpfr::pow10() // 10 ^ this
	{
		mpfr result( precision10local, roundingLocal ) ;

		mpfr ten = "10.0" ;                                   //ALBY test precision

		mpfr_pow( deref(result), deref(ten), deref(*this), roundingLocal ) ;

		return result ;   
	}

	mpfr 
	mpfr::root( const mpfr& op1 ) // the op1-th root of this
	{
		mpfr result( precision10local, roundingLocal ) ;

		mpfr index = mpfr( "1.0" ) / op1 ;

		mpfr_pow( deref(result), deref(*this), deref(index), roundingLocal ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr 
	mpfr::sqrt() // square root
	{
		return root( "2.0" ) ;
	}
		
	mpfr 
	mpfr::fact() // factorial n!
	{
		mpfr result( precision10local, roundingLocal ) ;

		auto n = mpfr_get_ui( deref( floor() ), roundingLocal ) ;

 		mpfr_fac_ui( deref(result), n, roundingLocal ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr 
	mpfr::ceil() 
	{
		mpfr result( precision10local, roundingLocal ) ;

		mpfr_ceil( deref(result), deref(*this) ) ;

		return result ;   
	}

	mpfr 
	mpfr::floor() 
	{
		mpfr result( precision10local, roundingLocal ) ;

		mpfr_floor( deref(result), deref(*this) ) ;

		return result ;   
	}

	mpfr 
	mpfr::trunc() 
	{
		mpfr result( precision10local, roundingLocal ) ;

		mpfr_trunc( deref(result), deref(*this) ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr_t& 
	mpfr::deref( const mpfr& mpfr ) // dereference the important part
	{
		return *( mpfr.p->get() ) ;
	}	

	mpfr::operator 
	std::string() const 
    {
        return toString() ;
    }

	std::string 
	mpfr::toString() const
	{
		return p->toString( true ) ;
	}

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

