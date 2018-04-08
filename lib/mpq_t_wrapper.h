#pragma once

namespace alby::bigmath
{
	class mpq_t_wrapper
	{
		protected:
			mpq_t        		 x                ;
			static unsigned long objectCount      ;
			static void (*free)( void *, size_t ) ;

		public:
			virtual ~mpq_t_wrapper() ;
			mpq_t_wrapper() ;

			mpq_t* 				 get()            ;
			static unsigned long getObjectCount() ;

			mpq_t_wrapper( const mpq_t_wrapper& rhs )            = delete ; // do not copy these objects
			mpq_t_wrapper& operator=( const mpq_t_wrapper& rhs ) = delete ; // do not copy these objects

			std::string toString() ; 
	} ;
} 


