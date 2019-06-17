#pragma once

#include "../Vector2.h"

class Object
{
public:
	Object();
	virtual ~Object();
	virtual void Draw() = 0;
	virtual void Update() = 0;
protected:
	int _imgHandle;
	const Vector2 charSize = Vector2(30, 32);
};

