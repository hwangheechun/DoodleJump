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

	_playerImage = IMAGEMANAGER->AddFrameImage(L"doodle_left", L"Resources/doodle_left_bend_sprite.png", 3, 1);
	_playerImage = IMAGEMANAGER->AddFrameImage(L"doodle_right", L"Resources/doodle_right_bend_sprite.png", 3, 1);
	_playerImage = IMAGEMANAGER->FindImage(L"doodle_left");
	//_playerImage = IMAGEMANAGER->AddImage(L"Player Idle", L"Resources/Idle.png");	// 일반 이미지

	_isLeft = true;
	_playerAnimation = new Animation();
	_playerAnimation->Init(_playerImage->GetWidth(), _playerImage->GetHeight(), _playerImage->GetFrameSize().x, _playerImage->GetFrameSize().y);
	_playerAnimation->SetPlayFrame(0, 3, false, false);	//(start, end, 거꾸로, 반복) 여기서는 점프 시 프레임을 순서대로 한 번 Play
	_playerAnimation->SetFPS(30);	// 조정하면서 살펴보기
}

void Player::Release()
{
}

void Player::Update()
{
	_doodlePos = Vector2(_position.x, _position.y + _size.y / 2); //편하게 사용하려고 _doodlePos 만듦

	if(_isLeft)	//좌우 판별
		_playerImage = IMAGEMANAGER->FindImage(L"doodle_left");
	else
		_playerImage = IMAGEMANAGER->FindImage(L"doodle_right");

	_playerAnimation->FrameUpdate(TIMEMANAGER->GetElapsedTime());

	_gravity += 2.5f;	//중력 가속
	if (!_onGround)
		Move(Vector2(0.0f, _gravity), 10);	//중력 적용

	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))		//좌
	{
		if (_position.x > 0)
		{
			Move(Vector2(-35, 0), 10);
			_isLeft = true;
		}
	}
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))	//우
	{
		if (_position.x < WINSIZEX)
		{
			Move(Vector2(35, 0), 10);
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
			_gravity = -90.0f;
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
				if (_collideBlock->_blockType >= 2)
				{
					if (_gravity > 0) //떨어지며 발판에 닿았다면(밑에서 충돌하는 판정 무시)
					{
						_gravity = -90.0f;
						_isJump = true;		//발판과 충돌하는 순간 true
					}
					else _isJump = false; //점프 이후에 바로 false
				}
			}
		}
	}

	if (_isJump)
	{
		_playerAnimation->Start();		// 이거 안 하면 시작 안 함
		//_isJump가 true인 찰나에 애니메이션 시작
	}
		
}

void Player::Render()
{
	_rect = RectMakePivot(CAMERA->GetRelativeVector2(_position), _size, Pivot::Center);	// 히트박스
	_playerImage->AniRender(CAMERA->GetRelativeVector2(_position) - Vector2(0, 10), _playerAnimation, 0.4f);
	//_D2DRenderer->DrawRectangle(_rect, D2DRenderer::DefaultBrush::Black, 2.0f);		// 라인

	//_playerImage->Render(CAMERA->GetRelativeVector2(_position));

	//카메라 값 표기
	/*_D2DRenderer->RenderText(20, 930, L"카메라 위치 왼쪽 : " + to_wstring(CAMERA->GetrcTop().x) + L"카메라 위치 위쪽 : " + to_wstring(CAMERA->GetrcTop().y), 15);
	_D2DRenderer->RenderText(20, 950, L"카메라 위치 오른쪽 : " + to_wstring(CAMERA->GetrcBottom().x) + L"카메라 위치 아래쪽 : " + to_wstring(CAMERA->GetrcBottom().y), 15);
	_D2DRenderer->RenderText(20, 980, L"캐릭터 실제 위치 x " + to_wstring(_position.x) + L"캐릭터 실제위치 Y " + to_wstring(_position.y), 15);
	_D2DRenderer->RenderText(20, 1010, L"캐릭터 보이는 위치 x " + to_wstring(CAMERA->GetRelativeVector2(_position).x) + L"캐릭터 보이는 위치 Y " + to_wstring(CAMERA->GetRelativeVector2(_position).y), 15);*/
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