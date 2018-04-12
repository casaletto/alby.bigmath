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

	mpq_t& 
	Q::deref( const Q& q ) // dereference the important part
	{
		return *( q.p->get() ) ;
	}	

	//----------------------------------------------------------------------------------------------------------------------

	void 
	Q::init()
	{
		p = nullptr ;
	}

	void 
	Q::cleanup()
	{
		if ( p != nullptr )
			 delete p ;		
	}

	//----------------------------------------------------------------------------------------------------------------------

	Q::~Q() // destr
	{
		cleanup() ;
	}

	Q::Q() // constr
	{
		init() ;

		p = new mpq_t_wrapper() ; // default 0 
	}

	Q::Q( const Q& rhs ) // copy constr
	{
		init() ;

		*this = rhs ;
	}

	//----------------------------------------------------------------------------------------------------------------------

	Q&
	Q::operator=( const Q& rhs ) // =
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

	Q::Q( long l ) // constr
	{
		init() ;

		p = new mpq_t_wrapper() ;

		mpq_set_si( deref( *this ), l, 1 ) ;

		reduce() ;
	}

	//----------------------------------------------------------------------------------------------------------------------

	Q::Q( const char* str1 ) // constr
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

	Q::Q( const std::string& str1 ) // constr
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

	Q::Q( long l, const char* str1 ) // constr
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

		*this += l ;
	}

	Q::Q( long l, const std::string& str1 ) // constr
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

		*this += l ;
	}

	//----------------------------------------------------------------------------------------------------------------------

	Q::Q( const R& rhs ) // explicit constructor
	{
		init() ;

		auto str = const_cast<R*>( &rhs )->toFraction() ;

		*this = str ;
	}

	//----------------------------------------------------------------------------------------------------------------------

	std::ostream& 
	operator<<( std::ostream& os, const Q& rhs )  
	{  
		os << const_cast<Q*>( &rhs )->toString() ;

		return os ;   
	}  

	Q::operator 
	std::string() 
    {
        return toString() ;
    }

	Q::operator 
	std::string() const
    {
		return const_cast<Q*>( this )->toString() ;
    }

	std::string 
	Q::toString() 
	{
		auto str = p->toString() ;

		return str ;	 
	}

	R 
	Q::toR()
	{
		return R( *this ) ;
	}

	//----------------------------------------------------------------------------------------------------------------------

	void
	Q::reduce()
	{
 		mpq_canonicalize( deref( *this ) ) ;
	}

	std::string 
	Q::numerator()  
	{
		std::string str = *this ;

		std::string numerator, denominator, sign ;

		numberhlp::splitRational( str, numerator, denominator, sign ) ;

		return sign + numerator ;
	}

	std::string 
	Q::denominator() 
	{
		std::string str = *this ;

		std::string numerator, denominator, sign ;

		numberhlp::splitRational( str, numerator, denominator, sign ) ;

		return "+" + denominator ;
	}

	//----------------------------------------------------------------------------------------------------------------------

	Q 
	operator+( const Q& op1, const Q& op2 )  
	{ 
		Q result ;

		mpq_add( 
			Q::deref( result ), 
			Q::deref( op1    ),
			Q::deref( op2    ) ) ;

		return result ;   
	}  

	Q& 
	Q::operator+=( const Q& op2 )  
	{  
		Q result ;

		mpq_add( 
			Q::deref( result ), 
			Q::deref( *this  ),
			Q::deref( op2    ) ) ;

		*this = result ;
		return *this ;   	
	}

	Q 
	operator-( const Q& op1, const Q& op2 )  
	{  
		Q result ;

		mpq_sub( 
			Q::deref( result ), 
			Q::deref( op1    ),
			Q::deref( op2    ) ) ;

		return result ;   
	}  

	Q& 
	Q::operator-=( const Q& op2 )  
	{  
		Q result ;

		mpq_sub( 
			Q::deref( result ), 
			Q::deref( *this  ),
			Q::deref( op2    ) ) ;

		*this = result ;
		return *this ;   	
	}  

	Q 
	operator*( const Q& op1, const Q& op2 )  
	{ 
		Q result ;

		mpq_mul( 
			Q::deref( result ), 
			Q::deref( op1    ),
			Q::deref( op2    ) ) ;

		return result ;   
	}  

	Q& 
	Q::operator*=( const Q& op2 )  
	{  
		Q result ;

		mpq_mul( 
			Q::deref( result ), 
			Q::deref( *this  ),
			Q::deref( op2    ) ) ;

		*this = result ;
		return *this ;   	
	}  

	Q 
	operator/( const Q& op1, const Q& op2 )  
	{  
		Q result ;

		mpq_div( 
			Q::deref( result ), 
			Q::deref( op1    ),
			Q::deref( op2    ) ) ;

		return result ;   
	}  

	Q& 
	Q::operator/=( const Q& op2 )  
	{  
		Q result ;

		mpq_div( 
			Q::deref( result ), 
			Q::deref( *this  ),
			Q::deref( op2    ) ) ;

		*this = result ;
		return *this ;   	
	}  

	//----------------------------------------------------------------------------------------------------------------------

	void
	Q::compare( const Q& op1, const Q& op2, bool& equal, bool& moreThan, bool& lessThan ) 
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
	operator>( const Q& op1, const Q& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		Q::compare( op1, op2, equal, moreThan, lessThan )  ;

		return moreThan ;
	}

	bool 
	operator<( const Q& op1, const Q& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		Q::compare( op1, op2, equal, moreThan, lessThan )  ;

		return lessThan ;
	}

	bool 
	operator>=( const Q& op1, const Q& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		Q::compare( op1, op2, equal, moreThan, lessThan )  ;

		return moreThan || equal ;
	}

	bool 
	operator<=( const Q& op1, const Q& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		Q::compare( op1, op2, equal, moreThan, lessThan )  ;

		return lessThan || equal ;
	}

	bool 
	operator==( const Q& op1, const Q& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		Q::compare( op1, op2, equal, moreThan, lessThan )  ;

		return equal ;
	}

	bool 
	operator!=( const Q& op1, const Q& op2 )  
	{  
		auto equal    = false ;
		auto moreThan = false ;
		auto lessThan = false ;

		Q::compare( op1, op2, equal, moreThan, lessThan )  ;

		return ! equal ;
	}
	
	//----------------------------------------------------------------------------------------------------------------------

	Q 
	Q::neg()  
	{ 
		Q result ;

		mpq_neg( 
			deref( result ), 
			deref( *this  ) ) ;

		return result ;  
	}

	Q 
	Q::inv()  
	{ 
		Q result ;

		mpq_inv( 
			deref( result ), 
			deref( *this  ) ) ;

		return result ;  
	}

	Q 
	Q::abs()  
	{ 
		Q result ;

		mpq_abs( 
			deref( result ), 
			deref( *this  ) ) ;

		return result ;  
	}

} // end ns

