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
	// ｷー情報を反映するためのもの(名前は後で変えるかも)
	void RefKeyData();
	void SetKeyConfig();
	char _buf[256];

	void (KeyState::*_keyMode)();

	std::vector<int> _keyID;
	// ﾃﾞﾌｫﾙﾄｷｰの設定
	std::vector<int> _defKeyID;
};

