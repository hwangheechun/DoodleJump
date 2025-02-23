#include "stdafx.h"
#include "KeyManager.h"

HRESULT KeyManager::Init()
{
	for (int i = 0; i < KEYMAX; i++)
	{
		this->GetKeyUp().set(i, false);
	}

	return S_OK;
}

void KeyManager::Release()
{
}

bool KeyManager::IsOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->GetKeyDown()[key])
		{
			this->SetKeyDown(key, true);

			return true;
		}
	}
	else 
		this->SetKeyDown(key, false);

	return false;
}

bool KeyManager::IsOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) 
		this->SetKeyUp(key, true);
	else
	{
		if (this->GetKeyUp()[key])
		{
			this->SetKeyUp(key, false);

			return true;
		}
	}

	return false;
}

bool KeyManager::IsStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) 
		return true;

	return false;
}

bool KeyManager::IsToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) 
		return true;

	return false;
}
