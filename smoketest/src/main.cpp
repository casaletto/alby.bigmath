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

void doMpfrRandom() ;
void doMpfrRandom2() ;
void doMpfrNumberParse() ;
void doMpfrMathRound() ;
void doMpfrMathCompare() ;
void doMpfrMath0() ;
void doMpfrMath1() ;
void doMpfrMathtoCanonical() ;
void doMpfrMathtoSigFig() ;
void roundToSignificantDigits() ;
void example1() ;
void pi_nilakantha() ;
void pi_ramanujan() ;
void pi_nonic() ;
void doMpqMath0() ;
void doMpqMath1() ;
void doMpqMath2() ;

int main( int argc, char** argv )
{
	try
	{
		// just the version number
		if ( argc >= 2 && std::string( argv[1] ) == "--version" )
		{
			std::cout << abm::version::getVersion() << std::endl ;                        
			return 0 ;
		}

		std::cout << abm::version::getVersion( true ) << std::endl ; // all versioln info

		doMpqMath0() ;
		doMpfrMath0() ;
		doMpfrMath1() ;
		doMpfrNumberParse() ;
		doMpfrMathCompare() ;
		doMpfrMathRound() ;
		doMpfrMathtoCanonical() ;
		doMpfrMathtoSigFig() ;
		roundToSignificantDigits() ;
		doMpfrRandom() ;
		doMpfrRandom2() ;
		pi_nilakantha() ;
		pi_ramanujan() ;
		pi_nonic() ;
		example1() ;
		doMpqMath1() ;
		doMpqMath2() ;
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

void doMpqMath2()
{
	std::cout << "---------------------" << std::endl ;

	// 5/49 + 3/21 - 6/25 = 6/1225 
	auto a = abm::Q( "5/49" ) + "3/21" - "6/25" ;
	std::cout << "a = " << a << std::endl ;
	
	// 2 2/3 + 1 1/4 - 5/6 = 37/12
	auto b = abm::Q( 2,"2/3" ) + abm::Q( 1,"1/4" ) - "5/6" ;
	std::cout << "b = " << b << std::endl ;

	// ( 3 - 2/3 ) / 5/6 = 14/5
	auto c = ( abm::Q(3) - "2/3" ) / "5/6" ;
	std::cout << "c = " << c << std::endl ;

	// 1 2/7 / 5 = 9/35
	auto d = abm::Q( 1,"2/7" ) / 5 ;
	std::cout << "d = " << d << std::endl ;

	// 1 2/3 / ( 1 1/4 * 4 2/5 ) = 10/33
	auto e = abm::Q( 1,"2/3" ) / ( abm::Q( 1,"1/4" ) * abm::Q( 4,"2/5" ) ) ;
	std::cout << "e = "             << e << std::endl ;
	std::cout << "e numerator   = " << e.numerator()   << std::endl ;
	std::cout << "e denominator = " << e.denominator() << std::endl ;

	e *= -1 ;	
	std::cout << "e = "             << e << std::endl ;
	std::cout << "e numerator   = " << e.numerator()   << std::endl ;
	std::cout << "e denominator = " << e.denominator() << std::endl ;
}

void doMpqMath1()
{
	abm::R::setSignificantFigures( 10 ) ;
	abm::R::setDebug( false ) ;

	{
		// mixed Q and R math

		std::cout << "---------------------" << std::endl ;
		
		abm::Q a = "1/4" ;
		abm::Q b = "-2 / 3" ;

		auto c = a + b ;
		auto d = a - b ;
		auto e = a * b ;
		auto f = a / b ;

		abm::R aa = a.toR() ;

		abm::R _1 = -1 ;
		abm::R bb = a.toR() * _1 ;

		auto cc = abm::R("100.5") + abm::Q(-10).toR() + abm::Q(90).toR() + abm::Q("1/4").toR()  + abm::Q("-1/8").toR() ; 
		auto dd = abm::R("100.5") - abm::Q(10).toR()  - abm::Q(-90).toR() - abm::Q("-1/4").toR() - abm::Q("1/8").toR()  ; 
		
		auto ee = abm::Q(-10).toR() + abm::Q(90).toR()  + abm::Q("1/4").toR()  + abm::Q("-1/8").toR() + abm::R("100.5")  ; 
		auto ff = abm::Q(-10).toR() - abm::Q(-90).toR() - abm::Q("-1/4").toR() - abm::Q("1/8").toR()  - abm::R("-100.5") ; 

		std::cout << "a  =         " << a  << std::endl ;
		std::cout << "aa =         " << aa << std::endl ;
		std::cout << "b  =         " << b  << std::endl ;
		std::cout << "c  = a + b = " << c  << std::endl ;
		std::cout << "d  = a - b = " << d  << std::endl ;
		std::cout << "e  = a * b = " << e  << std::endl ;
		std::cout << "f  = a / b = " << f  << std::endl ;
		std::cout << "bb =         " << bb << std::endl ;
		std::cout << "cc =         " << cc << std::endl ;
		std::cout << "dd =         " << dd << std::endl ;
		std::cout << "ee =         " << ee << std::endl ;
		std::cout << "ff =         " << ff << std::endl ;
	}
	{
		std::cout << "---------------------" << std::endl ;
		
		auto a = abm::R( "100.5" ) ;
		auto b = abm::Q( -10 ) ;
		auto c = abm::Q( 90 )  ;
		auto d = abm::Q( "1/4" ) ; 
		auto e = abm::Q( "-1/8" )  ; 

		auto f = a + b.toR() + c.toR() + d.toR() + e.toR() ;

		std::cout << "a = " << a << std::endl ;
		std::cout << "b = " << b << std::endl ;
		std::cout << "c = " << c << std::endl ;
		std::cout << "d = " << d << std::endl ;
		std::cout << "e = " << e << std::endl ;
		std::cout << "f = " << f << std::endl ;
	}

	{
		// cross conversions between R and Q
		// Q(R)
		// R(Q)
		// R = Q ;
		// Q = R ;

		std::cout << "---------------------" << std::endl ;

		abm::Q q1 = "22/7"  ;
		abm::R r1 = "3.14" ;

		auto q2 = abm::Q( r1 ) ;
		auto r2 = abm::R( q2 )  ;

		abm::Q q3 ;
		abm::R r3 ;
		
		q3 = r2.toQ() ;
		r3 = q2.toR() ;

		std::cout << "q1 = " << q1  << std::endl ;
		std::cout << "r1 = " << r1  << std::endl ;
		std::cout << "q2 = " << q2  << std::endl ;
		std::cout << "r2 = " << r2  << std::endl ;
		std::cout << "q3 = " << q3  << std::endl ;
		std::cout << "r3 = " << r3  << std::endl ;
	}

	{
		// pythagoras, mixed Q and R math

		std::cout << "---------------------" << std::endl ;

		abm::R::setSignificantFigures( 15 ) ;
		abm::R::setDebug( false ) ;
		
		abm::Q a = 3 ;
		abm::Q b = 4 ;

		auto temp = a*a + b*b ;
		auto c    = temp.toR().sqrt().toQ() ; 

		std::cout << "a = " << a      << std::endl ;
		std::cout << "b = " << b       << std::endl ;
		std::cout << "c = " << c       << std::endl ;
		std::cout << "c = " << c.toR() << std::endl ;
	}

	{
		// pythagoras, mixed Q and R math

		std::cout << "---------------------" << std::endl ;

		abm::R::setSignificantFigures( 15 ) ;
		abm::R::setDebug( false ) ;
		
		auto a = abm::Q( 3, "1/100" ) ;
		auto b = abm::Q( 4, "1/100" ) ;

		auto temp = a*a + b*b ;
		auto c    = temp.toR().sqrt().toQ() ; 

		std::cout << "a = " << a      << std::endl ;
		std::cout << "b = " << b       << std::endl ;
		std::cout << "c = " << c       << std::endl ;
		std::cout << "c = " << c.toR() << std::endl ;
	}

	{
		std::cout << "---------------------" << std::endl ;

		// more Q and R math
		// R = r * q, r = q* r, q = q *r, q = r* q

		abm::Q q1 = "22/7" ;
		abm::R r1 = "3.14" ;

		abm::R r2 = r1       * q1.toR() ;
		abm::R r3 = q1.toR() * r1       ;

		abm::Q q2 = r1.toQ() * q1       ;
		abm::Q q3 = q1       * r1.toQ() ;

		std::cout << "q1 = " << q1 << std::endl ;
		std::cout << "r1 = " << r1 << std::endl ;
		std::cout << "q2 = " << q2 << std::endl ;
		std::cout << "q3 = " << q3 << std::endl ;
		std::cout << "r2 = " << r2 << std::endl ;
		std::cout << "r3 = " << r3 << std::endl ;
	}
}

void doMpqMath0()
{
	{
		abm::mpq_t_wrapper a, b, c ;

		std::cout << a.toString() << std::endl ;
		std::cout << b.toString() << std::endl ;
		std::cout << c.toString() << std::endl ;
		std::cout << a.toString() << std::endl ;
		std::cout << b.toString() << std::endl ;
		std::cout << c.toString() << std::endl ;
	}

	{
		std::cout << "---------------------" << std::endl ;
		
		abm::Q a = "1/4" ;
		abm::Q b = "-2 / 3" ;

		auto c = a + b ;
		auto d = a - b ;
		auto e = a * b ;
		auto f = a / b ;

		std::cout << "a = " << a << std::endl ;
		std::cout << "b = " << b << std::endl ;
		std::cout << "c = " << c << std::endl ;
		std::cout << "d = " << d << std::endl ;
		std::cout << "e = " << e << std::endl ;
		std::cout << "f = " << f << std::endl ;
	}

	{
		std::cout << "---------------------" << std::endl ;
		
		abm::Q a = "+1/4" ;
		abm::Q b = "-2 / 3" ;

		auto c = a + b ;
		auto d = a - b ;
		auto e = a * b ;
		auto f = a / b ;

		std::cout << "a = " << a << std::endl ;
		std::cout << "b = " << b << std::endl ;
		std::cout << "c = " << c << std::endl ;
		std::cout << "d = " << d << std::endl ;
		std::cout << "e = " << e << std::endl ;
		std::cout << "f = " << f << std::endl ;
	}

	{
		std::cout << "---------------------" << std::endl ;
		
		abm::Q a = "  2 / 8   " ;
		abm::Q b = " -  2 0 / 3    0 " ;

		auto c = a + b ;
		auto d = a - b ;
		auto e = a * b ;
		auto f = a / b ;

		std::cout << "a = " << a << std::endl ;
		std::cout << "b = " << b << std::endl ;
		std::cout << "c = " << c << std::endl ;
		std::cout << "d = " << d << std::endl ;
		std::cout << "e = " << e << std::endl ;
		std::cout << "f = " << f << std::endl ;
		std::cout << "a + a = " << a + a << std::endl ;
	}

	{
		std::cout << "---------------------" << std::endl ;

		abm::Q a = std::string( "  2 / 8   " ) ;
		abm::Q b = std::string( "      -  2    0   /    3    0     " ) ;

		std::cout << "a = " << a << std::endl ;
		std::cout << "b = " << b << std::endl ;

		a += b ;
		b -= a ;

		std::cout << "a = " << a << std::endl ;
		std::cout << "b = " << b << std::endl ;

		a *= b ;
		b /= a ;

		std::cout << "a = " << a << std::endl ;
		std::cout << "b = " << b << std::endl ;

		auto f = a / b ;
		std::cout << "f     = " << f << std::endl ;
		std::cout << "f inv = " << f.inv() << std::endl ;
		std::cout << "f neg = " << f.neg() << std::endl ;
		std::cout << "f abs = " << f.abs() << std::endl ;

		std::string str = f ;
		std::cout << "f     = " << str << std::endl ;
		std::cout << "f     = " << f.toString() << std::endl ;
	}

	{
		std::cout << "---------------------" << std::endl ;

		abm::Q a = -34 ;
		std::cout << "a = " << a << std::endl ;

		abm::Q b = -0 ;
		std::cout << "b = " << b << std::endl ;

		abm::Q c = 10000 ;
		std::cout << "c = " << c << std::endl ;

		abm::Q d = -10000 ;
		std::cout << "d = " << d << std::endl ;

		a = c ;
		std::cout << "a = " << a << std::endl ;

		auto e = d ;
		std::cout << "e = " << e << std::endl ;
	}

	{
		std::cout << "---------------------" << std::endl ;

		abm::Q a = -34 ;
		std::cout << "a = " << a << std::endl ;

		abm::Q b = 400 ;
		std::cout << "b = " << b << std::endl ;

		std::cout << "a == b --> " << std::boolalpha << (a == b) << std::endl ;
		std::cout << "a != b --> " << std::boolalpha << (a != b) << std::endl ;
		std::cout << "a <  b --> " << std::boolalpha << (a <  b) << std::endl ;
		std::cout << "a <= b --> " << std::boolalpha << (a <= b) << std::endl ;
		std::cout << "a >  b --> " << std::boolalpha << (a >  b) << std::endl ;
		std::cout << "a >= b --> " << std::boolalpha << (a >= b) << std::endl ;
	}

	{
		std::cout << "---------------------" << std::endl ;

		abm::Q a = 34 ;
		std::cout << "a = " << a << std::endl ;

		abm::Q b = -400 ;
		std::cout << "b = " << b << std::endl ;

		std::cout << "a == b --> " << std::boolalpha << (a == b) << std::endl ;
		std::cout << "a != b --> " << std::boolalpha << (a != b) << std::endl ;
		std::cout << "a <  b --> " << std::boolalpha << (a <  b) << std::endl ;
		std::cout << "a <= b --> " << std::boolalpha << (a <= b) << std::endl ;
		std::cout << "a >  b --> " << std::boolalpha << (a >  b) << std::endl ;
		std::cout << "a >= b --> " << std::boolalpha << (a >= b) << std::endl ;
	}

	{
		std::cout << "---------------------" << std::endl ;

		abm::Q a = -400 ;
		std::cout << "a = " << a << std::endl ;

		abm::Q b = -400 ;
		std::cout << "b = " << b << std::endl ;

		std::cout << "a == b --> " << std::boolalpha << (a == b) << std::endl ;
		std::cout << "a != b --> " << std::boolalpha << (a != b) << std::endl ;
		std::cout << "a <  b --> " << std::boolalpha << (a <  b) << std::endl ;
		std::cout << "a <= b --> " << std::boolalpha << (a <= b) << std::endl ;
		std::cout << "a >  b --> " << std::boolalpha << (a >  b) << std::endl ;
		std::cout << "a >= b --> " << std::boolalpha << (a >= b) << std::endl ;
	}
	

}

void pi_nilakantha()
{
	// π = 3 + 4/(2*3*4) - 4/(4*5*6) + 4/(6*7*8) - 4/(8*9*10) + 4/(10*11*12) - 4/(12*13*14) ...

	// +3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384...
	// +3.14159265358979323 64626553832
	// 17 dp 
	// 500 000 iterations

	//+3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384...
    //+3.14159265358979323846 064338447950250419722939937490582349494131430791840727618900271949345354228126667
	// 20 dp 
	// 5 000 000 iterations

	abm::R::setSignificantFigures( 15 ) ;
	abm::R::setDebug( false ) ;

	auto pi = abm::pi::nilakantha( 5000 ) ;

	std::cout << pi << std::endl ;
}

void pi_ramanujan()
{
	// n = 0, 23 dp
	// pi = +3.14159265358979323846264

	// n = 5, 84 dp
	// pi = +3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628

	// n = 10, 155 dp
	// pi = +3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111

	// n = 100, 1432 dp
	// pi = +3.1415926535897932384626433..............42699227967823547816360093417216412199245 

	// n = 1000, dp = 14195
	// pi = +3.1415926535897932384626433.....228435988341003583854238973542439564755568409522484455413

	// n = 10000, dp = 141830
	// pi = +3.1415926535897932384626433.....9605721400330661597939815697061366098396405520287669991722547240

	abm::R::setSignificantFigures( 1500 ) ;
	abm::R::setDebug( false ) ;

	auto pi = abm::pi::ramanujan( 100 ) ;

	std::cout << pi << std::endl ;
}

void pi_nonic()
{
	// n = 0, dp = 0
	// pi = +3.0

	// n = 1, dp = 0
	// pi = +3.0

	// n = 2, dp = 21
	// pi = +3.141592653589793238462

	// n = 3, dp = 216
	// pi = +3.141592653589793238462...81117450284102701938521105559644622948954930381964428810975665933

	// n = 4, dp = 1984
	// pi = +3.141592653589793238462...50471237137869609563643719172874677646575739624138908658326459958

	// n = 5, dp = 17896
	// pi = +3.141592653589793238462...560011250184335607361222765949278393

	// n = 6, dp = 161 123
	// pi = +3.141592653589793238462...0712427360675833767835191012510994437030462

	// n = 7, dp > 1 000 000
	// pi = +3.141592653589793238462...696552087542450598956787961303311646283996346460422090106105779458151

	abm::R::setSignificantFigures( 1985 ) ;
	abm::R::setDebug( false ) ;

	auto pi = abm::pi::nonic( 4 ) ;

	std::cout << pi << std::endl ;
}

void doMpfrRandom2()
{
	abm::R::setSignificantFigures( 14 ) ;
	abm::R::setDebug( false ) ;

	abm::random rnd ;

	for ( auto i = 1 ; i <= 10000 ; i++ )
	{
		if ( i % 1000 == 0 )
			 std::this_thread::sleep_for( std::chrono::milliseconds(1) ) ; // sleep
		
		auto r = rnd.next().roundToDecimalPlaces( 1 ) ;

		auto d1 = r * abm::R( "2147483647" ) ;
		d1 = d1.roundToDecimalPlaces( 1 ) ;
		std::string str1 = d1 ;

		auto d2 = std::stod( r ) * 2147483647.0 ;
		auto str2 = abm::stringhlp::printf( 100, "+%.1f", d2 ) ;

		if ( str1 != str2 ) 
		{
			std::cout << r << "\t\t\t\t===> " << str1 << " === " << str2 << std::endl ;
		    exit( 1 ) ;
		}
	}
}

void doMpfrRandom()
{
	abm::R::setSignificantFigures( 55 ) ;
	abm::R::setDebug( true ) ;

	{
		abm::random rnd ;
		std::cout << "\nseed1 = " << rnd.getSeed() << std::endl ;
		
		for ( auto i = 1 ; i <= 10 ; i++ )
		{
			auto x = rnd.next() ;
			std::cout << x << std::endl ;
		}
		for ( auto i = 1 ; i <= 10 ; i++ )
		{
			auto str = rnd.hexBytes( i ) ;
			std::cout << str << std::endl ;
		}	
		for ( auto i = 1 ; i <= 10 ; i++ )
		{
			auto str = rnd.nanosecondsSinceEpoch() ;
			std::cout << str << std::endl ;
		}	
	}

	{
		abm::random rnd ;
		std::cout << "\nseed2 = " << rnd.getSeed() << std::endl ;

		std::map<unsigned long, unsigned long> map ;

		for ( auto i = 1 ; i <= 6000 ; i++ )
		{
			//std::this_thread::sleep_for( std::chrono::milliseconds(1) ) ; // sleep

			auto x = rnd.nextInteger( 6 ) ;
		
			if ( x < 1 ) exit( 1 ) ;
			if ( x > 6 ) exit( 1 ) ;			
		
			map[x]++ ;
		}	
	
		for ( auto const &i : map )
			  std::cout << i.first << " = " << i.second <<std::endl ;
	}

	{
		abm::random rnd( 10, abm::random::hexBytes( 3 ), abm::numberBase::_16 ) ;
		std::cout << "\nseed3 = " << rnd.getSeed() << std::endl ;

		for ( auto i = 1 ; i <= 10 ; i++ )
		{
			auto x = rnd.next() ;
			std::cout << x << std::endl ;
		}
	}
	
}

void doMpfrNumberParse()
{
	std::string decimalSign  ;
	std::string decimal      ; 
	std::string fraction     ; 
	std::string exponentSign ;
	std::string exponent     ;

	std::vector<std::string> rng =
	{
		"3.14e34",
		"-3.14e34",
		"+3.14e34",
		"3.14e+34",
		"-3.14e+34",
		"+3.14e+34",
		"3.14e-34",
		"-3.14e-34",
		"+3.14e-34",
		"3.14e0",
		"-3.14e0",
		"+3.14e0",
		"3.14e+0",
		"-3.14e+0",
		"+3.14e+0",
		"3.14e-0",
		"-3.14e-0",
		"+3.14e-0",
		"3.14",
		"-3.14",
		"+3.14",
		"3",
		"-3",
		"+3",
		"0",
		"-0",
		"+0"
		"0000000000.0000000000000",
		"-000000000000.0000000",
		"+0000000000.0000000000",
		"0000000000.0000000000000e0000000",
		"-000000000000.0000000e000000000000",
		"+0000000000.0000000000e00000000000",
		
		"00000000001234560000000.000000000076543200000000e0000000000089765000000",
		"+00000000001234560000000.000000000076543200000000e-0000000000089765000000",
		"-00000000001234560000000.000000000076543200000000e+0000000000089765000000",

		"00000000001234560000000.000000000076543200000000",
		"+00000000001234560000000.000000000076543200000000",
		"-00000000001234560000000.000000000076543200000000",

		"0",
		"000",
		"00000000",
		"00000e000000000000",
	} ;

	for ( auto& str : rng )
	{
		auto b = abm::numberhlp::regex2( str, decimalSign, decimal, fraction, exponentSign, exponent ) ;
		std::cout << abm::stringcat( "[", str, "]\t\t\t\t--> ", (bool) b, " -->     {", decimalSign , "}  [", decimal, "].[", fraction, "]  E  {", exponentSign, "}  [", exponent, "]" ) <<  std::endl ;
	} ;

	rng =
	{
		"",
		"fred",
		"12345.678.",
		"12345.678.1",
		"12345....678.",
		"12345....678....",
		".0",
		".",
		"34e45.44",
		"34e45.....44",
		"   232356wq ",
		"+3.14ee-0",
		".1232",
		".1232e232.22222",
	} ;

	for ( auto& str : rng )
	{
		auto b = abm::numberhlp::regex2( str, decimalSign, decimal, fraction, exponentSign, exponent ) ;
		std::cout << abm::stringcat( "[", str, "]\t\t\t\t--> ", (bool) b, " -->     {", decimalSign , "}  [", decimal, "].[", fraction, "]  E  {", exponentSign, "}  [", exponent, "]" ) <<  std::endl ;
	} ;

}

void example1()
{
	abm::R::setSignificantFigures( 22 ) ;
	abm::R::setDebug( false ) ; 

	auto a = abm::R( "1.2e10"  ) ;
	auto b = abm::R( "3.4"     ) ;
	auto c = abm::R( "5.6e-10" ) ;	

	auto sum = a + b + c ;

	std::cout 
		<< a << " + " 
		<< b << " + " 
		<< c << std::endl << std::endl 
		<< "= " << sum << std::endl << std::endl 
		<< "= " << sum.toScientificNotation() << std::endl << std::endl ;

	abm::R::setSignificantFigures( 2002 ) ;

	a = "1.2e1000"  ;
	b = "3.4"       ;
	c = "5.6e-1000" ;	

	sum = a + b + c ;

	std::cout 
		<< a.toScientificNotation() << " + " 
		<< b << " + " 
		<< c.toScientificNotation() << std::endl << std::endl 
		<< "= " << sum << std::endl << std::endl  
		<< "= " << sum.toScientificNotation()  << std::endl ;
}

void doMpfrMath0()
{
	abm::R::setDebug( true )   ; 
	abm::R::setSignificantFigures( 10 ) ; 

	{
		std::cout << "-----------------------------------------------------------------" << std::endl ;
		abm::R a( "2.0234" , 20 ) ;
		abm::R b( "3.12345", 20 ) ;

		std::cout << a << ", " << a.toFraction() << std::endl ;
		std::cout << b << ", " << b.toFraction() << std::endl ;
		std::cout << a + b << ", " << (a+ b).toFraction() << std::endl ;
		std::cout << b + a << std::endl ;

		b += a  ; 
		std::cout << b << ", " << b.toFraction() << std::endl ;

		std::cout << "-----------------------------------------------------------------" << std::endl ;
		abm::R c( "2.0234" , 20 ) ;
		abm::R d( "3.12345", 30 ) ;

		std::cout << "c      = " << c << std::endl ;
		std::cout << "d      = " << d << std::endl ;
		std::cout << "c + d  = " << (c + d) << ", " << (c + d).toFraction() <<  std::endl ;
		std::cout << "d + c  = " << (d + c) << ", " << (d + c).toFraction() << std::endl ;

		c += d  ; 
		d += c  ; 
		std::cout << "c      = " << c << ", " << c.toFraction() << std::endl ;
		std::cout << "d      = " << d << ", " << d.toFraction() << std::endl ;

		abm::R e( c, 3 ) ;
		abm::R f( d, 3 ) ;
		std::cout << "e      = " << e << ", " << e.toFraction() << std::endl ;
		std::cout << "f      = " << f << ", " << f.toFraction() << std::endl ;

		abm::R g( c, 2 ) ;
		abm::R h( d, 2 ) ;
		std::cout << "g      = " << g << ", " << g.toFraction() <<  std::endl ;
		std::cout << "h      = " << h << ", " << h.toFraction() << std::endl ;
		std::cout << "==================================================================" << std::endl ;
	}

	{
		abm::R i( "2.0234",  20 ) ;
		abm::R j( "3.12345", 20 ) ;

		std::cout << "i      = " << i << std::endl ;
		std::cout << "j      = " << j << std::endl ;
		std::cout << "i - j  = " << (i - j) << ", " << (i - j).toFraction() << std::endl ;
		std::cout << "j - i  = " << (j - i) << ", " << (j - i).toFraction() << std::endl ;

		i -= j  ; 
		j -= i  ; 
		std::cout << "i      = " << i << ", " << i.toFraction() << std::endl ;
		std::cout << "j      = " << j << ", " << j.toFraction() << std::endl ;
		std::cout << "-----------------------------------------------------------------" << std::endl ;

		i = abm::R( "2.0234",  20 ) ;
		j = abm::R( "3.12345", 30 ) ;

		std::cout << "i      = " << i << std::endl ;
		std::cout << "j      = " << j << std::endl ;
		std::cout << "i - j  = " << (i - j) << ", " << (i - j).toFraction() << std::endl ;
		std::cout << "j - i  = " << (j - i) << ", " << (j - i).toFraction() << std::endl ;

		i -= j  ; 
		j -= i  ; 
		std::cout << "i      = " << i << ", " << i.toFraction() << std::endl ;
		std::cout << "j      = " << j << ", " << j.toFraction() << std::endl ;
		std::cout << "==================================================================" << std::endl ;
	}

	{
		abm::R k( "2.0234" , 20 ) ;
		abm::R l( "3.12345", 20 ) ;

		std::cout << "k      = " << k << std::endl ;
		std::cout << "l      = " << l << std::endl ;
		std::cout << "k * l  = " << (k * l) << ", " << (k * l).toFraction() << std::endl ;
		std::cout << "l * k  = " << (l * k) << ", " << (l * k).toFraction() << std::endl ;

		k *= l  ; 
		l *= k  ; 
		std::cout << "l      = " << l << ", " << l.toFraction() << std::endl ;
		std::cout << "k      = " << k << ", " << k.toFraction() << std::endl ;
		std::cout << "-----------------------------------------------------------------" << std::endl ;

		k = abm::R( "2.0234",  20 ) ;
		l = abm::R( "3.12345", 30 ) ;

		std::cout << "k      = " << k << std::endl ;
		std::cout << "l      = " << l << std::endl ;
		std::cout << "k * l  = " << (k * l) << ", " << (k * l).toFraction() << std::endl ;
		std::cout << "l * k  = " << (l * k) << ", " << (l * k).toFraction() << std::endl ;

		k *= l  ; 
		l *= k  ; 
		std::cout << "l      = " << l << ", " << l.toFraction() << std::endl ;
		std::cout << "k      = " << k << ", " << k.toFraction() << std::endl ;
		std::cout << "==================================================================" << std::endl ;
	}

	{
		abm::R k( "2.0234" , 20 ) ;
		abm::R l( "3.12345", 20 ) ;

		std::cout << "k      = " << k << std::endl ;
		std::cout << "l      = " << l << std::endl ;
		std::cout << "k / l  = " << (k / l) << ", " << (k / l).toFraction() << std::endl ;
		std::cout << "l / k  = " << (l / k) << ", " << (l / k).toFraction() << std::endl ;

		k /= l  ; 
		l /= k  ; 
		std::cout << "k      = " << k << ", " << k.toFraction() << std::endl ;
		std::cout << "l      = " << l << ", " << l.toFraction() << std::endl ;
		std::cout << "-----------------------------------------------------------------" << std::endl ;

		k = abm::R( "2.0234",  20 ) ;
		l = abm::R( "3.12345", 30 ) ;

		std::cout << "k      = " << k << std::endl ;
		std::cout << "l      = " << l << std::endl ;
		std::cout << "k / l  = " << (k / l) << ", " << (k / l).toFraction() << std::endl ;
		std::cout << "l / k  = " << (l / k) << ", " << (l / k).toFraction() << std::endl ;

		k /= l  ; 
		l /= k  ; 
		std::cout << "k      = " << k << ", " << k.toFraction() << std::endl ;
		std::cout << "l      = " << l << ", " << l.toFraction() << std::endl ;

		std::cout << "==================================================================" << std::endl ;
	}

	{
		abm::R k( "2.0234" , 20 ) ;
		abm::R l( "3.12345", 20 ) ;

		std::cout << "k      = " << k << std::endl ;
		std::cout << "l      = " << l << std::endl ;
		std::cout << "k ^ l  = " << (k ^ l) << ", " << (k ^ l).toFraction() << std::endl ;
		std::cout << "l ^ k  = " << (l ^ k) << ", " << (l ^ k).toFraction() << std::endl ;

		k ^= l  ; 
		l ^= k  ; 
		std::cout << "k      = " << k << ", " << k.toFraction() << std::endl ;
		std::cout << "l      = " << l << ", " << l.toFraction() << std::endl ;
		std::cout << "-----------------------------------------------------------------" << std::endl ;

		k = abm::R( "2.0234",  20 ) ;
		l = abm::R( "3.12345", 30 ) ;

		std::cout << "k      = " << k << std::endl ;
		std::cout << "l      = " << l << std::endl ;
		std::cout << "k ^ l  = " << (k ^ l) << ", " << (k ^ l).toFraction() << std::endl ;
		std::cout << "l ^ k  = " << (l ^ k) << ", " << (l ^ k).toFraction() << std::endl ;

		k ^= l  ; 
		l ^= k  ; 
		std::cout << "k      = " << k << ", " << k.toFraction() << std::endl ;
		std::cout << "l      = " << l << ", " << l.toFraction() << std::endl ;

		std::cout << "==================================================================" << std::endl ;
	}

	{
		abm::R k( "125.0234", 20 ) ;
		abm::R l( "3.12345" , 20 ) ;

		std::cout << "k            = " << k << std::endl ;
		std::cout << "l            = " << l << std::endl ;
		std::cout << "k root l     = " << k.root(l) << ", " << k.root(l).toFraction() << std::endl ;
		std::cout << "l root k     = " << l.root(k) << ", " << l.root(k).toFraction() << std::endl ;

		auto x1 = k.root(l) ^ l ;
		auto y1 = l.root(k) ^ k ;

		std::cout << "k root l ^ l = " << x1 << ", " << x1.toFraction() << std::endl ;
		std::cout << "l root k ^ k = " << y1 << ", " << y1.toFraction() << std::endl ;		
		std::cout << "-----------------------------------------------------------------" << std::endl ;

		k = abm::R( "125.0234", 20 ) ;
		l = abm::R( "3.12345" , 10 ) ; 

		std::cout << "k            = " << k << std::endl ;
		std::cout << "l            = " << l << std::endl ;
		std::cout << "k root l     = " << k.root(l) << ", " << k.root(l).toFraction() << std::endl ;
		std::cout << "l root k     = " << l.root(k) << ", " << l.root(k).toFraction() << std::endl ;

		x1 = k.root(l) ^ l ;
		y1 = l.root(k) ^ k ;

		std::cout << "k root l ^ l = " << x1 << ", " << x1.toFraction() << std::endl ;
		std::cout << "l root k ^ k = " << y1 << ", " << y1.toFraction() << std::endl ;		
		std::cout << "-----------------------------------------------------------------" << std::endl ;

		k = abm::R( "125.0234", 10 ) ;
		l = abm::R( "3.12345" , 20 ) ; 

		std::cout << "k            = " << k << std::endl ;
		std::cout << "l            = " << l << std::endl ;
		std::cout << "k root l     = " << k.root(l) << ", " << k.root(l).toFraction() << std::endl ;
		std::cout << "l root k     = " << l.root(k) << ", " << l.root(k).toFraction() << std::endl ;

		x1 = k.root(l) ^ l ;
		y1 = l.root(k) ^ k ;

		std::cout << "k root l ^ l = " << x1 << ", " << x1.toFraction() << std::endl ;
		std::cout << "l root k ^ k = " << y1 << ", " << y1.toFraction() << std::endl ;		
		std::cout << "==================================================================" << std::endl ;
	}

}

void doMpfrMathCompare() 
{
	abm::R::setDebug( true )   ; 
	abm::R::setSignificantFigures( 10 ) ; 

	abm::R a( "2.0234" ) ; 
	abm::R b( "3.1234" ) ;
	abm::R c( "3.1234" ) ;
	abm::R d( "2.0234" ) ;
	abm::R e( "-3.1234" ) ;
	abm::R f( "0.00000000000000000009123456787" ) ;
	abm::R g( "0.00000000000000000009123456789" ) ;

	abm::R h( "1.2345678E-34", 8 ) ;
	abm::R i( "1.2345679E-50", 10 ) ;

	abm::R j( "9.2345678E-200001", 10 ) ; // smaller
	abm::R k( "1.2345679E-200000", 10 ) ; // bigger

	std::cout << "-----------------------------------------------------------------" << std::endl ;
	std::cout << a << "\t==\t" << b << "\t[" << std::boolalpha << ( a == b ) <<  std::endl ;
	std::cout << a << "\t!=\t" << b << "\t[" << std::boolalpha << ( a != b ) <<  std::endl ;
	std::cout << a << "\t> \t" << b << "\t[" << std::boolalpha << ( a >  b ) <<  std::endl ;
	std::cout << a << "\t>=\t" << b << "\t[" << std::boolalpha << ( a >= b ) <<  std::endl ;
	std::cout << a << "\t< \t" << b << "\t[" << std::boolalpha << ( a <  b ) <<  std::endl ;
	std::cout << a << "\t<=\t" << b << "\t[" << std::boolalpha << ( a <= b ) <<  std::endl ;

	std::cout << "-----------------------------------------------------------------" << std::endl ;
	std::cout << b << "\t==\t" << b << "\t[" << std::boolalpha << ( b == b ) <<  std::endl ;
	std::cout << b << "\t!=\t" << b << "\t[" << std::boolalpha << ( b != b ) <<  std::endl ;
	std::cout << b << "\t> \t" << b << "\t[" << std::boolalpha << ( b >  b ) <<  std::endl ;
	std::cout << b << "\t>=\t" << b << "\t[" << std::boolalpha << ( b >= b ) <<  std::endl ;
	std::cout << b << "\t< \t" << b << "\t[" << std::boolalpha << ( b <  b ) <<  std::endl ;
	std::cout << b << "\t<=\t" << b << "\t[" << std::boolalpha << ( b <= b ) <<  std::endl ;

	std::cout << "-----------------------------------------------------------------" << std::endl ;	
	std::cout << h.toScientificNotation() << "\t==\t" << i.toScientificNotation() << "\t[" << std::boolalpha << ( h == i ) <<  std::endl ;
	std::cout << h.toScientificNotation() << "\t!=\t" << i.toScientificNotation() << "\t[" << std::boolalpha << ( h != i ) <<  std::endl ;
	std::cout << h.toScientificNotation() << "\t> \t" << i.toScientificNotation() << "\t[" << std::boolalpha << ( h >  i ) <<  std::endl ;
	std::cout << h.toScientificNotation() << "\t>=\t" << i.toScientificNotation() << "\t[" << std::boolalpha << ( h >= i ) <<  std::endl ;
	std::cout << h.toScientificNotation() << "\t< \t" << i.toScientificNotation() << "\t[" << std::boolalpha << ( h <  i ) <<  std::endl ;
	std::cout << h.toScientificNotation() << "\t<=\t" << i.toScientificNotation() << "\t[" << std::boolalpha << ( h <= i ) <<  std::endl ;

	std::cout << "-----------------------------------------------------------------" << std::endl ;
	std::cout << b << "\t==\t" << c << "\t[" << std::boolalpha << ( b == c ) <<  std::endl ;
	std::cout << b << "\t!=\t" << c << "\t[" << std::boolalpha << ( b != c ) <<  std::endl ;
	std::cout << b << "\t> \t" << c << "\t[" << std::boolalpha << ( b >  c ) <<  std::endl ;
	std::cout << b << "\t>=\t" << c << "\t[" << std::boolalpha << ( b >= c ) <<  std::endl ;
	std::cout << b << "\t< \t" << c << "\t[" << std::boolalpha << ( b <  c ) <<  std::endl ;
	std::cout << b << "\t<=\t" << c << "\t[" << std::boolalpha << ( b <= c ) <<  std::endl ;

	std::cout << "-----------------------------------------------------------------" << std::endl ;
	std::cout << d << "\t==\t" << e << "\t[" << std::boolalpha << ( d == e ) <<  std::endl ;
	std::cout << d << "\t!=\t" << e << "\t[" << std::boolalpha << ( d != e ) <<  std::endl ;
	std::cout << d << "\t> \t" << e << "\t[" << std::boolalpha << ( d >  e ) <<  std::endl ;
	std::cout << d << "\t>=\t" << e << "\t[" << std::boolalpha << ( d >= e ) <<  std::endl ;
	std::cout << d << "\t< \t" << e << "\t[" << std::boolalpha << ( d <  e ) <<  std::endl ;
	std::cout << d << "\t<=\t" << e << "\t[" << std::boolalpha << ( d <= e ) <<  std::endl ;

	std::cout << "-----------------------------------------------------------------" << std::endl ;
	std::cout << e << "\t==\t" << d << "\t[" << std::boolalpha << ( e == d ) <<  std::endl ;
	std::cout << e << "\t!=\t" << d << "\t[" << std::boolalpha << ( e != d ) <<  std::endl ;
	std::cout << e << "\t> \t" << d << "\t[" << std::boolalpha << ( e >  d ) <<  std::endl ;
	std::cout << e << "\t>=\t" << d << "\t[" << std::boolalpha << ( e >= d ) <<  std::endl ;
	std::cout << e << "\t< \t" << d << "\t[" << std::boolalpha << ( e <  d ) <<  std::endl ;
	std::cout << e << "\t<=\t" << d << "\t[" << std::boolalpha << ( e <= d ) <<  std::endl ;

	std::cout << "-----------------------------------------------------------------" << std::endl ;
	std::cout << f << "\t==\t" << g << "\t[" << std::boolalpha << ( f == g ) <<  std::endl ;
	std::cout << f << "\t!=\t" << g << "\t[" << std::boolalpha << ( f != g ) <<  std::endl ;
	std::cout << f << "\t> \t" << g << "\t[" << std::boolalpha << ( f >  g ) <<  std::endl ;
	std::cout << f << "\t>=\t" << g << "\t[" << std::boolalpha << ( f >= g ) <<  std::endl ;
	std::cout << f << "\t< \t" << g << "\t[" << std::boolalpha << ( f <  g ) <<  std::endl ;
	std::cout << f << "\t<=\t" << g << "\t[" << std::boolalpha << ( f <= g ) <<  std::endl ;

	std::cout << "-----------------------------------------------------------------" << std::endl ;
	std::cout << h.toScientificNotation() << "\t==\t" << i.toScientificNotation() << "\t[" << std::boolalpha << ( h == i ) <<  std::endl ;
	std::cout << h.toScientificNotation() << "\t!=\t" << i.toScientificNotation() << "\t[" << std::boolalpha << ( h != i ) <<  std::endl ;
	std::cout << h.toScientificNotation() << "\t> \t" << i.toScientificNotation() << "\t[" << std::boolalpha << ( h >  i ) <<  std::endl ;
	std::cout << h.toScientificNotation() << "\t>=\t" << i.toScientificNotation() << "\t[" << std::boolalpha << ( h >= i ) <<  std::endl ;
	std::cout << h.toScientificNotation() << "\t< \t" << i.toScientificNotation() << "\t[" << std::boolalpha << ( h <  i ) <<  std::endl ;
	std::cout << h.toScientificNotation() << "\t<=\t" << i.toScientificNotation() << "\t[" << std::boolalpha << ( h <= i ) <<  std::endl ;

	std::cout << "-----------------------------------------------------------------" << std::endl ;
	std::cout << j.toScientificNotation() << "\t==\t" << k.toScientificNotation() << "\t[" << std::boolalpha << ( j == k ) <<  std::endl ;
	std::cout << j.toScientificNotation() << "\t!=\t" << k.toScientificNotation() << "\t[" << std::boolalpha << ( j != k ) <<  std::endl ;
	std::cout << j.toScientificNotation() << "\t> \t" << k.toScientificNotation() << "\t[" << std::boolalpha << ( j >  k ) <<  std::endl ;
	std::cout << j.toScientificNotation() << "\t>=\t" << k.toScientificNotation() << "\t[" << std::boolalpha << ( j >= k ) <<  std::endl ;
	std::cout << j.toScientificNotation() << "\t< \t" << k.toScientificNotation() << "\t[" << std::boolalpha << ( j <  k ) <<  std::endl ;
	std::cout << j.toScientificNotation() << "\t<=\t" << k.toScientificNotation() << "\t[" << std::boolalpha << ( j <= k ) <<  std::endl ;

	std::cout << "-----------------------------------------------------------------" << std::endl ;
	std::cout << k.toScientificNotation() << "\t==\t" << j.toScientificNotation() << "\t[" << std::boolalpha << ( k == j ) <<  std::endl ;
	std::cout << k.toScientificNotation() << "\t!=\t" << j.toScientificNotation() << "\t[" << std::boolalpha << ( k != j ) <<  std::endl ;
	std::cout << k.toScientificNotation() << "\t> \t" << j.toScientificNotation() << "\t[" << std::boolalpha << ( k >  j ) <<  std::endl ;
	std::cout << k.toScientificNotation() << "\t>=\t" << j.toScientificNotation() << "\t[" << std::boolalpha << ( k >= j ) <<  std::endl ;
	std::cout << k.toScientificNotation() << "\t< \t" << j.toScientificNotation() << "\t[" << std::boolalpha << ( k <  j ) <<  std::endl ;
	std::cout << k.toScientificNotation() << "\t<=\t" << j.toScientificNotation() << "\t[" << std::boolalpha << ( k <= j ) <<  std::endl ;

	std::cout << "-----------------------------------------------------------------" << std::endl ;
	std::cout << k.toScientificNotation() << "\t==\t" << k.toScientificNotation() << "\t[" << std::boolalpha << ( k == k ) <<  std::endl ;
	std::cout << k.toScientificNotation() << "\t!=\t" << k.toScientificNotation() << "\t[" << std::boolalpha << ( k != k ) <<  std::endl ;
	std::cout << k.toScientificNotation() << "\t> \t" << k.toScientificNotation() << "\t[" << std::boolalpha << ( k >  k ) <<  std::endl ;
	std::cout << k.toScientificNotation() << "\t>=\t" << k.toScientificNotation() << "\t[" << std::boolalpha << ( k >= k ) <<  std::endl ;
	std::cout << k.toScientificNotation() << "\t< \t" << k.toScientificNotation() << "\t[" << std::boolalpha << ( k <  k ) <<  std::endl ;
	std::cout << k.toScientificNotation() << "\t<=\t" << k.toScientificNotation() << "\t[" << std::boolalpha << ( k <= k ) <<  std::endl ;

}

void doMpfrMathRound()
{
	std::string numer ;
	std::string denom ;
	
	abm::R::setDebug( false )   ; 
	abm::R::setSignificantFigures( 30 ) ; 

	{
		abm::R c( "987654321.123456789", 30 ) ;
		std::cout << "---------------------------------------------" << std::endl ;
		std::cout << c << std::endl ;
		std::cout << "---------------------------------------------" << std::endl ;
		for ( long x = 40 ; x >= 0 ; x-- )
		{
			std::cout << abm::stringcat( "dp round ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     ( x ) ) << std::endl ;
			std::cout << abm::stringcat( "dp tostr ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.toDecimalPlaces          ( x ) ) << std::endl ;			
			std::cout << abm::stringcat( "dp fract ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     (x).toFraction() ) << std::endl  << std::endl;
			std::cout << abm::stringcat( "sf round ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures( x ) ) << std::endl ;
			std::cout << abm::stringcat( "sf tostr ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.toSignificantFigures     ( x ) ) << std::endl  ;

			c.roundToSignificantFigures(x).toFraction( numer, denom ) ; 
			std::cout << "[" << numer << "] [" << denom << "]" << std::endl ;
			std::cout << abm::stringcat( "sf fract ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures(x).toFraction() ) << std::endl << std::endl ;


		}
	}
	{
		abm::R c( "-987654321.123456789", 30 ) ;
		std::cout << "---------------------------------------------" << std::endl ;
		std::cout << c << std::endl ;
		std::cout << "---------------------------------------------" << std::endl ;
		for ( long x = 40 ; x >= 0 ; x-- )
		{
			std::cout << abm::stringcat( "dp round ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     ( x ) ) << std::endl ;
			std::cout << abm::stringcat( "dp tostr ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.toDecimalPlaces          ( x ) ) << std::endl ;			
			std::cout << abm::stringcat( "dp fract ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     (x).toFraction() ) << std::endl  << std::endl;
			std::cout << abm::stringcat( "sf round ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures( x ) ) << std::endl ;
			std::cout << abm::stringcat( "sf tostr ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.toSignificantFigures     ( x ) ) << std::endl  ;
			
			c.roundToSignificantFigures(x).toFraction( numer, denom ) ; 
			std::cout << "[" << numer << "] [" << denom << "]" << std::endl ;
			std::cout << abm::stringcat( "sf fract ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures(x).toFraction() ) << std::endl << std::endl ;
		}
	}
	{
		abm::R c( "4567.789", 10 ) ;
		std::cout << "---------------------------------------------" << std::endl ;
		std::cout << c << std::endl ;
		std::cout << "---------------------------------------------" << std::endl ;
		for ( long x = 10 ; x >= 0 ; x-- )
		{
			std::cout << abm::stringcat( "dp round ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     ( x ) ) << std::endl ;
			std::cout << abm::stringcat( "dp tostr ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.toDecimalPlaces          ( x ) ) << std::endl ;			
			std::cout << abm::stringcat( "dp fract ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     (x).toFraction() ) << std::endl  << std::endl;
			std::cout << abm::stringcat( "sf round ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures( x ) ) << std::endl ;
			std::cout << abm::stringcat( "sf tostr ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.toSignificantFigures     ( x ) ) << std::endl  ;

			c.roundToSignificantFigures(x).toFraction( numer, denom ) ; 
			std::cout << "[" << numer << "] [" << denom << "]" << std::endl ;
			std::cout << abm::stringcat( "sf fract ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures(x).toFraction() ) << std::endl << std::endl ;
		}
	}
	{
		abm::R c( "1.0", 5 ) ;
		std::cout << "---------------------------------------------" << std::endl ;
		std::cout << c << std::endl ;
		std::cout << "---------------------------------------------" << std::endl ;
		for ( long x = 6 ; x >= 0 ; x-- )
		{
			std::cout << abm::stringcat( "dp round ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     ( x ) ) << std::endl ;
			std::cout << abm::stringcat( "dp tostr ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.toDecimalPlaces          ( x ) ) << std::endl ;			
			std::cout << abm::stringcat( "dp fract ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     (x).toFraction() ) << std::endl  << std::endl;
			std::cout << abm::stringcat( "sf round ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures( x ) ) << std::endl ;
			std::cout << abm::stringcat( "sf tostr ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.toSignificantFigures     ( x ) ) << std::endl  ;

			c.roundToSignificantFigures(x).toFraction( numer, denom ) ; 
			std::cout << "[" << numer << "] [" << denom << "]" << std::endl ;
			std::cout << abm::stringcat( "sf fract ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures(x).toFraction() ) << std::endl << std::endl ;
		}
	}
	{
		abm::R c( "-1.0", 5 ) ;
		std::cout << "---------------------------------------------" << std::endl ;
		std::cout << c << std::endl ;
		std::cout << "---------------------------------------------" << std::endl ;
		for ( long x = 6 ; x >= 0 ; x-- )
		{
			std::cout << abm::stringcat( "dp round ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     ( x ) ) << std::endl ;
			std::cout << abm::stringcat( "dp tostr ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.toDecimalPlaces          ( x ) ) << std::endl ;			
			std::cout << abm::stringcat( "dp fract ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     (x).toFraction() ) << std::endl  << std::endl;
			std::cout << abm::stringcat( "sf round ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures( x ) ) << std::endl ;
			std::cout << abm::stringcat( "sf tostr ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.toSignificantFigures     ( x ) ) << std::endl  ;

			c.roundToSignificantFigures(x).toFraction( numer, denom ) ; 
			std::cout << "[" << numer << "] [" << denom << "]" << std::endl ;
			std::cout << abm::stringcat( "sf fract ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures(x).toFraction() ) << std::endl << std::endl ;
		}
	}
	{
		abm::R c( "0", 5 ) ;
		std::cout << "---------------------------------------------" << std::endl ;
		std::cout << c << std::endl ;
		std::cout << "---------------------------------------------" << std::endl ;
		for ( long x = 6 ; x >= 0 ; x-- )
		{
			std::cout << abm::stringcat( "dp round ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     ( x ) ) << std::endl ;
			std::cout << abm::stringcat( "dp tostr ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.toDecimalPlaces          ( x ) ) << std::endl ;			
			std::cout << abm::stringcat( "dp fract ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     (x).toFraction() ) << std::endl  << std::endl;
			std::cout << abm::stringcat( "sf round ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures( x ) ) << std::endl ;
			std::cout << abm::stringcat( "sf tostr ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.toSignificantFigures     ( x ) ) << std::endl  ;

			c.roundToSignificantFigures(x).toFraction( numer, denom ) ; 
			std::cout << "[" << numer << "] [" << denom << "]" << std::endl ;
			std::cout << abm::stringcat( "sf fract ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures(x).toFraction() ) << std::endl << std::endl ;
		}
	}
	{
		abm::R c( "0.00000987654321", 15 ) ;
		std::cout << "---------------------------------------------" << std::endl ;
		std::cout << c << std::endl ;
		std::cout << "---------------------------------------------" << std::endl ;
		for ( long x = 15 ; x >= 0 ; x-- )
		{
			std::cout << abm::stringcat( "dp round ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     ( x ) ) << std::endl ;
			std::cout << abm::stringcat( "dp tostr ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.toDecimalPlaces          ( x ) ) << std::endl ;			
			std::cout << abm::stringcat( "dp fract ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     (x).toFraction() ) << std::endl  << std::endl;
			std::cout << abm::stringcat( "sf round ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures( x ) ) << std::endl ;
			std::cout << abm::stringcat( "sf tostr ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.toSignificantFigures     ( x ) ) << std::endl  ;

			c.roundToSignificantFigures(x).toFraction( numer, denom ) ; 
			std::cout << "[" << numer << "] [" << denom << "]" << std::endl ;
			std::cout << abm::stringcat( "sf fract ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures(x).toFraction() ) << std::endl << std::endl ;
		}
	}
	{
		abm::R c( "0.99999", 10 ) ;
		std::cout << "---------------------------------------------" << std::endl ;
		std::cout << c << std::endl ;
		std::cout << "---------------------------------------------" << std::endl ;
		for ( long x = 10 ; x >= 0 ; x-- )
		{
			std::cout << abm::stringcat( "dp round ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     ( x ) ) << std::endl ;
			std::cout << abm::stringcat( "dp tostr ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.toDecimalPlaces          ( x ) ) << std::endl ;			
			std::cout << abm::stringcat( "dp fract ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     (x).toFraction() ) << std::endl  << std::endl;
			std::cout << abm::stringcat( "sf round ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures( x ) ) << std::endl ;
			std::cout << abm::stringcat( "sf tostr ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.toSignificantFigures     ( x ) ) << std::endl  ;

			c.roundToSignificantFigures(x).toFraction( numer, denom ) ; 
			std::cout << "[" << numer << "] [" << denom << "]" << std::endl ;
			std::cout << abm::stringcat( "sf fract ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures(x).toFraction() ) << std::endl << std::endl ;
		}
	}
	{
		abm::R c( "0.42645", 10 ) ;
		std::cout << "---------------------------------------------" << std::endl ;
		std::cout << c << std::endl ;
		std::cout << "---------------------------------------------" << std::endl ;
		for ( long x = 10 ; x >= 0 ; x-- )
		{
			std::cout << abm::stringcat( "dp round ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     ( x ) ) << std::endl ;
			std::cout << abm::stringcat( "dp tostr ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.toDecimalPlaces          ( x ) ) << std::endl ;			
			std::cout << abm::stringcat( "dp fract ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     (x).toFraction() ) << std::endl  << std::endl;
			std::cout << abm::stringcat( "sf round ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures( x ) ) << std::endl ;
			std::cout << abm::stringcat( "sf tostr ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.toSignificantFigures     ( x ) ) << std::endl  ;

			c.roundToSignificantFigures(x).toFraction( numer, denom ) ; 
			std::cout << "[" << numer << "] [" << denom << "]" << std::endl ;
			std::cout << abm::stringcat( "sf fract ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures(x).toFraction() ) << std::endl << std::endl ;
		}
	}
	{
		abm::R c( "0.62645", 10 ) ;
		std::cout << "---------------------------------------------" << std::endl ;
		std::cout << c << std::endl ;
		std::cout << "---------------------------------------------" << std::endl ;
		for ( long x = 10 ; x >= 0 ; x-- )
		{
			std::cout << abm::stringcat( "dp round ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     ( x ) ) << std::endl ;
			std::cout << abm::stringcat( "dp tostr ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.toDecimalPlaces          ( x ) ) << std::endl ;			
			std::cout << abm::stringcat( "dp fract ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     (x).toFraction() ) << std::endl  << std::endl;
			std::cout << abm::stringcat( "sf round ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures( x ) ) << std::endl ;
			std::cout << abm::stringcat( "sf tostr ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.toSignificantFigures     ( x ) ) << std::endl  ;

			c.roundToSignificantFigures(x).toFraction( numer, denom ) ; 
			std::cout << "[" << numer << "] [" << denom << "]" << std::endl ;
			std::cout << abm::stringcat( "sf fract ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures(x).toFraction() ) << std::endl << std::endl ;
		}
	}
	{
		abm::R c( "9.62645", 10 ) ;
		std::cout << "---------------------------------------------" << std::endl ;
		std::cout << c << std::endl ;
		std::cout << "---------------------------------------------" << std::endl ;
		for ( long x = 10 ; x >= 0 ; x-- )
		{
			std::cout << abm::stringcat( "dp round ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     ( x ) ) << std::endl ;
			std::cout << abm::stringcat( "dp tostr ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.toDecimalPlaces          ( x ) ) << std::endl ;			
			std::cout << abm::stringcat( "dp fract ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     (x).toFraction() ) << std::endl  << std::endl;
			std::cout << abm::stringcat( "sf round ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures( x ) ) << std::endl ;
			std::cout << abm::stringcat( "sf tostr ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.toSignificantFigures     ( x ) ) << std::endl  ;

			c.roundToSignificantFigures(x).toFraction( numer, denom ) ; 
			std::cout << "[" << numer << "] [" << denom << "]" << std::endl ;
			std::cout << abm::stringcat( "sf fract ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures(x).toFraction() ) << std::endl << std::endl ;
		}
	}
	{
		abm::R c( "98.62645", 10 ) ;
		std::cout << "---------------------------------------------" << std::endl ;
		std::cout << c << std::endl ;
		std::cout << "---------------------------------------------" << std::endl ;
		for ( long x = 10 ; x >= 0 ; x-- )
		{
			std::cout << abm::stringcat( "dp round ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     ( x ) ) << std::endl ;
			std::cout << abm::stringcat( "dp tostr ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.toDecimalPlaces          ( x ) ) << std::endl ;			
			std::cout << abm::stringcat( "dp fract ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     (x).toFraction() ) << std::endl  << std::endl;
			std::cout << abm::stringcat( "sf round ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures( x ) ) << std::endl ;
			std::cout << abm::stringcat( "sf tostr ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.toSignificantFigures     ( x ) ) << std::endl  ;

			c.roundToSignificantFigures(x).toFraction( numer, denom ) ; 
			std::cout << "[" << numer << "] [" << denom << "]" << std::endl ;
			std::cout << abm::stringcat( "sf fract ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures(x).toFraction() ) << std::endl << std::endl ;
		}
	}
	{
		abm::R c( "99.62645", 10 ) ;
		std::cout << "---------------------------------------------" << std::endl ;
		std::cout << c << std::endl ;
		std::cout << "---------------------------------------------" << std::endl ;
		for ( long x = 10 ; x >= 0 ; x-- )
		{
			std::cout << abm::stringcat( "dp round ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     ( x ) ) << std::endl ;
			std::cout << abm::stringcat( "dp tostr ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.toDecimalPlaces          ( x ) ) << std::endl ;			
			std::cout << abm::stringcat( "dp fract ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     (x).toFraction() ) << std::endl  << std::endl;
			std::cout << abm::stringcat( "sf round ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures( x ) ) << std::endl ;
			std::cout << abm::stringcat( "sf tostr ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.toSignificantFigures     ( x ) ) << std::endl  ;

			c.roundToSignificantFigures(x).toFraction( numer, denom ) ; 
			std::cout << "[" << numer << "] [" << denom << "]" << std::endl ;
			std::cout << abm::stringcat( "sf fract ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures(x).toFraction() ) << std::endl << std::endl ;
		}
	}
	{
		abm::R c( "-6.02e5", 10 ) ;
		std::cout << "---------------------------------------------" << std::endl ;
		std::cout << c << std::endl ;
		std::cout << "---------------------------------------------" << std::endl ;
		for ( long x = 10 ; x >= 0 ; x-- )
		{
			std::cout << abm::stringcat( "dp round ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     ( x ) ) << std::endl ;
			std::cout << abm::stringcat( "dp tostr ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.toDecimalPlaces          ( x ) ) << std::endl ;			
			std::cout << abm::stringcat( "dp fract ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     (x).toFraction() ) << std::endl  << std::endl;
			std::cout << abm::stringcat( "sf round ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures( x ) ) << std::endl ;
			std::cout << abm::stringcat( "sf tostr ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.toSignificantFigures     ( x ) ) << std::endl  ;

			c.roundToSignificantFigures(x).toFraction( numer, denom ) ; 
			std::cout << "[" << numer << "] [" << denom << "]" << std::endl ;
			std::cout << abm::stringcat( "sf fract ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures(x).toFraction() ) << std::endl << std::endl ;
		}
	}
	{
		abm::R c( "-6.02e-5", 10 ) ;
		std::cout << "---------------------------------------------" << std::endl ;
		std::cout << c << std::endl ;
		std::cout << "---------------------------------------------" << std::endl ;
		for ( long x = 10 ; x >= 0 ; x-- )
		{
			std::cout << abm::stringcat( "dp round ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     ( x ) ) << std::endl ;
			std::cout << abm::stringcat( "dp tostr ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.toDecimalPlaces          ( x ) ) << std::endl ;			
			std::cout << abm::stringcat( "dp fract ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     (x).toFraction() ) << std::endl  << std::endl;
			std::cout << abm::stringcat( "sf round ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures( x ) ) << std::endl ;
			std::cout << abm::stringcat( "sf tostr ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.toSignificantFigures     ( x ) ) << std::endl  ;

			c.roundToSignificantFigures(x).toFraction( numer, denom ) ; 
			std::cout << "[" << numer << "] [" << denom << "]" << std::endl ;
			std::cout << abm::stringcat( "sf fract ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures(x).toFraction() ) << std::endl << std::endl ;
		}
	}
	{
		abm::R c( "2.71828459045e10", 15 ) ;
		std::cout << "---------------------------------------------" << std::endl ;
		std::cout << c << std::endl ;
		std::cout << "---------------------------------------------" << std::endl ;
		for ( long x = 20 ; x >= 0 ; x-- )
		{
			std::cout << abm::stringcat( "dp round ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     ( x ) ) << std::endl ;
			std::cout << abm::stringcat( "dp tostr ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.toDecimalPlaces          ( x ) ) << std::endl ;			
			std::cout << abm::stringcat( "dp fract ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     (x).toFraction() ) << std::endl  << std::endl;
			std::cout << abm::stringcat( "sf round ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures( x ) ) << std::endl ;
			std::cout << abm::stringcat( "sf tostr ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.toSignificantFigures     ( x ) ) << std::endl  ;

			c.roundToSignificantFigures(x).toFraction( numer, denom ) ; 
			std::cout << "[" << numer << "] [" << denom << "]" << std::endl ;
			std::cout << abm::stringcat( "sf fract ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures(x).toFraction() ) << std::endl << std::endl ;
		}
	}
	{
		abm::R c( "2.71828459045e-10", 15 ) ;
		std::cout << "---------------------------------------------" << std::endl ;
		std::cout << c << std::endl ;
		std::cout << "---------------------------------------------" << std::endl ;
		for ( long x = 20 ; x >= 0 ; x-- )
		{
			std::cout << abm::stringcat( "dp round ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     ( x ) ) << std::endl ;
			std::cout << abm::stringcat( "dp tostr ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.toDecimalPlaces          ( x ) ) << std::endl ;			
			std::cout << abm::stringcat( "dp fract ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     (x).toFraction() ) << std::endl  << std::endl;
			std::cout << abm::stringcat( "sf round ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures( x ) ) << std::endl ;
			std::cout << abm::stringcat( "sf tostr ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.toSignificantFigures     ( x ) ) << std::endl  ;

			c.roundToSignificantFigures(x).toFraction( numer, denom ) ; 
			std::cout << "[" << numer << "] [" << denom << "]" << std::endl ;
			std::cout << abm::stringcat( "sf fract ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures(x).toFraction() ) << std::endl << std::endl ;
		}
	}
	{
		abm::R c( "-2.71828459045e-10", 15 ) ;
		std::cout << "---------------------------------------------" << std::endl ;
		std::cout << c << std::endl ;
		std::cout << "---------------------------------------------" << std::endl ;
		for ( long x = 20 ; x >= 0 ; x-- )
		{
			std::cout << abm::stringcat( "dp round ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     ( x ) ) << std::endl ;
			std::cout << abm::stringcat( "dp tostr ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.toDecimalPlaces          ( x ) ) << std::endl ;			
			std::cout << abm::stringcat( "dp fract ", abm::stringhlp::printf( 20, "%02d", x ), " dp --> ", c.roundToDecimalPlaces     (x).toFraction() ) << std::endl  << std::endl;
			std::cout << abm::stringcat( "sf round ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures( x ) ) << std::endl ;
			std::cout << abm::stringcat( "sf tostr ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.toSignificantFigures     ( x ) ) << std::endl  ;

			c.roundToSignificantFigures(x).toFraction( numer, denom ) ; 
			std::cout << "[" << numer << "] [" << denom << "]" << std::endl ;
			std::cout << abm::stringcat( "sf fract ", abm::stringhlp::printf( 20, "%02d", x ), " sf --> ", c.roundToSignificantFigures(x).toFraction() ) << std::endl << std::endl ;
		}
	}
}

void doMpfrMath1()
{
	abm::R::setSignificantFigures( 50 ) ; 
		
	std::string str = "3.14" ;

	abm::R a ;
	abm::R b( "2.0234" ) ;
	abm::R c( "8.02345333" ) ;
	abm::R d( str ) ;

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

	abm::R h( "1.0"  ) ;
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

	std::cout << abm::R( "1000.00001" ).root( abm::R( "3.000001" ) ) << std::endl ;
	
	auto u = abm::R( "-FFee.100", abm::R::getSignificantFigures(), abm::numberBase::_16 ) ;
	std::cout << u << std::endl ;

	u = abm::R( "FFFF.FFFF", abm::R::getSignificantFigures(), abm::numberBase::_16 ) ;
	std::cout << u << std::endl ;

	auto v = abm::R( "-11111111.01", abm::R::getSignificantFigures(), abm::numberBase::_2 ) ;
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
	abm::R a1( "-1.23E-2" ) ;
	std::cout << a1 << std::endl ;

	abm::R::setSignificantFigures( 204 ) ;

	auto sum = abm::R( "1.1e100" ) + abm::R( "1.2e-100", 206 ) + abm::R( "1.3" ) ;

	abm::R::setDebug( true ) ;
	std::cout << sum << std::endl ;

	abm::R::setDebug( false ) ;
	std::cout << sum << std::endl ;

	abm::R::setSignificantFigures( 50 ) ;

	// fact
	abm::R a2( "4.49" ) ; // expect 1.2.3.4 = 24
	std::cout << a2.fact() << std::endl ;

	a2 = "4.9999" ; // expect 1.2.3.4 = 24
	std::cout << a2.fact() << std::endl ;

	// sqrt
	abm::R a3( "100.01", 3 ) ;
	std::cout << a3.sqrt() << std::endl ;
	
	a3 = "0.0" ;
	std::cout << a3.sqrt() << std::endl ;

	a3 = "-10.0" ;
	std::cout << "sqrt [" << a3.sqrt() << "]" << std::endl ;

	// recurring
	abm::R a4 = abm::R( "1" ) / abm::R( "3") ;
	std::cout << a4 << std::endl ;

	a4 = abm::R( "2", 10 ) / abm::R( "3", 10 ) ;
	abm::R::setDebug( false ) ;
	std::cout << a4 << std::endl ;
	std::cout << "   1234567890" << std::endl ;
	abm::R::setDebug( true ) ;
	std::cout << a4 << std::endl ;
	abm::R::setDebug( false ) ;

	abm::R a5( "1" ) ;
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

	abm::R::setSignificantFigures( 44 ) ;

	abm::R a6( "0", 5 ) ; 
	std::cout << a6 << std::endl ; // sf 5

	abm::R a7( "8", 10  ) ; 
	abm::R a8( "9", 8   ) ; 
	
	a6 = a7 / a8 ; 
	std::cout << a6 << std::endl ; // sf 10
	std::cout << a7 << std::endl ; // sf 10
	std::cout << a8 << std::endl ; // sf 8

	abm::R a9( "-12.3456789", 5 ) ;
	std::cout << a9 << std::endl ; // sf 5
	
	auto a10 = a9 ;
	std::cout << a10 << std::endl ; // sf 5

	a10 = a7 ;
	std::cout << a10 << std::endl ; // sf 10

	auto a11 = abm::R( "10.1" ) + abm::R( "23.2" ) ;
	std::cout << a11 << std::endl ; // sf 44

	a11 = a7 + abm::R( "23.2" ) ;
	std::cout << a11 << std::endl ; // sf 10

	a11 = abm::R( "23.2" ) + a7 ;
	std::cout << a11 << std::endl ; // sf 44

	abm::R a12( "-12.3456789", 5 ) ;
	a12 += a11 ;
	std::cout << a12 << std::endl ; // sf 5

	abm::R a13( "-12.3456789"  ) ;
	a13 += a11 ;
	std::cout << a13 << std::endl ; // sf 44

	std::cout << "---" << std::endl ;

	auto a14 = abm::R( "-12.3456789" )  ;
	auto a15 = abm::R( "-12.3456789", 5 ) ;
	auto a16 = a14 + a15 ;
	auto a17 = a15 + a14 ;

	std::cout << "a14               " << a14 << std::endl ; // sf ??
	std::cout << "a15               " << a15 << std::endl ; // sf ??
	std::cout << "a16 = a14 + a15 = " << a16 << std::endl ; // sf ?? <---------------
	std::cout << "a17 = a15 + a14 = " << a17 << std::endl ; // sf ??

	auto a18 = a14 + a14 ;
	auto a19 = a15 + a15 ;
	auto a20 = a14 * "2" ;
	auto a21 = a15 * abm::R( "2", 5 )  ;
	std::cout << "a18 " << a18 << std::endl ; // sf ??
	std::cout << "a19 " << a19 << std::endl ; // sf ??
	std::cout << "a20 " << a20 << std::endl ; // sf ??
	std::cout << "a21 " << a21 << std::endl ; // sf ??

	std::cout << "---" << std::endl ;

	auto a22 = abm::R( "-12.3456789" ) ;
	auto a23 = a14 + a22 ;
	auto a24 = a22 + a14 ;
	std::cout << "a14               " << a14 << std::endl ; // sf ??
	std::cout << "a22               " << a15 << std::endl ; // sf ??
	std::cout << "a23 = a14 + a15 = " << a16 << std::endl ; // sf ?? <---------------
	std::cout << "a24 = a15 + a14 = " << a17 << std::endl ; // sf ??
}

void doMpfrMathtoCanonical()
{
	std::string strDecimal            ;
	std::string strScientificNotation ;
	std::string decimalSign  ;
	std::string decimal      ;
	std::string fraction     ; 
	std::string exponentSign ;
	std::string exponent     ;

	auto str = "  -0123456.12345678901234567890e+0121  " ;
	//auto b = abm::numberhlp::regex( str, decimalSign, decimal, fraction, exponentSign, exponent ) ;
	//std::cout << "[" << str << "] --> " 
	//	<< std::boolalpha << b 
	//	<< "[" << decimalSign << "]" 
	//	<< "[" << decimal << "]" 
	//	<< "[" << fraction << "]" 
	//	<< "[" << exponentSign << "]" 
	//	<< "[" << exponent << "]" 
	//	<< std::endl ;

	auto b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "42" ;
	//b = abm::numberhlp::regex( str, decimalSign, decimal, fraction, exponentSign, exponent ) ;
	//std::cout << "[" << str << "] --> " 
	//	<< std::boolalpha << b 
	//	<< "[" << decimalSign << "]" 
	//	<< "[" << decimal << "]" 
	//	<< "[" << fraction << "]" 
	//	<< "[" << exponentSign << "]" 
	//	<< "[" << exponent << "]" 
	//	<< std::endl ;

	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "123456.12345678901234567890" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "00000042" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "42.00" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "042.0" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "000000.0000000000000000E-00000000" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "000000.00000020000000000E-000000111" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-0.0000002E20" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "1123560e20" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-0.12345e10" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-0.12345e1" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-0.12345e0" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-0.12345e-1" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "9e2" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "9.0e2" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.9e2" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.90e2" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.999e2" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.0999e2" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.00999e2" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.000999e2" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.0000999e2" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;


	str = "9e0" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "9.0e0" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.9e0" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.90e0" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.999e0" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.0999e0" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.00999e0" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.000999e0" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.0000999e0" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;



	str = "9e-2" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "9.0e-2" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.9e-2" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.90e-2" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.999e-2" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.0999e-2" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.00999e-2" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.000999e-2" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.0000999e-2" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-0" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.0" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-0.0" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.0e100" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-0.0e-100" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;



	str = "-31415935253238" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-31415935253238.9" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-31415935253238.979" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-31415935253238e40" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-31415935253238.9e40" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-31415935253238.979e40" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-31415935253238e-40" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-31415935253238.9e-40" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-31415935253238.979e-40" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;



	str = "-3.14" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-3.1415935253238979" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-31.415935253238979" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-314.15935253238979" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-314159352532.38979" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;


	str = "-3.14e20" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-3.1415935253238979e20" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-31.415935253238979e20" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-314.15935253238979e20" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-314159352532.38979e20" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-314159352532.38979e4" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-314159352532.38979e5" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-314159352532.38979e6" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-3.14e-20" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-3.1415935253238979e-20" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-31.415935253238979e-20" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-314.15935253238979e-20" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-314159352532.38979e-20" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-314159352532.38979e-4" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-314159352532.38979e-5" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-314159352532.38979e-6" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "-000000123.45678000000" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "123456789123456789" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "123456789.67" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "12.3456789" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;




	str = "1" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "10" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "12" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "100" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "123" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "120" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "1000" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "1234" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "1230" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "1200" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "1001" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "20000" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "20001" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;





	str = "0.1" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.01" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.12" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.001" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.123" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.0001" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.1234" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.0002" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;


	str = "0.00000000012300000" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "12.345" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "1.2345" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.12345" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.012345" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.0012345" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.00012345" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.000012345" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.0000012345" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.00000012345" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.000000012345" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.0000000012345" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;

	str = "0.00000000012345" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( strScientificNotation, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;
	std::cout << "_____________________" << std::endl ;
}

void doMpfrMathtoSigFig()
{
	std::string strDecimal            ;
	std::string strScientificNotation ;

	auto str = "0.00000000012345" ;
	auto b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;

	auto sd = 20 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 10 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 6 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 5 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 4 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 3 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 2 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 1 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	std::cout << "---------------------------" << std::endl ;

	str = "0.1" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;

	sd = 1 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 2 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 3 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	std::cout << "---------------------------" << std::endl ;

	str = "0.0" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;

	sd = 1 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 2 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 3 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	std::cout << "---------------------------" << std::endl ;

	str = "0.123" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;

	sd = 1 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 2 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 3 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 4 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 10 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	std::cout << "---------------------------" << std::endl ;

	str = "0.1230456" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;

	sd = 1 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 2 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 3 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 4 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 5 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 6 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 7 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 8 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 20 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	std::cout << "---------------------------" << std::endl ;

	str = "42" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;

	sd = 1 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 2 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 3 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 4 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	std::cout << "---------------------------" << std::endl ;

	str = "-31415935253238" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;

	sd = 13 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 14 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 15 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 16 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	std::cout << "---------------------------" << std::endl ;

	str = "-31415935253238.123456" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;

	sd = 13 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 14 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 15 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 16 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 20 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 21 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	std::cout << "---------------------------" << std::endl ;

	str = "-12.345" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;

	sd = 1 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 2 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 3 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 4 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 5 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 6 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;


	std::cout << "---------------------------" << std::endl ;

	str = "-1.23" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;

	sd = 1 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 2 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 3 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 4 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 5 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	std::cout << "---------------------------" << std::endl ;

	str = "1.23456" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;

	sd = 1 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 2 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 3 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 4 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 5 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 6 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 7 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 8 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 9 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 10 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	std::cout << "---------------------------" << std::endl ;

	str = "123456.1234" ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " [" << strDecimal << "]" << std::endl ;

	sd = 1 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 2 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 5 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 6 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 7 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 12 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	std::cout << "---------------------------" << std::endl ;

	str = "9999.999" ;
	sd = 0 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 1 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 2 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 3 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 4 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 5 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 6 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 7 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 8 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	sd = 9 ;
	b = abm::numberhlp::toScientificNotation( str, strScientificNotation, sd ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strScientificNotation << "]" << std::endl ;
	b = abm::numberhlp::toDecimal( str, strDecimal, sd  ) ;
	std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << sd << " [" << strDecimal << "]" << std::endl ;

	std::cout << "---------------------------" << std::endl ;

	str = "9.999e-2" ;
	for ( int i = 0 ; i <= 6 ; i++ )
	{
		b = abm::numberhlp::toScientificNotation( str, strScientificNotation, i ) ;
		std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << i << " [" << strScientificNotation << "]" << std::endl ;
		b = abm::numberhlp::toDecimal( str, strDecimal, i  ) ;
		std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << i << " [" << strDecimal << "]" << std::endl ;
	}

	std::cout << "---------------------------" << std::endl ;

	str = "9.999e-1" ;
	for ( int i = 0 ; i <= 6 ; i++ )
	{
		b = abm::numberhlp::toScientificNotation( str, strScientificNotation, i ) ;
		std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << i << " [" << strScientificNotation << "]" << std::endl ;
		b = abm::numberhlp::toDecimal( str, strDecimal, i  ) ;
		std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << i << " [" << strDecimal << "]" << std::endl ;
	}

	std::cout << "---------------------------" << std::endl ;

	str = "9.999e-0" ;
	for ( int i = 0 ; i <= 6 ; i++ )
	{
		b = abm::numberhlp::toScientificNotation( str, strScientificNotation, i ) ;
		std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << i << " [" << strScientificNotation << "]" << std::endl ;
		b = abm::numberhlp::toDecimal( str, strDecimal, i  ) ;
		std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << i << " [" << strDecimal << "]" << std::endl ;
	}

	std::cout << "---------------------------" << std::endl ;

	str = "9.999e1" ;
	for ( int i = 0 ; i <= 6 ; i++ )
	{
		b = abm::numberhlp::toScientificNotation( str, strScientificNotation, i ) ;
		std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << i << " [" << strScientificNotation << "]" << std::endl ;
		b = abm::numberhlp::toDecimal( str, strDecimal, i  ) ;
		std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << i << " [" << strDecimal << "]" << std::endl ;
	}

	std::cout << "---------------------------" << std::endl ;

	str = "9.999e2" ;
	for ( int i = 0 ; i <= 6 ; i++ )
	{
		b = abm::numberhlp::toScientificNotation( str, strScientificNotation, i ) ;
		std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << i << " [" << strScientificNotation << "]" << std::endl ;
		b = abm::numberhlp::toDecimal( str, strDecimal, i  ) ;
		std::cout << "[" << str << "] --> " << std::boolalpha << b << " --> " << i << " [" << strDecimal << "]" << std::endl ;
	}

	std::cout << "---------------------------" << std::endl ;

}

void roundToSignificantDigits() 
{
	std::string str ;
	std::string strRounded ;
	std::string strScientificNotation ;

	std::cout << "---------------------------" << std::endl ;
	std::cout << "---------------------------" << std::endl ;
	std::cout << "---------------------------" << std::endl ;

	str = "123456789.0" ;
	for ( int i = 0 ; i <= 11 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}

	str = "12345678.9" ;
	for ( int i = 0 ; i <= 11 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}

	str = "1234567.8" ;
	for ( int i = 0 ; i <= 11 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}

	str = "123456.7" ;
	for ( int i = 0 ; i <= 11 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}

	str = "12345.6" ;
	for ( int i = 0 ; i <= 9 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}

	str = "1234.5" ;
	for ( int i = 0 ; i <= 9 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}

	str = "123.4" ;
	for ( int i = 0 ; i <= 9 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}

	str = "12.3" ;
	for ( int i = 0 ; i <= 5 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}

	str = "1.2" ;
	for ( int i = 0 ; i <= 5 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}

	for ( int i = 0 ; i <= 9 ; i++ )
	{
		auto s = abm::stringcat( "0.", i ) ;

		abm::numberhlp::toScientificNotation( s, strScientificNotation ) ;
		std::cout << "[" << s <<  "] --> " << 0 << " --> [" << strScientificNotation << "]" << std::endl ;

		abm::numberhlp::toScientificNotation( s, strScientificNotation, 1 ) ;
		std::cout << "[" << s <<  "] --> " << 1 << " --> [" << strScientificNotation << "]" << std::endl ;

		abm::numberhlp::toDecimal( s, strRounded, 1 ) ;
		std::cout << "[" << s <<  "] --> " << 1 << " --> [" << strRounded << "]" << std::endl ;
	}

	for ( int i = 0 ; i <= 9 ; i++ )
	{
		auto s = abm::stringcat( i, ".5" ) ;

		abm::numberhlp::toScientificNotation( s, strScientificNotation ) ;
		std::cout << "[" << s <<  "] --> " << 0 << " --> [" << strScientificNotation << "]" << std::endl ;

		abm::numberhlp::toScientificNotation( s, strScientificNotation, 1 ) ;
		std::cout << "[" << s <<  "] --> " << 1 << " --> [" << strScientificNotation << "]" << std::endl ;

		abm::numberhlp::toDecimal( s, strRounded, 1 ) ;
		std::cout << "[" << s <<  "] --> " << 1 << " --> [" << strRounded << "]" << std::endl ;
	}

	str = "9999" ;
	for ( int i = 0 ; i <= 7 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}

	str = "9900" ;
	for ( int i = 0 ; i <= 7 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}

	str = "9090" ;
	for ( int i = 0 ; i <= 7 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}

	str = "9099" ;
	for ( int i = 0 ; i <= 7 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}

	str = "9009" ;
	for ( int i = 0 ; i <= 7 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}

	str = "305.459" ;
	for ( int i = 0 ; i <= 7 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}

	str = "1111" ;
	for ( int i = 0 ; i <= 7 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}

	str = "2222" ;
	for ( int i = 0 ; i <= 7 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}

	str = "3333" ;
	for ( int i = 0 ; i <= 7 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}

	str = "4444" ;
	for ( int i = 0 ; i <= 7 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}

	str = "5555" ;
	for ( int i = 0 ; i <= 7 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}

	str = "6666" ;
	for ( int i = 0 ; i <= 7 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}	

	str = "7777" ;
	for ( int i = 0 ; i <= 7 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}

	str = "8888" ;
	for ( int i = 0 ; i <= 7 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}

	str = "9999" ;
	for ( int i = 0 ; i <= 7 ; i++ )
	{
		abm::numberhlp::toDecimal( str, strRounded, i ) ;
		std::cout << "[" << str <<  "] --> " << i << " --> [" << strRounded << "]" << std::endl ;
	}


}


