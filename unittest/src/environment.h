#pragma once

namespace t 
{
	class environment : public testing::Environment
	{
		public:
			environment() ;
			virtual ~environment() ;

			virtual void 		SetUp() ;
			virtual void 		TearDown() ;
			static void 		set( environment* p ) ;
			static environment* get() ;

			virtual void 		hello() ;

		protected:
			static environment* pEnvironment ;
	} ;
}
