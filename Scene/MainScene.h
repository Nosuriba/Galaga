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

	/// �����ɉ��̐����ł��邩�̐ݒ���z�肵�Ă���������������������Ȃ�
	void SetEnemy();

	int _ghGameScreen;		// �ްѽ�ذ݂̉摜�����

	int _dbgKeyTbl[10];
};

