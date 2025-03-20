#include "stdafx.h"
#include "PlayGround.h"
#include "IEvent.h"
#include "MainScene.h"

HRESULT PlayGround::Init()
{
	GameNode::Init(true);

	//플레이어 두들
	Player* player = new Player();
	OBJECTMANAGER->AddObject(ObjectType::Player, player);

	SCENEMANAGER->AddScene(L"MainScene", new MainScene());
	SCENEMANAGER->AddScene(L"AfterDeadScene", new AfterDeadScene());
	SCENEMANAGER->AddScene(L"PauseScene", new PauseScene());
	SCENEMANAGER->ChangeScene(L"MainScene");


	//시작 땅
	Platform* platform = new Platform();
	OBJECTMANAGER->AddObject(ObjectType::Platform, platform);

	return S_OK;
}

void PlayGround::Release()
{
	OBJECTMANAGER->Release();
}

void PlayGround::Update()
{
	GameNode::Update();

	OBJECTMANAGER->Update();
	SCENEMANAGER->Update();
	CAMERA->Update();

	EventManager::GetInstance()->Update();
}

void PlayGround::Render()
{	
	// 백버퍼 초기화
	D2DRenderer::GetInstance()->BeginRender(D2D1::ColorF::White);
	{
		SCENEMANAGER->Render();
		OBJECTMANAGER->Render();
	}
	D2DRenderer::GetInstance()->EndRender();
}
