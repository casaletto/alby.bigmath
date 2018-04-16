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

#include "albybigmath/albybigmath.h"

namespace abm = alby::bigmath ; 

int main( void )
{
	try
	{
		std::cout << abm::version::getVersion() << std::endl ;		
	}
	catch( const std::exception& ex )
	{
		std::cout << "EXCEPTION: " << ex.what() << std::endl ;
	}
	catch( ... )
	{
		std::cout << "EXCEPTION: ..." << std::endl ;
	}
	
	return 0 ;	
}

