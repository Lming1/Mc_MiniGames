#pragma once

namespace SB_Tetris
{

#define true 1
#define false 0
#define bool int

#define BOARD_WIDTH 10        // ���� ������ ����(��) >= 10 : ��
#define BOARD_HEIGHT 20        // ���� ������ ����(��) >= 20 : | 

#define BOARD_X 4 //���� �� x��ǥ 
#define BOARD_Y 2 //���� �� y��ǥ

#define DELAY 100//����

	// �Լ�

	void CursorVisible(bool);
	void SetCursorPosition(int, int);
	COORD GetCursorPosition(void);
	void ConsoleInit();
	void DrawField(void);
	void ShowPoint(void);
	bool CanPositionedAt(int, int, int);
	void WriteBlock(int);
	void BoardInit(int , int , int );
	void Stepper(int);
	void CountScore(void);
	void RemoveLine(void);
	void ClearBlock(int rotation, int move1, int move2);
	void StartGame(void);
	void EndGame();
	void Tetris();


}