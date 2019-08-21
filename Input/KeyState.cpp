#include <DxLib.h>
#include "KeyState.h"
#include "../DebugConOut.h"

KeyState::KeyState()
{
	/// ﾃﾞﾌｫﾙﾄのｷｰ設定
	_keyID.reserve(static_cast<size_t>(end(INPUT_ID())));
	_keyID.emplace_back(KEY_INPUT_LEFT);
	_keyID.emplace_back(KEY_INPUT_RIGHT);
	_keyID.emplace_back(KEY_INPUT_UP);
	_keyID.emplace_back(KEY_INPUT_DOWN);
	_keyID.emplace_back(KEY_INPUT_Z);
	_keyID.emplace_back(KEY_INPUT_X);
	_keyID.emplace_back(KEY_INPUT_A);
	_keyID.emplace_back(KEY_INPUT_S);
	_keyID.emplace_back(KEY_INPUT_SPACE);

	/// ｷｰ情報の読み込み
	if (!LoadKeyData())
	{
		_inputID.reserve(static_cast<size_t>(end(INPUT_ID())));
		_inputID = _keyID;
	}

	/// 読み込みに失敗した時、ｷｰ情報をﾃﾞﾌｫﾙﾄに戻す
	for (auto id : INPUT_ID())
	{
		if (_inputID[static_cast<int>(id)] <= 0)
		{
			TRACE("一部ｷｰの読み込みに失敗しました。\n");
			TRACE("ﾃﾞﾌｫﾙﾄのｷｰに戻します\n");
			_inputID = _keyID;
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
			_inputID[static_cast<int>(id)] = 0;
		}

		_confID = begin(INPUT_ID());
		_keyMode = &KeyState::SetKeyData;
	}

	if (CheckHitKey(KEY_INPUT_DELETE) == 1 &&
		_keyMode == &KeyState::RefKeyData)
	{
		for (auto id : INPUT_ID())
		{
			if (_inputID[static_cast<int>(id)] != _keyID[static_cast<int>(id)])
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
	fwrite(_inputID.data(), (_inputID.size() * sizeof(_inputID[0])), 1, fp);
	fclose(fp);

	return true;
}

bool KeyState::LoadKeyData()
{
	_inputID.resize(static_cast<size_t>(INPUT_ID::MAX));
			
	FILE *fp;
	if (fopen_s(&fp, "Data/key.dat", "rb") != 0)
	{
		return false;
	}
	fread(_inputID.data(), (_inputID.size() * sizeof(_inputID[0])), 1, fp);
	fclose(fp);

	return true;
}

void KeyState::RefKeyData()
{
	/// ボタンの入力情報の更新を行っている
	for (auto id : INPUT_ID())
	{
		state(id, _buf[_inputID[static_cast<int>(id)]]);
	}
}

void KeyState::ResetKeyData()
{
	_inputID = _keyID;
	_keyMode = &KeyState::RefKeyData;
}

void KeyState::SetKeyData()
{
	for (int id = 0; id < sizeof(_buf) / sizeof(_buf[0]); ++id)
	{
		if (_buf[id] && 
			!_buf[_lastID] && 
			id != KEY_INPUT_F1 &&
			id != KEY_INPUT_DELETE)
		{
			_lastID = id;
			_inputID[static_cast<int>(_confID)] = id;
			++_confID;
			TRACE("設定したｷｰ : " "%d\nｷｰのID :%d\n",_confID, id);
			break;
		}
	}
	
	if (_confID >= INPUT_ID::START)
	{
		TRACE("ｷｰｺﾝﾌｨｸﾞ終了\n");
		/// ここでセーブ処理を行う????
		_keyMode = &KeyState::RefKeyData;
	}
}
