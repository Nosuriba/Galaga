#include <DxLib.h>
#include "Input.h"

Input::Input()
{
}


Input::~Input()
{
}

const bool Input::IsPressing(int p) const
{
	return inputKey & p;
}

const bool Input::IsTrigger(int p) const
{
	return (inputKey & p) && !(lastInputKey & p);
}

const bool Input::IsMousePressing(int p) const
{
	return mouseInput & p;
}

const bool Input::IsMouseTrigger(int p) const
{
	return (mouseInput & p) && !(lastMouseInput & p);
}

void Input::Update()
{
	lastInputKey   = inputKey;
	lastMouseInput = mouseInput;

	inputKey   = DxLib::GetJoypadInputState(DX_INPUT_KEY_PAD1);
	mouseInput = DxLib::GetMouseInput();

	//PAD_INPUT_DOWN�@	// ���`�F�b�N�}�X�N(���L�[ or �e���L�[�̂Q�L�[)
	//PAD_INPUT_LEFT�@	// ���`�F�b�N�}�X�N(���L�[ or �e���L�[�̂S�L�[)
	//PAD_INPUT_RIGHT�@	// ���`�F�b�N�}�X�N(�E�L�[ or �e���L�[�̂U�L�[)
	//PAD_INPUT_UP�@	// ���`�F�b�N�}�X�N(��L�[ or �e���L�[�̂W�L�[)
	//PAD_INPUT_1�@		// 1�{�^���`�F�b�N�}�X�N(�y�L�[)
	//PAD_INPUT_2�@		// 2�{�^���`�F�b�N�}�X�N(�w�L�[)
	//PAD_INPUT_3�@		// 3�{�^���`�F�b�N�}�X�N(�b�L�[)
	//PAD_INPUT_4�@		// 4�{�^���`�F�b�N�}�X�N(�`�L�[)
	//PAD_INPUT_5�@		// 5�{�^���`�F�b�N�}�X�N(�r�L�[)
	//PAD_INPUT_6�@		// 6�{�^���`�F�b�N�}�X�N(�c�L�[)
	//PAD_INPUT_7�@		// 7�{�^���`�F�b�N�}�X�N(�p�L�[)
	//PAD_INPUT_8�@		// 8�{�^���`�F�b�N�}�X�N(�v�L�[)
	//PAD_INPUT_9�@		// 9�{�^���`�F�b�N�}�X�N(�d�r�b�L�[)
	//PAD_INPUT_10�@	// 10�{�^���`�F�b�N�}�X�N(�X�y�[�X�L�[)
}
