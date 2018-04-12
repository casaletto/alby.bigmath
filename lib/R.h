#pragma once

namespace alby::bigmath
{
	class Q ; // forward declaration

	class R
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

			std::string reduce ( const std::string& rational ) ;
			static void compare( const R& op1, const R& op2, bool& equal, bool& moreThan, bool& lessThan ) ;
	
		public:
			virtual ~R() ;

			R() ;               
			R( const R& rhs ) ;
			R( const R& rhs, unsigned long theSigFig10 ) ;
			R( long l ) ;
			R( const char* ) ;
			R( const char*, unsigned long theSigFig10, numberBase base = numberBase::_10 ) ;
			R( const std::string& ) ;
			R( const std::string&, unsigned long theSigFig10, numberBase base = numberBase::_10 ) ;
			R& operator=( const R& rhs ) ;

			explicit R( const Q& rhs ) ;
			explicit R( const Q& rhs, unsigned long theSigFig10 ) ; // explicit constructors

			static mpfr_t&       deref( const R& r ) ;            // get the important part of the wrapper, the actual mpfr_t
			unsigned long        getSignificantFiguresLocal() ;
			static unsigned long getSignificantFigures() ;
			static void          setSignificantFigures( unsigned long theSigFig10 ) ;
			static bool          getDebug() ;
			static void          setDebug( bool debug ) ;

			std::string toString()          ;
			operator    std::string()       ;
			operator    std::string() const ;

			friend std::ostream& operator<<( std::ostream& os, const R& r ) ;

			std::string toDecimal                ( bool allSigFig = false         ) ;
			std::string toScientificNotation     ( bool allSigFig = false         ) ;
			R           roundToDecimalPlaces     ( unsigned long theDecimalPlaces ) ;
			std::string toDecimalPlaces          ( unsigned long theDecimalPlaces ) ;
			R           roundToSignificantFigures( unsigned long theSigFig10      ) ; 
			std::string toSignificantFigures	 ( unsigned long theSigFig10      ) ;  
			std::string toFraction( bool reduce = true ) ;			
			std::string toFraction( std::string& numerator, std::string& denominator, bool reduce = true ) ;			
			Q 			toQ() ;

			R& operator-=( const R& op2 ) ;
			R& operator+=( const R& op2 ) ;
			R& operator*=( const R& op2 ) ;
			R& operator/=( const R& op2 ) ;
			R& operator^=( const R& op2 ) ;

			friend R operator-( const R& op1, const R& op2 ) ;
			friend R operator+( const R& op1, const R& op2 ) ;
			friend R operator*( const R& op1, const R& op2 ) ;
			friend R operator/( const R& op1, const R& op2 ) ;
			friend R operator^( const R& op1, const R& op2 ) ;

			friend bool operator> ( const R& op1, const R& op2 ) ; 
			friend bool operator< ( const R& op1, const R& op2 ) ;
			friend bool operator>=( const R& op1, const R& op2 ) ; 
			friend bool operator<=( const R& op1, const R& op2 ) ;
			friend bool operator==( const R& op1, const R& op2 ) ;
			friend bool operator!=( const R& op1, const R& op2 ) ;

			R e()   					; // return e  ;
			R pi()  					; // return pi ;

			R sin()						; // return sin( this )
			R cos() 					; // return cos( this )
			R tan() 					; // return tan( this )

			R neg() 					; // return this * -1.0 ;
			R inv() 					; // return 1.0 / recip ;
			R abs() 					; // return abs( this ) ;

			R exp  ()					; // return e pow this 
			R log  ()					; // return ln( this )
			R log2 ()					; // return log2( this )
			R log10()					; // return log10( this )
			R pow2 ()   				; // return 2 pow this
			R pow10()					; // return 10 pow this
			R root ( const R& op2 ) 	; // return the op2'th root of this

			R sqrt()					; // return square root
			R fact()					; // return factorial

			R ceil()  					; // ceiling
			R floor() 					; // floor
			R trunc() 					; // trunc towards 0

			static std::map<unsigned long, R> factorialMap( unsigned long n ) ; // create a map of factorials, range [0..n]
	} ;
} 

