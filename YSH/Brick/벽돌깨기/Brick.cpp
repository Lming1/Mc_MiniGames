#include "Header.h"
#include "Brick.h"

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

// ����ü

// ���� ����

//����ü ����

BALL Ball;
BAR Bar;
BLOCK Block[30];
GAMESTATUS GameStatus;
STAGE Stage;
WALL Wall;

// ��� ����

char StatString[500]; // ȭ�� ��� ���� ����� char[]
int PrintTime = 3 * 1000;
clock_t Stat_OldTime = clock(); // PrintTime�� OldTime

// �÷��� ����

int BlockCountTable[3] = { 10, 15, 20 }; // Stage.Level �� ���� Block ����

int WallStateTable[4][6] = { // ������ �浹 �� ���� ��ȭ ���̺�
	{3, 2, -1, -1, -1, 4},
	{-1, 5, 4, -1, -1, -1},
	{-1, -1, 1, 0, 5, -1},
	{-1, -1, -1, -1, 2, 1}
};
int BlockStateTable[6] = { 3, 2, 1, 0, 5, 4 }; // ������ �浹 �� ���� ��ȭ ���̺�
 
// �Լ�

// ���¿� ���� ��ũ�� ���
void StatusPrint() 
{
	clock_t CurTime = clock();

	switch (GameStatus) 
	{
	case START:
		sprintf(StatString, "[START ȭ��]");
		ScreenPrint(30, 10, StatString);
		break;

	case INIT:
		// �������� �ʱ�ȭ
		
		// Stage.Level++; // SUCCESS , FAILED ���� Level ��ȭ 
		Stage.BlockCount = BlockCountTable[Stage.Level]; // Level�� ���� BlockCount�� �ٸ� 

		// ȭ�� ���

		if (CurTime - Stat_OldTime < PrintTime)
		{
			sprintf(StatString, "[INIT ȭ��]");
			ScreenPrint(30, 10, StatString);
		}
		else
		{
			GameStatus = READY;
			Stat_OldTime = CurTime;
		}
		break;

	case READY:
		if (CurTime - Stat_OldTime < PrintTime)
		{
			sprintf(StatString, "[READY ȭ��]");
			ScreenPrint(30, 10, StatString);
		}
		else
		{
			GameStatus = RUNNING;
			Stat_OldTime = CurTime;
		}
		break;

	case RUNNING:
		break;

	case STOP:
		sprintf(StatString, "[STOP ȭ��]");
		ScreenPrint(30, 10, StatString);
		break;

	case SUCCESS:
		sprintf(StatString, "SUCCESS ȭ��");
		break;

	case FAILED:
		sprintf(StatString, "FAILED ȭ��");
		break;

	case RESULT:
		sprintf(StatString, "RESULT ȭ��");
		break;

	}
}

// �浹 üũ
int Collision(int x, int y) 
{
	int count = 0; // �� �浹 ����

	// Ball�� Bar�� �浹

	for (int i = 0; i < Bar.Length; i++)
	{
		if (y == Bar.Y)
		{

			// X[0]�� �浹
			if ((x >= Bar.X[0] && x <= Bar.X[0] + 1) || ((x + 1) >= Bar.X[0] && (x + 1) <= Bar.X[0] + 1))
			{
				Ball.Direction = (DIRECT) 5;
				return 1;
			}
			// X[1]�� �浹
			if ((x >= Bar.X[1] && x <= Bar.X[1] + 1) || ((x + 1) >= Bar.X[1] && (x + 1) <= Bar.X[1] + 1))
			{
				Ball.Direction = (DIRECT)0;
				return 1;
			}
			// X[2]�� �浹
			if ((x >= Bar.X[2] && x <= Bar.X[2] + 1) || ((x + 1) >= Bar.X[2] && (x + 1) <= Bar.X[2] + 1))
			{
				Ball.Direction = (DIRECT)1;
				return 1;
			}
		}
	}

	// Ball�� Block�� �浹

	for (int i = 0; i < Stage.BlockCount; i++)
	{
		if (Block[i].Life > 0) // Life�� ���� Block�� ���ؼ�
		{
			if (Block[i].Y == y) // y�� ����
			{
				if (Block[i].X == x || Block[i].X == (x + 1) ||
					(Block[i].X + 1) == x || (Block[i].X + 1) == (x + 1)) // x �Ǵ� x+1�� ����
				{
					Ball.Direction = (DIRECT) BlockStateTable[Ball.Direction];
					Block[i].Life--;
					count++;
				}
			}
		}
	}
	
	if (count > 0)
		return 1;

	// Ball�� ���� �浹
	
	// �� ([0])
	if (y < Wall.topY + 1)
	{
		Ball.Direction = (DIRECT) WallStateTable[0][Ball.Direction];
		return 1; // �浹 O
	}
	
	// �� ([1])
	if (x > Wall.rightX - 1)
	{
		Ball.Direction = (DIRECT)WallStateTable[1][Ball.Direction];
		return 1;
	}
	
	// �� ([2])
	if (y > Wall.bottomY - 1)
	{
		// Ball ���� �ʱ�ȭ
		Ball.Direction = TOP;
		Ball.IsReady = 1;
		Ball.X = Bar.X[1];
		Ball.Y = Bar.Y - 1;

		Bar.Life--; // Bar ������ ����
		if (Bar.Life < 1) // �������� ������
		{
			GameStatus = FAILED; // �̼� ����
		}
		return 1;
	}

	// �� ([3])
	if (x < Wall.leftX + 1)
	{
		Ball.Direction = (DIRECT)WallStateTable[3][Ball.Direction];
		return 1;
	}

	return 0; // �浹 X
}

// �ߺ�Block ����?
int OverlapBlock(int End, int x, int y)  
{
	for (int i = 0; i < End; i++)
	{
		if (Block[i].Y == y) // y����
		{
			if (Block[i].X == x || (Block[i].X + 1) == x
				|| Block[i].X == (x + 1) || (Block[i].X + 1) == (x + 1)) // x����
				return 1; // �ߺ� ����
		}
	} // �ߺ� �˻� ����
	return 0; // �ߺ� ����
}

// Block ����
void SetBlock(int BlockCount)
	{
		int x, y, i;
		srand((unsigned)time(NULL));
		for (int i = 0; i < BlockCount; i++)
		{
			Block[i].Life = 1; // Block[i]�� Life ����

			while (1)
			{
				x = (rand() % (Wall.rightX - Wall.leftX - 1)) + Wall.leftX + 1; // Wall.leftX + 1 <= x < Wall �ʺ� - 1 + Wall.letfX + 1
				y = (rand() % 10) + Wall.topY + 1; // Wall.topY + 1 <= y < Wall.topY + 10 + 1

				if (OverlapBlock(i, x, y) == 0) // 0~i�� ������ �� �� �ߺ��� ������
				{
					Block[i].X = x;
					Block[i].Y = y;
					break;
				}
			} // while �� ��
		} // for�� ��
	}

// (RUNNING������) Ű����
void KeyControl(int key) 
	{
		clock_t CurTime = clock();
		int direction;
		
		if (CurTime - Bar.OldTime > Bar.MoveTime) // Ball �̵����ѽð� ��� �� 
		{
			switch (key)
			{
			case LEFT:
				Bar.OldTime = clock();
				if (Bar.X[0] > Wall.leftX + 1)
				{
					Bar.X[0]--;
					Bar.X[1]--;
					Bar.X[2]--;
				}
				break;

			case RIGHT:
				Bar.OldTime = clock();
				if (Bar.X[2] < Wall.rightX - 1)
				{
					Bar.X[0]++;
					Bar.X[1]++;
					Bar.X[2]++;
				}
				break;

			case SPACE:
				//(Ball.IsReady == 1) ? (Ball.IsReady = 0) : (Ball.IsReady = 1); // Ball.IsReady �ٲ� 
				if (Ball.IsReady == 1) 
				{
					Ball.OldTime = clock();
					Ball.IsReady = 0; // �غ� O -> �غ� X
				}
				break;

			case '0': case '1': case '2': case '3': case '4': case '5': // Ball ���� ���� 
				direction = key - '0';
				Ball.IsReady = 1;
				Ball.X = Bar.X[1];
				Ball.Y = Bar.Y - 1;
				Ball.Direction = (DIRECT) direction;
				Ball.OldTime = clock();
				break;

			default:
				break;
			}
		}

	}

// Ball�� �̵�
void BallMove(clock_t CurTime)
	{
		char temp[20];
		if (Ball.IsReady == 0) // �غ���°� �ƴϸ�
		{
			if (CurTime - Ball.OldTime > Ball.MoveTime) // �̵����ѽð� ���
			{
				Ball.OldTime = CurTime;

				// ���⿡ ���� ��ǥ ��ȭ 
				switch (Ball.Direction)
				{
				case TOP:
					sprintf(temp, "TOP");
					ScreenPrint(10, 2, temp);
					if (Collision(Ball.X, Ball.Y -1 ) == 0) // �̵��� ��ǥ���� �浹�� �� �Ͼ�� 
					{
						Ball.Y--; // �̵��Ѵ�
					}
					// �浹�� �Ͼ�� ���, Collision���� Ball.Direction�� ����ȴ�.
					break;

				case TOP_RIGHT:
					if (Collision(Ball.X + 1, Ball.Y - 1) == 0)
					{
						Ball.X++;
						Ball.Y--;
					}
					break;

				case BOT_RIGHT:
					if (Collision(Ball.X + 1, Ball.Y + 1)== 0)
					{
						Ball.X++;
						Ball.Y++;
					}
					break;

				case BOTTOM:
					if (Collision(Ball.X, Ball.Y + 1) == 0)
					{
						Ball.Y++;
					}
					break;

				case BOT_LEFT:
					if (Collision(Ball.X - 1, Ball.Y + 1) == 0)
					{
						Ball.X--;
						Ball.Y++;
					}
					break;

				case TOP_LEFT:
					if (Collision(Ball.X - 1, Ball.Y - 1) == 0)
					{
						Ball.X--;
						Ball.Y--;
					}
					break;

				}
			}
			if (Ball.X < 0 || Ball.X >BOARD_WIDTH || Ball.Y < 0 || Ball.Y > BOARD_HEIGH) // ���� �浹
			{
				Ball.IsReady = 1;
				Ball.Direction = TOP;
				Ball.X = Bar.X[1];
				Ball.Y = Bar.Y - 1;
			}
		}
		else // �غ� ���¸�
		{
			Ball.X = Bar.X[1];
			Ball.Y = Bar.Y - 1;
		}
	}

// �����ӿ�ũ �Լ�

void Init()
	{
		// �� �ʱ�ȭ
		Wall.leftX = 12;
		Wall.rightX = BOARD_WIDTH - 12;
		Wall.topY = 2;
		Wall.bottomY = BOARD_HEIGH - 1;

		// ���� �ʱ�ȭ
		GameStatus = START;
		
		// �������� �ʱ�ȭ -> StatusPrint() �� case INIT: 
		Stage.Level = 0;
		Stage.BlockCount = BlockCountTable[Stage.Level];

		// �� �ʱ�ȭ
		Bar.X[0] = 30;
		Bar.X[1] = 32;
		Bar.X[2] = 34;
		Bar.Y = 20;
		Bar.Life = 3;
		Bar.Length = 3;
		Bar.OldTime = clock();
		Bar.MoveTime = 30;

		// �� �ʱ�ȭ
		Ball.X = Bar.X[1];
		Ball.Y = Bar.Y-1;
		Ball.Direction = TOP;
		Ball.OldTime = clock();
		Ball.IsReady = 1;
		Ball.MoveTime = 100;

		// Block ����
		SetBlock(Stage.BlockCount);

	}

void Update()
	{
		clock_t CurTime = clock(); // ���� �ð�

		if (GameStatus == RUNNING)
		{
			BallMove(CurTime);// �� ������
		}
	}

void Render()
	{
		ScreenClear();
		
		StatusPrint();

		// ��ܹ� ���

		char TheTopBar[81];

		if (GameStatus == RUNNING || GameStatus == STOP)
		{
			sprintf(TheTopBar, "�� �������� : %d         Life : %d", Stage.Level + 1, Bar.Life);
			ScreenPrint(20 , 1, TheTopBar);

			// Wall ǥ��
			
			// ���𼭸�
			ScreenPrint(Wall.leftX, Wall.topY, "��"); // ���� ���
			ScreenPrint(Wall.rightX, Wall.topY, "��"); // ���� ���
			ScreenPrint(Wall.leftX, Wall.bottomY, "��"); // ���� �ϴ�
			ScreenPrint(Wall.rightX, Wall.bottomY, "��"); // ���� �ϴ�
			
														 // ���Ʒ���
			for (int i = Wall.leftX + 2; i <Wall.rightX ; i++)
			{
				ScreenPrint(i, Wall.topY, "-");
				ScreenPrint(i, Wall.bottomY, "-");
			}
			
			// �¿캮
			for (int i = Wall.topY + 1 ; i < Wall.bottomY; i++)
			{
				ScreenPrint(Wall.leftX, i, "��");
				ScreenPrint(Wall.rightX, i, "��");
			}

			ScreenPrint(Ball.X, Ball.Y, "��"); // Ball ǥ��

			for (int i = 0; i < Bar.Length; i++) // Bar ǥ��
			{
				ScreenPrint(Bar.X[i], Bar.Y, "��");
			}

			for (int i = 0; i < Stage.BlockCount; i++) // Block ǥ��
			{
				if (Block[i].Life > 0) // Life�� ����������
					ScreenPrint(Block[i].X, Block[i].Y, "��");
			}
		}

		ScreenFlipping();
	}

void Release()
	{

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

				if ((key == 'q') || (key == 'Q'))
					break;
				
				// RUNNING �� ���¿����� Ű����

				if (key == ESC)
				{
					switch (GameStatus)
					{
					case RUNNING:
						GameStatus = STOP;
						break;

					case STOP:
						GameStatus = RUNNING;
						break;

					default:
						break;
					}
				}

				if (key == SPACE) 
				{
					switch (GameStatus)
					{	
					case START:
						GameStatus = INIT;
						break;

					default:
						break;
					}	
				}

				// RUNNING ������ ���� Ű����

				if (GameStatus == RUNNING) 				
				{
					KeyControl(key);
				}

		}

		Update();
		Render();
	}
}
