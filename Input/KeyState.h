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

	// ｷー情報を反映するためのもの(名前は後で変えるかも)
	void RefKeyData() override;
	void ResetKeyData() override;
	void SetKeyData() override;
	char _buf[256];

	void (KeyState::*_keyMode)();

	// ﾃﾞﾌｫﾙﾄｷｰの設定
	std::vector<int> _keyID;

	INPUT_ID _confID;
};

