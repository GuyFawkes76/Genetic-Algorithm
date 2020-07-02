#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "init.h"
#define GENOM_LEN 64
#define BOTS_START_CNT 64
#define BOTS_TRIG_CNT 8
#define BOTS_START_HP 10
#define F_SIZE_HOR 51
#define F_SIZE_VERT 21
#define F_WALLS_CNT 8
#define F_FOOD_CNT 64
#define F_POIS_CNT 32
#define F_ADDFOOD_CNT 1
#define F_ADDPOIS_CNT 1
#define F_CHAR_WALL '#'
#define F_CHAR_SPACE ' '
#define F_CHAR_FOOD '@'
#define F_CHAR_POIS '�'
#define FOOD_HP 5
#define GENOME_POIS_OFFSET 1
#define GENOME_WALL_OFFSET 2
#define GENOME_BOT_OFFSET 3
#define GENOME_FOOD_OFFSET 4
#define GENOME_SPACE_OFFSET 5


// ��� ������ ����
typedef struct bot {
	int genom[GENOM_LEN];
	int curCmd; //����� �������  � ������ ��� ���������� 0..63
	int id; // ������������� 0..63	
	int row, col; // row � col, ���������� ����
	int hp; // ����� ����� ����� 0..99
	int sight; // ����������� ������� 0..7
	struct bot* next;
} Bot;

// ������ �����
typedef struct bots {
	Bot* first, * last;
	int cnt;
} Bots;



#endif	//EVOLUTION_H