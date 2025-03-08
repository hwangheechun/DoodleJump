#include "stdafx.h"
#include "UI.h"

UI::UI()
{
	Init();
}

UI::~UI()
{

}

void UI::Init()
{
	_UIImage = IMAGEMANAGER->AddImage(L"TopScoreUI", L"Resources/TopScoreUI.png");
	_UIImage->SetAlpha(0.0f);
	_active = true;
	_position = Vector2(200, 100);
	_rect = RectMakePivot(_position, _size, Pivot::Center);	// 히트박스
}

void UI::Release()
{

}

void UI::Update()
{
	_position = Vector2(WINSIZEX / 2, (int)CAMERA->GetrcTop().y + 50);
	//_rect = RectMakePivot(Vector2(CAMERA->GetrcTop().x, CAMERA->GetrcTop().y), _size, Pivot::Center);	// 히트박스
}

void UI::Render()
{
	_D2DRenderer->FillRectangle(_rect, D2DRenderer::DefaultBrush::White);			// 채우기
	_D2DRenderer->DrawRectangle(_rect, D2DRenderer::DefaultBrush::Black, 2.0f);		// 라인

	_UIImage->Render(CAMERA->GetRelativeVector2(_position));
}