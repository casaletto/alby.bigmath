#pragma once

namespace alby::bigmath
{
	class version
	{
		public:
			static const std::string _version ;

			virtual ~version() ;
			version() ;

			version& operator=( const version& rhs ) ; 

			static std::string getVersion( bool detailed = false  ) ;
			static std::string system    ( const std::string& cmd ) ;
	} ;
} 
