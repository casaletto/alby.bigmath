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

namespace alby::bigmath 
{
	unsigned long mpfr_t_wrapper::objCount = 0;

	mpfr_t_wrapper::~mpfr_t_wrapper()
	{
		mpfr_clear( x ) ; 

		//objCount-- ;
		//std::cout << "mpfr_t_wrapper destr " << objCount << std::endl ;
	}

	mpfr_t_wrapper::mpfr_t_wrapper( mpfr_prec_t precision )
	{
		precision = precision ;

		mpfr_init2 ( x, precision ) ;                
		mpfr_set_ui( x, 0, MPFR_RNDN ) ; 

		//objCount++ ;
		//std::cout << "mpfr_t_wrapper constr " << objCount << std::endl ;
	}

	mpfr_t* mpfr_t_wrapper::get()
	{
		return &x ;
	}
}