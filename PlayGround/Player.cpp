#include "stdafx.h"
#include "Player.h"
#include "Platform.h"
#include <string>

Player::Player()
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
	_rect = RectMakePivot(_position, _size, Pivot::Center);
	_active = true;

	_playerImage = IMAGEMANAGER->AddFrameImage(L"doodle_left", L"Resources/doodle_left_bend_sprite.png", 3, 1);
	_playerImage = IMAGEMANAGER->AddFrameImage(L"doodle_right", L"Resources/doodle_right_bend_sprite.png", 3, 1);
	_playerImage = IMAGEMANAGER->FindImage(L"doodle_left");
	//_playerImage = IMAGEMANAGER->AddImage(L"Player Idle", L"Resources/Idle.png");	// 일반 이미지

	_isLeft = true;

	_playerAnimation = new Animation();
	_playerAnimation->Init(_playerImage->GetWidth(), _playerImage->GetHeight(), _playerImage->GetFrameSize().x, _playerImage->GetFrameSize().y);
	_playerAnimation->SetPlayFrame(0, 3, false, false);	//(start, end, 거꾸로, 반복) 여기서는 점프 시 프레임을 순서대로 한 번 Play
	_playerAnimation->SetFPS(30);	// 조정하면서 살펴보기

	_isDead = false;
	_deadLineY = WINSIZEY;
}

void Player::Release()
{
}

void Player::Update()
{
	_doodlePos = Vector2(_position.x, _position.y + _size.y / 2); //편하게 사용하려고 _doodlePos 만듦
	_rect = RectMakePivot(_position, _size, Pivot::Center);
	if(_isLeft)	//좌우 판별
		_playerImage = IMAGEMANAGER->FindImage(L"doodle_left");
	else
		_playerImage = IMAGEMANAGER->FindImage(L"doodle_right");

	_playerAnimation->FrameUpdate(TIMEMANAGER->GetElapsedTime());

	_gravity += 2.5f;	//중력 가속
	if (!_onGround)
		Move(Vector2(0.0f, _gravity), 10);	//중력 적용
	else 
	{
		_takenTime = 0;
		_position.y = _ground->GetPosition().y - _ground->GetSize().y / 2 - _size.y / 2;
	}

	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))		//좌
	{
		if (_position.x > 0)
		{
			Move(Vector2(-35, 0), 10);
			_isLeft = true;
		}
		else _position.x = WINSIZEX;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))	//우
	{
		if (_position.x < WINSIZEX)
		{
			Move(Vector2(35, 0), 10);
			_isLeft = false;
		}
		else _position.x = 0;
	}

	_ground = OBJECTMANAGER->FindObject(ObjectType::Platform, L"Platform");

	if (_position.y + _size.y / 2 >= _ground->GetPosition().y - _ground->GetSize().y / 2)
	{
		_onGround = true;

		if (KEYMANAGER->IsOnceKeyDown(VK_SPACE))
		{
			_onGround = false;
			_gravity = -90.0f;
		}
	}

	auto _platformBlock = OBJECTMANAGER->FindObjects(ObjectType::Block, L"Block");	//FindObject는 GameObject 포인터 타입 리턴, FindObjects는 GameObject 포인터 타입 벡터 리턴

	for (auto _block : _platformBlock) 
	{
		if (!_block)
			continue;

		auto _collideBlock = dynamic_cast<PlatformBlock*>(_block);

		if (IsCollide(_block))	//충돌
		{
			if (_collideBlock->_blockType != BlockType::BROWN)
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

	if (_isJump)
	{
		_playerAnimation->Start();		// 이거 안 하면 시작 안 함
		//_isJump가 true인 찰나에 애니메이션 시작
	}

	if (_gravity == 0)
		_deadLineY = CAMERA->GetrcBottom().y;

	if (_position.y > _deadLineY)
	{
		_isDead = true;
	}

	if (_isDead)
	{
		//SCENEMANAGER->ChangeScene(L"AfterDeadScene");
		SetActive(false);
	}
}

void Player::Render()
{
	_playerImage->AniRender(CAMERA->GetRelativeVector2(_position) - Vector2(0, 10), _playerAnimation, 0.4f);
}

void Player::Move(Vector2 moveDirection, float speed)
{
	_position += moveDirection * speed * TIMEMANAGER->GetElapsedTime();	// == deltaTime
	_rect = RectMakePivot(_position, _size, Pivot::Center);
}

void Player::MoveAngle(float angle, float speed)
{

}

bool Player::IsCollide(GameObject* object)	//충돌했다면
{
	if (_doodlePos.x > object->GetPosition().x - object->GetSize().x / 2 && _doodlePos.x < object->GetPosition().x + object->GetSize().x / 2
		&& _doodlePos.y > object->GetPosition().y - object->GetSize().y / 2 && _doodlePos.y < object->GetPosition().y + object->GetSize().y / 2)	
	{
		return true;
	}
	else return false;
}