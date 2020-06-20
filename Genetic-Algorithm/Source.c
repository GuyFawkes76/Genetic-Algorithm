/*
������������ ������ ����� 5. ������������ ��������.
���������� ����, ���������� ������, ���-13��.

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#define GENOM_LEN 64
#define BOTS_START_CNT 64
#define F_SIZE_HOR 45
#define F_SIZE_VERT 20
#define BOT_START_HP 40

// ��� ������ ����
typedef struct bot {
	int genom[GENOM_LEN];
	int id; // ������������� 0..63	
	int row, col; // row � col, ���������� ����
	int hp; // ����� ����� ����� 0..99
	int view; // ����������� ������� 0..7
	struct bot *next;
} Bot;

// ������ �����
typedef struct bots {
	Bot *first, *last;
} Bots;


// ���������� ��������� �����
int getRandomInt (int min, int max) {
	return rand() % (max - min + 1) + min;
}


// ������� ���������� ����
int createRandomBot (Bot *cur, int number) {
	int i;
	cur->next = NULL;
	cur->hp = BOT_START_HP;
	cur->id = number;
	cur->view = getRandomInt (0, 7);
	cur->col = getRandomInt (0, F_SIZE_HOR);
	cur->row = getRandomInt (0, F_SIZE_VERT);
	for (i = 0; i < GENOM_LEN; i++) {
		cur->genom[i] = getRandomInt (0, GENOM_LEN);
	}

	return 0;
}


int initBots (Bots **B) {
	int i;
	srand (time(NULL));
	Bots *newBotsList = malloc (sizeof (Bots));  // ������ ������ �����
	if (newBotsList == NULL)
		return 1;
	newBotsList->first = NULL;
	newBotsList->last = NULL;
	
	*B = newBotsList;

	Bot *cur;

	for (i = 0; i < BOTS_START_CNT; i++) {
		cur = malloc (sizeof(Bot));
		if (cur == NULL)
			return 1;

		createRandomBot (cur, i);

		if ((*B)->first == NULL) {
			(*B)->first = cur;
			(*B)->last = cur;
		}
		else {
			(*B)->last->next = cur;
			(*B)->last = (*B)->last->next;
		}
	}
	return 0;
}

// ������� ���� �� ������� ������ �����
int initField (char F[F_SIZE_VERT][F_SIZE_HOR], Bots **B) {

}


// ��������� ��� ������� ����� ������������ ���������
int init(char F[F_SIZE_VERT][F_SIZE_HOR], Bots **Bots) {
	int i, j, createOrLoad;

	printf("������� ��� ��������� ���������? [1\\0]: ");
	if (scanf("%d", &createOrLoad) == 0) {
		system("pause");
		return 1;
	}

	// �������� �����
	if (createOrLoad == 1) {
		// �������� �����
		if (initBots (Bots))
			return 1;
		if (initField (F, Bots))
			return 1;
	}
	// �������� �� �����
	else {
		// �� �����������
	}
	return 0;
}


// ����� �� ��������� ����� ���������
int isEndGeneration () {

}


// ������������ ���� �����
int handleBots () {

}


// ������� ���� � ��� ����������
int printInfo () {

}


// ���������, ����� �� ������������ �� �����
int isPause () {

}


// ������������� ���������
int stopSim () {

}


// ��������� �������� ��������� ������
int littlePause () {

}


// ���������� ����� �����, ��������� � �������
int mainCycle () {
	// ������� ������ ��������� ������
	// (�� ������� �������)
	while (1) {
		while (!isEndGeneration ())  // ���� �� ���� ������ 8 �����
		{
			handleBots ();  // ���������� ���� �����			
			printInfo ();  // ������� ���������� ����
			if (isPause ())  // ���� ������������ ��������� ���������
			{
				stopSim ();  // �����, ����� ��� ���������� � ����
			}
			else {
				littlePause ();  // ��������� Sleep (50), ����� �� ������� �����
			}
		}
		//
	}
}


// ��������� ������ ���������
int result () {

}


int main() {
	setlocale(LC_ALL, "RUS");

	char Field[F_SIZE_VERT][F_SIZE_HOR];
	Bots *Bots;

	if (init (Field, &Bots))
		return 0;
	mainCycle ();
	result ();

	system("pause");
	return 0;
}
