#include "stdafx.h"
#include "Item.h"
#include <string>

#pragma region 아이템
Item::Item()
{
	Init();
}

Item::~Item()
{

}

void Item::Init()
{
	_player = dynamic_cast<Player*>(OBJECTMANAGER->FindObject(ObjectType::Player, L"Player"));
}

void Item::Release()
{

}

void Item::Update()
{
	if (_player && _player->_isDead) this->SetActive(false);
}

void Item::Render()
{

}
#pragma endregion

#pragma region 프로펠러
Propeller::Propeller()
{
	
}

Propeller::~Propeller()
{

}

void Propeller::Init()
{
	_name = L"Propeller";
	_position = Vector2(WINSIZEX / 2, WINSIZEY - 100);
	_size = Vector2(75, 22);
	_active = true;

	IMAGEMANAGER->AddImage(L"propeller", L"Resources/block_green.png");
}

void Propeller::Release()
{

}

void Propeller::Update()
{

}

void Propeller::Render()
{
	_D2DRenderer->FillRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::White);
	_D2DRenderer->DrawRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::Black, 2.0f);

	_propellerImage->Render(CAMERA->GetRelativeVector2(_position));
	_D2DRenderer->RenderText(20, 910, L"UI 보이는 위치 x " + to_wstring(CAMERA->GetRelativeVector2(_position).x) + L"UI 보이는 위치 Y " + to_wstring(CAMERA->GetRelativeVector2(_position).y), 15);
}
#pragma endregion

#pragma region 트램펄린
Trampoline::Trampoline()
{
	Init();
}

Trampoline::~Trampoline()
{

}

void Trampoline::Init()
{
	_name = L"Trampoline";
	_position = Vector2(WINSIZEX / 2, WINSIZEY + 100);
	_size = Vector2(75, 22);
	_active = true;
	_rect = RectMakePivot(_position, _size, Pivot::Center);
	_trampolineImage = IMAGEMANAGER->AddFrameImage(L"propeller", L"Resources/trampoline.png", 3, 1);
	_onScreen = false;

	_trampolineAnimation = new Animation();
	_trampolineAnimation->Init(_trampolineImage->GetWidth(), _trampolineImage->GetHeight(), _trampolineImage->GetFrameSize().x, _trampolineImage->GetFrameSize().y);
	_trampolineAnimation->SetPlayFrame(0, 3, false, false);	//(start, end, 거꾸로, 반복) 여기서는 점프 시 프레임을 순서대로 한 번 Play
	_trampolineAnimation->SetFPS(10);
}

void Trampoline::Release()
{

}

void Trampoline::Update()
{
	_rect = RectMakePivot(_position, _size, Pivot::Center);

	_trampolineAnimation->FrameUpdate(TIMEMANAGER->GetElapsedTime());
	
	if(IsCollide(_player))
		_trampolineAnimation->Start();

	if (_player && _player->_isDead) this->SetActive(false);
}

void Trampoline::Render()
{
	_trampolineImage->AniRender(CAMERA->GetRelativeVector2(_position), _trampolineAnimation, 0.3f);
}

void Trampoline::SetRandomCreate(Vector2 randPos, int successValue)
{
	_onScreen = true;

	if(successValue > 5)
		_position = randPos;
}

bool Trampoline::IsCollide(GameObject* object)	//충돌했다면
{
	if (_position.x > object->GetPosition().x - object->GetSize().x / 2 && _position.x < object->GetPosition().x + object->GetSize().x / 2
		&& _position.y > object->GetPosition().y - object->GetSize().y / 2 && _position.y < object->GetPosition().y + object->GetSize().y / 2)
	{
		return true;
	}
	else return false;
}
#pragma endregion

#pragma region 구멍
Hole::Hole()
{
	Init();
}

Hole::~Hole()
{

}

void Hole::Init()
{
	_name = L"Hole";
	_position = Vector2(WINSIZEX / 2, WINSIZEY + 100);
	_size = Vector2(75, 22);
	_active = true;
	_rect = RectMakePivot(_position, _size, Pivot::Center);
	_holeImage = IMAGEMANAGER->AddImage(L"Hole", L"Resources/hole.png");
}

void Hole::Release()
{

}

void Hole::Update()
{
	_rect = RectMakePivot(_position, _size, Pivot::Center);

	if (IsCollide(_player))
	{
		_player->_isDead = true;
		this->SetActive(false);
	}
}

void Hole::Render()
{
	_holeImage->Render(CAMERA->GetRelativeVector2(_position));
}

void Hole::SetRandomCreate(Vector2 randPos, int successValue)
{
	_onScreen = true;

	if (successValue > 5)
		_position = randPos;
}

bool Hole::IsCollide(GameObject* object)	//충돌했다면
{
	if (_position.x > object->GetPosition().x - object->GetSize().x / 2 && _position.x < object->GetPosition().x + object->GetSize().x / 2
		&& _position.y > object->GetPosition().y - object->GetSize().y / 2 && _position.y < object->GetPosition().y + object->GetSize().y / 2)
	{
		return true;
	}
	else return false;
}
#pragma endregion 