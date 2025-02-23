#pragma once

namespace StringHelper
{
	namespace Internal
	{
		// Contain: 특정 문자열이 포함되어 있는지 확인
		template <typename T>
		bool ContainBasic(const T& str, const T& comp)
		{
			typename T::size_type found = str.find(comp);
			return found != T::npos;
		}

		// IsStartWith: 문자열이 특정 문자열로 시작하는지 확인
		template <typename T>
		bool IsStartWithBasic(const T& str, const T& comp)
		{
			typename T::size_type index = str.find(comp);
			return (index != T::npos && index == 0);
		}

		// SplitString: 특정 구분자로 문자열 분리
		template <typename T>
		void SplitStringBasic(std::vector<T>& result, const T& origin, const T& tok)
		{
			result.clear();
			T temp = origin;

			typename T::size_type cutAt = 0;
			while ((cutAt = temp.find_first_of(tok)) != T::npos)
			{
				if (cutAt > 0)
				{
					result.push_back(temp.substr(0, cutAt));
				}
				temp = temp.substr(cutAt + 1);
			}

			if (temp.length() > 0)
			{
				result.push_back(temp);
			}
		}

		// Replace: 특정 문자로 대체
		template <typename T>
		void ReplaceBasic(T& str, const T& comp, const T& rep)
		{
			typename T::size_type start_pos = 0;
			while ((start_pos = str.find(comp, start_pos)) != T::npos)
			{
				str.replace(start_pos, comp.length(), rep);
				start_pos += rep.length();  // Avoid infinite loops
			}
		}
	}

	bool Contain(const string& str, const string& comp);
	bool Contain(const wstring& str, const wstring& comp);

	bool IsStartWith(const string& str, const string& comp);
	bool IsStartWith(const wstring& str, const wstring& comp);

	void SplitString(vector<string>& result, const string& origin, const string& tok);
	void SplitString(vector<wstring>& result, const wstring& origin, const wstring& tok);

	void Replace(string& str, const string& comp, const string& rep);
	void Replace(wstring& str, const wstring& comp, const wstring& rep);

	wstring StringToWString(const string& value);
	string WStringToString(const wstring& value);
};