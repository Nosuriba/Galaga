#pragma once

#include <vector>
#include <memory>
#include <map>
#include "../Vector2.h"
#include "../Input.h"
#include "../DebugDisp.h"

// ｱﾆﾒｰｼｮﾝ管理用の可変長配列
using anim_vec = std::vector<std::pair<int, int>>;

enum class ANIM
{
	NORMAL,		// 通常
	DEATH,		// 死亡
	EX,			// 特殊
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

	// 先頭に登録された敵のｱﾆﾒｰｼｮﾝ更新
	void LeadAnimUpdate();
	int GetEnemyNum() const;

	bool GetDeath() const;

	const Vector2d& pos() const;
protected:
	// ｱﾆﾒｰｼｮﾝの登録
	bool SetAnim(ANIM key, anim_vec& data);
	void SetEnemyNum(const int& num);

	bool DestryCheck();

	void SetInvCnt(const int& leadCnt);
	void ResetInvCnt();

	// keyの状態を変更している
	bool animKey(const ANIM key);
	// keyの情報を取得している
	const ANIM& animKey() const;

	Vector2d _pos;
	Vector2d _vel;
	Size _size;
	Rect _rect;
	double _rad;
	bool _isAlive = true;		// true : 生存, false : 死亡
	bool _isDeath = false;		// true : 敵の削除, false : 死亡処理中

	static int _leadCnt;
private:
	void AnimUpdate();
	
	// pairの要素(first : ID, second : frame)
	std::map<ANIM, anim_vec> _animMap;

	ANIM _animKey;
	int _invCnt = 0;
	int _animID = 0;

	int _enNum;

};

