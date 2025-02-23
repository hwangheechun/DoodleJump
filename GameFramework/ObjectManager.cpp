#include "stdafx.h"
#include "ObjectManager.h"
#include "GameObject.h"

ObjectManager::ObjectManager()
{
	for (int i = 0; i < (int)ObjectType::End; ++i)
	{
		_objectContainer.insert(make_pair(static_cast<ObjectType>(i), vector<GameObject*>()));
	}
}

void ObjectManager::Release()
{
	ObjectContainerIter iter = _objectContainer.begin();
	for (; iter != _objectContainer.end(); ++iter)
	{
		vector<GameObject*>& objectList = iter->second;
		for (int i = 0; i < objectList.size(); ++i)
		{
			objectList[i]->Release();
			SAFE_DELETE(objectList[i]);
		}
	}

	_objectContainer.clear();
}

void ObjectManager::Update()
{
	ObjectContainerIter iter = _objectContainer.begin();
	for (; iter != _objectContainer.end(); ++iter)
	{
		vector<GameObject*>& objectList = iter->second;
		for (int i = 0; i < objectList.size(); ++i)
		{
			if (objectList[i]->GetActive())
				objectList[i]->Update();
		}
	}
}

void ObjectManager::Render()
{
	ObjectContainerIter iter = _objectContainer.begin();
	for (; iter != _objectContainer.end(); ++iter)
	{
		vector<GameObject*>& objectList = iter->second;
		for (int i = 0; i < objectList.size(); ++i)
		{
			if (objectList[i]->GetActive())
				objectList[i]->Render();
		}
	}
}

void ObjectManager::AddObject(ObjectType objectType, GameObject * newObject)
{
	// map, unordered_map은 해당 키값의 데이터가 없으면 새로 생성함
	_objectContainer[objectType].push_back(newObject);
}

void ObjectManager::RemoveObject(ObjectType objectType, GameObject * deleteObject)
{
	vector<GameObject*> objectList = _objectContainer[objectType];
	for (int i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i] == deleteObject)
		{
			objectList[i]->Release();
			SAFE_DELETE(objectList[i]);
			objectList.erase(objectList.begin() + i);
			return;
		}
	}
}

GameObject * ObjectManager::FindObject(ObjectType objectType, wstring objectName)
{
	vector<GameObject*>& objectList = _objectContainer[objectType];
	for (int i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i]->GetName() == objectName)
		{
			return objectList[i];
		}
	}
	return nullptr;	// 못 찾음
}

// 같은 이름을 가진 오브젝트 전부 찾아서 벡터로 반환
vector<class GameObject*> ObjectManager::FindObjects(ObjectType objectType, wstring objectName)
{
	vector<GameObject*> result;
	vector<GameObject*>& objectList = _objectContainer[objectType];
	for (int i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i]->GetName() == objectName)
		{
			result.push_back(objectList[i]);
		}
	}
	return result;
}

vector<class GameObject*>& ObjectManager::GetObjectList(ObjectType objectType)
{
	return _objectContainer[objectType];
}

