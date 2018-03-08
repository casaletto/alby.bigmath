#pragma once

namespace alby   
{
	namespace assemblyAttributes 
	{
		namespace lib 
		{
			class sprintf
			{
				protected:
					std::wstringstream _ss ;

				public:
					sprintf()
					{
					}

					virtual ~sprintf()
					{
					}

					sprintf::sprintf( const sprintf& rhs ) 
					{
						_ss = std::wstringstream() ;
						this->_ss << rhs._ss.str() ;
					}

					sprintf& sprintf::operator=( const sprintf& rhs ) 
					{
						_ss = std::wstringstream();
						this->_ss << rhs._ss.str();

						return *this;
					}

					std::wstring ws()
					{
						return _ss.rdbuf()->str() ;
					}

					std::string s()
					{		
						return lib::stringHelper::ws2s( this->ws() ) ;
					}

					template<typename U, typename ... T>
					sprintf( const U& head, const T& ... tail )
					{
						stream( head, tail ... ) ;
					}

					void stdOutput()
					{
						std::cout << this->s() << std::endl ;
					}

					void stdError()
					{
						std::cerr << this->s() << std::endl;
					}

					void debug()
					{
						::OutputDebugStringW( this->ws().c_str() );
					}

				protected:

					void stream()
					{
					}

					template<typename U, typename ... T>
					void stream( const U& head, const T& ... tail ) 
					{
						_ss << head ;

						stream( tail ... ) ;
					}

			} ; // end class

		} // ns lib

	} // ns assemblyAttributes

} //  ns alby

