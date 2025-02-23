#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN		// 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일#include <Windows.h>

// C 런타임 헤더 파일입니다.
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>

#include <vector>
#include <map>

enum class Pivot : int
{
	LeftTop, Center, Bottom
};

#include "LibraryHeader.h"
#include "Vector2.h"
#include "FloatRect.h"

#include "RandomFunction.h"
#include "KeyManager.h"
#include "Utils.h"
#include "D2DRenderer.h"
#include "ImageManager.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "TextData.h"
#include "ObjectManager.h"
#include "StringHelper.h"
#include "Camera.h"

using namespace UTIL;

// 여기서 프로그램에 필요한 추가 헤더를 참조합니다.
#define WINNAME (LPCTSTR)(TEXT("D2D-Framework"))
#define WINSTARTX	200
#define WINSTARTY	50
#define WINSIZEX	512		
#define WINSIZEY	1024
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#define RANDOM RandomFunction::GetInstance()
#define KEYMANAGER KeyManager::GetInstance()
#define IMAGEMANAGER ImageManager::GetInstance()
#define TIMEMANAGER TimeManager::GetInstance()
#define SOUNDMANAGER SoundManager::GetInstance()
#define SCENEMANAGER SceneManager::GetInstance()
#define TEXTDATA TextData::GetInstance()
#define OBJECTMANAGER ObjectManager::GetInstance()
#define CAMERA Camera::GetInstance()

#define SAFE_DELETE(p)		{if(p) {delete(p); (p) = nullptr;}}
#define SAFE_RELEASE(p)		{if(p) {(p)->Release(); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[](p); (p) = nullptr;}}

#define ASSERT_NO_EXIT(condition, message)                    \
    do {                                                      \
        if (!(condition)) {                                   \
            std::cerr << "Assertion failed: "                 \
                      << #condition << ", message: "          \
                      << message << ", file: "                \
                      << __FILE__ << ", line: "               \
                      << __LINE__ << std::endl;               \
        }                                                     \
    } while (false)

#define Property(ValueType, ValueName, FuncName) \
protected: ValueType ValueName; \
public: \
	inline ValueType Get##FuncName() const { return ValueName; } \
	inline void Set##FuncName(const ValueType& value) { ValueName = value; }

extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;
extern HDC			_hdc;