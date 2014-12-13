#include <cstdio>
#include <atlstr.h>
#include "Exception.h"

namespace exception{
	//--------------------------------------------------------
	// 処理	コンストラクタ
	// 引数	argMessage 受け取ったエラーメッセージ
	// 返値	none
	//--------------------------------------------------------
	Exception::Exception(const std::string& argMessage)
		: message(argMessage)
	{}
	//--------------------------------------------------------
	// 処理	コンストラクタ
	// 引数	argMessage 受け取ったエラーメッセージ
	// 引数	argFile エラーが起きたファイル名
	// 引数	argFunction エラーが起きた関数名
	// 引数	argLine エラーが起きた行番号
	// 返値	none
	//--------------------------------------------------------
	Exception::Exception(const std::string& argMessage, const std::string& argFile,
		const std::string& argFunction, const int argLine)
		: message(argMessage), fileName(argFile),
		functionName(argFunction), line(argLine)
	{}
	//--------------------------------------------------------
	// 処理	デストラクタ
	// 引数	none
	// 返値	none
	//--------------------------------------------------------
	Exception::~Exception() throw(){}
	//--------------------------------------------------------
	// 処理	何のエラーが起きたかメッセージを返す
	// 引数	
	// 返値	エラーメッセージ
	//--------------------------------------------------------
	const char* Exception::what()const throw(){//PCTSTR
		return NULL;
	}
	//--------------------------------------------------------
	// 処理	エラーが何のファイルで起きたか返す
	// 引数	
	// 返値	エラーファイル名
	//--------------------------------------------------------
	const std::string& Exception::getFileName()const{
		return fileName;
	}
	//--------------------------------------------------------
	// 処理	エラーが何のファイルで起きたか返す
	// 引数	
	// 返値	エラーファイル名
	//--------------------------------------------------------
	const std::string& Exception::getFunction()const{
		return functionName;
	}
	//--------------------------------------------------------
	// 処理	エラーが何行目で起きたか返す
	// 引数	
	// 返値	エラー行番号
	//--------------------------------------------------------
	const int Exception::getLineNumber()const{
		return line;

	}
	//--------------------------------------------------------
	// 処理	エラーがメッセージを変えす
	// 引数	
	// 返値	エラーメッセージ
	//--------------------------------------------------------
	const std::string& Exception::getMessage()const{
		return message;
	}
}