#pragma once
#include <vector>
#include <array>
#include <memory>
#include <map>
#include "../Vector2.h"
#include "../Input.h"
#include "../DebugDisp.h"

class Shot;

// ±ÆÒ°¼®İŠÇ——p‚Ì‰Â•Ï’·”z—ñ
using anim_vec = std::vector<std::pair<int, int>>;

// “G”z’u—pÃ°ÌŞÙ‚ÌˆÚ“®î•ñ
using enTbl_pair = std::pair<int, int>;

enum class ANIM
{
	NORMAL,		// ’Êí
	DEATH,		// €–S
	EX,			// “Áê
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

	// æ“ª‚É“o˜^‚³‚ê‚½“G‚Ì±ÆÒ°¼®İXV
	void LeadAnimUpdate();
	bool CheckMoveTbl() const;
	void SetMoveTbl(const enTbl_pair& tblInfo);
	int GetEnemyNum() const;

	//	“G‚ÌˆÚ“®î•ñ‚ğŒp³‚ÌŒp³æ‚Åİ’è‚µ‚Ä‚¢‚é
	virtual void SetMoveInfo(const Vector2d& sigEnd);

	bool GetDeath() const;

	const Vector2d& GetPos() const;
protected:
	// ±ÆÒ°¼®İ‚Ì“o˜^
	bool SetAnim(ANIM key, anim_vec& data);

	bool DestryCheck();

	void SetInvCnt(const int& leadCnt);
	void ResetInvCnt();						// €–S‚É±ÆÒ°¼®İ‚ğØ¾¯Ä‚·‚é‚½‚ß‚Ì‚à‚Ì

	// key‚Ìó‘Ô‚ğ•ÏX‚µ‚Ä‚¢‚é
	bool animKey(const ANIM key);
	//// key‚Ìî•ñ‚ğæ“¾‚µ‚Ä‚¢‚é
	//const ANIM& animKey() const;

	// std::array<shared_shot, 2> _shots;

	Vector2d _sigBegin;		// ¼¸ŞÓ²ÄŞ‚Ìn“_
	Vector2d _sigEnd;		// ¼¸ŞÓ²ÄŞ‚ÌI“_

	Vector2d _pos;
	Vector2d _vel;
	Size _size;
	Rect _rect;
	double _rad;			// ‰æ‘œ‚ÌŒü‚«(×¼Ş±İ)

	bool _isTable = false;		// true : Ã°ÌŞÙ‚É”z’u‚³‚ê‚½, false : Ã°ÌŞÙ‚É”z’u‚³‚ê‚Ä‚¢‚È‚¢
	bool _isAlive = true;		// true : ¶‘¶, false : €–S
	bool _isDeath = false;		// true : €–S, false : €–Sˆ—’†

	int _enNum;					// “G‚Ì”Ô†
	
	// first : ˆÚ“®•, second : ˆÚ“®‘¬“x
	static enTbl_pair _moveTblInfo;
	static int _leadCnt;
	void AnimUpdate(const int& animSpeed);
private:
	// void AnimUpdate();
	
	// first : ‰æ‘œID, second : ±ÆÒ°¼®İÌÚ°Ñ
	std::map<ANIM, anim_vec> _animMap;

	ANIM _animKey;
	int _invCnt = 0;
	int _animID = 0;
	int enAction = 0;

};

