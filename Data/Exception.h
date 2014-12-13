#pragma once 
#include <exception>
#include <string>

#define THROW_EXCEPTION(EXCEPTION_TYPE,message) \
	throw EXCEPTION_TYPE(message, __FILE__, __FUNCTION__, __LINE__)

namespace exception{
	class Exception :public std::exception{
	public:
		Exception(const std::string& argMessage);
		Exception(const std::string& argMessage,
			const std::string& argFile,
			const std::string& argFunction,
			const int argLine);
		virtual ~Exception() throw();
		const std::string& getFileName()const;
		const std::string& getFunction()const;
		const std::string& getMessage()const;
		const int getLineNumber()const;
		virtual const char* what()const throw();
	private:

		//Exception(const Exception& arg); ƒCƒ‰ƒ“
		//Exception operator=(const Exception& arg);ƒCƒ‰ƒ“

		const std::string message;
		const std::string fileName;
		const std::string functionName;
		int line;
	};
}