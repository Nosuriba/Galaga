#pragma once
#include <vector>
#include <array>
#include <memory>
#include <map>
#include "../Vector2.h"
#include "../DebugDisp.h"
#include "../AudioMng.h"

class Shot;
class InputState;

enum class ANIM
{
	NORMAL,		// 通常
	DEATH,		// 死亡
	EX,			// 特殊
	MAX
};

enum class OBJ
{
	ENEMY,
	PLAYER,
	MAX
};

// ｱﾆﾒｰｼｮﾝ管理用の可変長配列
using anim_vec = std::vector<std::pair<int, int>>;
// 敵配置用ﾃｰﾌﾞﾙの移動情報
using enTbl_pair = std::pair<int, int>;

using shared_shot = std::shared_ptr<Shot>;
// shared_ptrの固定長配列
using shot_array  = std::array<shared_shot, 2>;

class Object
{
public:
	Object();
	virtual ~Object();
	virtual void Update(const std::unique_ptr<InputState>& p) = 0;
	void Draw();
	virtual const OBJ GetObjID() const = 0;

	// 先頭に登録された敵のｱﾆﾒｰｼｮﾝ更新
	void LeadAnimUpdate();
	bool IsMoveTbl() const;
	void SetTblInfo(const enTbl_pair& tblInfo);

	Rect GetRect() const;
	shot_array GetShot() const;
	void ShotDelete(const shared_shot& shot);

	//	敵の移動情報を継承の継承先で設定している
	virtual void SetSigEnd(const Vector2d& sigEnd);

	bool IsAlive() const;
	void ChangeAlive();			// 死亡状態に変更する
	bool GetDeath() const;

	const Vector2d& GetPos() const;
protected:
	// ｱﾆﾒｰｼｮﾝの登録
	bool SetAnim(ANIM key, anim_vec& data);

	bool DestryCheck();

	void SetInvCnt(const int& leadCnt);
	void ResetAnim();						// 死亡時にｱﾆﾒｰｼｮﾝをﾘｾｯﾄするためのもの

	// keyの状態を変更している
	bool animKey(const ANIM key);
	//// keyの情報を取得している
	const ANIM& animKey() const;
	void AnimUpdate(const int& animSpeed);

	shot_array _shots;

	Vector2d _sigBegin;		// ｼｸﾞﾓｲﾄﾞの始点
	Vector2d _sigEnd;		// ｼｸﾞﾓｲﾄﾞの終点

	Vector2d _pos;
	Vector2d _vel;
	Size _size;
	Rect _rect;
	double _rad;			// 画像の向き(ﾗｼﾞｱﾝ)

	bool _isTable;		// true : ﾃｰﾌﾞﾙに配置された, false : ﾃｰﾌﾞﾙに配置されていない
	bool _isAlive;		// true : 生存, false : 死亡
	bool _isDeath;		// true : 死亡, false : 死亡処理中
	
	// first : 移動幅, second : 移動速度
	static enTbl_pair _moveTblInfo;
	static int _leadCnt;
private:

	// first : 画像ID, second : ｱﾆﾒｰｼｮﾝﾌﾚｰﾑ
	std::map<ANIM, anim_vec> _animMap;

	ANIM _animKey;
	int _invCnt;
	int _animID;
	int _enAction;

};

