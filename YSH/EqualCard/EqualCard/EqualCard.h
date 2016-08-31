#pragma once

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

// �Լ� ����
void CreateCard();
void AssignCoord(int );
void AssignCell(int );
int RandNumMake(int , int );
bool OverlapCell(int );

// �����ӿ�ũ �Լ�
void Init();
void Update();
void Render();
void Release();
void EqualCard();