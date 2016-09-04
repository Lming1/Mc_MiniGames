#include "Header.h"
#include "EqualCard.h"

// ���
const int CardCount = 12; // Card�� ����
const int TypeCount = 6; // Type�� ����

// ����ü���� & ����������
CARD Card[CardCount]; // Card ����
GAMESTATUS GameStatus;
BOARD Board;

// ��������
char PrintArray[TypeCount][3] = { "��" , "��" , "��" , "��" , "��" , "��" }; // Ÿ�Կ� ���� ��� �迭
//int TypeArray[TypeCount] = { 0, 1, 2, 3, 4, 5}; // Ÿ�� �̸� �迭 
// �Լ�

void AssignCoord()// ��ǥ �ο� �Լ�
{
	for (int index = 0; index < CardCount; index++)
	{
		/*
		9 10 11 12
		5  6  7  8 
		1  2  3  4
		*/
		switch (Card[index].CellNum)
		{
		case 1: // X, Y �ο�
			Card[index].X = 24;
			Card[index].Y = 16;
			break;

		case 2:
			Card[index].X = 34;
			Card[index].Y = 16;
			break;

		case 3:
			Card[index].X = 44;
			Card[index].Y = 16;
			break;

		case 4:
			Card[index].X = 54;
			Card[index].Y = 16;
			break;

		case 5:
			Card[index].X = 24;
			Card[index].Y = 12;
			break;

		case 6:
			Card[index].X = 34;
			Card[index].Y = 12;
			break;

		case 7:
			Card[index].X = 44;
			Card[index].Y = 12;
			break;

		case 8:
			Card[index].X = 54;
			Card[index].Y = 12;
			break;

		case 9:
			Card[index].X = 24;
			Card[index].Y = 8;
			break;

		case 10:
			Card[index].X = 34;
			Card[index].Y = 8;
			break;

		case 11:
			Card[index].X = 44;
			Card[index].Y = 8;
			break;

		case 12:
			Card[index].X = 54;
			Card[index].Y = 8;
			break;

		}
	}
}

void AssignCell(int start, int end) // start ~ end ������ ���� ���� ����
{
	int randomnum;
	bool IsOverlapCell[CardCount + 1 ] = { false, }; // �ߺ� �Ǻ��� bool �迭
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

void AssignType(int start, int end) // Type �ο� �Լ�
{
	int randomnum;
	int IsOverlapType[TypeCount] = { 0, }; // �ߺ� �Ǻ��� int �迭

	srand((unsigned)time(NULL));

	for (int i = 0; i < CardCount; )
	{
		randomnum = (rand() % (end - start)) + start; // start ~ end ������ ���� ����

		if (IsOverlapType[randomnum] < 2) // �ߺ� 0 ~ 1 ȸ
		{
			++IsOverlapType[randomnum]; // �ߺ� ǥ��
			Card[i].Type = randomnum; // �� ����
			++i; // ���� Card[i] �� �Ѿ
		} // if�� ����
	} // for�� ����

}

void AssignForm() // Type�� ���� PrintForm �ο�
{
	for (int i = 0; i < CardCount; i++)
	{
		Card[i].PrintForm = PrintArray[Card[i].Type];
	}
}

void CreateCard() // ī�� ���� �Լ�
{
	AssignCell(1, CardCount+1); // CellNum �ο� �Լ� (����. �ߺ�X)
	AssignCoord(); // CellNum�� ���� ��ǥ �ο�
	AssignType(0, TypeCount); // Type �ο� �Լ� (����. �ߺ� 1ȸ) 
	AssignForm();// Type�� ���� PrintForm �ο�
}

// �����ӿ�ũ �Լ�
void Init()
{
	CreateCard();	// ī�� ���� �Լ� ( GameStatue == INIT �� ������? )

	// Board �ʱ�ȭ
	Board.leftX = 15;
	Board.rightX = BOARD_WIDTH - 15;
	Board.topY = 4;
	Board.bottomY = BOARD_HEIGH - 4;
	
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
	
	// Board ���
	// ���𼭸�
	ScreenPrint(Board.leftX, Board.topY, "��"); // ���� ���
	ScreenPrint(Board.rightX, Board.topY, "��"); // ���� ���
	ScreenPrint(Board.leftX, Board.bottomY, "��"); // ���� �ϴ�
	ScreenPrint(Board.rightX, Board.bottomY, "��"); // ���� �ϴ�

	// ���Ʒ���
	for (int i = Board.leftX + 2; i < Board.rightX; i++)
	{
		ScreenPrint(i, Board.topY, "-");
		ScreenPrint(i, Board.bottomY, "-");
	}
	// �¿캮
	for (int i = Board.topY + 1; i < Board.bottomY; i++)
	{
		ScreenPrint(Board.leftX, i, "��");
		ScreenPrint(Board.rightX, i, "��");
	}

	// Card ���
	for (int i = 0; i < CardCount; i++)
	{
		ScreenPrint(Card[i].X, Card[i].Y, Card[i].PrintForm);
	}
	/*
	//test ����
	for (int i = 0; i < 4; i++)
	{
		ScreenPrint(24 + (10*i), 8, "��");
	}
	for (int i = 0; i < 3; i++)
	{
		ScreenPrint(24, 8 + (4*i), "��");
	}
	//test �� 
	*/

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