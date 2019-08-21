#pragma once

#include <tuple>
#include <array>
#include <list>
#include "Object.h"
#include "../Common/ImageMng.h"
#include "../DebugConOut.h"
#include "../Game.h"

enum class EN_STATE
{
	POS,
	SIZE,
	TYPE,
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

// 0 : ���W, 1 : ���� 2 : ���, 3 : �ҋ@���� 4 : ���Ӳ�ނ̏I�_, 5 : �ڕW�n�_
using EnemyState = std::tuple<Vector2, Size, EN_TYPE, int, Vector2d, Vector2d>;

class Enemy :
	public Object
{
public:
	Enemy();
	virtual ~Enemy();
	void Update(const std::unique_ptr<InputState>& p);

	/// �֐��߲���̱��ڽ���擾���邽�߁Apublic�Ɉړ�����
	int Sigmoid();
	int Rotation();
	virtual int Target();
	int TargetUpdate();

	const OBJ GetObjID() const override;
	virtual void SetSigEnd(const Vector2d& sigEnd) override = 0;

protected:
	/// �e�s���̏�����
	int Wait();
	int Move();
	int Scaling();

	/// �e�s���̍X�V
	int WaitUpdate();
	virtual int SigmoidUpdate();
	int RotationUpdate();
	int ScalingUpdate();						
	int MoveUpdate();

	void CalRad(const Vector2d& sPos, const Vector2d& ePos, const double& angle);

	std::list<int(Enemy::*)()> _moveList;	// �ړ���Ԃ̕ۑ��p
	int (Enemy::*_updater)();

	Vector2d _aimPos;		// �ڕW���W
	Vector2d _sigRange;		

	/// �g�k�̈ړ��Ŏg�p�������
	Vector2d _spLength;		
	Vector2d _spDistance;	

	int _waitTime;			// �G���ړ�����O�̑ҋ@����
	int _shotWait;

	bool _isAction;

	double _sigAdd;			// ���Ӳ�ނ̶��ĉ��Z�p
	double _gain;			
	double _spMag;			
	double _spVel;			

	static int _actionCnt;		
private:
	bool ChangeMove();

	void MakeRotaInfo();		

	Vector2  _rotDir;
	Vector2d _rotCenter;	

	int _angle;
	int _rotAngle;			// ��]�����p�x

	double _sigCnt;			
	const double _sigMax;
	const double _distance;
};

