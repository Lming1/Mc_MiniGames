#include "Games\Header.h"
#include "Main.h"
#include "Games\Dodge.h"
#include "Games\Shoot.h"
#include "Games\Tetris.h"
#include "Games\Brick.h"

#pragma warning(disable:4996)

// ��������
char mainPrint[200];

// �Լ�
void Init()
{
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