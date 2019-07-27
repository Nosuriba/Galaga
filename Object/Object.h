#pragma once
#include <vector>
#include <memory>
#include <map>
#include "../Vector2.h"
#include "../Input.h"
#include "../DebugDisp.h"

// ��Ұ��݊Ǘ��p�̉ϒ��z��
using anim_vec = std::vector<std::pair<int, int>>;

// ð��ق̈ړ������߱
using mTbl_pair = std::pair<double, int>;

enum class ANIM
{
	NORMAL,		// �ʏ�
	DEATH,		// ���S
	EX,			// ����
	MAX
};

enum class Obj
{
	PLAYER,
	ENEMY,
	MAX
};

class Object
{
public:
	Object();
	virtual ~Object();
	virtual void Update() = 0;
	virtual void Draw();
	virtual const Obj GetObjID() const = 0;

	// �擪�ɓo�^���ꂽ�G�̱�Ұ��ݍX�V
	void LeadAnimUpdate();
	bool CheckMoveTbl() const;
	void SetMoveTbl(const mTbl_pair& tblInfo);
	int GetEnemyNum() const;

	bool GetDeath() const;
protected:
	// ��Ұ��݂̓o�^
	bool SetAnim(ANIM key, anim_vec& data);

	bool DestryCheck();

	void SetInvCnt(const int& leadCnt);
	void ResetInvCnt();

	// key�̏�Ԃ�ύX���Ă���
	bool animKey(const ANIM key);
	//// key�̏����擾���Ă���
	//const ANIM& animKey() const;

	Vector2d _pos;
	Vector2d _vel;				// �K�v�Ȃ��ꍇ�A��ŏ���
	Size _size;
	Rect _rect;
	double _rad;

	bool _tblFlag = false;
	bool _isAlive = true;		// true : ����, false : ���S
	bool _isDeath = false;		// true : �G�̍폜, false : ���S������

	int _enNum;					// �G�̔ԍ�
	
	// first : �ړ���(int�ɕύX����\������), second : �ړ����x
	static mTbl_pair _moveTblInfo;
	static int _leadCnt;
private:
	void AnimUpdate();
	
	// first : �摜ID, second : ��Ұ����ڰ�
	std::map<ANIM, anim_vec> _animMap;

	ANIM _animKey;
	int _invCnt = 0;
	int _animID = 0;

};

