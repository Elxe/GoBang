#pragma once
#include "define.h"

typedef struct Chong3Chong4 { int Chong3; int Chong4; int TiaoChong4; } Chong3Chong4;//记录冲三、冲四、跳冲四
typedef struct Huo2Huo3 { int Huo2; int Huo3; }Huo2Huo3;//记录连二、连三
typedef struct Tiao2Tiao3 { int Tiao2; int Tiao3; }Tiao2Tiao3;//记录跳二、跳三
typedef struct XiaoQiXing { int Chong2; int Huo1; int Chong1; }XiaoQiXing;//记录冲二、活一、冲一
typedef struct TreeNode { Position Location; int Socre;  };

//连五函数，用于搜索连五或者长连，连五返回1，长连返回2，无返回0
int GetLian5(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans);
//活四函数，用于搜索活四以及禁手情况，返回活四的个数
int GetHuo4(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans);
//冲四冲三函数，用于搜索冲四冲三以及跳冲四，返回一个包含冲四冲三以及跳冲四个数的一个结构体
Chong3Chong4 GetChong3Chong4(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans);
//连二连三函数，用于搜索连二连三，返回一个包含连二连三个数的一个结构体
Huo2Huo3 GetHuo2Huo3(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans);
//跳活三跳活二函数，用于搜索跳二跳三，返回一个包含跳二跳三个数的结构体
Tiao2Tiao3 GetTiao2Tiao3(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans);
//小棋型函数，用于搜索除以上大棋型以外的棋型，包括冲一、活一、冲二
XiaoQiXing GetXiaoQiXing(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans);


Position AIDraw(int BoardPosition[][BOARDSIZE], int Flag,Position Previous);
int IfBans(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans);