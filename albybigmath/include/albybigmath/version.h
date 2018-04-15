#pragma once

#define ALBY_BIGMATH_VERSION "1.0.0.1"

namespace alby::bigmath
{
	class version
	{
		public:
			virtual ~version() ;

			static const std::string _version ;

			version() ;
			version& operator=( const version& rhs ) ; 

			static std::string getVersion() ;
	} ;
} 
