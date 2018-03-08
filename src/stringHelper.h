#pragma once

namespace alby
{
	namespace assemblyAttributes
	{
		namespace lib
		{
			class stringHelper
			{
				protected:
					const static std::wstring __delimiters ;

				public:
					stringHelper();
					virtual ~stringHelper();

					static std::wstring stringHelper::s2ws( const std::string&  str  ) ;
					static std::string  stringHelper::ws2s( const std::wstring& wstr ) ;

					static std::wstring stringHelper::rtrim( const std::wstring& wstr ) ;
					static std::wstring stringHelper::ltrim( const std::wstring& wstr ) ;
					static std::wstring stringHelper::trim ( const std::wstring& wstr ) ;

					static std::vector<std::wstring> stringHelper::split( const std::wstring& wstr, wchar_t delimiter ) ;

					static bool endsWith  ( const std::wstring& str, const std::wstring& suffix,    bool caseSensitive = true ) ;
					static bool startsWith( const std::wstring& str, const std::wstring& prefix,    bool caseSensitive = true ) ;
					static bool contains  ( const std::wstring& str, const std::wstring& subString, bool caseSensitive = true ) ;

					static std::wstring toUpper( const std::wstring& str ) ;
					static std::wstring toLower( const std::wstring& str ) ;
			} ;

		} // ns lib

	} // ns assemblyAttributes

} //  ns alby

