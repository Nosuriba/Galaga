#pragma once
#include <map>
#include <vector>
#include "INPUT_ID.h"

using key_pair = std::pair<int, int>;
using key_map = std::map<INPUT_ID, key_pair>;

class InputState
{
public:
	InputState();
	virtual ~InputState();
	virtual void Update() = 0;

	/// “Æ©‚Åì‚Á‚½‚à‚Ì
	bool IsTrigger(const INPUT_ID& id) const;
	bool IsPressing(const INPUT_ID& id) const;

	bool state(INPUT_ID id, int data);

protected:
	// ‘O‚É“ü—Í‚µ‚½·°î•ñæ“¾—p
	void SetOld(void);
	virtual bool SaveKeyData() = 0;
	virtual bool LoadKeyData() = 0;
	virtual void RefKeyData() = 0;
	virtual void ResetKeyData() = 0;
	virtual void SetKeyData() = 0;

	int _lastID;
private:
	// first : nowInput, second : oldInput
	key_map _state;
};

