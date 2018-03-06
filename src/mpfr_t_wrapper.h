#pragma once

namespace alby::bigmath
{
	class mpfr_t_wrapper
	{
		protected:
			mpfr_t        			x ;
			mpfr_prec_t   			precision ;
			static unsigned long 	objCount  ;

		public:
			virtual ~mpfr_t_wrapper() ;
			mpfr_t_wrapper( mpfr_prec_t precision ) ;

			mpfr_t* get() ;

			mpfr_t_wrapper( const mpfr_t_wrapper& rhs )            = delete ;
			mpfr_t_wrapper& operator=( const mpfr_t_wrapper& rhs ) = delete ;
	} ;
} 


