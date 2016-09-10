#include "Header.h"
#include "EqualCard.h"

// ���
const int CardCount = 12; // Card�� ����
const int TypeCount = 6; // Type�� ����

// ������
enum ControlKeys
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	SPACE = 32,
	ESC = 27
};

// ����ü���� & ����������
CARD Card[CardCount]; // Card ����
GAMESTATUS GameStatus;
BOARD Board;
CHOICE Choice;

// ��������
// Card ����
char PrintArray[TypeCount][3] = { "��" , "��" , "��" , "��" , "��" , "��" }; // Ÿ�Կ� ���� ��� �迭
char CoverPrint[3] = "��";
int ViewCard[2] = { -1, -1}; // ���̴� Card�� index ����
int selectChance; // ������ �� �ִ� ��ȸ
int matchCard; // ¦�� ���� Card

// Game ���� ����
clock_t OldTime; // Update �ð� ������
clock_t TurnTime = (clock_t) 1.2 * 1000; // Ŀ�� ���������� �ð�

// �Լ�

void CardOpening() // Card�� ���µǾ� �ִ� ������ �۾�
{
	clock_t CurTime = clock();

	if (IsEqualType()) // ���õ� �� ī���� Type�� ������
	{
		// ���� ī�� Count++
		matchCard++;

		// ViewCard -1 ó��
		ViewCard[0] = -1;
		ViewCard[1] = -1;
	}
	else // Type�� �ٸ���
	{
		// ���� �ð��� ���� ��, ViewCell[]�� -1 ���� �ʱ�ȭ�ϸ� Card[i].PrintForm = CoverPrint;
		if (CurTime - OldTime > TurnTime)
		{
			// Cover �ٽ� �����
			Card[ViewCard[0]].PrintForm = CoverPrint;
			Card[ViewCard[1]].PrintForm = CoverPrint;

			// ViewCard -1 ó��
			ViewCard[0] = -1;
			ViewCard[1] = -1;
		}
	}
}

bool IsEqualType() // ���� Type���� �Ǻ�
{
	if (Card[ViewCard[0]].Type == Card[ViewCard[1]].Type)
		return true;
	else
		return false;
}

void SelectCard()
{
	int select; // ���õ� ī��

	for (int i = 0; i < CardCount; i++) // ���õ� ī�� ã��
	{
		if ((Choice.select) == Card[i].CellNum)
			select = i;
	}

	// Card.select �� ���� Card ����
	// ���õ� ī��� Card[i].PrintForm = PrintArray[Card[i].Type]
	Card[select].PrintForm = PrintArray[Card[select].Type];

	// ViewCell[0] �Ǵ� ViewCell[1]�� Card�� index �Է�
	if (ViewCard[0] == -1)
	{
		ViewCard[0] = select;
	}
	else
	{
		ViewCard[1] = select;
		OldTime = clock();
	}

	selectChance--; // ������ ��ȸ ����
}

void AssignCoord()// ��ǥ �ο� �Լ�
{
	/*
	9 10 11 12
	5  6  7  8
	1  2  3  4
	*/

	// Choice ��ǥ �ο�
	switch (Choice.select)
	{
	case 1: // X, Y �ο�
		Choice.X = 21;
		Choice.Y = 16;
		break;

	case 2:
		Choice.X = 31;
		Choice.Y = 16;
		break;

	case 3:
		Choice.X = 41;
		Choice.Y = 16;
		break;

	case 4:
		Choice.X = 51;
		Choice.Y = 16;
		break;

	case 5:
		Choice.X = 21;
		Choice.Y = 12;
		break;

	case 6:
		Choice.X = 31;
		Choice.Y = 12;
		break;

	case 7:
		Choice.X = 41;
		Choice.Y = 12;
		break;

	case 8:
		Choice.X = 51;
		Choice.Y = 12;
		break;

	case 9:
		Choice.X = 21;
		Choice.Y = 8;
		break;

	case 10:
		Choice.X = 31;
		Choice.Y = 8;
		break;

	case 11:
		Choice.X = 41;
		Choice.Y = 8;
		break;

	case 12:
		Choice.X = 51;
		Choice.Y = 8;
		break;

	default:
		break;

	}

	// Card ��ǥ �ο�
	for (int index = 0; index < CardCount; index++)
	{
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

		default:
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

void AssignForm() // PrintForm �ο�
{
	for (int i = 0; i < CardCount; i++)
	{
		// Card[i].PrintForm = PrintArray[Card[i].Type]; // Type�� ���� PrintForm
		Card[i].PrintForm = CoverPrint; // Cover �����
	}
}

void CreateCard() // ī�� ���� �Լ�
{
	AssignCell(1, CardCount+1); // CellNum �ο� �Լ� (����. �ߺ�X)
	AssignCoord(); // CellNum�� ���� ��ǥ �ο�
	AssignType(0, TypeCount); // Type �ο� �Լ� (����. �ߺ� 1ȸ) 
	AssignForm();// PrintForm �ο�
}

void KeyControl(int key)
{
	// ��� ���¿���

	// RUNNING ���¿���
	switch (key)
	{
	case UP:
		if (Choice.select < 9)
			Choice.select += 4;
		break;

	case DOWN:
		if (Choice.select > 4)
			Choice.select -= 4;
		break;

	case LEFT:
		if ((Choice.select != 1) && (Choice.select != 5) && (Choice.select != 9))
		Choice.select--;
		break;

	case RIGHT:
		if ((Choice.select != 4) && (Choice.select != 8) && (Choice.select != 12))
		Choice.select++;
		break;

	case SPACE:
		if (ViewCard[1] == -1) // Card�� �� �� Open�� �ƴ϶��
		{
			SelectCard();
		}
		break;

	default:
		break;
	}
}

// �����ӿ�ũ �Լ�
void Init()
{
	// Card �ʱ�ȭ
	CreateCard();	// ī�� ���� �Լ� ( GameStatue == INIT �� ������? )
	matchCard = 0;

	// Chocie �ʱ�ȭ
	Choice.select = 9;

	// Board �ʱ�ȭ
	Board.leftX = 15;
	Board.rightX = BOARD_WIDTH - 15;
	Board.topY = 4;
	Board.bottomY = BOARD_HEIGH - 4;
	
	// Game ���� �ʱ�ȭ
	//GameStatus = START;
	selectChance = 30;
}

void Update()
{
	clock_t CurTime = clock();

	AssignCoord(); 

	if (ViewCard[1] != -1) // �� ī�尡 ��� Open
	{
		CardOpening();
	}
}

void Render()
{
	char BarPrint[100];

	ScreenClear();

	// GameStatus�� ���� ȭ�� ��� �Լ�
	
	// RUNNIG �� ��� ����

	// ���¹� ���
	sprintf(BarPrint, "���� ������ : %d     ���� ī�� : %d    ���� ī�� : %d" , selectChance, matchCard , (CardCount/2) - matchCard );
	ScreenPrint(16, 2, BarPrint);

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

	// Choice ���
	ScreenPrint(Choice.X, Choice.Y, "��");

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

			// key ����
			KeyControl(key);

		}

		Update();
		Render();
	}

	ScreenRelease();
	Release();
}