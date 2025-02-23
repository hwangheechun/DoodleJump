#include "stdafx.h"
#include "SoundManager.h"


SoundManager::SoundManager()
	: _system(nullptr), _channel(nullptr), _sound(nullptr)
{
}

HRESULT SoundManager::Init()
{
	// FMOD 엔진 초기화
	System_Create(&_system);

	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	memset(_sound, 0, sizeof(Sound*) * TOTALSOUNDBUFFER);
	memset(_channel, 0, sizeof(Channel*) * TOTALSOUNDBUFFER);

	return S_OK;
}

void SoundManager::Release()
{
	if (_system)
	{
		_system->release();
		_system->close();
	}
}

void SoundManager::Update()
{
	if (_system)
		_system->update();
}

void SoundManager::AddSound(const wstring& keyName, const wstring& soundName, bool bgm, bool loop)
{
	auto sSoundName = StringHelper::WStringToString(soundName);
	if (loop)
	{
		if (bgm)
		{
			_system->createStream(sSoundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_totalSounds.size()]);
		}
		else
		{
			_system->createSound(sSoundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_totalSounds.size()]);
		}
	}
	else
	{
		if (bgm)
		{
			_system->createStream(sSoundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_totalSounds.size()]);
		}
		else
		{
			_system->createSound(sSoundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_totalSounds.size()]);
		}
	}

	_totalSounds.insert(make_pair(keyName, &_sound[_totalSounds.size()]));
}

void SoundManager::Play(const wstring& keyName, float volume)
{
	arrSoundsIter iter = _totalSounds.begin();

	int count = 0;

	for (iter; iter != _totalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);

			_channel[count]->setVolume(volume);
			break;
		}
	}

}

void SoundManager::Stop(const wstring& keyName)
{
	arrSoundsIter iter = _totalSounds.begin();

	int count = 0;

	for (iter; iter != _totalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}

void SoundManager::Pause(const wstring& keyName)
{
	arrSoundsIter iter = _totalSounds.begin();

	int count = 0;

	for (iter; iter != _totalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void SoundManager::Resume(const wstring& keyName)
{
	arrSoundsIter iter = _totalSounds.begin();

	int count = 0;

	for (iter; iter != _totalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}

bool SoundManager::IsPlaySound(const wstring& keyName)
{
	bool isPlay = false;
	arrSoundsIter iter = _totalSounds.begin();

	int count = 0;

	for (iter; iter != _totalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool SoundManager::IsPauseSound(const wstring& keyName)
{
	bool isPause = false;
	arrSoundsIter iter = _totalSounds.begin();

	int count = 0;

	for (iter; iter != _totalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPaused(&isPause);
			break;
		}
	}

	return isPause;
}
