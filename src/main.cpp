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
#include <mpfr.h>

#include "../lib/stringhlp.h"
#include "../lib/stringcat.h"
#include "../lib/numberParser.h"
#include "../lib/mpfr_t_wrapper.h"
#include "../lib/mpfr.h"

namespace abm = alby::bigmath ; 

void doMpfrMath1() ;
void doMpfrMathNormalise() ;

int main( void )
{
	try
	{
		std::cout << abm::mpfr::version()   << std::endl ;
		
		std::cout << abm::mpfr::randomBytes(256) << std::endl ; //ALBY fix me

		doMpfrMath1() ;
		doMpfrMathNormalise() ;
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
	abm::mpfr::setPrecision( 50 ) ; // decimal digits of precision
		
	std::string str = "3.14" ;

	abm::mpfr a ;
	abm::mpfr b( "2.0234" ) ;
	abm::mpfr c( "8.02345333" ) ;
	abm::mpfr d( str ) ;

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

	abm::mpfr h( "1.0"  ) ;
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

	std::cout << abm::mpfr( "1000.00001" ).root( abm::mpfr( "3.000001" ) ) << std::endl ;
	
	auto u = abm::mpfr( "-FFee.100", 16 ) ;
	std::cout << u << std::endl ;

	u = abm::mpfr( "FFFF.FFFF", 16 ) ;
	std::cout << u << std::endl ;

	auto v = abm::mpfr( "-11111111.01", 2 ) ;
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
	abm::mpfr a1( "-1.23E-2" ) ;
	std::cout << a1 << std::endl ;

	auto sum = abm::mpfr( "1.1e1000" ) + abm::mpfr( "1.2e-1000" ) + "1.2" ;
	std::cout << sum << std::endl ;

	// fact
	abm::mpfr a2( "4.49" ) ; // expect 1.2.3.4 = 24
	std::cout << a2.fact() << std::endl ;
	
	a2 = "4.9999" ; // expect 1.2.3.4 = 24
	std::cout << a2.fact() << std::endl ;

	// sqrt
	abm::mpfr a3( "100.01", 3 ) ;
	std::cout << a3.sqrt() << std::endl ;
	
	a3 = "0.0" ;
	std::cout << a3.sqrt() << std::endl ;

	a3 = "-10.0" ;
	std::cout << a3.sqrt() << std::endl ;

	// recurring
	abm::mpfr a4 = abm::mpfr( "1" ) / abm::mpfr( "3") ;
	std::cout << a4 << std::endl ;
	
	a4 = abm::mpfr( "2" ) / abm::mpfr( "3") ;
	std::cout << a4 << std::endl ;

	abm::mpfr a5( "1" ) ;
	auto fmt = abm::stringcat( "HeLlOwOrLd a5", " = ", a5 ) ;
	std::cout << fmt << std::endl ;
	std::cout << abm::stringhlp::toUpper( fmt  ) << std::endl ;
	std::cout << abm::stringhlp::toLower( fmt  ) << std::endl ;


	std::string str1 = fmt ;
	std::string str2 = a5 ;
	std::cout << a5  << std::endl ;
	std::cout << abm::stringhlp::toUpper( a5   ) << std::endl ;
	std::cout << abm::stringhlp::toUpper( str1 ) << std::endl ;
	std::cout << abm::stringhlp::toUpper( str2 ) << std::endl ;

	std::cout <<  abm::stringcat( "HeLlOwOrLd a5", " = ", a5 ) << std::endl ;
	fmt = abm::stringcat( "HeLlOwOrLd !!! a5", " = ", a5 ) ;
	std::cout <<  fmt << std::endl ;

	auto str3 = abm::stringhlp::printf( 200,  ">>> %s ! %s ! %s ! %s ! %d <<<", "aaaaa", "bbbbb", "cccccc", str1.c_str(), 42 ) ;
	std::cout <<  str3 << std::endl ;

	// left and right
	str = "1234567890abcdefghijklmnopqrstuvwxyz" ; // 10 + 26

	std::cout << "---" << std::endl ;
	std::cout << str << std::endl ;
	std::cout << abm::stringhlp::left( str, 0 ) << std::endl ;
	std::cout << abm::stringhlp::left( str, 1 ) << std::endl ;
	std::cout << abm::stringhlp::left( str, 2 ) << std::endl ;
	std::cout << abm::stringhlp::left( str, 10 ) << std::endl ;
	std::cout << abm::stringhlp::left( str, 35 ) << std::endl ;
	std::cout << abm::stringhlp::left( str, 36 ) << std::endl ;
	std::cout << abm::stringhlp::left( str, 37 ) << std::endl ;

	std::cout << "---" << std::endl ;
	std::cout << str << std::endl ;
	std::cout << abm::stringhlp::right( str, 0 ) << std::endl ;
	std::cout << abm::stringhlp::right( str, 1 ) << std::endl ;
	std::cout << abm::stringhlp::right( str, 2 ) << std::endl ;
	std::cout << abm::stringhlp::right( str, 10 ) << std::endl ;
	std::cout << abm::stringhlp::right( str, 35 ) << std::endl ;
	std::cout << abm::stringhlp::right( str, 36 ) << std::endl ;
	std::cout << abm::stringhlp::right( str, 37 ) << std::endl ;


	//---------------------------------------------------

	abm::mpfr::setPrecision( 44 ) ;

	abm::mpfr a6( "0", 10, 5 ) ; 
	std::cout << a6 << std::endl ; // prec 5

	abm::mpfr a7( "8", 10, 10  ) ; 
	abm::mpfr a8( "9", 10, 8   ) ; 
	
	a6 = a7 / a8 ; 
	std::cout << a6 << std::endl ; // prec 10
	std::cout << a7 << std::endl ; // prec 10
	std::cout << a8 << std::endl ; // prec 8

	abm::mpfr a9( "-12.3456789", 10, 5 ) ;
	std::cout << a9 << std::endl ; // prec 5
	
	auto a10 = a9 ;
	std::cout << a10 << std::endl ; // prec 5

	a10 = a7 ;
	std::cout << a10 << std::endl ; // prec 10

	auto a11 = abm::mpfr( "10.1" ) + abm::mpfr( "23.2" ) ;
	std::cout << a11 << std::endl ; // prec 44

	a11 = a7 + abm::mpfr( "23.2" ) ;
	std::cout << a11 << std::endl ; // prec 10

	a11 = abm::mpfr( "23.2" ) + a7 ;
	std::cout << a11 << std::endl ; // prec 44

	abm::mpfr a12( "-12.3456789", 10, 5 ) ;
	a12 += a11 ;
	std::cout << a12 << std::endl ; // prec 5

	abm::mpfr a13( "-12.3456789"  ) ;
	a13 += a11 ;
	std::cout << a13 << std::endl ; // prec 44

	std::cout << "---" << std::endl ;

	auto a14 = abm::mpfr( "-12.3456789" )  ;
	auto a15 = abm::mpfr( "-12.3456789", 10, 5 ) ;
	auto a16 = a14 + a15 ;
	auto a17 = a15 + a14 ;

	auto a18 = a14 + a14 ;
	auto a19 = a15 + a15 ;
	auto a20 = a14 * "2" ;
	auto a21 = a15 * abm::mpfr( "2",10, 5 )  ;

	std::cout << "a14               " << a14 << std::endl ; // prec ??
	std::cout << "a15               " << a15 << std::endl ; // prec ??
	std::cout << "a16 = a14 + a15 = " << a16 << std::endl ; // prec ?? <---------------
	std::cout << "a17 = a15 + a14 = " << a17 << std::endl ; // prec ??
	//std::cout << "a18 " << a18 << std::endl ; // prec ??
	//std::cout << "a19 " << a19 << std::endl ; // prec ??
	//std::cout << "a20 " << a20 << std::endl ; // prec ??
	//std::cout << "a21 " << a21 << std::endl ; // prec ??

	std::cout << "---" << std::endl ;

	auto a22 = abm::mpfr( "-12.3456789" ) ;
	auto a23 = a14 + a22 ;
	auto a24 = a22 + a14 ;
	std::cout << "a14               " << a14 << std::endl ; // prec ??
	std::cout << "a22               " << a15 << std::endl ; // prec ??
	std::cout << "a23 = a14 + a15 = " << a16 << std::endl ; // prec ?? <---------------
	std::cout << "a24 = a15 + a14 = " << a17 << std::endl ; // prec ??


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

void doMpfrMathNormalise()
{
	//ALBY add sub function

	std::string strScientificNotation ;
	std::string decimalSign  ;
	std::string decimal      ;
	std::string fraction     ; 
	std::string exponentSign ;
	std::string exponent     ;

	auto str = "  -0123456.12345678901234567890e+09876  " ;
	auto b = abm::numberParser::regex( str, decimalSign, decimal, fraction, exponentSign, exponent ) ;
	//std::cout << "[" << str << "] --> " 
	//	<< std::boolalpha << b 
	//	<< "[" << decimalSign << "]" 
	//	<< "[" << decimal << "]" 
	//	<< "[" << fraction << "]" 
	//	<< "[" << exponentSign << "]" 
	//	<< "[" << exponent << "]" 
	//	<< std::endl ;

	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "42" ;
	b = abm::numberParser::regex( str, decimalSign, decimal, fraction, exponentSign, exponent ) ;
	//std::cout << "[" << str << "] --> " 
	//	<< std::boolalpha << b 
	//	<< "[" << decimalSign << "]" 
	//	<< "[" << decimal << "]" 
	//	<< "[" << fraction << "]" 
	//	<< "[" << exponentSign << "]" 
	//	<< "[" << exponent << "]" 
	//	<< std::endl ;

	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "00000042" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "42.00" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "042.0" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "000000.0000000000000000E-00000000" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "000000.00000020000000000E-000000200" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "-0.0000002E20" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "1123560e20" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "-3.14" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "-314.12345e-20" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "-314.12345e20" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "-314.12345e0000" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "-0.12345e10" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "-0.12345e1" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "-0.12345e0" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "-0.12345e-1" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "9e2" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "9.0e2" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "0.9e2" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "0.90e2" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "0.999e2" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "0.0999e2" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "0.00999e2" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "0.000999e2" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	str = "0.0000999e2" ;
	b = abm::numberParser::normalise( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;

	/*
	auto str = "123456.12345678901234567890" ;

	bool b = abm::numberParser::normalise( str, strNormalised ) ;
	std::cout << str << " --> " << std::boolalpha << b << " [" << strNormalised << std::endl ;

	str = "-123456.789e-1234" ;
	b = abm::numberParser::normalise( str, strNormalised ) ;
	std::cout << str << " --> " << std::boolalpha << b << " [" << strNormalised << std::endl ;

	str = "42" ;
	b = abm::numberParser::normalise( str, strNormalised ) ;
	std::cout << str << " --> " << std::boolalpha << b << " [" << strNormalised << std::endl ;

	str = "0.0" ;
	b = abm::numberParser::normalise( str, strNormalised ) ;
	std::cout << str << " --> " << std::boolalpha << b << " [" << strNormalised << std::endl ;

	str = "-0.0" ;
	b = abm::numberParser::normalise( str, strNormalised ) ;
	std::cout << str << " --> " << std::boolalpha << b << " [" << strNormalised << std::endl ;

	str = "-000000123.45678" ;
	b = abm::numberParser::normalise( str, strNormalised ) ;
	std::cout << str << " --> " << std::boolalpha << b << " [" << strNormalised << std::endl ;
	*/
}


