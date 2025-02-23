#pragma once
#include "SingletonBase.h"
#include <vector>

class TextData : public SingletonBase<TextData>
{
protected:
	TextData() = default;
	virtual ~TextData() = default;

	friend class SingletonBase<TextData>;

public:
	HRESULT Init();
	void Release();

	void TextSave(const wstring& strFileName, const vector<wstring>& vStr);
	wstring CombineVectorArray(const vector<wstring>& vArray);

	vector<wstring> TextLoad(const wchar_t* loadFileName);
	vector<wstring> SeparateCharArray(const wstring& charArray);
};

