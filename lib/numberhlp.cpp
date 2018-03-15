#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <inttypes.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <vector>
#include <fstream>
#include <iomanip>
#include <assert.h>    
#include <algorithm>
#include <regex>

#include "./stringhlp.h"
#include "./stringcat.h"
#include "./numberhlp.h"

// the 4 kinds of numbers
//
// +-#####
// +-#####.####
// +-#####     E-+#####
// +-#####.####E-+#####
//
// [decimal      ]
// [sign][integer] 
//
// [decimal      ] . [fraction] 
// [sign][integer] . [integer ] 
//
// [decimal      ] E [exponent     ]
// [sign][integer] E [sign][integer]
//
// [decimal      ] . [fraction] E [exponent     ]
// [sign][integer] . [integer ] E [sign][integer]

namespace alby::bigmath 
{
	numberhlp::numberhlp()
	{
	}

	numberhlp::~numberhlp()
	{
	}

	bool
	numberhlp::regex
	( 
		const std::string& 	str, 
		std::string& 		decimalSign, 
		std::string& 		decimal, 
		std::string& 		fraction, 
		std::string& 		exponentSign,	 
		std::string& 		exponent 
	)
	{
		decimalSign 	= "" ; 
		decimal 		= "" ;
		fraction 		= "" ; 
		exponentSign	= "" ;	 
		exponent 		= "" ; 

		auto str1 = stringhlp::trim( str ) ;
		str1 = stringhlp::toUpper( str1 ) ;

		static const char* expr = R"(^([+\-])?(\d+)(\.(\d+))?([eE]([+\-])?(\d+))?$)" ; // regex pattern for a number, eg 6.02e23

		std::regex  regex( expr ) ;
		std::smatch sm ;

		// do the regex, return if no match, up to caller to throw an exception if required
		auto matched = std::regex_match( str1, sm, regex ) ; 
		if ( ! matched ) return false ;

		// 0 regex [-123456.12345678901234567890E+9876]
		// 1 regex [-]
		// 2 regex [123456]
		// 3 regex [.12345678901234567890]
		// 4 regex [12345678901234567890]
		// 5 regex [E+9876]
		// 6 regex [+]
		// 7 regex [9876]

		/// extract bits of the regex
		decimalSign		= sm[1] ;
		decimal			= sm[2] ;
		fraction		= sm[4] ;
		exponentSign	= sm[6] ;
		exponent		= sm[7] ;

		// remove leading zeros from decimal and exponent
		// remove trailing zeros from fraction
		decimal  = stringhlp::ltrim( decimal,  "0" ) ;
		fraction = stringhlp::rtrim( fraction, "0" ) ;
		exponent = stringhlp::ltrim( exponent, "0" ) ;

		// defaults 
		if ( decimalSign.empty()  ) decimalSign  = "+" ;
		if ( decimal.empty()      ) decimal      = "0" ;
		if ( fraction.empty()     )	fraction     = "0" ;
		if ( exponentSign.empty() ) exponentSign = "+" ;
		if ( exponent.empty()     ) exponent     = "0" ;
		
		return matched ;
	}

	void
	numberhlp::adjustScientificNotation
	( 
		std::string& decimalSign, 
		std::string& decimal, 
		std::string& fraction, 
		std::string& exponentSign,	 
		std::string& exponent               
	)
	{
		// adjust the number so that the decimal is from 1 to 9

		// assume exponent can be expressed by a long 
		// 8 bytes = 64 bits = 0x7FFFFFFFFFFFFFFF = 9,223,372,036,854,775,807

		// [ 0.0 ] 
		// handle 0.0, special case
		if ( decimal + "." + fraction == "0.0" )
		{
			decimalSign  = "+" ;
			exponentSign = "+" ;
			exponent     = "0" ;
			return ;
		}

		// [ 1.0, 10.0 ) 
		// is the decimal a one digit number, from 1 to 9?		
		auto c = decimal[0] ;
		if ( decimal.length() == 1 )
		{
			if ( c >= '1' && c <= '9' ) return ; // nothing to do
		}

		// ( 0.0, 1.0 )
		if ( decimal.length() == 1 ) // c == '0'
		{
			// find pos of first non zero in fraction, shift dp to the right
			auto pos = stringhlp::positionOfNot( fraction, "0" ) ;

			decimal  = fraction.substr( pos, 1  ) ;
			fraction = fraction.substr( pos + 1 ) ;

			if ( decimal.empty()  ) decimal  = "0" ;
			if ( fraction.empty() ) fraction = "0" ;

			// subtract pos from the exponent			
			auto expstr = exponentSign + exponent ;
			auto exp = std::atol( expstr.c_str() ) ;
			exp = exp - pos - 1 ;

			exponentSign = exp < 0 ? "-" : "+" ;
			exponent     = stringhlp::printf( 1000, "%ld", std::abs( exp ) ) ;
			return ;
		}

		// [ 10.0, inf ) 
		// any number 10 or above, have to shift do x places to the left

		auto dpShift = decimal.length() - 1 ;
		
		// shift the decimal and fraction
		auto temp = decimal ;
		decimal  = stringhlp::left( temp, 1 ) ;

		fraction = stringhlp::substr( temp, 1 ) + stringhlp::rtrim( fraction, "0" ) ;
		fraction = stringhlp::rtrim( fraction, "0" ) ;

		if ( decimal.empty()  ) decimal  = "0" ;
		if ( fraction.empty() ) fraction = "0" ;

		// add dp shift to the exponent			
		auto expstr = exponentSign + exponent ;
		auto exp = std::atol( expstr.c_str() ) ;
		exp = exp + dpShift ;

		exponentSign = exp < 0 ? "-" : "+" ;
		exponent     = stringhlp::printf( 1000, "%ld", std::abs( exp ) ) ;		
	}

	bool
	numberhlp::toScientificNotation
	( 
		const std::string& str, 
		std::string&       strScientificNotation,
		unsigned long 	   significantFigures
	) 
	{
		// convert a number to the form aaaa.bbbbEeee, eg 314.15 => +3.1415e+2
		// return true if valid 

		strScientificNotation = "" ;	

		std::string decimalSign  ;
		std::string decimal      ;
		std::string fraction     ; 
		std::string exponentSign ;
		std::string exponent     ;

		// convert the number to standard form 
		auto ok = regex
		( 
			str, 
			decimalSign, 
			decimal, 
			fraction, 
			exponentSign, 
			exponent 
		) ;

		if ( ! ok ) return false ;

		// normalise the exponent
		adjustScientificNotation
		( 
			decimalSign, 
			decimal, 
			fraction, 
			exponentSign, 
			exponent 
		) ;

		// significant figures and rounding is required
		if ( significantFigures > 0 )
		{
			toSignificantFigures
			( 
				significantFigures + 1, 
				decimal, 
				fraction 
			) ;	

			toRound
			( 
				significantFigures,
				decimal, 
				fraction, 
				exponent 
			) ;

			toSignificantFigures
			( 
				significantFigures, 
				decimal, 
				fraction 
			) ;	
		}

		strScientificNotation = decimalSign + decimal + "." + fraction + "E" + exponentSign + exponent ;	
		return true ;
	}

	bool
	numberhlp::toDecimal
	( 
		const std::string& str, 
		std::string&       strDecimal,
		unsigned long 	   significantFigures	
	) 
	{
		// we convert the string to its canonical exponential representation
		// and then convert back to a normalised decimal format, eg 
		// -000000123.45678000000 => -1.2345678E+2 => -123.45678

		// assume exponent can be expressed by a long 
		// 8 bytes = 64 bits = 0x7FFFFFFFFFFFFFFF = 9,223,372,036,854,775,807
		
		strDecimal = "" ;

		std::string decimalSign  ;
		std::string decimal      ;
		std::string fraction     ; 
		std::string exponentSign ;
		std::string exponent     ;

		// convert the number to standard form 
		auto ok = regex
		( 
			str, 
			decimalSign, 
			decimal, 
			fraction, 
			exponentSign, 
			exponent 
		) ;

		if ( ! ok ) return false ;

		// normalise the exponent
		adjustScientificNotation
		( 
			decimalSign, 
			decimal, 
			fraction, 
			exponentSign, 
			exponent 
		) ;

		//ALBY TO Do rounding here - should be same code as above to sci notation
		// to sig fig + 1
		// round
		// to sig fig
		//




		// remove the exponent

		// exponent as a number
		auto expstr = exponentSign + exponent ;
		auto exp = std::atol( expstr.c_str() ) ;

		if ( decimal == "0" &&  fraction == "0" ) // [ 0.0 ] special case 0.0 
		{
			decimalSign = "+" ;
		}
		else
		if ( exp == 0 ) // [ 1.0, 10 ) numbers from 1 to 10
		{
			// nothing to do
		}
		else
		if ( exp > 0 ) // [ 10, inf ] numbers 10 and above
		{
			auto decimal2 = decimal + fraction + std::string( exp, '0' ) ;
			auto decimal3 = stringhlp::left( decimal2, exp + 1 ) ;

			auto fraction2 = stringhlp::substr( decimal2, exp + 1 ) ;
			fraction2      = stringhlp::rtrim( fraction2, "0" ) ;
			
			if ( decimal3.empty()  ) decimal3  = "0" ;
			if ( fraction2.empty() ) fraction2 = "0" ;

			decimal  = decimal3  ;
			fraction = fraction2 ;
		}
		else // exp < 0, ( 0.0, 1.0 ) numbers between 0 and 1
		{
			auto fraction2 = std::string( std::abs( exp ) - 1, '0' ) + decimal + fraction  ;
			fraction2      = stringhlp::rtrim( fraction2, "0" ) ;
		
			decimal  = "0" ;
			fraction = fraction2 ;
		}

		// format to significant figures
		toSignificantFigures
		( 
			significantFigures, 
			decimal, 
			fraction 
		) ;	

		strDecimal = decimalSign + decimal + "." + fraction ;	
		return true ;
	}

	void 
	numberhlp::toSignificantFigures
	( 
		unsigned long significantFigures, 
		std::string&  decimal, 
		std::string&  fraction	
	)
	{
		// note: this function does not do rounding

		if ( significantFigures == 0 ) return ; // 0 means do nothing

		if ( decimal == "0" ) // 0.xxxxxxxx
		{
			auto fraction1 = std::string() ;
			auto fraction2 = fraction ;

			auto pos = stringhlp::positionOfNot( fraction, "0" ) ; // position of first non zero

			if ( pos >= 1 )
 			     fraction1 = stringhlp::left( fraction, pos ) ;

			if ( pos >= 0 )
 			     fraction2 = stringhlp::substr( fraction, pos ) ;

			fraction2 += std::string( significantFigures, '0' ) ;
			fraction2  = stringhlp::left( fraction2, significantFigures ) ;

			fraction = fraction1 + fraction2 ;
			return ; 			
		}

		// decimal and fraction are the correct length
		auto declen  = decimal.length()  ; 
		auto fraclen = fraction.length() ; 

		if ( declen + fraclen == significantFigures ) return ;

		// decimal is the exact length
		if ( declen == significantFigures ) 
		{
			fraction = "0" ;
			return ; 
		}

		// decimal is too long, needs to be truncated to sf and then appended by 0's
		if ( declen > significantFigures ) 
		{
			decimal  = stringhlp::left( decimal, significantFigures ) + std::string( declen - significantFigures, '0' ) ;
			fraction = "0" ;
			return ; 
		}

		// decimal + fraction is too long, needs to be truncated to sf
		if ( declen + fraclen > significantFigures ) 
		{
			fraction = stringhlp::left( fraction, significantFigures - declen ) ;
			return ; 
		}

		// decimal + fraction is too short, needs to be appended
		fraction += std::string( significantFigures - declen - fraclen, '0' ) ;  
	}

//ALBY here
	void 
	numberhlp::toRound
	(
		unsigned long significantFigures, 
		std::string&  decimal, 
		std::string&  fraction,	
		std::string&  exponent
	)
	{
		// note input must be standard exponential format, ie
		// [1-9].xxxxxEyyyyy

		if ( significantFigures == 0 ) return ; // 0 means do nothing
		
		auto declen  = decimal.length()  ; 
		auto fraclen = fraction.length() ; 
		auto explen  = exponent.length() ; 

		if ( declen  != 1 ) return ; // standard format expected
		if ( fraclen <  1 ) return ; 
		if ( explen  <  1 ) return ; 

		if ( significantFigures > declen + fraclen ) return ; // beyond the fraction boundary, nothing to round

		if ( significantFigures <= 2 )
			 if ( fraction == "0" ) return ; // nothing to do, ie x.0
		




	}

//ALBY TO DO change name to roundString ???
	bool 
	numberhlp::round
	( 
		const std::string& 	strNumber,        
		const std::string& 	strRoundingDigit, // last digit is the rounding digit	
		std::string& 		strResult 
	)
	{
		// [0, 4] round down, ie do nothing
		// [5, 9] round up
		//
		// return true if carry set			

		strResult = strNumber ;
		if ( strNumber.empty()        ) return false ; 
		if ( strRoundingDigit.empty() ) return false ; 

		auto _0 = (unsigned int) '0' ;

		auto roundingDigit = (unsigned int) stringhlp::left( strRoundingDigit, 1 )[0] ;		
		roundingDigit     -= _0 ;		

		if ( roundingDigit < 5 ) return false ; // round down, nothing to do

		// round up from now on
		auto strReverse = stringhlp::reverse( strResult ) ;
		auto carry = false ;

		for ( auto& c : strReverse ) 
		{
			auto value = (unsigned int) c ;
			value     -= _0 ;
			value++ ;

			if ( value <= 9 )
			{
				c = (char) ( value + _0 ) ;
				carry = false ;
				break ;
			}
			
			c = '0' ; // 10 == carry
			carry = true ;
		}

		// finished
		strResult = stringhlp::reverse( strReverse ) ;
		return carry ; 
	}

} // end ns

