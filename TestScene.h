#pragma once
#include "Scene.h"

class TestScene : public Scene
{
public:
	virtual ~TestScene() override;

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
private:
	Image* _bgImage;
};

