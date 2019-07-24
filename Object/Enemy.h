#pragma once

#include <tuple>
#include <array>
#include "Object.h"
#include "../Common/ImageMng.h"
#include "../DebugConOut.h"

enum class EN_STATE
{
	POS,
	SIZE,
	TYPE,
	NUM,
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
	SCORPION,
	MAX
};

// 0 : ���W, 1 : ���� 2 : ���, 3 : �G��ð��ق̈ʒu 4 : �ڕW�n�_ 5 : ���Ӳ�ނ̈ړ��n�_
using EnemyState = std::tuple<Vector2, Size, EN_TYPE, int, Vector2d, Vector2d>;

class Enemy :
	public Object
{
public:
	Enemy();
	virtual ~Enemy();
	
	void Update() override;
	void Draw() override;
	const Obj GetObjID() const override;

protected:
	//// �K�v�̂Ȃ��@�\�͂��ׂāAprivate�������͍폜����
	void Sigmoid();
	void Target();
	void Rotation();
	void Move();
	void Shot();

	void SigmoidUpdate();
	void TargetUpdate();
	void RotationUpdate();
	void MoveUpdate();
	void ShotUpdate();

	/// protected�ɕK�v�̂Ȃ����̂́Aprivate�Ɉړ����Ă���
	Vector2 _rotDir;
	Vector2d _aimPos;		// �ڕW���W
	Vector2d _sPos;			// ���Ӳ�ނ̽��Ēn�_
	Vector2d _ePos;			// ���Ӳ�ނ̺ްْn�_
	Vector2d _rotCenter;	// ��]����Ƃ��̒��S�_

	double _rotDistance;	// ��]���̋���
	double _rotAngle;		// ��]�p�̊p�x

	double _sigCnt;		// ���Ӳ�ފ֐��̒l

	const double _sigMax;
	const double _distance;
private:
	
	void Init(EN_TYPE type, EN_ID id);
	void CalRad(const Vector2d& sPos, const Vector2d& ePos, const double& angle);
	void MakeRotaInfo(const double& distance);		// ��]���邽�߂̏��𐶐����Ă���

	void (Enemy::*_updater)();

};

