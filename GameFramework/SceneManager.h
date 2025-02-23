#pragma once
#include "SingletonBase.h"
#include <map>

class GameNode;

class SceneManager final : public SingletonBase<SceneManager>
{
public:
	typedef map<wstring, GameNode*>			 mapSceneList;
	typedef map<wstring, GameNode*>::iterator mapSceneIter;

private:
	static GameNode* _currentScene;
	mapSceneList _sceneList;

protected:
	SceneManager() = default;
	virtual ~SceneManager() = default;

	friend class SingletonBase<SceneManager>;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render();

	GameNode* AddScene(const wstring& sceneName, GameNode* scene);

	HRESULT ChangeScene(const wstring& sceneName);
};

