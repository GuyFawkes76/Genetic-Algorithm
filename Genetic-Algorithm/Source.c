/*
Лабораторная работа номер 5. Генетический алгоритм.
Червинский Артём, Степаненко Кирилл, ИВТ-13БО.

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#define GENOM_LEN 64
#define F_SIZE_HOR 45
#define F_SIZE_VERT 20

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


// Создает случайный геном
int createRandGenom (Bot *cur) {
	int a;
	cur->next = NULL;

	return 0;
}


int initBots (Bots **B) {
	int i;
	srand (time(NULL));
	Bots *new_b = malloc (sizeof (Bots));  // Создан список ботов
	if (new_b == NULL)
		return 1;
	new_b->first = NULL;
	new_b->last = NULL;

	if (*B == NULL)
		*B = new_b;

	Bot *cur;

	for (i = 0; i < GENOM_LEN; i++) {
		cur = malloc (sizeof(Bot));
		if (cur == NULL)
			return 1;

		createRandGenom (cur);

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
