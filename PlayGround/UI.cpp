#include "stdafx.h"
#include "UI.h"
#include <string>

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
	_active = true;
	_position = Vector2(WINSIZEX / 2, 40);
	_size = Vector2(WINSIZEX, 100);
	_rect = RectMakePivot(_position, _size, Pivot::Center);	// 히트박스

	_player = dynamic_cast<Player*>(OBJECTMANAGER->FindObject(ObjectType::Player, L"Player"));
}

void UI::Release()
{

}

void UI::Update()
{
	//_position = CAMERA->GetPosition();
	_score = -_player->GetPosition().y / 10 + 90;

	if (_score < 0)
		_score = 0;

	if (_score > _highScore)
		_highScore = _score;
}

void UI::Render()
{
	_D2DRenderer->FillRectangle(_rect, D2DRenderer::DefaultBrush::White);
	_D2DRenderer->DrawRectangle(_rect, D2DRenderer::DefaultBrush::Black, 2.0f);
	//_D2DRenderer->FillRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::White);			// 채우기
	//_D2DRenderer->DrawRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::Black, 2.0f);		// 라인

	/*_D2DRenderer->RenderText(256, 400, L"UI 위치" + to_wstring((int)_position.x) + to_wstring((int)_position.y), 15);
	_D2DRenderer->RenderText(30, 400, L"위 :" + to_wstring(_rect.top), 15);
	_D2DRenderer->RenderText(0, 450, L"왼쪽 :" + to_wstring(_rect.left), 15);
	_D2DRenderer->RenderText(150, 450, L"오른쪽 :" + to_wstring(_rect.right), 15);
	_D2DRenderer->RenderText(30, 500, L"아래 :" + to_wstring(_rect.bottom), 15);*/

	_UIImage->Render(_position);
	//_UIImage->Render(CAMERA->GetRelativeVector2(_position));
	_D2DRenderer->RenderText(20, 15, to_wstring(_highScore), 25);
	_D2DRenderer->RenderText(20, 880, L"UI 실제 위치 x " + to_wstring(_position.x) + L"UI 실제위치 Y " + to_wstring(_position.y), 15);
	_D2DRenderer->RenderText(20, 910, L"UI 보이는 위치 x " + to_wstring(CAMERA->GetRelativeVector2(_position).x) + L"UI 보이는 위치 Y " + to_wstring(CAMERA->GetRelativeVector2(_position).y), 15);
}