#pragma once

namespace alby::bigmath
{
	class mpfr_t_wrapper
	{
		protected:
			mpfr_t        			x ;
			unsigned long 			precision10 ;
			unsigned long  			precision2  ;
			static unsigned long 	objectCount ;

//ALBY fix me
			static const unsigned long extraPrecision10 = 10 ; // ten extra decimal place to mitigate rounding errors
			// 2^20 = 1,048,576 = 7 extra decimal digits for greater accuracy of temporay calculations

		public:
			virtual ~mpfr_t_wrapper() ;
			mpfr_t_wrapper( unsigned long precision10 ) ;

			mpfr_t* 				get()                           			   ;
			unsigned long 			getPrecision10()               				   ;
			unsigned long 			getPrecision2()                			  	   ;
			static unsigned long 	getObjectCount()             				   ;
			static unsigned long 	calcPrecision2( unsigned long thePrecision10 ) ;

			mpfr_t_wrapper( const mpfr_t_wrapper& rhs )            = delete ;
			mpfr_t_wrapper& operator=( const mpfr_t_wrapper& rhs ) = delete ;

			std::string toString( bool detailed = false ) const ;
			friend std::ostream& operator<<( std::ostream& os, const mpfr_t_wrapper& rhs ) ;		
	} ;
} 


