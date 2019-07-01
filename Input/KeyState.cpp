#include <DxLib.h>
#include "KeyState.h"

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

	if (CheckHitKey(KEY_INPUT_F1) == 1)
	{
		/// _stateのIDを初期化するようにしておく
		_keyMode = &KeyState::SetKeyConfig;
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

void KeyState::SetKeyConfig()
{
	_keyID.clear();
}
