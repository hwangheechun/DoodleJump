#pragma once
#include "GameObject.h"

class Item : public GameObject
{
public:
	Item();
	virtual ~Item();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

class Propeller : public Item
{
public:
	Propeller();
	virtual ~Propeller();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	Image* _propellerImage = nullptr;
};


