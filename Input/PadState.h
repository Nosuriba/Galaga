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

	// ��[���𔽉f���邽�߂̂���(���O�͌�ŕς��邩��)
	void RefKeyData() override;
	void ResetKeyData() override;
	void SetKeyData() override;

	void (PadState::*_padMode)();

	int _inputPad;

	std::vector<int> _padID;
	std::vector<int> _defPadID;
};

