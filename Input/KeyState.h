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
	char _buf[256];

	std::vector<int> _keyID;
	// ﾃﾞﾌｫﾙﾄｷーのﾃｰﾌﾞﾙ保存用
	int _keyTable[static_cast<int>(INPUT_ID::MAX)];
};

