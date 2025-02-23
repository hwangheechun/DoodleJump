#pragma once
template <typename T>
class SingletonBase
{
protected:
	SingletonBase() {}
	virtual ~SingletonBase() {}

	SingletonBase(const SingletonBase&) = delete;
	SingletonBase& operator=(const SingletonBase&) = delete;

public:
	static T* GetInstance()
	{
		static T instance;
		return &instance;
	}
};