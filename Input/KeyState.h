#pragma once
#include "InputState.h"
class KeyState :
	public InputState
{
public:
	KeyState();
	~KeyState();

	void Update() override;
	void GetState() override;

private:
	void Init();

	char _buf[256];
	char _oldBuf[256];
};

