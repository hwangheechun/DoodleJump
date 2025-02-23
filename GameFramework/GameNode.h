#pragma once
#include "Image.h"

class GameNode
{
private:
	bool _managerInit;

public:
	GameNode();
	virtual ~GameNode() = default;

	virtual HRESULT Init();
	virtual HRESULT Init(bool managerInit);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

