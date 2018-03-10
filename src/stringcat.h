#pragma once

namespace alby::bigmath
{
	class stringcat
	{
		protected:
			std::stringstream ss ;

		public:
			virtual ~stringcat() 
			{}

			stringcat() 
			{}

			stringcat( const stringcat& rhs ) 
			{
				ss = std::stringstream() ;
				ss << rhs.ss.str() ;
			}

			stringcat& operator=( const stringcat& rhs ) 
			{
				ss = std::stringstream() ;
				ss << rhs.ss.str() ;

				return *this ;
			}

			std::string toString() const 
		    {
		        return ss.str() ;
    		}

			friend std::ostream& operator<<( std::ostream& os, const stringcat& rhs ) 
			{  
				os << rhs.toString() ;  
				return os ;   
			}  

			operator std::string() const 
			{
				return toString() ;
			}
			
			template<typename U, typename... T>
			stringcat( const U& head, const T&... tail ) 
			{
				stream( head, tail ... ) ;
			}

		protected:
			void stream() 
			{}

			template<typename U, typename ... T>
			void stream( const U& head, const T& ... tail ) 
			{
				ss << head ;

				stream( tail ... ) ;			
			}
	} ;
} 




