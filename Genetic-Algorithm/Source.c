/*
Лабораторная работа номер 5. Генетический алгоритм.
Червинский Артём, Степаненко Кирилл, ИВТ-13БО.

*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

#define GENOM_LEN 64
#define F_SIZE_L 45
#define F_SIZE_W 20

// Все данные бота
struct bot
{
	int genom[GENOM_LEN];
	int id; // Идентификатор 0..63
	int alive; // жив ли бот
	int r, c; // row и col, координаты бота
	int hp; // Число очков жизни 0..99
	int view; // Направление взгляда 0..7
	struct bot *next;
};

// Список ботов
typedef struct bots
{
	struct bot *first;	
} Bots;


// Загружает или создает новую конфигурацию симуляции
int Init()
{

}


// Нужно ли создавать новое поколение
int isEndGeneration ()
{

}


// Обрабатывает ходы ботов
int HandleBots ()
{

}


// Выводит поле и доп информацию
int PrintInfo ()
{

}


// Проверяет, нажал ли пользователь на паузу
int isPause ()
{

}


// Останавливает симуляцию
int StopSim ()
{

}


// Уменьшает скорость мелькания экрана
int LittlePause ()
{

}


// Объединяет смену ходов, поколений и геномов
int MainCycle ()
{
	// Условие выхода находится внутри
	// (По нажатию клавиши)
	while (1)
	{
		while (!isEndGeneration ())  // Пока на поле больше 8 ботов
		{
			HandleBots ();  // Обработать ходы ботов
			PrintInfo ();  // Вывести измененное поле
			if (isPause ())  // Если пользователь остановил симуляцию
			{
				StopSim ();  // Пауза, выход или сохранение в файл
			}
			else
			{
				LittlePause ();  // Небольшой Sleep (50), чтобы не мелькал экран
			}
		}
	}
}


// Завершает работу симуляции
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
