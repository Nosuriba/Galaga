#pragma once
#include <list>
#include <array>
#include "Scene.h"
#include "../Object/Enemy.h"

class Object;

class MainScene :
	public Scene
{
public:
	MainScene();
	~MainScene();
	void Init() override;
	void Draw();
	unique_scene Update(unique_scene scene, const Input& p) override;
	const SCN_ID GetSceneID() const override;
private:
	std::vector<std::shared_ptr<Object>> _objs;

	void AddEnemy(const EnemyState& state);
	void DecideDir();

	int _ghGameScreen;		// ¹Ş°Ñ½¸Ø°İ‚Ì‰æ‘œÊİÄŞÙ

	char _dbgKey;
	char _dbgKeyOld;

	int _enCnt;				// oŒ»‚µ‚Ä‚¢‚é“G‚Ì¶³İÄ
	
	std::vector<char> _enTblInfo;					// “G‚Ì”z’uî•ñ‚ğŠm”F‚·‚éÃ°ÌŞÙ
	std::vector<std::vector<Vector2>> _dirInfo;	// “G‚ÌˆÚ“®•ûŒü‚Ìî•ñ
	std::array<Vector2, 6> _initPos;				// “G‚Ì‰Šú”z’u•Û‘¶—p
	std::array<Vector2, 6> _enSpace;				// “G‚ÌŠÔŠu—p

	const Size _charSize;
	const Vector2 _enMax;			// “G‚ÌÅ‘å”

};

