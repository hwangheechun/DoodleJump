#pragma once
#include "Button.h"

class UISave : public Button
{
public:
	UISave();

public:
	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void OnClick_Menu();
	void OnClick_Save();
	void OnClick_Load();

private:
	bool _isOnMenu = false;

	Button* _saveButton = nullptr;
	Button* _loadButton = nullptr;
};

