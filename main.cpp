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

void doMpfrMath() ;

int main( void )
{
	try
	{
		std::cout << alby::bigmath::mpfr::version()   << std::endl ;
		std::cout << alby::bigmath::mpfr::random(256) << std::endl ;

		doMpfrMath() ;
	}
	catch( std::exception ex )
	{
		std::cout << ex.what() << std::endl ;
	}
	catch( ... )
	{
		std::cout << "..." << std::endl ;
	}
	
	return 0 ;
}

void doMpfrMath()
{
	std::string str = "3.14" ;

	alby::bigmath::mpfr a ;
	alby::bigmath::mpfr b( "2.0234" ) ;
	alby::bigmath::mpfr c( "8.02345333" ) ;
	alby::bigmath::mpfr d( str ) ;

	auto s = b.toString() ;
	auto aa = a ;
	auto bb = b ;
	auto cc = c ;
	auto dd = d ;

	std::cout << a << std::endl ;
	std::cout << bb << std::endl ;
	std::cout << b << std::endl ;
	std::cout << c << std::endl ;
	std::cout << cc << std::endl ;
	std::cout << d << std::endl ;
	std::cout << dd << std::endl ;


	dd = b ;
	std::cout << b << std::endl ;
	std::cout << dd << std::endl ;

	dd = b + c ;
	std::cout << dd << std::endl ;

	// 2 ^ 8
	// 8 ^ 2
	auto e = b ^ c ;
	auto f = c ^ b ;
	auto g = (c^b) + d ;

	std::cout << e << std::endl ;
	std::cout << f << std::endl ;
	std::cout << g << std::endl ;

	alby::bigmath::mpfr h( "1.0"  ) ;
	auto i = h.sin() ;
	std::cout << "sin " << i << std::endl ;

	i = h.cos() ;
	std::cout << "cos " << i << std::endl ;

	i = h.tan() ;
	std::cout << "tan " << i << std::endl ;

	auto pi = a.pi() ;
	std::cout << pi << std::endl ;

	auto pipi = pi * pi ;
	std::cout << pipi << std::endl ;

	pipi = pi ^ pi ;
	std::cout << pipi << std::endl ;

	auto ee = a.e() ;
	std::cout << ee << std::endl ;

	auto j = pi - ee ;
	std::cout << j << std::endl ;

	j = pi / ee ;
	std::cout << j << std::endl ;

	//auto b1 = b.toMpq() ;

	//mpq_class b1 = (mpq_class) b ;

	//auto z1 = z.to_mpq_class() ;
	//auto a1 = a.to_mpq_class() ;
	//auto b1 = b.to_mpq_class() ;
	
	//std::cout << z1 << std::endl ;
	//std::cout << a1 << std::endl ;
	//std::cout << b1 << std::endl ;
}



