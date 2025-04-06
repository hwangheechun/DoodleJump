#include "stdafx.h"
#include "UI.h"
#include <string>
#include "UISave.h"

UI::UI()
{
	Init();
}

UI::~UI()
{

}

void UI::Init()
{
	_name = L"UI";
	_UIImage = IMAGEMANAGER->AddImage(L"TopScoreUI", L"Resources/TopScoreUI.png");
	_active = true;
	_position = Vector2(WINSIZEX / 2, 40);
	_size = Vector2(WINSIZEX, 100);
	_rect = RectMakePivot(_position, _size, Pivot::Center);	

	_player = dynamic_cast<Player*>(OBJECTMANAGER->FindObject(ObjectType::Player, L"Player"));

	IMAGEMANAGER->AddImage(L"Pause", L"Resources/pause_button.png");
	_pauseButton = new Button(L"Pause", Vector2(WINSIZEX - 50, 30), 0, 0, 0, 0);
}

void UI::Release()
{

}

void UI::Update()
{
	if(_player)	//null
		_score = -_player->GetPosition().y / 10 + 90;

	if (_score < 0)
		_score = 0;
	else if (_score > _highScore)
		_highScore = _score;

	RECT rc = _pauseButton->GetRect().GetRect();
	if (PtInRect(&rc, _ptMouse))	// 위치만 보는 것, 마우스가 RECT 안에 있다면
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			_pauseButton->Pause();
		}
	}

	if (_pauseButton->_isPause)
	{
		OBJECTMANAGER->FindObject(ObjectType::Player, L"Player")->SetActive(false);
		for (int i = 0; i < 20; i++)
		{
			OBJECTMANAGER->FindObjects(ObjectType::Block, L"Block")[i]->SetActive(false);
		}
		//SCENEMANAGER->ChangeScene(L"PauseScene");
	}
	else 
	{
		if (_player && !_player->_isDead)	//여기서 플레이어의 죽음 체크를 하지 않으면 플레이어 내부에서 죽음 판정을 부여하더라도 여기서 true라고 해버리니 플레이어가 죽지 않는다
		{
			OBJECTMANAGER->FindObject(ObjectType::Player, L"Player")->SetActive(true);

			for (int i = 0; i < 20; i++)
			{
				OBJECTMANAGER->FindObjects(ObjectType::Block, L"Block")[i]->SetActive(true);
			}
		}
	}

	if (_player && _player->_isDead) this->SetActive(false);
}

void UI::Render()
{
	_UIImage->Render(_position);
	_D2DRenderer->RenderText(20, 15, to_wstring(_highScore), 25);

	_pauseButton->Render();
}