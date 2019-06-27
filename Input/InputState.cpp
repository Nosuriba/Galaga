#include "InputState.h"

InputState::InputState()
{
	state(INPUT_ID::RIGHT, { 0,1 });
	state(INPUT_ID::LEFT,  { 0,1 });
	state(INPUT_ID::UP,    { 0,1 });
	state(INPUT_ID::DOWN,  { 0,1 });
	state(INPUT_ID::BTN_1, { 0,1 });
	state(INPUT_ID::BTN_2, { 0,1 });
	state(INPUT_ID::BTN_3, { 0,1 });
	state(INPUT_ID::BTN_4, { 0,1 });

}

InputState::~InputState()
{
}

bool InputState::IsTrigger(const INPUT_ID& id) const
{
	if (_state.find(id) == _state.end())
	{
		return false;
	}
	return (_state.at(id).first && !(_state.at(id).second));
}

bool InputState::IsPressing(const INPUT_ID& id) const
{
	if (_state.find(id) == _state.end())
	{
		return false;
	}
	return _state.at(id).first;
}

//const key_map & InputState::state() const
//{
//	return _state;
//}
//
//const key_pair InputState::state(INPUT_ID id) const
//{
//	if (_state.find(id) == _state.end())
//	{
//		return { 0, 0 };
//	}
//	return _state.at(id);
//}

bool InputState::state(const INPUT_ID id, const key_pair key)
{
	return _state.try_emplace(id, key).second;
}
