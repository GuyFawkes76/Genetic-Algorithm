/*
Лабораторная работа номер 5. Генетический алгоритм.
Червинский Артём, Степаненко Кирилл, ИВТ-13БО.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>


// Загружает или создает новую конфигурацию симуляции
int Init()
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
			PrintField ();  // Вывести измененное поле
			if (isPause ())  // Если пользователь остановил симуляцию
			{
				StopSim ();  // Пауза, выход или сохранение в файл
			}
			else
			{
				LittlePause ()  // Небольшой Sleep (50), чтобы не мелькал экран
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
	MainСycle ();
	Result ();

	system("pause");
	return 0;
}
