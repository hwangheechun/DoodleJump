#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet();
	virtual ~Bullet();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void Move(Vector2 moveDirection, float speed);
	void MoveAngle(float speed);

	class Player* _player;
	bool _isInit;
	Vector2 _direction;
};

