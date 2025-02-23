#pragma once
#include "Image.h"

class GameObject
{
protected:
	Property(wstring, _name, Name)
	Property(Vector2, _position, Position)
	Property(Vector2, _size, Size)
	Property(FloatRect, _rect, Rect)
	Property(bool, _active, Active)

	/*
	wstring _name;		// 게임 오브젝트의 이름
	Vector2 _position;	// 좌표
	Vector2 _size;
	FloatRect _rect;

	bool _active;
	*/

public:
	GameObject() = default;
	virtual ~GameObject() = default;

	virtual void Init() = 0;		// start
	virtual void Release() = 0;		// ondestroy
	virtual void Update() = 0;		// update - 게임 로직, 이동, 공격 처리 등등..
	virtual void Render() = 0;		// 실제 플레이어 그리기
};

