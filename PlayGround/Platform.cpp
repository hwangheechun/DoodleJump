#include "stdafx.h"
#include "Platform.h"
#include <string>


Platform::Platform()
	//: _gauge(0.f)
{
	Init();
}

Platform::~Platform()
{
}

void Platform::Init()
{
	_name = L"Platform";
	_position = Vector2(WINSIZEX / 2, WINSIZEY - 20);
	_size = Vector2(WINSIZEX, 5);
	_rect = RectMakePivot(_position, _size, Pivot::Center);	// 히트박스
	_gravity = 1.0f;
	_active = true;
}

void Platform::Release()
{
}

void Platform::Update()
{

}

void Platform::Render()
{
	_D2DRenderer->FillRectangle(_rect, D2DRenderer::DefaultBrush::White);			// 채우기
	_D2DRenderer->DrawRectangle(_rect, D2DRenderer::DefaultBrush::Black, 1.0f);		// 라인
	//_D2DRenderer->RenderText(10, 500, L"크기 : " + to_wstring(_blockImage1->GetSize().x) + L" " + to_wstring(_blockImage1->GetSize().y), 30);
}

PlatformBlock::PlatformBlock()
{
	Init();
}

PlatformBlock::PlatformBlock(int a)
{
	Init(a);
}

PlatformBlock::~PlatformBlock()
{

}

void PlatformBlock::Init()
{
	_name = L"Block";
	_position = Vector2(0, 300);
	_size = Vector2(75, 22);
	_rect = RectMakePivot(_position, _size, Pivot::Center);	// 히트박스
	_gravity = 1.0f;
	_active = true;

	_blockImage = IMAGEMANAGER->AddImage(L"Block", L"Resources/block_green.png");
}

void PlatformBlock::Init(int a)
{
	_name = L"Block";
	_position = Vector2(rand() % 473 + 20, a);	
	_size = Vector2(75, 22);
	_rect = RectMakePivot(_position, _size, Pivot::Center);	// 히트박스
	_gravity = 1.0f;
	_active = true;

	_blockImage = IMAGEMANAGER->AddImage(L"Block", L"Resources/block_green.png");
	
	//_blockImage->SetScale(0.5f);

	//_blockAnimation = new Animation();
	//_blockAnimation->Init(_blockImage->GetWidth(), _blockImage->GetHeight(), _blockImage->GetFrameSize().x, _blockImage->GetFrameSize().y);
	//_blockAnimation->SetPlayFrame(0, 1, false, true);
	//_blockAnimation->SetFPS(10);	// 조정하면서 살펴보기
	//_blockAnimation->Start();		// 이거 안 하면 시작 안 함
}

void PlatformBlock::Release()
{
}

void PlatformBlock::Update()
{
	//_blockAnimation->FrameUpdate(TIMEMANAGER->GetElapsedTime());
	//Move(Vector2(0, 10), 10);
}

void PlatformBlock::Render()
{
	//_D2DRenderer->FillRectangle(_rect, D2DRenderer::DefaultBrush::White);			// 채우기
	//_D2DRenderer->DrawRectangle(_rect, D2DRenderer::DefaultBrush::Black, 2.0f);		// 라인
	
	//_D2DRenderer->RenderText(10, 500, L"크기 : " + to_wstring(_blockImage->GetSize().x) + L" " + to_wstring(_blockImage->GetSize().y), 30);
	_blockImage->Render(CAMERA->GetRelativeVector2(_position));
}

void PlatformBlock::Move(Vector2 moveDirection, float speed)
{
	_position += moveDirection * speed * TIMEMANAGER->GetElapsedTime();	// == deltaTime
	_rect = RectMakePivot(_position, _size, Pivot::Center);
}