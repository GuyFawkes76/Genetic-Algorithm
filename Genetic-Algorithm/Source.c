/*
Лабораторная работа номер 5. Генетический алгоритм.
Червинский Артём, Степаненко Кирилл, ИВТ-13БО.

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#include <conio.h>
#include "init.h"



// Возвращает случайное число
int getRandomInt (int min, int max) {
	return rand() % (max - min + 1) + min;
}

// Наполняет мир едой и ядом
int fillField (char F[F_SIZE_VERT][F_SIZE_HOR]) {
	int i, j, r, c;
	for (i = 0; i < F_FOOD_CNT; i++) {
		do {
			r = getRandomInt (1, F_SIZE_VERT);
			c = getRandomInt (1, F_SIZE_HOR);
		} while (F[r][c] != F_CHAR_SPACE);
		F[r][c] = F_CHAR_FOOD;
	}
	for (i = 0; i < F_POIS_CNT; i++) {
		do {
			r = getRandomInt (1, F_SIZE_VERT);
			c = getRandomInt (1, F_SIZE_HOR);
		} while (F[r][c] != F_CHAR_SPACE);
		F[r][c] = F_CHAR_POIS;
	}
}

// Проверяет, живой ли бот
int isAlive(Bot * bot) {
	if (bot->hp <= 0)
		return 0;
	else 
		return 1;
}

// Обрабатывает ходы ботов
int handleBots (char Field[F_SIZE_VERT][F_SIZE_HOR], Bots * botlist) {
	Bot* curBot;
	for (curBot = botlist->first; curBot; ) {
		if (isAlive(curBot)) {
			if (curBot->genom[curBot->curCmd] <= 7) {
				move(Field, curBot);
			}
			if ((curBot->genom[curBot->curCmd] >= 8) && (curBot->genom[curBot->curCmd] <= 15))  {
				grab(Field, curBot);
			}
			if ((curBot->genom[curBot->curCmd] >= 16) && (curBot->genom[curBot->curCmd] <= 23)) {
				seek(Field, curBot);
			}
			if ((curBot->genom[curBot->curCmd] >= 24) && (curBot->genom[curBot->curCmd] <= 31)) {
				turn(Field, curBot);
			}
			if ((curBot->genom[curBot->curCmd] >= 32) && (curBot->genom[curBot->curCmd] <= 63)) {
				genomeStep(Field, curBot);
			}
		}
	}
	return 0;
}

// Делает шаг в указанную сторону
int move() {

}

// Хватает предмет в указанной стороне или преобразует яд в еду
int grab() {

}

// Смотрит, что находится в указанной стороне
int seek() {

}

// Поворачивает бота на указанное направление
int turn() {

}

// Прыгает на нужную ячеёку в геноме бота
int genomeStep() {

}

// Смещает на нужное количество ячеек в геноме бота в зависимости от того, что находится в клетке
int genomeWarp() {

}

// Выводит поле и доп информацию
int printInfo (char F[F_SIZE_VERT][F_SIZE_HOR], int stepNum, int genNum) {	
	system("cls");
	for (int i = 0; i < F_SIZE_VERT; i++) {
		for (int j = 0; j < F_SIZE_HOR; j++) {
			printf("%c", F[i][j]);
		}
		printf("\n");
	}	
	printf("\nТекущий ход: %d\n", stepNum);
	printf("Номер поколения: %d\n", genNum);
	printf("\n");
	printf("Остановка/продолжение - Пробел, сохранить - S, выйти - Q: \n");
}

// Обрабатывает нажатия клавиш
int handleKeys () {
	char symbol, pause;
	if (_kbhit()) { // Если буфер ввода не пуст
		while (symbol = _getch()) { // Прочитать введенный символ
			switch (symbol) {
			case ' ':
				// По нажатию пробела - пауза
				do {
					pause = _getch();
				} while (pause != ' ');
				return 2;
			case 's':
			case 'S':
			case 'ы':
			case 'Ы':
				// Сохранение
				return 1;
			case 'q':
			case 'Q':
			case 'й':
			case 'Й':
			case 27:
				// Выход на q или Esc
				return 0;
			}
		}
		fflush (stdin); // Остальные символы удаляем
	}
	else
		return 2; // Продолжать симуляцию
}

// Уменьшает скорость мелькания экрана
int littlePause () {
	_sleep(100);
}

// Создает новое поколение
int evolveGen (char F[F_SIZE_VERT][F_SIZE_HOR], Bots *B) {
	Bot *cur, *prev, *main;
	int i, k, r, c, randGen, genNum, genValue;
	cur = B->first;
	// Удаляем из списка мертвых ботов
	while (cur != NULL) {
		if (cur->hp == 0) {
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
			prev = cur;
		}
		cur = cur->next;
	}
	// Размножаем выживших
	prev = B->first;
	main = B->first;
	for (i = 0; i < BOTS_TRIG_CNT; i++) {
		randGen = getRandomInt (1, 7); // Какой по счету геном кроме первого мутирует
		for (k = 1; k < BOTS_TRIG_CNT; k++) {
			cur = malloc (sizeof(Bot));
			if (cur == NULL)
				return 1;

			cur->next = prev->next;
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
			memcpy (cur->genom, main->genom, sizeof(main->genom));
			prev->next = cur;
			prev = cur;
			if (k == randGen) {
				genNum = getRandomInt (0, GENOM_LEN-1);
				genValue = getRandomInt (0, GENOM_LEN-1);
				cur->genom[genNum] = genValue;
			}
		}
		
	}
}

// Удаляет всё, кроме стен
int clearField (char Field[F_SIZE_VERT][F_SIZE_HOR]) {
	int i, j;
	for (i = 1; i < F_SIZE_VERT; i++) {
		for (j = 1; j < F_SIZE_HOR; j++) {
			if (Field[i][j] != F_CHAR_WALL) 
				Field[i][j] = F_CHAR_SPACE;
		}
	}
}

// Объединяет смену ходов, поколений и геномов
int mainCycle (char Field[F_SIZE_VERT][F_SIZE_HOR], Bots **Bots) {
	int state, stepNum = 0, genNum = 0;

	while (1) {
		while (1) {  // Смена поколений 			
			if (handleBots (Field, *Bots)) // Проверка на конец поколения
				break;
			printInfo (Field, stepNum, genNum);  // Вывести измененное поле
			state = handleKeys ();  // Обработка нажатий клавиш
			if (state == 0) // Выход без сохранения
				return 0;
			if (state == 1)  // Выход с сохранением
				return 1;
			littlePause ();  // Небольшой Sleep, чтобы не мелькал экран
			stepNum++;
		}		
		clearField (Field);
		// Сгенерировать новое поколение
		evolveGen (Field, *Bots);		
		fillField (Field);
		genNum++;
	}
	return 0;
}

// Завершает работу симуляции
int saveAndExit (Bots *Bots) {
	// Сохранить каждый 8ой геном
	char s[64];
	Bot *cur;
	FILE *fp;
	printf("\nСохранить в файл: \n");
	gets(s);
	if ((fp = fopen (s, "w")) == NULL)
		return 0;
	else {
		// Сохранение
		cur = Bots->first;
		for (int i = 0; i < BOTS_START_CNT; i++) {
			if (cur->id % BOTS_TRIG_CNT == 0) {
				// Выбираем каждого восьмого бота
				for (int j = 0; j < GENOM_LEN; j++) {
					fprintf (fp, "%d ", cur->genom[j]);
				}
				fprintf (fp, "\n");
			}

			cur = cur->next;
		}
		fclose(fp);
	}
}

int main() {
	setlocale(LC_ALL, "RUS");

	char Field[F_SIZE_VERT][F_SIZE_HOR];
	Bots *Bots;

	if (init (Field, &Bots))
		return 0;
	if (mainCycle (Field, &Bots))
		saveAndExit (Bots);
	return 0;
}
