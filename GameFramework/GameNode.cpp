#include "stdafx.h"
#include "GameNode.h"

GameNode::GameNode()
	: _managerInit(false)
{
}

HRESULT GameNode::Init()
{
	return S_OK;
}

HRESULT GameNode::Init(bool managerInit)
{
	_managerInit = managerInit;

	if (_managerInit)
	{
	//	SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->Init();
		TIMEMANAGER->Init();
		SOUNDMANAGER->Init();
		SCENEMANAGER->Init();
		TEXTDATA->Init();
	}

	return S_OK;
}

void GameNode::Release()
{
	if (_managerInit)
	{
	//	KillTimer(_hWnd, 1);
		KEYMANAGER->Release();
		TEXTDATA->Release();
		TIMEMANAGER->Release();
		SOUNDMANAGER->Release();
		SCENEMANAGER->Release();
		OBJECTMANAGER->Release();
	}
	
	ReleaseDC(_hWnd, _hdc);
}

void GameNode::Update()
{
	
}

void GameNode::Render()
{

}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//HWND - 핸들메시지
	//UINT - 메시지 발생 번호
	//WPARAM - 키보드 입력 및 마우스 클릭 메시지 전달
	//LPARAM - 마우스 좌표 전달
	
	/*
	PAINTSTRUCT ps;
	HDC			hdc;
	*/

	switch (iMessage)
	{
		case WM_MOUSEMOVE:
		{
			_ptMouse.x = static_cast<LONG>(LOWORD(lParam));
			_ptMouse.y = static_cast<LONG>(HIWORD(lParam));
			break;
		}
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_ESCAPE:
					PostQuitMessage(0);
				break;

			}
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
