#pragma once
#include <list>
#include "Scene.h"

class Object;

class MainScene :
	public Scene
{
public:
	MainScene();
	~MainScene();
	void Init()override;
	void Draw();
	unique_scene Update(unique_scene scene, const Input& p) override;
	const SCN_ID GetSceneID() const override;
private:
	std::vector<std::shared_ptr<Object>> _objVector;

	/// 引数に何体生成できるかの設定も想定しておいた方がいいかもしれない
	void SetEnemy();

	int _ghGameScreen;		// ｹﾞｰﾑｽｸﾘｰﾝの画像ﾊﾝﾄﾞﾙ

	int _dbgKeyTbl[10];
};

