#pragma once
#include "Scene.h"
#include "PlayGround/UI.h"
#include "PlayGround/Item.h"

class MainScene : public Scene
{
public:
	virtual ~MainScene() override;

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	UI* ui;
	vector<GameObject*> _block;
	Trampoline* _trampoline;
	Hole* _hole;
private:
	Image* _bgImage;
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
	Image* _bgImage;
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
	Image* _bgImage;
};
