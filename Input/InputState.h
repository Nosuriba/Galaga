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

	/// �Ǝ��ō��������
	bool IsTrigger(const INPUT_ID& id) const;
	bool IsPressing(const INPUT_ID& id) const;

	// ϯ�ߏ����擾�p
	const key_map& state() const;
	// �����̎擾�p
	const key_pair state(INPUT_ID id) const;
	// �����͂̏��擾�p
	bool state(INPUT_ID id, int data);

protected:
	// �O�ɓ��͂��������擾�p
	void SetOld(void);
	virtual void RefKeyData() = 0;
	virtual void ResetKeyData() = 0;
	virtual void SetKeyData() = 0;

private:
	// first : nowInput, second : oldInput
	key_map _state;
};

