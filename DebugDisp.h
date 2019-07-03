#pragma once

#include <memory>

class DebugDisp
{
public:

	static DebugDisp & GetInstance()
	{
		return *s_Instance;
	}

private:
	DebugDisp();
	~DebugDisp();

	struct DispDeleter
	{
		void operator()(DebugDisp * disp)
		{
			delete disp;
		}
	};

	static std::unique_ptr<DebugDisp, DispDeleter> s_Instance;
};

