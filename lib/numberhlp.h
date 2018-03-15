#pragma once

namespace alby::bigmath
{
	class numberhlp
	{
		protected:
			static bool regex                   ( const std::string& strNumber, std::string& decimalSign, std::string& decimal, std::string& fraction, std::string& exponentSign, std::string& exponent ) ;
			static void adjustScientificNotation( std::string& decimalSign, std::string& decimal, std::string& fraction, std::string& exponentSign, std::string& exponent ) ;

		public:
			numberhlp();
			virtual ~numberhlp() ;

			static bool toDecimal               ( const std::string& strNumber, std::string& strDecimal,            unsigned long significantFigures = 0 ) ; // return true if ok
			static bool toScientificNotation    ( const std::string& strNumber, std::string& strScientificNotation, unsigned long significantFigures = 0 ) ; // return true if ok
			static void toSignificantFigures    ( unsigned long significantFigures, std::string& decimal, std::string& fraction ) ;
			static void toRound					( unsigned long significantFigures, std::string& decimal, std::string& fraction, std::string& exponent ) ;

//ALBY fix me - make protected 
			static bool round                   ( const std::string& strNumber, const std::string& strRoundingDigit, std::string& strResult ) ; // return true if carry set			

	} ;
} 
