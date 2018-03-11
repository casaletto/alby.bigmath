#pragma once

namespace alby::bigmath
{
	class numberParser
	{
		protected:

		public:
			numberParser();
			virtual ~numberParser() ;

			static bool normalise            ( const std::string& str, std::string& strScientifIcNotation ) ; // return true if ok
			static bool regex                ( const std::string& str, std::string& decimalSign, std::string& decimal, std::string& fraction, std::string& exponentSign, std::string& exponent ) ;
			static void fixScientificNotation( std::string& decimalSign, std::string& decimal, std::string& fraction, std::string& exponentSign, std::string& exponent ) ;
	} ;
} 
