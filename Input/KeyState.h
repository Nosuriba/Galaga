#pragma once
#include <vector>
#include "InputState.h"
class KeyState :
	public InputState
{
public:
	KeyState();
	~KeyState();

	void Update() override;
private:
	// ��[���𔽉f���邽�߂̂���(���O�͌�ŕς��邩��)
	void RefKeyData();
	void SetKeyConfig();
	char _buf[256];

	void (KeyState::*_keyMode)();

	std::vector<int> _keyID;
	// ��̫�ķ��̐ݒ�
	std::vector<int> _defKeyID;
};

