#pragma once
#include "GameObject.h"
#include "Player.h"

class UI : public GameObject
{
public:
	UI();
	virtual ~UI();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	//이미지 관련
	Image* _UIImage = nullptr;
	Player* _player = nullptr;

	//점수
	int _score = 0;
	int _highScore = 0;
};