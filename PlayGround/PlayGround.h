#pragma once
#include "../GameFramework/GameNode.h"
#include "Player.h"
#include "Platform.h"
#include "Scene.h"
#include "UI.h"
#include "Obstacle.h"

#include "EventManager.h"
#include "UIController.h"	//3 16 추가

class PlayGround : public GameNode
{	
public:
	PlayGround() = default;
	virtual ~PlayGround() = default;

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

private:
	UIController* _ui = nullptr;	//3 16 추가
};

