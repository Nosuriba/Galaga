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
	unique_scene Update(unique_scene scene, const std::unique_ptr<InputState>& p) override;
	const SCN_ID GetSceneID() const override;
private:

	// �G�̏����Đݒ肷�����
	void InitTbl();
	void CreateEnemy(const shared_itr& enBegin);
	void AddEnemy(const int& line, const EnemyState& state);
	void TblMoveUpdate();	// ð��ٍX�V�p

	/// �����蔻��̊m�F�p
	bool PlayerCol(const shared_obj& player, const shared_itr& enBegin);
	bool EnemyCol(const shared_obj& enemy, const shared_itr& enBegin);

	int WaitMode(const std::unique_ptr<InputState>& p);
	int PlayingMode(const std::unique_ptr<InputState>& p);

	int (MainScene::*_mode)(const std::unique_ptr<InputState>& p);

	// first : �ړ���, second : ���x
	enTbl_pair _tblInfo;

	std::unique_ptr<Collision> _col;
	std::vector<shared_obj> _objs;
	std::vector<std::string> _textData;
	
	std::vector<char> _enTblInfo;			// �G�̔z�u�����m�F����ð���
	std::array<Vector2, 2> _tblCtlPos;		// ð��وړ�����p�̍��W
	std::array<Vector2, 6> _initPos;		// �G�̏������W

	int _ghGameScreen;		// �ްѽ�ذ݂̉摜�����
	int _enCnt;				// �o�����Ă���G�̶���

	bool _isTable;

	const Size _charSize;
	const Vector2 _enMax;					// �G�̍ő吔

	int _textCnt;
};

