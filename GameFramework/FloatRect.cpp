#include "stdafx.h"
#include "FloatRect.h"

FloatRect::FloatRect()
	:left(0.f), top(0.f), right(0.f), bottom(0.f) {}

FloatRect::FloatRect(const float& left, const float& top, const float& right, const float& bottom)
	: left(left), top(top), right(right), bottom(bottom) {}

FloatRect::FloatRect(const int& left, const int& top, const int& right, const int& bottom)
	: left(static_cast<float>(left)), top(static_cast<float>(top)), right(static_cast<float>(right)), bottom(static_cast<float>(bottom)) {}

FloatRect::FloatRect(const Vector2& pos, const Vector2& size, const Pivot& pivot)
{
	*this = RectMakePivot(pos, size, pivot);
}

FloatRect::FloatRect(const RECT& rc)
	:left(static_cast<float>(rc.left)), top(static_cast<float>(rc.top)), right(static_cast<float>(rc.right)), bottom(static_cast<float>(rc.bottom)) {}

const RECT FloatRect::GetRect()
{
	return { static_cast<LONG>(left), static_cast<LONG>(top), static_cast<LONG>(right), static_cast<LONG>(bottom) };
}
float FloatRect::GetWidth()
{
	return right - left;
}
float FloatRect::GetHeight()
{
	return bottom - top;
}

Vector2 FloatRect::GetCenter()
{
	return Vector2(left + (right - left) / 2.f, top + (bottom - top) / 2.f);
}

Vector2 FloatRect::GetBottom()
{
	return Vector2(left + (right - left) / 2.f, bottom);
}

Vector2 FloatRect::GetSize()
{
	return Vector2((right - left), (bottom - top));
}

void FloatRect::Update(const Vector2& pos, const Vector2& size, const Pivot& pivot)
{
	*this = ::RectMakePivot(pos, size, pivot);
}

void FloatRect::Move(const Vector2& moveValue)
{
	left += moveValue.x;
	right += moveValue.x;
	top += moveValue.y;
	bottom += moveValue.y;
}

const FloatRect& ::FloatRect::operator=(const RECT& rc)
{
	this->left = static_cast<float>(rc.left);
	this->right = static_cast<float>(rc.right);
	this->top = static_cast<float>(rc.top);
	this->bottom = static_cast<float>(rc.bottom);
	return *this;
}

