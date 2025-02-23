#pragma once
#include <vector>

typedef void(*CALLBACK_FUNCTION)(void);
typedef void(*CALLBACK_FUNCTION_PARAMETER)(void*);

class Animation
{
public:
	typedef vector<POINT>	vFrameList;	// 프레임 저장용
	typedef vector<int>		vPlayList;	// 플레이 인덱스 저장용

private:
	int _frameNum;			// 프레임 갯수

	vFrameList	_frameList;
	vPlayList	_playList;

	int _frameWidth;		// 프레임 가로 크기
	int _frameHeight;		// 프레임 세로 크기

	bool _loop;				// 루프 여부

	float _frameUpdateSec;	// 프레임 경과 시간
	float _elapsedSec;		// delta time

	DWORD _nowPlayIndex;	// 현재 인덱스
	bool _isPlaying;		// 재생 중인지에 대한 여부

	void*						_obj;
	CALLBACK_FUNCTION			_callbackFunction;
	CALLBACK_FUNCTION_PARAMETER _callbackFunctionParameter;

public:
	Animation();
	~Animation() = default;

	HRESULT Init(int totalW, int totalH, int frameW, int frameH);
	void Release();

	// default
	void SetDefPlayFrame(bool reverse = false, bool loop = false);
	void SetDefPlayFrame(bool reverse, bool loop, CALLBACK_FUNCTION cbFunction);
	void SetDefPlayFrame(bool reverse, bool loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	// array 기반
	void SetPlayFrame(int* playArr, int arrLen, bool loop = false);
	void SetPlayFrame(int* playArr, int arrLen, bool loop, CALLBACK_FUNCTION cbFunction);
	void SetPlayFrame(int* playArr, int arrLen, bool loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	// 구간
	void SetPlayFrame(int start, int end, bool reverse = false, bool loop = false);
	void SetPlayFrame(int start, int end, bool reverse, bool loop, CALLBACK_FUNCTION cbFunction);
	void SetPlayFrame(int start, int end, bool reverse, bool loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	void SetFPS(int framePerSec);

	void FrameUpdate(float elapsedTime);

	void Start();
	void Stop();
	void Pause();
	void Resume();

	inline bool IsPlaying() { return _isPlaying; }

	inline POINT GetFramePos() { return _frameList[_playList[_nowPlayIndex]]; }

	inline int GetFrameWidth() { return _frameWidth; }
	inline int GetFrameHeight() { return _frameHeight; }
};

