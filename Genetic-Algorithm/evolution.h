#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "init.h"

// ��������� �� ���� ��������� ���������� ��� � ��� ������ ���
int addFoodAndPois(char Field[F_SIZE_VERT][F_SIZE_HOR]);

// ������� ��, ����� ����
int clearField(char Field[F_SIZE_VERT][F_SIZE_HOR]);

// ������� ����� ���������
int evolveGen(char F[F_SIZE_VERT][F_SIZE_HOR], Bots* B);

// ��������� ��� ���� � ����
int fillField(char F[F_SIZE_VERT][F_SIZE_HOR]);

// ������� �� ������ ������ � ������ ����
int genomeStep(Bot* bot);

// ������� �� ������ ���������� ����� � ������ ���� � ����������� �� ����, ��� ��������� � ������
int genomeWarp(Bot* bot, char curSymbol);

// ���������� ������� ������, ���������� ������ �� ��. ������ ����� ������� ���� � �������.
int getDirection(char Field[F_SIZE_VERT][F_SIZE_HOR], Bot* bot, int* row, int* col);

// ���������� ��������� �����
int getRandomInt(int min, int max);

// ������� ������� � ��������� ������� ��� ����������� �� � ���
int grab(char Field[F_SIZE_VERT][F_SIZE_HOR], Bot* bot);

// ������������ ���� �����
int handleBots(char Field[F_SIZE_VERT][F_SIZE_HOR], Bots* botlist);

// ������������ ������� ������
int handleKeys();

// ���������, ����� �� ���
int isAlive(Bot* bot);

// ���������� ����� �����, ��������� � �������
int mainCycle(char Field[F_SIZE_VERT][F_SIZE_HOR], Bots** Bots);

// ������ ��� � ��������� �������
int move(char Field[F_SIZE_VERT][F_SIZE_HOR], Bot* bot);

// ������� ���� � ��� ����������
int printInfo(char F[F_SIZE_VERT][F_SIZE_HOR], int stepNum, int genNum);

// ��������� ������ ���������
int saveAndExit(Bots* Bots);

// �������, ��� ��������� � ��������� �������
int seek(char Field[F_SIZE_VERT][F_SIZE_HOR], Bot* bot);

// ������������ ���� �� ��������� �����������
int turn (Bot* bot);


#endif	//EVOLUTION_H