#include "stdafx.h"
#include "movecursor.h"

void MoveCursor(Position BuffCursor,Position Cursor)
{
	refresh("  ", BuffCursor.Y * 4, BuffCursor.X * 2);
	refresh("  ", BuffCursor.Y * 4 + 4, BuffCursor.X * 2);
	refresh("  ", BuffCursor.Y * 4, BuffCursor.X * 2 + 2);
	refresh("  ", BuffCursor.Y * 4 + 4, BuffCursor.X * 2 + 2);
	refresh("��", Cursor.Y * 4, Cursor.X * 2);
	refresh("��", Cursor.Y * 4 + 4, Cursor.X * 2);
	refresh("��", Cursor.Y * 4, Cursor.X * 2 + 2);
	refresh("��", Cursor.Y * 4 + 4, Cursor.X * 2 + 2);
}
int Control(Position* Cursor, int BoardPosition[][BOARDSIZE], int Flag)
{
	int Input = 0;  //���밴����Ϣ
	Position BuffCursor,PreviousCursor;  
	PreviousCursor = *Cursor;  //������һ��λ��
	/*************��ӡ��ʼ���************/
	while (1)  //ѭ��
	{
		BuffCursor = *Cursor;//ǰһ������λ��
		Input = _getch();  //��һ�ζ��밴��
		if (Input == 224)  //�����
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
			//��������
			{
				printf("����=%d\n", GetLian5(BoardPosition, Flag, *Cursor, Bans));
				printf("����=%d\n", GetHuo4(BoardPosition, Flag, *Cursor, Bans));
				printf("����=%d\n", GetChong3Chong4(BoardPosition, Flag, *Cursor, Bans).Chong4);
				printf("������=%d\n", GetChong3Chong4(BoardPosition, Flag, *Cursor, Bans).TiaoChong4);
				printf("����=%d\n", GetHuo2Huo3(BoardPosition, Flag, *Cursor, Bans).Huo3);
				printf("����=%d\n", GetChong3Chong4(BoardPosition, Flag, *Cursor, Bans).Chong3);
				printf("����=%d\n", GetTiao2Tiao3(BoardPosition, Flag, *Cursor, Bans).Tiao3);
				printf("���=%d\n", GetHuo2Huo3(BoardPosition, Flag, *Cursor, Bans).Huo2);
				printf("����=%d\n", GetTiao2Tiao3(BoardPosition, Flag, *Cursor, Bans).Tiao2);
				printf("���=%d\n", GetXiaoQiXing(BoardPosition, Flag, *Cursor, Bans).Chong2);
				printf("��һ=%d\n", GetXiaoQiXing(BoardPosition, Flag, *Cursor, Bans).Huo1);
				printf("��һ=%d\n", GetXiaoQiXing(BoardPosition, Flag, *Cursor, Bans).Chong1);
			}
			
		}
		else if (Input == 27)  //�˳�����
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
		/************����************/
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
	//��¼�������
	push(Record, Cursor);
	if (Counter == 0)  //�տ�ʼ�����
	{
		if (Flag == BLACK)
			refresh("��", Cursor.Y * 4 + 2, Cursor.X * 2 + 1);
		else
			refresh("��", Cursor.Y * 4 + 2, Cursor.X * 2 + 1);
	}
	else
	{
		if (Flag == 1)
		{
			refresh("��", PreviousCursor.Y * 4 + 2, PreviousCursor.X * 2 + 1);  //����֮ǰ�Ļ�������
			refresh("��", Cursor.Y * 4 + 2, Cursor.X * 2 + 1);
		}
		else
		{
			refresh("��", PreviousCursor.Y * 4 + 2, PreviousCursor.X * 2 + 1);  //����֮ǰ�Ļ�������
			refresh("��", Cursor.Y * 4 + 2, Cursor.X * 2 + 1);
		}
	}

}
/******************����********************/
void push(Position record[], Position Current)//��ջ
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
		refresh(GetBoardStyle(PreviousCursor.X, PreviousCursor.Y), PreviousCursor.Y * 4 + 2, PreviousCursor.X * 2 + 1);  //����֮ǰ�Ļ�������
		refresh("��", Previous.Y * 4 + 2, Previous.X * 2 + 1);

		MoveCursor(Cursor,Previous);
	}
	else if (Flag == -1)
	{
		refresh(GetBoardStyle(PreviousCursor.X, PreviousCursor.Y), PreviousCursor.Y * 4 + 2, PreviousCursor.X * 2 + 1);  //����֮ǰ�Ļ�������
		refresh("��", Previous.Y * 4 + 2, Previous.X * 2 + 1);

		MoveCursor(Cursor, Previous);
	}
}