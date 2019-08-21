#include <DxLib.h>
#include "KeyState.h"
#include "../DebugConOut.h"

KeyState::KeyState()
{
	/// ��̫�Ă̷��ݒ�
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

	/// �����̓ǂݍ���
	if (!LoadKeyData())
	{
		_inputID.reserve(static_cast<size_t>(end(INPUT_ID())));
		_inputID = _keyID;
	}

	/// �ǂݍ��݂Ɏ��s�������A��������̫�Ăɖ߂�
	for (auto id : INPUT_ID())
	{
		if (_inputID[static_cast<int>(id)] <= 0)
		{
			TRACE("�ꕔ���̓ǂݍ��݂Ɏ��s���܂����B\n");
			TRACE("��̫�Ă̷��ɖ߂��܂�\n");
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
		TRACE("����̨��Ӱ�ނɈڍs����\n");
		/// ID�ƃL�[���̏����������Ă���
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
				TRACE("������ؾ�Ă���\n");
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
	/// �{�^���̓��͏��̍X�V���s���Ă���
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
			TRACE("�ݒ肵���� : " "%d\n����ID :%d\n",_confID, id);
			break;
		}
	}
	
	if (_confID >= INPUT_ID::START)
	{
		TRACE("����̨�ޏI��\n");
		/// �����ŃZ�[�u�������s��????
		_keyMode = &KeyState::RefKeyData;
	}
}
