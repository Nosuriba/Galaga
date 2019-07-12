#include <tuple>
#include "Object.h"

enum class EN_STATE
{
	POS,
	TYPE,
	SIZE,
	AIM,
	MAX
};

enum class EN_TYPE
{
	NORMAL,
	BONUS,
	BOSS,
	MAX
};

// 0 : pos, 1 : type, 2 : aimPos
using EnemyState = std::tuple<Vector2, EN_TYPE, Size, Vector2>;

class Enemy :
	public Object
{
public:
	Enemy();
	Enemy(EnemyState state);
	~Enemy();
	
	void Update() override;
	void Draw() override;
	const Obj GetObjID() const override;
private:
	void MidMove();
	void Target();
	void Rotation();
	void Move();
	void Shot();

	void MidMoveUpdate();
	void TargetUpdate();
	void RotationUpdate();
	void MoveUpdate();
	void ShotUpdate();

	void Init(EN_TYPE type);
	void (Enemy::*_updater)();

	Vector2 _aimPos;	// �ڕW���W
	Vector2 _midPos;	// ���ԍ��W

	int _midCnt;		// ���ԍ��W�܂ňړ����鎞��		
};

