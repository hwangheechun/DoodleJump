#pragma once

class Timer
{
private:
	float _timeScale;
	float _timeElapsed;

	__int64 _curTime;
	__int64 _lastTime;
	__int64 _periodFrequency;

	unsigned long _frameRate;
	unsigned long _FPSFrameCount;

	float _FPSTimeElapsed;
	float _worldTime;
	
public:
	Timer();
	~Timer() = default;

	HRESULT Init();
	void Tick(float lockFPS = 0.0f);

	unsigned long GetFrameRate();
	unsigned long GetFrameRate(std::wstring& str);

	inline float GetElapsedTime() const { return _timeElapsed; }
	inline float GetWorldTime() const { return _worldTime; }
};

