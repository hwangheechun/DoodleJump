#pragma once
class Vector2 final
{
public:
	float x;
	float y;
public:
	explicit Vector2();
	explicit Vector2(const float& x, const float& y);
	explicit Vector2(const int& x, const int& y);
	explicit Vector2(const POINT& pt);

	const int GetIntX();
	const int GetIntY();
	const POINT GetPoint();

	Vector2 operator+ (const Vector2& v);
	Vector2 operator- (const Vector2& v);
	void operator+= (const Vector2& v);
	void operator-= (const Vector2& v);
	Vector2 operator* (const float& scalar);
	Vector2 operator/ (const float& scalar);
	const bool operator==(const Vector2& v);
	const bool operator!=(const Vector2& v);

public:
	// 정규화된 벡터
	static Vector2 Normalize(const Vector2* const  pVector2);
	// 해당 벡터를 라디안으로 변환한 값
	static float ToRadian(const Vector2* const pVector2);
	// 벡터의 크기
	static float Length(const Vector2* const pVector2);
	// 두 벡터의 내적 값
	static float Dot(const Vector2* const pVector2A, const Vector2* const pVector2B);
	// 두 벡터의 외적 값
	static float Cross(const Vector2* const pvector2A, const Vector2* const pVector2B);
};

