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
#include <gmp.h>
#include <gmpxx.h>
#include <mpfr.h>

#include "./mpfr_t_wrapper.h"
#include "./mpfr.h"

namespace alby::bigmath 
{
	mpfr_rnd_t mpfr::getRounding()
	{
		return rounding ;
	}

	mpfr_prec_t mpfr::getPrecision()
	{
		return precision ;	
	}

	void mpfr::init()
	{
		p = nullptr ;
	}

	void mpfr::cleanup()
	{
		if ( p != nullptr )
			 delete p ;		
	}

	mpfr::~mpfr() // destr
	{
		cleanup() ;
	}

	mpfr::mpfr( const mpfr& rhs ) // copy constr
	{
		init() ;

		*this = rhs ;
	}

	mpfr& mpfr::operator=( const mpfr& rhs ) // =
	{
		if ( this != &rhs )
		{
			cleanup() ;
			init()    ;

			rounding  = rhs.rounding  ;
			precision = rhs.precision ;

			p = new mpfr_t_wrapper( precision ) ;

			mpfr_set( deref(*this), deref(rhs), rounding ) ; 
		}
		return *this ;
	}

	mpfr::mpfr( mpfr_rnd_t aRounding, mpfr_prec_t aPrecision ) // constr
	{
		init() ;

		rounding  = aRounding  ;
		precision = aPrecision ;

		p = new mpfr_t_wrapper( precision ) ; // default 0
	}

	mpfr::mpfr( const char* str, mpfr_rnd_t aRounding, mpfr_prec_t aPrecision, int base ) // constr
	{
		init() ;

		rounding  = aRounding  ;
		precision = aPrecision ;

		p = new mpfr_t_wrapper( precision ) ;

		mpfr_set_str( deref(*this), str, base, rounding ) ; 
	}

	mpfr::mpfr( const std::string& str, mpfr_rnd_t aRounding, mpfr_prec_t aPrecision, int base ) // constr
	{
		init() ;

		rounding  = aRounding  ;
		precision = aPrecision ;

		p = new mpfr_t_wrapper( precision ) ;

		mpfr_set_str( deref(*this), str.c_str(), base, rounding ) ; 	
	}
	
	std::ostream& operator<<( std::ostream& os, const mpfr& mpfr )  
	{  
		os << mpfr.toString() ;  
		return os ;   
	}  

	mpfr operator+( const mpfr& op1, const mpfr& op2 )  
	{  
		mpfr result( op1.rounding, op1.precision ) ;
		
		mpfr_add( mpfr::deref(result), mpfr::deref(op1), mpfr::deref(op2), op1.rounding ) ;

		return result ;   
	}  

	mpfr operator-( const mpfr& op1, const mpfr& op2 )  
	{  
		mpfr result( op1.rounding, op1.precision ) ;
		
		mpfr_sub( mpfr::deref(result), mpfr::deref(op1), mpfr::deref(op2), op1.rounding ) ;

		return result ;   
	}  

	mpfr operator*( const mpfr& op1, const mpfr& op2 )  
	{  
		mpfr result( op1.rounding, op1.precision ) ;
		
		mpfr_mul( mpfr::deref(result), mpfr::deref(op1), mpfr::deref(op2), op1.rounding ) ;

		return result ;   
	}  

	mpfr operator/( const mpfr& op1, const mpfr& op2 )  
	{  
		mpfr result( op1.rounding, op1.precision ) ;
		
		mpfr_div( mpfr::deref(result), mpfr::deref(op1), mpfr::deref(op2), op1.rounding ) ;

		return result ;   
	}  

	mpfr operator^( const mpfr& op1, const mpfr& op2 )  
	{  
		mpfr result( op1.rounding, op1.precision ) ;
		
		mpfr_pow( mpfr::deref(result), mpfr::deref(op1), mpfr::deref(op2), op1.rounding ) ;

		return result ;   
	}  

	mpfr mpfr::sin()  
	{
		mpfr result( rounding, precision ) ;

		mpfr_sin( deref(result), deref(*this), rounding ) ;

		return result ;   
	}

	mpfr mpfr::cos()  
	{
		mpfr result( rounding, precision ) ;

		mpfr_cos( deref(result), deref(*this), rounding ) ;

		return result ;   
	}

	mpfr mpfr::tan()  
	{
		mpfr result( rounding, precision ) ;

		mpfr_tan( deref(result), deref(*this), rounding ) ;

		return result ;   
	}

	mpfr mpfr::pi()  
	{
		mpfr result( rounding, precision ) ;

		mpfr_const_pi( deref(result), rounding ) ;

		return result ;   
	}

	mpfr mpfr::e()  
	{
		mpfr result( rounding, precision ) ;
		mpfr one = "1.0" ;                                   //ALBY test precision

		mpfr_exp( deref(result ), deref(one), rounding ) ;

		return result ;   
	}

	mpfr mpfr::neg()  
	{ 
		return *this * mpfr( "-1.0" ) ;   //ALBY test precision
	}


	mpfr_t& mpfr::deref( const mpfr& mpfr ) // dereference the important part
	{
		return *( mpfr.p->get() ) ;
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

