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

#include "./stringhlp.h"
#include "./mpq_t_wrapper.h"

namespace alby::bigmath 
{
	unsigned long mpq_t_wrapper::objectCount = 0 ;

	void (*mpq_t_wrapper::free)( void *, size_t ) = nullptr ;

	mpq_t_wrapper::~mpq_t_wrapper()
	{
		mpq_clear( x ) ; 

		objectCount-- ;
		//std::cout << "mpq_t_wrapper destr " << objectCount << std::endl ;
	}

	mpq_t_wrapper::mpq_t_wrapper()
	{
		mpq_init  ( x ) ;                
		mpq_set_ui( x, 0, 1 ) ; 

		objectCount++ ;
		//std::cout << "mpq_t_wrapper constr " << objectCount << std::endl ; 

		if ( free == nullptr ) 
			 mp_get_memory_functions( nullptr, nullptr, &free ) ;
	}

	mpq_t* 
	mpq_t_wrapper::get()
	{
		return &x ;
	}

	unsigned long 
	mpq_t_wrapper::getObjectCount() 
	{
		return objectCount ;
	}

	std::string 
	mpq_t_wrapper::toString() 
	{
		auto p = mpq_get_str( nullptr, 10, x ) ;
		std::string result = p ;
		free( p, std::strlen( p ) + 1 ) ;

		auto sign = stringhlp::left( result, 1 ) ;

		if ( sign != "-" ) 
		     result = "+" + result ;

		return result ;
	}

} // end ns
