#pragma once

namespace alby::bigmath
{
	class mpfr
	{
		public:
			static const mpfr_rnd_t default_rounding = MPFR_RNDN ;
			static const mpfr_rnd_t default_precison = (mpfr_rnd_t) 100 ;

		protected:
			mpfr_t_wrapper* p         = nullptr          ;
			mpfr_rnd_t  	rounding  = MPFR_RNDN        ;
			mpfr_prec_t 	precision = default_precison ;

			// ALBY TO DO
			// digits10 ;
			// digits2  ;

			void init()    ;
			void cleanup() ;

			static mpfr_t& deref( const mpfr& mpfr ) ; // get the important part of the wrapper

		public:
			virtual ~mpfr() ;

			mpfr(                     mpfr_rnd_t rounding = default_rounding, mpfr_prec_t precision = default_precison ) ;
			mpfr( const char*,        mpfr_rnd_t rounding = default_rounding, mpfr_prec_t precision = default_precison, int base = 10 ) ;
			mpfr( const std::string&, mpfr_rnd_t rounding = default_rounding, mpfr_prec_t precision = default_precison, int base = 10 ) ;

			mpfr( const mpfr& rhs ) ;
			mpfr& operator=( const mpfr& rhs ) ;

			mpfr_rnd_t  getRounding() ;
			mpfr_prec_t getPrecision() ;
			std::string toString() const ;

			friend std::ostream& operator<<( std::ostream& os, const mpfr& mpfr ) ;

			static std::string version() ;
			static std::string random( int bytes ) ; // random number of n bytes as hex string

			friend mpfr operator-( const mpfr& op1, const mpfr& op2 ) ;
			friend mpfr operator+( const mpfr& op1, const mpfr& op2 ) ;
			friend mpfr operator*( const mpfr& op1, const mpfr& op2 ) ;
			friend mpfr operator/( const mpfr& op1, const mpfr& op2 ) ;
			friend mpfr operator^( const mpfr& op1, const mpfr& op2 ) ;

			mpfr e()   ; // return e  ;
			mpfr pi()  ; // return pi ;

			mpfr sin() ; // return sin( this )
			mpfr cos() ; // return cos( this )
			mpfr tan() ; // return tan( this )

//alby do these
			mpfr neg() ; // return this * -1.0 ;
			mpfr inv() ; // return 1.0 / recip ;

			mpfr pow  ( mpfr& op2 ) ; // return this pow op2
			mpfr pow2 ()            ; // return 2 pow this
			mpfr pow10()            ; // return 10 pow this
			mpfr root ( mpfr& op2 ) ; // return the op2'th root of this
			mpfr exp  ()            ; // return e pow this 
			mpfr ln   ()            ; // return ln( this )
			mpfr log2 ()            ; // return log2( this )
			mpfr log10()            ; // return log10( this )


// x = a + "3.14" 
// pow( "1.0")
// operators and constructors from longs and strings
// ceil
// floor
// trunc
// mpfr_urandomb ( seed ??? )
// handle ie10

			//ALBY fix me
			//operator mpq_class() ;
			//mpq_class toMpq() ;
	} ;
} 

