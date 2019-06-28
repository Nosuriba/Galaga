#include <DxLib.h>
#include "KeyState.h"

KeyState::KeyState()
{
	/// ﾃﾞﾌｫﾙﾄのｷｰ設定
	_keyTable[static_cast<int>(INPUT_ID::LEFT)]  = KEY_INPUT_LEFT;
	_keyTable[static_cast<int>(INPUT_ID::RIGHT)] = KEY_INPUT_RIGHT;
	_keyTable[static_cast<int>(INPUT_ID::UP)]	 = KEY_INPUT_UP;
	_keyTable[static_cast<int>(INPUT_ID::DOWN)]  = KEY_INPUT_DOWN;
	_keyTable[static_cast<int>(INPUT_ID::BTN_1)] = KEY_INPUT_Z;
	_keyTable[static_cast<int>(INPUT_ID::BTN_2)] = KEY_INPUT_X;
	_keyTable[static_cast<int>(INPUT_ID::BTN_3)] = KEY_INPUT_A;
	_keyTable[static_cast<int>(INPUT_ID::BTN_4)] = KEY_INPUT_S;

	for (auto key : _keyTable)
	{
		_keyID.emplace_back(key);
	}
}

KeyState::~KeyState()
{
}

void KeyState::Update()
{
	GetHitKeyStateAll(_buf);

	SetOld();

	/// ボタンの入力情報の更新を行っている
	for (auto id : INPUT_ID())
	{
		state(id, _buf[_keyID[static_cast<int>(id)]]);
	}
}
