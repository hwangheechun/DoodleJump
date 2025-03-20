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

	Vector2 _doodlePos;
	bool _isUp;
	//float _angle;

	//이미지 관련
	Image* _playerImage = nullptr;
	Animation* _playerAnimation = nullptr;
	bool _isLeft;

	//중력 관련
	float _gravity;
	GameObject* _ground = nullptr;
	bool _onGround;
	GameObject* _block = nullptr;
	bool _isJump;

	//충돌 관련
	bool IsCollide(GameObject* Object);

	float _takenTime;

	//죽음 처리
	bool _isDead;
	float _deadLineY = 0.f;

	bool _isPause = false;
};

