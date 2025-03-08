#pragma once
#include "GameObject.h"

class UI : public GameObject
{
public:
	UI();
	virtual ~UI();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	//생성
	void SetRandomCreate(Vector2 randPos, int typeValue);
	void SetRandomY(int value);
	void SetRandomType(int value);

	//이미지 관련
	Image* _UIImage = nullptr;
};