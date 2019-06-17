#include "Input.h"

Input::Input()
{
}

Input::~Input()
{
}

const bool Input::IsKeyPressing(char k) const
{
	return keyInput[k];
}

const bool Input::IsKeyTrigger(char k) const
{
	return keyInput[k] & !(keyInputOld[k]);
}

void Input::Update()
{
	memcpy(keyInputOld, keyInput, sizeof(keyInputOld));
	GetHitKeyStateAll(keyInput);
}
