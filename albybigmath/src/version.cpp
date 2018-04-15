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

#include "albybigmath/numberBase.h"
#include "albybigmath/stringhlp.h"
#include "albybigmath/stringcat.h"
#include "albybigmath/numberhlp.h"
#include "albybigmath/version.h"

namespace alby::bigmath 
{
    const std::string version::_version = ALBY_BIGMATH_VERSION  ; 
    
	version::~version() // destr
	{
        // not implemented
	}

	version::version() // constr
	{
        // not implemented
	}

	version&
	version::operator=( const version& rhs ) // =
	{
        // not implemented
		if ( this != &rhs )
		{
		}
		return *this ;
	}

	std::string 
	version::getVersion() 
	{
		return stringcat
		(
			"alby::bigmath version ", _version,			
			"\nGMP version           ", gmp_version,			
			"\nMPFR version          ", mpfr_get_version(),
			"\nMPFR_PREC_MAX         ", MPFR_PREC_MAX,
			"\nMPFR default prec     ", mpfr_get_default_prec() ,
			"\nMPFR min exponent     ", mpfr_get_emin(), 
			"\nMPFR max exponent     ", mpfr_get_emax(), 			
			"\nbits per limb         ", mp_bits_per_limb 			
		) ;
	}

} // ns

