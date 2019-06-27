#include <DxLib.h>
#include "KeyState.h"

KeyState::KeyState()
{
	Init();
}

KeyState::~KeyState()
{
}

void KeyState::Init()
{
	state(INPUT_ID::RIGHT, { 0,1 });
	state(INPUT_ID::LEFT,  { 0,1 });
	state(INPUT_ID::UP,	   { 0,1 });
	state(INPUT_ID::DOWN,  { 0,1 });
	state(INPUT_ID::BTN_1, { 0,1 });
	state(INPUT_ID::BTN_2, { 0,1 });
	state(INPUT_ID::BTN_3, { 0,1 });
	state(INPUT_ID::BTN_4, { 0,1 });
}

void KeyState::Update()
{
	GetHitKeyStateAll(_buf);
}

void KeyState::GetState()
{
}

