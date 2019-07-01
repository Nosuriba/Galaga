#include <DxLib.h>
#include "KeyState.h"
#include "../DebugConOut.h"

KeyState::KeyState()
{
	/// ��̫�Ă̷��ݒ�
	_defKeyID.reserve(static_cast<size_t>(end(INPUT_ID())));
	_defKeyID.emplace_back(KEY_INPUT_LEFT);
	_defKeyID.emplace_back(KEY_INPUT_RIGHT);
	_defKeyID.emplace_back(KEY_INPUT_UP);
	_defKeyID.emplace_back(KEY_INPUT_DOWN);
	_defKeyID.emplace_back(KEY_INPUT_Z);
	_defKeyID.emplace_back(KEY_INPUT_X);
	_defKeyID.emplace_back(KEY_INPUT_A);
	_defKeyID.emplace_back(KEY_INPUT_S);

	/// �����͂̏����ݒ�
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
		TRACE("����̨�ނɈڍs����\n");
		/// ID�ƃL�[���̏����������Ă���
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
		TRACE("������ؾ�Ă���\n");
		_keyMode = &KeyState::ResetKeyData;
	}
}

void KeyState::RefKeyData()
{
	/// �{�^���̓��͏��̍X�V���s���Ă���
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
				TRACE("���������o�^����Ă��܂��B\n");
				return;
			}
		}
		_keyID.emplace_back(num);
	}
	
	if (_keyID.size() >= static_cast<int>(INPUT_ID::MAX))
	{
		TRACE("%s", "����̨�ޏI��\n");
		_keyMode = &KeyState::RefKeyData;
	}
}
