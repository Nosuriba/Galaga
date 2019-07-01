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
	// ·[î•ñ‚ğ”½‰f‚·‚é‚½‚ß‚Ì‚à‚Ì(–¼‘O‚ÍŒã‚Å•Ï‚¦‚é‚©‚à)
	void RefKeyData();
	void SetKeyConfig();
	char _buf[256];

	void (KeyState::*_keyMode)();

	std::vector<int> _keyID;
	// ÃŞÌ«ÙÄ·°‚Ìİ’è
	std::vector<int> _defKeyID;
};

