#include <tuple>
#include <array>
#include "Object.h"

enum class EN_STATE
{
	POS,
	SIZE,
	TYPE,
	ID,
	AIM,
	NUM,
	MOVEINFO,
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

//	0 : ���W, 1 : ����  2 : ���, 3 : ID, 4 : �ڕW�n�_, 5 : �G��ð��ق̈ʒu 6 : �ړ������̏��
using EnemyState = std::tuple<Vector2, Size, EN_TYPE, EN_ID, Vector2d, int, std::vector<int>>;

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
	void Curve();
	void Target();
	void Rotation();
	void Move();
	void Shot();

	void CurveUpdate();
	void TargetUpdate();
	void RotationUpdate();
	void MoveUpdate();
	void ShotUpdate();

	void Init(EN_TYPE type, EN_ID id);
	void CalRad(const Vector2d& sPos, const Vector2d& ePos);
	void MakeRotaInfo(const double& distance);		// ��]���邽�߂̏��𐶐����Ă���

	void (Enemy::*_updater)();

	Vector2 _rotDir;
	Vector2d _aimPos;		// �ڕW���W
	Vector2d _nextPos;
	Vector2d _rotCenter;	// ��]����Ƃ��̒��S�_

	std::vector<int> _curveID;			// �Ȃ���ID�̎w��
	std::vector<Vector2d> dbgPoint;
	std::array<Vector2, 4> _curveInfo;
	double _rotDistance;	// ��]���̋���
	double _rotAngle;		// ��]�p�̊p�x
	
	int _sigCnt;		// ���Ӳ�ފ֐��̒l
	int _sigRange;		// ���Ӳ�ފ֐��͈̔�

	const int _sigMax;
	const double _distance;
};

