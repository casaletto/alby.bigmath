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

namespace alby::bigmath 
{
	mpfr_t_wrapper::~mpfr_t_wrapper()
	{
		mpfr_clear( x ) ; 
	}

	mpfr_t_wrapper::mpfr_t_wrapper( mpfr_prec_t precision )
	{
		precision = precision ;

		mpfr_init2 ( x, precision ) ;                
		mpfr_set_ui( x, 0, MPFR_RNDN ) ; 
	}

	mpfr_t* mpfr_t_wrapper::get()
	{
		return &x ;
	}
}