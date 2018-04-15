#pragma once

namespace alby::bigmath
{
	class mpfr_t_wrapper
	{
		protected:
			mpfr_t        			   x           ;
			unsigned long 			   sigFig10    ;
			unsigned long  			   sigFig2     ;
			static unsigned long 	   objectCount ;

			static const unsigned long extraSigFig10 =  20 ; // 20 extra decimal places to mitigate rounding errors
			static const unsigned long minSigFig2    = 500 ; // minumum number of base 2 significant digits

		public:
			virtual ~mpfr_t_wrapper() ;
			mpfr_t_wrapper( unsigned long theSigFig10 ) ;

			mpfr_t* 				get()                     ;
			unsigned long 			getSignificantFigures10() ;
			unsigned long 			getSignificantFigures2()  ;
			static unsigned long 	getObjectCount()          ;
			static unsigned long 	calcSignificantFigures2( unsigned long theSigFig10 ) ;

			mpfr_t_wrapper( const mpfr_t_wrapper& rhs )            = delete ; // do not copy these objects
			mpfr_t_wrapper& operator=( const mpfr_t_wrapper& rhs ) = delete ;

			std::string toString( bool debug = false ) ; 
	} ;
} 


