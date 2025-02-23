#include "stdafx.h"
#include "TimeManager.h"

#include <string>

TimeManager::TimeManager()
	: _timer(std::make_unique<Timer>())
{
}

HRESULT TimeManager::Init()
{
	_timer->Init();

	return S_OK;
}

void TimeManager::Release()
{
}

void TimeManager::Update(float lockFPS)
{
	if (_timer)
		_timer->Tick(lockFPS);
}

void TimeManager::Render(HDC hdc)
{
	std::wstring str;

	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkMode(hdc, TRANSPARENT);

#ifdef _DEBUG
	{
		// frameRate 출력
		str = L"framePerSecond(FPS) : " + std::to_wstring(_timer->GetFrameRate());
		TextOut(hdc, 0, 0, str.c_str(), static_cast<int>(str.length()));

		// worldTime 출력
		str = L"worldTime : " + std::to_wstring(_timer->GetWorldTime());
		TextOut(hdc, 0, 20, str.c_str(), static_cast<int>(str.length()));

		// elapsedTime 출력
		str = L"elapsedTime : " + std::to_wstring(_timer->GetElapsedTime());
		TextOut(hdc, 0, 40, str.c_str(), static_cast<int>(str.length()));
	}
#else
	{
		// frameRate 출력
		str = L"framePerSecond(FPS) : " + std::to_wstring(_timer->getFrameRate());
		TextOut(hdc, 0, 0, str.c_str(), static_cast<int>(str.length()));
	}
#endif
}