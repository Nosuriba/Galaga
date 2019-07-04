#pragma once


#ifdef _DEBUG

#include <windows.h>
#include "Game.h"

#define _dbgSetUp(A)					(DebugDisp::GetInstance().SetUp(A))
#define _dbgStartUp						(DebugDisp::GetInstance().StartUp())
#define _dbgAddDraw						(DebugDisp::GetInstance().AddDraw())
#define _dbgDrawBox(fmt, ...)			(DebugDisp::GetInstance().DrawBox(fmt, __VA_ARGS__))
#define _dbgDrawGraph(fmt, ...)			(DebugDisp::GetInstance().DrawGraph(fmt, __VA_ARGS__))
#define _dbgDrawLine(fmt, ...)			(DebugDisp::GetInstance().DrawLine(fmt, __VA_ARGS__))
#define _dbgDrawCircle(fmt, ...)		(DebugDisp::GetInstance().DrawCircle(fmt, __VA_ARGS__))
#define _dbgDrawPixel(fmt, ...)			(DebugDisp::GetInstance().DrawPixel(fmt, __VA_ARGS__))
#define _dbgDrawString(fmt, ...)		(DebugDisp::GetInstance().DrawString(fmt, __VA_ARGS__))
#define _dbgDrawFormatString(fmt, ...)	(DebugDisp::GetInstance().DrawFormatString(fmt, __VA_ARGS__))

class DebugDisp
{
public:

	static DebugDisp & GetInstance()
	{
		return *s_Instance;
	}
	// ±ŸÃßílÇÃê›íË
	void SetUp(int alpha);

	// Ω∏ÿ∞›ÇÃèâä˙âª
	void StartUp();
	void AddDraw();

	int	DrawBox(int x1, int y1, int x2, int y2, unsigned int Color, int FillFlag);
	int	DrawGraph(int x, int y, int GrHandle, int TransFlag);
	int	DrawLine(int x1, int y1, int x2, int y2, unsigned int Color, int Thickness = 1);
	int	DrawCircle(int x, int y, int r, unsigned int Color, int FillFlag = true, int LineThickness = 1);
	int	DrawPixel(int x, int y, unsigned int Color);
	int	DrawString(int x, int y, const TCHAR *String, unsigned int Color, unsigned int EdgeColor = 0);
	int	DrawFormatString(int x, int y, unsigned int Color, const TCHAR *FormatString, ...);
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

	int _alpha;
	int _dbgScreen;
	bool _dispFlag;
};

#else
#define _dbgSetUp(A)					()
#define _dbgStartUp						()
#define _dbgAddDraw						()
#define _dbgDrawBox(fmt, ...)			()
#define _dbgDrawGraph(fmt, ...)			()
#define _dbgDrawLine(fmt, ...)			()
#define _dbgDrawCircle(fmt, ...)		()
#define _dbgDrawPixel(fmt, ...)			(DebugDisp::GetInstance().DrawPixel(fmt, ...))
#define _dbgDrawString(fmt, ...)		(DebugDisp::GetInstance().DrawString(fmt, ...))
#define _dbgDrawFormatString(fmt, ...)	(DebugDisp::GetInstance().DrawFormatString(fmt, ...))


#endif
