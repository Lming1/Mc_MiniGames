#include "Header.h"
#include "Screen.h"
#include "FlyBall.h"

// ����ü ���� & ������
enum ControlKeys
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	SPACE = 32,
	ESC = 27
};

PLAYER Player;


// �Լ�
// Player�� �̵�
void PlayerMove(clock_t CurTime)
{
	char temp[20];
	if (Player.IsReady == 0) // �غ���°� �ƴϸ�
	{
		if (CurTime - Player.OldTime > Player.MoveTime) // �̵����ѽð� ���
		{
			Player.OldTime = CurTime;

			// ���⿡ ���� ��ǥ ��ȭ 
			switch (Player.Direction)
			{
			case TOP:
				sprintf(temp, "TOP");
				ScreenPrint(10, 2, temp);
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
			Player.Direction = TOP;
		//	Player.X = Bar.X[1];
		//	Player.Y = Bar.Y - 1;
		}
	}
	else // �غ� ���¸�
	{
	//	Player.X = Bar.X[1];
	//	Player.Y = Bar.Y - 1;
	}
}

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

	case 'S': case 's': // ��
		direction = 0;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	case 'D': case 'd': // ��
		direction = 1;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	case 'C': case 'c': // ��
		direction = 2;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	case 'X': case 'x': // ��
		direction = 3;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	case 'Z': case 'z': // ��
		direction = 4;
		Player.Direction = (DIRECT)direction;
		Player.OldTime = clock();
		break;

	case 'A': case 'a': // ��
		direction = 5;
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
	Player.X = 2;
	Player.Y = 2;
	Player.Direction = TOP;
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

	ScreenPrint(Player.X, Player.Y, "��");

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