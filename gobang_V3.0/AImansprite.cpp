#include "stdafx.h"
#include "AImansprite.h"
//#define DEBUG

typedef struct Chong3Chong4{ int Chong3; int Chong4; int TiaoChong4; } Chong3Chong4;//��¼���������ġ�������
typedef struct Huo2Huo3 { int Huo2; int Huo3; }Huo2Huo3;//��¼����������
typedef struct Tiao2Tiao3 { int Tiao2; int Tiao3; }Tiao2Tiao3;//��¼����������
typedef struct XiaoQiXing { int Chong2; int Huo1; int Chong1; }XiaoQiXing;//��¼�������һ����һ
int ChangLian, Lian5, Huo4, Chong4, TiaoChong4, Huo3, Tiao3, Chong3, Huo2, Tiao2, Chong2, Huo1, Chong1;
//����������������������

//���庯������������������߳��������巵��1����������2���޷���0
int GetLian5(int BoardPosition[][BOARDSIZE], int Flag, Position Coord,int Bans)
{
	int Left, Right, i, j;
	//���᷽��
	for (Left = 0, i = Coord.X - 1; i >= 0&&BoardPosition[i][Coord.Y]==Flag; Left++, i--);
	for (Right = 0, i = Coord.X + 1; i <BOARDSIZE&&BoardPosition[i][Coord.Y]==Flag; Right++, i++);
	if (Left + Right == 4)
		return 1;
	else if (Left + Right >= 5)
		return 2;
	//���᷽��
	for (Left = 0, j = Coord.Y - 1; j >= 0&&BoardPosition[Coord.X][j] == Flag; Left++, j--);
	for (Right = 0, j = Coord.Y + 1; j <BOARDSIZE&&BoardPosition[Coord.X][j] == Flag; Right++, j++);
	if (Left + Right == 4)
		return 1;
	else if (Left + Right >= 5)
		return 2;
	//'\'
	for (Left = 0, i = Coord.X - 1,j=Coord.Y-1; i >= 0&&j>=0&&BoardPosition[i][j] == Flag; Left++, i--,j--);
	for (Right = 0, i = Coord.X + 1, j = Coord.Y + 1;i<BOARDSIZE&&j <BOARDSIZE&&BoardPosition[i][j] == Flag; Right++, i++,j++);
	if (Left + Right == 4)
		return 1;
	else if (Left + Right >= 5)
		return 2;
	//'/'
	for (Left = 0, i = Coord.X + 1, j = Coord.Y - 1; i<BOARDSIZE && j >= 0 && BoardPosition[i][j] == Flag; Left++, i++, j--);
	for (Right = 0, i = Coord.X - 1, j = Coord.Y + 1; i >= 0&&j <BOARDSIZE&&BoardPosition[i][j] == Flag; Right++, i--, j++);
	if (Left + Right == 4)
		return 1;
	else if (Left + Right >= 5)
		return 2;
	return 0;

}
//���ĺ������������������Լ�������������ػ��ĵĸ���
int GetHuo4(int BoardPosition[][BOARDSIZE], int Flag, Position Coord,int Bans)
{
	int Huo4=0,Left, Right, i, j;

	//���᷽��
	for (Left = 0, i = Coord.X - 1; i >= 0 && BoardPosition[i][Coord.Y] == Flag; Left++, i--);
	for (Right = 0, i = Coord.X + 1; i <BOARDSIZE&&BoardPosition[i][Coord.Y] == Flag; Right++, i++);
	if (Left+Right==3)
	{
		if (BoardPosition[Coord.X - Left - 1][Coord.Y] == BLANK&&BoardPosition[Coord.X + Right + 1][Coord.Y] == BLANK
			//���ǽ������
			&& (!(Flag==BLACK&&Bans && (BoardPosition[Coord.X - Left - 2][Coord.Y] == Flag || BoardPosition[Coord.X + Right + 2][Coord.Y] == Flag))))
			Huo4++;
	}

	//���᷽��
	for (Left = 0, j = Coord.Y - 1; j >= 0 && BoardPosition[Coord.X][j] == Flag; Left++, j--);
	for (Right = 0, j = Coord.Y + 1; j <BOARDSIZE&&BoardPosition[Coord.X][j] == Flag; Right++, j++);
	if (Left + Right == 3)
	{
		if (BoardPosition[Coord.X][Coord.Y - Left - 1] == BLANK&&BoardPosition[Coord.X][Coord.Y + Right + 1] == BLANK
			//���ǽ������
			&& (!(Flag==BLACK&&Bans && (BoardPosition[Coord.X][Coord.Y - Left - 2] == Flag || BoardPosition[Coord.X][Coord.Y + Right + 2] == Flag))))
			Huo4++;
	}

	//'\'
	for (Left = 0, i = Coord.X - 1, j = Coord.Y - 1; i >= 0 && j >= 0 && BoardPosition[i][j] == Flag; Left++, i--, j--);
	for (Right = 0, i = Coord.X + 1, j = Coord.Y + 1; i<BOARDSIZE&&j <BOARDSIZE&&BoardPosition[i][j] == Flag; Right++, i++, j++);
	if (Left + Right == 3)
	{
		if (BoardPosition[Coord.X-Left-1][Coord.Y - Left - 1] == BLANK&&BoardPosition[Coord.X + Right + 1][Coord.Y + Right + 1] == BLANK
			//���ǽ������
			&& (!(Flag==BLACK&&Bans && (BoardPosition[Coord.X - Left - 2][Coord.Y - Left - 2] == Flag || BoardPosition[Coord.X + Right + 2][Coord.Y + Right + 2] == Flag))))
			Huo4++;
	}

	//'/'
	for (Left = 0, i = Coord.X + 1, j = Coord.Y - 1; i<BOARDSIZE && j >= 0 && BoardPosition[i][j] == Flag; Left++, i++, j--);
	for (Right = 0, i = Coord.X - 1, j = Coord.Y + 1; i >= 0 && j <BOARDSIZE&&BoardPosition[i][j] == Flag; Right++, i--, j++);
	if (Left + Right == 3)
	{
		if (BoardPosition[Coord.X + Left + 1][Coord.Y - Left - 1] == BLANK&&BoardPosition[Coord.X - Right - 1][Coord.Y + Right + 1] == BLANK
			//���ǽ������
			&& (!(Flag==BLACK&&Bans && (BoardPosition[Coord.X + Left + 2][Coord.Y - Left - 2] == Flag || BoardPosition[Coord.X - Right - 2][Coord.Y + Right + 2] == Flag))))
			Huo4++;
	}
	return Huo4;
}
//���ĳ��������������������ĳ����Լ������ģ�����һ���������ĳ����Լ������ĸ�����һ���ṹ��
Chong3Chong4 GetChong3Chong4(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans)
{
	Chong3Chong4 ChessNum3;//���巵��ֵ
	ChessNum3.Chong3 = 0; ChessNum3.Chong4 = 0; ChessNum3.TiaoChong4 = 0;  //��ʼ��		
	int SpaceLeft, SpaceRight, Left1, Left2, Right1, Right2, i, j;//SpaceΪ�ո����,Left1Ϊ�ո�ǰ�����ӣ�Left2Ϊ�ո������ӣ�Rightͬ��

	//���᷽��
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //������ʼ��
	for (i = Coord.X - 1; i >= 0 && (BoardPosition[i][Coord.Y] == Flag|| BoardPosition[i][Coord.Y] == BLANK)&&SpaceLeft<2;i--)
	{
		if (BoardPosition[i][Coord.Y] == BLANK) SpaceLeft++;//�����ո�
		else if (BoardPosition[i][Coord.Y] == Flag) SpaceLeft ? Left2++ : Left1++; //������������
		else break;
	}
	for (i = Coord.X + 1; i <BOARDSIZE && (BoardPosition[i][Coord.Y] == Flag || BoardPosition[i][Coord.Y] == BLANK) && SpaceRight<2; i++)
	{
		if (BoardPosition[i][Coord.Y] == BLANK) SpaceRight++;//�����ո�
		else if (BoardPosition[i][Coord.Y] == Flag) SpaceRight ? Right2++ : Right1++; //������������
		else break;
	}
	//���������ҶԳ�
	if (Left1 + Left2 + Right1 >= 2)
	{	//��������������߸���һ���Է��ӵ�ס�����
		if ((SpaceLeft == 0 && Left1 + Right1 == 2 && SpaceRight)|| (SpaceLeft&&Left1 + Right1 == 2 && SpaceRight == 0))
			ChessNum3.Chong3++;
	}
	if (Left1 + Right1 + Right2 >= 2)
	{	//��������������߸���һ���Է��ӵ�ס�����
		if ((SpaceLeft == 0 && Left1 + Right1 == 2 && SpaceRight) || (SpaceLeft&&Left1 + Right1 == 2 && SpaceRight == 0))
			ChessNum3.Chong3++;
	}
	//���ĵ����,���ҶԳ� 
	if (Left1 + Left2 + Right1 >= 3)
	{
		if (SpaceLeft == 0 && Left1 + Right1 == 2 && SpaceRight)
			ChessNum3.TiaoChong4++;
		if (SpaceLeft && Left1 < 3 && Right1 < 3 && Left2)
			ChessNum3.Chong4++;
	}
	if (Left1 + Right1 + Right2 >= 3)
	{
		if (SpaceRight == 0 && Left1 + Right1 == 2 && SpaceLeft)
			ChessNum3.TiaoChong4++;
		if (SpaceRight && Left1 < 3 && Right1 < 3 && Right2)
			ChessNum3.Chong4++;
	}

	//���᷽��
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //������ʼ��
	for (j = Coord.Y - 1; j >= 0 && (BoardPosition[Coord.X][j] == Flag || BoardPosition[Coord.X][j] == BLANK) && SpaceLeft<2; j--)
	{
		if (BoardPosition[Coord.X][j] == BLANK) SpaceLeft++;//�����ո�
		else if (BoardPosition[Coord.X][j] == Flag) SpaceLeft ? Left2++ : Left1++; //������������
		else break;
	}
	for (j = Coord.Y + 1; j <BOARDSIZE && (BoardPosition[Coord.X][j] == Flag || BoardPosition[Coord.X][j] == BLANK) && SpaceRight<2; j++)
	{
		if (BoardPosition[Coord.X][j] == BLANK) SpaceRight++;//�����ո�
		else if (BoardPosition[Coord.X][j] == Flag) SpaceRight ? Right2++ : Right1++; //������������
		else break;
	}
	//���������ҶԳ�
	if (Left1 + Left2 + Right1 >= 2)
	{	//��������������߸���һ���Է��ӵ�ס�����
		if ((SpaceLeft == 0 && Left1 + Right1 == 2 && SpaceRight) || (SpaceLeft&&Left1 + Right1 == 2 && SpaceRight == 0))
			ChessNum3.Chong3++;
	}
	if (Left1 + Right1 + Right2 >= 2)
	{	//��������������߸���һ���Է��ӵ�ס�����
		if ((SpaceLeft == 0 && Left1 + Right1 == 2 && SpaceRight) || (SpaceLeft&&Left1 + Right1 == 2 && SpaceRight == 0))
			ChessNum3.Chong3++;
	}
	//���ĵ����,���ҶԳ� 
	if (Left1 + Left2 + Right1 >= 3)
	{
		if (SpaceLeft == 0 && Left1 + Right1 == 2 && SpaceRight)
			ChessNum3.TiaoChong4++;
		if (SpaceLeft && Left1 < 3 && Right1 < 3 && Left2)
			ChessNum3.Chong4++;
	}
	if (Left1 + Right1 + Right2 >= 3)
	{
		if (SpaceRight == 0 && Left1 + Right1 == 2 && SpaceLeft)
			ChessNum3.TiaoChong4++;
		if (SpaceRight && Left1 < 3 && Right1 < 3 && Right2)
			ChessNum3.Chong4++;
	}

	//'\'����
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //������ʼ��
	for (i=Coord.X-1, j = Coord.Y - 1; i>=0 && j >= 0 && (BoardPosition[i][j] == Flag || BoardPosition[i][j] == BLANK) && SpaceLeft<2;i--, j--)
	{
		if (BoardPosition[i][j] == BLANK) SpaceLeft++;//�����ո�
		else if (BoardPosition[i][j] == Flag) SpaceLeft ? Left2++ : Left1++; //������������
		else break;
	}
	for (i=Coord.X+1, j = Coord.Y + 1; i<BOARDSIZE && j <BOARDSIZE && (BoardPosition[i][j] == Flag || BoardPosition[i][j] == BLANK) && SpaceRight<2; i++,j++)
	{
		if (BoardPosition[i][j] == BLANK) SpaceRight++;//�����ո�
		else if (BoardPosition[i][j] == Flag) SpaceRight ? Right2++ : Right1++; //������������
		else break;
	}
	//���������ҶԳ�
	if (Left1 + Left2 + Right1 >= 2)
	{	//��������������߸���һ���Է��ӵ�ס�����
		if ((SpaceLeft == 0 && Left1 + Right1 == 2 && SpaceRight) || (SpaceLeft&&Left1 + Right1 == 2 && SpaceRight == 0))
			ChessNum3.Chong3++;
	}
	if (Left1 + Right1 + Right2 >= 2)
	{	//��������������߸���һ���Է��ӵ�ס�����
		if ((SpaceLeft == 0 && Left1 + Right1 == 2 && SpaceRight) || (SpaceLeft&&Left1 + Right1 == 2 && SpaceRight == 0))
			ChessNum3.Chong3++;
	}
	//���ĵ����,���ҶԳ� 
	if (Left1 + Left2 + Right1 >= 3)
	{
		if (SpaceLeft == 0 && Left1 + Right1 == 2 && SpaceRight)
			ChessNum3.TiaoChong4++;
		if (SpaceLeft && Left1 < 3 && Right1 < 3 && Left2)
			ChessNum3.Chong4++;
	}
	if (Left1 + Right1 + Right2 >= 3)
	{
		if (SpaceRight == 0 && Left1 + Right1 == 2 && SpaceLeft)
			ChessNum3.TiaoChong4++;
		if (SpaceRight && Left1 < 3 && Right1 < 3 && Right2)
			ChessNum3.Chong4++;
	}

	//'/'����
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //������ʼ��
	for (i = Coord.X + 1, j = Coord.Y - 1; i<BOARDSIZE && j >= 0 && (BoardPosition[i][j] == Flag || BoardPosition[i][j] == BLANK) && SpaceLeft<2; i++, j--)
	{
		if (BoardPosition[i][j] == BLANK) SpaceLeft++;//�����ո�
		else if (BoardPosition[i][j] == Flag) SpaceLeft ? Left2++ : Left1++; //������������
		else break;
	}
	for (i = Coord.X - 1, j = Coord.Y + 1; i >= 0 && j <BOARDSIZE && (BoardPosition[i][j] == Flag || BoardPosition[i][j] == BLANK) && SpaceRight<2; i--, j++)
	{
		if (BoardPosition[i][j] == BLANK) SpaceRight++;//�����ո�
		else if (BoardPosition[i][j] == Flag) SpaceRight ? Right2++ : Right1++; //������������
		else break;
	}
	//���������ҶԳ�
	if (Left1 + Left2 + Right1 >= 2)
	{	//��������������߸���һ���Է��ӵ�ס�����
		if ((SpaceLeft == 0 && Left1 + Right1 == 2 && SpaceRight) || (SpaceLeft&&Left1 + Right1 == 2 && SpaceRight == 0))
			ChessNum3.Chong3++;
	}
	if (Left1 + Right1 + Right2 >= 2)
	{	//��������������߸���һ���Է��ӵ�ס�����
		if ((SpaceLeft == 0 && Left1 + Right1 == 2 && SpaceRight) || (SpaceLeft&&Left1 + Right1 == 2 && SpaceRight == 0))
			ChessNum3.Chong3++;
	}
	//���ĵ����,���ҶԳ� 
	if (Left1 + Left2 + Right1 >= 3)
	{
		if (SpaceLeft == 0 && Left1 + Right1 == 2 && SpaceRight)
			ChessNum3.TiaoChong4++;
		if (SpaceLeft && Left1 < 3 && Right1 < 3 && Left2)
			ChessNum3.Chong4++;
	}
	if (Left1 + Right1 + Right2 >= 3)
	{
		if (SpaceRight == 0 && Left1 + Right1 == 2 && SpaceLeft)
			ChessNum3.TiaoChong4++;
		if (SpaceRight && Left1 < 3 && Right1 < 3 && Right2)
			ChessNum3.Chong4++;
	}
	return ChessNum3;
}
//������������������������������������һ��������������������һ���ṹ��
Huo2Huo3 GetHuo2Huo3(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans)
{
	int Left, Right, i, j, SpaceLeft, SpaceRight;
	Huo2Huo3 ChessNum2;//���巵��ֵ
	ChessNum2.Huo2 = 0; ChessNum2.Huo3 = 0;//��ʼ��

	//���᷽��
	for (Left = 0, i = Coord.X - 1; i >= 0 && BoardPosition[i][Coord.Y] == Flag; Left++, i--);
	for (Right = 0, i = Coord.X + 1; i <BOARDSIZE&&BoardPosition[i][Coord.Y] == Flag; Right++, i++);
	if (Left+Right==1)
	{
		for (SpaceLeft=0, i = Coord.X - Left - 1; i >= 0 && BoardPosition[i][Coord.Y] == BLANK; SpaceLeft++, i--);
		for (SpaceRight = 0, i = Coord.X + Right + 1; i <BOARDSIZE && BoardPosition[i][Coord.Y] == BLANK; SpaceRight++, i++);
		if (SpaceLeft && SpaceRight && SpaceLeft + SpaceRight >= 4) ChessNum2.Huo2++;
	}
	if (Left+Right==2)
	{	//���ĵ����
		if (!(Coord.X-Left-2>=0&&BoardPosition[Coord.X - Left - 2][Coord.Y]==Flag)
			&&!(Coord.X + Right + 2 >= 0 && BoardPosition[Coord.X +Right+2][Coord.Y] == Flag))
		{		
			for (SpaceLeft = 0, i = Coord.X - Left - 1; i >= 0 && BoardPosition[i][Coord.Y] == BLANK; SpaceLeft++, i--);
			for (SpaceRight = 0, i = Coord.X + Right + 1; i <BOARDSIZE && BoardPosition[i][Coord.Y] == BLANK; SpaceRight++, i++);
			if (SpaceLeft && SpaceRight && SpaceLeft + SpaceRight >= 3) ChessNum2.Huo3++;
		}
	}

	//���᷽��
	for (Left = 0, j = Coord.Y - 1; j >= 0 && BoardPosition[Coord.X][j] == Flag; Left++, j--);
	for (Right = 0, j = Coord.Y + 1; j <BOARDSIZE&&BoardPosition[Coord.X][j] == Flag; Right++, j++);
	if (Left + Right == 1)
	{
		for (SpaceLeft = 0, j = Coord.Y - Left - 1; j >= 0 && BoardPosition[Coord.X][j] == BLANK; SpaceLeft++, j--);
		for (SpaceRight = 0, j = Coord.Y + Right + 1; j <BOARDSIZE && BoardPosition[Coord.X][j] == BLANK; SpaceRight++, j++);
		if (SpaceLeft && SpaceRight && SpaceLeft + SpaceRight >= 4) ChessNum2.Huo2++;
	}
	if (Left + Right == 2)
	{	//���ĵ����
		if (!(Coord.Y - Left - 2 >= 0 && BoardPosition[Coord.X][Coord.Y - Left - 2] == Flag)
			&& !(Coord.Y + Right + 2 >= 0 && BoardPosition[Coord.X][Coord.Y + Right + 2] == Flag))
		{
			for (SpaceLeft = 0, j = Coord.Y - Left - 1; j >= 0 && BoardPosition[Coord.X][j] == BLANK; SpaceLeft++, j--);
			for (SpaceRight = 0, j = Coord.Y + Right + 1; j <BOARDSIZE && BoardPosition[Coord.X][j] == BLANK; SpaceRight++, j++);
			if (SpaceLeft && SpaceRight && SpaceLeft + SpaceRight >= 3) ChessNum2.Huo3++;
		}
	}

	//'\'����
	for (Left = 0, i = Coord.X - 1, j = Coord.Y - 1; i >= 0 && j >= 0 && BoardPosition[i][j] == Flag; Left++, i--, j--);
	for (Right = 0, i = Coord.X + 1, j = Coord.Y + 1; i<BOARDSIZE&&j <BOARDSIZE&&BoardPosition[i][j] == Flag; Right++, i++, j++);
	if (Left + Right == 1)
	{
		for (SpaceLeft = 0, i = Coord.X - Left - 1, j = Coord.Y - Left - 1;i>=0 && j >= 0 && BoardPosition[i][j] == BLANK; SpaceLeft++,i--,j--);
		for (SpaceRight = 0, i = Coord.X +Left + 1, j = Coord.Y + Right + 1;i<BOARDSIZE&& j <BOARDSIZE && BoardPosition[i][j] == BLANK; SpaceRight++,i++,j++);
		if (SpaceLeft && SpaceRight && SpaceLeft + SpaceRight >= 4) ChessNum2.Huo2++;
	}
	if (Left + Right == 2)
	{	//���ĵ����
		if (!(Coord.X - Left - 2 >= 0 &&Coord.Y - Left - 2 >= 0 && BoardPosition[Coord.X - Left - 2][Coord.Y - Left - 2] == Flag)
			&& !(Coord.X + Left + 2 <BOARDSIZE && Coord.Y + Right + 2 <BOARDSIZE && BoardPosition[Coord.X + Left + 2][Coord.Y + Right + 2] == Flag))
		{
			for (SpaceLeft = 0, i = Coord.X - Left - 1, j = Coord.Y - Left - 1; i >= 0 && j >= 0 && BoardPosition[i][j] == BLANK; SpaceLeft++, i--, j--);
			for (SpaceRight = 0, i = Coord.X + Left + 1, j = Coord.Y + Right + 1; i<BOARDSIZE&& j <BOARDSIZE && BoardPosition[i][j] == BLANK; SpaceRight++, i++, j++);
			if (SpaceLeft && SpaceRight && SpaceLeft + SpaceRight >= 3) ChessNum2.Huo3++;
		}
	}

	//'/'����
	for (Left = 0, i = Coord.X + 1, j = Coord.Y - 1; i<BOARDSIZE && j >= 0 && BoardPosition[i][j] == Flag; Left++, i++, j--);
	for (Right = 0, i = Coord.X - 1, j = Coord.Y + 1; i >= 0&&j <BOARDSIZE&&BoardPosition[i][j] == Flag; Right++, i--, j++);
	if (Left + Right == 1)
	{
		for (SpaceLeft = 0, i = Coord.X + Left + 1, j = Coord.Y - Left - 1; i<BOARDSIZE && j >= 0 && BoardPosition[i][j] == BLANK; SpaceLeft++, i++, j--);
		for (SpaceRight = 0, i = Coord.X - Left - 1, j = Coord.Y + Right + 1; i >= 0&& j <BOARDSIZE && BoardPosition[i][j] == BLANK; SpaceRight++, i--, j++);
		if (SpaceLeft && SpaceRight && SpaceLeft + SpaceRight >= 4) ChessNum2.Huo2++;
	}
	if (Left + Right == 2)
	{	//���ĵ����
		if (!(Coord.X + Left + 2 <BOARDSIZE && Coord.Y - Left - 2 >= 0 && BoardPosition[Coord.X + Left + 2][Coord.Y - Left - 2] == Flag)
			&& !(Coord.X - Left - 2 >= 0 && Coord.Y + Right + 2 <BOARDSIZE && BoardPosition[Coord.X - Left - 2][Coord.Y + Right + 2] == Flag))
		{
			for (SpaceLeft = 0, i = Coord.X + Left + 1, j = Coord.Y - Left - 1; i<BOARDSIZE && j >= 0 && BoardPosition[i][j] == BLANK; SpaceLeft++, i++, j--);
			for (SpaceRight = 0, i = Coord.X - Left - 1, j = Coord.Y + Right + 1; i >= 0 && j <BOARDSIZE && BoardPosition[i][j] == BLANK; SpaceRight++, i--, j++);
			if (SpaceLeft && SpaceRight && SpaceLeft + SpaceRight >= 3) ChessNum2.Huo3++;
		}
	}
	return ChessNum2;

}
//���������������������������������������һ�������������������Ľṹ��
Tiao2Tiao3 GetTiao2Tiao3(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans)
{
	Tiao2Tiao3 ChessNum1; //���巵��ֵ
	ChessNum1.Tiao2 = 0; ChessNum1.Tiao3 = 0;  //��ʼ��		
	int SpaceLeft, SpaceRight, Left1, Left2, Right1, Right2, i, j;//SpaceΪ�ո����,Left1Ϊ�ո�ǰ�����ӣ�Left2Ϊ�ո������ӣ�Rightͬ��

	//���᷽��
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //������ʼ��
	for (i = Coord.X - 1; i >= 0 && (BoardPosition[i][Coord.Y] == Flag || BoardPosition[i][Coord.Y] == BLANK) && SpaceLeft<2; i--)
	{
		if (BoardPosition[i][Coord.Y] == BLANK) SpaceLeft++;//�����ո�
		else if (BoardPosition[i][Coord.Y] == Flag) SpaceLeft ? Left2++ : Left1++; //������������
		else break;
	}
	for (i = Coord.X + 1; i <BOARDSIZE && (BoardPosition[i][Coord.Y] == Flag || BoardPosition[i][Coord.Y] == BLANK) && SpaceRight<2; i++)
	{
		if (BoardPosition[i][Coord.Y] == BLANK) SpaceRight++;//�����ո�
		else if (BoardPosition[i][Coord.Y] == Flag) SpaceRight ? Right2++ : Right1++; //������������
		else break;
	}//����������Ӽ���һ���ո�����Χ�ո���Ϊ4��
	if ((Left1+Left2+Right1+Right2==1&& SpaceLeft == 2 && SpaceRight == 2)&&((Left2==1)^(Right2==1)))
		ChessNum1.Tiao2++;
	if ((Left1 + Left2 + Right1 + Right2 == 2) && ((Left1 == 1) ^ (Right1 == 1))
		&& (Left2 == 1 && SpaceLeft == 2 && SpaceRight >= 1) && (Right2 == 1 && SpaceLeft >= 1 && SpaceRight == 2))
		ChessNum1.Tiao3++;

	//���᷽��
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //������ʼ��
	for (j = Coord.Y - 1; j >= 0 && (BoardPosition[Coord.X][j] == Flag || BoardPosition[Coord.X][j] == BLANK) && SpaceLeft<2; j--)
	{
		if (BoardPosition[Coord.X][j] == BLANK) SpaceLeft++;//�����ո�
		else if (BoardPosition[Coord.X][j] == Flag) SpaceLeft ? Left2++ : Left1++; //������������
		else break;
	}
	for (j = Coord.Y + 1; j <BOARDSIZE && (BoardPosition[Coord.X][j] == Flag || BoardPosition[Coord.X][j] == BLANK) && SpaceRight<2; j++)
	{
		if (BoardPosition[Coord.X][j] == BLANK) SpaceRight++;//�����ո�
		else if (BoardPosition[Coord.X][j] == Flag) SpaceRight ? Right2++ : Right1++; //������������
		else break;
	}//����������Ӽ���һ���ո�����Χ�ո���Ϊ4��
	if ((Left1 + Left2 + Right1 + Right2 == 1 && SpaceLeft == 2 && SpaceRight == 2) && ((Left2 == 1) ^ (Right2 == 1)))
		ChessNum1.Tiao2++;
	if ((Left1 + Left2 + Right1 + Right2 == 2) && ((Left1 == 1) ^ (Right1 == 1))
		&& (Left2 == 1 && SpaceLeft == 2 && SpaceRight >= 1) && (Right2 == 1 && SpaceLeft >= 1 && SpaceRight == 2))
		ChessNum1.Tiao3++;

	//'\'����
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //������ʼ��
	for (j = Coord.Y - 1; j >= 0 && (BoardPosition[Coord.X][j] == Flag || BoardPosition[Coord.X][j] == BLANK) && SpaceLeft<2; j--)
	{
		if (BoardPosition[Coord.X][j] == BLANK) SpaceLeft++;//�����ո�
		else if (BoardPosition[Coord.X][j] == Flag) SpaceLeft ? Left2++ : Left1++; //������������
		else break;
	}
	for (j = Coord.Y + 1; j <BOARDSIZE && (BoardPosition[Coord.X][j] == Flag || BoardPosition[Coord.X][j] == BLANK) && SpaceRight<2; j++)
	{
		if (BoardPosition[Coord.X][j] == BLANK) SpaceRight++;//�����ո�
		else if (BoardPosition[Coord.X][j] == Flag) SpaceRight ? Right2++ : Right1++; //������������
		else break;
	}//����������Ӽ���һ���ո�����Χ�ո���Ϊ4��
	if ((Left1 + Left2 + Right1 + Right2 == 1 && SpaceLeft == 2 && SpaceRight == 2) && ((Left2 == 1) ^ (Right2 == 1)))
		ChessNum1.Tiao2++;
	if ((Left1 + Left2 + Right1 + Right2 == 2) && ((Left1 == 1) ^ (Right1 == 1))
		&& (Left2 == 1 && SpaceLeft == 2 && SpaceRight >= 1) && (Right2 == 1 && SpaceLeft >= 1 && SpaceRight == 2))
		ChessNum1.Tiao3++;

	//'/'����
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //������ʼ��
	for (i = Coord.X + 1, j = Coord.Y - 1; i<BOARDSIZE && j >= 0 && (BoardPosition[i][j] == Flag || BoardPosition[i][j] == BLANK) && SpaceLeft<2; i++, j--)
	{
		if (BoardPosition[i][j] == BLANK) SpaceLeft++;//�����ո�
		else if (BoardPosition[i][j] == Flag) SpaceLeft ? Left2++ : Left1++; //������������
		else break;
	}
	for (i = Coord.X - 1, j = Coord.Y + 1; i >= 0 && j <BOARDSIZE && (BoardPosition[i][j] == Flag || BoardPosition[i][j] == BLANK) && SpaceRight<2; i--, j++)
	{
		if (BoardPosition[i][j] == BLANK) SpaceRight++;//�����ո�
		else if (BoardPosition[i][j] == Flag) SpaceRight ? Right2++ : Right1++; //������������
		else break;
	}//����������Ӽ���һ���ո�����Χ�ո���Ϊ4��
	if ((Left1 + Left2 + Right1 + Right2 == 1 && SpaceLeft == 2 && SpaceRight == 2) && ((Left2 == 1) ^ (Right2 == 1)))
		ChessNum1.Tiao2++;
	if ((Left1 + Left2 + Right1 + Right2 == 2) && ((Left1 == 1) ^ (Right1 == 1))
		&& (Left2 == 1 && SpaceLeft == 2 && SpaceRight >= 1) && (Right2 == 1 && SpaceLeft >= 1 && SpaceRight == 2))
		ChessNum1.Tiao3++;

	return ChessNum1;

}
//С���ͺ������������������ϴ�������������ͣ�������һ����һ�����
XiaoQiXing GetXiaoQiXing(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans)
{
	XiaoQiXing ChessNum0;//���巵��ֵ
	ChessNum0.Chong1 = 0; ChessNum0.Chong2 = 0; ChessNum0.Huo1 = 0;  //��ʼ��		
	int SpaceLeft, SpaceRight, Left1, Left2, Right1, Right2, i, j;//SpaceΪ�ո����,Left1Ϊ�ո�ǰ�����ӣ�Left2Ϊ�ո������ӣ�Rightͬ��

	//���᷽��
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //������ʼ��
	for (i = Coord.X - 1; i >= 0 && (BoardPosition[i][Coord.Y] == Flag || BoardPosition[i][Coord.Y] == BLANK) && SpaceLeft<2; i--)
	{
		if (BoardPosition[i][Coord.Y] == BLANK) SpaceLeft++;//�����ո�
		else if (BoardPosition[i][Coord.Y] == Flag) SpaceLeft ? Left2++ : Left1++; //������������
		else break;
	}
	for (i = Coord.X + 1; i <BOARDSIZE && (BoardPosition[i][Coord.Y] == Flag || BoardPosition[i][Coord.Y] == BLANK) && SpaceRight<2; i++)
	{
		if (BoardPosition[i][Coord.Y] == BLANK) SpaceRight++;//�����ո�
		else if (BoardPosition[i][Coord.Y] == Flag) SpaceRight ? Right2++ : Right1++; //������������
		else break;
	}
	//�����ж�����
	//���߸���һ���Է������赲
	if (Left1 + Left2 + Right1 + Right2 == 0)
	{
		if (((SpaceLeft == 0 && SpaceRight == 2 && Coord.X + 4<BOARDSIZE && BoardPosition[Coord.X + 3][Coord.Y] == BLANK&&BoardPosition[Coord.X + 4][Coord.Y] == BLANK)
			|| (SpaceLeft == 2 && SpaceRight == 0 && Coord.Y - 4 >= 0 && BoardPosition[Coord.X - 3][Coord.Y] == BLANK&&BoardPosition[Coord.X - 4][Coord.Y] == BLANK)))
			ChessNum0.Chong1++;
		if (SpaceLeft == 2 && SpaceRight == 2)
			ChessNum0.Huo1++;
	}
	if (Left1 + Left2 + Right1 + Right2 == 1&&(Left1||Right1))
	{
		if ((SpaceLeft == 0 && SpaceRight == 2 && Coord.Y + 3<BOARDSIZE&&BoardPosition[Coord.X + 3][Coord.Y] == BLANK)
			|| (SpaceLeft == 2 && SpaceRight == 0 &&  Coord.Y - 3 >= 0&& BoardPosition[Coord.X - 3][Coord.Y] == BLANK))
			ChessNum0.Chong2++;
	}

	//���᷽��
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //������ʼ��
	for (j = Coord.Y - 1; j >= 0 && (BoardPosition[Coord.X][j] == Flag || BoardPosition[Coord.X][j] == BLANK) && SpaceLeft<2; j--)
	{
		if (BoardPosition[Coord.X][j] == BLANK) SpaceLeft++;//�����ո�
		else if (BoardPosition[Coord.X][j] == Flag) SpaceLeft ? Left2++ : Left1++; //������������
		else break;
	}
	for (j = Coord.Y + 1; j <BOARDSIZE && (BoardPosition[Coord.X][j] == Flag || BoardPosition[Coord.X][j] == BLANK) && SpaceRight<2; j++)
	{
		if (BoardPosition[Coord.X][j] == BLANK) SpaceRight++;//�����ո�
		else if (BoardPosition[Coord.X][j] == Flag) SpaceRight ? Right2++ : Right1++; //������������
		else break;
	}
	//�����ж�����
	//���߸���һ���Է������赲
	if (Left1 + Left2 + Right1 + Right2 == 0)
	{
		if (((SpaceLeft == 0 && SpaceRight == 2 &&Coord.Y+4<BOARDSIZE&&BoardPosition[Coord.X][Coord.Y + 3] == BLANK&&BoardPosition[Coord.X][Coord.Y + 4] == BLANK)
			|| (SpaceLeft == 2 && SpaceRight == 0 && Coord.Y - 4>=0&& BoardPosition[Coord.X][Coord.Y - 3] == BLANK&&BoardPosition[Coord.X][Coord.Y - 4] == BLANK)))
			ChessNum0.Chong1++;
		if (SpaceLeft == 2 && SpaceRight == 2)
			ChessNum0.Huo1++;
	}
	if (Left1 + Left2 + Right1 + Right2 == 1 && (Left1 || Right1))
	{
		if ((SpaceLeft == 0 && SpaceRight == 2 && Coord.Y + 3<BOARDSIZE&& BoardPosition[Coord.X][Coord.Y + 3] == BLANK)
			|| (SpaceLeft == 2 && SpaceRight == 0 && Coord.Y - 3 >= 0 && BoardPosition[Coord.X][Coord.Y - 3] == BLANK))
			ChessNum0.Chong2++;
	}

	//'\'����
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //������ʼ��
	for (i = Coord.X - 1, j = Coord.Y - 1; i >= 0 && j >= 0 && (BoardPosition[i][j] == Flag || BoardPosition[i][j] == BLANK) && SpaceLeft<2; i--, j--)
	{
		if (BoardPosition[i][j] == BLANK) SpaceLeft++;//�����ո�
		else if (BoardPosition[i][j] == Flag) SpaceLeft ? Left2++ : Left1++; //������������
		else break;
	}
	for (i = Coord.X + 1, j = Coord.Y + 1; i<BOARDSIZE && j <BOARDSIZE && (BoardPosition[i][j] == Flag || BoardPosition[i][j] == BLANK) && SpaceRight<2; i++, j++)
	{
		if (BoardPosition[i][j] == BLANK) SpaceRight++;//�����ո�
		else if (BoardPosition[i][j] == Flag) SpaceRight ? Right2++ : Right1++; //������������
		else break;
	}
	//�����ж�����
	//���߸���һ���Է������赲
	if (Left1 + Left2 + Right1 + Right2 == 0)
	{
		if (((SpaceLeft == 0 && SpaceRight == 2 && Coord.Y + 4<BOARDSIZE&&Coord.X + 4<BOARDSIZE&&BoardPosition[Coord.X+3][Coord.Y + 3] == BLANK&&BoardPosition[Coord.X+4][Coord.Y + 4] == BLANK)
			|| (SpaceLeft == 2 && SpaceRight == 0 && Coord.Y - 4 >= 0&& Coord.X - 4 >= 0 && BoardPosition[Coord.X-3][Coord.Y - 3] == BLANK&&BoardPosition[Coord.X-4][Coord.Y - 4] == BLANK)))
			ChessNum0.Chong1++;
		if (SpaceLeft == 2 && SpaceRight == 2)
			ChessNum0.Huo1++;
	}
	if (Left1 + Left2 + Right1 + Right2 == 1 && (Left1 || Right1))
	{
		if ((SpaceLeft == 0 && SpaceRight == 2 && Coord.Y + 3<BOARDSIZE&&Coord.X + 3<BOARDSIZE&& BoardPosition[Coord.X+3][Coord.Y + 3] == BLANK)
			|| (SpaceLeft == 2 && SpaceRight == 0 && Coord.Y - 3 >= 0 && Coord.X - 3 >= 0 && BoardPosition[Coord.X-3][Coord.Y - 3] == BLANK))
			ChessNum0.Chong2++;
	}

	//'/'����
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //������ʼ��
	for (i = Coord.X + 1, j = Coord.Y - 1; i<BOARDSIZE && j >= 0 && (BoardPosition[i][j] == Flag || BoardPosition[i][j] == BLANK) && SpaceLeft<2; i++, j--)
	{
		if (BoardPosition[i][j] == BLANK) SpaceLeft++;//�����ո�
		else if (BoardPosition[i][j] == Flag) SpaceLeft ? Left2++ : Left1++; //������������
		else break;
	}
	for (i = Coord.X - 1, j = Coord.Y + 1; i >= 0 && j <BOARDSIZE && (BoardPosition[i][j] == Flag || BoardPosition[i][j] == BLANK) && SpaceRight<2; i--, j++)
	{
		if (BoardPosition[i][j] == BLANK) SpaceRight++;//�����ո�
		else if (BoardPosition[i][j] == Flag) SpaceRight ? Right2++ : Right1++; //������������
		else break;
	}
	//�����ж�����
	//���߸���һ���Է������赲
	if (Left1 + Left2 + Right1 + Right2 == 0)
	{
		if (((SpaceLeft == 0 && SpaceRight == 2 && Coord.Y + 4<BOARDSIZE&&Coord.X - 4 >= 0&&BoardPosition[Coord.X - 3][Coord.Y + 3] == BLANK&&BoardPosition[Coord.X - 4][Coord.Y + 4] == BLANK)
			|| (SpaceLeft == 2 && SpaceRight == 0 && Coord.Y - 4 >= 0 && Coord.X + 4<BOARDSIZE && BoardPosition[Coord.X + 3][Coord.Y - 3] == BLANK&&BoardPosition[Coord.X + 4][Coord.Y - 4] == BLANK)))
			ChessNum0.Chong1++;
		if (SpaceLeft == 2 && SpaceRight == 2)
			ChessNum0.Huo1++;
	}
	if (Left1 + Left2 + Right1 + Right2 == 1 && (Left1 || Right1))
	{
		if ((SpaceLeft == 0 && SpaceRight == 2 && Coord.Y + 3<BOARDSIZE&&Coord.X - 3 >= 0&& BoardPosition[Coord.X - 3][Coord.Y + 3] == BLANK)
			|| (SpaceLeft == 2 && SpaceRight == 0 && Coord.Y - 3 >= 0 && Coord.X + 3<BOARDSIZE && BoardPosition[Coord.X+3][Coord.Y - 3] == BLANK))
			ChessNum0.Chong2++;
	}
	
	return ChessNum0;
}
//��ø������͸���
void GetBoardType(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans)
{
	//��ʼ��
	ChangLian = Lian5 = Huo4 = Chong4 = TiaoChong4 = Huo3 = Tiao3 = Chong3 = Huo2 = Tiao2 = Chong2 = Huo1 = Chong1 = 0;
	switch (GetLian5(BoardPosition,Flag,Coord,Bans))
	{
	case 1:
		Lian5++;
		break;
	case 2:
		ChangLian++;
	default:
		break;
	}
	Huo4 += GetHuo4(BoardPosition, Flag, Coord, Bans);
	Chong4 += GetChong3Chong4(BoardPosition, Flag, Coord, Bans).Chong4;
	TiaoChong4 += GetChong3Chong4(BoardPosition, Flag, Coord, Bans).TiaoChong4;
	Huo3 += GetHuo2Huo3(BoardPosition, Flag, Coord, Bans).Huo3;
	Tiao3 += GetTiao2Tiao3(BoardPosition, Flag, Coord, Bans).Tiao3;
	Chong3 += GetChong3Chong4(BoardPosition, Flag, Coord, Bans).Chong3;
	Huo2 += GetHuo2Huo3(BoardPosition, Flag, Coord, Bans).Huo2;
	Tiao2 += GetTiao2Tiao3(BoardPosition, Flag, Coord, Bans).Tiao2;
	Chong2 += GetXiaoQiXing(BoardPosition, Flag, Coord, Bans).Chong2;
	Huo1 += GetXiaoQiXing(BoardPosition, Flag, Coord, Bans).Huo1;
	Chong1 += GetXiaoQiXing(BoardPosition, Flag, Coord, Bans).Chong1;
}
//�ж��Ƿ���֣����ǽ��ַ���0����������1���������ַ���2�����Ľ��ַ���3
int IfBans(int BoardPosition[][BOARDSIZE],int Flag, Position Coord,int Bans)
{
	if (!Bans || !(Flag == BLACK))
		return 0;
	else
	{
		GetBoardType(BoardPosition, Flag, Coord, Bans);

		if (ChangLian)
			return 1;
		//����������γ������ͬʱ�����γ����������Ľ��֣���ô���Ǻ����ʤ
		if (Lian5)
			return 0;
		if (Huo3 + Tiao3 >= 2)
			return 2;
		if (Huo4 + Chong4 + TiaoChong4 >= 2)
			return 3;

		return 0;
	}

}
//���ֺ���������ǰλ������
int GetScore(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans)
{
	int Score=10;
	if (Bans&&Flag == BLACK&&IfBans(BoardPosition, Flag, Coord, Bans))
		return -1;
	if (Flag==-ChessFlag)//�����ķ�������
	{
		GetBoardType(BoardPosition, Flag, Coord, Bans);
		//���������Ӯ�����͸�ֵ
		if (ChangLian || Lian5)
			Score += 5000000;
		if (Huo4)
			Score += 250000;
		if (Chong4 + TiaoChong4 >= 2)
			Score += 250000;
		if ((Huo3 + Tiao3) && (Chong4 + TiaoChong4))
			Score += 200000;
		if (Huo3 + Tiao3 >= 2)
			Score += 8000;
		//�������͸�ֵ
		Score += Chong4 * 230;
		Score += TiaoChong4 * 110;
		Score += Huo3 * 320;
		Score += Tiao3 * 150;
		Score += Huo2 * 160;
		Score += Tiao2 * 150;
		//����ֱ�ӻ�ʤ��������͸�ֵ
		if ((Chong4 + TiaoChong4 + Huo4) && (Huo2 + Tiao2 >= 2))
			Score += 220;
		if ((Huo3 + Tiao3) && (Huo2 + Tiao2 >= 2))
			Score += 200;
		if (Chong3&&Chong4)
			Score += 100;
		if (Chong3 >= 2 && TiaoChong4)
			Score += 100;
		if (Chong3 >= 2)
			Score += 100;
		if (Chong3 && (Huo2 + Tiao2))
			Score += 50;
		//�������͸�ֵ
		Score += Chong3 * 40;
		Score += Chong1 * 10;
		Score += Huo1 * 20;
		Score += Chong2 * 20;
	}
	else //�ԶԷ��ķ�������
	{
		GetBoardType(BoardPosition, Flag, Coord, Bans);
		//���������Ӯ�����͸�ֵ
		if (ChangLian || Lian5)
			Score += 1000000;
		if (Huo4)
			Score += 45000;
		if (Chong4 + TiaoChong4 >= 2)
			Score += 45000;
		if ((Huo3 + Tiao3) && (Chong4 + TiaoChong4))
			Score += 40000;
		if (Huo3 + Tiao3 >= 2)
			Score += 1900;
		//�������͸�ֵ
		Score += Chong4 * 230;
		Score += TiaoChong4 * 110;
		Score += Huo3 * 320;
		Score += Tiao3 * 150;
		Score += Huo2 * 160;
		Score += Tiao2 * 150;
		//����ֱ�ӻ�ʤ��������͸�ֵ
		if ((Chong4 + TiaoChong4 + Huo4) && (Huo2 + Tiao2 >= 2))
			Score += 220;
		if ((Huo3 + Tiao3) && (Huo2 + Tiao2 >= 2))
			Score += 200;
		if (Chong3&&Chong4)
			Score += 100;
		if (Chong3 >= 2 && TiaoChong4)
			Score += 100;
		if (Chong3 >= 2)
			Score += 100;
		if (Chong3 && (Huo2 + Tiao2))
			Score += 50;
		//�������͸�ֵ
		Score += Chong3 * 40;
		Score += Chong1 * 10;
		Score += Huo1 * 20;
		Score += Chong2 * 20;
	}
	return Score;
}

Position AIDraw(int BoardPosition[][BOARDSIZE], int Flag)
{
	Position AiRecommendation;
	Position Buff;
	int BoardValue[BOARDSIZE][BOARDSIZE];

#ifdef DEBUG
	int test=0;
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			if (BoardPosition[i][j]!=BLANK)
			{
				test++;
			}
		}
	}
	if (test==0)
	{
		AiRecommendation.X = 7;
		AiRecommendation.Y = 7;
		return AiRecommendation;
	}
#endif // DEBUG

#ifndef DEBUG
if (Counter==0)
	{
		AiRecommendation.X = 7;
		AiRecommendation.Y = 7;
		return AiRecommendation;
	}
#endif // !DEBUG


	for (Buff.X = 0; Buff.X < BOARDSIZE; Buff.X++)
	{
		for (Buff.Y = 0; Buff.Y < BOARDSIZE; Buff.Y++)
		{
			if (BoardPosition[Buff.X][Buff.Y]==BLANK)
			{
				BoardValue[Buff.X][Buff.Y] = GetScore(BoardPosition, Flag, Buff, Bans) + GetScore(BoardPosition, -Flag, Buff, Bans);
			}
			else
			{
				BoardValue[Buff.X][Buff.Y] = 0;
			}
		}
	}
	Position Temp;
	Temp.X = 7;
	Temp.Y = 7;
	for (Buff.X = 0; Buff.X < BOARDSIZE; Buff.X++)
	{
		for (Buff.Y = 0; Buff.Y < BOARDSIZE; Buff.Y++)
		{
			if (BoardValue[Buff.X][Buff.Y] > BoardValue[Temp.X][Temp.Y])
			{
				Temp = Buff;
			}
		}
	}
	AiRecommendation = Temp;
	return AiRecommendation;
}

#ifdef DEBUG
#define BOARDSIZE 15
Position API_Main(int BoardPosition[][BOARDSIZE], int Flag, int CF, int Bs)
{
	int ChessFlag = CF;
	int Bans = Bs;
	return AIDraw(BoardPosition, Flag);
}
#endif // DEBUG
