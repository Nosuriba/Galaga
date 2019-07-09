#include <stdarg.h>
#include <DxLib.h>
#include "DebugDisp.h"

#ifdef _DEBUG
std::unique_ptr<DebugDisp, DebugDisp::DispDeleter> DebugDisp::s_Instance(new DebugDisp());

DebugDisp::DebugDisp()
{
	_alpha	   = 0;
	_waitTime  = 0;
	_dbgScreen = -1;
	_dispFlag  = true;
}

DebugDisp::~DebugDisp()
{
}

void DebugDisp::SetUp(int alpha)
{
	/// ｽｸﾘｰﾝが生成されていない時、生成を行う
	if (_dbgScreen == -1)
	{
		_dbgScreen = MakeScreen(LpGame.screenSize.x, LpGame.screenSize.y, true);
	}
	/// ｱﾙﾌｧ値の設定
	_alpha = alpha;
}

void DebugDisp::StartUp()
{
	_beforScr = GetDrawScreen();
	SetDrawScreen(_dbgScreen);
	ClsDrawScreen();
	SetDrawScreen(_beforScr);
}

void DebugDisp::AddDraw()
{
	if (CheckHitKey(KEY_INPUT_PGUP))
	{
		_dispFlag = true;
	}

	if (CheckHitKey(KEY_INPUT_PGDN))
	{
		_dispFlag = false;
	}

	if (_dispFlag)
	{
		LpGame.AddDrawQue({ _dbgScreen, 0, 0 });
	}

	WaitMode();
}

void DebugDisp::SetScreen()
{
	_beforScr = GetDrawScreen();
	SetDrawScreen(_dbgScreen);
}

void DebugDisp::RevScreen()
{
	SetDrawScreen(_beforScr);
}

void DebugDisp::WaitMode()
{
	/// 時間の加算
	if (CheckHitKey(KEY_INPUT_ADD))
	{
		if (CheckHitKey(KEY_INPUT_MULTIPLY))
		{
			_waitTime += 100;
		}
		else
		{
			++_waitTime;
		}
	}

	/// 時間の減算
	if (CheckHitKey(KEY_INPUT_SUBTRACT))
	{
		if (CheckHitKey(KEY_INPUT_MULTIPLY))
		{
			_waitTime = (_waitTime <= 0.0 ? 0 : _waitTime - 100);
		}
		else
		{
			_waitTime = (_waitTime <= 0.0 ? 0 : _waitTime - 1);
		}
	}

	/// 時間のﾘｾｯﾄ
	if (CheckHitKey(KEY_INPUT_DIVIDE))
	{
		_waitTime = 0;
	}

	if (_waitTime)
	{
		_dbgDrawString(LpGame.gameScreenPos.x + 100, LpGame.gameScreenPos.y, "スロウモード発動中", 0xffff00);
		_startTime = std::chrono::system_clock::now();
		do 
		{
			_endTime = std::chrono::system_clock::now();
			if (!ProcessMessage() && CheckHitKey(KEY_INPUT_ESCAPE))
			{
				/// do～whileの条件で書いておく
				break;
			}
		} while (std::chrono::duration_cast<std::chrono::milliseconds>(_endTime - _startTime).count() < _waitTime);
	}
}

int DebugDisp::DrawBox(int x1, int y1, int x2, int y2, unsigned int Color, int FillFlag)
{
	_beforScr = GetDrawScreen();
	SetDrawScreen(_dbgScreen);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	int rtnFlag = DxLib::DrawBox(x1 + LpGame.gameScreenPos.x, y1 + LpGame.gameScreenPos.y,
								 x2 + LpGame.gameScreenPos.x, y2 + LpGame.gameScreenPos.y,
								 Color, FillFlag);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawScreen(_beforScr);
	return rtnFlag;
}

int DebugDisp::DrawGraph(int x, int y, int GrHandle, int TransFlag)
{
	_beforScr = GetDrawScreen();
	SetDrawScreen(_dbgScreen);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	int rtnFlag = DxLib::DrawGraph(x + LpGame.gameScreenPos.x, y + LpGame.gameScreenPos.y, GrHandle, TransFlag);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawScreen(_beforScr);
	return rtnFlag;
}

int DebugDisp::DrawLine(int x1, int y1, int x2, int y2, unsigned int Color, int Thickness)
{
	_beforScr = GetDrawScreen();
	SetDrawScreen(_dbgScreen);
	/// とりあえず透過なし
	int rtnFlag = DxLib::DrawLine(x1 + LpGame.gameScreenPos.x, y1 + LpGame.gameScreenPos.y,
								  x2 + LpGame.gameScreenPos.x, y2 + LpGame.gameScreenPos.y,
								  Color, Thickness);
	SetDrawScreen(_beforScr);
	return rtnFlag;
}

int DebugDisp::DrawCircle(int x, int y, int r, unsigned int Color, int FillFlag, int LineThickness)
{
	_beforScr = GetDrawScreen();
	SetDrawScreen(_dbgScreen);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	int rtnFlag = DxLib::DrawCircle(x + LpGame.gameScreenPos.x, y + LpGame.gameScreenPos.y, r,
									Color, FillFlag, LineThickness);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawScreen(_beforScr);
	return rtnFlag;
}

int DebugDisp::DrawPixel(int x, int y, unsigned int Color)
{
	_beforScr = GetDrawScreen();
	SetDrawScreen(_dbgScreen);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	int rtnFlag = DxLib::DrawPixel(x + LpGame.gameScreenPos.x, y + LpGame.gameScreenPos.y, Color);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawScreen(_beforScr);
	return 0;
}

int DebugDisp::DrawString(int x, int y, const TCHAR * String, unsigned int Color, unsigned int EdgeColor)
{
	_beforScr = GetDrawScreen();
	SetDrawScreen(_dbgScreen);

	int rtnFlag = DxLib::DrawString(x, y, String, Color, EdgeColor);

	SetDrawScreen(_beforScr);
	return rtnFlag;
}
#endif