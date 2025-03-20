#include "stdafx.h"
#include "MainScene.h"
#include "PlayGround/Platform.h"
#include <string>

MainScene::~MainScene()
{
}

HRESULT MainScene::Init()
{
	srand(unsigned int(time(NULL)));

	CAMERA->ChangeTarget(OBJECTMANAGER->FindObject(ObjectType::Player, L"Player"));
	//CAMERA->SetMapSize(Vector2(WINSIZEX, 1300));
	CAMERA->SetCameraMode(CameraState::TARGET);

	IMAGEMANAGER->AddImage(L"pause_cover", L"Resources/pause_cover.png");
	_bgImage = IMAGEMANAGER->AddImage(L"bg", L"Resources/background.png");

	//UI
	ui = new UI();
	OBJECTMANAGER->AddObject(ObjectType::UI, ui);

	//블록
	for (int i = 0; i < 20; i++)
	{
		PlatformBlock* block = new PlatformBlock();
		OBJECTMANAGER->AddObject(ObjectType::Block, block);
	}

	//트램펄린
	Trampoline* trampoline = new Trampoline();
	OBJECTMANAGER->AddObject(ObjectType::Item, trampoline);

	//구멍
	Hole* hole = new Hole();
	OBJECTMANAGER->AddObject(ObjectType::Item, hole);

	_block = OBJECTMANAGER->FindObjects(ObjectType::Block, L"Block");
	_trampoline = dynamic_cast<Trampoline*>(OBJECTMANAGER->FindObject(ObjectType::Item, L"Trampoline"));
	_hole = dynamic_cast<Hole*>(OBJECTMANAGER->FindObject(ObjectType::Item, L"Hole"));		

	for (int i = 0; i < 20; i++)
	{
		if (i == 0) 
			continue;

		dynamic_cast<PlatformBlock*>(_block[i])->SetRandomCreate(Vector2(rand() % 473 + 20, (int)(_block[i - 1]->GetPosition().y - (rand() % 51 + 50))), rand() % 20);

		if(dynamic_cast<PlatformBlock*>(_block[i])->_blockType == BlockType::GREEN && _trampoline->_onScreen == false)
			_trampoline->SetRandomCreate(_block[i]->GetPosition() + Vector2(0, -15), 1);
	}

	if(!_hole->_onScreen)
		_hole->SetRandomCreate(Vector2(rand() % 473 + 20, rand() % WINSIZEY), rand() % 10);

	return S_OK;
}

void MainScene::Release()
{

}

void MainScene::Update()
{
	Scene::Update();

	int randValue = 0;

	// 조건이 달성이 되었다
	bool bTest = false;
	if (bTest) {
		SCENEMANAGER->ChangeScene(_nextScene);
	}


	for (int i = 0; i < 20; i++)
	{
		if (CAMERA->GetRelativeVector2(_block[i]->GetPosition()).y > WINSIZEY)
		{
			if(i == 0)
				dynamic_cast<PlatformBlock*>(_block[i])->SetRandomCreate(Vector2(rand() % 473 + 20, (int)(_block[19]->GetPosition().y - (rand() % 51 + 50))), rand() % 20);
			else
				dynamic_cast<PlatformBlock*>(_block[i])->SetRandomCreate(Vector2(rand() % 473 + 20, (int)(_block[i - 1]->GetPosition().y - (rand() % 51 + 50))), rand() % 20);
		}
	}

	if (CAMERA->GetRelativeVector2(_trampoline->GetPosition()).y > WINSIZEY)
	{
		_trampoline->_onScreen = false;

		randValue = rand() % 20;
		if (dynamic_cast<PlatformBlock*>(_block[randValue])->_blockType == BlockType::GREEN && _trampoline->_onScreen == false && _block[randValue]->GetPosition().y < 0)
			_trampoline->SetRandomCreate(_block[randValue]->GetPosition() + Vector2(0, -15), rand() % 10 + 1);
	}

	if (CAMERA->GetRelativeVector2(_hole->GetPosition()).y > WINSIZEY)
	{
		_hole->_onScreen = false;

		_hole->SetRandomCreate(Vector2(rand() % 473 + 20, (int)CAMERA->GetrcTop().y), rand() % 10 + 1);
	}

	if (ui->_pauseButton->_isPause)
		_bgImage = IMAGEMANAGER->FindImage(L"pause_cover");
	else
		_bgImage = IMAGEMANAGER->FindImage(L"bg");
}

void MainScene::Render()
{
	Scene::Render();

	if (_bgImage) {
		Vector2 vImage{};
		vImage.x = _bgImage->GetWidth() / 2.f;
		vImage.y = _bgImage->GetHeight() / 2.f;
		_bgImage->Render(vImage);
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

	_bgImage = IMAGEMANAGER->AddImage(L"bg", L"Resources/background.png");

	return S_OK;
}

void AfterDeadScene::Release()
{
	// OBJECTMANAGER 지워 준다
}

void AfterDeadScene::Update()
{
	Scene::Update();

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

PauseScene::~PauseScene()
{
}

HRESULT PauseScene::Init()
{
	srand(unsigned int(time(NULL)));

	//_bgImage = IMAGEMANAGER->AddImage(L"bg", L"Resources/block_green.png");

	return S_OK;
}

void PauseScene::Release()
{
	// OBJECTMANAGER 지워 준다
}

void PauseScene::Update()
{
	Scene::Update();

	bool bTest = false;
	if (bTest) {
		SCENEMANAGER->ChangeScene(_nextScene);
	}
}

void PauseScene::Render()
{
	Scene::Render();

	if (_bgImage) {
		Vector2 vImage{};
		vImage.x = _bgImage->GetWidth() / 2.f;
		vImage.y = _bgImage->GetHeight() / 2.f;
		_bgImage->Render(vImage);
	}
}