#pragma once
#include "GameObject.h"
#include "Player.h"

class Platform : public GameObject
{
public:
	Platform();
	virtual ~Platform();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	FloatRect _platform;
	float _gravity;

	void Move(Vector2 moveDirection, float speed);
	void MoveAngle(float angle, float speed);

	Vector2 GetSize() { return _size; };
};

class PlatformBlock : public GameObject
{
public:
	PlatformBlock();
	PlatformBlock(int a);
	virtual ~PlatformBlock();

	void Init() override;
	void Init(int a);
	void Release() override;
	void Update() override;
	void Render() override;

	FloatRect _block;
	float _gravity;

	void Move(Vector2 moveDirection, float speed);
	void MoveAngle(float angle, float speed);

	Image* _blockImage;
	Animation* _blockAnimation;
	Player* _player;

	//블록 종류 관련
	int _blockType;	//다른 계산식을 사용할 수도 있을 듯
	bool _isRight;	//파란 블록은 오른쪽으로 먼저 움직임. 파란 블록의 방향을 나타냄
	bool _isBreak;	//갈색 블록이 부서짐을 판단함
	float _countTime;	//갈색 블록이 부서지고 1초 동안 떨어짐을 계산
};

