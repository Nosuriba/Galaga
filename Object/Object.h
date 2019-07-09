#pragma once

#include <vector>
#include <memory>
#include <map>
#include "../Vector2.h"
#include "../Input.h"
#include "../DebugDisp.h"

// ��Ұ��݊Ǘ��p�̉ϒ��z��
using anim_vec = std::vector<std::pair<int, int>>;

enum class ANIM
{
	NORMAL,		// �ʏ�
	BLAST,		// ���j
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
	virtual bool GetAlive() const = 0;
	
	// �e�X�g�p�ō�����̂ŁA��ŏ����\������
	virtual void SetAlive(bool flag);

	/// Vector2�ɑ��邩������Ȃ�
	const Vector2& pos() const;
protected:
	Vector2 _pos;
	Rect _rect;
	bool _isAlive = true;

	// ��Ұ��݂̓o�^
	bool SetAnim(ANIM key, anim_vec& data);

	bool animKey(const ANIM key);
	const ANIM& animKey() const;
	
	const Size _charSize = Size(30, 32);
private:
	void AnimUpdate();
	
	// pair�̗v�f(first : ID, second : frame)
	std::map<ANIM, anim_vec> _animMap;

	ANIM _animKey;
	int _invCnt = 0;
	int _animID = 0;

};

