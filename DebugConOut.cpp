#ifdef _DEBUG
#include "DebugConOut.h"

std::unique_ptr<DebugConOut, DebugConOut::DebugDeleter> DebugConOut::s_Instance(new DebugConOut());

DebugConOut::DebugConOut()
{
	/// ｺﾝｿｰﾙｳｨﾝﾄﾞｳの表示
	if (AllocConsole())
	{
		/// ｺﾝｿｰﾙｳｨﾝﾄﾞｳに対して入出力を行うための設定
		freopen_s(&_debugFp, "CONOUT$", "w", stdout);
		freopen_s(&_debugFp, "CONIN$", "r", stdin);
	}
}

DebugConOut::~DebugConOut()
{
	/// ｺﾝｿｰﾙｳｨﾝﾄﾞｳの開放
 	FreeConsole();
}
#endif
