#pragma once
#include <map>
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

	// ﾏｯﾌﾟ情報を取得用
	const key_map& state() const;
	// ｷｰ情報の取得用
	const key_pair state(INPUT_ID id) const;
	// ｷｰ入力の情報取得用
	bool state(INPUT_ID id, int data);
	// 前に入力したｷｰ情報取得用
	void SetOld(void);
private:
	// first : nowInput, second : oldInput
	key_map _state;
};

