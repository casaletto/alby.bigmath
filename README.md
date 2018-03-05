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


# developed and tested on

```
$ gcc --version
gcc (Ubuntu 6.3.0-12ubuntu2) 6.3.0 20170406
```

```
$ uname -a
Linux xxxxxxx 4.10.0-28-generic #32-Ubuntu SMP Fri Jun 30 05:32:18 UTC 2017 x86_64 x86_64 x86_64 GNU/Linux
```

* also partly developed and tested on windoze 10 mingw64/msys64, but I'm not admitting to that.


# here's an example TODO


1.1e1000 + 1.2e-1000 + 1.2 

```
mrfr::setPrecision( 2100 ) ; // number of required decimal digits

auto sum = mpfr( "1.1e1000" ) + mpfr( "1.2e-1000" ) + "1.2" ;
std::cout << sum << std::endl ;

```