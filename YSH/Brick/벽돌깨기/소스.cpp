#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "Screen.h"

typedef enum _DIRECT {
	TOP, LEFT_TOP, LEFT_DOWN, DOWN, RIGHT_DOWN,
	RIGHT_TOP
} DIRECT;
typedef struct _BALL
{
	int nReady;          // 1 �̸� �غ� ����, 0�̸� �̵� ����
	int  nHP;            // ����
	int  nX, nY;         // ��ǥ
	DIRECT  nDirect;     // �̵� ����
	clock_t  MoveTime;   // �̵� �ð� ����
	clock_t  OldTime;  // ���� �̵� �ð�
} BALL;

typedef struct _BAR
{
	int nX[3];
	int nY;
	clock_t OldTime;
	clock_t MoveTime;
} BAR;

BAR  g_sBar;
BALL g_sBall;

void Init()
{
	g_sBar.nY = 13;
	g_sBar.nX[0] = 30;
	g_sBar.nX[1] = 32;
	g_sBar.nX[2] = 34;
	g_sBar.MoveTime = 80;
	g_sBar.OldTime = clock();

	g_sBall.nX = g_sBar.nX[1];
	g_sBall.nY = g_sBar.nY - 1;
	g_sBall.nReady = 1; // �غ� ����
	g_sBall.nDirect = TOP;
	g_sBall.OldTime = clock();
	g_sBall.MoveTime = 100;
}

void Update()
{
	clock_t CurTime = clock();

	if (g_sBall.nReady == 0)
	{
		if (CurTime - g_sBall.OldTime > g_sBall.MoveTime)
		{
			g_sBall.OldTime = CurTime;

			switch (g_sBall.nDirect)
			{
			case TOP:
				g_sBall.nY--;
				break;
			case LEFT_TOP:
				g_sBall.nX++;
				g_sBall.nY--;
				break;
			case LEFT_DOWN:
				g_sBall.nX++;
				g_sBall.nY++;
				break;
			case DOWN:
				g_sBall.nY++;
				break;
			case RIGHT_DOWN:
				g_sBall.nX--;
				g_sBall.nY++;
				break;
			case RIGHT_TOP:
				g_sBall.nX--;
				g_sBall.nY--;
				break;
			}
		}

		// Note: ��� ������ �浹
		if (g_sBall.nX < 0 || g_sBall.nX > 78 || g_sBall.nY > 24 || g_sBall.nY < 0)
		{
			g_sBall.nReady = 1;
			g_sBall.nX = g_sBar.nX[1];
			g_sBall.nY = g_sBar.nY - 1;
			g_sBall.nDirect = TOP; // �⺻ ����
		}
	}
	else {
		g_sBall.nX = g_sBar.nX[1];
		g_sBall.nY = g_sBar.nY - 1;
	}
}

void Render()
{
	int i;
	ScreenClear();

	for (i = 0; i < 3; i++)
	{
		ScreenPrint(g_sBar.nX[i], g_sBar.nY, "��");
	}

	ScreenPrint(g_sBall.nX, g_sBall.nY, "��");

	ScreenFlipping();
}

void Release()
{
}

int main(void)
{
	int nKey, nDirect;
	clock_t CurTime;

	ScreenInit();
	Init();

	while (1)
	{
		if (_kbhit())
		{
			nKey = _getch();

			switch (nKey)
			{
			case 'k':
				g_sBall.nReady = 0;  // �̵� ����
				g_sBall.OldTime = clock();
				break;
			case 'j':
				CurTime = clock();
				if (CurTime - g_sBar.OldTime > g_sBar.MoveTime)
				{
					g_sBar.OldTime = CurTime;
					if (g_sBar.nX[0] > 0) // ��� ���� �浹 üũ
					{
						g_sBar.nX[0]--;
						g_sBar.nX[1]--;
						g_sBar.nX[2]--;
					}
				}
				break;
			case 'l':
				CurTime = clock();
				if (CurTime - g_sBar.OldTime > g_sBar.MoveTime)
				{
					g_sBar.OldTime = CurTime;
					if (g_sBar.nX[2] <= 77)  // ��� ���� üũ
					{
						g_sBar.nX[0]++;
						g_sBar.nX[1]++;
						g_sBar.nX[2]++;
					}
				}
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
				nDirect = nKey - '0';  // 0�������� 5������ ���������� ��ȯ
				g_sBall.nReady = 1;
				g_sBall.nX = g_sBar.nX[1];
				g_sBall.nY = g_sBar.nY - 1;
				g_sBall.nDirect = (DIRECT) nDirect;
				g_sBall.OldTime = clock();
				break;
			}
		}

		Update();
		Render();
	}

	Release();
	ScreenRelease();
	return 0;
}