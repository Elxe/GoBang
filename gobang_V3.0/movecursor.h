#pragma once
#include"refresh.h"
#include "define.h"
#include "displaychessboard.h"

//ר������ת�����λ��
void MoveCursor(Position BuffCursor, Position Cursor);
/**********�����ֶ�����ʱ�ƶ���꣬����һ������ֵ********/
/**********����ͨ������ֵ�ķ����������˵���-1Ϊ�������˵���-2Ϊ����*********/
int Control(Position* Cursor, int BoardPosition[][BOARDSIZE], int Flag);
/*******����ʱ���ӣ�������ֵ�Լ������ϸ�λ�õ����ӣ���ӡ��λ�õ�����*******/
void Draw(int BoardPosition[][BOARDSIZE], int Flag, Position PreviousCursor, Position Cursor);

//ջ�ṹ���Ƚ���������ڴ�������λ��

//��ֵһ����������λ�õ����顢��ǰλ�á��Լ�ջ��λ�ã��޷���ֵ
void push(Position record[], Position Current);
//��ֵһ����������λ�õ����顢�Լ�ջ��λ�ã�����һ��λ��
Position pop(Position record[]);

//���壬��ֵ���̶�ά���飬��ǰ�����ˣ�
void regret(int BoardPosition[][BOARDSIZE], int Flag, Position Cursor, Position PreviousCursor, Position Previous);
