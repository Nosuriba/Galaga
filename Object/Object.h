#pragma once
#include <vector>
#include <array>
#include <memory>
#include <map>
#include "../Vector2.h"
#include "../Input.h"
#include "../DebugDisp.h"

class Shot;

// ��Ұ��݊Ǘ��p�̉ϒ��z��
using anim_vec = std::vector<std::pair<int, int>>;

// �G�z�u�pð��ق̈ړ����
using enTbl_pair = std::pair<int, int>;

enum class ANIM
{
	NORMAL,		// �ʏ�
	DEATH,		// ���S
	EX,			// ����
	MAX
};

enum class OBJ
{
	PLAYER,
	ENEMY,
	MAX
};

struct ShotInfo
{
	Vector2d _pos;
	Vector2d _vel;
	Size _size;
	Rect _rect;

	bool flag;

	ShotInfo() : _pos(0, 0), _vel(0, 0), _size(0, 0) {};
	ShotInfo(const Vector2d& pos, const Vector2d& vel, const Size& size)
	{
		_pos = pos;
		_vel = vel;
		_size = size;
	}
};

using shared_shot = std::shared_ptr<Shot>;

class Object
{
public:
	Object();
	virtual ~Object();
	virtual void Update() = 0;
	void Draw();
	virtual const OBJ GetObjID() const = 0;

	// �擪�ɓo�^���ꂽ�G�̱�Ұ��ݍX�V
	void LeadAnimUpdate();
	bool CheckMoveTbl() const;
	void SetMoveTbl(const enTbl_pair& tblInfo);
	int GetEnemyNum() const;

	bool GetDeath() const;

	void SetSigEnd(const Vector2d& sigEnd);
	const Vector2d& GetPos() const;
protected:
	// ��Ұ��݂̓o�^
	bool SetAnim(ANIM key, anim_vec& data);

	bool DestryCheck();

	void SetInvCnt(const int& leadCnt);
	void ResetInvCnt();						// ���S���ɱ�Ұ��݂�ؾ�Ă��邽�߂̂���

	// key�̏�Ԃ�ύX���Ă���
	bool animKey(const ANIM key);
	//// key�̏����擾���Ă���
	//const ANIM& animKey() const;

	// std::array<shared_shot, 2> _shots;

	Vector2d _sigBegin;		// ���Ӳ�ނ̎n�_
	Vector2d _sigEnd;		// ���Ӳ�ނ̏I�_

	Vector2d _pos;
	Vector2d _vel;
	Size _size;
	Rect _rect;
	double _rad;			// �摜�̌���(׼ޱ�)

	bool _isTable = false;		// true : ð��قɔz�u���ꂽ, false : ð��قɔz�u����Ă��Ȃ�
	bool _isAlive = true;		// true : ����, false : ���S
	bool _isDeath = false;		// true : ���S, false : ���S������

	int _enNum;					// �G�̔ԍ�
	
	// first : �ړ���, second : �ړ����x
	static enTbl_pair _moveTblInfo;
	static int _leadCnt;
	void AnimUpdate(const int& animSpeed);
private:
	// void AnimUpdate();
	
	// first : �摜ID, second : ��Ұ����ڰ�
	std::map<ANIM, anim_vec> _animMap;

	ANIM _animKey;
	int _invCnt = 0;
	int _animID = 0;

};

