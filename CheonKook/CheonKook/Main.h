#pragma once

// ����ü
typedef struct _CHOICE
{
	int X;
	int Y;
	int select; // ���õ� ������
	clock_t OldTime;
	clock_t MoveTime;
} CHOICE;

// �Լ�����
void KeyControl(int);
void AssignCoord();
void SelectGame();

// �����ӿ�ũ �Լ�
void Init();
void Update();
void Render();
