#include "Header.h"
#include "Header2.h"
#include "Push.h"

namespace SB_Push
{

	enum ControlKeys
	{
		UP = 72,
		DOWN = 80,
		LEFT = 75,
		RIGHT = 77,
		SPACE = 32,
		ESC = 27
	};

//�������� ==============================+

	int Rx, Ry; // �÷��̾� ��ǥ
	int Round; // �����

	char stage[18][21];

	//=======================================+



	void LoadingStage() { //�ε�â

		int i;

		for (i = 0; i < 45; i++) {
			putchxy(10 + i, 5, '-');
			delay(10);
		}

		for (i = 0; i < 45; i++) {
			putchxy(70 - i, 10, '-');
			delay(10);
		}

		delay(800);

		gotoxy(35, 7);
		printf("P");
		delay(600);

		gotoxy(37, 7);
		printf("U");
		delay(600);

		gotoxy(39, 7);
		printf("S");
		delay(600);

		gotoxy(41, 7);
		printf("H");
		delay(600);

		putchxy(48, 8, 'M');
		delay(40);

		putchxy(49, 8, 'I');
		delay(40);

		putchxy(50, 8, 'N');
		delay(40);

		putchxy(51, 8, 'I');
		delay(40);

		putchxy(52, 8, 'G');
		delay(40);

		putchxy(53, 8, 'A');
		delay(40);

		putchxy(54, 8, 'M');
		delay(40);

		putchxy(55, 8, 'E');
		delay(40);

		gotoxy(57, 8);
		printf("��");
		delay(60);

		gotoxy(59, 8);
		printf("��");
		delay(60);

		gotoxy(61, 8);
		printf("��");
		delay(60);

		gotoxy(63, 8);
		printf("Ʈ");


		delay(2500);

		/*gotoxy(59, 8);
		printf("������Ʈ");
		delay(2500);
		*/
	}

	void DrawStage() { //x, y�� ������������ ��ǥ

		int x, y;

		for (y = 0; y < 18; y++) {
			for (x = 0; x < 20; x++) {
				putchxy(x, y, stage[y][x]);
			}
		}

		putchxy(Rx, Ry, '@');

	}


	void PlayerMove() {

		int dx, dy; //������ǥ

		char ch;

		ch = getchar();

		//ESC ������
		if (ch == ESC) {
			exit(0);
		}

		if (ch == -32) {
			ch = getchar();

			switch (ch)
			{
			case LEFT:
				dx = -1; dy = 0; break;

			case RIGHT:
				dx = 1; dy = 0; break;

			case UP:
				dx = 0; dy = -1; break;

			case DOWN:
				dx = 0; dy = 1; break;
			}
		}


		/*
		if (ch == LEFT) {
			dx = -1;
			dy = 0;
		}

		if (ch == RIGHT) {
			dx = 1;
			dy = 0;
		}

		if (ch == UP) {
			dx = 0;
			dy = -1;
		}

		if (ch == DOWN) {
			dx = 0;
			dy = 1;
		}


		*/
		if (stage[Ry + dy][Rx + dy] == '#') {
			return;
		}

		Rx += dx;
		Ry += dy;

	}



	//�� ================================ 18*21

	const char StageData[MAXSTAGE][18][21] = {
		{
		"####################",
		"####################",
		"####################",
		"####################",
		"####################",
		"####################",
		"##      ��       *#",
		"##      ��       *#",
		"##      ��       *#",
		"##   @  ��       *#",
		"##      ��       *#",
		"##      ��       *#",
		"##      ��       *#",
		"####################",
		"####################",
		"####################",
		"####################",
		"####################"
		},

		/*{
		"####################",
		"####################",
		"#####################",
		"#####################",
		"#####################",
		"#####################",
		"##      ��       *##",
		"##      ��       *##",
		"##      ��       *##",
		"##   @  ��       *##",
		"##      ��       *##",
		"##      ��       *##",
		"##      ��       *##",
		"#####################",
		"#####################",
		"#####################",
		"#####################",
		"#####################"
		}*/
	};


	//==============================================




	int Push() {

		int x, y; //�÷��̾��� �ǽð���ǥ

		setcursortype(NOCURSOR);

		LoadingStage();

		Round = 0;

		while (1) {
			memcpy(stage, StageData[Round], sizeof(stage));

			clrscr();


			for (y = 0; y < 18; y++) {

				for (x = 0; x < 20; x++) {

					if (stage[y][x] == '@') {

						Rx = x; //�÷��̾� ��ǥ����
						Ry = y; //�÷��̾� ��ǥ����
						stage[y][x] = ' '; //�������� �����

					}

				}
			}

			while (1) {

				DrawStage();
				PlayerMove();
			}
		}



		getchar();
		return 0;

	}
}