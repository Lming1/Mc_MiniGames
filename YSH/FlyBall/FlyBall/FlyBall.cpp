#include "Header.h"
#include "Screen.h"
#include "FlyBall.h"

// ����ü ���� & ������
enum ControlKeys
{
	UP = 72,
	DOWN = 80,
	//LEFT = 75,
	//RIGHT = 77,
	SPACE = 32,
	ESC = 27
};

PLAYER Player;

// ���� ����
// ���
const int PlayerFirstX = 10;
const int PlayerFirstY = 6;
const int MaxBlockCount = 160;

// ����ü ����
BLOCK Block[MaxBlockCount];
BOARD Board;


// �迭
bool IsBlock[Board.Height / 2][Board.Width / 2] = { false, }; // Block ���� ��ġ �Ǻ� [20][8]

// �Լ�

// Block ��ǥ ����
void AssignCoord(int k)
{
	for (int i = 0; i < Board.Height / 2; i++) // i��
	{
		for (int j = 0; j < Board.Width / 2; j++) // j��
		{
			if (IsBlock[i][j] == true)
			{
				Block[k].X = Board.leftX + (j * 2) + 1;
				Block[k].Y = Board.topY + (i * 2) + 1;
				IsBlock[i][j] = false;

				break;
			} // if�� end
		} // for j end
	} // for i end
} 

// Block Map ����
void MapMake()
{
	// bool IsBlock[][] �� true ������ [7][32]
	for (int i = 5; i < 30; i++) IsBlock[0][i] = true; // 0
	// 1
	// 2
	IsBlock[3][5] = true; // 3
	// 4
	// 5
	// 6
	// 7
}

// Block ����
void CreateBlock()
{
	MapMake();
	for (int i = 0; i < MaxBlockCount; i++)
	{
		AssignCoord(i);
	}
}

// �浹 üũ
int Collision(int x, int y)
{
	int count = 0;

	// Player�� Block�� �浹
	for (int i = 0; i < MaxBlockCount; i++)
	{
		if ((Block[i].Y == y) || (Block[i].Y == (y+1)) ||
			((Block[i].Y + 1) == y) || ((Block[i].Y + 1) == (y + 1))) // y �Ǵ� y+1�� ����
		{
			if (Block[i].X == x || Block[i].X == (x + 1) ||
				(Block[i].X + 1) == x || (Block[i].X + 1) == (x + 1)) // x �Ǵ� x+1�� ����
			{
				// �浹 �� ����
				Player.Life--; // Life ����

				// Player ���� �ʱ�ȭ
				Player.X = PlayerFirstX;
				Player.Y = PlayerFirstY;
				Player.Direction = RIGHT;
				Player.OldTime = clock();
				Player.IsReady = 1;

				if (Player.Life < 1) // �������� ������
				{
					//	GameStatus = FAILED; // �̼� ����
				}

				count++; // �浹üũ
			}
		}	
	}

	if (count > 0)
		return 1;

	// Ball�� ���� �浹
	if (y < Board.topY + 1 || x > Board.rightX - 1 || y > Board.bottomY - 1 || x < Board.leftX + 1)
	{	
		// �浹 �� ����
		Player.Life--; // Life ����

	    // Player ���� �ʱ�ȭ
		Player.X = PlayerFirstX;
		Player.Y = PlayerFirstY;
		Player.Direction = RIGHT;
		Player.OldTime = clock();
		Player.IsReady = 1;

		if (Player.Life < 1) // �������� ������
		{
		//	GameStatus = FAILED; // �̼� ����
		}
		return 1; // �浹 O
	}

	return 0; // �浹 X
}

// Player�� �̵�
void PlayerMove(clock_t CurTime)
{
	if (Player.IsReady == 0) // �غ���°� �ƴϸ�
	{
		if (CurTime - Player.OldTime > Player.MoveTime) // �̵����ѽð� ���
		{
			Player.OldTime = CurTime;

			// ���⿡ ���� ��ǥ ��ȭ 
			switch (Player.Direction)
			{
			case TOP:
				if (Collision(Player.X, Player.Y - 1) == 0) // �̵��� ��ǥ���� �浹�� �� �Ͼ�� 
				{
					Player.Y--; // �̵��Ѵ�
				}
				// �浹�� �Ͼ�� ���, Collision���� �浹 ó��
				break;

			case TOP_RIGHT:
				if (Collision(Player.X + 1, Player.Y - 1) == 0)
				{
					Player.X++;
					Player.Y--;
				}
				break;
				
			case RIGHT:
				if (Collision(Player.X + 2, Player.Y) == 0)
				{
					Player.X += 2;
				}
				break;

			case BOT_RIGHT:
				if (Collision(Player.X + 1, Player.Y + 1) == 0)
				{
					Player.X++;
					Player.Y++;
				}
				break;

			case BOTTOM:
				if (Collision(Player.X, Player.Y + 1) == 0)
				{
					Player.Y++;
				}
				break;

			case BOT_LEFT:
				if (Collision(Player.X - 1, Player.Y + 1) == 0)
				{
					Player.X--;
					Player.Y++;
				}
				break;

			case LEFT:
				if (Collision(Player.X - 2, Player.Y) == 0)
				{
					Player.X -= 2;
				}
				break;

			case TOP_LEFT:
				if (Collision(Player.X - 1, Player.Y - 1) == 0)
				{
					Player.X--;
					Player.Y--;
				}
				break;

			}
		}
		if (Player.X < 0 || Player.X >BOARD_WIDTH || Player.Y < 0 || Player.Y > BOARD_HEIGH) // ���� �浹
		{
			Player.IsReady = 1;
			Player.Direction = RIGHT;
			Player.X = PlayerFirstX;
			Player.Y = PlayerFirstY;
		}
	}
	else // �غ� ���¸�
	{
		Player.X = PlayerFirstX;
		Player.Y = PlayerFirstY;
	}
}

// Ű����
void KeyControl(int key)
{
	int direction;

	switch (key)
	{
	case SPACE:
		//(Player.IsReady == 1) ? (Player.IsReady = 0) : (Player.IsReady = 1); // Player.IsReady �ٲ� 
		if (Player.IsReady == 1)
		{
			Player.OldTime = clock();
			Player.IsReady = 0; // �غ� O -> �غ� X
		}
		break;

	case '8': // ��
		direction = 0;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	case '9': // ��
		direction = 1;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	case '6': // ��
		direction = 2;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	case '3': // ��
		direction = 3;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	case '2': // ��
		direction = 4;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	case '1': // ��
		direction = 5;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	case '4': // ��
		direction = 6;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	case '7': // ��
		direction = 7;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	default:
		break;
	}
}

// �����ӿ�ũ �Լ�
void Init()
{
	// Board �ʱ�ȭ
	Board.topY = 4;
	Board.bottomY = Board.topY + Board.Height;
	Board.leftX = 8;
	Board.rightX = Board.leftX + Board.Width;

	// Block �ʱ�ȭ
	CreateBlock();

	// Player �ʱ�ȭ
	Player.X = PlayerFirstX;
	Player.Y = PlayerFirstY;
	Player.Life = 3;
	Player.Direction = RIGHT;
	Player.OldTime = clock();
	Player.IsReady = 1;
	Player.MoveTime = 170;
}

void Update()
{
	clock_t CurTime = clock(); // ���� �ð�

	PlayerMove(CurTime);
}

void Render()
{
	ScreenClear();

	// ��ܹ� ���
	char TheTopBar[81];
	sprintf(TheTopBar, "�� �������� : %d | Life : %d", 1, /*Stage.Level + 1,*/ Player.Life);
	ScreenPrint(17, 1, TheTopBar);

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

	ScreenPrint(Player.X, Player.Y, "*");

	for (int i = 0; i < MaxBlockCount; i++)
	{
		if (Block[i].X == 0 && Block[i].Y == 0) continue; // ��ǥ�� �־����� ���� Block ǥ�� X
		ScreenPrint(Block[i].X, Block[i].Y, "��");
	}

	ScreenFlipping();
}

void main()
{
	int key;

	Init();
	ScreenInit();
	
	while (1)
	{
		if (_kbhit())
		{
			key = _getch();

			if (key == 'q' || key == 'Q')
				break;

			KeyControl(key);

		}

		Update();
		Render();
	}
}