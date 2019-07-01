#include <DxLib.h>
#include "PadState.h"

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
	_padID = _defPadID;

	_padMode = &PadState::RefKeyData;
}

PadState::~PadState()
{
}

void PadState::Update()
{
	_inputPad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	SetOld();
	(this->*_padMode)();

	if (CheckHitKey(KEY_INPUT_F1) == 1)
	{
		_padID.clear();
		for (auto id : INPUT_ID())
		{
			state(id, 0);
		}
		_padMode = &PadState::SetKeyData;
	}

	if (CheckHitKey(KEY_INPUT_DELETE) == 1)
	{
		_padMode = &PadState::ResetKeyData;
	}
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
	auto num = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (num > 0)
	{
		_padID.emplace_back(num);
	}
	if (_padID.size() >= static_cast<int>(INPUT_ID::MAX))
	{
		_padMode = &PadState::RefKeyData;
	}
}
