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

	/// ˆø”‚É‰½‘Ì¶¬‚Å‚«‚é‚©‚Ìİ’è‚à‘z’è‚µ‚Ä‚¨‚¢‚½•û‚ª‚¢‚¢‚©‚à‚µ‚ê‚È‚¢
	void SetEnemy();

	int _ghGameScreen;		// ¹Ş°Ñ½¸Ø°İ‚Ì‰æ‘œÊİÄŞÙ

	int _dbgKeyTbl[10];
};

