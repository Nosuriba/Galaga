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
	void AddEnemy(EnemyState state);

	int _ghGameScreen;		// �ްѽ�ذ݂̉摜�����

	char _dbgKey;
	char _dbgKeyOld;

	Vector2 _defPos;

	int _enCnt;			  // �o�����Ă���G�̶���

	/// �G�̏����z�u�p�̐ݒ�
	std::array<Vector2, 6> _initPos; 

	const Size _charSize;

};

