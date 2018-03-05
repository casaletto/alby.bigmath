#pragma once

namespace alby::bigmath
{
	class mpfr
	{
		public:
			static const mpfr_prec_t precisionDefault = (mpfr_prec_t) 100 ; // the default number of decimal digits required 
			static const mpfr_rnd_t  roundingDefault  = MPFR_RNDN         ; // the default rounding

			static       mpfr_prec_t precisionGlobal ;
			static       mpfr_rnd_t  roundingGlobal  ;

			static const unsigned long extraPrecisionBinary = 20 ; // 2^20 = 1,048,576 = 7 extra decimal digits for greater accuracy of temporay calculations
							
		protected:
			mpfr_t_wrapper* p              = nullptr          ;
			mpfr_prec_t 	precisionLocal = precisionDefault ;
			mpfr_rnd_t  	roundingLocal  = roundingDefault  ;

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

			mpfr_prec_t        getPrecisionLocal() ;
			static mpfr_prec_t getPrecision() ;
			static void        setPrecision( mpfr_prec_t prec ) ;

			mpfr_rnd_t         getRoundingLocal() ;
			static mpfr_rnd_t  getRounding() ;
			static void        setRounding( mpfr_rnd_t rnd ) ;

			std::string toString() const ;

			friend std::ostream& operator<<( std::ostream& os, const mpfr& mpfr ) ;

			static std::string version() ;
			static std::string random( int bytes ) ; // random number of n bytes as hex string

			mpfr& operator-=( const mpfr& op2 ) ;
			mpfr& operator+=( const mpfr& op2 ) ;
			mpfr& operator*=( const mpfr& op2 ) ;
			mpfr& operator/=( const mpfr& op2 ) ;
			mpfr& operator^=( const mpfr& op2 ) ;

			friend mpfr operator-( const mpfr& op1, const mpfr& op2 ) ;
			friend mpfr operator+( const mpfr& op1, const mpfr& op2 ) ;
			friend mpfr operator*( const mpfr& op1, const mpfr& op2 ) ;
			friend mpfr operator/( const mpfr& op1, const mpfr& op2 ) ;
			friend mpfr operator^( const mpfr& op1, const mpfr& op2 ) ;

			friend bool operator> ( const mpfr& op1, const mpfr& op2 ) ; 
			friend bool operator< ( const mpfr& op1, const mpfr& op2 ) ;
			friend bool operator>=( const mpfr& op1, const mpfr& op2 ) ; 
			friend bool operator<=( const mpfr& op1, const mpfr& op2 ) ;
			friend bool operator==( const mpfr& op1, const mpfr& op2 ) ;
			friend bool operator!=( const mpfr& op1, const mpfr& op2 ) ;

			mpfr e()   ; // return e  ;
			mpfr pi()  ; // return pi ;

			mpfr sin() ; // return sin( this )
			mpfr cos() ; // return cos( this )
			mpfr tan() ; // return tan( this )

			mpfr neg() ; // return this * -1.0 ;
			mpfr inv() ; // return 1.0 / recip ;
			mpfr abs() ; // return abs( this ) ;

			mpfr exp  ()					; // return e pow this 
			mpfr log  ()					; // return ln( this )
			mpfr log2 ()					; // return log2( this )
			mpfr log10()					; // return log10( this )
			mpfr pow2 ()   					; // return 2 pow this
			mpfr pow10()					; // return 10 pow this
			mpfr root ( const mpfr& op2 ) 	; // return the op2'th root of this

			mpfr ceil()  ;
			mpfr floor() ;
			mpfr trunc() ;
			
			unsigned long getBinaryPrecision( unsigned long precisionDecimal ) ;

	} ;
} 

