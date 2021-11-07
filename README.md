
[![Build Status](https://travis-ci.org/casaletto/alby.bigmath.svg?branch=master)](https://travis-ci.org/casaletto/alby.bigmath)

# alby.bigmath

a c++ wrapper around the mpfr **ℝ** and gmp **ℚ** projects to make extreme maths more pleasant.\
\
move seamlessly between exact rational number **ℚ** arithmetic
```
class alby::bigmath::Q
```
and almost unlimited precision real number **ℝ** arithmetic
```
class alby::bigmath::R
```

# base projects

* mpfr http://www.mpfr.org
* gmp  https://gmplib.org

# packages required   

* build-essential (or equivalent gnu compiler toolchain)
* libgmp-dev \
  2:6.2.0+dfsg-4 

* libgmp10 \
  2:6.2.0+dfsg-4 

* libmpfr-dev  \
  4.0.2-1  

* libmpfr6  \
  4.0.2-1 

* googletest \
  1.10.0-2 
  

# what is the main artifact produced by this project?

```
a C++ static library
./albybigmath/lib/libalbybigmath.a
```

# how do I build the code?

```
$ make 
```

# how do I run the smoke tests?

```
$ make smoke
```

# how do I run the unit tests?

```
$ make test
```

# what unit test framework is used by this project?

* googletest https://github.com/google/googletest

# where can I find the ci builds for this project?

* travis ci https://travis-ci.org/casaletto/alby.bigmath

# how do I use the code in my project?

include files

```
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
```

makefile

```
$ g++ -c *.cpp -I <path to albybigmath/include>

$ g++ -s \
	-o exefile *.o \
	-static \
	-static-libgcc \
	-static-libstdc++ \
	-L <path to albybigmath/lib> \
	-l:libmpfr.a \
	-l:libgmp.a \
	-llibalbybigmath.a
```

I have previously suffered terribly in dll hell.\
Ipso facto, I perform static linking wherever possible.

# developed and tested on

my development platform

```
$ g++ --version
g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
```

```
$ uname -a
Linux xxxxxxx 5.11.0-38-generic #42~20.04.1-Ubuntu SMP Tue Sep 28 20:41:07 UTC 2021 x86_64 x86_64 x86_64 GNU/Linux
```

my previous development platform 

```
$ g++ --version
g++ (Ubuntu 6.3.0-12ubuntu2) 6.3.0 20170406
```

```
$ uname -a
Linux xxxxxxx 4.10.0-28-generic #32-Ubuntu SMP Fri Jun 30 05:32:18 UTC 2017 x86_64 x86_64 x86_64 GNU/Linux
```

my alt development platform

```
$ g++ --version
g++.exe (Rev1, Built by MSYS2 project) 6.1.0
```

```
$ uname -a
MINGW64_NT-6.3 xxxxxxx 2.5.2(0.297/5/3) 2016-07-15 08:31 x86_64 Msys
```

travis ci reports build success on the following platforms

```
$ g++6 --version
g++-6 (Ubuntu/Linaro 6.3.0-18ubuntu2~14.04) 6.3.0 20170519
```

```
$ g++7 --version
g++-7 (Ubuntu 7.2.0-1ubuntu1~14.04) 7.2.0
```

```
$ uname -a
Linux travis-job-casaletto-alby-bigmath-367621695.travisci.net 4.14.12-041412-generic #201801051649 SMP Fri Jan 5 16:50:54 UTC 2018 x86_64 x86_64  x86_64 GNU/Linux
```

# some ℝ examples

```
1.2e+10 + 3.4 + 5.6e-10
```

```
1.2e+1000 + 3.4 + 5.6e-1000 
```

```
namespace abm = alby::bigmath ; 

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
```

results

```
+12000000000.0 + +3.4 + +0.00000000056

= +12000000003.40000000056

= +1.200000000340000000056E+10
```

```
+1.2E+1000 + +3.4 + +5.6E-1000

= +12000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000003.40000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000056

= +1.200000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000340000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000056E+1000
```

# calculate π, method #1

![π #1](doc/pi%20nilakantha.png)

500 000 iterations yield 17 decimal places
```
+3.14159265358979323
```

5 000 000 iterations yield 20 decimal places
```
+3.14159265358979323846
```

```
namespace abm = alby::bigmath ; 

void pi_nilakantha()
{
	abm::R::setSignificantFigures( 1000 ) ;
	abm::R::setDebug( false ) ;

	abm::R pi ;

	auto plus = true ;

	for ( unsigned long i = 2 ; i <= 5000 * 2 ; i += 2 )
	{
		auto term = pi_nilakantha_term(i) ; 

		pi = plus ? pi + term : pi - term ;

		plus = ! plus ;	 
	}

	pi += 3 ; 

	std::cout << pi << std::endl ;
}

abm::R pi_nilakantha_term( unsigned long _i )
{
	static abm::R _4 = 4 ;

	abm::R i = _i ;

	return _4 / ( i * (i+1) * (i+2) ) ;
}
```

# calculate π, method #2

![π #2](doc/pi%20ramujan.png)

10 iterations yield 155 decimal places
```
+3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111
```

100 iterations yield 1 432 decimal places
```
+3.1415926535897932384626433...42699227967823547816360093417216412199245
```

1 000 iterations yield 14 195 decimal places
```
+3.1415926535897932384626433...228435988341003583854238973542439564755568409522484455413
```

10 000 iterations yield 141 830 decimal places
```
+3.1415926535897932384626433...9605721400330661597939815697061366098396405520287669991722547240
```

```
namespace abm = alby::bigmath ; 

void pi_ramanujan()
{
	unsigned long N = 100 ;
	
	abm::R::setSignificantFigures( 1500 ) ;
	abm::R::setDebug( false ) ;

	auto factorial = abm::R::factorialMap( N * 6 ) ;

	abm::R pi ;

	auto plus = true ;

	for ( unsigned long n = 0 ; n <= N ; n++ )
	{
		auto term = pi_ramanujan_term( n, factorial ) ; 

		pi = plus ? pi + term : pi - term ;

		plus = ! plus ;
	}

	pi *= 12 ;
	pi  = pi.inv() ;

	std::cout << pi << std::endl ;
}

abm::R pi_ramanujan_term( unsigned long _n, std::map<unsigned long, abm::R>& factorial )
{
	static abm::R _3   = 3     ;
	static abm::R _6   = 6     ;
	static abm::R _1_5 = "1.5" ;

	static abm::R a = 13591409  ;
	static abm::R b = 545140134 ;
	static abm::R c = 640320    ;

	abm::R n = _n   ;
	abm::R num, den ;

	num  = factorial[ 6*_n ] ;
	num *= a + n*b           ;

	den  = factorial[ _n ] ^ 3 ;
	den *= factorial[ 3*_n ]   ; 
	den *= c ^ (n*3 + _1_5)    ;

	return num / den ;
}
```

# calculate π, method #3

![π #3](doc/pi%20nonic%20convergence.png)

calculate π to **1 000 000 decimal places** with only 7 iterations
```
+3.141592653589793238462...696552087542450598956787961303311646283996346460422090106105779458151
```

```
namespace abm = alby::bigmath ; 

void pi_nonic()
{
	abm::R::setSignificantFigures( 1000001 ) ;
	abm::R::setDebug( false ) ;

	auto pi = abm::pi::nonic( 7 ) ;

	std::cout << pi << std::endl ;
}

R pi::nonic( unsigned long N ) 
{
	nonic_term_t t0 ; 

	t0.a = R(1) / 3 ;
	t0.r = ( R(3).sqrt() - 1 ) / 2 ;

	t0.s  = 1 - ( t0.r ^ 3 ) ;
	t0.s ^= R(1) / 3 ;

	auto prev = t0 ;
	auto t    = t0 ;

	for ( unsigned long n = 1 ; n <= N ; n++ )
	{
		t = nonic_term( n, prev ) ; 
		prev = t ;
	}

	return t.a.inv() ;
}
	 
pi::nonic_term_t pi::nonic_term( unsigned long n, nonic_term_t& prev ) // calculate term n
{
	nonic_term_t t ; 

	t.t = 1 + 2 * prev.r ;
	
	t.u  = 9 * prev.r * ( 1 + prev.r + ( prev.r ^ 2 ) ) ;
	t.u ^= R(1) / 3 ; 

	t.v = ( t.t ^ 2 ) + t.t * t.u + ( t.u ^ 2 ) ;

	t.w  = 1 + prev.s + ( prev.s ^ 2 ) ;
	t.w *= 27 / t.v ;

	t.a  = t.w * prev.a ;
	t.a += ( 3 ^ R( 2 * (n-1) - 1 ) ) * ( 1 - t.w ) ;

	t.s  = ( 1 - prev.r ) ^ 3;
	t.s /= ( t.t + 2 * t.u ) * t.v ;

	t.r  = 1 - ( t.s ^ 3 ) ;
	t.r ^= R(1) / 3 ; 

	return t ;
}
```

# some ℚ examples

```
a = 5/49 + 3/21 - 6/25 
b = 2 2/3 + 1 1/4 - 5/6
c = ( 3 - 2/3 ) / 5/6
d = 1 2/7 / 5 
e = 1 2/3 / ( 1 1/4 * 4 2/5 )
```

```
namespace abm = alby::bigmath ; 

void rationals()
{
	auto a = abm::Q( "5/49" ) + "3/21" - "6/25" ;
	std::cout << "a = " << a << std::endl ;
	
	auto b = abm::Q( 2,"2/3" ) + abm::Q( 1,"1/4" ) - "5/6" ;
	std::cout << "b = " << b << std::endl ;

	auto c = ( abm::Q(3) - "2/3" ) / "5/6" ;
	std::cout << "c = " << c << std::endl ;

	auto d = abm::Q( 1,"2/7" ) / 5 ;
	std::cout << "d = " << d << std::endl ;

	auto e = abm::Q( 1,"2/3" ) / ( abm::Q( 1,"1/4" ) * abm::Q( 4,"2/5" ) ) ;
	std::cout << "e = "             << e << std::endl ;
	std::cout << "e numerator   = " << e.numerator()   << std::endl ;
	std::cout << "e denominator = " << e.denominator() << std::endl ;

	e *= -1 ;	
	std::cout << "e = "             << e << std::endl ;
	std::cout << "e numerator   = " << e.numerator()   << std::endl ;
	std::cout << "e denominator = " << e.denominator() << std::endl ;
}
```

results

```
a = +6/1225
b = +37/12
c = +14/5
d = +9/35
e = +10/33
e numerator   = +10
e denominator = +33
e = -10/33
e numerator   = -10
e denominator = +33
```

# some mixed ℚ and ℝ examples

```
namespace abm = alby::bigmath ; 

void pythagoras1()
{
	abm::R::setSignificantFigures( 15 ) ;
	abm::R::setDebug( false ) ;
	
	abm::Q a = 3 ;
	abm::Q b = 4 ;

	auto temp = a*a + b*b ;
	auto c    = temp.toR().sqrt().toQ() ; 

	std::cout << "a = " << a       << std::endl ;
	std::cout << "b = " << b       << std::endl ;
	std::cout << "c = " << c       << std::endl ;
	std::cout << "c = " << c.toR() << std::endl ;
}
```

```
namespace abm = alby::bigmath ; 

void pythagoras2()
{
	abm::R::setSignificantFigures( 15 ) ;
	abm::R::setDebug( false ) ;
	
	auto a = abm::Q( 3, "1/100" ) ;
	auto b = abm::Q( 4, "1/100" ) ;

	auto temp = a*a + b*b ;
	auto c    = temp.toR().sqrt().toQ() ; 

	std::cout << "a = " << a       << std::endl ;
	std::cout << "b = " << b       << std::endl ;
	std::cout << "c = " << c       << std::endl ;
	std::cout << "c = " << c.toR() << std::endl ;
}

```

results

```
a = +3
b = +4
c = +5
c = +5.0
```

```
a = +301/100
b = +401/100
c = +501400039888311/100000000000000
c = +5.01400039888311
```

# useful links

* http://www.mpfr.org
* https://gmplib.org
* https://github.com/google/googletest
* https://regexr.com/3m16c
* https://en.wikipedia.org/wiki/Borwein%27s_algorithm
* https://helloacm.com/two-simple-equations-to-compute-pi
* http://www.pi314.net/eng/borwein.php
* https://ipfs.io/ipfs/QmXoypizjW3WknFiJnKLwHCnL72vedxjQkDDP1mXWo6uco/wiki/Borwein%27s_algorithm.html
* https://www.carma.newcastle.edu.au/jon/RAMA125f.pdf
* https://crypto.stanford.edu/pbc/notes/pi/ramanujan.html
* http://www.piday.org/million/
* http://webdocs.cs.ualberta.ca/~smillie/Pi10000.html
* http://www.eveandersson.com/pi/digits/1000000
* https://jbt.github.io/markdown-editor/
* https://www.calculatorsoup.com/calculators/discretemathematics/factorials.php
* http://xahlee.info/comp/unicode_math_operators.html
* https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.cbclx01/explicit_keyword.htm
* https://github.com/mbonaci/mbo-storm/wiki/Integrate-Travis-CI-with-your-GitHub-repo 
* https://docs.travis-ci.com/user/getting-started/
* https://docs.travis-ci.com/user/languages/cpp/
* https://docs.travis-ci.com/user/installing-dependencies/
* https://docs.travis-ci.com/user/environment-variables/

&nbsp;
