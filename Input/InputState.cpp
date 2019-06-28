#include "InputState.h"

InputState::InputState()
{
	for (auto id : INPUT_ID())
	{
		_state.try_emplace(id, key_pair{ 0,1 });
	}
}

InputState::~InputState()
{
}

bool InputState::IsTrigger(const INPUT_ID& id) const
{
	return _state.at(id).first && !(_state.at(id).second);
}

bool InputState::IsPressing(const INPUT_ID& id) const
{
	return _state.at(id).first;
}

const key_map & InputState::state() const
{
	return _state;
}

const key_pair InputState::state(INPUT_ID id) const
{
	try
	{
		return _state.at(id);
	}
	catch(...)
	{
	}
}

bool InputState::state(INPUT_ID id, int data)
{
	if (_state.find(id) == _state.end())
	{
		return false;
	}
	_state[id].first = data;
	return true;
}

void InputState::SetOld(void)
{
	for (auto id : INPUT_ID())
	{
		try
		{
			_state[id].second = _state[id].first;
		}
		catch (...)
		{
			/// ‰½‚à’l‚ª“ü—Í‚³‚ê‚Ä‚¢‚È‚¢Žž‚Ì•œ‹Œ—p
			//AST();
			_state.try_emplace(id, key_pair{ 0, 1 });
		}
		
	}
}