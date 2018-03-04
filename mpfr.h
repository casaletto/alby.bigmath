#pragma once

namespace alby::bigmath
{
	class mpfr
	{
		public:
			static const mpfr_prec_t defaultPrecision = (mpfr_prec_t) 100 ; //ALBY FIX this shuould be decimal sinificant digits defaultSignificantDigits10
			static       mpfr_prec_t globalPrecision                      ;

			static const mpfr_rnd_t  defaultRounding = MPFR_RNDN ;
			static       mpfr_rnd_t  globalRounding              ;

		protected:
			mpfr_t_wrapper* p         = nullptr          ;
			mpfr_prec_t 	precision = defaultPrecision ;
			mpfr_rnd_t  	rounding  = defaultRounding  ;

			// ALBY TO DO
			// digits10 ;
			// digits2  ;

			void init()    ;
			void cleanup() ;

			static mpfr_t& deref( const mpfr& mpfr ) ; // get the important part of the wrapper, the actual mpfr_t

		public:
			virtual ~mpfr() ;

			mpfr() ;               
			mpfr(                  mpfr_prec_t precision, mpfr_rnd_t rounding ) ;
			mpfr( const mpfr& rhs, mpfr_prec_t precision, mpfr_rnd_t rounding ) ;

			mpfr( const char*,        int base = 10 ) ;
			mpfr( const std::string&, int base = 10 ) ;

			mpfr( const char*,        mpfr_prec_t precision, mpfr_rnd_t rounding, int base = 10 ) ;
			mpfr( const std::string&, mpfr_prec_t precision, mpfr_rnd_t rounding, int base = 10 ) ;

			mpfr( const mpfr& rhs ) ;
			mpfr& operator=( const mpfr& rhs ) ;

			mpfr_prec_t        getPrecision() ;
			static mpfr_prec_t getGlobalPrecision() ;
			static void        setGlobalPrecision( mpfr_prec_t prec ) ;

			mpfr_rnd_t         getRounding() ;
			static mpfr_rnd_t  getGlobalRounding() ;
			static void        setGlobalRounding( mpfr_rnd_t rnd ) ;

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

			mpfr neg() ; // return this * -1.0 ;
			mpfr inv() ; // return 1.0 / recip ;

			mpfr exp  ()					; // return e pow this 
			mpfr log  ()					; // return ln( this )
			mpfr log2 ()					; // return log2( this )
			mpfr log10()					; // return log10( this )
			mpfr pow2 ()   					; // return 2 pow this
			mpfr pow10()					; // return 10 pow this
			mpfr root ( const mpfr& op2 ) 	; // return the op2'th root of this
	} ;
} 

