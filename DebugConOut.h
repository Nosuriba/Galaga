#pragma once

/// debug中のみ、ｸﾗｽの生成を行う
#ifdef _DEBUG
#include <memory>
#include <Windows.h>

#define TRACE(fmt, ...) printf(fmt, __VA_ARGS__)		

/// ここにAST()の処理を書いて、try, catchエラーの対処ができるようにする

class DebugConOut
{
public:

	static DebugConOut & GetInstance()
	{
		return *s_Instance;
	}
private:
	DebugConOut();
	~DebugConOut();

	struct DebugDeleter
	{
		void operator()(DebugConOut * debug) const
		{
			delete debug;
		}
	};
	static std::unique_ptr<DebugConOut, DebugDeleter> s_Instance;

	FILE *_debugFp = nullptr;
};
#else
#define TRACE(fmt, ...)

#endif