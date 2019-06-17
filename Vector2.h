#pragma once

class Vector2
{
public:
	int x, y;

	Vector2() : x(0), y(0){};
	Vector2(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	~Vector2();

	// ‘ã“ü‰‰Zq
	Vector2& operator=(const Vector2& vec);

	// “Y‚¦š‰‰Zq
	int operator[](int j);

	// ”äŠr‰‰Zq
	bool operator==(const Vector2& vec) const;
	bool operator!=(const Vector2& vec) const;
	bool operator<=(const Vector2& vec) const;
	bool operator<(const Vector2& vec) const;
	bool operator>=(const Vector2& vec) const;
	bool operator>(const Vector2& vec) const;

	// ’P€‰‰Zq
	Vector2& operator+=(const Vector2& vec);
	Vector2& operator-=(const Vector2& vec);
	Vector2& operator*=(const Vector2& vec);
	Vector2& operator*=(int k);
	Vector2& operator/=(const Vector2& vec);
	Vector2& operator/=(int k);
	Vector2 operator+() const;
	Vector2 operator-() const;
};

// Vector2 + Vector2
Vector2 operator+(const Vector2& vec1, const Vector2& vec2);
// Vector2 + int
Vector2 operator+(const Vector2& vec1, const int& i);
// Vector2 - Vector2
Vector2 operator-(const Vector2& vec1, const Vector2& vec2);
// Vector2 * Vector2
Vector2 operator*(const Vector2& vec1, const Vector2& vec2);
// Vector2 * int
Vector2 operator*(const Vector2& vec1, const int& k);
// int * Vector2
Vector2 operator*(const int& k, const Vector2& vec1);
// Vector2 / Vector2
Vector2 operator/(const Vector2& vec1, const Vector2& vec2);
// Vector2 / int
Vector2 operator/(const Vector2& vec1, const int& k);

struct Rect
{
	Vector2 center;
	Vector2 size;
	Rect() : center(0, 0), size(0, 0) {};
	Rect(Vector2 & p, Vector2 & s)
	{
		center = p;
		size = s;
	}

	const int Left() const;
	const int Right() const;
	const int Top() const;
	const int Bottom() const;
	const int Width() const;
	const int Height() const;
};

