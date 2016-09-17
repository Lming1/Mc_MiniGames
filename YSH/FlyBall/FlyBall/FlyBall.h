#pragma once

#define BOARD_WIDTH 78
#define BOARD_HEIGH 24

// ������
typedef enum _DIRECT { TOP, TOP_RIGHT, RIGHT, BOT_RIGHT, BOTTOM, BOT_LEFT, LEFT, TOP_LEFT } DIRECT; // ���� ����. �ð����. 

// ����ü
typedef struct _BLOCK
{
	int X;
	int Y;
} BLOCK;

typedef struct _GOAL
{
	int X;
	int Y;
} GOAL;

typedef struct _PLAYER
{
	int X, Y;
	int IsReady; // �غ�? �̵�?
	int Life;
	DIRECT Direction; // �� �̵�����
	clock_t MoveTime;
	clock_t OldTime;
} PLAYER;

// �Լ�����
void PlayerMove(clock_t );
void KeyControl(int);

void Init();
void Update();
void Render();
void FlyBall();