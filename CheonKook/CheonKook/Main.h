#pragma once

// ����ü
typedef struct _CHOICE
{
	int X;
	int Y;
	int select;
	clock_t OldTime;
	clock_t MoveTime;
} CHOICE;

// �Լ�����
void KeyControl(int);
void AssignCoord();

// �����ӿ�ũ �Լ�
void Init();
void Update();
void Render();
