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

	// �G�̏����Đݒ肷�����
	void ResetTbl();
	void AddEnemy(const int& line, const EnemyState& state);
	void TblMoveUpdate();	// ð��ٍX�V�p

	// first : �ړ���, second : ���x
	enTbl_pair _tblInfo;

	int _ghGameScreen;		// �ްѽ�ذ݂̉摜�����
	int _enCnt;				// �o�����Ă���G�̶���

	/// ���ޯ�ޗp�Ȃ̂ŁA��ŏ���
	char _dbgKey;
	char _dbgKeyOld;

	std::vector<shared_obj> _objs;

	/// ���������W��double�^�Ȃ̂ŁAint�^�ŃL���X�g���ď����_�̖����Y��Ȓl��n���Ă�����΂�������
	std::array<Vector2d, 2> _tblCtlPos;		// ð��وړ�����p�̍��W

	std::vector<char> _enTblInfo;			// �G�̔z�u�����m�F����ð���
	std::array<Vector2, 6> _initPos;		// �G�̏������W

	const Size _charSize;
	const Vector2 _enMax;					// �G�̍ő吔
};

