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

	int _ghGameScreen;		// �ްѽ�ذ݂̉摜�����
	int _enCnt;				// �o�����Ă���G�̶���

	/// ���ޯ�ޗp�Ȃ̂ŁA��ŏ���
	char _dbgKey;
	char _dbgKeyOld;

	std::vector<shared_obj> _objs;

	//// ð��ق̍��[�̏������������W���g���Ă����΁A���Ƃ��ł���������
	/// ���������W��double�^�Ȃ̂ŁAint�^�ŃL���X�g���ď����_�̖����Y��Ȓl��n���Ă�����΂�������
	Vector2d _posLD;		// ð��ق̍����̍��W

	std::vector<char> _enTblInfo;		// �G�̔z�u�����m�F����ð���
	std::array<Vector2, 6> _initPos;	// �G�̏������W

	const Size _charSize;
	const Vector2 _enMax;				// �G�̍ő吔
};

