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

	bool IsTrigger(const INPUT_ID& id) const;
	bool IsPressing(const INPUT_ID& id) const;

	// Ï¯Ìßî•ñ‚ğæ“¾—p
	const key_map& state() const;
	// ·°î•ñ‚Ìæ“¾—p
	const key_pair state(INPUT_ID id) const;
private:
	// “ü—Íî•ñ‚Ì“o˜^—p
	bool state(const INPUT_ID id, const key_pair key);
protected:
	// first : now, second : old
	key_map _state;
};

