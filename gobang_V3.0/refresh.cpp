#include "stdafx.h"
#include "refresh.h"


void refresh(char* buff, int StartX, int StartY)
{
	HANDLE Handle;
	COORD XYPosition;

	XYPosition.X = StartX;
	XYPosition.Y = StartY;
	Handle = GetStdHandle(STD_OUTPUT_HANDLE);  //��ñ�׼����ľ��
	SetConsoleCursorPosition(Handle, XYPosition);  //������ƶ���ָ��λ��
	printf("%s", buff);
	XYPosition.X = 0;
	XYPosition.Y = 31;
	SetConsoleCursorPosition(Handle, XYPosition);
}
void RefreshNum(int buff, int StartX, int StartY)
{
	HANDLE Handle;
	COORD XYPosition;

	XYPosition.X = StartX;
	XYPosition.Y = StartY;
	Handle = GetStdHandle(STD_OUTPUT_HANDLE);  //��ñ�׼����ľ��
	SetConsoleCursorPosition(Handle, XYPosition);  //������ƶ���ָ��λ��
	printf("%.2d", buff);
	XYPosition.X = 0;
	XYPosition.Y = 31;
	SetConsoleCursorPosition(Handle, XYPosition);
}
//ghjgkjhjl
//jvhvhu uuh gyug uyig ug yu