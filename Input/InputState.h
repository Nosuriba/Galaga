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

	/// 独自で作ったもの
	bool IsTrigger(const INPUT_ID& id) const;
	bool IsPressing(const INPUT_ID& id) const;

	bool state(INPUT_ID id, int data);

protected:
	// 前に入力したｷｰ情報取得用
	void SetOld(void);
	virtual bool SaveKeyData() = 0;
	virtual bool LoadKeyData() = 0;
	virtual void RefKeyData() = 0;
	virtual void ResetKeyData() = 0;
	virtual void SetKeyData() = 0;

	int _lastID;
	std::vector<int> _inputID;

private:
	// first : nowInput, second : oldInput
	key_map _state;
};

