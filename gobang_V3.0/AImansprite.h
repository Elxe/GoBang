#pragma once
#include "define.h"
#define MAX 100000000  //Alpha��Beta�����ֵ
#define MIN -100000000  //Alpha��Beta����Сֵ


typedef struct Chong3Chong4 { int Chong3; int Chong4; int TiaoChong4; } Chong3Chong4;//��¼���������ġ�������
typedef struct Huo2Huo3 { int Huo2; int Huo3; }Huo2Huo3;//��¼����������
typedef struct Tiao2Tiao3 { int Tiao2; int Tiao3; }Tiao2Tiao3;//��¼����������
typedef struct XiaoQiXing { int Chong2; int Huo1; int Chong1; }XiaoQiXing;//��¼�������һ����һ
typedef struct TreeNode { Position Location; int Socre=0;}TreeNode;
typedef struct NodeBuff { Position Location; int Length=0; }NodeBuff;
typedef struct NodeImf { int Alpha=0; int Beta=0; int Tpye=0; }NodeImf;
typedef struct Box { int MinLeft = 5; int MaxRight = 9; int MinTop = 5; int MaxBottom=9; }Box;


//���庯������������������߳��������巵��1����������2���޷���0
int GetLian5(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans);
//���ĺ������������������Լ�������������ػ��ĵĸ���
int GetHuo4(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans);
//���ĳ��������������������ĳ����Լ������ģ�����һ���������ĳ����Լ������ĸ�����һ���ṹ��
Chong3Chong4 GetChong3Chong4(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans);
//������������������������������������һ��������������������һ���ṹ��
Huo2Huo3 GetHuo2Huo3(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans);
//���������������������������������������һ�������������������Ľṹ��
Tiao2Tiao3 GetTiao2Tiao3(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans);
//С���ͺ������������������ϴ�������������ͣ�������һ����һ�����
XiaoQiXing GetXiaoQiXing(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans);
//Alpha��Beta��֦�㷨
int GetMinValue(int BoardPosition[][BOARDSIZE], int CDepth, int Flag, int Alpha, int Beta);
int GetMaxValue(int BoardPosition[][BOARDSIZE], int CDepth, int Flag, int Alpha, int Beta);
//���庯��������һ������
Position AIDraw(int BoardPosition[][BOARDSIZE], int Flag,Position Previous);
//���ֺ������ж��Ƿ����
int IfBans(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans);
//���ƿ򣬵ݹ�ʱֻ���ǿ��ڵ�λ��
void LimitBox(int BoardPosition[][BOARDSIZE], Box *Limitation);