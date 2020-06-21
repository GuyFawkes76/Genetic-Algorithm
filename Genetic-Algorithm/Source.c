/*
Лабораторная работа номер 5. Генетический алгоритм.
Червинский Артём, Степаненко Кирилл, ИВТ-13БО.

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#define GENOM_LEN 64
#define BOTS_START_CNT 64
#define BOTS_TRIG_CNT 8
#define BOTS_START_HP 40
#define F_SIZE_HOR 45
#define F_SIZE_VERT 20
#define F_WALLS_CNT 8
#define F_FOOD_CNT 64
#define F_POIS_CNT 32
#define F_CHAR_WALL '#'
#define F_CHAR_SPACE ' '
#define F_CHAR_FOOD '@'
#define F_CHAR_POIS 'я'


// Все данные бота
typedef struct bot {
	int genom[GENOM_LEN];
	int id; // Идентификатор 0..63	
	int row, col; // row и col, координаты бота
	int hp; // Число очков жизни 0..99
	int view; // Направление взгляда 0..7
	struct bot *next;
} Bot;

// Список ботов
typedef struct bots {
	Bot *first, *last;
	int cnt;
} Bots;

typedef struct config {
	int stepNum; // Номер хода в поколении
	int genNum; // Номер поколения в генерации
	int savedGens[BOTS_TRIG_CNT]; // Массив выживших в прошлом поколении геномов
} Config;


// Возвращает случайное число
int getRandomInt (int min, int max) {
	return rand() % (max - min + 1) + min;
}

// Создает случайного бота
int createRandomBot (char F[F_SIZE_VERT][F_SIZE_HOR], Bot *cur, int number) {
	int i, r, c;
	cur->next = NULL;
	cur->hp = BOTS_START_HP;
	cur->id = number;
	cur->view = getRandomInt (0, 7);
	do {
		c = getRandomInt (0, F_SIZE_HOR);
		r = getRandomInt (0, F_SIZE_VERT);
	} while (F[r][c] != F_CHAR_SPACE);
	cur->col = c;
	cur->row = r;
	for (i = 0; i < GENOM_LEN; i++) {
		cur->genom[i] = getRandomInt (0, GENOM_LEN);
	}

	return 0;
}

// Создает список ботов
int initBots (char F[F_SIZE_VERT][F_SIZE_HOR], Bots **B) {
	int i;
	Bots *newBotsList = malloc (sizeof (Bots));  // Создан список ботов
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

// Создает поле по данному списку ботов
int initField (char F[F_SIZE_VERT][F_SIZE_HOR], Bots **B) {
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

	// После создания стены не должны меняться при ходах!
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

	for (i = 0; i < F_SIZE_VERT; i++) {
		for (j = 0; j < F_SIZE_HOR; j++) {
			printf("%c", F[i][j]);
		}
		printf("\n");
	}
	return 0;
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

// Загружает или создает новую конфигурацию симуляции
int init(char F[F_SIZE_VERT][F_SIZE_HOR], Bots **Bots) {
	int i, j, createOrLoad = 1;
	srand (time(NULL));
	/*
	printf("Создать или загрузить симуляцию? [1\\0]: ");
	if (scanf("%d", &createOrLoad) == 0) {
		scanf("%d");
		return 1;
	}
	*/
	// Создание новой
	if (createOrLoad == 1) {
		// Создание мира со стенами
		initField (F, Bots);
		// Создание ботов
		if (initBots (F, Bots))
			return 1;
		// Заполнение мира едой и ядом
		fillField (F);

		for (i = 0; i < F_SIZE_VERT; i++) {
			for (j = 0; j < F_SIZE_HOR; j++) {
				printf("%c", F[i][j]);
			}
			printf("\n");
		}
	}
	// Загрузка из файла
	else {
		// Не реализовано
	}
	return 0;
}

// Нужно ли создавать новое поколение
int isEndGeneration () {

}

// Обрабатывает ходы ботов
int handleBots () {

}

// Выводит поле и доп информацию
int printInfo () {

}

// Проверяет, нажал ли пользователь на паузу
int isPause () {

}

// Сохраняет симуляцию
int saveSim () {

}

// Уменьшает скорость мелькания экрана
int littlePause () {

}

// Создает новое поколение
int evolveSeed () {

}

// Заселяет ботов в мир
int spawnSeed () {

}

// Сохраняет номера выживших ботов
int saveConfig () {

}

// Объединяет смену ходов, поколений и геномов
int mainCycle (char Field[F_SIZE_VERT][F_SIZE_HOR], Bots **Bots) {
	// Условие выхода находится внутри
	// (По нажатию клавиши)
	while (1) {
		while (1)  // Смена поколений
		{
			if (handleBots ()) // Проверка на конец поколения
				break;				
			printInfo ();  // Вывести измененное поле
			if (isPause ())  // Обработка паузы
			{
				if (saveSim ())  // Сохранение в файл
					return 0;
			}
			else {
				littlePause ();  // Небольшой Sleep (50), чтобы не мелькал экран
			}
		}	
		// Запомнить конфигурацию 
		saveConfig ();
		// Сгенерировать новое поколение
		evolveSeed ();
		// Заселить в мир
		spawnSeed ();
	}
}

// Завершает работу симуляции
int result () {

}

int main() {
	setlocale(LC_ALL, "RUS");

	char Field[F_SIZE_VERT][F_SIZE_HOR];
	Bots *Bots;

	if (init (Field, &Bots))
		return 0;
	mainCycle (Field, &Bots);
	result ();

	scanf("%d");
	return 0;
}