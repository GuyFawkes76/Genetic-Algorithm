#include "evolution.h"

// ���������� ��������� �����
int getRandomInt(int min, int max) {
	return rand() % (max - min + 1) + min;
}

// ��������� ��� ���� � ����
int fillField(char F[F_SIZE_VERT][F_SIZE_HOR]) {
	int i, r, c;
	for (i = 0; i < F_FOOD_CNT; i++) {
		do {
			r = getRandomInt(1, F_SIZE_VERT);
			c = getRandomInt(1, F_SIZE_HOR);
		} while (F[r][c] != F_CHAR_SPACE);
		F[r][c] = F_CHAR_FOOD;
	}
	for (i = 0; i < F_POIS_CNT; i++) {
		do {
			r = getRandomInt(1, F_SIZE_VERT);
			c = getRandomInt(1, F_SIZE_HOR);
		} while (F[r][c] != F_CHAR_SPACE);
		F[r][c] = F_CHAR_POIS;
	}
}


// ��������� �� ���� ��������� ���������� ��� � ��� ������ ���
int addFoodAndPois(char Field[F_SIZE_VERT][F_SIZE_HOR]) {
	int i,		// �������
		row,	// ������� ��������������� ����� ������
		col;	// ������� ��������������� ����� �������
	for (i = 0; i < F_ADDFOOD_CNT; i++) {
		do {
			row = getRandomInt(1, F_SIZE_VERT);
			col = getRandomInt(1, F_SIZE_HOR);
		} while (Field[row][col] != F_CHAR_SPACE);
		Field[row][col] = F_CHAR_FOOD;
	}
	for (i = 0; i < F_ADDPOIS_CNT; i++) {
		do {
			row = getRandomInt(1, F_SIZE_VERT);
			col = getRandomInt(1, F_SIZE_HOR);
		} while (Field[row][col] != F_CHAR_SPACE);
		Field[row][col] = F_CHAR_POIS;
	}
}

// ���������, ����� �� ���
int isAlive(Bot* bot) {
	if (bot->hp <= 0)
		return 0;
	else
		return 1;
}

// ������������ ���� �����
int handleBots(char Field[F_SIZE_VERT][F_SIZE_HOR], Bots* botlist) {
	Bot* curBot = botlist->first;
	int uselessCnt = 0;
	// ����� �����
	while ((curBot != NULL) && (botlist->cnt > BOTS_TRIG_CNT)) {
		uselessCnt = 0;
		// ������������ � ���������
		while (uselessCnt < 10) {
			if (isAlive(curBot)) {
				if (curBot->genom[curBot->curCmd] <= 7) {
					move(Field, curBot);
					break;
				}
				else if (curBot->genom[curBot->curCmd] <= 15) {
					grab(Field, curBot);
					break;
				}
				else if (curBot->genom[curBot->curCmd] <= 23) {
					seek(Field, curBot);
					uselessCnt++;
				}
				else if (curBot->genom[curBot->curCmd] <= 31) {
					turn(curBot);
					uselessCnt++;
				}
				else if (curBot->genom[curBot->curCmd] <= 63) {
					genomeStep(curBot);
					uselessCnt++;
				}
			}
			else
				break;
		}

		if (curBot->hp == 0 || curBot->hp == 1) {
			curBot->hp = -10;
			botlist->cnt--;
			Field[curBot->row][curBot->col] = F_CHAR_FOOD;
		}
		else if (curBot->hp > 1) {
			curBot->hp--;
			Field[curBot->row][curBot->col] = '0' + curBot->hp / 10;
		}
		curBot = curBot->next;
	}
	if (botlist->cnt == 8)
		return 1;
	else
		return 0;
}

// ������ ��� � ��������� �������
int move(char Field[F_SIZE_VERT][F_SIZE_HOR], Bot* bot) {
	char curCell;
	int trgRow = bot->row,	// ����� �������� ����
		trgCol = bot->col;	// ����� ������� ������
	curCell = getDirection(Field, bot, &trgRow, &trgCol);
	switch (curCell) {
	case F_CHAR_POIS:
		bot->hp = 0;
		Field[bot->row][bot->col] = F_CHAR_POIS;
		break;
	case F_CHAR_FOOD:
		bot->hp += FOOD_HP;
		if (bot->hp > 99)
			bot->hp = 99;
		Field[bot->row][bot->col] = F_CHAR_SPACE;
		Field[trgRow][trgCol] = '0' + bot->hp / 10;
		bot->row = trgRow;
		bot->col = trgCol;
		break;
	case F_CHAR_SPACE:
		Field[bot->row][bot->col] = F_CHAR_SPACE;
		Field[trgRow][trgCol] = '0' + bot->hp / 10;
		bot->row = trgRow;
		bot->col = trgCol;
		break;
	case F_CHAR_WALL:
		break;
	default:
		break;
	}
	genomeWarp(bot, curCell);
}

// 
int getDirection(char Field[F_SIZE_VERT][F_SIZE_HOR], Bot* bot, int* row, int* col) {
	int direction = (bot->sight + bot->genom[bot->curCmd]) % 8;
	switch (direction) {
	case 0:
		(*row)--;
		break;
	case 1:
		(*row)--;
		(*col)++;
		break;
	case 2:
		(*col)++;
		break;
	case 3:
		(*row)++;
		(*col)++;
		break;
	case 4:
		(*row)++;
		break;
	case 5:
		(*row)++;
		(*col)--;
		break;
	case 6:
		(*col)--;
		break;
	case 7:
		(*row)--;
		(*col)--;
		break;
	}
	return Field[*row][*col];
}

// ������� ������� � ��������� ������� ��� ����������� �� � ���
int grab(char Field[F_SIZE_VERT][F_SIZE_HOR], Bot* bot) {
	char curCell;
	int trgRow = bot->row,	// ����� �������� ����
		trgCol = bot->col;	// ����� ������� ������
	curCell = getDirection(Field, bot, &trgRow, &trgCol);
	switch (curCell) {
	case F_CHAR_POIS:
		Field[trgRow][trgCol] = F_CHAR_FOOD;
		break;
	case F_CHAR_FOOD:
		bot->hp += FOOD_HP;
		if (bot->hp > 99)
			bot->hp = 99;
		Field[trgRow][trgCol] = F_CHAR_SPACE;
		Field[bot->row][bot->col] = '0' + bot->hp / 10;
		break;
	case F_CHAR_SPACE:
		break;
	case F_CHAR_WALL:
		break;
	default:
		break;
	}
	genomeWarp(bot, curCell);
}

// �������, ��� ��������� � ��������� �������
int seek(char Field[F_SIZE_VERT][F_SIZE_HOR], Bot* bot) {
	char curCell;
	int trgRow = bot->row,	// ����� �������� ����
		trgCol = bot->col;	// ����� ������� ������
	curCell = getDirection(Field, bot, &trgRow, &trgCol);
	genomeWarp(bot, curCell);
}

// ������������ ���� �� ��������� �����������
int turn(/*char Field[F_SIZE_VERT][F_SIZE_HOR],*/ Bot* bot) {
	bot->sight = (bot->sight + bot->genom[bot->curCmd]) % 8;
	bot->curCmd++;
}

// ������� �� ������ ������ � ������ ����
int genomeStep(Bot* bot) {
	bot->curCmd = (bot->curCmd + bot->genom[bot->curCmd]) % GENOM_LEN;
}

// ������� �� ������ ���������� ����� � ������ ���� � ����������� �� ����, ��� ��������� � ������
int genomeWarp(Bot* bot, char curSymbol) {
	switch (curSymbol) {
	case F_CHAR_POIS:
		bot->curCmd = (bot->curCmd + GENOME_POIS_OFFSET) % GENOM_LEN;
		break;
	case F_CHAR_WALL:
		bot->curCmd = (bot->curCmd + GENOME_WALL_OFFSET) % GENOM_LEN;
		break;
	case F_CHAR_FOOD:
		bot->curCmd = (bot->curCmd + GENOME_FOOD_OFFSET) % GENOM_LEN;
		break;
	case F_CHAR_SPACE:
		bot->curCmd = (bot->curCmd + GENOME_SPACE_OFFSET) % GENOM_LEN;
		break;
	default:
		bot->curCmd = (bot->curCmd + GENOME_BOT_OFFSET) % GENOM_LEN;
		break;
	}
}

// ������� ���� � ��� ����������
int printInfo(char F[F_SIZE_VERT][F_SIZE_HOR], int stepNum, int genNum) {
	system("cls");
	for (int i = 0; i < F_SIZE_VERT; i++) {
		for (int j = 0; j < F_SIZE_HOR; j++) {
			printf("%c", F[i][j]);
		}
		printf("\n");
	}
	printf("\nStep: %d\n", stepNum);
	printf("Gen: %d\n", genNum);
	printf("\n");
	printf("Stop - Space, Save - S, Quit - Q: \n");
}

// ������������ ������� ������
int handleKeys() {
	char symbol, pause;
	if (_kbhit()) { // ���� ����� ����� �� ����
		while (symbol = _getch()) { // ��������� ��������� ������
			switch (symbol) {
			case ' ':
				// �� ������� ������� - �����
				do {
					pause = _getch();
				} while (pause != ' ');
				return 2;
			case 's':
			case 'S':
			case '�':
			case '�':
				// ����������
				return 1;
			case 'q':
			case 'Q':
			case '�':
			case '�':
			case 27:
				// ����� �� q ��� Esc
				return 0;
			}
		}
		fflush(stdin); // ��������� ������� �������
	}
	else
		return 2; // ���������� ���������
}

// ������� ����� ���������
int evolveGen(char F[F_SIZE_VERT][F_SIZE_HOR], Bots* B) {
	Bot* cur, * prev, * main;
	int i, k, r, c, randGen, genNum, genValue;
	cur = B->first;
	i = 0;
	// ������� �� ������ ������� �����
	while (cur != NULL) {
		if (!isAlive(cur)) {
			if (cur == B->first) {
				B->first = cur->next;
			}
			else {
				prev->next = cur->next;
				free(cur);
				cur = prev;
			}
		}
		else {
			cur->id = i * BOTS_TRIG_CNT;	// ������ id
			i++;
			prev = cur;
		}
		cur = cur->next;
	}
	// ���������� ��������
	prev = B->first;
	main = B->first;
	for (i = 0; i < BOTS_TRIG_CNT; i++) {
		randGen = getRandomInt(1, 7); // ����� �� ����� ����� ����� ������� ��������
		for (k = 1; k < BOTS_TRIG_CNT; k++) {
			cur = malloc(sizeof(Bot));
			if (cur == NULL)
				return 1;

			cur->next = prev->next;
			cur->hp = BOTS_START_HP;
			cur->curCmd = 0;
			cur->id = i * BOTS_TRIG_CNT + k;
			cur->sight = getRandomInt(0, 7);
			do {
				c = getRandomInt(1, F_SIZE_HOR - 1);
				r = getRandomInt(1, F_SIZE_VERT - 1);
			} while (F[r][c] != F_CHAR_SPACE);

			cur->col = c;
			cur->row = r;
			F[r][c] = cur->hp / 10 + '0';
			memcpy(cur->genom, main->genom, sizeof(main->genom));
			prev->next = cur;
			prev = cur;
			if (k == randGen) {
				genNum = getRandomInt(0, GENOM_LEN - 1);
				genValue = getRandomInt(0, GENOM_LEN - 1);
				cur->genom[genNum] = genValue;
			}
		}
		main = cur->next;
		prev = cur->next;

	}
	//���������� ���������� �����.
	B->cnt = BOTS_START_CNT;
}

// ������� ��, ����� ����
int clearField(char Field[F_SIZE_VERT][F_SIZE_HOR]) {
	int i, j;
	for (i = 1; i < F_SIZE_VERT; i++) {
		for (j = 1; j < F_SIZE_HOR; j++) {
			if (Field[i][j] != F_CHAR_WALL)
				Field[i][j] = F_CHAR_SPACE;
		}
	}
}

// ���������� ����� �����, ��������� � �������
int mainCycle(char Field[F_SIZE_VERT][F_SIZE_HOR], Bots** Bots) {

	int state, stepNum = 0, genNum = 0;

	while (1) {
		while (1) {  // ����� ��������� 			
			if (handleBots(Field, *Bots)) // �������� �� ����� ���������
				break;
			addFoodAndPois(Field);
			printInfo(Field, stepNum, genNum);  // ������� ���������� ����
			state = handleKeys();  // ��������� ������� ������
			if (state == 0) // ����� ��� ����������
				return 0;
			if (state == 1)  // ����� � �����������
				return 1;
			_sleep(0);  // ����� �� ������� �����
			stepNum++;
		}
		clearField(Field);
		// ������������� ����� ���������
		evolveGen(Field, *Bots);
		fillField(Field);
		genNum++;
		stepNum = 0;
	}
	return 0;
}

// ��������� ������ ���������
int saveAndExit(Bots* Bots) {
	// ��������� ������ 8�� �����
	char s[64];
	Bot* cur;
	FILE* fp;
	printf("\nSave in file: \n");
	gets(s);
	if ((fp = fopen(s, "w")) == NULL)
		return 0;
	else {
		// ����������
		cur = Bots->first;
		for (int i = 0; i < BOTS_START_CNT; i++) {
			if (cur->id % BOTS_TRIG_CNT == 0) {
				// �������� ������� �������� ����
				for (int j = 0; j < GENOM_LEN; j++) {
					fprintf(fp, "%d ", cur->genom[j]);
				}
				fprintf(fp, "\n");
			}

			cur = cur->next;
		}
		fclose(fp);
	}
}
