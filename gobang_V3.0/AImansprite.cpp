#include "stdafx.h"
#include "AImansprite.h"
//#define DEBUG

int ChangLian, Lian5, Huo4, Chong4, TiaoChong4, Huo3, Tiao3, Chong3, Huo2, Tiao2, Chong2, Huo1, Chong1;//各种棋型的赋值
int MinLeft, MaxRight, MinTop, MaxBottom;

//连五函数，用于搜索连五或者长连，连五返回1，长连返回2，无返回0
int GetLian5(int BoardPosition[][BOARDSIZE], int Flag, Position Coord,int Bans)
{
	int Left, Right, i, j;
	//纵轴方向
	for (Left = 0, i = Coord.X - 1; i >= 0&&BoardPosition[i][Coord.Y]==Flag; Left++, i--);
	for (Right = 0, i = Coord.X + 1; i <BOARDSIZE&&BoardPosition[i][Coord.Y]==Flag; Right++, i++);
	//如果落子前有4个子，则落子后为连五；如果落子前有大于或等于5个子，则落子后为长连
	if (Left + Right == 4)
		return 1;
	else if (Left + Right >= 5)
		return 2;
	//横轴方向
	for (Left = 0, j = Coord.Y - 1; j >= 0&&BoardPosition[Coord.X][j] == Flag; Left++, j--);
	for (Right = 0, j = Coord.Y + 1; j <BOARDSIZE&&BoardPosition[Coord.X][j] == Flag; Right++, j++);
	//如果落子前有4个子，则落子后为连五；如果落子前有大于或等于5个子，则落子后为长连
	if (Left + Right == 4)
		return 1;
	else if (Left + Right >= 5)
		return 2;
	//'\'
	for (Left = 0, i = Coord.X - 1,j=Coord.Y-1; i >= 0&&j>=0&&BoardPosition[i][j] == Flag; Left++, i--,j--);
	for (Right = 0, i = Coord.X + 1, j = Coord.Y + 1;i<BOARDSIZE&&j <BOARDSIZE&&BoardPosition[i][j] == Flag; Right++, i++,j++);
	//如果落子前有4个子，则落子后为连五；如果落子前有大于或等于5个子，则落子后为长连
	if (Left + Right == 4)
		return 1;
	else if (Left + Right >= 5)
		return 2;
	//'/'
	for (Left = 0, i = Coord.X + 1, j = Coord.Y - 1; i<BOARDSIZE && j >= 0 && BoardPosition[i][j] == Flag; Left++, i++, j--);
	for (Right = 0, i = Coord.X - 1, j = Coord.Y + 1; i >= 0&&j <BOARDSIZE&&BoardPosition[i][j] == Flag; Right++, i--, j++);
	//如果落子前有4个子，则落子后为连五；如果落子前有大于或等于5个子，则落子后为长连
	if (Left + Right == 4)
		return 1;
	else if (Left + Right >= 5)
		return 2;
	return 0;

}
//活四函数，用于搜索活四以及禁手情况，返回活四的个数
int GetHuo4(int BoardPosition[][BOARDSIZE], int Flag, Position Coord,int Bans)
{
	int Huo4=0,Left, Right, i, j;

	//纵轴方向
	for (Left = 0, i = Coord.X - 1; i >= 0 && BoardPosition[i][Coord.Y] == Flag; Left++, i--);
	for (Right = 0, i = Coord.X + 1; i <BOARDSIZE&&BoardPosition[i][Coord.Y] == Flag; Right++, i++);
	if (Left+Right==3)  //落子前，连子为3
	{		//两边都没有对方的子挡住
		if (Coord.X - Left - 1 >= 0&& Coord.X + Right + 1<BOARDSIZE
			&& BoardPosition[Coord.X - Left - 1][Coord.Y] == BLANK&&BoardPosition[Coord.X + Right + 1][Coord.Y] == BLANK
			//考虑长连禁手情况
			&& (!(Flag==BLACK&&Bans && (BoardPosition[Coord.X - Left - 2][Coord.Y] == Flag || BoardPosition[Coord.X + Right + 2][Coord.Y] == Flag))))
			Huo4++;
	}

	//横轴方向
	for (Left = 0, j = Coord.Y - 1; j >= 0 && BoardPosition[Coord.X][j] == Flag; Left++, j--);
	for (Right = 0, j = Coord.Y + 1; j <BOARDSIZE&&BoardPosition[Coord.X][j] == Flag; Right++, j++);
	if (Left + Right == 3)  //落子前，连子为3
	{		//两边都没有对方的子挡住
		if (Coord.Y - Left - 1 >= 0 && Coord.Y + Right + 1<BOARDSIZE&&
			BoardPosition[Coord.X][Coord.Y - Left - 1] == BLANK&&BoardPosition[Coord.X][Coord.Y + Right + 1] == BLANK
			//考虑长连禁手情况
			&& (!(Flag==BLACK&&Bans && (BoardPosition[Coord.X][Coord.Y - Left - 2] == Flag || BoardPosition[Coord.X][Coord.Y + Right + 2] == Flag))))
			Huo4++;
	}

	//'\'
	for (Left = 0, i = Coord.X - 1, j = Coord.Y - 1; i >= 0 && j >= 0 && BoardPosition[i][j] == Flag; Left++, i--, j--);
	for (Right = 0, i = Coord.X + 1, j = Coord.Y + 1; i<BOARDSIZE&&j <BOARDSIZE&&BoardPosition[i][j] == Flag; Right++, i++, j++);
	if (Left + Right == 3)  //落子前，连子为3
	{		//两边都没有对方的子挡住
		if (Coord.X - Left - 1 >= 0 && Coord.X + Right + 1<BOARDSIZE&&Coord.Y - Left - 1 >= 0 && Coord.Y + Right + 1<BOARDSIZE&&
			BoardPosition[Coord.X-Left-1][Coord.Y - Left - 1] == BLANK&&BoardPosition[Coord.X + Right + 1][Coord.Y + Right + 1] == BLANK
			//考虑长连禁手情况
			&& (!(Flag==BLACK&&Bans && (BoardPosition[Coord.X - Left - 2][Coord.Y - Left - 2] == Flag || BoardPosition[Coord.X + Right + 2][Coord.Y + Right + 2] == Flag))))
			Huo4++;
	}

	//'/'
	for (Left = 0, i = Coord.X + 1, j = Coord.Y - 1; i<BOARDSIZE && j >= 0 && BoardPosition[i][j] == Flag; Left++, i++, j--);
	for (Right = 0, i = Coord.X - 1, j = Coord.Y + 1; i >= 0 && j <BOARDSIZE&&BoardPosition[i][j] == Flag; Right++, i--, j++);
	if (Left + Right == 3)  //落子前，连子为3
	{		//两边都没有对方的子挡住
		if (Coord.X + Left + 1 < BOARDSIZE && Coord.X - Right - 1>=0&&Coord.Y - Left - 1 >= 0 && Coord.Y + Right + 1<BOARDSIZE&&
			BoardPosition[Coord.X + Left + 1][Coord.Y - Left - 1] == BLANK&&BoardPosition[Coord.X - Right - 1][Coord.Y + Right + 1] == BLANK
			//考虑长连禁手情况
			&& (!(Flag==BLACK&&Bans && (BoardPosition[Coord.X + Left + 2][Coord.Y - Left - 2] == Flag || BoardPosition[Coord.X - Right - 2][Coord.Y + Right + 2] == Flag))))
			Huo4++;
	}
	return Huo4;
}
//冲四冲三函数，用于搜索冲四冲三以及跳冲四，返回一个包含冲四冲三以及跳冲四个数的一个结构体
Chong3Chong4 GetChong3Chong4(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans)
{
	Chong3Chong4 ChessNum3;//定义返回值
	ChessNum3.Chong3 = 0; ChessNum3.Chong4 = 0; ChessNum3.TiaoChong4 = 0;  //初始化		
	int SpaceLeft, SpaceRight, Left1, Left2, Right1, Right2, i, j;//Space为空格个数,Left1为空格前的连子，Left2为空格后的连子，Right同理

	//纵轴方向
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //搜索初始化
	for (i = Coord.X - 1; i >= 0 && (BoardPosition[i][Coord.Y] == Flag|| BoardPosition[i][Coord.Y] == BLANK)&&SpaceLeft<2;i--)
	{
		if (BoardPosition[i][Coord.Y] == BLANK) SpaceLeft++;//遇到空格
		else if (BoardPosition[i][Coord.Y] == Flag) SpaceLeft ? Left2++ : Left1++; //遇到己方棋子
		else break;
	}
	for (i = Coord.X + 1; i <BOARDSIZE && (BoardPosition[i][Coord.Y] == Flag || BoardPosition[i][Coord.Y] == BLANK) && SpaceRight<2; i++)
	{
		if (BoardPosition[i][Coord.Y] == BLANK) SpaceRight++;//遇到空格
		else if (BoardPosition[i][Coord.Y] == Flag) SpaceRight ? Right2++ : Right1++; //遇到己方棋子
		else break;
	}
	//冲三，左右对称
	if (Left1 + Right1 == 2)
	{	//冲三的情况，两边各有一个对方子挡住的情况
		if ((SpaceLeft == 0 && SpaceRight) || (SpaceLeft && SpaceRight == 0))
			ChessNum3.Chong3++;
	}
	//跳冲三，左右对称
	if (Left1 + Left2 + Right1 == 2)
	{
		if (Left2 && ((SpaceLeft == 1 && SpaceRight) || (SpaceLeft == 2 && !SpaceRight)))
			ChessNum3.Chong3++;
	}
	if (Left1 + Right1 + Right2 == 2)
	{
		if (Right2 && ((SpaceRight == 1 && SpaceLeft) || (SpaceRight == 2 && !SpaceLeft)))
			ChessNum3.Chong3++;
	}
	//冲四的情况,左右对称 
	if (Left1 + Left2 + Right1 >= 3)
	{
		if (Left2 && ((SpaceLeft == 1 && SpaceRight) || (SpaceLeft == 2 && !SpaceRight)))
			ChessNum3.TiaoChong4++;
		if (SpaceLeft && Left1 + Right1 >= 3 && SpaceRight == 0)
			ChessNum3.Chong4++;
	}
	if (Left1 + Right1 + Right2 >= 3)
	{
		if (Right2 && ((SpaceRight == 1 && SpaceLeft) || (SpaceRight == 2 && !SpaceLeft)))
			ChessNum3.TiaoChong4++;
		if (SpaceRight && Left1 + Right1 >= 3 && SpaceLeft == 0)
			ChessNum3.Chong4++;
	}

	//横轴方向
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //搜索初始化
	for (j = Coord.Y - 1; j >= 0 && (BoardPosition[Coord.X][j] == Flag || BoardPosition[Coord.X][j] == BLANK) && SpaceLeft<2; j--)
	{
		if (BoardPosition[Coord.X][j] == BLANK) SpaceLeft++;//遇到空格
		else if (BoardPosition[Coord.X][j] == Flag) SpaceLeft ? Left2++ : Left1++; //遇到己方棋子
		else break;
	}
	for (j = Coord.Y + 1; j <BOARDSIZE && (BoardPosition[Coord.X][j] == Flag || BoardPosition[Coord.X][j] == BLANK) && SpaceRight<2; j++)
	{
		if (BoardPosition[Coord.X][j] == BLANK) SpaceRight++;//遇到空格
		else if (BoardPosition[Coord.X][j] == Flag) SpaceRight ? Right2++ : Right1++; //遇到己方棋子
		else break;
	}
	//冲三，左右对称
	if (Left1 + Right1 == 2)
	{	//冲三的情况，两边各有一个对方子挡住的情况
		if ((SpaceLeft == 0 && SpaceRight) || (SpaceLeft && SpaceRight == 0))
			ChessNum3.Chong3++;
	}
	//跳冲三，左右对称
	if (Left1 + Left2 + Right1 == 2)
	{
		if (Left2 && ((SpaceLeft == 1 && SpaceRight) || (SpaceLeft == 2 && !SpaceRight)))
			ChessNum3.Chong3++;
	}
	if (Left1 + Right1 + Right2 == 2)
	{
		if (Right2 && ((SpaceRight == 1 && SpaceLeft) || (SpaceRight == 2 && !SpaceLeft)))
			ChessNum3.Chong3++;
	}
	//冲四的情况,左右对称 
	if (Left1 + Left2 + Right1 >= 3)
	{
		if (Left2 && ((SpaceLeft == 1 && SpaceRight) || (SpaceLeft == 2 && !SpaceRight)))
			ChessNum3.TiaoChong4++;
		if (SpaceLeft && Left1 + Right1 >= 3 && SpaceRight == 0)
			ChessNum3.Chong4++;
	}
	if (Left1 + Right1 + Right2 >= 3)
	{
		if (Right2 && ((SpaceRight == 1 && SpaceLeft) || (SpaceRight == 2 && !SpaceLeft)))
			ChessNum3.TiaoChong4++;
		if (SpaceRight && Left1 + Right1 >= 3 && SpaceLeft == 0)
			ChessNum3.Chong4++;
	}

	//'\'方向
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //搜索初始化
	for (i=Coord.X-1, j = Coord.Y - 1; i>=0 && j >= 0 && (BoardPosition[i][j] == Flag || BoardPosition[i][j] == BLANK) && SpaceLeft<2;i--, j--)
	{
		if (BoardPosition[i][j] == BLANK) SpaceLeft++;//遇到空格
		else if (BoardPosition[i][j] == Flag) SpaceLeft ? Left2++ : Left1++; //遇到己方棋子
		else break;
	}
	for (i=Coord.X+1, j = Coord.Y + 1; i<BOARDSIZE && j <BOARDSIZE && (BoardPosition[i][j] == Flag || BoardPosition[i][j] == BLANK) && SpaceRight<2; i++,j++)
	{
		if (BoardPosition[i][j] == BLANK) SpaceRight++;//遇到空格
		else if (BoardPosition[i][j] == Flag) SpaceRight ? Right2++ : Right1++; //遇到己方棋子
		else break;
	}
	//冲三，左右对称
	if (Left1 + Right1 == 2)
	{	//冲三的情况，两边各有一个对方子挡住的情况
		if ((SpaceLeft == 0 && SpaceRight) || (SpaceLeft && SpaceRight == 0))
			ChessNum3.Chong3++;
	}
	//跳冲三，左右对称
	if (Left1 + Left2 + Right1 == 2)
	{
		if (Left2 && ((SpaceLeft == 1 && SpaceRight) || (SpaceLeft == 2 && !SpaceRight)))
			ChessNum3.Chong3++;
	}
	if (Left1 + Right1 + Right2 == 2)
	{
		if (Right2 && ((SpaceRight == 1 && SpaceLeft) || (SpaceRight == 2 && !SpaceLeft)))
			ChessNum3.Chong3++;
	}
	//冲四的情况,左右对称 
	if (Left1 + Left2 + Right1 >= 3)
	{
		if (Left2 && ((SpaceLeft == 1 && SpaceRight) || (SpaceLeft == 2 && !SpaceRight)))
			ChessNum3.TiaoChong4++;
		if (SpaceLeft && Left1 + Right1 >= 3 && SpaceRight == 0)
			ChessNum3.Chong4++;
	}
	if (Left1 + Right1 + Right2 >= 3)
	{
		if (Right2 && ((SpaceRight == 1 && SpaceLeft) || (SpaceRight == 2 && !SpaceLeft)))
			ChessNum3.TiaoChong4++;
		if (SpaceRight && Left1 + Right1 >= 3 && SpaceLeft == 0)
			ChessNum3.Chong4++;
	}

	//'/'方向
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //搜索初始化
	for (i = Coord.X + 1, j = Coord.Y - 1; i<BOARDSIZE && j >= 0 && (BoardPosition[i][j] == Flag || BoardPosition[i][j] == BLANK) && SpaceLeft<2; i++, j--)
	{
		if (BoardPosition[i][j] == BLANK) SpaceLeft++;//遇到空格
		else if (BoardPosition[i][j] == Flag) SpaceLeft ? Left2++ : Left1++; //遇到己方棋子
		else break;
	}
	for (i = Coord.X - 1, j = Coord.Y + 1; i >= 0 && j <BOARDSIZE && (BoardPosition[i][j] == Flag || BoardPosition[i][j] == BLANK) && SpaceRight<2; i--, j++)
	{
		if (BoardPosition[i][j] == BLANK) SpaceRight++;//遇到空格
		else if (BoardPosition[i][j] == Flag) SpaceRight ? Right2++ : Right1++; //遇到己方棋子
		else break;
	}
	//冲三，左右对称
	if (Left1 + Right1 == 2)
	{	//冲三的情况，两边各有一个对方子挡住的情况
		if ((SpaceLeft == 0 && SpaceRight) || (SpaceLeft && SpaceRight == 0))
			ChessNum3.Chong3++;
	}
	//跳冲三，左右对称
	if (Left1 + Left2 + Right1 == 2)
	{
		if (Left2 && ((SpaceLeft == 1 && SpaceRight) || (SpaceLeft == 2 && !SpaceRight)))
			ChessNum3.Chong3++;
	}
	if (Left1 + Right1 + Right2 == 2)
	{
		if (Right2 && ((SpaceRight == 1 && SpaceLeft) || (SpaceRight == 2 && !SpaceLeft)))
			ChessNum3.Chong3++;
	}
	//冲四的情况,左右对称 
	if (Left1 + Left2 + Right1 >= 3)
	{
		if (Left2 && ((SpaceLeft == 1 && SpaceRight) || (SpaceLeft == 2 && !SpaceRight)))
			ChessNum3.TiaoChong4++;
		if (SpaceLeft && Left1 + Right1 >= 3 && SpaceRight == 0)
			ChessNum3.Chong4++;
	}
	if (Left1 + Right1 + Right2 >= 3)
	{
		if (Right2 && ((SpaceRight == 1 && SpaceLeft) || (SpaceRight == 2 && !SpaceLeft)))
			ChessNum3.TiaoChong4++;
		if (SpaceRight && Left1 + Right1 >= 3 && SpaceLeft == 0)
			ChessNum3.Chong4++;
	}
	return ChessNum3;
}
//连二连三函数，用于搜索连二连三，返回一个包含连二连三个数的一个结构体
Huo2Huo3 GetHuo2Huo3(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans)
{
	int Left, Right, i, j, SpaceLeft, SpaceRight;
	Huo2Huo3 ChessNum2;//定义返回值
	ChessNum2.Huo2 = 0; ChessNum2.Huo3 = 0;//初始化

	//横轴方向
	for (Left = 0, i = Coord.X - 1; i >= 0 && BoardPosition[i][Coord.Y] == Flag; Left++, i--);
	for (Right = 0, i = Coord.X + 1; i <BOARDSIZE&&BoardPosition[i][Coord.Y] == Flag; Right++, i++);
	if (Left+Right==1)
	{
		for (SpaceLeft=0, i = Coord.X - Left - 1; i >= 0 && BoardPosition[i][Coord.Y] == BLANK; SpaceLeft++, i--);
		for (SpaceRight = 0, i = Coord.X + Right + 1; i <BOARDSIZE && BoardPosition[i][Coord.Y] == BLANK; SpaceRight++, i++);
		if (SpaceLeft && SpaceRight && SpaceLeft + SpaceRight >= 4) ChessNum2.Huo2++;
	}
	if (Left+Right==2)
	{	//冲四的情况
		if (!(Coord.X-Left-2>=0&&BoardPosition[Coord.X - Left - 2][Coord.Y]==Flag)
			&&!(Coord.X + Right + 2 >= 0 && BoardPosition[Coord.X +Right+2][Coord.Y] == Flag))
		{		
			for (SpaceLeft = 0, i = Coord.X - Left - 1; i >= 0 && BoardPosition[i][Coord.Y] == BLANK; SpaceLeft++, i--);
			for (SpaceRight = 0, i = Coord.X + Right + 1; i <BOARDSIZE && BoardPosition[i][Coord.Y] == BLANK; SpaceRight++, i++);
			if (SpaceLeft && SpaceRight && SpaceLeft + SpaceRight >= 3) ChessNum2.Huo3++;
		}
	}

	//竖轴方向
	for (Left = 0, j = Coord.Y - 1; j >= 0 && BoardPosition[Coord.X][j] == Flag; Left++, j--);
	for (Right = 0, j = Coord.Y + 1; j <BOARDSIZE&&BoardPosition[Coord.X][j] == Flag; Right++, j++);
	if (Left + Right == 1)
	{
		for (SpaceLeft = 0, j = Coord.Y - Left - 1; j >= 0 && BoardPosition[Coord.X][j] == BLANK; SpaceLeft++, j--);
		for (SpaceRight = 0, j = Coord.Y + Right + 1; j <BOARDSIZE && BoardPosition[Coord.X][j] == BLANK; SpaceRight++, j++);
		if (SpaceLeft && SpaceRight && SpaceLeft + SpaceRight >= 4) ChessNum2.Huo2++;
	}
	if (Left + Right == 2)
	{	//冲四的情况
		if (!(Coord.Y - Left - 2 >= 0 && BoardPosition[Coord.X][Coord.Y - Left - 2] == Flag)
			&& !(Coord.Y + Right + 2 >= 0 && BoardPosition[Coord.X][Coord.Y + Right + 2] == Flag))
		{
			for (SpaceLeft = 0, j = Coord.Y - Left - 1; j >= 0 && BoardPosition[Coord.X][j] == BLANK; SpaceLeft++, j--);
			for (SpaceRight = 0, j = Coord.Y + Right + 1; j <BOARDSIZE && BoardPosition[Coord.X][j] == BLANK; SpaceRight++, j++);
			if (SpaceLeft && SpaceRight && SpaceLeft + SpaceRight >= 3) ChessNum2.Huo3++;
		}
	}

	//'\'方向
	for (Left = 0, i = Coord.X - 1, j = Coord.Y - 1; i >= 0 && j >= 0 && BoardPosition[i][j] == Flag; Left++, i--, j--);
	for (Right = 0, i = Coord.X + 1, j = Coord.Y + 1; i<BOARDSIZE&&j <BOARDSIZE&&BoardPosition[i][j] == Flag; Right++, i++, j++);
	if (Left + Right == 1)
	{
		for (SpaceLeft = 0, i = Coord.X - Left - 1, j = Coord.Y - Left - 1;i>=0 && j >= 0 && BoardPosition[i][j] == BLANK; SpaceLeft++,i--,j--);
		for (SpaceRight = 0, i = Coord.X +Right + 1, j = Coord.Y + Right + 1;i<BOARDSIZE&& j <BOARDSIZE && BoardPosition[i][j] == BLANK; SpaceRight++,i++,j++);
		if (SpaceLeft && SpaceRight && SpaceLeft + SpaceRight >= 4) ChessNum2.Huo2++;
	}
	if (Left + Right == 2)
	{	//冲四的情况
		if (!(Coord.X - Left - 2 >= 0 &&Coord.Y - Left - 2 >= 0 && BoardPosition[Coord.X - Left - 2][Coord.Y - Left - 2] == Flag)
			&& !(Coord.X + Left + 2 <BOARDSIZE && Coord.Y + Right + 2 <BOARDSIZE && BoardPosition[Coord.X + Left + 2][Coord.Y + Right + 2] == Flag))
		{
			for (SpaceLeft = 0, i = Coord.X - Left - 1, j = Coord.Y - Left - 1; i >= 0 && j >= 0 && BoardPosition[i][j] == BLANK; SpaceLeft++, i--, j--);
			for (SpaceRight = 0, i = Coord.X + Right + 1, j = Coord.Y + Right + 1; i<BOARDSIZE&& j <BOARDSIZE && BoardPosition[i][j] == BLANK; SpaceRight++, i++, j++);
			if (SpaceLeft && SpaceRight && SpaceLeft + SpaceRight >= 3) ChessNum2.Huo3++;
		}
	}

	//'/'方向
	for (Left = 0, i = Coord.X + 1, j = Coord.Y - 1; i<BOARDSIZE && j >= 0 && BoardPosition[i][j] == Flag; Left++, i++, j--);
	for (Right = 0, i = Coord.X - 1, j = Coord.Y + 1; i >= 0&&j <BOARDSIZE&&BoardPosition[i][j] == Flag; Right++, i--, j++);
	if (Left + Right == 1)
	{
		for (SpaceLeft = 0, i = Coord.X + Left + 1, j = Coord.Y - Left - 1; i<BOARDSIZE && j >= 0 && BoardPosition[i][j] == BLANK; SpaceLeft++, i++, j--);
		for (SpaceRight = 0, i = Coord.X - Right - 1, j = Coord.Y + Right + 1; i >= 0&& j <BOARDSIZE && BoardPosition[i][j] == BLANK; SpaceRight++, i--, j++);
		if (SpaceLeft && SpaceRight && SpaceLeft + SpaceRight >= 4) ChessNum2.Huo2++;
	}
	if (Left + Right == 2)
	{	//冲四的情况
		if (!(Coord.X + Left + 2 <BOARDSIZE && Coord.Y - Left - 2 >= 0 && BoardPosition[Coord.X + Left + 2][Coord.Y - Left - 2] == Flag)
			&& !(Coord.X - Left - 2 >= 0 && Coord.Y + Right + 2 <BOARDSIZE && BoardPosition[Coord.X - Left - 2][Coord.Y + Right + 2] == Flag))
		{
			for (SpaceLeft = 0, i = Coord.X + Left + 1, j = Coord.Y - Left - 1; i<BOARDSIZE && j >= 0 && BoardPosition[i][j] == BLANK; SpaceLeft++, i++, j--);
			for (SpaceRight = 0, i = Coord.X - Right - 1, j = Coord.Y + Right + 1; i >= 0 && j <BOARDSIZE && BoardPosition[i][j] == BLANK; SpaceRight++, i--, j++);
			if (SpaceLeft && SpaceRight && SpaceLeft + SpaceRight >= 3) ChessNum2.Huo3++;
		}
	}
	return ChessNum2;

}
//跳活三跳活二函数，用于搜索跳二跳三，返回一个包含跳二跳三个数的结构体
Tiao2Tiao3 GetTiao2Tiao3(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans)
{
	Tiao2Tiao3 ChessNum1; //定义返回值
	ChessNum1.Tiao2 = 0; ChessNum1.Tiao3 = 0;  //初始化		
	int SpaceLeft, SpaceRight, Left1, Left2, Right1, Right2, i, j;//Space为空格个数,Left1为空格前的连子，Left2为空格后的连子，Right同理

	//纵轴方向
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //搜索初始化
	for (i = Coord.X - 1; i >= 0 && (BoardPosition[i][Coord.Y] == Flag || BoardPosition[i][Coord.Y] == BLANK) && SpaceLeft<2; i--)
	{
		if (BoardPosition[i][Coord.Y] == BLANK) SpaceLeft++;//遇到空格
		else if (BoardPosition[i][Coord.Y] == Flag) SpaceLeft ? Left2++ : Left1++; //遇到己方棋子
		else break;
	}
	for (i = Coord.X + 1; i <BOARDSIZE && (BoardPosition[i][Coord.Y] == Flag || BoardPosition[i][Coord.Y] == BLANK) && SpaceRight<2; i++)
	{
		if (BoardPosition[i][Coord.Y] == BLANK) SpaceRight++;//遇到空格
		else if (BoardPosition[i][Coord.Y] == Flag) SpaceRight ? Right2++ : Right1++; //遇到己方棋子
		else break;
	}//跳活二，二子间有一个空格，且周围空格数为4个
	if ((Left1+Left2+Right1+Right2==1&& SpaceLeft == 2 && SpaceRight == 2)&&((Left2==1)^(Right2==1)))
		ChessNum1.Tiao2++;
	if ((Left1 + Left2 + Right1 + Right2 == 2) && ((Left1 == 1) ^ (Right1 == 1))
		&& ((Left2 == 1 && SpaceLeft == 2 && SpaceRight >= 1) || (Right2 == 1 && SpaceLeft >= 1 && SpaceRight == 2)))
		ChessNum1.Tiao3++;

	//横轴方向
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //搜索初始化
	for (j = Coord.Y - 1; j >= 0 && (BoardPosition[Coord.X][j] == Flag || BoardPosition[Coord.X][j] == BLANK) && SpaceLeft<2; j--)
	{
		if (BoardPosition[Coord.X][j] == BLANK) SpaceLeft++;//遇到空格
		else if (BoardPosition[Coord.X][j] == Flag) SpaceLeft ? Left2++ : Left1++; //遇到己方棋子
		else break;
	}
	for (j = Coord.Y + 1; j <BOARDSIZE && (BoardPosition[Coord.X][j] == Flag || BoardPosition[Coord.X][j] == BLANK) && SpaceRight<2; j++)
	{
		if (BoardPosition[Coord.X][j] == BLANK) SpaceRight++;//遇到空格
		else if (BoardPosition[Coord.X][j] == Flag) SpaceRight ? Right2++ : Right1++; //遇到己方棋子
		else break;
	}//跳活二，二子间有一个空格，且周围空格数为4个
	if ((Left1 + Left2 + Right1 + Right2 == 1 && SpaceLeft == 2 && SpaceRight == 2) && ((Left2 == 1) ^ (Right2 == 1)))
		ChessNum1.Tiao2++;
	if ((Left1 + Left2 + Right1 + Right2 == 2) && ((Left1 == 1) ^ (Right1 == 1))
		&& ((Left2 == 1 && SpaceLeft == 2 && SpaceRight >= 1) || (Right2 == 1 && SpaceLeft >= 1 && SpaceRight == 2)))
		ChessNum1.Tiao3++;

	//'\'方向
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //搜索初始化
	for (i = Coord.X - 1, j = Coord.Y - 1;i>=0&&j >= 0 && (BoardPosition[i][j] == Flag || BoardPosition[i][j] == BLANK) && SpaceLeft<2;i--, j--)
	{
		if (BoardPosition[i][j] == BLANK) SpaceLeft++;//遇到空格
		else if (BoardPosition[i][j] == Flag) SpaceLeft ? Left2++ : Left1++; //遇到己方棋子
		else break;
	}
	for (i = Coord.X + 1, j = Coord.Y + 1;i<BOARDSIZE&&j <BOARDSIZE && (BoardPosition[i][j] == Flag || BoardPosition[i][j] == BLANK) && SpaceRight<2; i++,j++)
	{
		if (BoardPosition[i][j] == BLANK) SpaceRight++;//遇到空格
		else if (BoardPosition[i][j] == Flag) SpaceRight ? Right2++ : Right1++; //遇到己方棋子
		else break;
	}//跳活二，二子间有一个空格，且周围空格数为4个
	if ((Left1 + Left2 + Right1 + Right2 == 1 && SpaceLeft == 2 && SpaceRight == 2) && ((Left2 == 1) ^ (Right2 == 1)))
		ChessNum1.Tiao2++;
	if ((Left1 + Left2 + Right1 + Right2 == 2) && ((Left1 == 1) ^ (Right1 == 1))
		&& ((Left2 == 1 && SpaceLeft == 2 && SpaceRight >= 1) || (Right2 == 1 && SpaceLeft >= 1 && SpaceRight == 2)))
		ChessNum1.Tiao3++;

	//'/'方向
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //搜索初始化
	for (i = Coord.X + 1, j = Coord.Y - 1; i<BOARDSIZE && j >= 0 && (BoardPosition[i][j] == Flag || BoardPosition[i][j] == BLANK) && SpaceLeft<2; i++, j--)
	{
		if (BoardPosition[i][j] == BLANK) SpaceLeft++;//遇到空格
		else if (BoardPosition[i][j] == Flag) SpaceLeft ? Left2++ : Left1++; //遇到己方棋子
		else break;
	}
	for (i = Coord.X - 1, j = Coord.Y + 1; i >= 0 && j <BOARDSIZE && (BoardPosition[i][j] == Flag || BoardPosition[i][j] == BLANK) && SpaceRight<2; i--, j++)
	{
		if (BoardPosition[i][j] == BLANK) SpaceRight++;//遇到空格
		else if (BoardPosition[i][j] == Flag) SpaceRight ? Right2++ : Right1++; //遇到己方棋子
		else break;
	}//跳活二，二子间有一个空格，且周围空格数为4个
	if ((Left1 + Left2 + Right1 + Right2 == 1 && SpaceLeft == 2 && SpaceRight == 2) && ((Left2 == 1) ^ (Right2 == 1)))
		ChessNum1.Tiao2++;
	if ((Left1 + Left2 + Right1 + Right2 == 2) && ((Left1 == 1) ^ (Right1 == 1))
		&& ((Left2 == 1 && SpaceLeft == 2 && SpaceRight >= 1) || (Right2 == 1 && SpaceLeft >= 1 && SpaceRight == 2)))
		ChessNum1.Tiao3++;

	return ChessNum1;

}
//小棋型函数，用于搜索除以上大棋型以外的棋型，包括冲一、活一、冲二（其中冲一、冲二函数判断有问题，由于影响棋局能力小，不予修改）
XiaoQiXing GetXiaoQiXing(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans)
{
	XiaoQiXing ChessNum0;//定义返回值
	ChessNum0.Chong1 = 0; ChessNum0.Chong2 = 0; ChessNum0.Huo1 = 0;  //初始化		
	int SpaceLeft, SpaceRight, Left1, Left2, Right1, Right2, i, j;//Space为空格个数,Left1为空格前的连子，Left2为空格后的连子，Right同理

	//纵轴方向
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //搜索初始化
	for (i = Coord.X - 1; i >= 0 && (BoardPosition[i][Coord.Y] == Flag || BoardPosition[i][Coord.Y] == BLANK) && SpaceLeft<2; i--)
	{
		if (BoardPosition[i][Coord.Y] == BLANK) SpaceLeft++;//遇到空格
		else if (BoardPosition[i][Coord.Y] == Flag) SpaceLeft ? Left2++ : Left1++; //遇到己方棋子
		else break;
	}
	for (i = Coord.X + 1; i <BOARDSIZE && (BoardPosition[i][Coord.Y] == Flag || BoardPosition[i][Coord.Y] == BLANK) && SpaceRight<2; i++)
	{
		if (BoardPosition[i][Coord.Y] == BLANK) SpaceRight++;//遇到空格
		else if (BoardPosition[i][Coord.Y] == Flag) SpaceRight ? Right2++ : Right1++; //遇到己方棋子
		else break;
	}
	//下面判断棋型
	//两边各有一个对方的子阻挡
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

	//横轴方向
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //搜索初始化
	for (j = Coord.Y - 1; j >= 0 && (BoardPosition[Coord.X][j] == Flag || BoardPosition[Coord.X][j] == BLANK) && SpaceLeft<2; j--)
	{
		if (BoardPosition[Coord.X][j] == BLANK) SpaceLeft++;//遇到空格
		else if (BoardPosition[Coord.X][j] == Flag) SpaceLeft ? Left2++ : Left1++; //遇到己方棋子
		else break;
	}
	for (j = Coord.Y + 1; j <BOARDSIZE && (BoardPosition[Coord.X][j] == Flag || BoardPosition[Coord.X][j] == BLANK) && SpaceRight<2; j++)
	{
		if (BoardPosition[Coord.X][j] == BLANK) SpaceRight++;//遇到空格
		else if (BoardPosition[Coord.X][j] == Flag) SpaceRight ? Right2++ : Right1++; //遇到己方棋子
		else break;
	}
	//下面判断棋型
	//两边各有一个对方的子阻挡
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

	//'\'方向
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //搜索初始化
	for (i = Coord.X - 1, j = Coord.Y - 1; i >= 0 && j >= 0 && (BoardPosition[i][j] == Flag || BoardPosition[i][j] == BLANK) && SpaceLeft<2; i--, j--)
	{
		if (BoardPosition[i][j] == BLANK) SpaceLeft++;//遇到空格
		else if (BoardPosition[i][j] == Flag) SpaceLeft ? Left2++ : Left1++; //遇到己方棋子
		else break;
	}
	for (i = Coord.X + 1, j = Coord.Y + 1; i<BOARDSIZE && j <BOARDSIZE && (BoardPosition[i][j] == Flag || BoardPosition[i][j] == BLANK) && SpaceRight<2; i++, j++)
	{
		if (BoardPosition[i][j] == BLANK) SpaceRight++;//遇到空格
		else if (BoardPosition[i][j] == Flag) SpaceRight ? Right2++ : Right1++; //遇到己方棋子
		else break;
	}
	//下面判断棋型
	//两边各有一个对方的子阻挡
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

	//'/'方向
	SpaceLeft = SpaceRight = Left1 = Left2 = Right1 = Right2 = 0;  //搜索初始化
	for (i = Coord.X + 1, j = Coord.Y - 1; i<BOARDSIZE && j >= 0 && (BoardPosition[i][j] == Flag || BoardPosition[i][j] == BLANK) && SpaceLeft<2; i++, j--)
	{
		if (BoardPosition[i][j] == BLANK) SpaceLeft++;//遇到空格
		else if (BoardPosition[i][j] == Flag) SpaceLeft ? Left2++ : Left1++; //遇到己方棋子
		else break;
	}
	for (i = Coord.X - 1, j = Coord.Y + 1; i >= 0 && j <BOARDSIZE && (BoardPosition[i][j] == Flag || BoardPosition[i][j] == BLANK) && SpaceRight<2; i--, j++)
	{
		if (BoardPosition[i][j] == BLANK) SpaceRight++;//遇到空格
		else if (BoardPosition[i][j] == Flag) SpaceRight ? Right2++ : Right1++; //遇到己方棋子
		else break;
	}
	//下面判断棋型
	//两边各有一个对方的子阻挡
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
//获得各种棋型个数
void GetBoardType(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans)
{
	//初始化
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
//判断是否禁手，不是禁手返回0，长连返回1，三三禁手返回2，四四禁手返回3
int IfBans(int BoardPosition[][BOARDSIZE],int Flag, Position Coord,int Bans)
{
	if (!Bans || !(Flag == BLACK))
		return 0;
	else
	{
		GetBoardType(BoardPosition, Flag, Coord, Bans);

		if (ChangLian)
			return 1;
		//如果黑棋在形成连五的同时，又形成三三、四四禁手，那么还是黑棋获胜
		if (Lian5)
			return 0;
		if (Huo3 + Tiao3 >= 2)
			return 2;
		if (Huo4 + Chong4 + TiaoChong4 >= 2)
			return 3;

		return 0;
	}

}
//评分函数，给当前位置评分
int GetScore(int BoardPosition[][BOARDSIZE], int Flag,int CurrentFlag ,Position Coord, int Bans)
{
	int Score=10;
	if (Bans&&Flag == BLACK&&IfBans(BoardPosition, Flag, Coord, Bans))
		return -1;
	if (Flag==CurrentFlag)//己方的分数评估
	{
		GetBoardType(BoardPosition, Flag, Coord, Bans);
		//下面给可以赢的棋型赋值
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
		//单种棋型赋值
		Score += Chong4 * 230;
		Score += TiaoChong4 * 110;
		Score += Huo3 * 320;
		Score += Tiao3 * 150;
		Score += Huo2 * 160;
		Score += Tiao2 * 150;
		//不能直接获胜的组合棋型赋值
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
		//单种棋型赋值
		Score += Chong3 * 40;
		Score += Chong1 * 10;
		Score += Huo1 * 20;
		Score += Chong2 * 20;
	}
	else //对对方的分数评估
	{
		GetBoardType(BoardPosition, Flag, Coord, Bans);
		//下面给可以赢的棋型赋值
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
		//单种棋型赋值
		Score += Chong4 * 230;
		Score += TiaoChong4 * 110;
		Score += Huo3 * 320;
		Score += Tiao3 * 150;
		Score += Huo2 * 160;
		Score += Tiao2 * 150;
		//不能直接获胜的组合棋型赋值
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
		//单种棋型赋值
		Score += Chong3 * 40;
		Score += Chong1 * 10;
		Score += Huo1 * 20;
		Score += Chong2 * 20;
	}
	return Score;
}
//得到AI的分数
Position GetBestPosition(int BoardPosition[][BOARDSIZE], int Flag)
{
	Position Buff;
	int AIValue[BOARDSIZE][BOARDSIZE] = { 0 };
	int HumanValue[BOARDSIZE][BOARDSIZE] = {0};
	int Value[BOARDSIZE][BOARDSIZE] = {
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
		{ 0,1,2,2,2,2,2,2,2,2,2,2,2,1,0 },
		{ 0,1,2,3,3,3,3,3,3,3,3,3,2,1,0 },
		{ 0,1,2,3,4,4,4,4,4,4,4,3,2,1,0 },
		{ 0,1,2,3,4,5,5,5,5,5,4,3,2,1,0 },
		{ 0,1,2,3,4,5,6,6,6,5,4,3,2,1,0 },
		{ 0,1,2,3,4,5,6,7,6,5,4,3,2,1,0 },
		{ 0,1,2,3,4,5,6,6,6,5,4,3,2,1,0 },
		{ 0,1,2,3,4,5,5,5,5,5,4,3,2,1,0 },
		{ 0,1,2,3,4,4,4,4,4,4,4,3,2,1,0 },
		{ 0,1,2,3,3,3,3,3,3,3,3,3,2,1,0 },
		{ 0,1,2,2,2,2,2,2,2,2,2,2,2,1,0 },
		{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	};
	int AIFlag = -ChessFlag;
	int HumanFlag = ChessFlag;
	int AIThreatLevel=0;// AI落子的威胁性，有四个等级0，1,2,3
	int HumanThreatLevel=0;// 人落子的威胁性，有四个等级0,1,2,3
	int ThreatLevel;
    //取最大价值点,以及最大人的分值、AI的分值
	Position Temp;
	Temp.X = 0;
	Temp.Y = 0;
	Position AITemp;
	AITemp.X = 0;
	AITemp.Y = 0;
	Position HumanTemp;
	HumanTemp.X = 0;
	HumanTemp.Y = 0;
	int MaxHumanValue = 0;
	int MaxAIValue = 0;

	//对于人来说
	if (Flag==ChessFlag)
	{
		for (Buff.X = 0; Buff.X < BOARDSIZE; Buff.X++)
		{
			for (Buff.Y = 0; Buff.Y < BOARDSIZE; Buff.Y++)
			{
				//棋盘分数赋值部分
				if (BoardPosition[Buff.X][Buff.Y] == BLANK) 
				{
					HumanValue[Buff.X][Buff.Y] = GetScore(BoardPosition, Flag, HumanFlag, Buff, Bans);
					AIValue[Buff.X][Buff.Y] = GetScore(BoardPosition, -Flag, HumanFlag, Buff, Bans);
					Value[Buff.X][Buff.Y] += HumanValue[Buff.X][Buff.Y] + AIValue[Buff.X][Buff.Y];
				}
				else
					Value[Buff.X][Buff.Y] = 0;
				//取最大值，以及最大值对应的点
				if (HumanValue[Buff.X][Buff.Y] > MaxHumanValue)
				{
					MaxHumanValue = HumanValue[Buff.X][Buff.Y];
					HumanTemp = Buff;
				}
				if (AIValue[Buff.X][Buff.Y] > MaxAIValue)
				{
					MaxAIValue = AIValue[Buff.X][Buff.Y];
					AITemp = Buff;
				}
				if (Value[Buff.X][Buff.Y]>Value[Temp.X][Temp.Y])
					Temp = Buff;
			}
		}

		if (MaxAIValue >= 1000000)
			AIThreatLevel = 3;
		else if (MaxAIValue >= 40000)
			AIThreatLevel = 2;
		else if (MaxAIValue >= 1900)
			AIThreatLevel = 1;

		if (MaxHumanValue >= 5000000)
			HumanThreatLevel = 3;
		else if (MaxHumanValue >= 200000)
			HumanThreatLevel = 2;
		else if (MaxHumanValue >= 8000)
			HumanThreatLevel = 1;

		if (HumanThreatLevel == 3 || AIThreatLevel == 3)
			ThreatLevel = 3;
		else if (HumanThreatLevel == 2 || AIThreatLevel == 2)
			ThreatLevel = 2;
		else if (HumanThreatLevel == 1 || AIThreatLevel == 1)
			ThreatLevel = 1;
		//先手情况专注攻击
		if (ChessFlag==BLACK)
		{
			//棋盘已满的情况
			if (MaxHumanValue == 0 && MaxAIValue == 0)
			{
				Temp.X = -1;
				Temp.Y = -1;
				return Temp;
			}
			//有胜点的情况
			if (ThreatLevel == 3)
				return Temp;

			return HumanThreatLevel >= AIThreatLevel ? HumanTemp : AITemp;
		}
		else
			return Temp;

	}
	//对于AI来说
	else
	{
		for (Buff.X = 0; Buff.X < BOARDSIZE; Buff.X++)
		{
			for (Buff.Y = 0; Buff.Y < BOARDSIZE; Buff.Y++)
			{
				//棋盘分数赋值部分
				if (BoardPosition[Buff.X][Buff.Y] == BLANK)
				{
					AIValue[Buff.X][Buff.Y] = GetScore(BoardPosition, Flag, AIFlag, Buff, Bans);
					HumanValue[Buff.X][Buff.Y] = GetScore(BoardPosition, -Flag, AIFlag, Buff, Bans);
					Value[Buff.X][Buff.Y] += HumanValue[Buff.X][Buff.Y] + AIValue[Buff.X][Buff.Y];
				}
				else
					Value[Buff.X][Buff.Y] = 0;
				//取最大值，以及最大值对应的点
				if (HumanValue[Buff.X][Buff.Y] > MaxHumanValue)
				{
					MaxHumanValue = HumanValue[Buff.X][Buff.Y];
					HumanTemp = Buff;
				}
				if (AIValue[Buff.X][Buff.Y] > MaxAIValue)
				{
					MaxAIValue = AIValue[Buff.X][Buff.Y];
					AITemp = Buff;
				}
				if (Value[Buff.X][Buff.Y]>Value[Temp.X][Temp.Y])
					Temp = Buff;
			}
		}

		if (MaxHumanValue >= 1000000)
			HumanThreatLevel = 3;
		else if (MaxHumanValue >= 40000)
			HumanThreatLevel = 2;
		else if (MaxHumanValue >= 1900)
			HumanThreatLevel = 1;

		if (MaxAIValue >= 5000000)
			AIThreatLevel = 3;
		else if (MaxAIValue >= 200000)
			AIThreatLevel = 2;
		else if (MaxAIValue >= 8000)
			AIThreatLevel = 1;

		if (HumanThreatLevel == 3 || AIThreatLevel == 3)
			ThreatLevel = 3;
		else if (HumanThreatLevel == 2 || AIThreatLevel == 2)
			ThreatLevel = 2;
		else if (HumanThreatLevel == 1 || AIThreatLevel == 1)
			ThreatLevel = 1;
		//先手情况专注攻击
		if (ChessFlag == WHITE)
		{
			//棋盘已满的情况
			if (MaxHumanValue == 0 && MaxAIValue == 0)
			{
				Temp.X = -1;
				Temp.Y = -1;
				return Temp;
			}
			//有胜点的情况
			if (ThreatLevel == 3)
				return Temp;

			return HumanThreatLevel >= AIThreatLevel ? HumanTemp : AITemp;
		}
		else
			return Temp;

	}
}
//开局布局，必胜开局是花月局和浦月局，必败开局是游星局和彗星局
int Layout(Position Current,Position *Best)
{
	// 只考虑前面三步的情况
	if (Counter >= 3)
		return 0;
	if (Current.X <= 2 || Current.X >= BOARDSIZE - 3 || Current.Y <= 2 || Current.Y >= BOARDSIZE - 3)
		return 0;
	if (ChessFlag == WHITE)// 如果计算机先手，则考虑第三手
	{
		// 计算机第一手必然在天元，那么紧邻有8种位置，其他位置不考虑。
		int Random = 0;
		srand((unsigned)time(NULL));
		Random = rand() % 2;

		if (Counter == 0)
		{
			Best->X = 7;
			Best->Y = 7;
			return 1;
		}

		// 花月
		if ((Current.X == 6 || Current.X == 8) && Current.Y == 7)
			Best->X = Current.X, Best->Y = (Random ? 6 : 8);
		else if (Current.X == 7 && (Current.Y == 6 || Current.Y == 8))
			Best->X = (Random ? 6 : 8), Best->Y = Current.Y;

		// 浦月
		else if (Current.X == 6 && Current.X == 8)
			Random ? (Best->X = Best->Y = 8) : (Best->X = Best->Y = 6);
		else if (6 == Current.X && 6 == Current.Y)
			Random ? (Best->X = 8, Best->Y = 6) : (Best->X = 6, Best->Y = 8);
		else if (8 == Current.X && 6 == Current.Y)
			Random ? (Best->X = Best->Y = 6) : (Best->X = Best->Y = 8);
		else if (8 == Current.X && 8 == Current.Y)
			Random ? (Best->X = 8, Best->Y = 6) : (Best->X = 6, Best->Y = 8);

		// 若不是上面两种棋型,则判断白棋的相对位置
		else
		{
			if (Current.X <= 7 && Current.Y <= 7)
				Best->X = Best->Y = 8;
			else if (Current.X >= 7 && Current.Y >= 7)
				Best->X = Best->Y = 6;
			else if (Current.X >= 7 && Current.Y <= 7)
				Best->X = 6, Best->Y = 8;
			else
				Best->X = 8, Best->Y = 6;
		}
	}

	else //计算机执白，只考虑第二手
	{
		// 四种情况，随机
		int Random = 0;
		srand((unsigned)time(NULL));
		Random = rand() % 4;

		while (1)
		{
			if (Random==0)
			{
				if (Current.X - 1 >= 0)
				{
					Best->X = Current.X - 1, Best->Y = Current.Y;
					break;
				}
				else
					Random = 1;
			}
			if (Random==1)
			{
				if (Current.X + 1 < BOARDSIZE)
				{
					Best->X = Current.X + 1, Best->Y = Current.Y;
					break;
				}
				else
					Random = 2;
			}
			if (Random==2)
			{
				if (Current.Y - 1 >= 0)
				{
					Best->X = Current.X, Best->Y = Current.Y - 1;
					break;
				}
				else
					Random = 3;
			}
			if (Random==3)
			{
				if (Current.Y + 1 < BOARDSIZE)
				{
					Best->X = Current.X, Best->Y = Current.Y + 1;
					break;
				}
				else
					Random = 0;
			}
		}

	}
	return 1;
}
//限制框，递归时只考虑框内的位置
void LimitBox(int BoardPosition [][BOARDSIZE])
{
	MinTop =  MinLeft =  5;
	MaxBottom = MaxRight = 9;
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			if (BoardPosition[i][j]!=0)
			{
				if (i - 2 < MinTop)
					MinTop = i - 2;
				else if(i + 2 > MaxBottom)
					MaxBottom = i + 2;
				if (j - 2 < MinLeft)
					MinLeft = j - 2;
				else if (j + 2 > MaxRight)
					MaxRight = j + 2;
			}
		}
	}
}
//从这里开始修改
Position AIDraw(int BoardPosition[][BOARDSIZE], int Flag ,Position Previous)
{
	Position AIBest; //AI计算出的最佳落子位置

	if (Layout(Previous,&AIBest))  //设置开局
		return AIBest;

	return GetBestPosition(BoardPosition, Flag);
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
