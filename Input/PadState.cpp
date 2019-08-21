#include <DxLib.h>
#include "PadState.h"
#include "../DebugConOut.h"

PadState::PadState()
{
	_padID.reserve(static_cast<size_t>(end(INPUT_ID())));
	_padID.emplace_back(PAD_INPUT_LEFT);
	_padID.emplace_back(PAD_INPUT_RIGHT);
	_padID.emplace_back(PAD_INPUT_UP);
	_padID.emplace_back(PAD_INPUT_DOWN);
	_padID.emplace_back(PAD_INPUT_A);
	_padID.emplace_back(PAD_INPUT_B);
	_padID.emplace_back(PAD_INPUT_X);
	_padID.emplace_back(PAD_INPUT_Y);
	_padID.emplace_back(PAD_INPUT_START);

	_inputID.reserve(static_cast<size_t>(end(INPUT_ID())));
	if (!LoadKeyData())
	{
		_inputID = _padID;
	}

	/// ì«Ç›çûÇ›Ç…é∏îsÇµÇΩéûÅA∑∞èÓïÒÇ√ﬁÃ´ŸƒÇ…ñﬂÇ∑
	for (auto id : INPUT_ID())
	{
		if (_inputID[static_cast<int>(id)] <= 0)
		{
			TRACE("àÍïî∑∞ÇÃì«Ç›çûÇ›Ç…é∏îsÇµÇ‹ÇµÇΩÅB\n");
			TRACE("√ﬁÃ´ŸƒÇÃ∑∞Ç…ñﬂÇµÇ‹Ç∑\n");
			_inputID = _padID;
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
		TRACE("∑∞∫›Ã®∏ﬁ”∞ƒﬁÇ…à⁄çsÇ∑ÇÈ\n");
		_inputID.clear();
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
			if (_inputID[static_cast<int>(id)] != _padID[static_cast<int>(id)])
			{
				TRACE("∑∞èÓïÒÇÿæØƒÇ∑ÇÈ\n");
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
	fwrite(_inputID.data(), (_inputID.size() * sizeof(_inputID[0])), 1, fp);
	fclose(fp);

	return true;
}

bool PadState::LoadKeyData()
{
	_inputID.resize(static_cast<size_t>(INPUT_ID::MAX));

	FILE *fp;
	if (fopen_s(&fp, "Data/pad.dat", "rb") != 0)
	{
		return false;
	}
	fread(_inputID.data(), (_inputID.size() * sizeof(_inputID[0])), 1, fp);
	fclose(fp);

	return true;
}

void PadState::RefKeyData()
{
	for (auto id : INPUT_ID())
	{
		state(id, _inputID[(static_cast<int>(id))] & _inputPad);
	}
}

void PadState::ResetKeyData()
{
	_inputID = _padID;
	_padMode = &PadState::RefKeyData;
}

void PadState::SetKeyData()
{
	if (_inputPad > 0)
	{
		for (auto pad : _inputID)
		{
			if (pad == _inputPad &&
				_inputPad == _lastID)
			{
				TRACE("ìØÇ∂∑∞Ç™ìoò^Ç≥ÇÍÇƒÇ¢Ç‹Ç∑ÅB\n");
				break;
			}
		}
		_lastID = _inputPad;
		_inputID.emplace_back(_inputPad);
	}

	if (_inputID.size() >= static_cast<int>(INPUT_ID::START))
	{
		_padMode = &PadState::RefKeyData;
	}
}
