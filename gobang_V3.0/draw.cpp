#include "stdafx.h"
#include "draw.h"


void Draw(int BoardPosition[][BOARDSIZE], int Flag, Position PreviousCursor, Position Cursor)
{
	BoardPosition[Cursor.X][Cursor.Y] = Flag;
	if (Flag == 1)
	{
		refresh("○", PreviousCursor.Y * 4 + 2, PreviousCursor.X * 2 + 1);  //覆盖之前的缓冲棋型
		refresh("◆", Cursor.Y * 4 + 2, Cursor.X * 2 + 1);
	}
	else
	{
		refresh("●", PreviousCursor.Y * 4 + 2, PreviousCursor.X * 2 + 1);  //覆盖之前的缓冲棋型
		refresh("◇", Cursor.Y * 4 + 2, Cursor.X * 2 + 1);
	}
}