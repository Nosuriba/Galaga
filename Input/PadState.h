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
	bool SaveKeyData() override;
	bool LoadKeyData() override;

	// ｷー情報を反映するためのもの(名前は後で変えるかも)
	void RefKeyData() override;
	void ResetKeyData() override;
	void SetKeyData() override;

	void (PadState::*_padMode)();

	int _inputPad;

	std::vector<int> _padID;
};

