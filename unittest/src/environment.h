#pragma once

namespace t 
{
	class environment : public testing::Environment
	{
		public:
			environment() ;
			virtual ~environment() ;

			static void 		init() ;
			static environment* get() ;

			virtual void 		SetUp() ;
			virtual void 		TearDown() ;

			virtual void 		hello() ;

		protected:
			static environment* pEnvironment ;
	} ;
}
