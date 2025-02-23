#include "stdafx.h"
#include "animation.h"


Animation::Animation()
	: _frameNum(0), _frameWidth(0), _frameHeight(0), _loop(false), _frameUpdateSec(0), _elapsedSec(0), _nowPlayIndex(0), _isPlaying(false),
	_obj(nullptr), _callbackFunction(nullptr), _callbackFunctionParameter(nullptr)
{
}

HRESULT Animation::Init(int totalW, int totalH, int frameW, int frameH)
{
	// 가로 몇 장인지 계산
	_frameWidth = frameW;
	int _frameNumWidth = totalW / _frameWidth;

	// 세로 몇 장인지 계산
	_frameHeight = frameH;
	int _frameNumHeight = totalH / _frameHeight;

	// 총 애니메이션 프레임이 몇 장인지 계산
	_frameNum = _frameNumWidth * _frameNumHeight;

	for (int i = 0; i < _frameNumHeight; ++i)
	{
		for (int j = 0; j < _frameNumWidth; ++j)
		{
			POINT framePos;

			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			_frameList.push_back(framePos);
		}
	}

	return S_OK;
}

void Animation::Release()
{
}

void Animation::SetDefPlayFrame(bool reverse, bool loop)
{
	_obj = nullptr;
	_callbackFunction = nullptr;
	_callbackFunctionParameter = nullptr;

	_loop = loop;
	_playList.clear();

	if (reverse)
	{
		if (_loop)
		{
			for (int i = 0; i < _frameNum; ++i)
			{
				_playList.push_back(i);
			}

			for (int i = _frameNum - 1; i >= 0; --i)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			for (int i = 0; i < _frameNum; ++i)
			{
				_playList.push_back(i);
			}

			for (int i = _frameNum - 1; i >= 0; --i)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		if (_loop)
		{
			for (int i = 0; i < _frameNum; ++i)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			for (int i = 0; i < _frameNum; ++i)
			{
				_playList.push_back(i);
			}
		}
	}

}

void Animation::SetDefPlayFrame(bool reverse, bool loop, CALLBACK_FUNCTION cbFunction)
{
	_obj = nullptr;
	_callbackFunction = cbFunction;
	_callbackFunctionParameter = nullptr;

	_loop = loop;
	_playList.clear();

	if (reverse)
	{
		if (_loop)
		{
			for (int i = 0; i < _frameNum; ++i)
			{
				_playList.push_back(i);
			}

			for (int i = _frameNum - 1; i >= 0; --i)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			for (int i = 0; i < _frameNum; ++i)
			{
				_playList.push_back(i);
			}

			for (int i = _frameNum - 1; i >= 0; --i)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		if (_loop)
		{
			for (int i = 0; i < _frameNum; ++i)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			for (int i = 0; i < _frameNum; ++i)
			{
				_playList.push_back(i);
			}
		}
	}

}

void Animation::SetDefPlayFrame(bool reverse, bool loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void * obj)
{
	_obj = obj;
	_callbackFunction = nullptr;
	_callbackFunctionParameter = cbFunction;

	_loop = loop;
	_playList.clear();

	if (reverse)
	{
		if (_loop)
		{
			for (int i = 0; i < _frameNum; ++i)
			{
				_playList.push_back(i);
			}

			for (int i = _frameNum - 1; i >= 0; --i)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			for (int i = 0; i < _frameNum; ++i)
			{
				_playList.push_back(i);
			}

			for (int i = _frameNum - 1; i >= 0; --i)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		if (_loop)
		{
			for (int i = 0; i < _frameNum; ++i)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			for (int i = 0; i < _frameNum; ++i)
			{
				_playList.push_back(i);
			}
		}
	}

}

void Animation::SetPlayFrame(int * playArr, int arrLen, bool loop)
{
	_obj = nullptr;
	_callbackFunction = nullptr;
	_callbackFunctionParameter = nullptr;

	_loop = loop;

	_playList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}

}

void Animation::SetPlayFrame(int * playArr, int arrLen, bool loop, CALLBACK_FUNCTION cbFunction)
{
	_obj = nullptr;
	_callbackFunction = cbFunction;
	_callbackFunctionParameter = nullptr;

	_loop = loop;

	_playList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}
}

void Animation::SetPlayFrame(int * playArr, int arrLen, bool loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void * obj)
{
	_obj = obj;
	_callbackFunction = nullptr;
	_callbackFunctionParameter = cbFunction;

	_loop = loop;

	_playList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}
}

void Animation::SetPlayFrame(int start, int end, bool reverse, bool loop)
{
	_obj = nullptr;
	_callbackFunction = nullptr;
	_callbackFunctionParameter = nullptr;


	_loop = loop;

	_playList.clear();

	if (start == end)
	{
		_playList.clear();
		Stop();
		return;
	}

	if (start > end)
	{
		if (reverse)
		{
			if (_loop)
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			if (_loop)
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
			}
		}
	}
	else
	{
		if (reverse)
		{
			if (_loop)
			{
				for (int i = start; i < end; ++i)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i > start; --i)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i < end; ++i)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i > start; --i)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			if (_loop)
			{
				for (int i = start; i < end; ++i)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i < end; ++i)
				{
					_playList.push_back(i);
				}
			}
		}
	}


}

void Animation::SetPlayFrame(int start, int end, bool reverse, bool loop, CALLBACK_FUNCTION cbFunction)
{
	_obj = nullptr;
	_callbackFunction = cbFunction;
	_callbackFunctionParameter = nullptr;

	_loop = loop;

	_playList.clear();

	if (start == end)
	{
		_playList.clear();
		Stop();
		return;
	}

	if (start > end)
	{
		if (reverse)
		{
			if (_loop)
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			if (_loop)
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
			}
		}
	}
	else
	{
		if (reverse)
		{
			if (_loop)
			{
				for (int i = start; i < end; ++i)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i > start; --i)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i < end; ++i)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i > start; --i)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			if (_loop)
			{
				for (int i = start; i < end; ++i)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i < end; ++i)
				{
					_playList.push_back(i);
				}
			}
		}
	}


}

void Animation::SetPlayFrame(int start, int end, bool reverse, bool loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void * obj)
{
	_obj = obj;
	_callbackFunction = nullptr;
	_callbackFunctionParameter = cbFunction;

	_loop = loop;

	_playList.clear();

	if (start == end)
	{
		_playList.clear();
		Stop();
		return;
	}

	if (start > end)
	{
		if (reverse)
		{
			if (_loop)
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			if (_loop)
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
			}
		}
	}
	else
	{
		if (reverse)
		{
			if (_loop)
			{
				for (int i = start; i < end; ++i)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i > start; --i)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i < end; ++i)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i > start; --i)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			if (_loop)
			{
				for (int i = start; i < end; ++i)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i < end; ++i)
				{
					_playList.push_back(i);
				}
			}
		}
	}


}

void Animation::SetFPS(int framePerSec)
{
	_frameUpdateSec = 1.0f / framePerSec;
}

void Animation::FrameUpdate(float elapsedTime)
{
	if (_isPlaying)
	{
		_elapsedSec += elapsedTime;

		if (_elapsedSec >= _frameUpdateSec)
		{
			_elapsedSec -= _frameUpdateSec;

			_nowPlayIndex++;

			if (_nowPlayIndex == _playList.size())
			{
				if (_loop) 
					_nowPlayIndex = 0;
				else
				{
					if (_obj == nullptr)
					{
						if (_callbackFunction != nullptr) 
							_callbackFunction();
					}
					else 
						_callbackFunctionParameter(_obj);

					_nowPlayIndex--;
					_isPlaying = false;
				}
			}
		}
	}

}

void Animation::Start()
{
	_isPlaying = true;
	_nowPlayIndex = 0;
}

void Animation::Stop()
{
	_isPlaying = false;
	_nowPlayIndex = 0;
}

void Animation::Pause()
{
	_isPlaying = false;
}

void Animation::Resume()
{
	_isPlaying = true;
}
