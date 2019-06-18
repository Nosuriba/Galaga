#pragma once

#include "../Vector2.h"
#include "../Input.h"

class Object
{
public:
	Object();
	virtual ~Object();
	virtual void Update(const Input& p) = 0;
	virtual void Draw() = 0;
	void Draw(int id);				/// 
protected:
	/*void Draw(int id);*/
	Vector2f _pos;
	Vector2f _vel;

	const Vector2 charSize = Vector2(30, 32);
};

