#pragma once

/// template<class T>�̌`�ɒ����Ă���
//template <class T>
/// ����ڰČ^���g�������������Ă���
template <class T>
class Vector2D
{
public:
	T x, y;

	Vector2D() : x(0), y(0) {};
	Vector2D(T x, T y)
	{
		this->x = x;
		this->y = y;
	}
	~Vector2D(){};

	// ������Z�q
	Vector2D& operator=(const Vector2D& vec)
	{
		x = vec.x;
		y = vec.y;

		return *this;
	}

	// �Y�������Z�q
	int operator[](int j)
	{
		if		(j == 0){ return x;}
		else if (j == 1){ return y;}
		else			{ return x; }
	}

	/// ��r���Z�q
	bool operator==(const Vector2D& vec) const
	{
		return ((x == vec.x) && (y == vec.y));
	}
	bool operator!=(const Vector2D& vec) const
	{
		return !((x == vec.x) && (y == vec.y));
	}
	bool operator<=(const Vector2D& vec) const
	{
		return ((x <= vec.x) && (y <= vec.y));
	}
	bool operator<(const Vector2D& vec) const
	{
		return ((x < vec.x) && (y < vec.y));
	}
	bool operator>=(const Vector2D & vec) const
	{
		return ((x >= vec.x) && (y >= vec.y));
	}
	bool operator>(const Vector2D & vec) const
	{
		return ((x > vec.x) && (y > vec.y));
	}

	// Vector2D���m�̉��Z
	Vector2D<T> & operator+=(const Vector2D & vec)
	{
		x += vec.x;
		y += vec.y;

		return *this;
	}
	// Vector2D���m�̌��Z
	Vector2D<T> & operator-=(const Vector2D & vec)
	{
		x -= vec.x;
		y -= vec.y;

		return *this;
	}
	// Vector2D���m�̏�Z
	Vector2D<T> & operator*=(const Vector2D & vec)
	{
		x *= vec.x;
		y *= vec.y;

		return *this;
	}
	// Vector2D������ڰČ^�̏�Z
	Vector2D<T> & operator*=(T k)
	{
		x *= k;
		y *= k;

		return *this;
	}
	// Vector2D���m�̏��Z
	Vector2D<T> & operator/=(const Vector2D & vec)
	{
		x /= vec.x;
		y /= vec.y;

		return *this;
	}
	// Vector2D������ڰČ^�̏��Z
	Vector2D<T> & operator/=(T k)
	{
		x /= k;
		y /= k;

		return *this;
	}
	Vector2D<T> operator+() const
	{
		return *this;
	}
	Vector2D<T> operator-() const
	{
		return Vector2D<T>(-this->x, -this->y);
	}
};
// Vector2D���m�̉��Z
template <class T>
Vector2D<T> operator+(const Vector2D<T> & vec1, const Vector2D<T> & vec2)
{
	return Vector2D<T>(vec1.x + vec2.x, vec1.y + vec2.y);
}

// Vector2D������ڰČ^�̉��Z
template <class T>
Vector2D<T> operator+(const Vector2D<T> & vec1, const T& i)
{
	return Vector2D<T>(vec1.x + i, vec1.y + i);
}
// Vector2D���m�̌��Z
template <class T>
Vector2D<T> operator-(const Vector2D<T> & vec1, const Vector2D<T> & vec2)
{
	return Vector2D<T>(vec1.x - vec2.x, vec1.y - vec2.y);
}
// Vector2D���m�̏�Z
template <class T>
Vector2D<T> operator*(const Vector2D<T> & vec1, const Vector2D<T> & vec2)
{
	return Vector2D<T>(vec1.x * vec2.x, vec1.y * vec2.y);
}
// Vector2D������ڰČ^�̏�Z
template <class T>
Vector2D<T> operator*(const Vector2D<T>& vec, const T & k)
{
	return Vector2D<T>(vec.x * k, vec.y * k);
}
// Vector2D���m�̏��Z
template <class T>
Vector2D<T> operator/(const Vector2D<T> & vec1, const Vector2D<T> & vec2)
{
	 return Vector2D<T>(vec1.x / vec2.x, vec1.y / vec2.y);
}

// Vector2D������ڰČ^�̏��Z
template <class T>
Vector2D<T> operator/(const Vector2D<T>& vec, const T & k)
{
	return Vector2D<T>(vec.x / k, vec.y / k);
}

using Vector2  = Vector2D<int>;
using Vector2f = Vector2D<float>;
using Vector2d = Vector2D<double>;

struct Size
{
	int height, width;
	Size() {};
	Size(int w, int h)
	{
		width = w;
		height = h;
	}
	
};

struct Rect
{
	Vector2 center;
	Size size;
	Rect() : center(0, 0), size(0, 0) {};
	Rect(Vector2 & p, Size & s)
	{
		center = p;
		size = s;
	}

	const int Left() const;
	const int Right() const;
	const int Top() const;
	const int Bottom() const;
};
