#pragma once
#include <vector>
#include <memory>
#include <map>
#include "../Vector2.h"
#include "../Input.h"
#include "../DebugDisp.h"

// ±ÆÒ°¼®İŠÇ——p‚Ì‰Â•Ï’·”z—ñ
using anim_vec = std::vector<std::pair<int, int>>;

// Ã°ÌŞÙ‚ÌˆÚ“®î•ñ‚ÌÍß±
using mTbl_pair = std::pair<double, int>;

enum class ANIM
{
	NORMAL,		// ’Êí
	DEATH,		// €–S
	EX,			// “Áê
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

	// æ“ª‚É“o˜^‚³‚ê‚½“G‚Ì±ÆÒ°¼®İXV
	void LeadAnimUpdate();
	bool CheckMoveTbl() const;
	void SetMoveTbl(const mTbl_pair& tblInfo);
	int GetEnemyNum() const;

	bool GetDeath() const;
protected:
	// ±ÆÒ°¼®İ‚Ì“o˜^
	bool SetAnim(ANIM key, anim_vec& data);

	bool DestryCheck();

	void SetInvCnt(const int& leadCnt);
	void ResetInvCnt();

	// key‚Ìó‘Ô‚ğ•ÏX‚µ‚Ä‚¢‚é
	bool animKey(const ANIM key);
	//// key‚Ìî•ñ‚ğæ“¾‚µ‚Ä‚¢‚é
	//const ANIM& animKey() const;

	Vector2d _pos;
	Vector2d _vel;				// •K—v‚È‚¢ê‡AŒã‚ÅÁ‚·
	Size _size;
	Rect _rect;
	double _rad;

	bool _tblFlag = false;
	bool _isAlive = true;		// true : ¶‘¶, false : €–S
	bool _isDeath = false;		// true : “G‚Ìíœ, false : €–Sˆ—’†

	int _enNum;					// “G‚Ì”Ô†
	
	// first : ˆÚ“®•(int‚É•ÏX‚·‚é‰Â”\«‚ ‚è), second : ˆÚ“®‘¬“x
	static mTbl_pair _moveTblInfo;
	static int _leadCnt;
private:
	void AnimUpdate();
	
	// first : ‰æ‘œID, second : ±ÆÒ°¼®İÌÚ°Ñ
	std::map<ANIM, anim_vec> _animMap;

	ANIM _animKey;
	int _invCnt = 0;
	int _animID = 0;

};

