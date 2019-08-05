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
	NORMAL,		// ’Êí
	DEATH,		// €–S
	EX,			// “Áê
	MAX
};

enum class OBJ
{
	ENEMY,
	PLAYER,
	MAX
};

// ±ÆÒ°¼®İŠÇ——p‚Ì‰Â•Ï’·”z—ñ
using anim_vec = std::vector<std::pair<int, int>>;
// “G”z’u—pÃ°ÌŞÙ‚ÌˆÚ“®î•ñ
using enTbl_pair = std::pair<int, int>;

using shared_shot = std::shared_ptr<Shot>;
// shared_ptr‚ÌŒÅ’è’·”z—ñ
using shot_array  = std::array<shared_shot, 2>;

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
	bool IsMoveTbl() const;
	void SetTblInfo(const enTbl_pair& tblInfo);

	Rect GetRect() const;
	shot_array GetShot() const;
	void ShotDelete(const shared_shot& shot);

	//	“G‚ÌˆÚ“®î•ñ‚ğŒp³‚ÌŒp³æ‚Åİ’è‚µ‚Ä‚¢‚é
	virtual void SetSigEnd(const Vector2d& sigEnd);

	bool IsAlive() const;
	void ChangeAlive();			// €–Só‘Ô‚É•ÏX‚·‚é
	bool GetDeath() const;

	const Vector2d& GetPos() const;
protected:
	// ±ÆÒ°¼®İ‚Ì“o˜^
	bool SetAnim(ANIM key, anim_vec& data);

	bool DestryCheck();

	void SetInvCnt(const int& leadCnt);
	void ResetAnim();						// €–S‚É±ÆÒ°¼®İ‚ğØ¾¯Ä‚·‚é‚½‚ß‚Ì‚à‚Ì

	// key‚Ìó‘Ô‚ğ•ÏX‚µ‚Ä‚¢‚é
	bool animKey(const ANIM key);
	//// key‚Ìî•ñ‚ğæ“¾‚µ‚Ä‚¢‚é
	const ANIM& animKey() const;

	shot_array _shots;

	Vector2d _sigBegin;		// ¼¸ŞÓ²ÄŞ‚Ìn“_
	Vector2d _sigEnd;		// ¼¸ŞÓ²ÄŞ‚ÌI“_

	Vector2d _pos;
	Vector2d _vel;
	Size _size;
	Rect _rect;
	double _rad;			// ‰æ‘œ‚ÌŒü‚«(×¼Ş±İ)

	bool _isTable;		// true : Ã°ÌŞÙ‚É”z’u‚³‚ê‚½, false : Ã°ÌŞÙ‚É”z’u‚³‚ê‚Ä‚¢‚È‚¢
	bool _isAlive;		// true : ¶‘¶, false : €–S
	bool _isDeath;		// true : €–S, false : €–Sˆ—’†
	
	// first : ˆÚ“®•, second : ˆÚ“®‘¬“x
	static enTbl_pair _moveTblInfo;
	static int _leadCnt;
	void AnimUpdate(const int& animSpeed);
private:
	// void AnimUpdate();
	
	// first : ‰æ‘œID, second : ±ÆÒ°¼®İÌÚ°Ñ
	std::map<ANIM, anim_vec> _animMap;

	ANIM _animKey;
	int _invCnt;
	int _animID;
	int _enAction;

};

