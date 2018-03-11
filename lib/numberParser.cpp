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
#include "./numberParser.h"

//
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
//

namespace alby::bigmath 
{
	numberParser::numberParser()
	{
	}

	numberParser::~numberParser()
	{
	}

	bool
	numberParser::normalise( const std::string& str, std::string& strScientificNotation ) 
	{
		// return true if valid 
		// return the normalised value in scientific notation +-[1-9].[0-9][0-9][0-9]E+-[1-9].[0-9][0-9][0-9] 
		// callers should throw an exception if they want to

		strScientificNotation = "" ;	

		std::string decimalSign  ;
		std::string decimal      ;
		std::string fraction     ; 
		std::string exponentSign ;
		std::string exponent     ;

		auto ok = regex( str, decimalSign, decimal, fraction, exponentSign, exponent ) ;

		if ( ! ok ) return false ;

		// raw scientific notation
		strScientificNotation = decimalSign + decimal + "." + fraction + "E" + exponentSign + exponent ;	

		// now fix such that decimal starts with 1..9


		return true ;
	}

	bool
	numberParser::regex
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

		auto expr = R"(^([+\-])?(\d+)(\.(\d+))?([eE]([+\-])?(\d+))?$)" ; // see above

		std::regex  regex( expr ) ;
		std::smatch sm ;

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

		decimalSign		= sm[1] ;
		decimal			= sm[2] ;
		fraction		= sm[4] ;
		exponentSign	= sm[6] ;
		exponent		= sm[7] ;

		//std::cout << "regex ds [" << decimalSign  << "]" << std::endl ;
		//std::cout << "regex d  [" << decimal      << "]" << std::endl ;
		//std::cout << "regex f  [" << fraction     << "]" << std::endl ;
		//std::cout << "regex es [" << exponentSign << "]" << std::endl ;
		//std::cout << "regex e  [" << exponent     << "]" << std::endl ;

		// remove leading zeros from decimal and exponent
		// remove trailing zeros from fraction
		decimal  = stringhlp::ltrim( decimal,  "0" ) ;
		fraction = stringhlp::rtrim( fraction, "0" ) ;
		exponent = stringhlp::ltrim( exponent, "0" ) ;

		if ( decimalSign.empty() ) 
		     decimalSign = "+" ;

		if ( decimal.empty() ) 
		     decimal = "0" ;

		if ( fraction.empty() ) 
		     fraction = "0" ;

		if ( exponentSign.empty() ) 
		     exponentSign = "+" ;

		if ( exponent.empty() ) 
		     exponent = "0" ;

		// fix the scientific notation, ie make decimal in the range [ 1.0, 10 )
		fixScientificNotation( decimalSign, decimal, fraction, exponentSign, exponent ) ;
		


		return matched ;
	}

	// 0.123456789e10 ==>
	// 1.23456789e9

	void
	numberParser::fixScientificNotation
	( 
		std::string& decimalSign, 
		std::string& decimal, 
		std::string& fraction, 
		std::string& exponentSign,	 
		std::string& exponent               
	)
	{
		// assume exponent can be expressed by a long 
		// 8 bytes = 64 bits = 0x7FFFFFFFFFFFFFFF = 9,223,372,036,854,775,807

		// handle 0.0, special case
		if ( decimal + "." + fraction == "0.0" )
		{
			decimalSign  = "+" ;
			exponentSign = "+" ;
			exponent     = "0" ;
			return ;
		}

		// is the decimal a one digit number, from 1 to 9?		
		char c = decimal[0] ;
		if ( decimal.length() == 1 )
		{
			if ( c >= '1' && c <= '9' ) return ; // nothing to do
		}

		// is the decimal a one digit number, ie 0? 
		if ( decimal.length() == 1 )
		{
			if ( c == '0' ) 
			{
				// find pos of first non zero in fraction, shift dp to the right
				auto pos = stringhlp::positionOfNot( fraction, "0" ) ;

				decimal  = fraction.substr( pos, 1  ) ;
				fraction = fraction.substr( pos + 1 ) ;

				if ( fraction.empty() ) 
					 fraction = "0" ;

				// subtract pos from the exponent			
				auto expstr = exponentSign + exponent ;
				long exp = std::atol( expstr.c_str() ) ;
				exp = exp - pos -1 ;

				exponentSign = exp < 0 ? "-" : "+" ;
				exponent     = stringhlp::printf( 1000, "%ld", std::abs( exp ) ) ;
				return ;
			}
		}

	}

	
} // end ns

