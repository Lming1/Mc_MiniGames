#include "Games\Header.h"
#include "Main.h"
#include "Games\Dodge.h"
#include "Games\Shoot.h"
#include "Games\Tetris.h"
#include "Games\Brick.h"

#pragma warning(disable:4996)

// ������
enum ControlKeys
{
	UP = 72,
	DOWN = 80,
	SPACE = 32
};

// ��������
// ���
int const distractorNum = 5; // ������ ����

// ����ü ����
CHOICE Choice;

// ��� ����
char mainPrint[200]; // �⺻ ��� ����
char choicePrint[3] = "��"; // ���� ǥ��

// �Լ�
void KeyControl(int key) // Ű ���� �Լ�
{
	switch (key)
	{
	case UP:
		if (Choice.select > 0)
			Choice.select--; // ���� �̵�
		else
			Choice.select = distractorNum - 1; // ���� �Ʒ��� �̵�

		break;

	case DOWN:
		if (Choice.select < distractorNum - 1)
			Choice.select++; // �Ʒ��� �̵�
		else
			Choice.select = 0; // ���� ���� �̵�

		break;

	default:
		break;
	}
}

void AssignCoord() // ��ǥ �ο� �Լ�
{
	switch (Choice.select)
	{
	case 0:
		Choice.X = 25;
		Choice.Y = 12;
		break;

	case 1:
		Choice.X = 25;
		Choice.Y = 13;
		break;

	case 2:
		Choice.X = 25;
		Choice.Y = 14;
		break;

	case 3:
		Choice.X = 25;
		Choice.Y = 15;
		break;

	case 4:
		Choice.X = 25;
		Choice.Y = 16;
		break;
		
	default:
		break;
	}
}

// �����ӿ�ũ �Լ�
void Init()
{
	// ���õ� ������ �ʱ�ȭ
	Choice.select = 0;

	// �⺻ ��� ���� �ʱ�ȭ
	sprintf(mainPrint,
		"\t\t [ �̴ϰ���õ�� ]\n\n\n\n"
		"\t\t\t- ������ �����ϼ��� - \n\n\n"
		"\t\t\t �� ����\n"
		"\t\t\t �� ��������\n"
		"\t\t\t �� ������\n"
		"\t\t\t �� ��Ʈ����\n"
		"\t\t\t �� ���Ұ�\n\n\n\n\n\n\n\n");
}

void Update()
{
	// �������� ���� ��ǥ �ο� �Լ�
}

void Render()
{
	ScreenClear();

	ScreenPrint(10, 10, mainPrint);
	
	ScreenFlipping();
}

void main()
{
	int key;

	ScreenInit();
	Init();

	while (1)
	{
		if (_kbhit())
		{
			key = _getch();

			if (key == 'q' || key == 'Q')
				break;

			// Ű ���� �Լ� -> ������ ����
		}

		Update();
		Render();
	}
}

void main2()
{
	int choice;
	bool qFlag = true;

	while (qFlag)
	{
		ScreenClear();

		printf("�̴ϰ����� �����ϼ���. Dodge(1) Shoot(2) Tetris(3) Brick(4) ������(5) \n");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			SH_Dodge::Dodge();
			break;

		case 2:
			SB_Shoot::Shoot();
			break;

		case 3:
			SB_Tetris::Tetris();
			break;

		case 4:
			SH_Brick::Brick();
			break;

		case 5:
			qFlag = false;
			break;

		default:
			break;
		}


		ScreenFlipping();
	}
	
}