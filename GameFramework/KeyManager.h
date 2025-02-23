#pragma once
#include "SingletonBase.h"
#include <bitset>

#define KEYMAX 256

using namespace std;

class KeyManager final : public SingletonBase<KeyManager>
{
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;

	KeyManager() = default;
	virtual ~KeyManager() = default;

	friend class SingletonBase<KeyManager>;

public:
	HRESULT Init();
	void Release();

	// 키를 한 번 누름
	bool IsOnceKeyDown(int key);
	// 키를 눌렀다가 뗌
	bool IsOnceKeyUp(int key);
	// 키를 계속 누르고 있음
	bool IsStayKeyDown(int key);
	// 키가 토글됨 (Caps Lock)
	bool IsToggleKey(int key);

	bitset<KEYMAX> GetKeyUp() { return _keyUp; }
	bitset<KEYMAX> GetKeyDown() { return _keyDown; }

	void SetKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void SetKeyUp(int key, bool state) { _keyUp.set(key, state); }
};

