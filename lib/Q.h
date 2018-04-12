#pragma once

namespace alby::bigmath
{
	class R ; // forward declaration

	class Q
	{
		protected:
			mpq_t_wrapper* p = nullptr ;

			void init() ;
			void cleanup() ;

			static void compare( const Q& op1, const Q& op2, bool& equal, bool& moreThan, bool& lessThan ) ;
	
		public:
			virtual ~Q() ;

			Q() ;  
			Q( const Q& rhs ) ;
			Q( long l ) ;
			Q( const char* ) ;
			Q( const std::string& ) ;
			Q( long l, const char* ) ;
			Q( long l, const std::string& ) ;
			Q& operator=( const Q& rhs ) ;

			explicit Q( const R& rhs ) ; // explicit constructor 
		
			operator    std::string() ;
			operator    std::string() const ;
			std::string toString() ;
			R 			toR() ;

			static mpq_t& deref( const Q& q ) ; // get the important part of the wrapper, the actual mpq_t

			friend std::ostream& operator<<( std::ostream& os, const Q& q ) ;

			Q& operator-=( const Q& op2 ) ;
			Q& operator+=( const Q& op2 ) ;
			Q& operator*=( const Q& op2 ) ;
			Q& operator/=( const Q& op2 ) ;

			friend Q operator-( const Q& op1, const Q& op2 ) ;
			friend Q operator+( const Q& op1, const Q& op2 ) ;
			friend Q operator*( const Q& op1, const Q& op2 ) ;
			friend Q operator/( const Q& op1, const Q& op2 ) ;

			friend bool operator> ( const Q& op1, const Q& op2 ) ; 
			friend bool operator< ( const Q& op1, const Q& op2 ) ;
			friend bool operator>=( const Q& op1, const Q& op2 ) ; 
			friend bool operator<=( const Q& op1, const Q& op2 ) ;
			friend bool operator==( const Q& op1, const Q& op2 ) ;
			friend bool operator!=( const Q& op1, const Q& op2 ) ;

			void	    reduce()      ;			
			std::string numerator()   ;
			std::string denominator() ;			

			Q neg() ;
			Q inv() ; 
			Q abs() ;
	} ;
} 

