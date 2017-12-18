#pragma once
#include"refresh.h"
#include "define.h"
#include "displaychessboard.h"

//专门用来转换光标位置
void MoveCursor(Position BuffCursor, Position Cursor);
/**********用于手动下棋时移动光标，返回一个坐标值********/
/**********另外通过错误值的方法返回主菜单，-1为返回主菜单，-2为悔棋*********/
int Control(Position* Cursor, int BoardPosition[][BOARDSIZE], int Flag);
/*******下棋时落子，包括赋值以及覆盖上个位置的棋子，打印新位置的棋子*******/
void Draw(int BoardPosition[][BOARDSIZE], int Flag, Position PreviousCursor, Position Cursor);

//栈结构，先进后出，用于储存落子位置

//传值一个储存落子位置的数组、当前位置、以及栈顶位置；无返回值
void push(Position record[], Position Current);
//传值一个储存落子位置的数组、以及栈顶位置；弹出一个位置
Position pop(Position record[]);

//悔棋，传值棋盘二维数组，当前下棋人，
void regret(int BoardPosition[][BOARDSIZE], int Flag, Position Cursor, Position PreviousCursor, Position Previous);
