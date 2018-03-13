#pragma once

namespace alby::bigmath
{
	class numberParser
	{
		protected:

		public:
			numberParser();
			virtual ~numberParser() ;

			static bool toDecimal               ( const std::string& strNumber, std::string& strDecimal,            unsigned long significantFigures = 0 ) ; // return true if ok
			static bool toScientificNotation    ( const std::string& strNumber, std::string& strScientificNotation, unsigned long significantFigures = 0 ) ; // return true if ok

			static bool regex                   ( const std::string& strNumber, std::string& decimalSign, std::string& decimal, std::string& fraction, std::string& exponentSign, std::string& exponent ) ;
			static void adjustScientificNotation( std::string& decimalSign, std::string& decimal, std::string& fraction, std::string& exponentSign, std::string& exponent ) ;
			static void toSignificantFigures    ( unsigned long significantFigures, std::string& decimalSign, std::string& decimal, std::string& fraction, std::string& exponentSign, std::string& exponent ) ;

			static std::string toSignificantFigures( const std::string& strDecimal, unsigned long significantFigures = 0 ) ; 

	} ;
} 
