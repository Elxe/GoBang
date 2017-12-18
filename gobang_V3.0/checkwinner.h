#pragma once
#include "define.h"

/**************每次落子后运行该函数进行检查有无形成五连子***************/
/*****返回检查结果，未检查出五连子为0，黑方胜为1，白方胜为-1，平局为2****/
int CheckWinner(int FlagPosition[][BOARDSIZE], int Flag, Position Current);
