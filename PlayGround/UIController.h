#pragma once
#include "GameNode.h"
#include "UISave.h"

class UIController : public GameNode
{
public:
	UIController();

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

private:
	class UISave* _uiSave = nullptr;
};
