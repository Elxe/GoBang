#pragma once

#define BOARDSIZE 15  //定义棋盘的大小
#define BLACK 1  //定义棋盘的落子情况（黑为1，白为-1，无子时为0）
#define WHITE -1
#define BLANK 0
#define DOUBLEWIN 2

typedef struct Position { int X; int Y; }Position;

extern Position Record[BOARDSIZE*BOARDSIZE];
extern int StackMark;
extern int Counter;  //回合
extern int ChessFlag; //先后手
extern int Bans;  //禁手
extern int Depth;  //搜索深度
extern int Mode;
extern int MaxTotal;
extern int MinTotal;
extern int Number;
