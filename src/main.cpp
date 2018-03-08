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

#include "mpfr_t_wrapper.h"
#include "mpfr.h"

using namespace alby::bigmath ; 

void doMpfrMath1() ;

int main( void )
{
	try
	{
		std::cout << mpfr::version()   << std::endl ;
		//std::cout << mpfr::random(256) << std::endl ; //ALBY fix me

		doMpfrMath1() ;
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

void doMpfrMath1()
{
	mpfr::setPrecision( 50 ) ; // decimal digits of precision
		
	std::string str = "3.14" ;

	mpfr a ;
	mpfr b( "2.0234" ) ;
	mpfr c( "8.02345333" ) ;
	mpfr d( str ) ;

	auto s = b.toString() ;
	auto aa = a ;
	auto bb = b ;
	auto cc = c ;
	auto dd = d ;
	
	std::cout << "..." << std::endl ;
	dd = d ;
	dd = d ;
	dd = d ;
	dd = d ;
	dd = d ;
	dd = d ;
	dd = d ;
	dd = d ;
	dd = d ;
	dd = d ;
	std::cout << "..." << std::endl ;
	
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

	mpfr h( "1.0"  ) ;
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

	auto k = c.neg() ;
	std::cout << k << std::endl ;

	k = k.neg() * b ;
	std::cout << k << std::endl ;

	k = b.inv() ;
	std::cout << k << std::endl ;

	auto l = pi.exp() ;
	std::cout << l << std::endl ;

	auto m = l.log() ;
	std::cout << m << std::endl ;

	auto n = e.log2() ;
	std::cout << n << std::endl ;
	
	auto o = dd.log10() ;
	std::cout << o << std::endl ;

	auto p = d.pow2() ;
	std::cout << p << std::endl ;

	auto q = d.pow10() ;
	std::cout << q << std::endl ;

	auto r = a.e() ^ a.pi() ;
	std::cout << r << std::endl ;

	auto t = r.root( a.pi() ) ;
	std::cout << t << std::endl ;

	r = a.pi() ^ a.e() ; 
	std::cout << r << std::endl ;

	t = r.root( a.e() ) ;
	std::cout << t << std::endl ;

	std::cout << mpfr( "1000.00001" ).root( mpfr( "3.000001" ) ) << std::endl ;
	
	auto u = mpfr( "-FFee.100", 16 ) ;
	std::cout << u << std::endl ;

	u = mpfr( "FFFF.FFFF", 16 ) ;
	std::cout << u << std::endl ;

	auto v = mpfr( "-11111111.01", 2 ) ;
	std::cout << v << std::endl ;

	v = v.abs() ;
	std::cout << v << std::endl ;
	
	v = v.abs() ;
	std::cout << v << std::endl ;

	// test ceil floor trunc

	auto w = q.pi() ;
	std::cout << w << std::endl ;
	std::cout << w.ceil() << std::endl ;
	std::cout << w.floor() << std::endl ;
	std::cout << w.trunc() << std::endl ;
	
	w = q.pi().neg() ;
	std::cout << w << std::endl ;
	std::cout << w.ceil() << std::endl ;
	std::cout << w.floor() << std::endl ;
	std::cout << w.trunc() << std::endl ;

	w = "23.0" ;
	std::cout << w << std::endl ;
	std::cout << w.ceil() << std::endl ;
	std::cout << w.floor() << std::endl ;
	std::cout << w.trunc() << std::endl ;

	w = "-1000.0" ;
	std::cout << w << std::endl ;
	std::cout << w.ceil() << std::endl ;
	std::cout << w.floor() << std::endl ; 
	std::cout << w.trunc() << std::endl ;

	auto x = w + "100.2" ;
	std::cout << x << std::endl ;
	x = x * "100.2" ;
	std::cout << x << std::endl ;
	x = x / "100.2" ;
	std::cout << x << std::endl ;
	x = x - "100.2" ;
	std::cout << x << std::endl ;

	x = "200.01" ;
	auto y = "100.01" ;
	x += y ;
	std::cout << x << std::endl ;
	x += "1.1" ;
	std::cout << x << std::endl ;

	x = "200.01" ;
	y = "100.01" ;
	x -= y ;
	std::cout << x << std::endl ;
	x -= "1.0" ;
	std::cout << x << std::endl ;

	x = "200.01" ;
	y = "100.01" ;
	x *= y ;
	std::cout << x << std::endl ;
	x *= "10.0" ;
	x *= std::string( "20.0" ) ;
	std::cout << x << std::endl ;

	x = "200.01" ;
	y = "100.01" ;
	x /= y ;
	std::cout << x << std::endl ;
	x /= "10.0" ;
	std::cout << x << std::endl ;

	x = "10" ;
	y = "2" ;
	x ^= y ;
	std::cout << x << std::endl ;
	x ^= "0.5" ;
	std::cout << x << std::endl ;


	auto z  = "200.01" + a.pi() ;
	std::cout << z << std::endl ;
	z = "200.01" - a.pi() ;
	std::cout << z << std::endl ;
	z = "200.01" * a.pi() ;
	std::cout << z << std::endl ;
	z = "200.01" / a.pi() ;
	std::cout << z << std::endl ;
	z = "200.01" ^ a.pi() ;
	std::cout << z << std::endl ;

	// 1e10
	mpfr a1( "-1.23E-2" ) ;
	std::cout << a1 << std::endl ;

	auto sum = mpfr( "1.1e1000" ) + mpfr( "1.2e-1000" ) + "1.2" ;
	std::cout << sum << std::endl ;

	// fact
	mpfr a2( "4.49" ) ; // expect 1.2.3.4 = 24
	std::cout << a2.fact() << std::endl ;
	
	a2 = "4.9999" ; // expect 1.2.3.4 = 24
	std::cout << a2.fact() << std::endl ;

	// sqrt
	mpfr a3( "100.01", 3 ) ;
	std::cout << a3.sqrt() << std::endl ;
	
	a3 = "0.0" ;
	std::cout << a3.sqrt() << std::endl ;

	a3 = "-10.0" ;
	std::cout << a3.sqrt() << std::endl ;

	// recurring
	mpfr a4 = mpfr( "1" ) / mpfr( "3") ;
	std::cout << a4 << std::endl ;
	
	a4 = mpfr( "2" ) / mpfr( "3") ;
	std::cout << a4 << std::endl ;

	//mpfr::setPrecision( 30 ) ;
	//ALBY not working !!!
	mpfr a5( "1", 30 ) ;
	a5 = mpfr( "8", 20 ) / mpfr( "9", 20 ) ;
	std::cout << a5 << std::endl ;


/*
	mpfr a3 = "1.23" ;
	mpfr b3 = "10.23" ;
	mpfr c3 = "10.23" ;
	mpfr d3 = "-3.001" ;
	
	std::cout << std::boolalpha << ( a3 < b3 )<< std::endl ;
	std::cout << std::boolalpha << ( a3 > b3 )<< std::endl ;
	std::cout << std::boolalpha << ( a3 <= b3 )<< std::endl ;
	std::cout << std::boolalpha << ( a3 >= b3 )<< std::endl ;
	std::cout << std::boolalpha << ( a3 == b3 )<< std::endl ;
	std::cout << std::boolalpha << ( a3 != b3 )<< std::endl ;
*/	

	
}


