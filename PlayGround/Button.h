#pragma once
#include "GameObject.h"

enum class ButtonDirection : int
{
	None,
	Up,
	Down,
};

class Button : public GameObject
{
public:
	Button() = delete;
	Button(const wstring& imageName, Vector2 pos, int frameX, int frameY, int frameDownX, int frameDownY, function<void(void)> cbFuntion);
	Button(const wstring& imageName, Vector2 pos, int frameX, int frameY, int frameDownX, int frameDownY);
	~Button() = default;

public:
	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void Pause();
	bool _isPause = false;
private:
	ButtonDirection _direction = ButtonDirection::None;		// 현재 상태

	Image* _image = nullptr;		// 이미지

	POINT _frameDownPoint;
	POINT _frameUpPoint;

	function<void(void)> _cbFunction;		// 콜백 함수
};

