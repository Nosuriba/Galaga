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

	int _ghGameScreen;		// ｹﾞｰﾑｽｸﾘｰﾝの画像ﾊﾝﾄﾞﾙ

	char _dbgKey;
	char _dbgKeyOld;

	int _enCnt;				// 出現している敵のｶｳﾝﾄ
	
	std::vector<char> _enTblInfo;				// 敵の配置情報を確認するﾃｰﾌﾞﾙ
	std::vector<std::vector<int>> _dirInfo;		// 敵の移動方向の情報
	std::array<Vector2, 6> _initPos;			// 敵の初期配置保存用
	std::array<Vector2, 6> _enSpace;			// 敵の間隔用

	const Size _charSize;
	const Vector2 _enMax;			// 敵の最大数

};

