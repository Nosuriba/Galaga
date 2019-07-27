#pragma once
#include <vector>
#include <memory>
#include <map>
#include "../Vector2.h"
#include "../Input.h"
#include "../DebugDisp.h"

// ｱﾆﾒｰｼｮﾝ管理用の可変長配列
using anim_vec = std::vector<std::pair<int, int>>;

// ﾃｰﾌﾞﾙの移動情報のﾍﾟｱ
using mTbl_pair = std::pair<double, int>;

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
	bool CheckMoveTbl() const;
	void SetMoveTbl(const mTbl_pair& tblInfo);
	int GetEnemyNum() const;

	bool GetDeath() const;
protected:
	// ｱﾆﾒｰｼｮﾝの登録
	bool SetAnim(ANIM key, anim_vec& data);

	bool DestryCheck();

	void SetInvCnt(const int& leadCnt);
	void ResetInvCnt();

	// keyの状態を変更している
	bool animKey(const ANIM key);
	//// keyの情報を取得している
	//const ANIM& animKey() const;

	Vector2d _pos;
	Vector2d _vel;				// 必要ない場合、後で消す
	Size _size;
	Rect _rect;
	double _rad;

	bool _tblFlag = false;
	bool _isAlive = true;		// true : 生存, false : 死亡
	bool _isDeath = false;		// true : 敵の削除, false : 死亡処理中

	int _enNum;					// 敵の番号
	
	// first : 移動幅(intに変更する可能性あり), second : 移動速度
	static mTbl_pair _moveTblInfo;
	static int _leadCnt;
private:
	void AnimUpdate();
	
	// first : 画像ID, second : ｱﾆﾒｰｼｮﾝﾌﾚｰﾑ
	std::map<ANIM, anim_vec> _animMap;

	ANIM _animKey;
	int _invCnt = 0;
	int _animID = 0;

};

