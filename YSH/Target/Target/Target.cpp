#include "Header.h"
#include "Target.h"


// ��������

// ����ü ����
STAGE Stage;
TARGET_O Target_O[10];
TARGET_X Target_X[10];
TARGET_HEART Target_heart[3];
GAMESTATUS GameStatus;

// ��� ����
int OArray[3] = {1,2,3};// O ���� �迭
int XArray[3] = {1,2,3};// X ���� �迭
						// ���� ��� Stage���� 3��

// �Լ�



void CreateTarget() // Target ���� �Լ�
{
	// O ����

	// X ����

	// �� ����
}

// �����ӿ�ũ �Լ�

void Init()
{
	// Target�� �ʱ�ȭ
	CreateTarget();

	// ���� ���� �ʱ�ȭ
	GameStatus = START;
}

void Update()
{

}

void Render()
{
	ScreenClear();

	ScreenFlipping();
}

void Release()
{

}

void main()
{
	int key;

	ScreenInit();
	Init();

	while (1)
	{
		if (_kbhit)
		{
			key = _getch();

			if (key == 'q' || key == 'Q')
				break;
		}

		Update();
		Render();
	}

	Release();
}