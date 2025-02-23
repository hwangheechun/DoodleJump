#pragma once
#include "SingletonBase.h"
#include <map>

#include "inc/fmod.hpp"
#pragma comment(lib, "lib/fmodex64_vc.lib")

using namespace FMOD;

#define SOUNDBUFFER 10
#define EXTRACHANNELBUFFER 5

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER


class SoundManager final : public SingletonBase<SoundManager>
{
private:
	typedef map<wstring, Sound**>			arrSounds;
	typedef map<wstring, Sound**>::iterator	arrSoundsIter;

	typedef map<wstring, Channel**>			 arrChannels;
	typedef map<wstring, Channel**>::iterator arrChannelIter;

private:
	System*			_system;
	Sound**			_sound;
	Channel**		_channel;

	arrSounds		_totalSounds;

protected:
	SoundManager();
	virtual ~SoundManager() = default;

	friend class SingletonBase<SoundManager>;

public:
	HRESULT Init();
	void Release();
	void Update();

	void AddSound(const wstring& keyName, const wstring& soundName, bool bgm, bool loop);

	void Play(const wstring& keyName, float volume = 1.0f);
	void Stop(const wstring& keyName);
	void Pause(const wstring& keyName);
	void Resume(const wstring& keyName);

	bool IsPlaySound(const wstring& keyName);
	bool IsPauseSound(const wstring& keyName);
};

