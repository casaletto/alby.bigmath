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
		return true ;
	}

	bool
	numberParser::isInteger( const std::string& str ) 
	{
		// sanity check
		// return true if ok
		// can only contain 0-9

		return true ;
	}

} // end ns

