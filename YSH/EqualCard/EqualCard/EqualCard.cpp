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

void AssignCoord()// ��ǥ �ο� �Լ�
{
	for (int i = 0; i < CardCount; i++)
	{
		switch (Card[i].CellNum)
		{
		case 1: // X, Y �ο�
			break;

		case 2:
			break;

		case 3:
			break;

		case 4:
			break;

		case 5:
			break;

		case 6:
			break;

		case 7:
			break;

		case 8:
			break;

		case 9:
			break;
		}
	}
}


void AssignCell(int index) // CellNum �ο� �Լ�
{

}

void CreateCard() // ī�� ���� �Լ�
{
	for (int i = 0; i < CardCount; i++)
	{
		AssignCell(i); // CellNum �ο� �Լ� (����. �ߺ�X)
		// CellNum�� ���� ��ǥ �ο�
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

}

void Release()
{
	ScreenClear();

	// GameStatus�� ���� ȭ�� ��� �Լ�

	ScreenFlipping();
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