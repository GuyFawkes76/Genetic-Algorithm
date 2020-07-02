#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include "evolution.h"

#define FILE_INP_NAME "input.txt"
#define FILE_OUT_NAME "output.txt"


// Создает случайного бота
int createRandomBot(char F[F_SIZE_VERT][F_SIZE_HOR], Bot* cur, int number);

// Загружает или создает новую конфигурацию симуляции
int init(char F[F_SIZE_VERT][F_SIZE_HOR], Bots **Bots);

// Создает список ботов
int initBots (char F[F_SIZE_VERT][F_SIZE_HOR], Bots **B);

// Создает поле по данному списку ботов
int initField (char F[F_SIZE_VERT][F_SIZE_HOR]);

// Чтение из файла
int readFile (FILE *fp, char F[F_SIZE_VERT][F_SIZE_HOR], Bots **B);

#endif	//INIT_H
