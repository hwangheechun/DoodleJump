#include "stdafx.h"
#include "Doodle.h"
#include "Platform.h"
#include <string>

Doodle::Doodle()
{
	Init();
}

Doodle::~Doodle()
{

}

void Doodle::Init()
{
	_name = L"Doodle";
	_position = Vector2(WINSIZEX / 2, WINSIZEY - 100);
	_size = Vector2(60, 60);
	_rect = RectMakePivot(_position, _size, Pivot::Center);
	_active = true;

	_gravity = 10.0f;

	_doodleLeft = IMAGEMANAGER->AddImage(L"Doodle_Left", L"Resources/doodle_left.png");
	_doodleRight = IMAGEMANAGER->AddImage(L"Doodle_Right", L"Resources/doodle_right.png");

	//_doodleAnimation = new Animation();
	//_doodleAnimation->Init(_doodleLeft->GetWidth(), _doodleLeft->GetHeight(), _doodleLeft->GetFrameSize().x, _doodleLeft->GetFrameSize().y);
	//_doodleAnimation->SetPlayFrame(0, 1, false, true);
	//_doodleAnimation->SetFPS(10);	// 조정하면서 살펴보기
	//_doodleAnimation->Start();		// 이거 안 하면 시작 안 함

	_isLeft = true;
}

void Doodle::Release()
{

}

void Doodle::Update()
{
	_doodlePos = Vector2(_position.x, _position.y + _size.y / 2);

	_gravity += 2.0f;

	if (!_onGround)
		Move(Vector2(0.0f, _gravity), 10);

	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
	{
		if (_position.x > 0)
		{
			Move(Vector2(-20, 0), 10);
			_isLeft = true;
		}
	}
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
	{
		if (_position.x < WINSIZEX)
		{
			Move(Vector2(20, 0), 10);
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

	//_doodleAnimation->FrameUpdate(TIMEMANAGER->GetElapsedTime());
}

void Doodle::Render()
{
	//_D2DRenderer->FillRectangle(_rect, D2DRenderer::DefaultBrush::White);			// 채우기
	//_D2DRenderer->DrawRectangle(_rect, D2DRenderer::DefaultBrush::Black, 1.0f);		// 라인

	if (_isLeft)
	{
		_doodleLeft->Render(_rect.GetCenter());	// 일반 이미지
		//_doodleLeft->AniRender(_rect.GetCenter() + Vector2(0, -15), _doodleAnimation, 2.0f);
	}
	else
	{
		_doodleRight->Render(_rect.GetCenter());	// 일반 이미지
		//_doodleRight->AniRender(_rect.GetCenter() + Vector2(0, -15), _doodleAnimation, 2.0f);
	}

	//_doodleRight->Render(_rect.GetCenter());	// 일반 이미지
	//_doodleImage->AniRender(_rect.GetCenter() + Vector2(0, -15), _doodleAnimation, 2.0f);
	//_doodleImage->FrameRender(_rect.GetCenter(), 0, 0);
	//_playerImage->Render(_rect.GetCenter());	// 일반 이미지
	_D2DRenderer->RenderText(10, 10, L"Score : " + to_wstring(-((int)_doodlePos.y - 1000) / 100), 20);
}

void Doodle::Move(Vector2 moveDirection, float speed)
{
	_position += moveDirection * speed * TIMEMANAGER->GetElapsedTime();	// == deltaTime
	_rect = RectMakePivot(_position, _size, Pivot::Center);
}