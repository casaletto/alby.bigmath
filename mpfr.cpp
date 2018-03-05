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

#include "./mpfr_t_wrapper.h"
#include "./mpfr.h"

namespace alby::bigmath 
{
	mpfr_prec_t mpfr::precisionGlobal = mpfr::precisionDefault ;
	mpfr_rnd_t  mpfr::roundingGlobal  = mpfr::roundingDefault  ;

	//----------------------------------------------------------------------------------------------------------------------

	mpfr_prec_t mpfr::getPrecisionLocal()
	{
		return precisionLocal ;	
	}

	mpfr_prec_t mpfr::getPrecision()
	{
		return precisionGlobal ;	
	}

	void mpfr::setPrecision( mpfr_prec_t prec )
	{
		precisionGlobal = prec ;	
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr_rnd_t mpfr::getRoundingLocal()
	{
		return roundingLocal ;
	}

	mpfr_rnd_t mpfr::getRounding()
	{
		return roundingGlobal ;	
	}

	void mpfr::setRounding( mpfr_rnd_t rnd )
	{
		roundingGlobal = rnd ;	
	}

	//----------------------------------------------------------------------------------------------------------------------

	void mpfr::init()
	{
		p = nullptr ;
	}

	void mpfr::cleanup()
	{
		if ( p != nullptr )
			 delete p ;		
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr::~mpfr() // destr
	{
		cleanup() ;
	}

	mpfr& mpfr::operator=( const mpfr& rhs ) // =
	{
		if ( this != &rhs )
		{
			cleanup() ;
			init()    ;

			precisionLocal = rhs.precisionLocal ;
			roundingLocal  = rhs.roundingLocal  ;

			p = new mpfr_t_wrapper( precisionLocal ) ;

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

		precisionLocal = precisionGlobal ;
		roundingLocal  = roundingGlobal  ;

		p = new mpfr_t_wrapper( precisionLocal ) ; // default 0
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr::mpfr( mpfr_prec_t aPrecision, mpfr_rnd_t aRounding  ) // constr
	{
		init() ;

		precisionLocal = aPrecision ;
		roundingLocal  = aRounding  ;

		p = new mpfr_t_wrapper( precisionLocal ) ; // default 0
	}

	mpfr::mpfr( const mpfr& rhs, mpfr_prec_t aPrecision, mpfr_rnd_t aRounding  ) // constr
	{
		init() ;

		precisionLocal = aPrecision ;
		roundingLocal  = aRounding  ;

		p = new mpfr_t_wrapper( precisionLocal ) ; // default 0

		mpfr_set( deref(*this), deref(rhs), roundingLocal ) ; 
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr::mpfr( const char* str, int base ) // constr
	{
		init() ;

		precisionLocal = precisionGlobal ;
		roundingLocal  = roundingGlobal  ;

		p = new mpfr_t_wrapper( precisionLocal ) ;

		mpfr_set_str( deref(*this), str, base, roundingLocal ) ; 
	}

	mpfr::mpfr( const char* str, mpfr_prec_t aPrecision, mpfr_rnd_t aRounding, int base  ) // constr
	{
		init() ;

		precisionLocal = aPrecision ;
		roundingLocal  = aRounding  ;

		p = new mpfr_t_wrapper( precisionLocal ) ;

		mpfr_set_str( deref(*this), str, base, roundingLocal ) ; 
	}

	mpfr::mpfr( const std::string& str, int base ) // constr
	{
		init() ;

		precisionLocal = precisionGlobal ;
		roundingLocal  = roundingGlobal  ;

		p = new mpfr_t_wrapper( precisionLocal ) ;

		mpfr_set_str( deref(*this), str.c_str(), base, roundingLocal ) ; 	
	}

	mpfr::mpfr( const std::string& str, mpfr_prec_t aPrecision, mpfr_rnd_t aRounding, int base ) // constr
	{
		init() ;

		precisionLocal = aPrecision ;
		roundingLocal  = aRounding  ;

		p = new mpfr_t_wrapper( precisionLocal ) ;

		mpfr_set_str( deref(*this), str.c_str(), base, roundingLocal ) ; 	
	}
	
	//----------------------------------------------------------------------------------------------------------------------

	std::ostream& operator<<( std::ostream& os, const mpfr& mpfr )  
	{  
		os << mpfr.toString() ;  
		return os ;   
	}  

	mpfr operator+( const mpfr& op1, const mpfr& op2 )  
	{  
		mpfr result( op1.precisionLocal, op1.roundingLocal ) ;
		
		mpfr_add( mpfr::deref(result), mpfr::deref(op1), mpfr::deref(op2), op1.roundingLocal ) ;

		return result ;   
	}  

	mpfr& mpfr::operator+=( const mpfr& op2 )  
	{  
		mpfr_add( mpfr::deref(*this), mpfr::deref(*this), mpfr::deref(op2), roundingLocal ) ;

		return *this ;   
	}

	mpfr operator-( const mpfr& op1, const mpfr& op2 )  
	{  
		mpfr result( op1.precisionLocal, op1.roundingLocal ) ;
		
		mpfr_sub( mpfr::deref(result), mpfr::deref(op1), mpfr::deref(op2), op1.roundingLocal ) ;

		return result ;   
	}  

	mpfr& mpfr::operator-=( const mpfr& op2 )  
	{  
		mpfr_sub( mpfr::deref(*this), mpfr::deref(*this), mpfr::deref(op2), roundingLocal ) ;

		return *this ;   
	}  

	mpfr operator*( const mpfr& op1, const mpfr& op2 )  
	{  
		mpfr result( op1.precisionLocal, op1.roundingLocal ) ;
		
		mpfr_mul( mpfr::deref(result), mpfr::deref(op1), mpfr::deref(op2), op1.roundingLocal ) ;

		return result ;   
	}  

	mpfr& mpfr::operator*=( const mpfr& op2 )  
	{  
		mpfr_mul( mpfr::deref(*this), mpfr::deref(*this), mpfr::deref(op2), roundingLocal ) ;

		return *this ;   
	}  

	mpfr operator/( const mpfr& op1, const mpfr& op2 )  
	{  
		mpfr result( op1.precisionLocal, op1.roundingLocal ) ;
		
		mpfr_div( mpfr::deref(result), mpfr::deref(op1), mpfr::deref(op2), op1.roundingLocal ) ;

		return result ;   
	}  

	mpfr& mpfr::operator/=( const mpfr& op2 )  
	{  
		mpfr_div( mpfr::deref(*this), mpfr::deref(*this), mpfr::deref(op2), roundingLocal ) ;

		return *this ;   
	}  

	mpfr operator^( const mpfr& op1, const mpfr& op2 )  
	{  
		mpfr result( op1.precisionLocal, op1.roundingLocal ) ;
		
		mpfr_pow( mpfr::deref(result), mpfr::deref(op1), mpfr::deref(op2), op1.roundingLocal ) ;

		return result ;   
	}  

	mpfr& mpfr::operator^=( const mpfr& op2 )  
	{  
		mpfr_pow( mpfr::deref(*this), mpfr::deref(*this), mpfr::deref(op2), roundingLocal ) ;

		return *this ;   
	}  

	//----------------------------------------------------------------------------------------------------------------------

	bool operator>( const mpfr& op1, const mpfr& op2 )  
	{  
		//ALBY fix me

		return true ;
	}

	bool operator<( const mpfr& op1, const mpfr& op2 )  
	{  
		//ALBY fix me

		return true ;
	}

	bool operator>=( const mpfr& op1, const mpfr& op2 )  
	{  
		//ALBY fix me

		return true ;
	}

	bool operator<=( const mpfr& op1, const mpfr& op2 )  
	{  
		//ALBY fix me

		return true ;
	}

	bool operator==( const mpfr& op1, const mpfr& op2 )  
	{  
		//ALBY fix me

		return true ;
	}

	bool operator!=( const mpfr& op1, const mpfr& op2 )  
	{  
		//ALBY fix me

		return true ;
	}
	
	//----------------------------------------------------------------------------------------------------------------------

	mpfr mpfr::sin()  
	{
		mpfr result( precisionLocal, roundingLocal ) ;

		mpfr_sin( deref(result), deref(*this), roundingLocal ) ;

		return result ;   
	}

	mpfr mpfr::cos()  
	{
		mpfr result( precisionLocal, roundingLocal ) ;

		mpfr_cos( deref(result), deref(*this), roundingLocal ) ;

		return result ;   
	}

	mpfr mpfr::tan()  
	{
		mpfr result( precisionLocal, roundingLocal ) ;

		mpfr_tan( deref(result), deref(*this), roundingLocal ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr mpfr::pi()  
	{
		mpfr result( precisionLocal, roundingLocal ) ;

		mpfr_const_pi( deref(result), roundingLocal ) ;

		return result ;   
	}

	mpfr mpfr::e()  
	{
		mpfr result( precisionLocal, roundingLocal ) ;
		mpfr one = "1.0" ;                                   //ALBY test precision

		mpfr_exp( deref(result), deref(one), roundingLocal ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr mpfr::neg()  
	{ 
		return *this * mpfr( "-1.0" ) ;  
	}

	mpfr mpfr::inv()  
	{ 
		return mpfr( "1.0" ) / *this ;   
	}

	mpfr mpfr::abs()  
	{ 
		mpfr result( precisionLocal, roundingLocal ) ;

		mpfr_abs( deref(result), deref(*this), roundingLocal ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr mpfr::exp() 
	{
		mpfr result( precisionLocal, roundingLocal ) ;

		mpfr_exp( deref(result), deref(*this), roundingLocal ) ;

		return result ;   
	}

	mpfr mpfr::log() 
	{
		mpfr result( precisionLocal, roundingLocal ) ;

		mpfr_log( deref(result), deref(*this), roundingLocal ) ;

		return result ;   
	}

	mpfr mpfr::log2() 
	{
		mpfr result( precisionLocal, roundingLocal ) ;

		mpfr_log2( deref(result), deref(*this), roundingLocal ) ;

		return result ;   
	}

	mpfr mpfr::log10() 
	{
		mpfr result( precisionLocal, roundingLocal ) ;

		mpfr_log10( deref(result), deref(*this), roundingLocal ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr mpfr::pow2() // 2 ^ this
	{
		mpfr result( precisionLocal, roundingLocal ) ;

		mpfr two = "2.0" ;                                   //ALBY test precision

		mpfr_pow( deref(result), deref(two), deref(*this), roundingLocal ) ;

		return result ;   
	}

	mpfr mpfr::pow10() // 10 ^ this
	{
		mpfr result( precisionLocal, roundingLocal ) ;

		mpfr ten = "10.0" ;                                   //ALBY test precision

		mpfr_pow( deref(result), deref(ten), deref(*this), roundingLocal ) ;

		return result ;   
	}

	mpfr mpfr::root( const mpfr& op1 ) // the op1-th root of this
	{
		mpfr result( precisionLocal, roundingLocal ) ;

		mpfr index = mpfr( "1.0" ) / op1 ;

		mpfr_pow( deref(result), deref(*this), deref(index), roundingLocal ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr mpfr::ceil() 
	{
		mpfr result( precisionLocal, roundingLocal ) ;

		mpfr_ceil( deref(result), deref(*this) ) ;

		return result ;   
	}

	mpfr mpfr::floor() 
	{
		mpfr result( precisionLocal, roundingLocal ) ;

		mpfr_floor( deref(result), deref(*this) ) ;

		return result ;   
	}

	mpfr mpfr::trunc() 
	{
		mpfr result( precisionLocal, roundingLocal ) ;

		mpfr_trunc( deref(result), deref(*this) ) ;

		return result ;   
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpfr_t& mpfr::deref( const mpfr& mpfr ) // dereference the important part
	{
		return *( mpfr.p->get() ) ;
	}	

	unsigned long getBinaryPrecision( unsigned long precisionDecimal ) 
	{
		// the number of binary bits for x decimal places

		return ::ceil( ::log2( ::pow( 10.0, precisionDecimal ) ) )  ;

	}


///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////
//ALBY TODO
	std::string mpfr::toString() const
	{
		// take into account - and + and .

		auto digits10 = 20 ; // fix me

		char format[100] ;
		std::sprintf( format, "%%.%uRF", digits10 ) ;


		char buffer[ digits10+2 ] ;
		mpfr_snprintf( buffer, digits10+1, format, p->get() ) ;

		return std::string( buffer ) ;
	}






//ALBY TODO 10/15
/*
	mpq_class mpfr::toMpq() 
	{
		std::cout << "111" << std::endl ;

		mpq_class x( 10, 20 ) ;

		std::cout << "222" << std::endl ;

		//x = "20/10000000" ; 

		return x ;
		
	}

	mpfr::operator mpq_class()  // convert to gmp c++ class rational number a/b
	{ 
		std::cout << "111" << std::endl ;

		mpq_class x( 10, 20 ) ;

		std::cout << "222" << std::endl ;

		//x = "20/10000000" ; 

		return x ;
	}
*/

	std::string mpfr::version() 
	{
		std::stringstream bob ;

		bob	
			<< "MPFR library  "
			<< ::mpfr_get_version()
			<< std::endl
			<< "MPFR header   " 
			<< MPFR_VERSION_STRING                      
			<< " (based on "
			<< MPFR_VERSION_MAJOR
			<< "."
			<< MPFR_VERSION_MINOR
			<< "."
			<< MPFR_VERSION_PATCHLEVEL
			<< ")"
			<< std::endl
			<< "MPFR_PREC_MAX "
			<< MPFR_PREC_MAX
			<< std::endl
			<< "default prec  "
			<< mpfr_get_default_prec() ;

		return bob.str() ;
	}

	std::string mpfr::random( int bytes ) // string of hex random bytes
	{
		std::vector<char> buffer ;
		buffer.resize( bytes ) ;
		std::fill( buffer.begin(), buffer.end(), 0 ) ;

		auto f = "/dev/urandom" ;
		std::ifstream mystream( f, std::ios::in | std::ios_base::binary ) ;

		mystream.seekg( 0, std::ios_base::beg ) ;
		mystream.read ( buffer.data(), bytes ) ;

		std::stringstream bob ;

		for ( auto c : buffer )
		{
			auto x = (int) (unsigned char) c ;
			bob
				<< std::uppercase
				<< std::right
				<< std::setw(2) 
				<< std::setfill( '0' ) 
				<< std::hex 
				<< x ;
		}

		return bob.str() ;
	}
	

} // end ns

