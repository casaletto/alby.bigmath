#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <inttypes.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <vector>
#include <fstream>
#include <iomanip>
#include <assert.h>    
#include <algorithm>
#include <regex>
#include <random>
#include <chrono>
#include <thread>

#include "albybigmath/stringhlp.h"

namespace alby::bigmath 
{
	stringhlp::stringhlp()
	{
	}

	stringhlp::~stringhlp()
	{
	}

	const std::string stringhlp::__delimiters = " \f\n\r\t\v" ;

	std::string 
	stringhlp::ltrim( const std::string& str, const std::string& delim )
	{
		if ( str.empty() ) return str ;

		auto pos = str.find_first_not_of( delim ) ;

		if ( pos == std::string::npos ) return "" ;

		return str.substr( pos ) ;
	}

	std::string 
	stringhlp::rtrim( const std::string& str, const std::string& delim )
	{
		if ( str.empty() ) return str ;

		auto pos = str.find_last_not_of( delim ) ;

		if ( pos == std::string::npos ) return "" ;

		return str.substr( 0, pos + 1 ) ;
	}

	std::string 
	stringhlp::ltrim( const std::string& str )
	{
		if ( str.empty() ) return str ;

		auto pos = str.find_first_not_of( __delimiters ) ;

		if ( pos == std::string::npos ) return "" ;

		return str.substr( pos ) ;
	}

	std::string 
	stringhlp::rtrim( const std::string& str )
	{
		if ( str.empty() ) return str ;

		auto pos = str.find_last_not_of( __delimiters ) ;

		if ( pos == std::string::npos ) return "" ;

		return str.substr( 0, pos + 1 ) ;
	}

	std::string 
	stringhlp::trim( const std::string& str )
	{
		return rtrim( ltrim( str ) ) ;
	}

	std::string 
	stringhlp::replace( const std::string& str, const std::string& find, const std::string& replace ) 
	{
		if ( str.empty()  ) return str ;
		if ( find.empty() ) return str ;

		auto str2 = str ;

		auto pos = str2.find( find ) ;
 
		while( true )
		{
			if ( pos == std::string::npos ) break ;
	
			str2.replace( pos, find.length(), replace ) ;

			if ( replace.empty() )
				 pos = str2.find( find ) ;
			else
				 pos = str2.find( find, pos + find.length() ) ;
		}

		return str2 ;
	}

	std::vector<std::string> 
	stringhlp::split( const std::string& str, char delimiter )
	{
		std::vector<std::string> result ;

		std::stringstream ss( str ) ;
		std::string item ;

		while ( std::getline( ss, item, delimiter ) )
			result.push_back( item ) ;

		return result ;
	}

	bool 
	stringhlp::endsWith( const std::string& str, const std::string& suffix, bool caseSensitive )
	{
		if ( str.empty()                ) return false ;
		if ( suffix.empty()             ) return false ;
		if ( suffix.size() > str.size() ) return false ;

		auto str2    = str    ;
		auto suffix2 = suffix ;

		if ( ! caseSensitive ) // case insensitive, convert to upper case
		{
			str2	= toUpper( str2    ) ;
			suffix2	= toUpper( suffix2 ) ;
		}

		auto pos2 = str2.rfind( suffix2 ) ;

		if ( pos2 == std::string::npos ) return false ;

		return str2.size() == suffix2.size() + pos2 ;
	}

	bool
	stringhlp::startsWith( const std::string& str, const std::string& prefix, bool caseSensitive )
	{
		if ( str.empty()                ) return false ;
		if ( prefix.empty()             ) return false ;
		if ( prefix.size() > str.size() ) return false ;

		auto str2    = str    ;
		auto prefix2 = prefix ;

		if ( ! caseSensitive ) // case insensitive, convert to upper case
		{
			str2	= toUpper( str2    ) ;
			prefix2	= toUpper( prefix2 ) ;
		}

		auto pos2 = str2.find( prefix2 ) ;

		if ( pos2 == std::string::npos ) return false ;

		return pos2 == 0 ;
	}

	bool
	stringhlp::contains( const std::string& str, const std::string& subString, bool caseSensitive )
	{
		if ( str.empty()                   ) return false ;
		if ( subString.empty()             ) return true  ;
		if ( subString.size() > str.size() ) return false ;

		auto str2       = str       ;
		auto subString2 = subString ;

		if ( ! caseSensitive ) // case insensitive, convert to upper case
		{
			str2		= toUpper( str2       ) ;
			subString2	= toUpper( subString2 ) ;
		}

		auto pos2 = str2.find( subString2 ) ;

		return pos2 != std::string::npos ;
	}

	long
	stringhlp::positionOf( const std::string& str, const std::string& subString, bool caseSensitive ) // return -1 if not found
	{
		if ( str.empty()                   ) return false ;
		if ( subString.empty()             ) return true  ;
		if ( subString.size() > str.size() ) return false ;

		auto str2       = str       ;
		auto subString2 = subString ;

		if ( ! caseSensitive ) // case insensitive, convert to upper case
		{
			str2		= toUpper( str2       ) ;
			subString2	= toUpper( subString2 ) ;
		}

		auto pos2 = str2.find( subString2 ) ;

		if ( pos2 == std::string::npos ) return -1 ;
		return pos2 ;
	}

	long 
	stringhlp::positionOfNot( const std::string& str, const std::string& delim )
	{
		if ( str.empty() ) return -1 ;

		auto pos = str.find_first_not_of( delim ) ;

		if ( pos == std::string::npos ) return -1 ;

		return pos ;
	}

	std::string 
	stringhlp::toUpper( const std::string& str )
	{
		if ( str.empty() ) return str ;

		auto result = str ; 

		for ( auto& c : result )
			c = std::toupper( c ) ;

		return result ;
	}

	std::string
	stringhlp::toLower( const std::string& str )
	{
		if ( str.empty() ) return str ;

		auto result = str ; 

		for ( auto& c : result )
			c = std::tolower( c ) ;

		return result ;
	}

	std::string
	stringhlp::left( const std::string& str, long chars )
	{
		if ( str.empty() ) return str ;

		if ( chars <= 0 ) return "" ;

		if ( chars >= str.length() ) return str ;

		return str.substr( 0, chars ) ; 
	}

	std::string
	stringhlp::right( const std::string& str, long chars )
	{
		if ( str.empty() ) return str ;

		if ( chars <= 0 ) return "" ;

		if ( chars >= str.length() ) return str ;

		return str.substr( str.length() - chars, chars ) ; 
	}

	std::string
	stringhlp::substr( const std::string& str, long startPos )
	{
		if ( str.empty() ) return str ;

		if ( startPos < 0 ) return "" ;

		if ( startPos == 0 ) return str ;

		auto chars = str.length() - startPos ;

		if ( chars <= 0 ) return "" ;

		return right( str, chars ) ; 
	}

	std::string
	stringhlp::substr( const std::string& str, long startPos, long chars )
	{
		auto str1 = substr( str, startPos ) ;

		return left( str1, chars ) ;
	}

	std::string
	stringhlp::printf( unsigned long bytes, const std::string& format, ... )
	{
  		va_list args ;
    	va_start( args, format ) ;

		auto str = printf( bytes, format, args ) ;

    	va_end( args ) ;
		return str ;
	}

	std::string
	stringhlp::printf( unsigned long bytes, const std::string& format, va_list args )
	{
		std::vector<char> buffer ;
		buffer.resize( bytes + 10 ) ;
		std::fill( buffer.begin(), buffer.end(), 0 ) ;
		
		std::vsnprintf( buffer.data(), bytes, format.c_str(), args ) ;

		return buffer.data() ; 	
	}

	std::string 
	stringhlp::reverse( const std::string& str ) 
	{
		if ( str.empty() ) return str ;

		auto str1 = str ; 

		std::reverse( str1.begin(), str1.end() ) ;

		return str1 ;
	}

} // end ns

