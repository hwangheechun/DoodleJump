#include "stdafx.h"
#include "Player.h"
#include "Platform.h"
#include <string>

Player::Player()
	: _gauge(0.f)
{
	Init();
}

Player::~Player()
{
}

void Player::Init()
{
	_name = L"Player";
	_position = Vector2(WINSIZEX / 2, WINSIZEY - 100);
	_size = Vector2(60, 60);
	_rect = RectMakePivot(_position, _size, Pivot::Center);	// 히트박스
	_active = true;

	// 커스텀 변수들
	_direction = Vector2(1, 0);
	_gaugeRect = RectMakePivot(_position + Vector2(0, 60), Vector2(40.f, 10.f), Pivot::Center);

	_playerImage = IMAGEMANAGER->AddImage(L"Player Idle", L"Resources/doodle_left.png");
	//_playerImage = IMAGEMANAGER->FindImage(L"Player Idle");
	//_playerImage = IMAGEMANAGER->AddImage(L"Player Idle", L"Resources/Idle.png");	// 일반 이미지

	//_playerAnimation = new Animation();
	//_playerAnimation->Init(_playerImage->GetWidth(), _playerImage->GetHeight(), _playerImage->GetFrameSize().x, _playerImage->GetFrameSize().y);
	//_playerAnimation->SetPlayFrame(0, 1, false, true);
	//_playerAnimation->SetFPS(10);	// 조정하면서 살펴보기
	//_playerAnimation->Start();		// 이거 안 하면 시작 안 함
}

void Player::Release()
{
}

void Player::Update()
{
	// 0 -> 1 -> 2 / SetFPS를 통한 속도 반영
	//_playerAnimation->FrameUpdate(TIMEMANAGER->GetElapsedTime());
	/*_position = CAMERA->GetRelativeVector2(_position);*/
	_doodlePos = Vector2(_position.x, _position.y + _size.y / 2);

	_gravity += 2.0f;

	if (!_onGround)
		Move(Vector2(0.0f, _gravity), 10);

	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
	{
		if (_position.x > 0)
		{
			Move(Vector2(-25, 0), 10);
			_isLeft = true;
		}
	}
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
	{
		if (_position.x < WINSIZEX)
		{
			Move(Vector2(25, 0), 10);
			_isLeft = false;
		}
	}

	if (KEYMANAGER->IsStayKeyDown(VK_SPACE))
	{

	}
	if (KEYMANAGER->IsOnceKeyUp(VK_SPACE))
	{

	}

	_ground = OBJECTMANAGER->FindObject(ObjectType::Platform, L"Platform");

	if (_position.y + _size.y / 2 + 3 > _ground->GetPosition().y - _ground->GetSize().y / 2)
	{
		_onGround = true;

		if (KEYMANAGER->IsOnceKeyDown(VK_SPACE))
		{
			_onGround = false;
			_gravity = -70.0f;
		}
	}

	auto _platformBlock = OBJECTMANAGER->FindObjects(ObjectType::Block, L"Block");	//FindObject는 GameObject 포인터 타입 리턴, FindObjects는 GameObject 포인터 타입 벡터 리턴

	for (auto _block : _platformBlock) {
		if (!_block)
			continue;

		auto _collideBlock = dynamic_cast<PlatformBlock*>(_block);

		if (_doodlePos.x > _block->GetPosition().x - _block->GetSize().x / 2 && _doodlePos.x < _block->GetPosition().x + _block->GetSize().x / 2)	//두들의 x좌표가 블록의 x 범위 내부에 있다면
		{
			if (_doodlePos.y > _block->GetPosition().y - _block->GetSize().y / 2 && _doodlePos.y < _block->GetPosition().y + _block->GetSize().y / 2)
			{
				if (_gravity > 0)
				{
					_gravity = -70.0f;
				}
			}
		}
	}
}

void Player::Render()
{
	//_playerImage->AniRender(_position, _playerAnimation, 2.0f);
	
	//_D2DRenderer->DrawRectangle(_rect, D2DRenderer::DefaultBrush::Black, 2.0f);		// 라인
	_playerImage->Render(CAMERA->GetRelativeVector2(_position));
	_D2DRenderer->RenderText(100, 730, L"카메라 대비 캐릭터 위치x : " + to_wstring(CAMERA->GetRelativeVector2(_position).x) + to_wstring(CAMERA->GetRelativeVector2(_position).y), 15);
	_D2DRenderer->RenderText(100, 830, L"카메라 좌측 : " + to_wstring(CAMERA->Getrc().x) + L"스크린 중심 : " + to_wstring(CAMERA->Getrc().y), 15);
	_D2DRenderer->RenderText(100, 930, L"캐릭터 위치 x " + to_wstring(_position.x) + L"캐릭터 위치 Y " + to_wstring(_position.y), 15);
	
}

void Player::Move(Vector2 moveDirection, float speed)
{
	// 예시 1
	/*
	_position.x += moveDirection.x * speed * TIMEMANAGER->GetElapsedTime();
	_position.y += moveDirection.y * speed * TIMEMANAGER->GetElapsedTime();
	_rect = RectMakePivot(_position, _size, Pivot::Center);
	*/

	// 예시 2
	_position += moveDirection * speed * TIMEMANAGER->GetElapsedTime();	// == deltaTime
	_rect = RectMakePivot(_position, _size, Pivot::Center);
}