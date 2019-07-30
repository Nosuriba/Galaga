#pragma once

#include <tuple>
#include <array>
#include <list>
#include "Object.h"
#include "../Common/ImageMng.h"
#include "../DebugConOut.h"

enum class EN_STATE
{
	POS,
	SIZE,
	TYPE,
	NUM,
	WAIT,
	AIM,
	SIGPOS,
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
	BOSS,
	MAX
};

// 0 : ���W, 1 : ���� 2 : ���, 3 : �G��ð��ق̈ʒu 4 : �ҋ@���� 5 : �ڕW�n�_ 6 : ���Ӳ�ނ̈ړ��n�_
using EnemyState = std::tuple<Vector2, Size, EN_TYPE, int, int, Vector2d, Vector2d>;

class Enemy :
	public Object
{
public:
	Enemy();
	virtual ~Enemy();
	
	virtual void Update() = 0;
	const Obj GetObjID() const override;

protected:
	/// �e�s���̏�����
	int Wait();
	int Sigmoid();
	int Target();
	int Rotation();
	int Move();

	/// �e�s���̍X�V
	int WaitUpdate();
	int SigmoidUpdate();
	int TargetUpdate();
	int RotationUpdate();
	int MoveUpdate();

	void SetSigAdd(const double& sigAdd);	// ���Ӳ�ނɉ��Z����l�̕ύX�p

	std::list<int(Enemy::*)()> _moveList;	// �ړ���Ԃ̕ۑ��p
	int (Enemy::*_updater)();

	/// protected�ɕK�v�̂Ȃ����̂́Aprivate�Ɉړ����Ă���
	Vector2d _aimPos;		// �ڕW���W
	Vector2d _sigBegin;		// ���Ӳ�ނ̎n�_
	Vector2d _sigEnd;		// ���Ӳ�ނ̏I�_
	Vector2d _sigRange;		// ���Ӳ�ނ̈ړ���

	Vector2 _rotDir;
	Vector2d _rotCenter;	// ��]����Ƃ��̒��S�_

	int _waitCnt;			// �G���ړ�����O�̑ҋ@����

	int _angle;
	int _rotAngle;			// ��_�����p�x

	double _sigCnt;			// ���Ӳ�ފ֐��̒l

	const double _sigMax;
	const double _distance;

	/// debug�p�œG���폜���Ă���(��ŕK�������I�I)
	static char now;
	static char old;
private:

	bool ChangeMove();			// �ړ���Ԃ̕ύX
	void CalRad(const Vector2d& sPos, const Vector2d& ePos, const double& angle);
	void MakeRotaInfo();		// ��]���邽�߂̏��𐶐����Ă���

	double _sigAdd;				// ���Ӳ�ނ̶��ĉ��Z�p
};

