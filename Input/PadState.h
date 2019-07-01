#pragma once
#include "InputState.h"
class PadState :
	public InputState
{
public:
	PadState();
	~PadState();
	void Update() override;
private:
	void RefKeyData() override;
	void ResetKeyData() override;
	void SetKeyData() override;

	void (PadState::*_padMode)();

	int _inputPad;

	std::vector<int> _padID;
	std::vector<int> _defPadID;
};

