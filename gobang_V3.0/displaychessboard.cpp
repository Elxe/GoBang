#include "stdafx.h"
#include "displaychessboard.h"

char* GetBoardStyle(int x, int y)
{
	if (x == 0)
	{
		if (y == 0) return "��";
		else if (y == BOARDSIZE - 1) return "��";
		else return "��";
	}
	else if (x == BOARDSIZE - 1)
	{
		if (y == 0) return "��";
		else if (y == BOARDSIZE - 1) return "��";
		else return "��";
	}
	else
	{
		if (y == 0) return "��";
		else if (y == BOARDSIZE - 1) return "��";
		else
		{
			if (x == 7 && y == 7) return "�p";
			else if (x == 3 && y == 3) return "�p";
			else if (x == 3 && y == 11) return "�p";
			else if (x == 11 && y == 3) return "�p";
			else if (x == 11 && y == 11) return "�p";
			else return "��";
		}
	}
}
void DisplayChessBoard()
{
	system("cls");  //������д�������ַ�

	/*************��ӡ�������ӵ�**************/
	for (int x = 0; x < BOARDSIZE; x++)
		for (int y = 0; y < BOARDSIZE; y++)
			refresh(GetBoardStyle(x, y), y * 4 + 2, x * 2 + 1);
	/***********��ӡ�������ߺͺ���***********/
	for (int x = 0; x < BOARDSIZE - 1; x++)
		for (int y = 0; y < BOARDSIZE; y++)
		{
			if (y == 0) refresh("��", y * 4 + 2, x * 2 + 2);
			else if (y == BOARDSIZE - 1) refresh("��", y * 4 + 2, x * 2 + 2);
			else refresh("��", y * 4 + 2, x * 2 + 2);
		}
	for (int x = 0; x < BOARDSIZE; x++)
		for (int y = 0; y < BOARDSIZE - 1; y++)
		{
			if (x == 0) refresh("��", y * 4 + 4, x * 2 + 1);
			else if (x == BOARDSIZE - 1) refresh("��", y * 4 + 4, x * 2 + 1);
			else refresh("��", y * 4 + 4, x * 2 + 1);
		}
	/************�м��ӡ���**************/
	refresh("��", 7 * 4, 7 * 2);
	refresh("��", 7 * 4 + 4, 7 * 2);
	refresh("��", 7 * 4, 7 * 2 + 2);
	refresh("��", 7 * 4 + 4, 7 * 2 + 2);
}