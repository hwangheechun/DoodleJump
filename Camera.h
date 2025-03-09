#pragma once
#include "SingletonBase.h"

enum class CameraState : int
{
	TARGET,			// 타겟 고정
	TARGET_LERP,	// 타겟 고정, 부드럽게 보정
	END,
};

class Camera final : public SingletonBase<Camera>
{
protected:
	Camera();
	virtual ~Camera() = default;

	friend class SingletonBase<Camera>;

public:
	void Update();

private:
	CameraState _state = CameraState::TARGET;
	FloatRect _rc;
	Vector2 _position;
	float _width = 0;
	float _height = 0;
	Vector2 _mapSize;
	float _speed = 0;

	class GameObject* _target = nullptr;	// 타겟팅될 게임 오브젝트

public:
	void SetCameraMode(CameraState state) { _state = state; }

	void ChangeTarget(class GameObject* object);
	void MoveToTarget();
	void MoveToTarget_Lerp();

	Vector2 GetMapSize() { return _mapSize; }
	void SetMapSize(Vector2 size) { _mapSize = size; }

	Vector2 GetRelativeVector2(Vector2 vector);
	FloatRect GetRelativeRect(FloatRect _rect);
	Vector2 GetrcTop() { return Vector2(_rc.left, _rc.top); }
	Vector2 GetrcBottom() { return Vector2(_rc.right, _rc.bottom); }

	Vector2 GetPosition() { return _position; }

private:
	void UpdateRect();
	void CheckRect();

	Vector2 Lerp(Vector2 start, Vector2 end, float t);
};

