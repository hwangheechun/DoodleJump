#pragma once
#include "../GameFramework/GameNode.h"
#include "Platform.h"
#include "Obstacle.h"
#include "EventManager.h"
#include "UIController.h"	

class Player;

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
	UIController* _ui = nullptr;	
};

