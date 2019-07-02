#include <DxLib.h>
#include "KeyState.h"
#include "../DebugConOut.h"

KeyState::KeyState()
{
	/// ÃŞÌ«ÙÄ‚Ì·°İ’è
	_defKeyID.reserve(static_cast<size_t>(end(INPUT_ID())));
	_defKeyID.emplace_back(KEY_INPUT_LEFT);
	_defKeyID.emplace_back(KEY_INPUT_RIGHT);
	_defKeyID.emplace_back(KEY_INPUT_UP);
	_defKeyID.emplace_back(KEY_INPUT_DOWN);
	_defKeyID.emplace_back(KEY_INPUT_Z);
	_defKeyID.emplace_back(KEY_INPUT_X);
	_defKeyID.emplace_back(KEY_INPUT_A);
	_defKeyID.emplace_back(KEY_INPUT_S);

	/// ·°î•ñ‚Ì“o˜^
	if (!LoadKeyData())
	{
		_keyID.reserve(static_cast<size_t>(end(INPUT_ID())));
		_keyID = _defKeyID;
	}

	/// ÃŞ°À‚ÉƒL[î•ñ‚ª‚È‚©‚Á‚½‚Ì“o˜^
	for (auto id : INPUT_ID())
	{
		if (_keyID[static_cast<int>(id)] <= 0)
		{
			ResetKeyData();
			break;
		}
	}
	_keyMode = &KeyState::RefKeyData;
}

KeyState::~KeyState()
{
	SaveKeyData();
}

void KeyState::Update()
{
	GetHitKeyStateAll(_buf);
	SetOld();
	(this->*_keyMode)();

	if (CheckHitKey(KEY_INPUT_F1) == 1 &&
		_keyMode == &KeyState::RefKeyData)
	{
		TRACE("·°ºİÌ¨¸ŞÓ°ÄŞ‚ÉˆÚs‚·‚é\n");
		/// ID‚ÆƒL[î•ñ‚Ì‰Šú‰»‚ğ‚µ‚Ä‚¢‚é
		for (auto id : INPUT_ID())	
		{
			state(id, 0);
		}

		_confID = begin(INPUT_ID());
		_keyMode = &KeyState::SetKeyData;
	}

	if (CheckHitKey(KEY_INPUT_DELETE) == 1)
	{
		for (auto id : INPUT_ID())
		{
			if (_keyID[static_cast<int>(id)] != _defKeyID[static_cast<int>(id)])
			{
				TRACE("·°î•ñ‚ğØ¾¯Ä‚·‚é\n");
				_keyMode = &KeyState::ResetKeyData;
				break;
			}
		}
	}
}

bool KeyState::SaveKeyData()
{
	FILE *fp;
	if (fopen_s(&fp, "keyData.dat", "wb") != 0)
	{
		return false;
	}
	for (auto id : _keyID)
	{
		fwrite(&id, sizeof(_keyID[0]), 1, fp);
	}
	fclose(fp);

	return true;
}

bool KeyState::LoadKeyData()
{
	_keyID.resize(static_cast<size_t>(INPUT_ID::MAX));
			
	FILE *fp;
	if (fopen_s(&fp, "keyData.dat", "rb") != 0)
	{
		return false;
	}
	for (auto id : INPUT_ID())
	{
		fread(&_keyID[static_cast<size_t>(id)], sizeof(_keyID[0]), 1, fp);
	}
	fclose(fp);

	return true;
}

void KeyState::RefKeyData()
{
	/// ƒ{ƒ^ƒ“‚Ì“ü—Íî•ñ‚ÌXV‚ğs‚Á‚Ä‚¢‚é
	for (auto id : INPUT_ID())
	{
		state(id, _buf[_keyID[static_cast<int>(id)]]);
	}
}

void KeyState::ResetKeyData()
{
	_keyID = _defKeyID;
	_keyMode = &KeyState::RefKeyData;
}

void KeyState::SetKeyData()
{
	for (int id = 0; id < sizeof(_buf) / sizeof(_buf[0]); ++id)
	{
		if (_buf[id] && 
			!_buf[_lastKeyID] &&
			id != _lastKeyID && 
			id != KEY_INPUT_F1)
		{
			/// â‘ÎC³‚µ‚Ä‚â‚é‚¼.....
			/// “¯‚¶·°‚ª“o˜^‚³‚ê‚Ä‚¢‚È‚¢‚É“o˜^‚·‚é‚æ‚¤‚È”»’è‚ğ’Ç‰Á‚·‚é
			_lastKeyID = id;
			_keyID[static_cast<int>(_confID)] = id;
			++_confID;
			TRACE("İ’è‚µ‚½·° : " "%d\n", _confID);
			break;
		}
	}
	
	if (_confID >= end(INPUT_ID()))
	{
		TRACE("·°ºİÌ¨¸ŞI—¹\n");
		_keyMode = &KeyState::RefKeyData;
	}
}
