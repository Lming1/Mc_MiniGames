#pragma once

#define BOARD_WIDTH 78
#define BOARD_HEIGH 24

// ������
typedef enum _DIRECT { TOP, TOP_RIGHT, RIGHT, BOT_RIGHT, BOTTOM, BOT_LEFT, LEFT, TOP_LEFT } DIRECT; // ���� ����. �ð����. 

// ����ü
typedef struct _BOARD
{
	int topY;
	int bottomY;
	int leftX;
	int rightX;
	static const int Width = 64;
	static const int Height = 16;
} BOARD;

typedef struct _BLOCK
{
	int X;
	int Y;
} BLOCK;

typedef struct _PLAYER
{
	int X, Y;
	int IsReady; // �غ�? �̵�?
	int Life;
	DIRECT Direction; // �� �̵�����
	clock_t MoveTime;
	clock_t OldTime;
} PLAYER;

typedef struct _PORTAL
{
	int X, Y;
	int nextMap; // �̵��� ��
	bool IsEnable; // Ȱ��ȭ�� ��Ż�ΰ�?
} PORTAL;

// �Լ�����
void PlayerMove(clock_t );
void KeyControl(int);
void AssignCoord(int);
void MapMake(int );
void CreateBlock(int );
int Collision(int, int);
void SetPortal(int);

void Init();
void Update();
void Render();
void FlyBall();