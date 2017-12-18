#include "stdafx.h"
#include "movecursor.h"

void MoveCursor(Position BuffCursor,Position Cursor)
{
	refresh("  ", BuffCursor.Y * 4, BuffCursor.X * 2);
	refresh("  ", BuffCursor.Y * 4 + 4, BuffCursor.X * 2);
	refresh("  ", BuffCursor.Y * 4, BuffCursor.X * 2 + 2);
	refresh("  ", BuffCursor.Y * 4 + 4, BuffCursor.X * 2 + 2);
	refresh("┎", Cursor.Y * 4, Cursor.X * 2);
	refresh("┒", Cursor.Y * 4 + 4, Cursor.X * 2);
	refresh("┖", Cursor.Y * 4, Cursor.X * 2 + 2);
	refresh("┚", Cursor.Y * 4 + 4, Cursor.X * 2 + 2);
}
int Control(Position* Cursor, int BoardPosition[][BOARDSIZE], int Flag)
{
	int Input = 0;  //输入按键信息
	Position BuffCursor,PreviousCursor;  
	PreviousCursor = *Cursor;  //储存上一步位置
	/*************打印初始光标************/
	while (1)  //循环
	{
		BuffCursor = *Cursor;//前一轮落子位置
		Input = _getch();  //第一次读入按键
		if (Input == 224)  //方向键
		{
			Input = _getch();
			switch (Input)
			{
			case 72: Cursor->X--; break;
			case 80: Cursor->X++; break;
			case 75: Cursor->Y--; break;
			case 77: Cursor->Y++; break;
			default:
				break;
			}
			if (Cursor->X < 0) Cursor->X = BOARDSIZE - 1;
			if (Cursor->Y < 0) Cursor->Y = BOARDSIZE - 1;
			if (Cursor->X >= BOARDSIZE) Cursor->X = 0;
			if (Cursor->Y >= BOARDSIZE) Cursor->Y = 0;
			
			MoveCursor(BuffCursor, *Cursor);
			
		}
		else if (Input == 27)  //退出功能
			return -2;
		else if (Input == 8)
		{
			if (Counter>1)
			{
				regret(BoardPosition, Flag, *Cursor, pop(Record), Record[StackMark - 1]);
				*Cursor = Record[StackMark - 1];
				Counter--;
			}
			return -1;
		}
		/************落子************/
		else if ((Input == 13 || Input == 32) && BoardPosition[Cursor->X][Cursor->Y] == 0)
		{
			Draw(BoardPosition, Flag, PreviousCursor, *Cursor);
			return 0;
		}
	}
}
void Draw(int BoardPosition[][BOARDSIZE], int Flag, Position PreviousCursor, Position Cursor)
{
	BoardPosition[Cursor.X][Cursor.Y] = Flag;
	//记录落子情况
	push(Record, Cursor);
	if (Counter == 0)  //刚开始的情况
	{
		if (Flag == BLACK)
			refresh("◆", Cursor.Y * 4 + 2, Cursor.X * 2 + 1);
		else
			refresh("◇", Cursor.Y * 4 + 2, Cursor.X * 2 + 1);
	}
	else
	{
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

}
/******************悔棋********************/
void push(Position record[], Position Current)//入栈
{
		record[StackMark++] = Current;
}
Position pop(Position record[])
{
	if (StackMark >0)
		return record[--StackMark];
	else
	{
		return{7,7};
	}
}
void regret(int BoardPosition[][BOARDSIZE], int Flag, Position Cursor, Position PreviousCursor,Position Previous)
{
	BoardPosition[PreviousCursor.X][PreviousCursor.Y] = BLANK;
	if (Flag == 1)
	{
		refresh(GetBoardStyle(PreviousCursor.X, PreviousCursor.Y), PreviousCursor.Y * 4 + 2, PreviousCursor.X * 2 + 1);  //覆盖之前的缓冲棋型
		refresh("◆", Previous.Y * 4 + 2, Previous.X * 2 + 1);

		MoveCursor(Cursor,Previous);
	}
	else if (Flag == -1)
	{
		refresh(GetBoardStyle(PreviousCursor.X, PreviousCursor.Y), PreviousCursor.Y * 4 + 2, PreviousCursor.X * 2 + 1);  //覆盖之前的缓冲棋型
		refresh("◇", Previous.Y * 4 + 2, Previous.X * 2 + 1);

		MoveCursor(Cursor, Previous);
	}
}