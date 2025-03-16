#include "stdafx.h"
#include "Button.h"

Button::Button(const wstring& imageName, Vector2 pos, int frameX, int frameY, int frameDownX, int frameDownY, function<void(void)> cbFuntion)
	: _cbFunction(cbFuntion)
{
	_direction = ButtonDirection::None;

	_position = pos;

	_image = IMAGEMANAGER->FindImage(imageName);

	_frameUpPoint = { frameX, frameY };
	_frameDownPoint = { frameDownX, frameDownY };

	_rect.Update(_position, Vector2(_image->GetFrameSize()), Pivot::Center);
}

Button::Button(const wstring& imageName, Vector2 pos, int frameX, int frameY, int frameDownX, int frameDownY)
{
	_name = L"Button";
	_direction = ButtonDirection::None;

	_position = pos;

	_image = IMAGEMANAGER->FindImage(imageName);

	_frameUpPoint = { frameX, frameY };
	_frameDownPoint = { frameDownX, frameDownY };

	_rect.Update(_position, Vector2(_image->GetFrameSize()), Pivot::Center);
}

void Button::Init()
{
}

void Button::Release()
{
}

void Button::Update()
{
	RECT rc = _rect.GetRect();
	if (PtInRect(&rc, _ptMouse))	// 위치만 보는 것, 마우스가 RECT 안에 있다면
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			_direction = ButtonDirection::Down;
		}
		else if (_direction == ButtonDirection::Down && KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
		{
			_direction = ButtonDirection::Up;
			_cbFunction();
		}
	}
}

void Button::Render()
{
	switch (_direction)
	{
	case ButtonDirection::None:
	case ButtonDirection::Up:
		_image->FrameRender(_rect.GetCenter(), _frameUpPoint.x, _frameUpPoint.y);
		break;
	case ButtonDirection::Down:
		_image->FrameRender(_rect.GetCenter(), _frameDownPoint.x, _frameDownPoint.y);
		break;
	}
}

void Button::Pause()
{
	_isPause = !_isPause;
}
