#pragma once
#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#define FILE_INP_NAME "input.txt"
#define FILE_OUT_NAME "output.txt"
#define GENOM_LEN 64
#define BOTS_START_CNT 64
#define BOTS_TRIG_CNT 8
#define BOTS_START_HP 30
#define FOOD_HP 10
#define F_SIZE_HOR 51
#define F_SIZE_VERT 21
#define F_WALLS_CNT 8
#define F_FOOD_CNT 64
#define F_POIS_CNT 32
#define F_CHAR_WALL '#'
#define F_CHAR_SPACE ' '
#define F_CHAR_FOOD '@'
#define F_CHAR_POIS '�'


// ��� ������ ����
typedef struct bot {
	int genom[GENOM_LEN];
	int curCmd; //����� �������  � ������ ��� ���������� 0..63
	int id; // ������������� 0..63	
	int row, col; // row � col, ���������� ����
	int hp; // ����� ����� ����� 0..99
	int sight; // ����������� ������� 0..7
	struct bot *next;
} Bot;

// ������ �����
typedef struct bots {
	Bot *first, *last;
	int cnt;
} Bots;


// ��������� ��� ������� ����� ������������ ���������
int init(char F[F_SIZE_VERT][F_SIZE_HOR], Bots **Bots);

// ������� ���������� ����
int createRandomBot (char F[F_SIZE_VERT][F_SIZE_HOR], Bot *cur, int number);

// ������� ������ �����
int initBots (char F[F_SIZE_VERT][F_SIZE_HOR], Bots **B);

// ������� ���� �� ������� ������ �����
int initField (char F[F_SIZE_VERT][F_SIZE_HOR]);

// ������ �� �����
int readFile (FILE *fp, char F[F_SIZE_VERT][F_SIZE_HOR], Bots **B);

// ��������� ��� ������� ����� ������������ ���������
int init(char F[F_SIZE_VERT][F_SIZE_HOR], Bots **Bots);


#endif
