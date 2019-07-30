#pragma once
#include <list>
#include <array>
#include "Scene.h"
#include "../Object/Enemy.h"

class Object;

using shared_obj = std::shared_ptr<Object>;

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

	// 敵の情報を再設定するもの
	void ResetTbl();
	void AddEnemy(const int& line, const EnemyState& state);
	void TblMoveUpdate();	// ﾃｰﾌﾞﾙ更新用

	// first : 移動幅, second : 速度
	enTbl_pair _tblInfo;

	int _ghGameScreen;		// ｹﾞｰﾑｽｸﾘｰﾝの画像ﾊﾝﾄﾞﾙ
	int _enCnt;				// 出現している敵のｶｳﾝﾄ

	/// ﾃﾞﾊﾞｯｸﾞ用なので、後で消す
	char _dbgKey;
	char _dbgKeyOld;

	std::vector<shared_obj> _objs;

	/// 動かす座標はdouble型なので、int型でキャストして小数点の無い綺麗な値を渡してあげればいいかな
	std::array<Vector2d, 2> _tblCtlPos;		// ﾃｰﾌﾞﾙ移動制御用の座標

	std::vector<char> _enTblInfo;			// 敵の配置情報を確認するﾃｰﾌﾞﾙ
	std::array<Vector2, 6> _initPos;		// 敵の初期座標

	const Size _charSize;
	const Vector2 _enMax;					// 敵の最大数
};

