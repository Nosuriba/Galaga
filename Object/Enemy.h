#include <tuple>
#include "Object.h"

enum class EN_STATE
{
	POS,
	SIZE,
	TYPE,
	ID,
	AIM,
	NUM,
	MAX
};

/// �G�̎��
enum class EN_TYPE
{
	NORMAL,
	BONUS,
	BOSS,
	MAX
};

/// �G��ID
enum class EN_ID
{
	BEE,
	BUTTERFLY,
	SCORPION,
	MAX
};

//	0 : pos, 1 : size  2 : type, 3 : id, 4 : aimPos, 5 : num
using EnemyState = std::tuple<Vector2, Size, EN_TYPE, EN_ID, Vector2, int>;

class Enemy :
	public Object
{
public:
	Enemy();
	Enemy(const EnemyState& state);
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

	void Init(EN_TYPE type, EN_ID id);
	void CalAngle();			// �p�x�v�Z�p
	void (Enemy::*_updater)();

	Vector2 _aimPos;	// �ڕW���W
	Vector2 _midPos;	// ���ԍ��W

	int _midCnt;		// ���ԍ��W�܂ňړ����鎞��
};

