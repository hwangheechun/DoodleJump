#pragma once
#include "Scene.h"

class MainScene : public Scene
{
public:
	virtual ~MainScene() override;

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
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
