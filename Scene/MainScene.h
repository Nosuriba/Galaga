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
	void Init()override;
	void Draw();
	unique_scene Update(unique_scene scene, const Input& p) override;
	const SCN_ID GetSceneID() const override;
private:
	std::vector<std::shared_ptr<Object>> _objs;

	void SetEnemy();
	void AddEnemy(const Vector2& pos, EN_TYPE type);

	int _ghGameScreen;		// ¹Ş°Ñ½¸Ø°İ‚Ì‰æ‘œÊİÄŞÙ

	char _dbgKey;
	char _dbgKeyOld;

	/// “G‚Ì‰Šú”z’u—p‚Ìİ’è
	std::array<Vector2, 6> _initPos; 

};

