#include "stdafx.h"
#include "iEvent.h"
#include "GameObject.h"

IObjectMove::IObjectMove(GameObject * targetObject, Vector2 targetLocation, float speed)
{
	_targetObject = targetObject;
	_targetLocation = targetLocation;
	_speed = speed;
}

void IObjectMove::EventStart()
{
}

bool IObjectMove::EventUpdate()
{
	Vector2 position = _targetObject->GetPosition();
	float angle = GetAngle(position.x, position.y, _targetLocation.x, _targetLocation.y);
	
	position.x += cosf(angle) * _speed * TIMEMANAGER->GetElapsedTime();
	position.y -= sinf(angle) * _speed * TIMEMANAGER->GetElapsedTime();

	_targetObject->SetPosition(position);
	_targetObject->SetRect(FloatRect(position, _targetObject->GetSize(), Pivot::Center));

	if (GetDistance(position.x, position.y, _targetLocation.x, _targetLocation.y) < 3)
	{
		_targetObject->SetPosition(_targetLocation);
		return true;
	}

	return false;
}

IWaitForSecond::IWaitForSecond(int count)
{
	_count = count;
}

void IWaitForSecond::EventStart()
{
}

bool IWaitForSecond::EventUpdate()
{
	return false;
}
