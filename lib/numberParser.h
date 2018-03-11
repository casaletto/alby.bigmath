#pragma once

namespace alby::bigmath
{
	class numberParser
	{
		protected:
			//static bool split    ( const std::string& str, std::string& decimal, std::string& fraction, std::string& exponent, std::string& decimalSign, std::string& exponentSign ) ;
			static bool isInteger( const std::string& str ) ;

		public:
			numberParser();
			virtual ~numberParser() ;

			static bool	normalise( const std::string& str, std::string& strScientifIcNotation ) ; // return true if ok
	} ;
} 
