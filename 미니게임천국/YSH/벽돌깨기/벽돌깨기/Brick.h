#pragma once


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

	// �Լ� ����
