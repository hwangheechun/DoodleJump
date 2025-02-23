#pragma once
// 인터페이스: 순수 가상 함수만 가지고 있는 부모 클래스
// 정의는 부모가, 구현은 자식이
class IEvent
{
public:
	// 이벤트가 시작할 때 실행할 함수
	virtual void EventStart() = 0;
	// 이벤트 업데이트
	virtual bool EventUpdate() = 0;
};

class IObjectMove final : public IEvent
{
	class GameObject* _targetObject;
	Vector2 _targetLocation;
	float _speed;

public:
	IObjectMove(GameObject* targetObject, Vector2 targetLocation, float speed);

	void EventStart() override;
	bool EventUpdate() override;
};

class IWaitForSecond : IEvent
{
	int _count;

public:
	IWaitForSecond(int count);

	void EventStart() override;
	bool EventUpdate() override;
};
