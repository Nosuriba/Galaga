#pragma once


#ifdef _DEBUG

#include <windows.h>
#include <chrono>			///
#include "Game.h"

#define _dbgSetUp(A)					(DebugDisp::GetInstance().SetUp(A))
#define _dbgStartUp						(DebugDisp::GetInstance().StartUp())
#define _dbgAddDraw						(DebugDisp::GetInstance().AddDraw())
#define _dbgWait						(DebugDisp::GetInstance().SetWait())
#define _dbgDrawBox(fmt, ...)			(DebugDisp::GetInstance().DrawBox(fmt, __VA_ARGS__))
#define _dbgDrawGraph(fmt, ...)			(DebugDisp::GetInstance().DrawGraph(fmt, __VA_ARGS__))
#define _dbgDrawLine(fmt, ...)			(DebugDisp::GetInstance().DrawLine(fmt, __VA_ARGS__))
#define _dbgDrawCircle(fmt, ...)		(DebugDisp::GetInstance().DrawCircle(fmt, __VA_ARGS__))
#define _dbgDrawPixel(fmt, ...)			(DebugDisp::GetInstance().DrawPixel(fmt, __VA_ARGS__))
#define _dbgDrawString(fmt, ...)		(DebugDisp::GetInstance().DrawString(fmt, __VA_ARGS__))
#define _dbgDrawFormatString(fmt, ...)	{\
										DebugDisp::GetInstance().SetScreen();\
										DxLib::DrawFormatString(fmt, __VA_ARGS__);\
										DebugDisp::GetInstance().RevScreen();\
										}


/// 時間計測用
using TimePoint = std::chrono::system_clock::time_point;

class DebugDisp
{
public:

	static DebugDisp & GetInstance()
	{
		return *s_Instance;
	}
	// ｱﾙﾌｧ値の設定
	void SetUp(int alpha);

	// ｽｸﾘｰﾝの初期化
	void StartUp();
	void AddDraw();

	/// ｹﾞｰﾑ中の待機時間の設定
	void SetWait();

	/// 外部で使ったら問題があるので、修正を考える
	void SetScreen();
	void RevScreen();

	int	DrawBox(int x1, int y1, int x2, int y2, unsigned int Color, int FillFlag);
	int	DrawGraph(int x, int y, int GrHandle, int TransFlag);
	int	DrawLine(int x1, int y1, int x2, int y2, unsigned int Color, int Thickness = 1);
	int	DrawCircle(int x, int y, int r, unsigned int Color, int FillFlag = true, int LineThickness = 1);
	int	DrawPixel(int x, int y, unsigned int Color);
	int	DrawString(int x, int y, const TCHAR *String, unsigned int Color, unsigned int EdgeColor = 0);
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
	int _beforScr;
	bool _dispFlag;

	/// 時間計測用
	TimePoint _startTime;
	TimePoint _endTime;

	double _waitTime;
};

#else
#define _dbgSetUp(A)					
#define _dbgStartUp					
#define _dbgAddDraw						
#define _dbgDrawBox(fmt, ...)			
#define _dbgDrawGraph(fmt, ...)			
#define _dbgDrawLine(fmt, ...)			
#define _dbgDrawCircle(fmt, ...)		
#define _dbgDrawPixel(fmt, ...)			
#define _dbgDrawString(fmt, ...)		
#define _dbgDrawFormatString(fmt, ...)	


#endif
