#pragma once

namespace alby::bigmath
{
	class pi
	{
		protected:
			class nonic_term_t
			{
				public:
					mpfr a ;
					mpfr r ;
					mpfr s ;
					mpfr t ;
					mpfr u ;
					mpfr v ;
					mpfr w ;

					virtual ~nonic_term_t() 
					{}

					nonic_term_t() 
					{}

					nonic_term_t( const nonic_term_t& rhs ) 
					{					
						*this = rhs ;	
					}

					nonic_term_t& operator=( const nonic_term_t& rhs ) 
					{
						if ( this != &rhs )
						{
							a = rhs.a ;
							r = rhs.r ;
							s = rhs.s ;
							t = rhs.t ;
							u = rhs.u ;
							v = rhs.v ;
							w = rhs.w ;
						}
						return *this ;
					} 

					std::string toString()
					{
						auto dp = 20 ;
						return stringcat
						( 
							"t  = ", t.toDecimalPlaces      ( dp ), "\n", 
							"u  = ", u.toDecimalPlaces      ( dp ), "\n", 
							"v  = ", v.toDecimalPlaces      ( dp ), "\n", 
							"w  = ", w.toDecimalPlaces      ( dp ), "\n", 
							"a  = ", a.toDecimalPlaces      ( dp ), "\n", 
							"s  = ", s.toDecimalPlaces      ( dp ), "\n", 
							"r  = ", r.toDecimalPlaces      ( dp ), "\n" 
							"pi = ", a.inv().toDecimalPlaces( dp ), "\n" 
						 ) ;
					}
			} ;

		protected:
			static mpfr         nilakantha_term( unsigned long n ) ;
			static mpfr         ramanujan_term ( unsigned long n, std::map<unsigned long, mpfr>& factorial ) ;
			static nonic_term_t nonic_term     ( unsigned long n, nonic_term_t& prev ) ;

		public:
			virtual ~pi() ;

			pi() ;
			pi( const pi& rhs ) ;
			pi& operator=( const pi& rhs ) ; 

			static mpfr nilakantha( unsigned long n ) ;
			static mpfr ramanujan ( unsigned long n ) ;			
			static mpfr nonic     ( unsigned long n ) ;			
	} ;
} 
