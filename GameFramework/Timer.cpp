#include "stdafx.h"
#include "Timer.h"
#include <string>

#pragma comment(lib, "winmm.lib")

Timer::Timer()
	: _timeScale(0.f), _timeElapsed(0.f), _curTime(0), _lastTime(0), _periodFrequency(0), _frameRate(0), _FPSFrameCount(0), _FPSTimeElapsed(0.f), _worldTime(0.f)
{
}

HRESULT Timer::Init()
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

		_timeScale = 1.0f / _periodFrequency;
	}

	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0;
	_worldTime = 0;

	return S_OK;
}

void Timer::Tick(float lockFPS)
{
	QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);

	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	// 프레임에 Lock을 걸어서 deltaTime 주기를 일정하게 잡아 둔다 (프레임 스키핑)
	if (lockFPS > 0.0f)
	{
		while (_timeElapsed < 1.0f / lockFPS)
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);

			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _curTime;

	_FPSFrameCount++;

	_FPSTimeElapsed += _timeElapsed;
	_worldTime += _timeElapsed;


	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPSTimeElapsed = 0.0f;
	}

}

unsigned long Timer::GetFrameRate()
{
	return _frameRate;
}

unsigned long Timer::GetFrameRate(std::wstring& str)
{
	str = L"FPS : " + std::to_wstring(_frameRate);
	return _frameRate;
}
