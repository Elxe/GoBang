#pragma once

#define BOARDSIZE 15  //�������̵Ĵ�С
#define BLACK 1  //�������̵������������Ϊ1����Ϊ-1������ʱΪ0��
#define WHITE -1
#define BLANK 0
#define DOUBLEWIN 2

typedef struct Position { int X; int Y; }Position;

extern Position Record[BOARDSIZE*BOARDSIZE];
extern int StackMark;
extern int Counter;  //�غ�
extern int ChessFlag; //�Ⱥ���
extern int Bans;  //����
extern int Depth;  //�������
extern int Mode;
extern int MaxTotal;
extern int MinTotal;
extern int Number;
