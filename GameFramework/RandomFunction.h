#pragma once
#include "SingletonBase.h"
#include <random>

class RandomFunction : public SingletonBase<RandomFunction>
{
private:
	std::mt19937 generator;

public:
	RandomFunction()
		: generator(static_cast<unsigned int>(std::random_device{}()))
	{}

	~RandomFunction() = default;

	// 매개변수에 넣은 숫자의 -1만큼 범위를 가지는 난수 생성
	inline int GetInt(int num)
	{
		std::uniform_int_distribution<int> distribution(0, num - 1);
		return distribution(generator);
	}

	// 정수와 정수 사이 범위에서 난수 생성
	inline int GetIntFromTo(int fromNum, int toNum)
	{
		std::uniform_int_distribution<int> distribution(fromNum, toNum);
		return distribution(generator);
	}

	// 0과 1 사이의 부동소수점 난수 생성
	inline float GetFloat(float num)
	{
		std::uniform_real_distribution<float> distribution(0.0f, num);
		return distribution(generator);
	}

	// 특정 범위에서 부동소수점 난수 생성
	inline float GetFloatFromTo(float fromNum, float toNum)
	{
		std::uniform_real_distribution<float> distribution(fromNum, toNum);
		return distribution(generator);
	}
};