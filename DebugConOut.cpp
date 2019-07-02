#ifdef _DEBUG
#include "DebugConOut.h"

std::unique_ptr<DebugConOut, DebugConOut::DebugDeleter> DebugConOut::s_Instance(new DebugConOut());

DebugConOut::DebugConOut()
{
	/// �ݿ�ٳ���޳�̕\��
	if (AllocConsole())
	{
		/// �ݿ�ٳ���޳�ɑ΂��ē��o�͂��s�����߂̐ݒ�
		freopen_s(&_debugFp, "CONOUT$", "w", stdout);
		freopen_s(&_debugFp, "CONIN$", "r", stdin);
	}
}

DebugConOut::~DebugConOut()
{
	/// �ݿ�ٳ���޳�̊J��
 	FreeConsole();
}
#endif
