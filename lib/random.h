#pragma once

namespace alby::bigmath
{
	class random
	{
		protected:
		    static const std::string   devUrandomFile ;  
            static const unsigned long seedBytes ; 
    
            mpz_t                      seed  ;
            gmp_randstate_t            state ;
            std::string                theSeed ;

		public:
			virtual ~random() ;
			random() ;

			random( const std::string& seed, numberBase base )  ;
			random( const random& rhs ) ;
			random& operator=( const random& rhs ) ; 

            std::string getSeed() ;
            mpfr        next() ;
            mpfr        next( unsigned long significantDigits ) ; // get next float random number [0.0, 1.0)
//ALBY
            std::string nextInteger ( unsigned long max ) ; // return a number [0, max]


        	static std::string hexBytes( int bytes ) ; // hex string of random bytes fom urandom
            static std::string nanosecondsSinceEpoch() ; 
	} ;
} 
