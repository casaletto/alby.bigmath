#pragma once

namespace alby::bigmath
{
	class mpq
	{
		protected:
			mpq_t_wrapper* p = nullptr ;

			void init() ;
			void cleanup() ;

			static void compare( const mpq& op1, const mpq& op2, bool& equal, bool& moreThan, bool& lessThan ) ;
	
		public:
			virtual ~mpq() ;

			mpq() ;  
			mpq( const mpq& rhs ) ;
			mpq( long l ) ;
			mpq( const char* ) ;
			mpq( const std::string& ) ;
			
			mpq& operator=( const mpq& rhs ) ;

			static mpq_t& deref( const mpq& mpq ) ; // get the important part of the wrapper, the actual mpq_t

			std::string toString()          ;
			operator    std::string()       ;
			operator    std::string() const ;

			friend std::ostream& operator<<( std::ostream& os, const mpq& mpq ) ;

			mpq& operator-=( const mpq& op2 ) ;
			mpq& operator+=( const mpq& op2 ) ;
			mpq& operator*=( const mpq& op2 ) ;
			mpq& operator/=( const mpq& op2 ) ;

			friend mpq operator-( const mpq& op1, const mpq& op2 ) ;
			friend mpq operator+( const mpq& op1, const mpq& op2 ) ;
			friend mpq operator*( const mpq& op1, const mpq& op2 ) ;
			friend mpq operator/( const mpq& op1, const mpq& op2 ) ;

			friend bool operator> ( const mpq& op1, const mpq& op2 ) ; 
			friend bool operator< ( const mpq& op1, const mpq& op2 ) ;
			friend bool operator>=( const mpq& op1, const mpq& op2 ) ; 
			friend bool operator<=( const mpq& op1, const mpq& op2 ) ;
			friend bool operator==( const mpq& op1, const mpq& op2 ) ;
			friend bool operator!=( const mpq& op1, const mpq& op2 ) ;

			std::string numerator()   ;
			std::string denominator() ;			
			void	    reduce()      ;			

			mpq neg() ;
			mpq inv() ; 
			mpq abs() ;
	} ;
} 

