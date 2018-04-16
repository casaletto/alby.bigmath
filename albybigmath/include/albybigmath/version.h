#pragma once

#define ALBY_BIGMATH_VERSION "1.0.0.1"
 
namespace alby::bigmath
{
	class version
	{
		public:
			static const std::string _version ;

			virtual ~version() ;
			version() ;

			version& operator=( const version& rhs ) ; 

			static std::string getVersion() ;
			static std::string system( const std::string& cmd ) ;

	} ;
} 
