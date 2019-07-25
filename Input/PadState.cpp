#include <DxLib.h>
#include "PadState.h"
#include "../DebugConOut.h"

PadState::PadState()
{
	_defPadID.reserve(static_cast<size_t>(end(INPUT_ID())));
	_defPadID.emplace_back(PAD_INPUT_LEFT);
	_defPadID.emplace_back(PAD_INPUT_RIGHT);
	_defPadID.emplace_back(PAD_INPUT_UP);
	_defPadID.emplace_back(PAD_INPUT_DOWN);
	_defPadID.emplace_back(PAD_INPUT_A);
	_defPadID.emplace_back(PAD_INPUT_B);
	_defPadID.emplace_back(PAD_INPUT_X);
	_defPadID.emplace_back(PAD_INPUT_Y);

	_padID.reserve(static_cast<size_t>(end(INPUT_ID())));
	if (!LoadKeyData())
	{
		_padID = _defPadID;
	}

	/// �ǂݍ��݂Ɏ��s�������A��������̫�Ăɖ߂�
	for (auto id : INPUT_ID())
	{
		if (_padID[static_cast<int>(id)] <= 0)
		{
			TRACE("�ꕔ���̓ǂݍ��݂Ɏ��s���܂����B\n");
			TRACE("��̫�Ă̷��ɖ߂��܂�\n");
			_padID = _defPadID;
			break;
		}
	}

	_padMode = &PadState::RefKeyData;
}

PadState::~PadState()
{
	SaveKeyData();
}

void PadState::Update()
{
	_inputPad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	SetOld();
	(this->*_padMode)();

	if (CheckHitKey(KEY_INPUT_F1) == 1 &&
		_padMode == &PadState::RefKeyData)
	{
		TRACE("����̨��Ӱ�ނɈڍs����\n");
		_padID.clear();
		for (auto id : INPUT_ID())
		{
			state(id, 0);
		}
		_padMode = &PadState::SetKeyData;
	}

	if (CheckHitKey(KEY_INPUT_DELETE) == 1)
	{
		for (auto id : INPUT_ID())
		{
			if (_padID[static_cast<int>(id)] != _defPadID[static_cast<int>(id)])
			{
				TRACE("������ؾ�Ă���\n");
				_padMode = &PadState::ResetKeyData;
				break;
			}
		}
	}
}

bool PadState::SaveKeyData()
{
	FILE *fp;
	if (fopen_s(&fp, "Data/pad.dat", "wb") != 0)
	{
		return false;
	}
	fwrite(_padID.data(), (_padID.size() * sizeof(_padID[0])), 1, fp);
	fclose(fp);

	return true;
}

bool PadState::LoadKeyData()
{
	_padID.resize(static_cast<size_t>(INPUT_ID::MAX));

	FILE *fp;
	if (fopen_s(&fp, "Data/pad.dat", "rb") != 0)
	{
		return false;
	}
	fread(_padID.data(), (_padID.size() * sizeof(_padID[0])), 1, fp);
	fclose(fp);

	return true;
}

void PadState::RefKeyData()
{
	for (auto id : INPUT_ID())
	{
		state(id, _padID[(static_cast<int>(id))] & _inputPad);
	}
}

void PadState::ResetKeyData()
{
	_padID = _defPadID;
	_padMode = &PadState::RefKeyData;
}

void PadState::SetKeyData()
{
	if (_inputPad > 0)
	{
		for (auto pad : _padID)
		{
			if (pad == _inputPad &&
				_inputPad == _lastID)
			{
				TRACE("���������o�^����Ă��܂��B\n");
				return;
			}
		}
		_lastID = _inputPad;
		_padID.emplace_back(_inputPad);
	}

	if (_padID.size() >= static_cast<int>(INPUT_ID::MAX))
	{
		_padMode = &PadState::RefKeyData;
	}
}
