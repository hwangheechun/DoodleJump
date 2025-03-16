#include "stdafx.h"
#include "UISave.h"

UISave::UISave()
	: Button(L"Menu", Vector2(WINSIZEX - 150, 50), 0, 0, 0, 0, bind(&UISave::OnClick_Menu, this))	// funtion 쪽 중급 문법 std::bind 찾아보세요
{
	Init();
}

void UISave::Init()
{
	_name = L"UI_Save";

	OBJECTMANAGER->AddObject(ObjectType::UI, this);
	SetActive(true);

	IMAGEMANAGER->AddFrameImage(L"Menus", L"Resources/button_menu.png", 1, 5);
	_saveButton = new Button(L"Menus", Vector2(WINSIZEX / 2, WINSIZEY / 2), 0, 0, 0, 0, bind(&UISave::OnClick_Save, this));
	_loadButton = new Button(L"Menus", Vector2(WINSIZEX / 2, WINSIZEY / 2 + 100), 0, 1, 0, 1, bind(&UISave::OnClick_Load, this));

	OBJECTMANAGER->AddObject(ObjectType::UI, _saveButton);
	OBJECTMANAGER->AddObject(ObjectType::UI, _loadButton);
}

void UISave::Release()
{
}

void UISave::Update()
{
	__super::Update();	// Button의 Update가 일을 하고 있으니까, 무조건 호출

	_saveButton->SetActive(_isOnMenu);
	_loadButton->SetActive(_isOnMenu);
}

void UISave::Render()
{
	__super::Render();	// Button의 Render가 일을 하고 있으니까, 무조건 호출

	if (_isOnMenu) {
		D2DRenderer::GetInstance()->RenderText(50, 50, L"isOnMenu TRUE", 20);
	}
}

void UISave::OnClick_Menu()
{
	_isOnMenu = !_isOnMenu;
}

void UISave::OnClick_Save()
{
}

void UISave::OnClick_Load()
{
}