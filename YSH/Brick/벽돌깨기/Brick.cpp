#include "Header.h"
#include "Brick.h"

	// ������ 

	enum ControlKeys
	{
		UP = 72,
		DOWN = 80,
		LEFT = 75,
		RIGHT = 77,
		SPACE = 32
	};

	// ����ü

	// ���� ����

	char *KeyInput[] = { "��", "�Ʒ�", "��", "��", "�����̽�" }; // KeyInput[k_Index]
	int k_Index = -1;

	BALL Ball;
	BAR Bar;

	// �Լ�

	void BallDirect(int key)
	{
		int direction;
		direction = key - '0';
		if (direction >= 0 && direction <= 5)
		{
			Ball.Direction = (DIRECT) direction;
			Ball.IsReady = 0;
		}
	}

	void KeyControl(int key) // Ű����
	{
		clock_t CurTime = clock();
		
		if (CurTime - Bar.OldTime > Bar.MoveTime)
		{
			switch (key)
			{
			case UP:
				k_Index = 0;
				break;

			case DOWN:
				k_Index = 1;
				break;

			case LEFT:
				k_Index = 2;
				if (Bar.X[0] > 0)
				{
					Bar.X[0]--;
					Bar.X[1]--;
					Bar.X[2]--;
				}
				break;

			case RIGHT:
				k_Index = 3;
				if (Bar.X[2] < BOARD_WIDTH)
				{
					Bar.X[0]++;
					Bar.X[1]++;
					Bar.X[2]++;
				}
				break;

			case SPACE:
				k_Index = 4;
				(Ball.IsReady == 0) ? (Ball.IsReady = 1) : (Ball.IsReady = 0); // Ball.IsReady �ٲ� 
				break;
			}
		}

		if (Ball.IsReady == 0)
			BallDirect(_getch()); // Ball�� ������ ����
	}

	void BallMove(clock_t CurTime) // Ball�� �̵�
	{
		if (Ball.IsReady == 0) // �غ���°� �ƴϸ�
		{
			if (CurTime - Ball.OldTime > Ball.MoveTime) // �̵����ѽð� ���
			{
				Ball.OldTime = CurTime;

				// ���⿡ ���� ��ǥ ��ȭ 
				switch (Ball.Direction)
				{
				case TOP:
					Ball.Y--;
					break;

				case TOP_RIGHT:
					Ball.X++;
					Ball.Y--;
					break;

				case BOT_RIGHT:
					Ball.X++;
					Ball.Y++;
					break;

				case BOTTOM:
					Ball.Y++;
					break;

				case BOT_LEFT:
					Ball.X--;
					Ball.Y++;
					break;

				}
			}
			if (Ball.X < 0 || Ball.X >BOARD_WIDTH || Ball.Y < 0 || Ball.Y > BOARD_HEIGH) // ���� �浹
			{
				Ball.IsReady = 1;
				Ball.X = FirstX;
				Ball.Y = FirstY;
			}
		}
	}

	// �����ӿ�ũ �Լ�

	void Init()
	{
		// �� �ʱ�ȭ
		Ball.X = FirstX;
		Ball.Y = FirstY;
		Ball.Direction = TOP;
		Ball.OldTime = clock();
		Ball.IsReady = 1;
		Ball.MoveTime = 200;

		// �� �ʱ�ȭ
		Bar.X[0] = 30;
		Bar.X[1] = 32;
		Bar.X[2] = 34;
		Bar.Y = 20;
		Bar.Length = 3;
		Bar.OldTime = clock();
		Bar.MoveTime = 100;
	}

	void Update()
	{
		clock_t CurTime = clock(); // ���� �ð�

		BallMove(CurTime);// �� ������
		
	}

	void Render()
	{
		ScreenClear();

		if (k_Index >= 0)
			ScreenPrint(10, 10, KeyInput[k_Index]);

		ScreenPrint(Ball.X, Ball.Y, "��"); // �� ǥ��
		for (int i = 0; i < Bar.Length; i++)
		{
			ScreenPrint(Bar.X[i], Bar.Y, "��");
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
				
				KeyControl(key);

			}
			Update();
			Render();
		}
	}
