# alby.bigmath

a c++ wrapper around mpfr and gmp to make extreme maths more pleasant.

move seamlessly between exact rational number arithmetic (gmp) and almost unlimited precision floating point aritmetic (mpfr).


# base projects

* http://www.mpfr.org
* https://gmplib.org


# packages required

* gcc + standard linux toolchain
* libgmp-dev
* libgmp10
* libmpfr-dev
* libmpfr4


# how to build

*.cpp

```
#include "mpfr_t_wrapper.h"
#include "mpfr.h"
```

makefile

```
g++ -c *.cpp
g++ -s -o exefile *.o -static -static-libgcc -static-libstdc++ -l:libmpfr.a -l:libgmp.a -llibalbympfr.a
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


# here's an example TODO

1.2e1000 + 3.4e-1000 + 5.6 

```
#include "mpfr_t_wrapper.h"
#include "mpfr.h"

using namespace alby::bigmath ; 

mpfr::setPrecision( 2100 ) ; // number of required decimal digits

auto sum = mpfr( "1.2e1000" ) + mpfr( "3.4e-1000" ) + "5.6" ;
std::cout << sum << std::endl ;
```


# calculate π to 10,000 decimal places TODO

```
the Nilakantha series

	π = 3 + 4/(2*3*4) - 4/(4*5*6) + 4/(6*7*8) - 4/(8*9*10) + 4/(10*11*12) - 4/(12*13*14) ...
```

```
the class number three Ramanujan type series, 25 digits per term

	1 / 12π = sum( n = 0, n = ∞ ) ( num / den )

where 

	num = pow( -1, n ) * (6n)! * ( A + nB )
	den = pow( n!, 3 ) * (3n)! * pow( C, n + 0.5 )

	A = 212 175 710 912 sqrt(61) + 1 657 145 277 365,
	B = 13 773 980 892 672 sqrt(61) + 107 578 229 802 750,
	C = ( 5280 ( 236 674 + 30 303 sqrt(61) ) )  pow 3.
```








