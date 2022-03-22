#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <math.h> 

class Vector2f
{
public:
	float X;
	float Y;

	Vector2f()
	{
		X = 0.0f;
		Y = 0.0f;
	}

	Vector2f(float anX, float anY)
	{
		X = anX;
		Y = anY;
	}

	const Vector2f Vector2f::operator-(const Vector2f& other) const
	{
		Vector2f v(X - other.X, Y - other.Y);
		return v;
	}

	const Vector2f Vector2f::operator+(const Vector2f& other) const
	{
		Vector2f v(X + other.X, Y + other.Y);
		return v;
	}


	const Vector2f Vector2f::operator*(const Vector2f& other) const
	{
		Vector2f v(X * other.X, Y * other.Y);
		return v;
	}

	Vector2f& Vector2f::operator+=(const Vector2f& other)
	{
		X = X + other.X;
		Y = Y + other.Y;
		return *this;
	}

	Vector2f& Vector2f::operator*=(const float aFloat)
	{
		X *= aFloat;
		Y *= aFloat;
		return *this;
	}

	Vector2f& Vector2f::operator/=(const float aFloat)
	{
		X /= aFloat;
		Y /= aFloat;

		return *this;
	}

	const Vector2f Vector2f::operator*(const float aValue) const
	{
		Vector2f v(X * aValue, Y * aValue);
		return v;
	}

	float Vector2f::Length() const
	{
		return sqrtf(X * X + Y * Y);
	}

	void Vector2f::Normalize()
	{
		float length = Length();

		if (length > 0.0f)
			*this /= length;
	}
};

#endif // VECTOR2F_H