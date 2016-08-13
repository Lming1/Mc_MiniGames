#pragma once

	// ���

	#define BAR_FIRST_X 30 // Bar ù x[0]��ǥ
	#define BAR_FIRST_Y 20 // Bar ù y��ǥ

//	#define BLOCK_COUNT 20 // Block ���� 	

	#define BOARD_WIDTH 78
	#define BOARD_HEIGH 24

	// ������

	typedef enum _DIRECT { TOP, TOP_RIGHT, BOT_RIGHT, BOTTOM, BOT_LEFT, TOP_LEFT } DIRECT; // ���� ����. �ð����. 
	typedef enum _GAMESTAUTS { START, INIT, READY, RUNNING, STOP, SUCCESS, FAILED, RESULT} GAMESTATUS; // stage ����

	// ����ü

	typedef struct _WALL
	{
		int leftX; // ���� ��
		int rightX; // ������ ��
		int topY; // ���� ��
		int bottomY; // �Ʒ��� ��
	} WALL;

	typedef struct _STAGE
	{
		int BlockCount;
		int Level;
	} STAGE;

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
		int Life;
		int Length;
		clock_t OldTime;
		clock_t MoveTime;
	} BAR;

	typedef struct _BLOCK
	{
		int X;
		int Y;
		int Life;
	} BLOCK;

	// �Լ� ����

	void BallDirect(int);
	void Init();
	void Update();
	void Render();
	void Release();