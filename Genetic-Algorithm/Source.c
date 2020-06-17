/*
������������ ������ ����� 5. ������������ ��������.
���������� ����, ���������� ������, ���-13��.

*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

#define GENOM_LEN 64
#define F_SIZE_L 45
#define F_SIZE_W 20

// ��� ������ ����
struct bot
{
	int genom[GENOM_LEN];
	int id; // ������������� 0..63
	int alive; // ��� �� ���
	int r, c; // row � col, ���������� ����
	int hp; // ����� ����� ����� 0..99
	int view; // ����������� ������� 0..7
	struct bot *next;
};

// ������ �����
typedef struct bots
{
	struct bot *first;	
} Bots;


// ��������� ��� ������� ����� ������������ ���������
int Init()
{

}


// ����� �� ��������� ����� ���������
int isEndGeneration ()
{

}


// ������������ ���� �����
int HandleBots ()
{

}


// ������� ���� � ��� ����������
int PrintInfo ()
{

}


// ���������, ����� �� ������������ �� �����
int isPause ()
{

}


// ������������� ���������
int StopSim ()
{

}


// ��������� �������� ��������� ������
int LittlePause ()
{

}


// ���������� ����� �����, ��������� � �������
int MainCycle ()
{
	// ������� ������ ��������� ������
	// (�� ������� �������)
	while (1)
	{
		while (!isEndGeneration ())  // ���� �� ���� ������ 8 �����
		{
			HandleBots ();  // ���������� ���� �����
			PrintInfo ();  // ������� ���������� ����
			if (isPause ())  // ���� ������������ ��������� ���������
			{
				StopSim ();  // �����, ����� ��� ���������� � ����
			}
			else
			{
				LittlePause ();  // ��������� Sleep (50), ����� �� ������� �����
			}
		}
	}
}


// ��������� ������ ���������
int Result ()
{

}


int main() {
	setlocale(LC_ALL, "RUS");
	
	Init ();
	MainCycle ();
	Result ();

	system("pause");
	return 0;
}
