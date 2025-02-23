#pragma once
#include "SingletonBase.h"
#include "Timer.h"

class TimeManager final : public SingletonBase<TimeManager>
{
protected:
	TimeManager();
	virtual ~TimeManager() = default;

	friend class SingletonBase<TimeManager>;

private:
	unique_ptr<Timer> _timer;

public:
	HRESULT Init();
	void Release();
	void Update(float lockFPS = 0.0f);
	void Render(HDC hdc);

	inline float GetElapsedTime() const { return _timer->GetElapsedTime(); }
	inline float GetWorldTime() const { return _timer->GetWorldTime(); }
};

