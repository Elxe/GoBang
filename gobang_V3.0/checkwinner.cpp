#include "stdafx.h"
#include "checkwinner.h"

int CheckWinner(int FlagPosition[][BOARDSIZE], int Flag, Position Current)
{
	int i, j;
	int Left, Right;  //�������ߵ�ͬɫ���Ӹ���
	Counter++;  //��һ
	/****************���·���***************/
	for (i = Current.X - 1, Left = 0; i >= 0 && FlagPosition[i][Current.Y] == Flag; i--, Left++);
	for (i = Current.X + 1, Right = 0; i < BOARDSIZE && FlagPosition[i][Current.Y] == Flag; i++, Right++);
	if (Left + Right >= 4) return Flag;
	/****************���ҷ���***************/
	for (j = Current.Y - 1, Left = 0; j >= 0 && FlagPosition[Current.X][j] == Flag; j--, Left++);
	for (j = Current.Y + 1, Right = 0; j < BOARDSIZE && FlagPosition[Current.X][j] == Flag; j++, Right++);
	if (Left + Right >= 4) return Flag;
	/****************'\����***************/
	for (i = Current.X - 1, j = Current.Y - 1, Left = 0; i >= 0 && j >= 0 && FlagPosition[i][j] == Flag; i--, j--, Left++);
	for (i = Current.X + 1, j = Current.Y + 1, Right = 0; i < BOARDSIZE &&j < BOARDSIZE&& FlagPosition[i][j] == Flag; i++, j++, Right++);
	if (Left + Right >= 4) return Flag;
	/****************'/����***************/
	for (i = Current.X + 1, j = Current.Y - 1, Left = 0; i <BOARDSIZE && j >= 0 && FlagPosition[i][j] == Flag; i++, j--, Left++);
	for (i = Current.X - 1, j = Current.Y + 1, Right = 0; i >= 0 && j < BOARDSIZE&& FlagPosition[i][j] == Flag; i--, j++, Right++);
	if (Left + Right >= 4) return Flag;
	if (Counter >= BOARDSIZE*BOARDSIZE) return DOUBLEWIN;  //ƽ��
	return 0;
}