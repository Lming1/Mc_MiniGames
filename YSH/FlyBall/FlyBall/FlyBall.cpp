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
const int PlayerFirstX = 8;
const int PlayerFirstY = 4;
const int MaxBlockCount = 30;

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
	// bool IsBlock[][] �� true ������ [7][19]
	IsBlock[7][19] = true;
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
				//if (Collision(Player.X, Player.Y - 1) == 0) // �̵��� ��ǥ���� �浹�� �� �Ͼ�� 
				{
					Player.Y--; // �̵��Ѵ�
				}
				// �浹�� �Ͼ�� ���, Collision���� Player.Direction�� ����ȴ�.
				break;

			case TOP_RIGHT:
				//if (Collision(Player.X + 1, Player.Y - 1) == 0)
				{
					Player.X++;
					Player.Y--;
				}
				break;
				
			case RIGHT:
				Player.X += 2;
				break;

			case BOT_RIGHT:
				//if (Collision(Player.X + 1, Player.Y + 1) == 0)
				{
					Player.X++;
					Player.Y++;
				}
				break;

			case BOTTOM:
				//if (Collision(Player.X, Player.Y + 1) == 0)
				{
					Player.Y++;
				}
				break;

			case BOT_LEFT:
				//if (Collision(Player.X - 1, Player.Y + 1) == 0)
				{
					Player.X--;
					Player.Y++;
				}
				break;

			case LEFT:
				Player.X -= 2;
				break;

			case TOP_LEFT:
				//if (Collision(Player.X - 1, Player.Y - 1) == 0)
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
	Board.topY = 2;
	Board.bottomY = Board.topY + Board.Height;
	Board.leftX = 6;
	Board.rightX = Board.leftX + Board.Width;

	// Block �ʱ�ȭ
	CreateBlock();

	// Player �ʱ�ȭ
	Player.X = PlayerFirstX;
	Player.Y = PlayerFirstY;
	Player.Direction = RIGHT;
	Player.OldTime = clock();
	Player.IsReady = 1;
	Player.MoveTime = 130;
}

void Update()
{
	clock_t CurTime = clock(); // ���� �ð�

	PlayerMove(CurTime);
}

void Render()
{
	ScreenClear();

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

	//ScreenPrint(Player.X, Player.Y, "��");

	//for (int i = 0; i < MaxBlockCount; i++)
	{
		ScreenPrint(Block[0].X, Block[0].Y, "��");
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