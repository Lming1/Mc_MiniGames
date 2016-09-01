#pragma once

#define BOARD_WIDTH 78
#define BOARD_HEIGH 24

// ������
typedef enum _GAMESTAUTS { START, INIT, READY, RUNNING, STOP, SUCCESS, FAILED, RESULT} GAMESTATUS;

// ����ü
typedef struct _CARD
{
	int X;
	int Y;
	int CellNum; // ǥ�õ� ��� 
	clock_t PrintTime; // ȭ�� ǥ�� �ð�
	clock_t OldTime;
	char* PrintForm; // ǥ�õǴ� ���
	char* Type; // ī�� Ÿ��
} CARD;

typedef struct _BOARD
{
	int leftX;
	int rightX;
	int topY;
	int bottomY;
	int one_forthX;
	int two_forthX;
	int three_forthX;
	int one_thirdY;
	int two_thirdY;
} BOARD;

// �Լ� ����
void CreateCard();
void AssignCell(int, int);

// �����ӿ�ũ �Լ�
void Init();
void Update();
void Render();
void Release();
void EqualCard();