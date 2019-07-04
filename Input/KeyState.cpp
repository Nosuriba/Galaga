#include <DxLib.h>
#include "KeyState.h"
#include "../DebugConOut.h"

KeyState::KeyState()
{
	/// ﾃﾞﾌｫﾙﾄのｷｰ設定
	_defKeyID.reserve(static_cast<size_t>(end(INPUT_ID())));
	_defKeyID.emplace_back(KEY_INPUT_LEFT);
	_defKeyID.emplace_back(KEY_INPUT_RIGHT);
	_defKeyID.emplace_back(KEY_INPUT_UP);
	_defKeyID.emplace_back(KEY_INPUT_DOWN);
	_defKeyID.emplace_back(KEY_INPUT_Z);
	_defKeyID.emplace_back(KEY_INPUT_X);
	_defKeyID.emplace_back(KEY_INPUT_A);
	_defKeyID.emplace_back(KEY_INPUT_S);

	/// ｷｰ情報の読み込み
	if (!LoadKeyData())
	{
		_keyID.reserve(static_cast<size_t>(end(INPUT_ID())));
		_keyID = _defKeyID;
	}

	/// 読み込みに失敗した時、ｷｰ情報をﾃﾞﾌｫﾙﾄに戻す
	for (auto id : INPUT_ID())
	{
		if (_keyID[static_cast<int>(id)] <= 0)
		{
			TRACE("一部ｷｰの読み込みに失敗しました。\n");
			ResetKeyData();
			break;
		}
	}
	_keyMode = &KeyState::RefKeyData;
}

KeyState::~KeyState()
{
	SaveKeyData();
}

void KeyState::Update()
{
	GetHitKeyStateAll(_buf);
	SetOld();
	(this->*_keyMode)();

	if (CheckHitKey(KEY_INPUT_F1) == 1 &&
		_keyMode == &KeyState::RefKeyData)
	{
		TRACE("ｷｰｺﾝﾌｨｸﾞﾓｰﾄﾞに移行する\n");
		/// IDとキー情報の初期化をしている
		for (auto id : INPUT_ID())	
		{
			state(id, 0);
			_keyID[static_cast<int>(id)] = 0;
		}

		_confID = begin(INPUT_ID());
		_keyMode = &KeyState::SetKeyData;
	}

	if (CheckHitKey(KEY_INPUT_DELETE) == 1 &&
		_keyMode == &KeyState::RefKeyData)
	{
		for (auto id : INPUT_ID())
		{
			if (_keyID[static_cast<int>(id)] != _defKeyID[static_cast<int>(id)])
			{
				TRACE("ｷｰ情報をﾘｾｯﾄする\n");
				_keyMode = &KeyState::ResetKeyData;
				break;
			}
		}
	}
}

bool KeyState::SaveKeyData()
{
	FILE *fp;
	if (fopen_s(&fp, "Data/key.dat", "wb") != 0)
	{
		return false;
	}
	fwrite(_keyID.data(), (_keyID.size() * sizeof(_keyID[0])), 1, fp);
	fclose(fp);

	return true;
}

bool KeyState::LoadKeyData()
{
	_keyID.resize(static_cast<size_t>(INPUT_ID::MAX));
			
	FILE *fp;
	if (fopen_s(&fp, "Data/key.dat", "rb") != 0)
	{
		return false;
	}
	fread(_keyID.data(), (_keyID.size() * sizeof(_keyID[0])), 1, fp);
	fclose(fp);

	return true;
}

void KeyState::RefKeyData()
{
	/// ボタンの入力情報の更新を行っている
	for (auto id : INPUT_ID())
	{
		state(id, _buf[_keyID[static_cast<int>(id)]]);
	}
}

void KeyState::ResetKeyData()
{
	_keyID = _defKeyID;
	_keyMode = &KeyState::RefKeyData;
}

void KeyState::SetKeyData()
{
	for (int id = 0; id < sizeof(_buf) / sizeof(_buf[0]); ++id)
	{
		if (_buf[id] && 
			!_buf[_lastKeyID] &&
			id != _lastKeyID && 
			id != KEY_INPUT_F1)
		{
			/// 絶対修正してやるぞ.....
			/// 同じｷｰが登録されていない時に登録するような判定を追加する
			_lastKeyID = id;
			_keyID[static_cast<int>(_confID)] = id;
			++_confID;
			TRACE("設定したｷｰ : " "%d\nｷｰのID :%d\n",_confID, id);
			break;
		}
	}
	
	if (_confID >= end(INPUT_ID()))
	{
		TRACE("ｷｰｺﾝﾌｨｸﾞ終了\n");
		/// ここでセーブ処理を行う????
		_keyMode = &KeyState::RefKeyData;
	}
}
