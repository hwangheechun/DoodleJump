#pragma once
#include "SingletonBase.h"

enum class CameraState : int
{
	TARGET,			// Ÿ�� ����
	TARGET_LERP,	// Ÿ�� ����, �ε巴�� ����
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
	CameraState _state;
	FloatRect _rc;
	Vector2 _position;
	float _width;
	float _height;
	Vector2 _mapSize;
	float _speed;

	class GameObject* _target;	// Ÿ���õ� ���� ������Ʈ

public:
	void SetCameraMode(CameraState state) { _state = state; }

	void ChangeTarget(class GameObject* object);
	void MoveToTarget();
	void MoveToTarget_Lerp();

	Vector2 GetMapSize() { return _mapSize; }
	void SetMapSize(Vector2 size) { _mapSize = size; }

	Vector2 GetRelativeVector2(Vector2 vector);
	Vector2 Getrc() { return Vector2(_rc.left, _rc.top); }
private:
	void UpdateRect();
	void CheckRect();

	Vector2 Lerp(Vector2 start, Vector2 end, float t);
};

