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


// ���
const int PlayerFirstX = 10; // �÷��̾��� ���� X��ǥ
const int PlayerFirstY = 6; // �÷��̾��� ���� Y��ǥ
const int MaxBlockCount = 160; // Map�� ���� �ִ� Block ��
const int MAXMAPNUM = 6; // �ִ� Map ��

// ���� ����
int MapIndex; // ���� Map�� Index

// ����ü ����
BLOCK Block[MaxBlockCount];
BOARD Board;
PLAYER Player;
PORTAL Portal[4]; // ��, ��, ��, ��
GOAL Goal;
STARTP StartP;

// �迭
bool IsBlock[Board.Height / 2][Board.Width / 2] = { false, }; // Block ���� ��ġ �Ǻ� [20][8]

// �Լ�

// Start, Goal ���� Map ����
void SetStartGoal()
{
	srand((unsigned)time(NULL));

	StartP.whereMap = rand() % MAXMAPNUM;

	do
	{
		Goal.whereMap = rand() % MAXMAPNUM;
	} while (StartP.whereMap == Goal.whereMap);

}

// ���� Map ���� ����
void MapReset()
{
	// Player ����
	Player.X = PlayerFirstX;
	Player.Y = PlayerFirstY;
	Player.Direction = RIGHT;
	Player.OldTime = clock();
	Player.IsReady = 1;

	// Block ����
	for (int i = 0; i < Board.Height / 2; i++)
	{
		for (int j = 0; j < Board.Width / 2; j++)
		{
			IsBlock[i][j] = false;
		}
	}

	// Portal ����
	for (int i = 0; i < 4; i++)
	{
		Portal[i].IsEnable = false;
	}

	// Goal ����
	Goal.IsEnable = false;
}

// Portal Ȱ��ȭ �� ����
void SetPortal(int i)
{
	switch (i)
	{
	case 0: // ��
		Portal[i].IsEnable = true; // ��Ż Ȱ��ȭ
		Portal[i].nextMap = MapIndex - 1; // �̵� �� ����
		break;

	case 1: // ��
		Portal[i].IsEnable = true; // ��Ż Ȱ��ȭ
		Portal[i].nextMap = MapIndex + 2; // �̵� �� ����
		break;

	case 2: // ��
		Portal[i].IsEnable = true; // ��Ż Ȱ��ȭ
		Portal[i].nextMap = MapIndex + 1; // �̵� �� ����
		break;

	case 3: // ��
		Portal[i].IsEnable = true; // ��Ż Ȱ��ȭ
		Portal[i].nextMap = MapIndex - 2; // �̵� �� ����
		break;

	default:
		break;
	}
}

// Block ��ǥ ����
void AssignCoord(int k)
{
	for (int i = 0; i < Board.Height / 2; i++) // i��
	{
		for (int j = 0; j < Board.Width / 2; j++) // j��
		{
			if (IsBlock[i][j] == true) // MapMake()�� ���� ������ �� �ڸ�
			{
				// Block ��ǥ �ʱ�ȭ
				Block[k].X = Board.leftX + (j * 2) + 1;
				Block[k].Y = Board.topY + (i * 2) + 1;
				
				// �� �ڸ� false
				IsBlock[i][j] = false;

				// k��° Block ��ǥ �ʱ�ȭ ����
				return;
			} // if�� end
		} // for j end
	} // for i end
} 

// Block Map ����
void MapMake(int index)
{
	// Map ������ ���� �ٸ��� ����
	switch (index)
	{
	case 0: // Map0
			// bool IsBlock[][] �� true ������ [7][32]
		IsBlock[0][3] = IsBlock[0][7] = true; // 0
		IsBlock[1][4] = true; // 1
		 // 2
		IsBlock[3][5] = true; // 3
		// 4
		IsBlock[5][12] = true; // 5
		 // 6
		IsBlock[7][10] = true; // 7
		
		// ��Ż ���� 
		SetPortal(1);
		SetPortal(2);

		break;


	case 1:
		// bool IsBlock[][] �� true ������ [7][32]
		IsBlock[0][3] = IsBlock[0][7] = true; // 0
		IsBlock[1][4] = true; // 1
		 // 2
		IsBlock[3][5] = true; // 3
		// 4
		IsBlock[5][12] = true; // 5
		// 6
		// 7
		
		// ��Ż ���� 
		SetPortal(0);
		SetPortal(1);

		break;


	case 2:
		// bool IsBlock[][] �� true ������ [7][32]
		IsBlock[0][3] = true; // 0
		IsBlock[1][4] = true; // 1
		 // 2
		IsBlock[3][5] = true; // 3
		// 4
		IsBlock[5][12] = true; // 5
		// 6
		// 7

	  // ��Ż ���� (IsEnable, nextMap)
		SetPortal(1);
		SetPortal(2);
		SetPortal(3);

		break;


	case 3:
		// bool IsBlock[][] �� true ������ [7][32]
		// 0
		IsBlock[1][4] = true; // 1
		 // 2
		IsBlock[3][5] = true; // 3
		  // 4
		IsBlock[5][12] = true; // 5
		// 6
		// 7

		// ��Ż ���� (IsEnable, nextMap)
		SetPortal(0);
		SetPortal(1);
		SetPortal(3);

		break;


	case 4:
		// bool IsBlock[][] �� true ������ [7][32]
		// 0
		IsBlock[1][4] = true; // 1
		 // 2
		IsBlock[3][5] = true; // 3
		// 4
		// 5
		// 6
		// 7
		
		// ��Ż ���� (IsEnable, nextMap)
		SetPortal(2);
		SetPortal(3);

		break;


	case 5:
		// bool IsBlock[][] �� true ������ [7][32]
		// 0
		IsBlock[1][4] = true; // 1
		// 2
		// 3
		// 4
		// 5
		// 6
		// 7

		// ��Ż ���� (IsEnable, nextMap)
		SetPortal(0);
		SetPortal(3);

		break;

	default:
		break;
	}
}

// index�� �´� Map Block ����
void CreateBlock(int MapIndex)
{
	MapReset(); // ���� �� ����

	if (MapIndex == Goal.whereMap) // Goal Map �̸�
		Goal.IsEnable = true; // Goal Ȱ��ȭ

	MapMake(MapIndex); // �� ����
	for (int i = 0; i < MaxBlockCount; i++)
	{
		AssignCoord(i); // ��ǥ �ο�
	}
}

// �浹 üũ
int Collision(int x, int y)
{
	int count = 0;

	// Player�� Portal[i]�� �浹
	for (int i = 0; i < 4; i++)
	{
		if (Portal[i].IsEnable == false) // ��ȿ���� ���� ��Ż�̸�
			continue;

		if (Portal[i].Y == y) // y �Ǵ� y+1�� ����
		{
			if (Portal[i].X == x || Portal[i].X == (x + 1) ||
				(Portal[i].X + 1) == x || (Portal[i].X + 1) == (x + 1)) // x �Ǵ� x+1�� ����
			{
				// �浹 �� ����
				// Portal[i].nextMap�� ���� �� �̵�
				MapIndex = Portal[i].nextMap;
				CreateBlock(MapIndex);

				return 1; // �浹 O
			}
		}
	}
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

	// Player�� ���� �浹
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

	// Portal �ʱ�ȭ
	// ��
	Portal[0].X = 35; 
	Portal[0].Y = 6;
	// ��
	Portal[1].X = 70;
	Portal[1].Y = 10;
	// ��
	Portal[2].X = 35;
	Portal[2].Y = 18;
	// ��
	Portal[3].X = 10;
	Portal[3].Y = 10;

	for (int i = 0; i < 4; i++)
	{
		Portal[i].IsEnable = false; // ��� Portal ��Ȱ��ȭ
	}

	// Start, Goal ���� �ʱ�ȭ
	Goal.X = 70;
	Goal.Y = 18;
	SetStartGoal();

	// Map �ʱ�ȭ
	MapIndex = StartP.whereMap;
	CreateBlock(MapIndex);


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
	sprintf(TheTopBar, "�� �������� : %d | Life : %d  \t\t    [Map%d]", 1, /*Stage.Level + 1,*/ Player.Life, MapIndex);
	ScreenPrint(17, 2, TheTopBar);

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

	// Player ���
	ScreenPrint(Player.X, Player.Y, "��");

	// Block ���
	for (int i = 0; i < MaxBlockCount; i++)
	{
		if (Block[i].X == 0 && Block[i].Y == 0) continue; // ��ǥ�� �־����� ���� Block ǥ�� X
		ScreenPrint(Block[i].X, Block[i].Y, "��");
	}

	// Portal ���
	for (int i = 0; i < 4; i++)
	{
		if (Portal[i].IsEnable == false) // ��ȿ���� ���� ��Ż�̸�
			continue; 

		ScreenPrint(Portal[i].X, Portal[i].Y, "��");
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