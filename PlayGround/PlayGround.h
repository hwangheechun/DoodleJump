#pragma once
#include "../GameFramework/GameNode.h"
#include "Player.h"
#include "Doodle.h"
#include "Platform.h"
#include "Scene.h"
#include "Obstacle.h"

#include "EventManager.h"

class PlayGround : public GameNode
{	
public:
	PlayGround() = default;
	virtual ~PlayGround() = default;

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

