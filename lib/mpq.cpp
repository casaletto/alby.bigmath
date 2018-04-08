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

#include "./numberBase.h"
#include "./stringhlp.h"
#include "./stringcat.h"
#include "./numberhlp.h"
#include "./mpq_t_wrapper.h"
#include "./mpq.h"

namespace alby::bigmath 
{

	mpq_t& 
	mpq::deref( const mpq& mpq ) // dereference the important part
	{
		return *( mpq.p->get() ) ;
	}	

	//----------------------------------------------------------------------------------------------------------------------

	void 
	mpq::init()
	{
		p = nullptr ;
	}

	void 
	mpq::cleanup()
	{
		if ( p != nullptr )
			 delete p ;		
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpq::~mpq() // destr
	{
		cleanup() ;
	}

	mpq::mpq() // constr
	{
		init() ;

		p = new mpq_t_wrapper() ; // default 0 
	}

	mpq::mpq( const mpq& rhs ) // copy constr
	{
		init() ;

		*this = rhs ;
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpq&
	mpq::operator=( const mpq& rhs ) // =
	{
		if ( this != &rhs )
		{
			cleanup() ;
			init()    ;

			p = new mpq_t_wrapper() ;

			mpq_set( deref( *this ), deref( rhs ) ) ; 
		}
		return *this ;
	}

	mpq::mpq( long l ) // constr
	{
		init() ;

		p = new mpq_t_wrapper() ;

		mpq_set_si( deref( *this ), l, 1 ) ;

		reduce() ;
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpq::mpq( const char* str1 ) // constr
	{
		init() ;

		p = new mpq_t_wrapper() ;

		std::string str = str1 ;
		str = stringhlp::trim( str ) ;
		str = stringhlp::replace( str, " ", "" ) ;

		if ( stringhlp::startsWith( str, "+" ) )
			 str = stringhlp::substr( str, 1 ) ;

		auto rc = mpq_set_str( deref( *this ), str.c_str(), 10 ) ;

		if ( rc == -1 ) throw std::invalid_argument( stringcat( "Bad rational number [", str, "]" ) ) ;

		reduce() ;
	}

	mpq::mpq( const std::string& str1 ) // constr
	{
		init() ;

		p = new mpq_t_wrapper() ;

		std::string str = str1 ;
		str = stringhlp::trim( str ) ;
		str = stringhlp::replace( str, " ", "" ) ;

		if ( stringhlp::startsWith( str, "+" ) )
			 str = stringhlp::substr( str, 1 ) ;

		auto rc = mpq_set_str( deref( *this ), str.c_str(), 10 ) ;

		if ( rc == -1 ) throw std::invalid_argument( stringcat( "Bad rational number [", str, "]" ) ) ;

		reduce() ;
	}

	//----------------------------------------------------------------------------------------------------------------------

	std::ostream& 
	operator<<( std::ostream& os, const mpq& rhs )  
	{  
		os << const_cast<mpq*>( &rhs )->toString() ;

		return os ;   
	}  

	mpq::operator 
	std::string() 
    {
        return toString() ;
    }

	mpq::operator 
	std::string() const
    {
		return const_cast<mpq*>( this )->toString() ;
    }

	std::string 
	mpq::toString() 
	{
		auto str = p->toString() ;

		return str ;	 
	}

	//----------------------------------------------------------------------------------------------------------------------

	void
	mpq::reduce()
	{
 		mpq_canonicalize( deref( *this ) ) ;
	}

	//----------------------------------------------------------------------------------------------------------------------

	mpq 
	operator+( const mpq& op1, const mpq& op2 )  
	{ 
		mpq result ;

		mpq_add( 
			mpq::deref( result ), 
			mpq::deref( op1    ),
			mpq::deref( op2    ) ) ;

		return result ;   
	}  

	mpq& 
	mpq::operator+=( const mpq& op2 )  
	{  
		mpq result ;

		mpq_add( 
			mpq::deref( result ), 
			mpq::deref( *this  ),
			mpq::deref( op2    ) ) ;

		*this = result ;
		return *this ;   	
	}

	mpq 
	operator-( const mpq& op1, const mpq& op2 )  
	{  
		mpq result ;

		mpq_sub( 
			mpq::deref( result ), 
			mpq::deref( op1    ),
			mpq::deref( op2    ) ) ;

		return result ;   
	}  

	mpq& 
	mpq::operator-=( const mpq& op2 )  
	{  
		mpq result ;

		mpq_sub( 
			mpq::deref( result ), 
			mpq::deref( *this  ),
			mpq::deref( op2    ) ) ;

		*this = result ;
		return *this ;   	
	}  

	mpq 
	operator*( const mpq& op1, const mpq& op2 )  
	{ 
		mpq result ;

		mpq_mul( 
			mpq::deref( result ), 
			mpq::deref( op1    ),
			mpq::deref( op2    ) ) ;

		return result ;   
	}  

	mpq& 
	mpq::operator*=( const mpq& op2 )  
	{  
		mpq result ;

		mpq_mul( 
			mpq::deref( result ), 
			mpq::deref( *this  ),
			mpq::deref( op2    ) ) ;

		*this = result ;
		return *this ;   	
	}  

	mpq 
	operator/( const mpq& op1, const mpq& op2 )  
	{  
		mpq result ;

		mpq_div( 
			mpq::deref( result ), 
			mpq::deref( op1    ),
			mpq::deref( op2    ) ) ;

		return result ;   
	}  

	mpq& 
	mpq::operator/=( const mpq& op2 )  
	{  
		mpq result ;

		mpq_div( 
			mpq::deref( result ), 
			mpq::deref( *this  ),
			mpq::deref( op2    ) ) ;

		*this = result ;
		return *this ;   	
	}  

	//----------------------------------------------------------------------------------------------------------------------

	void
	mpq::compare( const mpq& op1, const mpq& op2, bool& equal, bool& moreThan, bool& lessThan ) 
	{
		equal    = false ;
		moreThan = false ;
		lessThan = false ;

		auto result = mpq_cmp( deref(op1), deref(op2) ) ;

		equal    = result == 0 ;
		lessThan = result <  0 ; 
		moreThan = result >  0 ;
	}

	bool 
	operator>( const mpq& op1, const mpq& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		mpq::compare( op1, op2, equal, moreThan, lessThan )  ;

		return moreThan ;
	}

	bool 
	operator<( const mpq& op1, const mpq& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		mpq::compare( op1, op2, equal, moreThan, lessThan )  ;

		return lessThan ;
	}

	bool 
	operator>=( const mpq& op1, const mpq& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		mpq::compare( op1, op2, equal, moreThan, lessThan )  ;

		return moreThan || equal ;
	}

	bool 
	operator<=( const mpq& op1, const mpq& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		mpq::compare( op1, op2, equal, moreThan, lessThan )  ;

		return lessThan || equal ;
	}

	bool 
	operator==( const mpq& op1, const mpq& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		mpq::compare( op1, op2, equal, moreThan, lessThan )  ;

		return equal ;
	}

	bool 
	operator!=( const mpq& op1, const mpq& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		mpq::compare( op1, op2, equal, moreThan, lessThan )  ;

		return ! equal ;
	}
	
	//----------------------------------------------------------------------------------------------------------------------

	mpq 
	mpq::neg()  
	{ 
		mpq result ;

		mpq_neg( 
			deref( result ), 
			deref( *this  ) ) ;

		return result ;  
	}

	mpq 
	mpq::inv()  
	{ 
		mpq result ;

		mpq_inv( 
			deref( result ), 
			deref( *this  ) ) ;

		return result ;  
	}

	mpq 
	mpq::abs()  
	{ 
		mpq result ;

		mpq_abs( 
			deref( result ), 
			deref( *this  ) ) ;

		return result ;  
	}

} // end ns

