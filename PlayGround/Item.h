#pragma once
#include "GameObject.h"
#include "Player.h"

class Item : public GameObject
{
public:
	Item();
	virtual ~Item();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	Player* _player = nullptr;
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

class Trampoline : public Item
{
public:
	Trampoline();
	virtual ~Trampoline();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	Image* _trampolineImage = nullptr;
	Animation* _trampolineAnimation = nullptr;

	//持失
	bool _onScreen = false;
	void SetRandomCreate(Vector2 randPos, int successValue);

	bool IsCollide(GameObject* Object);
};

class Hole : public Item
{
public:
	Hole();
	virtual ~Hole();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	Image* _holeImage = nullptr;
	Animation* _trampolineAnimation = nullptr;

	//持失
	bool _onScreen = false;
	void SetRandomCreate(Vector2 randPos, int successValue);

	bool IsCollide(GameObject* Object);
};