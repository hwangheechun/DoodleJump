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
	CAMERA->SetCameraMode(CameraState::TARGET);

	IMAGEMANAGER->AddImage(L"pause_cover", L"Resources/pause_cover.png");
	IMAGEMANAGER->AddImage(L"end_cover", L"Resources/end_cover.png");
	_bgImage = IMAGEMANAGER->AddImage(L"bg", L"Resources/background.png");

	//UI
	ui = new UI();
	OBJECTMANAGER->AddObject(ObjectType::UI, ui);

	//블록
	for (int i = 0; i < BLOCKCOUNT; i++)
	{
		PlatformBlock* block = new PlatformBlock();
		OBJECTMANAGER->AddObject(ObjectType::Block, block);
	}

	_block = OBJECTMANAGER->FindObjects(ObjectType::Block, L"Block");

	for (int i = 1; i < BLOCKCOUNT; i++)	//1~19번째 블록 50~100 간격 두고 생성하기
	{
		dynamic_cast<PlatformBlock*>(_block[i])->SetRandomCreate(Vector2(rand() % 473 + 20, (int)(_block[i - 1]->GetPosition().y - (rand() % 51 + 50))), BLOCKTYPEVALUE);
	}

	//구멍
	_hole = new Hole();
	OBJECTMANAGER->AddObject(ObjectType::Item, _hole);

	//트램펄린
	_trampoline = new Trampoline();
	OBJECTMANAGER->AddObject(ObjectType::Item, _trampoline);

	_player = dynamic_cast<Player*>(OBJECTMANAGER->FindObject(ObjectType::Player, L"Player"));

	return S_OK;
}

void MainScene::Release()
{

}

void MainScene::Update()
{
	Scene::Update();

	for (int i = 0; i < BLOCKCOUNT; i++)
	{
		if (CAMERA->GetRelativeVector2(_block[i]->GetPosition()).y > WINSIZEY)
		{
			if(i == 0)
				dynamic_cast<PlatformBlock*>(_block[i])->SetRandomCreate(Vector2(rand() % 473 + 20, (int)(_block[19]->GetPosition().y - (rand() % 51 + 50))), BLOCKTYPEVALUE);
			else
				dynamic_cast<PlatformBlock*>(_block[i])->SetRandomCreate(Vector2(rand() % 473 + 20, (int)(_block[i - 1]->GetPosition().y - (rand() % 51 + 50))), BLOCKTYPEVALUE);
		}
	}

	if (CAMERA->GetRelativeVector2(_trampoline->GetPosition()).y > WINSIZEY)	//트램펄린이 화면 밖을 나가면 재생성
	{
		_trampoline->_onScreen = false;

		//20번째 블록마다 블록 타입이 그린이고 화면 밖에 있을 때 50% 확률로 트램펄린 설치 
		if (dynamic_cast<PlatformBlock*>(_block[BLOCKCOUNT - 1])->_blockType == BlockType::GREEN && _trampoline->_onScreen == false && _block[BLOCKCOUNT - 1]->GetPosition().y < -100)
			_trampoline->SetRandomCreate(_block[BLOCKCOUNT - 1]->GetPosition() + Vector2(0, -15), rand() % 10 + 1);
	}

	if (CAMERA->GetRelativeVector2(_hole->GetPosition()).y > WINSIZEY)
	{
		_hole->_onScreen = false;

		_hole->SetRandomCreate(Vector2(rand() % 473 + 20, (int)CAMERA->GetrcTop().y), rand() % 10 + 1);
	}

	if (!_player->_isDead)
	{
		if (ui->_pauseButton->_isPause)
		{
			_bgImage = IMAGEMANAGER->FindImage(L"pause_cover");
			_hole->SetActive(false);
		}
		else
		{
			_bgImage = IMAGEMANAGER->FindImage(L"bg");
			_hole->SetActive(true);
		}
	}
	else
	{
		_bgImage = IMAGEMANAGER->FindImage(L"end_cover");
		_hole->SetActive(false);
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
	}

	if(_player && _player->_isDead)
		_D2DRenderer->RenderText(260, 400, to_wstring(ui->_highScore), 75);
}

AfterDeadScene::~AfterDeadScene()
{
}

HRESULT AfterDeadScene::Init()
{
	srand(unsigned int(time(NULL)));

	CAMERA->ChangeTarget(OBJECTMANAGER->FindObject(ObjectType::Player, L"Player"));
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