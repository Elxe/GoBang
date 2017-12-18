#pragma once
#include"refresh.h"
#include "define.h"
/*******下棋时落子，包括赋值以及覆盖上个位置的棋子，打印新位置的棋子*******/
void Draw(int BoardPosition[][BOARDSIZE], int Flag, Position PreviousCursor, Position Cursor);
