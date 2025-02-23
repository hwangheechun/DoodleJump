#pragma once
#include "GameObject.h"

class Doodle : public GameObject
{
public:
	Doodle();
	virtual ~Doodle();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void Move(Vector2 moveDirection, float speed);
	void MoveAngle(float angle, float speed);

	Vector2 _direction;
	Vector2 GetDirection() { return _direction; };

	FloatRect _gaugeRect;

	Vector2 _doodlePos;
	bool isUp;

	//중력 관련
	float _gravity;
	GameObject* _ground;
	bool _onGround;
	GameObject* _block;

	//이미지 관련
	bool _isLeft;
	Image* _doodleLeft;
	Image* _doodleRight;
	Animation* _doodleAnimation;
};

