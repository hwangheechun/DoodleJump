#include "stdafx.h"
#include "EventManager.h"
#include "IEvent.h"

void EventManager::Update()
{
	if (_eventQueue.size() == 0)
		return;

	// true 반환이라면 event 종료
	bool isEventEnd = _eventQueue[0]->EventUpdate();
	if (isEventEnd)
	{
		SAFE_DELETE(_eventQueue[0]);
		_eventQueue.erase(_eventQueue.begin());

		// 다음 예약되어 있는 이벤트가 있다면 실행
		if (_eventQueue.size() != 0)
			_eventQueue[0]->EventStart();
	}
}

void EventManager::AddEvent(IEvent* pEvent)
{
	// 현재 예약되어 있는 이벤트가 없다면, 새로 추가하려는 이벤트를 호출 후 추가
	if (_eventQueue.size() == 0) 
	{
		pEvent->EventStart();
	}
	_eventQueue.push_back(pEvent);
}
