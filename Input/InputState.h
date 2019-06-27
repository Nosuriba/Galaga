#pragma once
#include <map>

enum class INPUT_ID
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	BTN_1,
	BTN_2,
	BTN_3,
	BTN_4,
	MAX
};

using key_pair = std::pair<int, int>;
using key_map = std::map<INPUT_ID, key_pair>;

class InputState
{
public:
	InputState();
	virtual ~InputState();
	virtual void Update() = 0;
	virtual void GetState() = 0;


	/// 入力情報の取得用
	const key_map& state() const;
	const key_pair state(INPUT_ID id) const;

	// 入力情報の登録用
	bool state(const INPUT_ID, const key_pair);
private:
	key_map _state;
};

