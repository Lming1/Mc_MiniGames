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
	for (int index = 0; index < CardCount; index++)
	{
		switch (Card[index].CellNum)
		{
		case 1: // X, Y �ο�
			Card[index].X = 10;
			Card[index].Y = 15;
			break;

		case 2:
			Card[index].X = 13;
			Card[index].Y = 15;
			break;

		case 3:
			Card[index].X = 16;
			Card[index].Y = 15;
			break;

		case 4:
			Card[index].X = 10;
			Card[index].Y = 12;
			break;

		case 5:
			Card[index].X = 13;
			Card[index].Y = 12;
			break;

		case 6:
			Card[index].X = 16;
			Card[index].Y = 12;
			break;

		case 7:
			Card[index].X = 10;
			Card[index].Y = 9;
			break;

		case 8:
			Card[index].X = 13;
			Card[index].Y = 9;
			break;

		case 9:
			Card[index].X = 16;
			Card[index].Y = 9;
			break;

		}
	}
}

void AssignCell(int start, int end) // start ~ end ������ ���� ���� ����
{
	int randomnum;
	bool IsOverlapCell[10] = { false, }; // �ߺ� �Ǻ��� bool �迭
	srand((unsigned)time(NULL));

	for (int i = 0; i < CardCount; )
	{
		randomnum = (rand() % (end - start)) + start; // start ~ end ������ ���� ����

		if (IsOverlapCell[randomnum] == false) // �ߺ��� ���ٸ�
		{
			IsOverlapCell[randomnum] = true; // �ߺ� ǥ��
			Card[i].CellNum = randomnum; // �� ����
			++i; // ���� CellNum���� �Ѿ
		} // if�� ����
	} // for�� ����

} // �Լ� ����

void CreateCard() // ī�� ���� �Լ�
{
	AssignCell(1, CardCount+1); // CellNum �ο� �Լ� (����. �ߺ�X)
	AssignCoord();// CellNum�� ���� ��ǥ �ο�
	// Type �ο� �Լ� (����. �ߺ� 1ȸ) 
	// Type�� ���� PrintForm �ο�
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
	for (int i = 0; i < CardCount; i++)
	{
		ScreenPrint(Card[i].X, Card[i].Y, "T");
	}
	// test ����
	char test[20];
	for (int i = 0; i < CardCount; i++)
	{
		sprintf(test, "Cell %d : %d", i, Card[i].CellNum);
		ScreenPrint(30, i * 2, test);
	}
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