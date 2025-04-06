#pragma once
#include "Scene.h"
#include "PlayGround/UI.h"
#include "PlayGround/Item.h"

class Player;

class MainScene : public Scene
{
public:
	virtual ~MainScene() override;

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	UI* ui = nullptr;
	vector<GameObject*> _block;
	Trampoline* _trampoline = nullptr;
	Hole* _hole = nullptr;

	Player* _player = nullptr;
private:
	Image* _bgImage = nullptr;
};

class AfterDeadScene : public Scene
{
public:
	virtual ~AfterDeadScene() override;

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
private:
	Image* _bgImage = nullptr;
};

class PauseScene : public Scene
{
public:
	virtual ~PauseScene() override;

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
private:
	Image* _bgImage = nullptr;
};
