#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include "evolution.h"

#define FILE_INP_NAME "input.txt"
#define FILE_OUT_NAME "output.txt"


// ������� ���������� ����
int createRandomBot(char F[F_SIZE_VERT][F_SIZE_HOR], Bot* cur, int number);

// ��������� ��� ������� ����� ������������ ���������
int init(char F[F_SIZE_VERT][F_SIZE_HOR], Bots **Bots);

// ������� ������ �����
int initBots (char F[F_SIZE_VERT][F_SIZE_HOR], Bots **B);

// ������� ���� �� ������� ������ �����
int initField (char F[F_SIZE_VERT][F_SIZE_HOR]);

// ������ �� �����
int readFile (FILE *fp, char F[F_SIZE_VERT][F_SIZE_HOR], Bots **B);

#endif	//INIT_H
