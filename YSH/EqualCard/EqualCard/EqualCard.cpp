#include "Header.h"
#include "EqualCard.h"

// ����ü���� & ����������
CARD Card[9]; // Card 9�� 
GAMESTATUS GameStatus;

// ��������
const int CardCount = 9; // Card�� ����
char PrintArray[5][3] = { "��" , "��" , "��" , "��" , "J" }; // Ÿ�Կ� ���� ��� �迭
char TypeArray[5][7] = { "Heart", "Star", "Clover", "Spade" , "Joker" }; // Ÿ�� �̸� �迭 
 
// �Լ�

void AssignCoord(int index)// ��ǥ �ο� �Լ�
{
	switch (Card[index].CellNum)
	{
	case 1: // X, Y �ο�
		Card[index].X = 10;
		Card[index].Y = 20;
		break;

	case 2:
		Card[index].X = 13;
		Card[index].Y = 20;
		break;

	case 3:
		Card[index].X = 16;
		Card[index].Y = 20;
		break;

	case 4:
		Card[index].X = 10;
		Card[index].Y = 17;
		break;

	case 5:
		Card[index].X = 13;
		Card[index].Y = 17;
		break;

	case 6:
		Card[index].X = 16;
		Card[index].Y = 17;
		break;

	case 7:
		Card[index].X = 10;
		Card[index].Y = 13;
		break;

	case 8:
		Card[index].X = 13;
		Card[index].Y = 13;
		break;

	case 9:
		Card[index].X = 16;
		Card[index].Y = 13;
		break;
		
	}
}

bool OverlapCell(int start, int end, int num) // �ߺ� Cell�� �ִ°�?
{
	if (start == end)
		return false; 

	for (int i = start; i < end; i++)
	{
		if (Card[i].CellNum == num) // �ߺ� O
			return true;
	}

	return false; // �ߺ� X
}

int RandNumMake(int start, int end) // start ~ end ������ ���� ���� ����
{
	int num;
	srand((unsigned) time(NULL));

	num = (rand() % (end - start)) + start;

	return num;
}

void AssignCell(int index) // CellNum �ο� �Լ�
{
	int randomNum;

	while (true)
	{
		randomNum = RandNumMake(0, CardCount); // 0 ~ CardCount ������ �� ���� ����

		if (OverlapCell(0, index, randomNum) == false) // �ߺ� Cell�� ������
			break;	
	}

	//Card[index].CellNum = randomNum;
}

void CreateCard() // ī�� ���� �Լ�
{
	for (int i = 0; i < CardCount; i++)
	{
		AssignCell(i); // CellNum �ο� �Լ� (����. �ߺ�X)
		//AssignCoord(i);// CellNum�� ���� ��ǥ �ο�
		// Type �ο� �Լ� (����. �ߺ� 1ȸ) 
		// Type�� ���� PrintForm �ο�
	}
}

// �����ӿ�ũ �Լ�
void Init()
{
	CreateCard();	// ī�� ���� �Լ� ( GameStatue == INIT �� ������? )
	
	// Game ���� �ʱ�ȭ
	//GameStatus = START;
}

void Update()
{

}

void Render()
{

	ScreenClear();

	// GameStatus�� ���� ȭ�� ��� �Լ�
	
	// RUNNIG �� ��� ����
/*	for (int i = 0; i < CardCount; i++)
	{
		ScreenPrint(Card[i].X, Card[i].Y, "T");
	}*/
	// test�� ��� ����
	char test[30];
	for (int i = 0; i < CardCount; i++)
	{
		sprintf(test, "card cell : " + Card[i].CellNum);
		ScreenPrint(30, i * 2, test);
	}
	// test�� ��� ����

	ScreenFlipping();
}

void Release()
{
}

void main()
{
	int key;

	Init();
	ScreenInit();

	while (1)
	{
		if (_kbhit()) // key �Է��� ������
		{
			key = _getch();

			if ((key == 'q') || (key == 'Q'))
				break;
		}

		Update();
		Render();
	}

	ScreenRelease();
	Release();
}