#pragma once

namespace alby::bigmath
{
	class numberhlp
	{
		public:
			numberhlp();
			virtual ~numberhlp() ;

			static bool toDecimal               ( const std::string& strNumber, std::string& strDecimal,            unsigned long significantFigures = 0 ) ; // return true if ok
			static bool toScientificNotation    ( const std::string& strNumber, std::string& strScientificNotation, unsigned long significantFigures = 0 ) ; // return true if ok

		protected:
			static bool regex                   ( const std::string& strNumber, std::string& decimalSign, std::string& decimal, std::string& fraction, std::string& exponentSign, std::string& exponent ) ;
			static void adjustScientificNotation( std::string& decimalSign, std::string& decimal, std::string& fraction, std::string& exponentSign, std::string& exponent ) ;
			static bool	toScientificNotation    ( const std::string& strNumber, std::string& decimalSign, std::string& decimal, std::string& fraction, std::string& exponentSign, std::string& exponent, unsigned long significantFigures ) ;
			static void toSignificantFigures    ( std::string& decimal, std::string& fraction, unsigned long significantFigures ) ;
			static void roundSignificantFigures	( std::string& decimal, std::string& fraction, std::string& exponentSign, std::string& exponent, unsigned long significantFigures ) ;
			static bool roundNumber             ( const std::string& strNumber, const std::string& strRoundingDigit, std::string& strResult, bool& carry ) ; // return true if rounded			
	} ;
} 
