#pragma once

// ����ü
typedef struct _STAGE
{
	int level; // Stage level
	// int �迭�� �ʱ�ȭ 
	int targetCount; // �� target�� ����
	int OCount; // O target�� ����
	int XCount; // X target�� ����
	int heartCount; // �� target�� ����
} STAGE;

typedef struct _TARGET_O
{
	int X;
	int Y;
} TARGET_O;

typedef struct _TARGET_X
{
	int X;
	int Y;
} TARGET_X;

typedef struct _TARGET_HEART
{
	int X;
	int Y;
} TARGET_HEART;

// ������
typedef enum _GAMESTATUS {START, INIT, READY, RUNNING, STOP, SUCCESS, FAILED, RESULT} GAMESTATUS;


// �Լ�����
void CreateTarget();

void Init();
void Update();
void Render();
void Release();
void Target();