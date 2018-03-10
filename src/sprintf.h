#pragma once

namespace alby::bigmath
{
	class sprintf
	{
		protected:
			std::stringstream ss ;

		public:
			virtual ~sprintf() 
			{}

			sprintf() 
			{}

			sprintf( const sprintf& rhs ) 
			{
				ss = std::stringstream() ;
				ss << rhs.ss.str() ;
			}

			sprintf& operator=( const sprintf& rhs ) 
			{
				ss = std::stringstream() ;
				ss << rhs.ss.str() ;

				return *this ;
			}

			std::string toString() const 
		    {
		        return ss.str() ;
    		}

			friend std::ostream& operator<<( std::ostream& os, const sprintf& rhs ) 
			{  
				os << rhs.toString() ;  
				return os ;   
			}  

			operator std::string() const 
			{
				return toString() ;
			}
			
			template<typename U, typename... T>
			sprintf( const U& head, const T&... tail ) 
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




