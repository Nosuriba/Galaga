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

	/// ｷｰ入力の初期設定
	_keyID.reserve(static_cast<size_t>(end(INPUT_ID())));
	_keyID = _defKeyID;

	_keyMode = &KeyState::RefKeyData;
}

KeyState::~KeyState()
{
}

void KeyState::Update()
{
	GetHitKeyStateAll(_buf);
	SetOld();
	(this->*_keyMode)();

	if (CheckHitKey(KEY_INPUT_F1) == 1 &&
		_keyMode == &KeyState::RefKeyData)
	{
		TRACE("ｷｰｺﾝﾌｨｸﾞに移行する\n");
		/// IDとキー情報の初期化をしている
		_keyID.clear();
		for (auto id : INPUT_ID())
		{
			state(id, 0);
		}
		_keyMode = &KeyState::SetKeyData;
	}

	if (CheckHitKey(KEY_INPUT_DELETE) == 1 &&
		_keyMode == &KeyState::RefKeyData)
	{
		TRACE("ｷｰ情報をﾘｾｯﾄする\n");
		_keyMode = &KeyState::ResetKeyData;
	}
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
	if (CheckHitKeyAll() == 0)
	{
		auto num = WaitKey();
		for (auto key : _keyID)
		{
			if (key == num)
			{
				TRACE("同じｷｰが登録されています。\n");
				return;
			}
		}
		_keyID.emplace_back(num);
	}
	
	if (_keyID.size() >= static_cast<int>(INPUT_ID::MAX))
	{
		TRACE("%s", "ｷｰｺﾝﾌｨｸﾞ終了\n");
		_keyMode = &KeyState::RefKeyData;
	}
}
