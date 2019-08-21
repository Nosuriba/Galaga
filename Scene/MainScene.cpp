#include <algorithm>
#include <stdlib.h>	
#include <time.h>			/// 乱数の生成で使用している
#include <DxLib.h>
#include "MainScene.h"
#include "ResultScene.h"
#include "../Game.h"
#include "../Collision.h"
#include "../DebugConOut.h"

#include "../Object/Shot.h"
#include "../Object/Player.h"
#include "../Object/Bee.h"
#include "../Object/Butterfly.h"
#include "../Object/Boss.h"

MainScene::MainScene() : _charSize(30,32), _enMax(10, 5)
{
	/// 敵のﾃｰﾌﾞﾙを生成している
	_enTblInfo.reserve(_enMax.x * _enMax.y);
	for (int i = 0; i < (_enMax.x * _enMax.y); ++i)
	{
		_enTblInfo.emplace_back(0);
	}
	/// 特定のﾃｰﾌﾞﾙには配置できないようにしている
	_enTblInfo[0] = 1;
	_enTblInfo[1] = 1;
	_enTblInfo[2] = 1;
	_enTblInfo[7] = 1;
	_enTblInfo[8] = 1;
	_enTblInfo[9] = 1;
	_enTblInfo[10] = 1;
	_enTblInfo[19] = 1;
	_enTblInfo[20] = 1;
	_enTblInfo[29] = 1;

	_enCnt = 10;
	InitTbl();

	/// 左端
	_initPos[0] = Vector2(-_charSize.width, _charSize.height);
	_initPos[1] = Vector2(-_charSize.width, LpGame.gameScreenSize.y / 2);
	_initPos[2] = Vector2(-_charSize.width, LpGame.gameScreenSize.y - _charSize.height * 2);
	/// 右端
	_initPos[3] = Vector2(LpGame.gameScreenSize.x, _charSize.height);
	_initPos[4] = Vector2(LpGame.gameScreenSize.x, 
						  LpGame.gameScreenSize.y / 2);
	_initPos[5] = Vector2(LpGame.gameScreenSize.x,
						  LpGame.gameScreenSize.y - _charSize.height * 2);
	Init();

	_col = std::make_unique<Collision>();

	_textCnt = 0;
	_textData.emplace_back("PLAYER ");
	_textData.emplace_back("STAGE ");

	/// 音楽が停止されているかの判定用関数がなかったため
	/// 後で追加する。
	LpAudioMng.PlayBGM("Music/wait.mp3");
	_mode = &MainScene::WaitMode;
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	srand((unsigned int)time(0));

	_ghGameScreen = MakeScreen(LpGame.gameScreenSize.x, LpGame.gameScreenSize.y, true);
}

const SCN_ID MainScene::GetSceneID() const
{
	return SCN_ID::MAIN;
}

void MainScene::InitTbl()
{
	_tblInfo = { 1,0 };

	double posX, posY;
	/// 左下のﾃｰﾌﾞﾙ位置を求める計算
	posX = LpGame.gameScreenPos.x / 2 + _charSize.width;
	posY = LpGame.gameScreenPos.y / 2 + (_enMax.y - 2) * _charSize.height;
	_tblCtlPos[0] = Vector2(posX, posY);

	/// 右下のﾃｰﾌﾞﾙ位置を求める計算
	posX = LpGame.gameScreenPos.x / 2 + _enMax.x * _charSize.width;
	_tblCtlPos[1] = Vector2(posX, posY);
}

void MainScene::CreateEnemy(const shared_itr& enBegin)
{
	auto isCreate = enBegin == _objs.end();
	auto enemy = enBegin;
	for (; enemy != _objs.end(); ++enemy)
	{
		if ((*enemy)->IsMoveTbl())
		{
			isCreate = true;
		}
		else
		{
			isCreate = false;
			break;
		}
	}
	
	/// 敵の生成(仮で生成している)
	if (isCreate)
	{
		auto randNum = rand();
		auto debugPos = Vector2d(200 + (rand() % 10 * 10), 250);
		for (int cnt = 0; cnt < 8;)
		{
			/// 出現している敵が最大数を超えている時、処理を抜ける
			if (_enCnt >= (_enMax.x * _enMax.y))
			{
				break;
			}
			auto num = rand() % (_enMax.x * _enMax.y);
			if (!_enTblInfo[num])
			{
				/// 敵の情報設定
				auto aimPos = Vector2d(LpGame.gameScreenPos.x / 2 + ((num % _enMax.x) + 1) * _charSize.width,
									   LpGame.gameScreenPos.y / 2 + ((num / _enMax.x) - 1) * _charSize.height);

				/// 敵の生成
				auto line = num / _enMax.x;
				EnemyState state = { _initPos[randNum % 6], _charSize,
									 EN_TYPE::NORMAL, 10 * cnt, debugPos, aimPos };

				AddEnemy(line, state);
				++cnt;
				++_enCnt;
				_enTblInfo[num] = 1;
			}
			LpAudioMng.PlaySE("Music/comeOut.mp3");
		}

		/// 敵を末尾にｿｰﾄしている
		std::sort(_objs.begin(),
				  _objs.end(),
				  [](shared_obj& obj, shared_obj& obj2) { return (*obj).GetObjID() > (*obj2).GetObjID(); });
	}
}

void MainScene::AddEnemy(const int & line, const EnemyState & state)
{
	if (line == 0)
	{
		/// ｻｿﾘの生成
		_objs.emplace_back(std::make_shared<Boss>(state));
	}
	else if (line == 1 || line == 2)
	{
		/// 蝶の生成
		_objs.emplace_back(std::make_shared<Butterfly>(state));
	}
	else
	{
		/// 蜂の生成
		_objs.emplace_back(std::make_shared<Bee>(state));
	}
}

void MainScene::Draw()
{
	/// ｹﾞｰﾑｽｸﾘｰﾝの描画を行っている
	auto beforScr = GetDrawScreen();
	SetDrawScreen(_ghGameScreen);
	ClsDrawScreen();

	for (auto obj : _objs)
	{
		if (obj != nullptr)
		{
			obj->Object::Draw();
		}
	}

	if (_mode == &MainScene::WaitMode)
	{
		for (int i = 0; i <= (_textCnt / 120); ++i)
		{
			Vector2 offset(150, LpGame.gameScreenSize.y / 3 + (i * 30));
			for (auto charCode : _textData[i])
			{
				if (charCode >= 'A' || charCode <= 'Z')
				{
					if (charCode <= 0)
					{
						continue;
					}
					if (charCode == 32)
					{
						offset.x += 16;
						continue;
					}
					int id = charCode - 'A';
					DrawGraph(offset.x, offset.y, IMAGE_ID("text")[id], true);
					offset.x += 16;
				}
			}
			DrawGraph(offset.x, offset.y, IMAGE_ID("num")[1], true);
		}
		
	}

	LpGame.AddDrawQue({ _ghGameScreen, LpGame.gameScreenPos.x, LpGame.gameScreenPos.y});
	SetDrawScreen(beforScr);
}

void MainScene::TblMoveUpdate()
{
	if (_tblCtlPos[0].x <= _charSize.width / 2 ||
		_tblCtlPos[1].x >= LpGame.gameScreenSize.x - _charSize.width / 2)
	{
		_tblInfo.second = -_tblInfo.second;
	}
	_tblInfo.first += _tblInfo.second;
}

bool MainScene::PlayerCol(const shared_obj& player, const shared_itr& enBegin)
{
	auto enemy = enBegin;
	for (; enemy != _objs.end(); ++enemy)
	{
		/// 敵との当たり判定
		if (_col->IsCollision(player->GetRect(), (*enemy)->GetRect()))
		{
			return true;
		}

		/// 敵のｼｮｯﾄとの当たり判定
		for (auto& shot : (*enemy)->GetShot())
		{
			if (shot != nullptr)
			{
				if (_col->IsCollision(player->GetRect(), shot->GetRect()) &&
					player->IsAlive())
				{
					(*enemy)->ShotDelete(shot);
					return true;
				}
			}
		}
	}
	return false;
}

bool MainScene::EnemyCol(const shared_obj& enemy, const shared_itr& enBegin)
{
	auto player = _objs.begin();
	for (; player != enBegin; ++player)
	{
		/// ﾌﾟﾚｲﾔｰのｼｮｯﾄとの当たり判定
		for (auto shot : (*player)->GetShot())
		{
			if (shot != nullptr)
			{
				if (_col->IsCollision(enemy->GetRect(), shot->GetRect()) &&
					enemy->IsAlive())
				{
					(*player)->ShotDelete(shot);
					return true;
				}
			}
		}
	}
	return false;
}

int MainScene::WaitMode(const std::unique_ptr<InputState>& p)
{
	Draw();
	_textCnt = (_textCnt <= 238 ? _textCnt + 1 : _textCnt);
	if (_textCnt == 120)
	{
		/// ﾌﾟﾚｲﾔｰの生成
		_objs.emplace_back(std::make_shared<Player>(Vector2(LpGame.gameScreenSize.x / 2 - _charSize.width,
															LpGame.gameScreenSize.y - _charSize.height), _charSize));
	}

	if (!LpAudioMng.CheckSound("Music/wait.mp3"))
	{
		_mode = &MainScene::PlayingMode;
	}
	return 0;
}

int MainScene::PlayingMode(const std::unique_ptr<InputState>& p)
{
	/// 敵の生成前の先頭を取得している
	auto enBegin = std::find_if(_objs.begin(),
								_objs.end(),
								[](shared_obj& obj) {return (*obj).GetObjID() == OBJ::ENEMY; });
	auto player = _objs.begin();

	CreateEnemy(enBegin);

	/// 敵を生成後の先頭を取得している
	enBegin = std::find_if(_objs.begin(),
		_objs.end(),
		[](shared_obj& obj) {return (*obj).GetObjID() == OBJ::ENEMY; });
	auto enemy = enBegin;


	/// 全ての敵が配置された時の処理
	if (_enCnt >= (_enMax.x * _enMax.y))
	{
		_isTable = true;
		Vector2d pPos;
		pPos = (*player)->GetPos();
		for (; enemy != _objs.end(); ++enemy)
		{
			if ((*enemy)->IsMoveTbl())
			{
				auto isAction = (rand() % 20 == 0);
				if (isAction && _tblInfo.second == 0)
				{
					(*enemy)->SetSigEnd(pPos);
				}
			}
			else
			{
				_isTable = false;
			}
		}
	}

	/// 最初に登録された敵のみ情報を更新する処理
	enemy = enBegin;
	for (; enemy != _objs.end(); ++enemy)
	{
		if ((*enemy)->IsMoveTbl())
		{
			TblMoveUpdate();
			/// ﾃｰﾌﾞﾙ制御の座標更新
			for (auto& tPos : _tblCtlPos)
			{
				tPos.x += _tblInfo.second;
			}
		}
		(*enemy)->LeadAnimUpdate();
		(*enemy)->SetTblInfo(_tblInfo);
		break;
	}
	/// ﾃｰﾌﾞﾙ情報の更新
	if (!_isTable)
	{
		_tblInfo.second = (_tblInfo.second == 0 ? 1 : _tblInfo.second);
	}
	else
	{
		/// 全員配置された後、真ん中に到着したとき横移動を止めている
		_tblInfo.second = (_tblInfo.first == 0 ? 0 : _tblInfo.second);
	}

	/// 敵とﾌﾟﾚｲﾔｰの更新
	for (auto obj : _objs)
	{
		obj->Update(p);
	}

	/// ﾌﾟﾚｲﾔｰの当たり判定
	player = _objs.begin();
	for (; player != enBegin; ++player)
	{
		if (PlayerCol((*player), enBegin))
		{
			(*player)->ChangeAlive();
		}
	}

	/// 敵の当たり判定
	enemy = enBegin;
	for (; enemy != _objs.end(); ++enemy)
	{
		if (EnemyCol((*enemy), enBegin))
		{
			(*enemy)->ChangeAlive();
		}
	}

	/// ｹﾞｰﾑｽｸﾘｰﾝ上の描画
	Draw();
	/// vectorの削除する範囲の指定
	auto eraseBegin = remove_if(_objs.begin(),				// 開始位置
		_objs.end(),				// 終了位置
		[](shared_obj& obj) {return (*obj).GetDeath(); });		// moveするかの判定部

	/// 指定した範囲のvectorを削除している
	_objs.erase(eraseBegin, _objs.end());

	return 0;
}

unique_scene MainScene::Update(unique_scene scene, const std::unique_ptr<InputState>& p)
{
	(this->*_mode)(p);

	if (_enCnt >= (_enMax.x * _enMax.y))
	{
		auto isClear = true;
		for (auto obj : _objs)
		{
			if (obj->GetObjID() == OBJ::ENEMY)
			{
				isClear = false;
				break;
			}
		}
		
		if (isClear)
		{
			return std::make_unique<ResultScene>();
		}
	}
	return std::move(scene);
}