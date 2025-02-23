#include "stdafx.h"
#include "Obstacle.h"

void Obstacle::Init()
{
	mName = "Obstacle";
	mPosition = Vector2(WINSIZEX / 2 - 100, WINSIZEY / 2 - 100);
	mSize = Vector2(300, 50);
	mRect = RectMakePivot(mPosition, mSize, Pivot::Center);
	mActive = true;
}

void Obstacle::Release()
{
}

void Obstacle::Update()
{
}

void Obstacle::Render()
{
	D2DRenderer::GetInstance()->DrawRectangle(mRect, D2DRenderer::DefaultBrush::Green, 1.0f);
}
