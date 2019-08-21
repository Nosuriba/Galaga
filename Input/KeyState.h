#pragma once
#include "InputState.h"

class KeyState :
	public InputState
{
public:
	KeyState();
	~KeyState();

	void Update() override;
private:
	bool SaveKeyData() override;
	bool LoadKeyData() override;

	// ��[���𔽉f���邽�߂̂���(���O�͌�ŕς��邩��)
	void RefKeyData() override;
	void ResetKeyData() override;
	void SetKeyData() override;
	char _buf[256];

	void (KeyState::*_keyMode)();

	// ��̫�ķ��̐ݒ�
	std::vector<int> _keyID;

	INPUT_ID _confID;
};

