#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"

Bullet::Bullet()
	: _player(nullptr), _isInit(false)
{
	Init();
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	_name = L"Bullet";
	_position = Vector2(WINSIZEX / 2 - 100, WINSIZEY / 2 - 100);
	_size = Vector2(10, 10);
	_rect = RectMakePivot(_position, _size, Pivot::Center);
	_active = false;	// 미리 생성 후 가져다 쓸 용도로 이렇게 설정함, 생성해서 쓰려면 true로 놓는 것이 맞음

	_direction = Vector2(1, 0);
	_isInit = false;

	_player = dynamic_cast<Player*>(OBJECTMANAGER->FindObject(ObjectType::Player, L"Player"));
	if (_player)
	{
		_position = _player->GetPosition();
	}
}

void Bullet::Release()
{
}

void Bullet::Update()
{
	MoveAngle(200.0f);
}

void Bullet::Render()
{
	D2DRenderer::GetInstance()->DrawEllipse(_position, _size.x, D2DRenderer::DefaultBrush::Black, 1.0f);
}

void Bullet::Move(Vector2 moveDirection, float speed)
{
	_position += moveDirection * speed * TIMEMANAGER->GetElapsedTime();
	_rect = RectMakePivot(_position, _size, Pivot::Center);
}

void Bullet::MoveAngle(float speed)
{
	_position += _direction * speed * TIMEMANAGER->GetElapsedTime();
	_rect.Update(_position, _size, Pivot::Center);
}
