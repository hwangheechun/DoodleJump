#include "stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

GameNode* SceneManager::_currentScene = nullptr;

HRESULT SceneManager::Init()
{
	_currentScene = nullptr;

	return S_OK;
}

void SceneManager::Release()
{
	mapSceneIter miSceneList = _sceneList.begin();

	for (; miSceneList != _sceneList.end();)
	{
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->Release();
			SAFE_DELETE(miSceneList->second);
			miSceneList = _sceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}

	_sceneList.clear();
}

void SceneManager::Update()
{
	if (_currentScene) 
		_currentScene->Update();
}

void SceneManager::Render()
{
	if (_currentScene) 
		_currentScene->Render();
}

GameNode * SceneManager::AddScene(const wstring& sceneName, GameNode* scene)
{
	if (!scene) 
		return nullptr;

	_sceneList.insert(make_pair(sceneName, scene));

	return scene;
}

HRESULT SceneManager::ChangeScene(const wstring& sceneName)
{
	mapSceneIter find = _sceneList.find(sceneName);

	if (find == _sceneList.end()) 
		return E_FAIL;

	if (find->second == _currentScene) 
		return S_OK;

	if (SUCCEEDED(find->second->Init()))
	{
		// 어떤 Scene의 정보가 들어 있기 때문에 릴리즈 먼저 해 주고
		if (_currentScene) 
			_currentScene->Release();

		// 현재 Scene에 바꾸려는 Scene을 담는다
		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}
