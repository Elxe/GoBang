#pragma once

#include "define.h"
#include"refresh.h"
#include"displaychessboard.h"

//ջ�ṹ���Ƚ���������ڴ�������λ��

//��ֵһ����������λ�õ����顢��ǰλ�á��Լ�ջ��λ�ã��޷���ֵ
void push(Position record[], Position Current, int* StackMark);
//��ֵһ����������λ�õ����顢�Լ�ջ��λ�ã�����һ��λ��
Position pop(Position record[], int* StackMark);
//��ֵһ����������λ�õ����顢�Լ�ջ��λ�ã�����һ��λ��
Position getposition(Position record[], int* StackMark);
//���壬��ֵ���̶�ά���飬��ǰ�����ˣ�
void regret(int BoardPosition[][BOARDSIZE], int Flag, Position Cursor,Position PreviousCursor);
/*******����ʱ���ӣ�������ֵ�Լ������ϸ�λ�õ����ӣ���ӡ��λ�õ�����*******/
void Draw(int BoardPosition[][BOARDSIZE], int Flag, Position PreviousCursor, Position Cursor);
