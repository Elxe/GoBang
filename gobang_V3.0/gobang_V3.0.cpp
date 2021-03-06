// gobang_V3.0.cpp: 定义控制台应用程序的入口点。

#include "stdafx.h"
#include "AImansprite.h"
#include "displaychessboard.h"
#include "movecursor.h"
#include "checkwinner.h"
#include "refresh.h"
#include "define.h"

int Mode;
Position Current;  //当前落子位置
Position Record[BOARDSIZE*BOARDSIZE];  //记录所有落子情况
int ChessBoard[BOARDSIZE][BOARDSIZE];
int Flag;  //当前落子人
int Counter; //落子数
int StackMark;  //栈顶位置
int ChessFlag; //玩家选定的颜色
int Bans; //禁手
int Depth=2;
void SoloMode();
void DuoMode();
int MaxTotal ;
int MinTotal ;
int Number = 0;

void Copy(char* CopyStr,const char* Str)  //复制函数，去掉后面的'\0'
{
	while (*Str!='\0')
		*CopyStr++ = *Str++;
}
void Initialize()  //初始化
{
	for (int i = 0; i < BOARDSIZE; i++)
		for (int j = 0; j < BOARDSIZE; j++)
		{
			ChessBoard[i][j] = 0;
		}
	StackMark = 0;
	Counter = 0;
	Flag = BLACK;  //先手
	int i, j;
	for (i = 0; i < BOARDSIZE; i++)
		for (j = 0; j < BOARDSIZE; j++)
			ChessBoard[i][j] = BLANK;
	Current.X = BOARDSIZE / 2;
	Current.Y = BOARDSIZE / 2;
	system("cls");
	DisplayChessBoard();
}
void WinnerScreen(int Ban,int Winner)
{
	char* ShowText="";
	if (Ban==0)
	{
		switch (Winner)  //检查胜负
		{
		case BLACK:
			ShowText = "大吉大利，黑方今晚吃鸡";
			refresh(ShowText, (BOARDSIZE * 4 + 3 - strlen(ShowText)) / 2, (BOARDSIZE * 2 + 1) / 2);
			_getch();
			/******重新初始化*******/
			if (Mode == 1) SoloMode();
			else if (Mode == 2) DuoMode();
			break;
		case WHITE:
			ShowText = "大吉大利，白方今晚吃鸡";
			refresh(ShowText, (BOARDSIZE * 4 + 3 - strlen(ShowText)) / 2, (BOARDSIZE * 2 + 1) / 2);
			_getch();
			/******重新初始化*******/
			if (Mode == 1) SoloMode();
			else if (Mode == 2) DuoMode();
			break;
		case DOUBLEWIN:
			ShowText = "大吉大利，双方今晚吃鸡";
			refresh(ShowText, (BOARDSIZE * 4 + 3 - strlen(ShowText)) / 2, (BOARDSIZE * 2 + 1) / 2);
			_getch();
			/******重新初始化*******/
			if (Mode == 1) SoloMode();
			else if (Mode == 2) DuoMode();
			break;
		default:
			break;
		}
	}
	else
	{
		switch (Ban)  //检查胜负
		{
		case 1:
			ShowText = "长连禁手";
			refresh(ShowText, (BOARDSIZE * 4 + 3 - strlen(ShowText)) / 2, (BOARDSIZE * 2 + 1) / 2);
			_getch();
			/******重新初始化*******/
			if (Mode == 1) SoloMode();
			else if (Mode == 2) DuoMode();
			break;
		case 2:
			ShowText = "三三禁手";
			refresh(ShowText, (BOARDSIZE * 4 + 3 - strlen(ShowText)) / 2, (BOARDSIZE * 2 + 1) / 2);
			_getch();
			/******重新初始化*******/
			if (Mode == 1) SoloMode();
			else if (Mode == 2) DuoMode();
			break;
		case 3:
			ShowText = "四四禁手";
			refresh(ShowText, (BOARDSIZE * 4 + 3 - strlen(ShowText)) / 2, (BOARDSIZE * 2 + 1) / 2);
			_getch();
			/******重新初始化*******/
			if (Mode == 1) SoloMode();
			else if (Mode == 2) DuoMode();
			break;
		default:
			break;
		}
	}
}
int WelcomeScreen()
{
	char* ShowText="";  //即将输出的字符并且初始化
	int CursorY = 1;  //初始化为单人模式
	int BuffCursorY;  //按键缓冲
	int Input;  //输入按键

	/*************打印介绍内容*************/
	system("cls");  //首先清空屏幕
	ShowText = "五子棋 Version3.0.0";
	refresh(ShowText,(BOARDSIZE*4+3-strlen(ShowText))/2,2);
	ShowText = "------------------------------------------------------";
	refresh(ShowText, (BOARDSIZE * 4 + 3 - strlen(ShowText)) / 2, 5);
	ShowText = "单人模式";
	refresh(ShowText, (BOARDSIZE * 4 + 3 - strlen(ShowText)) / 2, 8);
	ShowText = "双人模式";
	refresh(ShowText, (BOARDSIZE * 4 + 3 - strlen(ShowText)) / 2, 11);
	ShowText = "游戏设置";
	refresh(ShowText, (BOARDSIZE * 4 + 3 - strlen(ShowText)) / 2, 14);
	ShowText = "游戏规则";
	refresh(ShowText, (BOARDSIZE * 4 + 3 - strlen(ShowText)) / 2, 17);
	ShowText = "关于我们";
	refresh(ShowText, (BOARDSIZE * 4 + 3 - strlen(ShowText)) / 2, 20);
	ShowText = "退出游戏";
	refresh(ShowText, (BOARDSIZE * 4 + 3 - strlen(ShowText)) / 2, 23);
	ShowText = "------------------------------------------------------";
	refresh(ShowText, (BOARDSIZE * 4 + 3 - strlen(ShowText)) / 2, 26);
	ShowText = "Copyright 2017 by Zhang Ningxin. All rights reserved.";
	refresh(ShowText, (BOARDSIZE * 4 + 3 - strlen(ShowText)) / 2, 27);
	/*****初始光标*****/
	refresh("→", (BOARDSIZE * 4 + 3) / 2 - 10, CursorY * 3 + 5);
	refresh("←", (BOARDSIZE * 4 + 3) / 2 + 8, CursorY * 3 + 5);
	/***********打印模式选择光标***********/
	while ((Input=_getch())!=13)
	{
		BuffCursorY = CursorY;
		switch (Input)  //选择模式
		{
		case 72:
			CursorY--;
			break;
		case 80:
			CursorY++;
			break;
		default:
			break;
		}
		if (CursorY == 0) CursorY = 6;
		else if (CursorY == 7) CursorY = 1;
		refresh(" ", (BOARDSIZE * 4 + 3) / 2 - 10, BuffCursorY * 3 + 5);
		refresh(" ", (BOARDSIZE * 4 + 3) / 2 + 8, BuffCursorY * 3 + 5);
		refresh("→", (BOARDSIZE * 4 + 3) / 2 - 10, CursorY * 3 + 5);
		refresh("←", (BOARDSIZE * 4 + 3) / 2 + 8, CursorY * 3 + 5);
	}
	Mode = CursorY;
	return CursorY;
}
int HumanDecide()
{
	int Choice;
	Choice = Control(&Current, ChessBoard, Flag);
	if (Choice == -1)//悔棋
		Flag = -Flag;
	else if (Choice==0)
	{
		//检查有无胜者
		WinnerScreen(IfBans(ChessBoard,Flag,Current,Bans),CheckWinner(ChessBoard, Flag, Current));
		Flag = -Flag;  //修正落子顺序
	}
	return Choice;
}
void AIDecide()
{
	Position AiPosition;  //ai走子位置
/////////////////////////////
	MaxTotal = 0;
	MinTotal = 0;
////////////////////
	AiPosition.X = 7;
	AiPosition.Y = 7;  //初始化
	AiPosition = AIDraw(ChessBoard, Flag,Current); //ai走子位置赋值
	Draw(ChessBoard, Flag, Current, AiPosition);
	//将光标移动到ai落子位置
	MoveCursor(Current, AiPosition);
	Current = AiPosition;  //记录
	//检查有无胜者
	WinnerScreen(IfBans(ChessBoard, Flag, Current, Bans), CheckWinner(ChessBoard, Flag, Current));
	Flag = -Flag;  //修正落子顺序
}

void SoloMode()
{
	int Choice;
	Initialize();  //初始化
	while (1)
	{
		//人落子
		if (Flag==ChessFlag)
		{
			Choice = HumanDecide();
			if (Choice == -1)
				HumanDecide();
			else if (Choice == -2)
				return;
		}
		//AI落子
		else AIDecide();
	}
}
void DuoMode()
{
	int Choice;
	Initialize();  //初始化
	while (1)
	{ 
		Choice = HumanDecide();
		if (Choice == -2)
			return;
	}
}
void GameSetting()
{
	char* ShowText = "";  //即将输出的字符并且初始化
	int CursorY = 1;  //初始化为单人模式
	int BuffCursorY;  //按键缓冲
	int Input;  //输入按键

				/*************打印介绍内容*************/
	system("cls");  //首先清空屏幕
	ShowText = "五子棋 Version3.0.0";
	refresh(ShowText, (BOARDSIZE * 4 + 3 - strlen(ShowText)) / 2, 2);
	ShowText = "------------------------------------------------------";
	refresh(ShowText, (BOARDSIZE * 4 + 3 - strlen(ShowText)) / 2, 5);
	ShowText = "选择先后手：";
	refresh(ShowText,12, 8);
	ShowText = "先手";
	refresh(ShowText, 34, 8);
	ShowText = "后手";
	refresh(ShowText, 46, 8);
	ShowText = "选择是否禁手：";
	refresh(ShowText, 12, 11);
	ShowText = "禁手";
	refresh(ShowText,34, 11);
	ShowText = "不禁手";
	refresh(ShowText, 46, 11);
	ShowText = "AI搜索深度：";
	refresh(ShowText, 12, 14);
	RefreshNum(Depth, 34, 14);
	refresh("◆", 36 - ChessFlag * 6, 1 * 3 + 5);
	refresh("◆", 30 + !Bans * 12, 2 * 3 + 5);

	ShowText = "------------------------------------------------------";
	refresh(ShowText, (BOARDSIZE * 4 + 3 - strlen(ShowText)) / 2, 26);
	ShowText = "Copyright 2017 by Zhang Ningxin. All rights reserved.";
	refresh(ShowText, (BOARDSIZE * 4 + 3 - strlen(ShowText)) / 2, 27);
	/*****初始光标*****/
	refresh("→", 8, CursorY * 3 + 5);
	/***********打印模式选择光标***********/
	while ((Input = _getch()) != 13&&Input!=27)
	{
		BuffCursorY = CursorY;
		switch (Input)  //选择模式
		{
		case 72:
			CursorY--;
			break;
		case 80:
			CursorY++;
			break;
		case 75:
			switch (CursorY)
			{
			case 1:
				ChessFlag = -ChessFlag;
				//利用正负性,中点36
				refresh(" ", 36 + ChessFlag * 6, CursorY * 3 + 5);
				refresh("◆", 36 - ChessFlag * 6, CursorY * 3 + 5);
				break;
			case 2:
				Bans = !Bans;
				//起点30
				refresh(" ", 30 + Bans * 12, CursorY * 3 + 5);
				refresh("◆", 30 + !Bans * 12, CursorY * 3 + 5);
				break;
			case 3:
				Depth--;
				if (Depth >= 100) Depth = 1;
				else if (Depth <= 0) Depth = 99;
				RefreshNum(Depth, 34, 14);
				break;
			default:
				break;
			}
			break;
		case 77:
			switch (CursorY)
			{
			case 1:
				ChessFlag = -ChessFlag;
				//利用正负性,中点36
				refresh(" ", 36 + ChessFlag * 6, CursorY * 3 + 5);
				refresh("◆", 36 - ChessFlag * 6, CursorY * 3 + 5);
				break;
			case 2:
				Bans = !Bans;
				//起点30
				refresh(" ", 30+Bans*12, CursorY * 3 + 5);
				refresh("◆", 30 + !Bans * 12, CursorY * 3 + 5);
				break;
			case 3:
				Depth++;
				if (Depth >= 100) Depth = 1;
				else if (Depth <= 0) Depth = 99;
				RefreshNum(Depth, 34, 14);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		if (CursorY == 0) CursorY = 3;
		else if (CursorY == 4) CursorY = 1;
		refresh(" ", 8, BuffCursorY * 3 + 5);
		refresh("→", 8, CursorY * 3 + 5);
	}
	return;
}
void GameRule()
{
	;
}
void AboutUs()
{
	char* ShowText="";
	ShowText = "研发团队：逃跑的清流";
	refresh(ShowText, 4, 4);
	ShowText = "研发团队成员：";
	refresh(ShowText, 4, 6);
	ShowText = "张宁鑫：";
	refresh(ShowText, 8, 8);
	ShowText = "邮箱：zhangningxin16@mails.ucas.cn";
	refresh(ShowText, 16, 9);
	ShowText = "个人主页：";
	refresh(ShowText, 16, 11);
	_getch();
}

void RunGame()
{
	//模式选择
	while (1)
	{
		switch (WelcomeScreen())
		{
		case 1:
			system("cls");
			SoloMode();
			break;
		case 2:
			system("cls");
			DuoMode();
			break;
		case 3:
			system("cls");
			GameSetting();
			break;
		case 4:
			system("cls");
			GameRule();
			break;
		case 5:
			system("cls");
			AboutUs();
			break;
		case 6:
			exit(0);
			break;
		default:
			break;
		};
	}
}
void main()
{
	system("五子棋V3.0");//设置窗口标题
	system("mode con cols=63 lines=48");//设置窗口大小
	system("color F0");//设置控制台颜色
	while (1)//一直循环游戏
	{
		//设置项的初始化
		ChessFlag = 1;
		Bans = 0;
		//加载游戏
		RunGame();
	}
}