#include "Header.h"
//#include "Brick.h"


	// ������ 

typedef enum _DIRECT {UP, UP_RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, UP_LEFT } DIRECT;

	enum ControlKeys
	{
		UP = 72,
		DOWN = 80,
		LEFT = 75,
		RIGHT = 77,
		SPACE = 32
	};

	// ����ü

	typedef struct _BALL
	{
		int X, Y;
		int IsReady; // �غ�? �̵�?
		int Life; 
		DIRECT Direction; // �� �̵�����
		clock_t MoveTime; 
		clock_t OldTime;
		
	} BALL;

	// ���� ����

	char *KeyInput[] = { "��", "�Ʒ�", "��", "��", "�����̽�" }; // KeyInput[k_Index]
	int k_Index = -1;

	BALL Ball;

	// �Լ�

	void Init()
	{

	}

	void Update()
	{

	}

	void Render()
	{
		ScreenClear();

		if (k_Index >= 0)
			ScreenPrint(10, 10, KeyInput[k_Index]);

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
					break;

				case RIGHT:
					k_Index = 3;
					break;

				case SPACE:
					k_Index = 4;
					break;
				}
			}
			Update();
			Render();
		}
	}
