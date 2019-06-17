#include "Vector2.h"

Vector2::~Vector2()
{
}

Vector2 & Vector2::operator=(const Vector2 & vec)
{
	x = vec.x;
	y = vec.y;

	return *this;
}

int Vector2::operator[](int j)
{
	if (j == 0)
	{
		return x;
	}
	else if (j == 1)
	{
		return y;
	}
	else
	{
		return x;
	}
}

bool Vector2::operator==(const Vector2 & vec) const
{
	return ((x == vec.x) && (y == vec.y));
}

bool Vector2::operator!=(const Vector2 & vec) const
{
	return !((x == vec.x) && (y == vec.y));
}

bool Vector2::operator<=(const Vector2 & vec) const
{
	return ((x <= vec.x) && (y <= vec.y));
}

bool Vector2::operator<(const Vector2 & vec) const
{
	return ((x < vec.x) && (y < vec.y));
}

bool Vector2::operator>=(const Vector2 & vec) const
{
	return ((x >= vec.x) && (y >= vec.y));
}

bool Vector2::operator>(const Vector2 & vec) const
{
	return ((x > vec.x) && (y > vec.y));
}

Vector2 & Vector2::operator+=(const Vector2 & vec)
{
	x += vec.x;
	y += vec.y;

	return *this;
}

Vector2 & Vector2::operator-=(const Vector2 & vec)
{
	x -= vec.x;
	y -= vec.y;

	return *this;
}

Vector2 & Vector2::operator*=(const Vector2 & vec)
{
	x *= vec.x;
	y *= vec.y;

	return *this;
}

Vector2 & Vector2::operator*=(int k)
{
	x *= k;
	y *= k;

	return *this;
}

Vector2 & Vector2::operator/=(const Vector2 & vec)
{
	x /= vec.x;
	y /= vec.y;

	return *this;
}

Vector2 & Vector2::operator/=(int k)
{
	x /= k;
	y /= k;

	return *this;
}

Vector2 Vector2::operator+() const
{

	return *this;
}

Vector2 Vector2::operator-() const
{
	return Vector2(-this->x, -this->y) ;
}

Vector2 operator+(const Vector2 & vec1, const Vector2 & vec2)
{
	return Vector2(vec1.x + vec2.x, vec1.y + vec2.y);
}

Vector2 operator+(const Vector2 & vec1, const int& i)
{
	return Vector2(vec1.x + i, vec1.y + i);
}

Vector2 operator-(const Vector2 & vec1, const Vector2 & vec2)
{
	return Vector2(vec1.x - vec2.x, vec1.y - vec2.y);
}

Vector2 operator*(const Vector2 & vec1, const Vector2 & vec2)
{
	return Vector2(vec1.x * vec2.x, vec1.y * vec2.y);
}

Vector2 operator*(const Vector2 & vec, const int& k)
{
	return Vector2(vec.x * k, vec.y * k);
}

Vector2 operator*(const int& k, const Vector2 & vec)
{
	return Vector2(k * vec.x, k * vec.y);
}

Vector2 operator/(const Vector2 & vec1, const Vector2 & vec2)
{
	return Vector2(vec1.x / vec2.x, vec1.y / vec2.y);
}

Vector2 operator/(const Vector2 & vec, const int& k)
{
	return Vector2(vec.x / k, vec.y / k);
}

/// ãÈå`ÇÃê›íË
const int Rect::Left() const
{
	return center.x - (size.x / 2);
}

const int Rect::Right() const
{
	return center.x + (size.x / 2);
}

const int Rect::Top() const
{
	return center.y - (size.y / 2);
}

const int Rect::Bottom() const
{
	return center.y + (size.y / 2);
}

const int Rect::Width() const
{
	return size.x;
}

const int Rect::Height() const
{
	return size.y;
}
