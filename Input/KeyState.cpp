#include <DxLib.h>
#include "KeyState.h"

KeyState::KeyState()
{

}

KeyState::~KeyState()
{
}

void KeyState::Update()
{
	GetHitKeyStateAll(_buf);

	for (int i = 0; i < _state.size(); ++i)
	{
		_state[INPUT_ID(i)].second = _state[INPUT_ID(i)].first;
	}

	_state[INPUT_ID::RIGHT].first = _buf[KEY_INPUT_RIGHT];
	_state[INPUT_ID::LEFT].first  = _buf[KEY_INPUT_LEFT];
	_state[INPUT_ID::DOWN].first  = _buf[KEY_INPUT_DOWN];
	_state[INPUT_ID::UP].first    = _buf[KEY_INPUT_UP];
	_state[INPUT_ID::BTN_1].first = _buf[KEY_INPUT_Z];
	_state[INPUT_ID::BTN_2].first = _buf[KEY_INPUT_X];
	_state[INPUT_ID::BTN_3].first = _buf[KEY_INPUT_A];
	_state[INPUT_ID::BTN_4].first = _buf[KEY_INPUT_S];
}

void KeyState::GetState()
{

}

