#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void Move(Vector2 moveDirection, float speed);
	void MoveAngle(float angle, float speed);

	Vector2 _direction;
	Vector2 GetDirection() { return _direction; };

	float _gauge;
	FloatRect _gaugeRect;

	Image* _playerImage;
	Animation* _playerAnimation;

	Vector2 _doodlePos;
	bool isUp;

	//중력 관련
	float _gravity;
	GameObject* _ground;
	bool _onGround;
	GameObject* _block;

	//이미지 관련
	bool _isLeft;
};

