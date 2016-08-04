#pragma once

	// ���

	#define BAR_FIRST_X 30 // Bar ù x[0]��ǥ
	#define BAR_FIRST_Y 20 // Bar ù y��ǥ

	#define BOARD_WIDTH 78
	#define BOARD_HEIGH 24

	// ������

	typedef enum _DIRECT { TOP, TOP_RIGHT, BOT_RIGHT, BOTTOM, BOT_LEFT, TOP_LEFT } DIRECT; // ���� ����. �ð����. 

	// ����ü

	typedef struct _BALL
	{
		int X, Y;
		int IsReady; // �غ�? �̵�?
		int Life;
		DIRECT Direction; // �� �̵�����
		clock_t MoveTime;
		clock_t OldTime;

	} BALL;

	typedef struct _BAR
	{
		int X[3];
		int Y;
		int Length;
		clock_t OldTime;
		clock_t MoveTime;
	} BAR;

	// �Լ� ����

	void BallDirect(int);