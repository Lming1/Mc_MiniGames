
#include "Header.h"

char print[500];

char rsp[5][50] = { "rock", "scissor", "paper" };
char result[20];

int computer;
int score = 0;

bool IsRPrint; // result�� ��� �Ǻ�
clock_t RPrintOldTime; // result print�� ������ �ð�


typedef struct _CHOICE {

	int select;
	int x;
	int y;

}CHOICE;

CHOICE Choice;

enum ControlKeys
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	SPACE = 32,
	ESC = 27
};

void Init() {
	sprintf(print, " \t---------\t\t---------\t\t---------\n"
		"\t   rock   \t\t scissor \t\t  paper \n"
		"\t---------\t\t---------\t\t---------\n");
	
	Choice.select = 1;

}//ȭ���ʱ�ȭ

void AssignCoord()
{

	switch (Choice.select) {

	case 1:
		Choice.x = 12;
		Choice.y = 5;
		break;

	case 2:
		Choice.x = 36;
		Choice.y = 5;
		break;

	case 3:
		Choice.x = 60;
		Choice.y = 5;
		break;
	}
}

void Update()
{
	AssignCoord();
}

void Render()
{
	clock_t CurTime = clock();

	ScreenClear();

	if (IsRPrint == true)
	{
		ScreenPrint(10, 10, result);

		// �ð� ���� �α�
		if (CurTime - RPrintOldTime >= 3 * 1000) // ��� �ð��� 3�ʰ� ������
		{
			IsRPrint = false; // ���̻� ����� �ʴ´�
		}
	}

	ScreenPrint(0, 0, print);
	
	ScreenPrint(Choice.x, Choice.y, "��");

	ScreenFlipping();
}

void SelectRSP() {
	
	computer = rand() % 3;

	if (Choice.select == (computer + 1) % 3) {
		sprintf(result, "Win!");
		score++;
	}
	else if (Choice.select == computer)
		sprintf(result, "Draw!");

	else sprintf(result, "Lose!");

	RPrintOldTime = clock(); // ������ ��� �ð��� ���� �ð����� ���� 
	IsRPrint = true; // result print ���

}
//��������������

void KeyControl(int key)
{
	switch (key)
	{
		case LEFT :
		{
			if (Choice.select >= 2)
				Choice.select--;
			else
				Choice.select = 3;
			break;
		}

		case RIGHT :
		{
			if (Choice.select <= 2)
				Choice.select++;
			else
				Choice.select = 1;
			break;
		}

		case SPACE :
		{
			
			SelectRSP();
			break;
		}
		default:
			break;

	}
}

void main() {

	int key;

	srand((unsigned)time(NULL));

	Init();
	ScreenInit();

	while (1) {

		if (_kbhit()) {

			key = _getch();

			if (key == 75 || key == 77 || key==32)
				KeyControl(key);
			
		}

		Update();
		Render();
	}
	
}




