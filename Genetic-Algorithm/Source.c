/*
������������ ������ ����� 5. ������������ ��������.
���������� ����, ���������� ������, ���-13��.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>


// ��������� ��� ������� ����� ������������ ���������
int Init()
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
			PrintField ();  // ������� ���������� ����
			if (isPause ())  // ���� ������������ ��������� ���������
			{
				StopSim ();  // �����, ����� ��� ���������� � ����
			}
			else
			{
				LittlePause ()  // ��������� Sleep (50), ����� �� ������� �����
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
	Main�ycle ();
	Result ();

	system("pause");
	return 0;
}
