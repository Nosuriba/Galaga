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

	/// ̧�ٓǂݍ��݂Ɏ��s�������A��̫�Ēl������
	if (!LoadKeyData())
	{
		/// �����͂̏����ݒ�
		_keyID.reserve(static_cast<size_t>(end(INPUT_ID())));
		_keyID = _defKeyID;
	}
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
		TRACE("����̨��Ӱ�ނɈڍs����\n");
		/// ID�ƃL�[���̏����������Ă���
		for (auto id : INPUT_ID())
		{
			state(id, 0);
		}

		_confID = begin(INPUT_ID());
		_keyMode = &KeyState::SetKeyData;
	}

	if (CheckHitKey(KEY_INPUT_DELETE) == 1)
	{
		TRACE("������ؾ�Ă���\n");
		_keyMode = &KeyState::ResetKeyData;
	}
}

bool KeyState::SaveKeyData()
{
	/// ̧�ُ����o���̏���������
	FILE *fp;
	fopen_s(&fp, "Data/keyData.dat", "w");
	if (fp == NULL)
	{
		return false;
	}
	for (int i = 0; i < _keyID.size(); ++i)
	{
		/*fwrite();*/
	}

	return true;
}

bool KeyState::LoadKeyData()
{
	/// ̧�ق̓ǂݍ��݂̏���������
	_keyID.resize(static_cast<size_t>(INPUT_ID::MAX));

	return false;
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
	for (int id = 0; id < sizeof(_buf) / sizeof(_buf[0]); ++id)
	{
		if (_buf[id] && 
			id != _lastKeyID && 
			id != KEY_INPUT_F1)
		{
			/// ���������o�^����Ă��Ȃ����ɓo�^����悤�Ȕ����ǉ�����
			_lastKeyID = id;
			_keyID[static_cast<int>(_confID)] = id;
			++_confID;
			TRACE("�����o�^���ꂽ��\n");
			TRACE("�����o�^���ꂽ��\n");
			break;
		}
	}
	
	if (_confID >= end(INPUT_ID()))
	{
		TRACE("����̨�ޏI��\n");
		_keyMode = &KeyState::RefKeyData;
	}
}
