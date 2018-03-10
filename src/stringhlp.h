#pragma once

namespace alby::bigmath
{
	class stringhlp
	{
		protected:
			const static std::string __delimiters ;

			static std::string printf( unsigned long bytes, const std::string& format, va_list args ) ;

		public:
			stringhlp();
			virtual ~stringhlp() ;

			static std::string rtrim( const std::string& str ) ;
			static std::string ltrim( const std::string& str ) ;
			static std::string trim ( const std::string& str ) ;

			static std::vector<std::string> split( const std::string& str, char delimiter ) ;

			static bool endsWith  ( const std::string& str, const std::string& suffix,    bool caseSensitive = true ) ;
			static bool startsWith( const std::string& str, const std::string& prefix,    bool caseSensitive = true ) ;
			static bool contains  ( const std::string& str, const std::string& subString, bool caseSensitive = true ) ;

			static std::string toUpper( const std::string& str ) ;
			static std::string toLower( const std::string& str ) ;

			static std::string printf( unsigned long bytes, const std::string& format, ... ) ;
		
	} ;
} 
