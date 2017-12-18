#pragma once

#include "define.h"
#include"refresh.h"
#include"displaychessboard.h"

//栈结构，先进后出，用于储存落子位置

//传值一个储存落子位置的数组、当前位置、以及栈顶位置；无返回值
void push(Position record[], Position Current, int* StackMark);
//传值一个储存落子位置的数组、以及栈顶位置；弹出一个位置
Position pop(Position record[], int* StackMark);
//传值一个储存落子位置的数组、以及栈顶位置；返回一个位置
Position getposition(Position record[], int* StackMark);
//悔棋，传值棋盘二维数组，当前下棋人，
void regret(int BoardPosition[][BOARDSIZE], int Flag, Position Cursor,Position PreviousCursor);
/*******下棋时落子，包括赋值以及覆盖上个位置的棋子，打印新位置的棋子*******/
void Draw(int BoardPosition[][BOARDSIZE], int Flag, Position PreviousCursor, Position Cursor);
