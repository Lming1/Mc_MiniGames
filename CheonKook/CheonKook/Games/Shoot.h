#pragma once
#include <time.h>

namespace SB_Shoot
{

	typedef struct _GOAL
	{
		int gMoveX, gMoveY;
		int gLength; //����� ���� 
		int gLineX[9]; //����� ���ν� ��ǥ 
		int gDistance; // ��� �̵��Ÿ� 
		clock_t MoveTime;
		clock_t OldTime;
	} GOAL;

	typedef struct _Ball
	{
		int ReadyB; // 1 = �غ�, 0 = �� 
		int bMoveX, bMoveY; //�� �̵� ��ǥ
		clock_t MoveTime; // �̵��� �ɸ� �ð�
		clock_t OldTime; // ���� �̵��ð� 
	} BALL;

	typedef struct _Player
	{
		int CenterX, CenterY; //X, Y ��ǥ ���� 
		int MoveX, MoveY; // X, Y ��ǥ �̵� 
		int X, Y; // X, Y ���� ��� ��ǥ �� 
		int Index; // �߽���ǥ�� �ε��� 
	} PLAYER;

	typedef struct _Position
	{
		int X, Y; // X, Y ���� ��ǥ 
	} Position;

	typedef struct _Effect
	{
		clock_t StartTime; // ȿ�� �߻� �ð�
		clock_t StayTime; // ȿ�� ���ӽð�
	}EFFECT;

	typedef enum _GameState { START, INIT, READY, RUNNING, STOP, SUCCESS, FAILED, RESULT } GameState;

	typedef struct _StageInfo // �������� �ʱ�ȭ ��, Init���� �ʱ�ȭ.
	{
		int GoalBall; // ��ǥ ���� ����
		clock_t LimitTime; // ���� �ð�
		int GD_Length; // ��� ����
		int GD_X; // ���� X��ǥ
		int GD_Y; // ���� Y��ǥ
		clock_t GD_MoveTime; // ��� �̵� �ð� ����
		int GD_Dist; // ��� �̵� �Ÿ� 
	} StageInfo;

	// �Լ�

	void Shoot();


}