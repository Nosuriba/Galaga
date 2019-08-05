#pragma once
#include <vector>
#include <array>
#include <memory>
#include <map>
#include "../Vector2.h"
#include "../Input.h"
#include "../DebugDisp.h"

class Shot;

enum class ANIM
{
	NORMAL,		// �ʏ�
	DEATH,		// ���S
	EX,			// ����
	MAX
};

enum class OBJ
{
	ENEMY,
	PLAYER,
	MAX
};

// ��Ұ��݊Ǘ��p�̉ϒ��z��
using anim_vec = std::vector<std::pair<int, int>>;
// �G�z�u�pð��ق̈ړ����
using enTbl_pair = std::pair<int, int>;

using shared_shot = std::shared_ptr<Shot>;
// shared_ptr�̌Œ蒷�z��
using shot_array  = std::array<shared_shot, 2>;

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
	bool IsMoveTbl() const;
	void SetTblInfo(const enTbl_pair& tblInfo);

	Rect GetRect() const;
	shot_array GetShot() const;
	void ShotDelete(const shared_shot& shot);

	//	�G�̈ړ������p���̌p����Őݒ肵�Ă���
	virtual void SetSigEnd(const Vector2d& sigEnd);

	bool IsAlive() const;
	void ChangeAlive();			// ���S��ԂɕύX����
	bool GetDeath() const;

	const Vector2d& GetPos() const;
protected:
	// ��Ұ��݂̓o�^
	bool SetAnim(ANIM key, anim_vec& data);

	bool DestryCheck();

	void SetInvCnt(const int& leadCnt);
	void ResetAnim();						// ���S���ɱ�Ұ��݂�ؾ�Ă��邽�߂̂���

	// key�̏�Ԃ�ύX���Ă���
	bool animKey(const ANIM key);
	//// key�̏����擾���Ă���
	const ANIM& animKey() const;

	shot_array _shots;

	Vector2d _sigBegin;		// ���Ӳ�ނ̎n�_
	Vector2d _sigEnd;		// ���Ӳ�ނ̏I�_

	Vector2d _pos;
	Vector2d _vel;
	Size _size;
	Rect _rect;
	double _rad;			// �摜�̌���(׼ޱ�)

	bool _isTable;		// true : ð��قɔz�u���ꂽ, false : ð��قɔz�u����Ă��Ȃ�
	bool _isAlive;		// true : ����, false : ���S
	bool _isDeath;		// true : ���S, false : ���S������
	
	// first : �ړ���, second : �ړ����x
	static enTbl_pair _moveTblInfo;
	static int _leadCnt;
	void AnimUpdate(const int& animSpeed);
private:
	// void AnimUpdate();
	
	// first : �摜ID, second : ��Ұ����ڰ�
	std::map<ANIM, anim_vec> _animMap;

	ANIM _animKey;
	int _invCnt;
	int _animID;
	int _enAction;

};

