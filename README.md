# alby.bigmath

a c++ wrapper around the mpfr **ℝ** and gmp **ℚ** projects to make extreme maths more pleasant.\
\
move seamlessly between exact rational number **ℚ** arithmetic
```
class alby::bigmath::mpq
```
and almost unlimited precision real number **ℝ** arithmetic
```
class alby::bigmath::mpfr
```

# base projects

* http://www.mpfr.org
* https://gmplib.org

# packages required

* build-essential (or equivalent gnu compiler toolchain)
* libgmp-dev
* libgmp10
* libmpfr-dev
* libmpfr4

# what is the main artifact produced by this project?

```
libalbybigmath.a
```

# how do I build it?

```
$ make 
```

# how do I use it in my project?

cpp files

```
#include <gmp.h>
#include <mpfr.h>
#include "../lib/numberBase.h"
#include "../lib/stringhlp.h"
#include "../lib/stringcat.h"
#include "../lib/numberhlp.h"
#include "../lib/mpfr_t_wrapper.h"
#include "../lib/mpfr.h"
#include "../lib/mpq_t_wrapper.h"
#include "../lib/mpq.h"
#include "../lib/random.h"
#include "../lib/pi.h"
#include "../lib/version.h"
```

makefile

```
$ g++ -c *.cpp

$ g++ -s \
	-o exefile *.o \
	-static \
	-static-libgcc \
	-static-libstdc++ \
	-l:libmpfr.a \
	-l:libgmp.a \
	-llibalbybigmath.a
```

I hate dll hell. I do static linking as much as possible.

# developed and tested on

```
$ gcc --version
gcc (Ubuntu 6.3.0-12ubuntu2) 6.3.0 20170406
```

```
$ uname -a
Linux xxxxxxx 4.10.0-28-generic #32-Ubuntu SMP Fri Jun 30 05:32:18 UTC 2017 x86_64 x86_64 x86_64 GNU/Linux
```

I had a bad dream that I partly developed and tested this on windoze 10 mingw64/msys64, but yeh, probably just a dream.

```
$ gcc --version
gcc.exe (Rev1, Built by MSYS2 project) 6.1.0
```

```
$ uname -a
MINGW64_NT-6.3 xxxxxxx 2.5.2(0.297/5/3) 2016-07-15 08:31 x86_64 Msys
```

# some examples

(1)
```
1.2e+10 + 3.4 + 5.6e-10
```

(2)
```
1.2e+1000 + 3.4 + 5.6e-1000 
```

```
namespace abm = alby::bigmath ; 

void example1()
{
	abm::mpfr::setSignificantFigures( 22 ) ;
	abm::mpfr::setDebug( false ) ; 

	auto a = abm::mpfr( "1.2e10"  ) ;
	auto b = abm::mpfr( "3.4"     ) ;
	auto c = abm::mpfr( "5.6e-10" ) ;	

	auto sum = a + b + c ;

	std::cout 
		<< a << " + " 
		<< b << " + " 
		<< c << std::endl << std::endl 
		<< "= " << sum << std::endl << std::endl 
		<< "= " << sum.toScientificNotation() << std::endl << std::endl ;

	abm::mpfr::setSignificantFigures( 2002 ) ;

	a = abm::mpfr( "1.2e1000"  ) ;
	b = abm::mpfr( "3.4"       ) ;
	c = abm::mpfr( "5.6e-1000" ) ;	

	sum = a + b + c ;

	std::cout 
		<< a.toScientificNotation() << " + " 
		<< b << " + " 
		<< c.toScientificNotation() << std::endl << std::endl 
		<< "= " << sum << std::endl << std::endl  
		<< "= " << sum.toScientificNotation()  << std::endl ;
}
```

result (1)

```
+12000000000.0 + +3.4 + +0.00000000056

= +12000000003.40000000056

= +1.200000000340000000056E+10
```

result (2)

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
	abm::mpfr::setSignificantFigures( 1000 ) ;
	abm::mpfr::setDebug( false ) ;

	abm::mpfr pi ;

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

abm::mpfr pi_nilakantha_term( unsigned long _i )
{
	static abm::mpfr _4 = 4 ;

	abm::mpfr i = _i ;

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
	
	abm::mpfr::setSignificantFigures( 1500 ) ;
	abm::mpfr::setDebug( false ) ;

	auto factorial = abm::mpfr::factorialMap( N * 6 ) ;

	abm::mpfr pi ;

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

abm::mpfr pi_ramanujan_term( unsigned long _n, std::map<unsigned long, abm::mpfr>& factorial )
{
	static abm::mpfr _3   = 3     ;
	static abm::mpfr _6   = 6     ;
	static abm::mpfr _1_5 = "1.5" ;

	static abm::mpfr a = 13591409  ;
	static abm::mpfr b = 545140134 ;
	static abm::mpfr c = 640320    ;

	abm::mpfr n = _n   ;
	abm::mpfr num, den ;

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
	abm::mpfr::setSignificantFigures( 1000001 ) ;
	abm::mpfr::setDebug( false ) ;

	auto pi = abm::pi::nonic( 7 ) ;

	std::cout << pi << std::endl ;
}

mpfr pi::nonic( unsigned long N ) 
{
	nonic_term_t t0 ; 

	t0.a = mpfr(1) / 3 ;
	t0.r = ( mpfr(3).sqrt() - 1 ) / 2 ;

	t0.s  = 1 - ( t0.r ^ 3 ) ;
	t0.s ^= mpfr(1) / 3 ;

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
	t.u ^= mpfr(1) / 3 ; 

	t.v = ( t.t ^ 2 ) + t.t * t.u + ( t.u ^ 2 ) ;

	t.w  = 1 + prev.s + ( prev.s ^ 2 ) ;
	t.w *= 27 / t.v ;

	t.a  = t.w * prev.a ;
	t.a += ( 3 ^ mpfr( 2 * (n-1) - 1 ) ) * ( 1 - t.w ) ;

	t.s  = ( 1 - prev.r ) ^ 3;
	t.s /= ( t.t + 2 * t.u ) * t.v ;

	t.r  = 1 - ( t.s ^ 3 ) ;
	t.r ^= mpfr(1) / 3 ; 

	return t ;
}
```

# how do I run the unit tests?

```
$ make test
```

# useful links

* http://www.mpfr.org
* https://gmplib.org
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

&nbsp;
