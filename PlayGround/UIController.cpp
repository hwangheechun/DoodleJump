#include "stdafx.h"
#include "UIController.h"

UIController::UIController()
{
	Init();
}

HRESULT UIController::Init()
{
	//IMAGEMANAGER->AddImage(L"Menu", L"Resources/button_back.png");
	IMAGEMANAGER->AddImage(L"Menu", L"Resources/pause_button.png");

	_uiSave = new UISave;

	return S_OK;
}

void UIController::Release()
{
}

void UIController::Update()
{
}

void UIController::Render()
{
}
