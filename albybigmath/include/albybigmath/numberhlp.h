#pragma once

namespace alby::bigmath
{
	class numberhlp
	{

		public:
			numberhlp();
			virtual ~numberhlp() ;

			// return true if number ok
			static bool toScientificNotation    ( const std::string& strNumber, std::string& strScientificNotation, unsigned long significantFigures = 0 ) ; 
			static bool toDecimal               ( const std::string& strNumber, std::string& strDecimal,            unsigned long significantFigures = 0 ) ; 
			static bool scientificNotationExtend( const std::string& strNumber, std::string& strScientificNotation, unsigned long significantFigures     ) ; 
			static bool decimalPlacesExtend     ( const std::string& strNumber, std::string& strDecimal,            unsigned long decimalPlaces          ) ; 
			static bool	toNumeratorDenominator  ( const std::string& strNumber, std::string& strNumerator, std::string& strDenominator ) ;
			static bool regex2					( const std::string& strNumber, std::string& decimalSign, std::string& decimal, std::string& fraction, std::string& exponentSign, std::string& exponent ) ;
			static bool splitRational			( const std::string& strNumber, std::string& strNumerator, std::string& strDenominator, std::string& strSign ) ;

		protected:
			static bool regexOld                ( const std::string& strNumber, std::string& decimalSign, std::string& decimal, std::string& fraction, std::string& exponentSign, std::string& exponent ) ;
			static void adjustScientificNotation( std::string& decimalSign, std::string& decimal, std::string& fraction, std::string& exponentSign, std::string& exponent ) ;
			static bool	toScientificNotation    ( const std::string& strNumber, std::string& decimalSign, std::string& decimal, std::string& fraction, std::string& exponentSign, std::string& exponent, unsigned long significantFigures ) ;
			static void toSignificantFigures    ( std::string& decimal, std::string& fraction, unsigned long significantFigures ) ;
			static void roundSignificantFigures	( std::string& decimal, std::string& fraction, std::string& exponentSign, std::string& exponent, unsigned long significantFigures ) ;
			static bool roundNumber             ( const std::string& strNumber, const std::string& strRoundingDigit, std::string& strResult, bool& carry ) ; // return true if rounded			
	} ;
} 
