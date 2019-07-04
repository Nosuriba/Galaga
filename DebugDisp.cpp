#include "DebugDisp.h"
#include <DxLib.h>

std::unique_ptr<DebugDisp, DebugDisp::DispDeleter> DebugDisp::s_Instance(new DebugDisp());

DebugDisp::DebugDisp()
{
	_alpha = 0;
	_dbgScreen = -1;
	_dispFlag = true;
}

DebugDisp::~DebugDisp()
{
}

void DebugDisp::SetUp(int alpha)
{
	/// ��ذ݂���������Ă��Ȃ����A�������s��
	if (_dbgScreen == -1)
	{
		_dbgScreen = MakeScreen(LpGame.screenSize.x, LpGame.screenSize.y, true);
	}
	/// ��̧�l�̐ݒ�
	_alpha = alpha;
}

void DebugDisp::StartUp()
{
	int _ghBefor = GetDrawScreen();
	SetDrawScreen(_dbgScreen);
	ClsDrawScreen();
	SetDrawScreen(_ghBefor);	
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
}

int DebugDisp::DrawBox(int x1, int y1, int x2, int y2, unsigned int Color, int FillFlag)
{
	int _ghBefor = GetDrawScreen();
	SetDrawScreen(_dbgScreen);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	int rtnFlag = DxLib::DrawBox(x1 + LpGame.gameScreenPos.x, y1 + LpGame.gameScreenPos.y,
								 x2 + LpGame.gameScreenPos.x, y2 + LpGame.gameScreenPos.y,
								 Color, FillFlag);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawScreen(_ghBefor);
	return rtnFlag;
	return 0;
}

int DebugDisp::DrawGraph(int x, int y, int GrHandle, int TransFlag)
{
	int _ghBefor = GetDrawScreen();
	SetDrawScreen(_dbgScreen);


	SetDrawScreen(_ghBefor);
	return 0;
}

int DebugDisp::DrawLine(int x1, int y1, int x2, int y2, unsigned int Color, int Thickness)
{
	return 0;
}

int DebugDisp::DrawCircle(int x, int y, int r, unsigned int Color, int FillFlag, int LineThickness)
{
	int _ghBefor = GetDrawScreen();
	SetDrawScreen(_dbgScreen);


	SetDrawScreen(_ghBefor);
	return 0;
}

int DebugDisp::DrawPixel(int x, int y, unsigned int Color)
{
	int _ghBefor = GetDrawScreen();
	SetDrawScreen(_dbgScreen);


	SetDrawScreen(_ghBefor);
	return 0;
}

int DebugDisp::DrawString(int x, int y, const TCHAR * String, unsigned int Color, unsigned int EdgeColor)
{
	int _ghBefor = GetDrawScreen();
	SetDrawScreen(_dbgScreen);


	SetDrawScreen(_ghBefor);
	return 0;
}

int DebugDisp::DrawFormatString(int x, int y, unsigned int Color, const TCHAR * FormatString, ...)
{
	int _ghBefor = GetDrawScreen();
	SetDrawScreen(_dbgScreen);


	SetDrawScreen(_ghBefor);
	return 0;
}
