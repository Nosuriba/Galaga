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
	unique_scene Update(unique_scene scene, const Input& p) override;
	const SCN_ID GetSceneID() const override;
private:

	// �G�̏����Đݒ肷�����
	void ResetTbl();
	void AddEnemy(const int& line, const EnemyState& state);
	void TblMoveUpdate();	// ð��ٍX�V�p

	/// �����蔻��̊m�F�p
	bool CheckCol(const shared_obj& obj);
	bool PlayerCol(const shared_obj& player);
	bool EnemyCol(const shared_obj& enemy);

	// first : �ړ���, second : ���x
	enTbl_pair _tblInfo;

	std::unique_ptr<Collision> _col;
	std::vector<shared_obj> _objs;
	
	std::vector<char> _enTblInfo;			// �G�̔z�u�����m�F����ð���
	std::array<Vector2, 2> _tblCtlPos;		// ð��وړ�����p�̍��W
	std::array<Vector2, 6> _initPos;		// �G�̏������W


	int _ghGameScreen;		// �ްѽ�ذ݂̉摜�����
	int _enCnt;				// �o�����Ă���G�̶���

	/// ���ޯ�ޗp�Ȃ̂ŁA��ŏ���
	char _dbgKey;
	char _dbgKeyOld;

	
	const Size _charSize;
	const Vector2 _enMax;					// �G�̍ő吔
};

