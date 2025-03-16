#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Button.h"

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

	//점수
	Player* _player = nullptr;
	int _score = 0;
	int _highScore = 0;

	//버튼
	Button* _pauseButton = nullptr;
};