#include "Object.h"

class Enemy :
	public Object
{
public:
	Enemy();
	~Enemy();

	void Draw();
	void Update();
private:
};

