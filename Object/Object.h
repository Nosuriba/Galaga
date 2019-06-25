#pragma once

#include <vector>
#include <memory>
#include <map>
#include "../Vector2.h"
#include "../Input.h"

// ��Ұ��݊Ǘ��p�̉ϒ��z��
using anim_vec = std::vector<std::pair<int, int>>;

/// ���g���C������\������
enum class ANIM
{
	NORMAL,		// �ʏ�
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
	virtual void Update(const Input& p) = 0;
	virtual void Draw() = 0;
	virtual const Obj GetObjID() const = 0;
protected:
	Vector2f _pos;
	Vector2f _vel;
	Rect _rect;

	int _invCnt  = 0;
	int _animCnt = 0;

	bool SetAnim(const ANIM key, const anim_vec& data);
	std::map<ANIM, anim_vec> _animMap;

	const Size _charSize = Size(30, 32);

private:
	//std::map<ANIM, anim_vec> _animMap;
};

