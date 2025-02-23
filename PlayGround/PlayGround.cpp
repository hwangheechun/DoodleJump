#include "stdafx.h"
#include "PlayGround.h"
#include "IEvent.h"
#include "Bullet.h"
#include "TestScene.h"

HRESULT PlayGround::Init()
{
	GameNode::Init(true);

	Player* player = new Player();

	OBJECTMANAGER->AddObject(ObjectType::Player, player);

	CAMERA->ChangeTarget(OBJECTMANAGER->FindObject(ObjectType::Player, L"Player"));
	CAMERA->SetMapSize(Vector2(512, WINSIZEY));

	SCENEMANAGER->AddScene(L"TestScene", new TestScene());
	SCENEMANAGER->ChangeScene(L"TestScene");
	/*
	SCENEMANAGER->AddScene(L"TestScene2", new TestScene2());
	SCENEMANAGER->AddScene(L"TestScene3", new TestScene3());
	SCENEMANAGER->AddScene(L"TestScene4", new TestScene4());
	SCENEMANAGER->AddScene(L"TestScene5", new TestScene5());
	*/

	

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
		OBJECTMANAGER->Render();
		SCENEMANAGER->Render();
	}
	D2DRenderer::GetInstance()->EndRender();
}
