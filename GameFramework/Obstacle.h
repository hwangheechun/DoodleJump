#pragma once
#include "GameObject.h"

class Obstacle : public GameObject
{
public:
	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void OnCollision() {}
};

