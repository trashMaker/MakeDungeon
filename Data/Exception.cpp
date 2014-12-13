#include <cstdio>
#include <atlstr.h>
#include "Exception.h"

namespace exception{
	//--------------------------------------------------------
	// ����	�R���X�g���N�^
	// ����	argMessage �󂯎�����G���[���b�Z�[�W
	// �Ԓl	none
	//--------------------------------------------------------
	Exception::Exception(const std::string& argMessage)
		: message(argMessage)
	{}
	//--------------------------------------------------------
	// ����	�R���X�g���N�^
	// ����	argMessage �󂯎�����G���[���b�Z�[�W
	// ����	argFile �G���[���N�����t�@�C����
	// ����	argFunction �G���[���N�����֐���
	// ����	argLine �G���[���N�����s�ԍ�
	// �Ԓl	none
	//--------------------------------------------------------
	Exception::Exception(const std::string& argMessage, const std::string& argFile,
		const std::string& argFunction, const int argLine)
		: message(argMessage), fileName(argFile),
		functionName(argFunction), line(argLine)
	{}
	//--------------------------------------------------------
	// ����	�f�X�g���N�^
	// ����	none
	// �Ԓl	none
	//--------------------------------------------------------
	Exception::~Exception() throw(){}
	//--------------------------------------------------------
	// ����	���̃G���[���N���������b�Z�[�W��Ԃ�
	// ����	
	// �Ԓl	�G���[���b�Z�[�W
	//--------------------------------------------------------
	const char* Exception::what()const throw(){//PCTSTR
		return NULL;
	}
	//--------------------------------------------------------
	// ����	�G���[�����̃t�@�C���ŋN�������Ԃ�
	// ����	
	// �Ԓl	�G���[�t�@�C����
	//--------------------------------------------------------
	const std::string& Exception::getFileName()const{
		return fileName;
	}
	//--------------------------------------------------------
	// ����	�G���[�����̃t�@�C���ŋN�������Ԃ�
	// ����	
	// �Ԓl	�G���[�t�@�C����
	//--------------------------------------------------------
	const std::string& Exception::getFunction()const{
		return functionName;
	}
	//--------------------------------------------------------
	// ����	�G���[�����s�ڂŋN�������Ԃ�
	// ����	
	// �Ԓl	�G���[�s�ԍ�
	//--------------------------------------------------------
	const int Exception::getLineNumber()const{
		return line;

	}
	//--------------------------------------------------------
	// ����	�G���[�����b�Z�[�W��ς���
	// ����	
	// �Ԓl	�G���[���b�Z�[�W
	//--------------------------------------------------------
	const std::string& Exception::getMessage()const{
		return message;
	}
}