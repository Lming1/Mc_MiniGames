#pragma once
#include <time.h>

namespace SH_Dodge
{
#define DotNum 17 // Dot�� ����
#define StageNum 3 // Stage ����
#define BOARD_WIDTH 80      // ȭ���� �ʺ�
#define BOARD_HEIGHT 25      // ȭ���� ����
#define Zero 50 // Stage==0 �� ���� Dot�� ��

	// ������ ����


	typedef enum _GAMESTATUS { START, INIT, READY, GO, RUNNING, STOP, NEXT, RESULT } GAMESTATUS;

	// ����ü ����

	typedef struct _PLAYER
	{
		int X, Y; // �÷��̾� ĳ������ X, Y ��ǥ
				  //	clock_t MoveTime;
		int InStop; // Stop����? OR Move ����?
		int Life; // Life.
				  //	int Crash; // Dot���� �浹. if (Crash==1) -> Life--; Crash=0;
	}PLAYER;

	typedef struct _DOT
	{
		int X, Y; // ���� X, Y ��ǥ
				  //	int Crash; // ���� �浹?
		clock_t MoveTime, OldTime;
		clock_t	Speed; // �ӵ�
		int DirectionX, DirectionY; // �̵�����
	}DOT;

	typedef struct _STAR
	{
		int X, Y; // Star�� X, Y ��ǥ
		int Catch; // Player�� Star�� ĳġ�� Ƚ��
		int SumCatch; // ��� ���������� Catch�� ��
	}STAR;


	// �Լ�

	void KeyControl(int);
	void IfCrash(int);
	void StarInit();
	void MoveCoord(int);
	void DotInit();
	void StatusPrint();
	void Init();
	void Update();
	void Render();
	void Release();
	void Dodge();

}