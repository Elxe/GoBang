#include "stdafx.h"
#include "checkwinner.h"

int CheckWinner(int FlagPosition[][BOARDSIZE], int Flag, Position Current)
{
	int i, j;
	int Left, Right;  //左右两边的同色落子个数
	Counter++;  //加一
	/****************上下方向***************/
	for (i = Current.X - 1, Left = 0; i >= 0 && FlagPosition[i][Current.Y] == Flag; i--, Left++);
	for (i = Current.X + 1, Right = 0; i < BOARDSIZE && FlagPosition[i][Current.Y] == Flag; i++, Right++);
	if (Left + Right >= 4) return Flag;
	/****************左右方向***************/
	for (j = Current.Y - 1, Left = 0; j >= 0 && FlagPosition[Current.X][j] == Flag; j--, Left++);
	for (j = Current.Y + 1, Right = 0; j < BOARDSIZE && FlagPosition[Current.X][j] == Flag; j++, Right++);
	if (Left + Right >= 4) return Flag;
	/****************'\方向***************/
	for (i = Current.X - 1, j = Current.Y - 1, Left = 0; i >= 0 && j >= 0 && FlagPosition[i][j] == Flag; i--, j--, Left++);
	for (i = Current.X + 1, j = Current.Y + 1, Right = 0; i < BOARDSIZE &&j < BOARDSIZE&& FlagPosition[i][j] == Flag; i++, j++, Right++);
	if (Left + Right >= 4) return Flag;
	/****************'/方向***************/
	for (i = Current.X + 1, j = Current.Y - 1, Left = 0; i <BOARDSIZE && j >= 0 && FlagPosition[i][j] == Flag; i++, j--, Left++);
	for (i = Current.X - 1, j = Current.Y + 1, Right = 0; i >= 0 && j < BOARDSIZE&& FlagPosition[i][j] == Flag; i--, j++, Right++);
	if (Left + Right >= 4) return Flag;
	if (Counter >= BOARDSIZE*BOARDSIZE) return DOUBLEWIN;  //平局
	return 0;
}