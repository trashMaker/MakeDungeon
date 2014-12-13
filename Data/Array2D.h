#pragma once

#include <assert.h>
#include <vector>

#include "Common.h"

template <typename TYPE>
class Array2D{
private:
	std::vector<TYPE> mArray;
	int mSize0;
	int mSize1;
public:
	//----------------------------------------------------------------
	// ����	�R���X�g���N�^
	// ����	�Ȃ�
	// �Ԓl	�Ȃ�
	//----------------------------------------------------------------
	explicit Array2D() :mArray(0){}
	//----------------------------------------------------------------
	// ����	�f�X�g���N�^
	// ����	�Ȃ�
	// �Ԓl	�Ȃ�
	//----------------------------------------------------------------
	virtual ~Array2D(){}
	//----------------------------------------------------------------
	// ����	�v�f����ǉ�
	// ����	size0
	//  	size1
	// �Ԓl	�Ȃ�
	//----------------------------------------------------------------
	void setSize(const int size0, const int size1)throw(){
		ASSERT((0 < size0 && size0 < INT_MAX), size0, STRING(size0), "size0�̃T�C�Y�������Ă��܂���");
		ASSERT((0 < size1 && size1 < INT_MAX), size1, STRING(size1), "size1�̃T�C�Y�������Ă��܂���");
		mSize0 = size0;
		mSize1 = size1;
		mArray.resize(mSize0 * mSize1);
	}
	//----------------------------------------------------------------
	// ����	�v�f���𓾂�
	// �Ԓl	�v�f����Ԃ�
	//----------------------------------------------------------------
	const int getSize()const throw(){
		return mArray.size();
	}
	//----------------------------------------------------------------
	// ����	charctor�̐��𐔂���
	// �Ԓl	charctor�̌���Ԃ�
	//----------------------------------------------------------------
	const int getCharctorCount(const char charctor)const throw(){
		return std::count(mArray.begin(), mArray.end(), charctor);
	}
	//----------------------------------------------------------------
	// ����	�z��̗v�f�̎Q�Ƃ��擾 �������ݗp
	// ����	index0	���C���f�b�N�X
	// �@�@	index1	���C���f�b�N�X
	// �Ԓl	�z��̗v�f�̎Q��                operator
	//----------------------------------------------------------------
	TYPE& operator()(int index0, int index1) throw(){
		ASSERT((0 <= index0 && index0 < mSize0), index0, STRING(index0), "size0�̃T�C�Y�������Ă��܂���");
		ASSERT((0 <= index1 && index1 < mSize1), index1, STRING(index1), "size1�̃T�C�Y�������Ă��܂���");
		return mArray[index1 * mSize0 + index0];
	}
	//----------------------------------------------------------------
	// ����	�z��̗v�f�̎Q�Ƃ��擾 �ǂݍ��ݗp
	// ����	index0	���C���f�b�N�X
	// �@�@	index1	���C���f�b�N�X
	// �Ԓl	�z��̗v�f�̎Q��
	//----------------------------------------------------------------
	const TYPE& operator()(int index0, int index1)const throw(){
		ASSERT((0 <= index0 && index0 < mSize0), index0, STRING(index0), "size0�̃T�C�Y�������Ă��܂���");
		ASSERT((0 <= index1 && index1 < mSize1), index1, STRING(index1), "size1�̃T�C�Y�������Ă��܂���");
		return mArray[index1 * mSize0 + index0];
	}
};