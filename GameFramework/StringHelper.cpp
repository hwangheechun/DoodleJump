#include "stdafx.h"
#include "StringHelper.h"

namespace StringHelper {
	bool Contain(const string& str, const string& comp)
	{
		return Internal::ContainBasic(str, comp);
	}

	bool Contain(const wstring& str, const wstring& comp)
	{
		return Internal::ContainBasic(str, comp);
	}

	bool IsStartWith(const string& str, const string& comp)
	{
		return Internal::IsStartWithBasic(str, comp);
	}

	bool IsStartWith(const wstring& str, const wstring& comp)
	{
		return Internal::IsStartWithBasic(str, comp);
	}

	void SplitString(vector<string>& result, const string& origin, const string& tok)
	{
		Internal::SplitStringBasic(result, origin, tok);
	}

	void SplitString(vector<wstring>& result, const wstring& origin, const wstring& tok)
	{
		Internal::SplitStringBasic(result, origin, tok);
	}

	void Replace(string& str, const string& comp, const string& rep)
	{
		Internal::ReplaceBasic(str, comp, rep);
	}

	void Replace(wstring& str, const wstring& comp, const wstring& rep)
	{
		Internal::ReplaceBasic(str, comp, rep);
	}

	wstring StringToWString(const string& value)
	{
		if (value.empty())
			return L"";

		int sizeNeeded = MultiByteToWideChar(CP_ACP, 0, value.c_str(), -1, nullptr, 0);
		wstring result(sizeNeeded, 0);
		MultiByteToWideChar(CP_ACP, 0, value.c_str(), -1, &result[0], sizeNeeded);

		return result;
	}

	string WStringToString(const wstring& value)
	{
		if (value.empty())
			return "";

		int sizeNeeded = WideCharToMultiByte(CP_ACP, 0, value.c_str(), -1, nullptr, 0, nullptr, nullptr);
		string result(sizeNeeded, 0);
		WideCharToMultiByte(CP_ACP, 0, value.c_str(), -1, &result[0], sizeNeeded, nullptr, nullptr);

		return result;
	}
}