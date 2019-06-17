#pragma once

#include <DxLib.h>

class Input
{
public:
	Input();
	~Input();
	const bool IsKeyPressing(char k) const;
	const bool IsKeyTrigger(char k) const;

	void Update();
private:
	char keyInput[256];
	char keyInputOld[256];
};

