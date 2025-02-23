#include "stdafx.h"
#include "TextData.h"
#include <sstream>

HRESULT TextData::Init()
{
	return S_OK;
}

void TextData::Release()
{
}

void TextData::TextSave(const wstring& strFileName, const vector<wstring>& vStr)
{
	HANDLE file;
	DWORD write;

	// 문자열 결합
	std::wstring combinedStr;
	for (const auto& str : vStr) {
		combinedStr += str + L"\n"; // 각 문자열을 줄바꿈으로 연결
	}

	// 파일 생성 (유니코드 경로 사용)
	file = CreateFile(strFileName.c_str(), GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE) {
		// 오류 처리
		return;
	}

	WriteFile(file, combinedStr.c_str(), static_cast<DWORD>(combinedStr.size() * sizeof(wchar_t)), &write, NULL);

	CloseHandle(file);
}

wstring TextData::CombineVectorArray(const vector<wstring>& vArray)
{
	wstring result;

	for (size_t i = 0; i < vArray.size(); ++i)
	{
		result += vArray[i];
		if (i + 1 < vArray.size())
			result += L","; // 유니코드 구분자
	}

	return result;
}

vector<wstring> TextData::TextLoad(const wchar_t* loadFileName)
{
	HANDLE file;
	DWORD read;

	wchar_t str[128] = { 0 };

	file = CreateFile(loadFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file == INVALID_HANDLE_VALUE) {
		// 오류 처리: 빈 벡터 반환
		return {};
	}

	BOOL success = ReadFile(file, str, sizeof(str) - sizeof(wchar_t), &read, NULL);
	if (!success) {
		// 파일 읽기 실패 처리가 필요하다면 오류 처리
		CloseHandle(file);
		return {};
	}

	CloseHandle(file);

	return SeparateCharArray(str);
}

vector<wstring> TextData::SeparateCharArray(const wstring& charArray)
{
	vector<wstring> vArray;
	wstringstream wss(charArray);
	wstring token;

	while (getline(wss, token, L',')) // 유니코드 구분자
	{
		vArray.push_back(token);
	}

	return vArray;
}
