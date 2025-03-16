#include "stdafx.h"
#include "Item.h"
#include <string>

Item::Item()
{

}

Item::~Item()
{

}

void Item::Init()
{

}

void Item::Release()
{

}

void Item::Update()
{

}

void Item::Render()
{

}

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