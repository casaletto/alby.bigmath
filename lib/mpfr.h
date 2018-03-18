#pragma once

namespace alby::bigmath
{
	class mpfr
	{
		public:
			static const unsigned long precision10default = 100        ; // the default number of decimal digits required 
			static const mpfr_rnd_t    roundingDefault    = MPFR_RNDN  ; // the default rounding
			static       unsigned long precision10global               ;
			static       bool  		   debug                           ;
							
		protected:
			mpfr_t_wrapper* p           = nullptr            ;
			mpfr_prec_t 	precision10 = precision10default ;

			void init()    ;
			void cleanup() ;

			static mpfr_t& deref( const mpfr& mpfr ) ; // get the important part of the wrapper, the actual mpfr_t

		public:
			virtual ~mpfr() ;

			mpfr()                             ;               
			mpfr( const mpfr& rhs )            ;
			mpfr& operator=( const mpfr& rhs ) ;

			mpfr( const char* )                ;
			mpfr( const char*, int base )      ;
			mpfr( const char*, int base, unsigned long thePrecision10 ) ;

			mpfr( const std::string& )           ;
			mpfr( const std::string&, int base ) ;
			mpfr( const std::string&, int base, unsigned long thePrecision10 ) ;

			unsigned long        getPrecisionLocal() ;
			static unsigned long getPrecision()      ;
			static void          setPrecision( unsigned long thePrecision10 ) ;
			static bool          getDebug()             ;
			static void          setDebug( bool debug ) ;

			std::string toString() ;
			operator std::string() ;
			operator std::string() const ;

			friend std::ostream& operator<<( std::ostream& os, const mpfr& mpfr ) ;

			std::string toDecimal           ( bool fullPrecision = false ) ;
			std::string toScientificNotation( bool fullPrecision = false ) ;

			static std::string version()                ;
			static std::string randomBytes( int bytes ) ; 

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

			mpfr e()   						; // return e  ;
			mpfr pi()  						; // return pi ;

			mpfr sin()						; // return sin( this )
			mpfr cos() 						; // return cos( this )
			mpfr tan() 						; // return tan( this )

			mpfr neg() 						; // return this * -1.0 ;
			mpfr inv() 						; // return 1.0 / recip ;
			mpfr abs() 						; // return abs( this ) ;

			mpfr exp  ()					; // return e pow this 
			mpfr log  ()					; // return ln( this )
			mpfr log2 ()					; // return log2( this )
			mpfr log10()					; // return log10( this )
			mpfr pow2 ()   					; // return 2 pow this
			mpfr pow10()					; // return 10 pow this
			mpfr root ( const mpfr& op2 ) 	; // return the op2'th root of this

			mpfr sqrt()						; // return square root
			mpfr fact()						; // return factorial

			mpfr ceil()  					; // ceiling
			mpfr floor() 					; // floor
			mpfr trunc() 					; // trunc towards 0

//ALBY TODO
			mpfr roundDecimalPlaces     ( unsigned long dp ) ;
			mpfr roundSignificantFigures( unsigned long sf ) ;			

			void toFraction     (                       std::string numerator, std::string& denominator, bool reduce = true ) ;			
			void toMixedFraction( std::string& integer, std::string numerator, std::string& denominator, bool reduce = true ) ;			
			
	} ;
} 

