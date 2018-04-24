#pragma once

namespace alby::bigmath
{
	class random
	{
		protected:
		    static const std::string	devUrandomFile ;  
            static const unsigned long	seedBytes ; 
            mpz_t						seed ;
            gmp_randstate_t				state ;			
            std::string					theSeed ;
			unsigned long 				theSignificantFigures ;

		public:
			virtual ~random() ;

			random() ;
			random( unsigned long significantFigures, const std::string& seed, numberBase base ) ;
			random( const random& rhs ) ;
			random& operator=( const random& rhs ) ; 

            R					next() ;     						// get next float random number [0.0, 1.0)
            unsigned long		nextInteger( unsigned long max ) ; 	// return an integer [1, max]

            std::string			getSeed() ;
		 	unsigned long		getSignificantFigures() ;
        	static std::string	getUrandomBytes( int bytes ) ; 			// hex string of random bytes from urandom
            static std::string	nanosecondsSinceEpoch() ; 			// alternate seed for windoze
	} ;
} 
