#include "stdafx.h"
#include "TestScene.h"
#include "PlayGround/Platform.h"

TestScene::~TestScene()
{
}

HRESULT TestScene::Init()
{
	srand(unsigned int(time(NULL)));

	CAMERA->ChangeTarget(OBJECTMANAGER->FindObject(ObjectType::Player, L"Player"));
	//CAMERA->SetMapSize(Vector2(WINSIZEX, 1300));
	CAMERA->SetCameraMode(CameraState::TARGET);

	_bgImage = IMAGEMANAGER->AddImage(L"bg", L"Resources/background.png");

	//블록
	for (int i = 0; i < 20; i++)
	{
		PlatformBlock* block = new PlatformBlock(rand() % (WINSIZEY - 100));
		OBJECTMANAGER->AddObject(ObjectType::Block, block);
	}

	return S_OK;
}

void TestScene::Release()
{
	// OBJECTMANAGER 지워 준다
}

void TestScene::Update()
{
	Scene::Update();

	// 조건이 달성이 되었다
	bool bTest = false;
	if (bTest) {
		SCENEMANAGER->ChangeScene(_nextScene);
	}
}

void TestScene::Render()
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
