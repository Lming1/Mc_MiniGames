#include "Header.h"

namespace SH_Intro
{
	const int printStr = 24; // ������ �� ��� ���ڿ� ����
	const int strCount = 48; // ���ڿ� ����
	int startIndex; // ��� ���� �� 
	char IntroPrint[strCount][85]; // �Ұ� ����
	bool upFlag = true; // ȭ���� �ö󰡴°�?
	clock_t OldTime;
	clock_t PrintTime;

	void Init()
	{
		// clock_t �ʱ�ȭ
		OldTime = clock();
		PrintTime = 1 * 1000;

		// ��� ���� ��
		startIndex = 0;

		// 1������
		for (int i = 0; i < printStr; i++)
		{
			sprintf(IntroPrint[i], " \n");
		}

		// 2������ (24 ~ 47��) // ������� ����
		sprintf(IntroPrint[24], "�������");



		sprintf(IntroPrint[47], "�ٺ�");
	}

	void Render()
	{
		clock_t CurTime = clock();
		int j = 0;

		ScreenClear();


		for (int i = startIndex; i < startIndex + printStr - 1; i++, j++)
		{
			ScreenPrint(15, j, IntroPrint[i]); // (15,j) ������ ��� // ������� ����
		}

		if (upFlag == true)
		{
			if (CurTime - OldTime > PrintTime) // ���� �ö󰡴� �ð� : 2��
			{
				if (startIndex >= printStr)
					upFlag = false;

				startIndex++;

				OldTime = CurTime;
			}
		}

		ScreenFlipping();
	}

	void Intro()
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

			}

			Render();
		}
	}
}