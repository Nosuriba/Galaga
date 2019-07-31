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
	SIGPOS,
	AIM,
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

// 0 : ���W, 1 : ���� 2 : ���, 3 : �G��ð��ق̈ʒu 4 : �ҋ@���� 5 : ���Ӳ�ނ̏I�_, 6 : �ڕW�n�_
using EnemyState = std::tuple<Vector2, Size, EN_TYPE, int, int, Vector2d, Vector2d>;

class Enemy :
	public Object
{
public:
	Enemy();
	virtual ~Enemy();
	virtual void Update() = 0;

	/// �֐��߲���̱��ڽ���擾���邽�߁Apublic�Ɉړ�����
	int Sigmoid();
	int Rotation();
	int Target();

	//static void SetTarget(const Vector2d& sigEnd);

	const OBJ GetObjID() const override;
	virtual void SetMoveInfo(const Vector2d& sigEnd) override = 0;

protected:
	/// �e�s���̏�����
	int Wait();
	int Move();

	/// �e�s���̍X�V
	int WaitUpdate();
	int SigmoidUpdate();
	int RotationUpdate();
	int TargetUpdate();
	virtual int MoveUpdate() = 0;

	void SetSigAdd(const double& sigAdd);	// ���Ӳ�ނɉ��Z����l�̕ύX�p

	std::list<int(Enemy::*)()> _moveList;	// �ړ���Ԃ̕ۑ��p
	int (Enemy::*_updater)();

	/// protected�ɕK�v�̂Ȃ����̂́Aprivate�Ɉړ����Ă���
	Vector2d _aimPos;		// �ڕW���W
	Vector2d _sigRange;		// ���Ӳ�ނ̈ړ���

	int _waitTime;			// �G���ړ�����O�̑ҋ@����
	int _waitAction;		// �G���s������܂ł̑ҋ@����

	double _sigAdd;			// ���Ӳ�ނ̶��ĉ��Z�p
	double _gain;			// ���Ӳ�ނ̸��̐���p

	static int _actionCnt;		// �s�����̓G�̐�

	/// debug�p�œG���폜���Ă���(��ŕK�������I�I)
	static char now;
	static char old;
private:
	bool ChangeMove();			// �ړ���Ԃ̕ύX
	void CalRad(const Vector2d& sPos, const Vector2d& ePos, const double& angle);
	void MakeRotaInfo();		// ��]���邽�߂̏��𐶐����Ă���

	Vector2  _rotDir;
	Vector2d _rotCenter;	// ��]����Ƃ��̒��S�_

	int _angle;
	int _rotAngle;			// ��]�����p�x

	double _sigCnt;			// ���Ӳ�ނ̒l
	const double _sigMax;
	const double _distance;

	
};

