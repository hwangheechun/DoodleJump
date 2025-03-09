#include "stdafx.h"
#include "MainScene.h"
#include "PlayGround/Platform.h"
#include "PlayGround/UI.h"

MainScene::~MainScene()
{
}

HRESULT MainScene::Init()
{
	srand(unsigned int(time(NULL)));

	CAMERA->ChangeTarget(OBJECTMANAGER->FindObject(ObjectType::Player, L"Player"));
	//CAMERA->SetMapSize(Vector2(WINSIZEX, 1300));
	CAMERA->SetCameraMode(CameraState::TARGET);

	_bgImage = IMAGEMANAGER->AddImage(L"bg", L"Resources/background.png");

	//블록
	for (int i = 0; i < 20; i++)
	{
		PlatformBlock* block = new PlatformBlock();
		OBJECTMANAGER->AddObject(ObjectType::Block, block);
	}

	UI* ui = new UI();
	OBJECTMANAGER->AddObject(ObjectType::UI, ui);

	return S_OK;
}

void MainScene::Release()
{
	// OBJECTMANAGER 지워 준다
	OBJECTMANAGER->RemoveObjects(ObjectType::Block);
}

void MainScene::Update()
{
	Scene::Update();

	// 조건이 달성이 되었다
	bool bTest = false;
	if (bTest) {
		SCENEMANAGER->ChangeScene(_nextScene);
	}
}

void MainScene::Render()
{
	Scene::Render();

	if (_bgImage) {
		Vector2 vImage{};
		vImage.x = _bgImage->GetWidth() / 2.f;
		vImage.y = _bgImage->GetHeight() / 2.f;
		_bgImage->Render(vImage);
		//_bgImage->Render(CAMERA->GetRelativeVector2(vImage));
	}
}

AfterDeadScene::~AfterDeadScene()
{
}

HRESULT AfterDeadScene::Init()
{
	srand(unsigned int(time(NULL)));

	CAMERA->ChangeTarget(OBJECTMANAGER->FindObject(ObjectType::Player, L"Player"));
	//CAMERA->SetMapSize(Vector2(WINSIZEX, 1300));
	CAMERA->SetCameraMode(CameraState::TARGET);

	//_bgImage = IMAGEMANAGER->AddImage(L"bg", L"Resources/background.png");

	return S_OK;
}

void AfterDeadScene::Release()
{
	// OBJECTMANAGER 지워 준다
}

void AfterDeadScene::Update()
{
	Scene::Update();

	// 조건이 달성이 되었다
	bool bTest = false;
	if (bTest) {
		SCENEMANAGER->ChangeScene(_nextScene);
	}
}

void AfterDeadScene::Render()
{
	Scene::Render();

	if (_bgImage) {
		Vector2 vImage{};
		vImage.x = _bgImage->GetWidth() / 2.f;
		vImage.y = _bgImage->GetHeight() / 2.f;
		_bgImage->Render(vImage);
		//_bgImage->Render(CAMERA->GetRelativeVector2(vImage));
	}
}