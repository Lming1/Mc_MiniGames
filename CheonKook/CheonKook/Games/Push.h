#pragma once
#include "Header2.h"

namespace SB_Push
{
#define MAXSTAGE 1


	//+======================================+

#define putchxy(x,y,z) { gotoxy(x,y); _putch(z);} //gotoxy �Լ��� putch�Լ��� ����ü (.... �����Ƽ�)

	//+======================================+

	void LoadingStage();
	void DrawStage();
	void PlayerMove();
	int Push();
}