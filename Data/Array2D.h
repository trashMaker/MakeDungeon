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
	// 処理	コンストラクタ
	// 引数	なし
	// 返値	なし
	//----------------------------------------------------------------
	explicit Array2D() :mArray(0){}
	//----------------------------------------------------------------
	// 処理	デストラクタ
	// 引数	なし
	// 返値	なし
	//----------------------------------------------------------------
	virtual ~Array2D(){}
	//----------------------------------------------------------------
	// 処理	要素数を追加
	// 引数	size0
	//  	size1
	// 返値	なし
	//----------------------------------------------------------------
	void setSize(const int size0, const int size1)throw(){
		ASSERT((0 < size0 && size0 < INT_MAX), size0, STRING(size0), "size0のサイズが入っていません");
		ASSERT((0 < size1 && size1 < INT_MAX), size1, STRING(size1), "size1のサイズが入っていません");
		mSize0 = size0;
		mSize1 = size1;
		mArray.resize(mSize0 * mSize1);
	}
	//----------------------------------------------------------------
	// 処理	要素数を得る
	// 返値	要素数を返す
	//----------------------------------------------------------------
	const int getSize()const throw(){
		return mArray.size();
	}
	//----------------------------------------------------------------
	// 処理	charctorの数を数える
	// 返値	charctorの個数を返す
	//----------------------------------------------------------------
	const int getCharctorCount(const char charctor)const throw(){
		return std::count(mArray.begin(), mArray.end(), charctor);
	}
	//----------------------------------------------------------------
	// 処理	配列の要素の参照を取得 書き込み用
	// 引数	index0	第一インデックス
	// 　　	index1	第二インデックス
	// 返値	配列の要素の参照                operator
	//----------------------------------------------------------------
	TYPE& operator()(int index0, int index1) throw(){
		ASSERT((0 <= index0 && index0 < mSize0), index0, STRING(index0), "size0のサイズが入っていません");
		ASSERT((0 <= index1 && index1 < mSize1), index1, STRING(index1), "size1のサイズが入っていません");
		return mArray[index1 * mSize0 + index0];
	}
	//----------------------------------------------------------------
	// 処理	配列の要素の参照を取得 読み込み用
	// 引数	index0	第一インデックス
	// 　　	index1	第二インデックス
	// 返値	配列の要素の参照
	//----------------------------------------------------------------
	const TYPE& operator()(int index0, int index1)const throw(){
		ASSERT((0 <= index0 && index0 < mSize0), index0, STRING(index0), "size0のサイズが入っていません");
		ASSERT((0 <= index1 && index1 < mSize1), index1, STRING(index1), "size1のサイズが入っていません");
		return mArray[index1 * mSize0 + index0];
	}
};