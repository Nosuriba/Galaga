#include <DxLib.h>
#include "Game.h"

#ifdef _DEBUG
int main()
#else
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdLine)
#endif
{
	Game::GetInstance().Init();
	Game::GetInstance().Run();

	return 0;
}