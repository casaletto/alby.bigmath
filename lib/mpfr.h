#pragma once

namespace alby::bigmath
{
	class mpfr
	{
		public:
			static const unsigned long sigFig10default = 100        ; // the default number of decimal significant figures required 
			static const mpfr_rnd_t    roundingDefault = MPFR_RNDN  ; // the default rounding
			static       unsigned long sigFig10global               ;
			static       bool  		   debug                        ;
							
		protected:
			mpfr_t_wrapper* p        = nullptr         ;
			mpfr_prec_t 	sigFig10 = sigFig10default ;

			void init()    ;
			void cleanup() ;

			std::string    reduce ( const std::string& rational ) ;
			static void    compare( const mpfr& op1, const mpfr& op2, bool& equal, bool& moreThan, bool& lessThan ) ;
	
		public:
			virtual ~mpfr() ;

			mpfr()                             ;               
			mpfr( const mpfr& rhs )            ;
			mpfr( const mpfr& rhs, unsigned long theSigFig10 ) ;
			mpfr( long l ) ;
			
			mpfr& operator=( const mpfr& rhs ) ;

			mpfr( const char* )                ;
			mpfr( const char*, unsigned long theSigFig10, numberBase base = numberBase::_10 ) ;

			mpfr( const std::string& )           ;
			mpfr( const std::string&, unsigned long theSigFig10, numberBase base = numberBase::_10 ) ;

			static mpfr_t&       deref( const mpfr& mpfr ) ; // get the important part of the wrapper, the actual mpfr_t

			unsigned long        getSignificantFiguresLocal() ;
			static unsigned long getSignificantFigures()      ;
			static void          setSignificantFigures( unsigned long theSigFig10 ) ;
			static bool          getDebug()             ;
			static void          setDebug( bool debug ) ;

			std::string toString()          ;
			operator    std::string()       ;
			operator    std::string() const ;

			friend std::ostream& operator<<( std::ostream& os, const mpfr& mpfr ) ;

			std::string toDecimal                ( bool allSigFig = false         ) ;
			std::string toScientificNotation     ( bool allSigFig = false         ) ;

			mpfr        roundToDecimalPlaces     ( unsigned long theDecimalPlaces ) ;
			std::string toDecimalPlaces          ( unsigned long theDecimalPlaces ) ;

			mpfr        roundToSignificantFigures( unsigned long theSigFig10      ) ; 
			std::string toSignificantFigures	 ( unsigned long theSigFig10      ) ;  

			std::string toFraction( bool reduce = true ) ;			
			std::string toFraction( std::string& numerator, std::string& denominator, bool reduce = true ) ;			

			static std::string version()                ;

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

			static std::map<unsigned long, mpfr> factorialMap( unsigned long n ) ; // create a map of factorials, range [0..n]
	} ;
} 

