#pragma once
#include <unordered_map>

enum class ObjectType : int
{
	TileObject, Doodle, Platform, Block, Enemy, Player, Bullet, Item, UI, End
};

// 게임 오브젝트 관리 클래스
class ObjectManager final : public SingletonBase<ObjectManager>
{
private:
	// Tile - vector<오브젝트>
	// Enemy - vector<오브젝트>
	// Player - vector
	unordered_map<ObjectType, vector<class GameObject*>> _objectContainer;
	typedef unordered_map<ObjectType, vector<class GameObject*>>::iterator ObjectContainerIter;

protected:
	ObjectManager();
	virtual ~ObjectManager() = default;

	friend class SingletonBase<ObjectManager>;

public:
	void Release();
	void Update();
	void Render();

	void AddObject(ObjectType objectType, class GameObject* newObject);
	void RemoveObject(ObjectType objectType, class GameObject* deleteObject);

	class GameObject* FindObject(ObjectType objectType, wstring objectName);
	vector<class GameObject*> FindObjects(ObjectType objectType, wstring objectName);
	vector<class GameObject*>& GetObjectList(ObjectType objectType);
};

