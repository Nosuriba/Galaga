#include "Object.h"

class Enemy :
	public Object
{
public:
	Enemy();
	Enemy(const Vector2f & pos, const Vector2f & vel);
	~Enemy();

	void Update(const Input& p);
	void Draw();
	
private:
};

