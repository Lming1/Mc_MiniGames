#include "Header.h"
#include "Target.h"

// �����ӿ�ũ �Լ�

void Init()
{

}

void Update()
{

}

void Render()
{
	ScreenClear();

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
		if (_kbhit)
		{
			key = _getch();

			if (key == 'q' || key == 'Q')
				break;
		}

		Update();
		Render();
	}

	Release();
}