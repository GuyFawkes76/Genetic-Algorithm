#define _CRT_SECURE_NO_WARNINGS
#include "init.h"

// ������� ���������� ����
int createRandomBot (char F[F_SIZE_VERT][F_SIZE_HOR], Bot *cur, int number) {
	int i, r, c;
	cur->next = NULL;
	cur->hp = BOTS_START_HP;
	cur->id = number;
	cur->view = getRandomInt (0, 7);
	do {
		c = getRandomInt (1, F_SIZE_HOR-1);
		r = getRandomInt (1, F_SIZE_VERT-1);
	} while (F[r][c] != F_CHAR_SPACE);
	cur->col = c;
	cur->row = r;
	for (i = 0; i < GENOM_LEN; i++) {
		cur->genom[i] = getRandomInt (0, GENOM_LEN);
	}

	return 0;
}

// ������� ������ �����
int initBots (char F[F_SIZE_VERT][F_SIZE_HOR], Bots **B) {
	int i;
	Bots *newBotsList = malloc (sizeof (Bots));  // ������ ������ �����
	if (newBotsList == NULL)
		return 1;
	newBotsList->first = NULL;
	newBotsList->last = NULL;
	newBotsList->cnt = BOTS_START_CNT;
	*B = newBotsList;

	Bot *cur;

	for (i = 0; i < BOTS_START_CNT; i++) {
		cur = malloc (sizeof(Bot));
		if (cur == NULL)
			return 1;

		createRandomBot (F, cur, i);
		F[cur->row][cur->col] = cur->hp / 10 + '0';
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
int initField (char F[F_SIZE_VERT][F_SIZE_HOR]) {
	int i, j, k, r, c, len;

	for (i = 1; i < F_SIZE_VERT; i++) {
		for (j = 1; j < F_SIZE_HOR; j++) {
			F[i][j] = F_CHAR_SPACE;
		}
	}
	for (j = 0; j < F_SIZE_HOR; j++)
		F[0][j] = F_CHAR_WALL;
	for (j = 0; j < F_SIZE_HOR; j++)
		F[F_SIZE_VERT-1][j] = F_CHAR_WALL;
	for (i = 0; i < F_SIZE_VERT; i++)
		F[i][0] = F_CHAR_WALL;
	for (i = 0; i < F_SIZE_VERT; i++)
		F[i][F_SIZE_HOR-1] = F_CHAR_WALL;

	// ����� �������� ����� �� ������ �������� ��� �����!
	for (k = 0; k < F_WALLS_CNT; k++) {
		len = getRandomInt (3, 5);
		r = getRandomInt (len, F_SIZE_VERT-len-1);
		c = getRandomInt (len, F_SIZE_HOR-len-1);

		for (i = 0; i < len; i++) {
			if (k % 2 == 0)
				F[r][c+i] = F_CHAR_WALL;
			else
				F[r+i][c] = F_CHAR_WALL;
		}
	}
	return 0;
}


// ������ �� �����
int readFile (FILE *fp, char F[F_SIZE_VERT][F_SIZE_HOR], Bots **B) {
	int i, j, k, r, c;
	int newGenom[GENOM_LEN];
	Bot *cur;
	Bots *newBotsList = malloc (sizeof (Bots));  // ������ ������ �����
	if (newBotsList == NULL)
		return 1;
	newBotsList->first = NULL;
	newBotsList->last = NULL;
	newBotsList->cnt = BOTS_START_CNT;
	*B = newBotsList;

	for (i = 0; i < BOTS_TRIG_CNT; i++) {
		// ������ ����� ������ ������
		for (j = 0; j < GENOM_LEN; j++) {
			fscanf(fp, "%d", &newGenom[j]);
		}
		// ������ ������ ������ ������������� 8 �����:
		for (k = 0; k < BOTS_TRIG_CNT; k++) {
			cur = malloc (sizeof(Bot));
			if (cur == NULL)
				return 1;

			cur->next = NULL;
			cur->hp = BOTS_START_HP;
			cur->id = i * BOTS_TRIG_CNT + k;
			cur->view = getRandomInt (0, 7);
			do {
				c = getRandomInt (1, F_SIZE_HOR - 1);
				r = getRandomInt (1, F_SIZE_VERT - 1);
			} while (F[r][c] != F_CHAR_SPACE);

			cur->col = c;
			cur->row = r;
			F[r][c] = cur->hp / 10 + '0';
			memcpy (cur->genom, newGenom, sizeof(newGenom));
			
			if ((*B)->last == NULL) {
				(*B)->first = cur;
				(*B)->last = cur;
			}
			else {
				(*B)->last->next = cur;
				(*B)->last = (*B)->last->next;
			}
		}
	}
	return 0;
}


// ��������� ��� ������� ����� ������������ ���������
int init(char F[F_SIZE_VERT][F_SIZE_HOR], Bots **Bots) {
	int i, j, createOrLoad = 0;
	char fileName[128] = "";
	FILE *fp;
	srand (time(NULL));
	/*
	printf("������� ��� ��������� ���������? [1\\0]: ");
	if (scanf("%d\n", &createOrLoad) == 0) {
		return 1;
	}
	*/
	if (createOrLoad == 1) {  // �������� �����
		// �������� ���� �� �������
		initField (F);
		// �������� �����
		if (initBots (F, Bots))
			return 1;
		// ���������� ���� ���� � ����
		fillField (F);
	}
	else {  // �������� �� �����
		printf("\n�������� ����� ��� ��������: ");
		gets (fileName);
		if (!strlen (fileName))
			memcpy (fileName, FILE_INP_NAME, sizeof(FILE_INP_NAME));
		if ((fp = fopen (fileName, "r")) == NULL) {
			printf ("�� ������ ����\n");
			system ("pause");
			return 1;
		}
		else {
			// ���� ������:
			initField (F);

			if (readFile (fp, F, Bots)) {
				printf ("������ ��� ������\n");
				system ("pause");
				return 1;
			}
			// ���������� ���� ���� � ����
			fillField (F);
			fclose (fp);
		}
	}
	return 0;
}
