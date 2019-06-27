#include "InputState.h"

InputState::InputState()
{
}

InputState::~InputState()
{
}

const key_map & InputState::state() const
{
	return _state;
}

const key_pair InputState::state(INPUT_ID id) const
{
	if (_state.find(id) == _state.end())
	{
		return { 0, 0 };
	}
	return _state.at(id);
}

bool InputState::state(const INPUT_ID id, const key_pair key)
{
	return _state.try_emplace(id, key).second;
}
