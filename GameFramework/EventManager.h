#pragma once
#include <vector>

class EventManager final : public SingletonBase<EventManager>
{
private:
	EventManager() = default;
	virtual ~EventManager() = default;

	friend class SingletonBase<EventManager>;

public:
	vector<class IEvent*> _eventQueue;

	void Update();
	void AddEvent(class IEvent* pEvent);
};

