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
#define F_SIZE_HOR 45
#define F_SIZE_VERT 20
#define BOT_START_HP 40

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
} Bots;


// Возвращает случайное число
int getRandomInt (int min, int max) {
	return rand() % (max - min + 1) + min;
}


// Создает случайного бота
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
	Bots *newBotsList = malloc (sizeof (Bots));  // Создан список ботов
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

// Создает поле по данному списку ботов
int initField (char F[F_SIZE_VERT][F_SIZE_HOR], Bots **B) {

}


// Загружает или создает новую конфигурацию симуляции
int init(char F[F_SIZE_VERT][F_SIZE_HOR], Bots **Bots) {
	int i, j, createOrLoad;

	printf("Создать или загрузить симуляцию? [1\\0]: ");
	if (scanf("%d", &createOrLoad) == 0) {
		system("pause");
		return 1;
	}

	// Создание новой
	if (createOrLoad == 1) {
		// Создание ботов
		if (initBots (Bots))
			return 1;
		if (initField (F, Bots))
			return 1;
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


// Останавливает симуляцию
int stopSim () {

}


// Уменьшает скорость мелькания экрана
int littlePause () {

}


// Объединяет смену ходов, поколений и геномов
int mainCycle () {
	// Условие выхода находится внутри
	// (По нажатию клавиши)
	while (1) {
		while (!isEndGeneration ())  // Пока на поле больше 8 ботов
		{
			handleBots ();  // Обработать ходы ботов			
			printInfo ();  // Вывести измененное поле
			if (isPause ())  // Если пользователь остановил симуляцию
			{
				stopSim ();  // Пауза, выход или сохранение в файл
			}
			else {
				littlePause ();  // Небольшой Sleep (50), чтобы не мелькал экран
			}
		}
		//
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
	mainCycle ();
	result ();

	system("pause");
	return 0;
}
