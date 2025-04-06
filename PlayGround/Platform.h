#pragma once
#include "GameObject.h"
#include "Player.h"

enum class BlockType : int
{
	GREEN, BLUE, BROWN
};

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

	Vector2 GetSize() { return _size; };
};

class PlatformBlock : public GameObject
{
public:
	PlatformBlock();
	virtual ~PlatformBlock();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void Move(Vector2 moveDirection);

	//생성
	void SetRandomCreate(Vector2 randPos, int typeValue);

	//이미지 관련
	Image* _blockImage = nullptr;
	Animation* _blockAnimation = nullptr;

	//충돌 관련
	FloatRect _block;
	Player* _player = nullptr;

	//블록 종류 관련
	BlockType _blockType;
	bool _isRight = false;	//파란 블록은 오른쪽으로 먼저 움직임. 파란 블록의 방향을 나타냄
	bool _isBreak = false;	//갈색 블록이 부서짐을 판단함
	float _countTime = 0;	//갈색 블록이 부서지고 1초 동안 떨어짐을 계산
};

