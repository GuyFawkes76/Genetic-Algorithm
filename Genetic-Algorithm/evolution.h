#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "init.h"

// Добавляет на поле некоторое количество еды и яда каждый ход
int addFoodAndPois(char Field[F_SIZE_VERT][F_SIZE_HOR]);

// Удаляет всё, кроме стен
int clearField(char Field[F_SIZE_VERT][F_SIZE_HOR]);

// Создает новое поколение
int evolveGen(char F[F_SIZE_VERT][F_SIZE_HOR], Bots* B);

// Наполняет мир едой и ядом
int fillField(char F[F_SIZE_VERT][F_SIZE_HOR]);

// Прыгает на нужную ячейку в геноме бота
int genomeStep(Bot* bot);

// Смещает на нужное количество ячеек в геноме бота в зависимости от того, что находится в клетке
int genomeWarp(Bot* bot, char curSymbol);

// Определяет целевую клетку, возвращает символ из неё. Меняет номер целевых ряда и столбца.
int getDirection(char Field[F_SIZE_VERT][F_SIZE_HOR], Bot* bot, int* row, int* col);

// Возвращает случайное число
int getRandomInt(int min, int max);

// Хватает предмет в указанной стороне или преобразует яд в еду
int grab(char Field[F_SIZE_VERT][F_SIZE_HOR], Bot* bot);

// Обрабатывает ходы ботов
int handleBots(char Field[F_SIZE_VERT][F_SIZE_HOR], Bots* botlist);

// Обрабатывает нажатия клавиш
int handleKeys();

// Проверяет, живой ли бот
int isAlive(Bot* bot);

// Объединяет смену ходов, поколений и геномов
int mainCycle(char Field[F_SIZE_VERT][F_SIZE_HOR], Bots** Bots);

// Делает шаг в указанную сторону
int move(char Field[F_SIZE_VERT][F_SIZE_HOR], Bot* bot);

// Выводит поле и доп информацию
int printInfo(char F[F_SIZE_VERT][F_SIZE_HOR], int stepNum, int genNum);

// Завершает работу симуляции
int saveAndExit(Bots* Bots);

// Смотрит, что находится в указанной стороне
int seek(char Field[F_SIZE_VERT][F_SIZE_HOR], Bot* bot);

// Поворачивает бота на указанное направление
int turn (Bot* bot);


#endif	//EVOLUTION_H