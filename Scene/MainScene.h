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
	void AddEnemy(const int& line, const EnemyState& state);
	void DecideDir();

	int _ghGameScreen;		// �ްѽ�ذ݂̉摜�����

	char _dbgKey;
	char _dbgKeyOld;

	int _enCnt;				// �o�����Ă���G�̶���
	
	std::vector<shared_obj> _objs;


	std::vector<char> _enTblInfo;				// �G�̔z�u�����m�F����ð���
	std::vector<std::vector<int>> _dirInfo;		// �G�̈ړ������̏��
	std::array<Vector2, 6> _initPos;			// �G�̏����z�u�ۑ��p
	std::array<Vector2, 6> _enSpace;			// �G�̊Ԋu�p

	const Size _charSize;
	const Vector2 _enMax;			// �G�̍ő吔

};

