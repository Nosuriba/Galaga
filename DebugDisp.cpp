#include "DebugDisp.h"

std::unique_ptr<DebugDisp, DebugDisp::DispDeleter> DebugDisp::s_Instance;

DebugDisp::DebugDisp()
{
}

DebugDisp::~DebugDisp()
{
}
