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
#include "stringhlp.h"

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
	stringhlp::ltrim( const std::string& str )
	{
		if ( str.empty() ) return str ;

		return str.substr( str.find_first_not_of( __delimiters ) ) ;
	}

	std::string 
	stringhlp::rtrim( const std::string& str )
	{
		if ( str.empty() ) return str ;

		return str.substr( 0, str.find_last_not_of( __delimiters ) + 1 ) ;
	}

	std::string 
	stringhlp::trim( const std::string& str )
	{
		return rtrim( ltrim( str ) ) ;
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

	std::string 
	stringhlp::toUpper( const std::string& str )
	{
		if ( str.empty() ) return str ;

		auto result = str ; 

		std::transform( result.begin(), 
						result.end(), 
						result.begin(), 
						[] (unsigned char c) -> unsigned char 
						{ 
							return std::toupper( c ) ; 
						} ) ; 

		return result ;
	}

	std::string
	stringhlp::toLower( const std::string& str )
	{
		if ( str.empty() ) return str ;

		auto result = str ; 

		std::transform( result.begin(), 
						result.end(), 
						result.begin(), 
						[] (unsigned char c) -> unsigned char 
						{ 
							return std::tolower( c ) ; 
						} ) ; 

		return result ;
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

}
