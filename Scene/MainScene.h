#pragma once
#include <list>
#include <array>
#include "Scene.h"
#include "../Object/Enemy.h"
#include "../Object/Object.h"

class Collision;

using shared_obj = std::shared_ptr<Object>;
using shared_itr = std::vector<shared_obj>::iterator;

class MainScene :
	public Scene
{
public:
	MainScene();
	~MainScene();
	void Init() override;
	void Draw();
	unique_scene Update(unique_scene scene, const std::unique_ptr<InputState>& p) override;
	const SCN_ID GetSceneID() const override;
private:

	// 敵の情報を再設定するもの
	void InitTbl();
	void CreateEnemy(const shared_itr& enBegin);
	void AddEnemy(const int& line, const EnemyState& state);
	void TblMoveUpdate();	// ﾃｰﾌﾞﾙ更新用

	/// 当たり判定の確認用
	bool PlayerCol(const shared_obj& player, const shared_itr& enBegin);
	bool EnemyCol(const shared_obj& enemy, const shared_itr& enBegin);

	int WaitMode(const std::unique_ptr<InputState>& p);
	int PlayingMode(const std::unique_ptr<InputState>& p);

	int (MainScene::*_mode)(const std::unique_ptr<InputState>& p);

	// first : 移動幅, second : 速度
	enTbl_pair _tblInfo;

	std::unique_ptr<Collision> _col;
	std::vector<shared_obj> _objs;
	std::vector<std::string> _textData;
	
	std::vector<char> _enTblInfo;			// 敵の配置情報を確認するﾃｰﾌﾞﾙ
	std::array<Vector2, 2> _tblCtlPos;		// ﾃｰﾌﾞﾙ移動制御用の座標
	std::array<Vector2, 6> _initPos;		// 敵の初期座標

	int _ghGameScreen;		// ｹﾞｰﾑｽｸﾘｰﾝの画像ﾊﾝﾄﾞﾙ
	int _enCnt;				// 出現している敵のｶｳﾝﾄ

	bool _isTable;

	const Size _charSize;
	const Vector2 _enMax;					// 敵の最大数

	int _textCnt;
};

